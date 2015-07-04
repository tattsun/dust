//
// Created by tattsun on 15/07/05.
//

#include <dust/async/Event.h>
#include <dust/async/AsyncTCPServer.h>

#include <assert.h>
#include <iostream>

using namespace dust;

struct read_cb : public BufferEventDataCallBack {
    void Call(BufferEvent* bufev) {
        std::cout << "read_cb::Call" << std::endl;

        /*
        size_t buflen = 1024;
        char* buf = (char*)malloc(buflen);
        size_t readt = bufev->Read(buf, buflen);

        std::cout << "Received: ";
        for(size_t i=0; i < readt; i++) {
            putchar(buf[i]);
        }
        std::cout << std::endl;
         */

        ByteChars bc(bufev->Read(1024));

        std::string str(bc.c_str(), bc.length());

        std::cout << "Received: " << str << std::endl;
    }
};

struct newcli_cb : public AsyncTCPServer::OnNewClient {
    void Call(BufferEvent* bufev) {
        std::cout << "Accepted new clinet" << std::endl;
        read_cb* read_callback = new read_cb();

        bufev->Enable(EV_READ);
        bufev->SetCallBack(read_callback, NULL, NULL);
        std::cout << "Call finished" << std::endl;
    }
};

int main() {
    int res;

    EventBase ev_base;

    AsyncTCPServer server(&ev_base, 10001);
    newcli_cb newcli_cb_i;

    server.set_on_new_cli_(&newcli_cb_i);
    res = server.Start();
    assert(res == 0);

    res = ev_base.LoopForever();
    assert(res == 0);
}