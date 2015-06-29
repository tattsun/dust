//
// Created by tattsun on 15/06/29.
//

#ifndef DUST_PTHREAD_H
#define DUST_PTHREAD_H

#include <pthread.h>

namespace dust{

    struct PThreadWorker {
        PThreadWorker() {};
        ~PThreadWorker() = default;
        virtual void Call() = 0;
    };

    class PThread {
        pthread_t* th_;
        PThreadWorker* worker_;
    public:
        PThread(PThreadWorker* worker);
        ~PThread();

        int Join();
        int Cancel();
    };

}


#endif //DUST_PTHREAD_H
