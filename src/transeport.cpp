#include <string>
#include <uv.h>
#include "transeport.h"
// #include "http_transport.h"

transeport::transeport(const std::string ip ,const int port , uv_loop_t *loop):ip(ip),port(port),loop(loop){
    uv_rwlock_init(&rwLock);
}

// 启动服务
int transeport::Start(){
    
    int res;
    res = uv_tcp_init(loop,&serve);
    if (res){
        fprintf(stderr,"tcp_init err:%s",uv_err_name(res));
        return res;
    }
    

    struct sockaddr_in addr;
    res = uv_ip4_addr(ip.c_str(),port,&addr);
    if (res){
        fprintf(stderr,"uv_ip4_addr err:%s",uv_err_name(res));
        return res;
    }

    res = uv_tcp_bind(&serve , (const struct sockaddr *)&addr,0);
    if (res){
        fprintf(stderr,"uv_tcp_bind err:%s",uv_err_name(res));
        return res;
    }

    serve.data = this;
    res = uv_listen((uv_stream_t*)&serve,default_back_log, [](uv_stream_t * server, int status) {
        ((transeport *)server->data)->OnNewConnection(server, status);
    });

    if (res){
        fprintf(stderr,"uv_listen err:%s",uv_err_name(res));
        return res;
    }

    return 0;
}

 void transeport::OnNewConnection(uv_stream_t * server, int status){
    int res;
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    transeport_conn *conn =  transeport_handl.copy_one();

    uv_tcp_t* client = &conn->clent;


    res = uv_tcp_init(loop, client);
    if (res){
        fprintf(stderr,"uv_tcp_init err:%s",uv_err_name(res));
        return ;
    }
    if (uv_accept(server, (uv_stream_t *)client) == 0) {
        conn->fd = client->accepted_fd;
        conn->transeport = this;

        uv_rwlock_wrlock(&rwLock);
        client_conns.insert(std::map<int,transeport_conn*>::value_type(conn->fd,conn));
        uv_rwlock_wrunlock(&rwLock);

        client->data = conn;
        uv_read_start((uv_stream_t *) client,
            [](uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf){
                buf->base = (char *)malloc(suggested_size);
                buf->len = suggested_size;
            },
            [](uv_stream_t *client, ssize_t nread, const uv_buf_t *buf){
                 ((transeport_conn*)client->data)->OnNewPacket(client, nread, buf);
            }
        );

    }else {
        free(conn);
        uv_close((uv_handle_t *) client, NULL);
    }
 }