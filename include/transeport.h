#ifndef TRANSEPORT_H
#define TRANSEPORT_H

#include <mutex>
#include <map>
#include <uv.h>
#include "transeport_conn.h"


class transeport
{
public:
    std::string ip;
    int port ;
    int listenfd;
    int default_back_log;

    transeport_conn* transeport_handl;
    
    uv_loop_t *loop;
    uv_tcp_t serve;

    uv_rwlock_t rwLock;
    std::map<int , transeport_conn*> client_conns;

    int Start();
    void OnNewConnection(uv_stream_t * server, int status);

    transeport(const std::string ip ,const int port , uv_loop_t *loop);
};

#endif