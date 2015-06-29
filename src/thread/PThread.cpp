//
// Created by tattsun on 15/06/29.
//

#include "PThread.h"
#include "stdlib.h"


namespace dust {

    void *_pthread_wrapper(void* args) {
        PThreadWorker* w = (PThreadWorker*)args;
        return w->Call();
    }

    PThread::PThread(PThreadWorker* worker)
    :th_(){
        worker_ = worker;
    }

    PThread::~PThread() {
        Cancel();
    }

    int PThread::Start() {
        return pthread_create(&th_, NULL, _pthread_wrapper, (void*)worker_);
    }

    int PThread::Join() {
        return pthread_join(th_, NULL);

    }

    int PThread::Cancel() {
        return pthread_cancel(th_);
    }

}