//
// Created by tattsun on 15/06/30.
//

#include "TCPServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace dust {

    TCPServer::TCPServer(int port)
    : sock_(0)
    , port_(port) {
    }

    TCPServer::~TCPServer() {
        Close();
    }

    int TCPServer::Start() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        addr.sin_addr.s_addr = INADDR_ANY;

        if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            return -1;
        }

        if(listen(sock, 5) < 0) {
            return -1;
        }

        const int optVal = 1;
        const socklen_t optLen = sizeof(optVal);
        if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&optVal, optLen) != 0) {
            return -1;
        }

        this->sock_ = sock;
        return 0;
    }

    int TCPServer::Accept() {
        struct sockaddr_in client;
        int csock;
        socklen_t len = sizeof(client);
        csock = accept(sock_, (struct sockaddr *)&client, &len);
        return csock;
    }

    void TCPServer::Close() {
        close(sock_);
    }

    int TCPServer::get_sock_() {
        return sock_;
    }

}