//
// Created by tattsun on 15/06/29.
//

#include "PThread.h"

namespace dust {

    void *_pthread_wrapper(void* args) {
        PThreadWorker* w = (PThreadWorker*)args;
        w->Call();
        return NULL;
    }

    PThread::PThread(PThreadWorker* worker) {
        pthread_create(th_, NULL, _pthread_wrapper, (void*)worker);
    }

    PThread::~PThread() {
        Cancel();
    }

    int PThread::Join() {
        return pthread_join(*th_, NULL);

    }

    int PThread::Cancel() {
        return pthread_cancel(*th_);
    }

}