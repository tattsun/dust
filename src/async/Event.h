//
// Created by tattsun on 15/06/29.
//

#ifndef DUST_EVENT_H
#define DUST_EVENT_H

#include "event2/event.h"

namespace dust {
    struct EventCallBack {
        ~EventCallBack() = default;
        virtual void Call();
        evutil_socket_t sock;
        short ev_type;
    };

    class Event {
        evutil_socket_t sock_;
        EventCallBack callback_;
        short ev_type_;
        event* event_;
    public:
        Event(evutil_socket_t sock, EventCallBack callback, short ev_type);
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

        void LoopOnce();
        void LoopForever();
    };
}


#endif //DUST_EVENT_H
