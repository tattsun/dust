//
// Created by tattsun on 15/06/29.
//

#ifndef DUST_EVENT_H
#define DUST_EVENT_H

#include <iostream>
#include <event2/bufferevent.h>
#include "event2/event.h"

namespace dust {
    class Event;

    struct EventCallBack {
        EventCallBack(){};
        ~EventCallBack() = default;
        virtual void Call() = 0;
        evutil_socket_t sock;
        short ev_type;
        Event* ev;
    };

    class Event {
        evutil_socket_t sock_;
        EventCallBack* callback_;
        short ev_type_;
        event* event_;
    public:
        Event(evutil_socket_t sock, EventCallBack* callback, short ev_type);
        ~Event() = default;

        evutil_socket_t get_sock_();
        EventCallBack* get_callback_();
        short get_ev_type_();
        void set_event_(event* event);
        event* get_event_();
    };

    class EventBase {
        event_base* ev_base_;
    public:
        EventBase();
        ~EventBase();

        void AddListener(Event* ev);
        void DeleteListener(Event* ev);

        int LoopOnce();
        int LoopForever();

        event_base* get_ev_base_();
    };

    class BufferEvent {
        bufferevent* bufev_;
    public:
        BufferEvent(EventBase* base, Event* ev, short ev_type);
        ~BufferEvent();

        int Enable(short ev_type);
        int Disable(short ev_type);

        size_t Read(void* data, size_t size);
        size_t Write(const void* data, size_t size);

        std::string Read(size_t size);
        size_t Write(std::string data);
    };
}


#endif //DUST_EVENT_H
