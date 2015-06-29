//
// Created by tattsun on 15/06/29.
//

#include "Event.h"

namespace dust {

    Event::Event(evutil_socket_t sock, EventCallBack callback, short ev_type)
    : sock_(sock)
    , callback_(callback)
    , ev_type_(ev_type){
    }

    evutil_socket_t Event::get_sock_() {
        return sock_;
    }

    EventCallBack* Event::get_callback_() {
        return &callback_;
    }

    short Event::get_ev_type_() {
        return ev_type_;
    }

    void Event::set_event_(event *event) {
        event_ = event;
    }

    event* Event::get_event_() {
        return event_;
    }


    EventBase::EventBase() {
        ev_base_ = event_base_new();
    }

    EventBase::~EventBase() {
        event_base_free(ev_base_);
    }

    void (*_wrap_callback)(evutil_socket_t sock, short ev_type, void* args) {
        EventCallBack* cb = (EventCallBack*)args;
        cb->sock = sock;
        cb->ev_type = ev_type;
        cb->Call();
    }

    void EventBase::AddListener(Event* ev) {
        event* e = event_new(ev_base_, ev->get_sock_(),
                             ev->get_ev_type_(), _wrap_callback,
                             (void*)ev->get_callback_());
        ev->set_event_(e);
    }

    void EventBase::DeleteListener(Event *ev) {
        event_del(ev->get_event_());
    }

    void EventBase::LoopOnce() {
        event_base_loop(ev_base_, 1);
    }

    void EventBase::LoopForever() {
        event_base_dispatch(ev_base_);
    }


}