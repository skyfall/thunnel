#include "http_transport.h"

http_transport::http_transport(){

}

void transeport_conn::OnNewPacket(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    printf("http_transport  OnNewPacket\n");
}   

transeport_conn* transeport_conn::copy_one(){
    printf("http_transport  copy_one\n");
    return new transeport_conn();
}