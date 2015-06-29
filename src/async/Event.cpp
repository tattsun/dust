//
// Created by tattsun on 15/06/29.
//

#include "Event.h"

namespace dust {

    Event::Event(evutil_socket_t sock, EventCallBack*  callback
            , short ev_type)
    : sock_(sock)
    , ev_type_(ev_type){
        callback_ = callback;
        callback_->ev = this;
    }

    evutil_socket_t Event::get_sock_() {
        return sock_;
    }

    EventCallBack* Event::get_callback_() {
        return callback_;
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

    void _wrap_callback(evutil_socket_t sock, short ev_type, void* args) {
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

    int EventBase::LoopOnce() {
        return event_base_loop(ev_base_, 1);
    }

    int EventBase::LoopForever() {
        return event_base_dispatch(ev_base_);
    }

    event_base* EventBase::get_ev_base_() {
        return ev_base_;
    }

    BufferEvent::BufferEvent(EventBase* base, Event* ev, short ev_type) {
        bufev_ = bufferevent_socket_new(base->get_ev_base_(), ev->get_sock_(), 0);
    }

    BufferEvent::~BufferEvent() {
        bufferevent_free(bufev_);
    }

    int BufferEvent::Enable(short ev_type) {
        return bufferevent_enable(bufev_, ev_type);
    }

    int BufferEvent::Disable(short ev_type) {
        return bufferevent_disable(bufev_, ev_type);
    }

    size_t BufferEvent::Read(void *data, size_t size) {
        return bufferevent_read(bufev_, data, size);
    }

    size_t BufferEvent::Write(const void *data, size_t size) {
        return bufferevent_write(bufev_, data, size);
    }

    std::string BufferEvent::Read(size_t size) {
        char* cs = (char*)malloc(size);
        Read(cs, size);
        std::string str(cs);
        free(cs);
        return str;
    }

    size_t BufferEvent::Write(std::string data) {
        return Write(data.c_str(), data.length());
    }

}