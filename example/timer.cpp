//
// Created by tattsun on 15/07/20.
//

#include <dust/async/Event.h>
#include <iostream>

using namespace dust;

struct timer_cb : public EventTimerCallback {
    EventTimer* timer;
    void Call() {
        std::cout << "Timer called!" << std::endl;
        delete timer;
    }
};

int main() {
    EventBase ev_base;

    timer_cb callback;

    EventTimer* timer = new EventTimer(&ev_base, &callback);
    callback.timer = timer;

    timer->Set(5, 0);

    ev_base.LoopForever();
}