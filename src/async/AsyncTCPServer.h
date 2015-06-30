//
// Created by tattsun on 15/06/30.
//

#ifndef DUST_ASYNCTCPSERVER_H
#define DUST_ASYNCTCPSERVER_H

#include "../network/TCPServer.h"
#include "./Event.h"

namespace dust {
    class AsyncTCPServer {
    public:
        struct OnNewClient {
            OnNewClient(){};
            ~OnNewClient() = default;
            virtual void Call(int csock) = 0;
        };

        AsyncTCPServer(EventBase* ev_base, int port);
        ~AsyncTCPServer();

        void set_on_new_cli_(OnNewClient* n);
        OnNewClient* get_on_new_cli_();

        int Start();
        void Close();

        TCPServer& get_srv_();
    private:
        struct _ats_server_cb : public EventCallBack {
            _ats_server_cb(AsyncTCPServer* ats) {
                this->ats = ats;
            }
            ~_ats_server_cb() = default;
            AsyncTCPServer* ats;
            void Call() {
                int csock = ats->get_srv_().Accept();
                if(ats->get_on_new_cli_()) {
                    ats->get_on_new_cli_()->Call(csock);
                }
            }
        };
        TCPServer srv_;
        EventBase* ev_base_;
        Event* server_ev_;
        _ats_server_cb* server_cb_;
        OnNewClient* on_new_cli_;
    };
}


#endif //DUST_ASYNCTCPSERVER_H
