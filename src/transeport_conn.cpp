#include "transeport_conn.h"

transeport_conn::transeport_conn(){

}
transeport_conn::~transeport_conn(){
    
}

transeport_conn* transeport_conn::copy_one(){
    printf("transeport_conn  copy_one\n");
    return new transeport_conn();
}

void transeport_conn::OnNewPacket(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf){
    printf("transeport_conn  OnNewPacket\n");
    // if (nread <=0){

    // }
}