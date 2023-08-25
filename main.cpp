#include "transeport.h"
#include "http_transport.h"

uv_loop_t loop;

int main(int argc,char* argv[]){

    uv_loop_init(&loop);


    transeport tr("0.0.0.0",9999,&loop);

    http_transport http_tr();
    

    // tr.transeport_handl = http_tr;

    tr.Start();

    return uv_run(&loop,UV_RUN_DEFAULT);


}