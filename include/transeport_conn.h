#ifndef TRANSEPORT_CONN_H
#define TRANSEPORT_CONN_H
#include "transeport.h"


class transeport_conn {
public:
    int fd;
    uv_tcp_t clent;
    transeport* transeport;
    virtual void OnNewPacket(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) ;
    transeport_conn(){
    };
    ~transeport_conn();
    virtual transeport_conn* copy_one();
};


#endif