#include <uv.h>
#include <stdlib.h>
#include <string>
#include "thunnel_conn.h"

const int DEFAULT_BACKLOG = 100;

std::string linsten_ip;

int port ;

uv_loop_t loop;


void on_new_connection(uv_stream_t *server, int status);

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);

void read_cb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)

int main(int argc,char* argv[]){
    uv_loop_init(&loop);
    // 监听网络信息

    // transeport aaa(linsten_ip,port,&loop);

    uv_tcp_t serve;
    uv_tcp_init(&loop,&serve);

    struct sockaddr_in addr;
    uv_ip4_addr(linsten_ip.c_str(),port,&addr);

    uv_tcp_bind(&serve , (const struct sockaddr *)&addr,0);
    
    if (int r = uv_listen((uv_stream_t*)&serve,DEFAULT_BACKLOG,on_new_connection) && r){
        fprintf(stderr,"listen err %s\n",uv_strerror(r));
        return 1;
    }

    return uv_run(&loop,UV_RUN_DEFAULT);

}

void on_new_connection(uv_stream_t *server, int status){
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));//为tcp client申请资源
    uv_tcp_init(&loop, client);//初始化tcp client句柄
     //判断accept是否成功
    if (uv_accept(server, (uv_stream_t *) client) == 0) {
        //从传入的stream中读取数据，read_cb会被多次调用，直到数据读完，或者主动调用uv_read_stop方法停止
        // client->accepted_fd
        thunnel_conn *conn = new thunnel_conn(client->accepted_fd);
        client->data = conn;
        uv_read_start((uv_stream_t *) client, alloc_buffer, read_cb);
    }else {
        uv_close((uv_handle_t *) client, NULL);
    }
}

//负责为新来的消息申请空间
void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->len = suggested_size;
  buf->base = static_cast<char *>(malloc(suggested_size));
}



void read_cb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf){

}