//
// Created by tattsun on 15/06/30.
//

#ifndef DUST_TCPSERVER_H
#define DUST_TCPSERVER_H

namespace dust {
    class TCPServer {
        int sock_;
        int port_;
    public:
        TCPServer(int port);
        ~TCPServer();

        int Start();
        int Accept();
        void Close();

        int get_sock_();
    };
}


#endif //DUST_TCPSERVER_H
