//
// Created by tattsun on 15/06/30.
//

#include "AsyncTCPServer.h"

namespace dust {

    AsyncTCPServer::AsyncTCPServer(EventBase* ev_base, int port)
    : srv_(port) {
        this->ev_base_ = ev_base;
        this->server_cb_ = new _ats_server_cb(this);
        this->on_new_cli_ = nullptr;
    }

    AsyncTCPServer::~AsyncTCPServer() {
        srv_.Close();
    }


    void AsyncTCPServer::set_on_new_cli_(OnNewClient *n) {
        on_new_cli_ = n;
    }

    AsyncTCPServer::OnNewClient* AsyncTCPServer::get_on_new_cli_() {
        return on_new_cli_;
    }

    int AsyncTCPServer::Start() {
        int r = srv_.Start();
        if (r != 0) return r;

        server_ev_ = new Event(srv_.get_sock_(), server_cb_, EV_READ | EV_PERSIST);
        ev_base_->AddListener(server_ev_);
        return r;
    }

    void AsyncTCPServer::Close() {
        srv_.Close();
        ev_base_->DeleteListener(server_ev_);
        delete server_ev_;
        delete server_cb_;
    }

}