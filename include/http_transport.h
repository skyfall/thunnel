#ifndef HTTP_TRANSPORT_H
#define HTTP_TRANSPORT_H
#include "transeport.h"

class http_transport :public transeport_conn {
public:
    http_transport();

    
public:
    void OnNewPacket(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) ;
    http_transport* copy_one();
};

#endif