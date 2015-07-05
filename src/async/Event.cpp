//
// Created by tattsun on 15/06/29.
//

#include "Event.h"
#include <assert.h>

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

    void saylog(int s, const char *msg) {
        printf("%d: %s\n", s, msg);
    }

    EventBase::EventBase() {
        event_enable_debug_mode();
        event_set_log_callback(saylog);
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
        event_add(e, NULL);
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

    BufferEvent::BufferEvent(EventBase* base, evutil_socket_t sock) {
        bufev_ = bufferevent_socket_new(base->get_ev_base_(), sock, 0);
        //bufferevent_setwatermark(bufev_, EV_READ, 16, 0);
    }

    BufferEvent::~BufferEvent() {
        bufferevent_free(bufev_);
    }

    void _bufev_wrap_read_callback(bufferevent*, void *ctx) {
        std::cout << "_bufev_wrap_read_callback" << std::endl;
        BufferEvent* bufev = (BufferEvent*)ctx;

        if (bufev->get_readcb_() == NULL) {
            return;
        }

        if(bufev->get_readcb_()) {
            bufev->get_readcb_()->Call(bufev);
        }
    }

    void _bufev_wrap_write_callback(bufferevent*, void *ctx) {
        std::cout << "_bufev_wrap_write_callback" << std::endl;
        BufferEvent* bufev = (BufferEvent*)ctx;

        if(bufev->get_writecb_() == NULL) {
            return;
        }

        if(bufev->get_writecb_()) {
            bufev->get_writecb_()->Call(bufev);
        }
    }

    void _bufev_wrap_event_callback(bufferevent*, short evtype, void* ctx) {
        std::cout << "_bufev_wrap_event_callback" << std::endl;
        BufferEvent* bufev = (BufferEvent*)ctx;

        if (bufev->get_eventcb_() == NULL) {
            return;
        }

        if(bufev->get_eventcb_()) {
            bufev->get_eventcb_()->Call(bufev, evtype);
        }
    }

    void BufferEvent::SetCallBack(BufferEventDataCallBack *readcb, BufferEventDataCallBack *writecb,
                                  BufferEventEvCallBack *eventcb) {
        std::cerr << "Callback set" << std::endl;
        this->readcb_ = readcb;
        this->writecb_ = writecb;
        this->eventcb_ = eventcb;
        bufferevent_setcb(bufev_,
                          _bufev_wrap_read_callback,
                          _bufev_wrap_write_callback,
                          _bufev_wrap_event_callback,
                          (void*)this);
    }

    BufferEventDataCallBack* const BufferEvent::get_readcb_() const {
        return readcb_;
    }

    BufferEventDataCallBack* const BufferEvent::get_writecb_() const {
        return writecb_;
    }

    BufferEventEvCallBack* const BufferEvent::get_eventcb_() const {
        return eventcb_;
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

    int BufferEvent::Write(const void *data, size_t size) {
        return bufferevent_write(bufev_, data, size);
    }

    ByteChars BufferEvent::Read(size_t size) {
        char* cs = (char*)malloc(size);
        size_t recvlen = Read(cs, size);

        /*
        for(int i=0; i < 20; i++) {
            printf("%d: %x\n", i, cs[i]);
        }*/

        ByteChars str(cs, recvlen);
        free(cs);
        return str;
    }

    int BufferEvent::Write(ByteChars data) {
        return Write(data.c_str(), data.length()+1);
    }

}