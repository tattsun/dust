//
// Created by tattsun on 15/06/29.
//

#ifndef DUST_EVENT_H
#define DUST_EVENT_H

#include <iostream>
#include <event2/bufferevent.h>
#include "event2/event.h"
#include "../ByteChars.h"

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

    class BufferEvent;

    struct BufferEventDataCallBack {
        BufferEventDataCallBack(){};
        ~BufferEventDataCallBack() = default;
        virtual void Call(BufferEvent* bufev) = 0;
    };

    struct BufferEventEvCallBack {
        BufferEventEvCallBack() {};
        ~BufferEventEvCallBack() = default;
        virtual void Call(BufferEvent* bufev, short evtype) = 0;
    };


    class BufferEvent {
        bufferevent* bufev_;
        BufferEventDataCallBack* readcb_;
        BufferEventDataCallBack* writecb_;
        BufferEventEvCallBack* eventcb_;
    public:
        BufferEvent(EventBase* base, evutil_socket_t sock);
        ~BufferEvent();

        void SetCallBack(BufferEventDataCallBack* readcb,
                         BufferEventDataCallBack* writecb,
                         BufferEventEvCallBack* eventcb);
        BufferEventDataCallBack* const get_readcb_() const;
        BufferEventDataCallBack* const get_writecb_() const;
        BufferEventEvCallBack* const get_eventcb_() const;

        int Enable(short ev_type);
        int Disable(short ev_type);

        size_t Read(void* data, size_t size);
        int Write(const void* data, size_t size);

        std::string Read(size_t size);
        int Write(std::string data);
    };

    class EventTimer;

    struct EventTimerCallback {
        EventTimerCallback() {};
        virtual ~EventTimerCallback() = default;
        virtual void Call() = 0;
        EventTimer* ev_timer;
    };

    class EventTimer {
        timeval* timeout;
        event* ev;
    public:
        EventTimer(EventBase* base, EventTimerCallback* cb);
        ~EventTimer();

        void Set(long sec, long usec);
    };
}


#endif //DUST_EVENT_H
