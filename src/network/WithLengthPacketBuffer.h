//
// Created by tattsun on 15/07/24.
//

#ifndef DUST_WITHLENGTHPACKETBUFFER_H
#define DUST_WITHLENGTHPACKETBUFFER_H

#include <iostream>
#include <queue>

#if CPPUTEST_USE_NEW_MACROS
    #undef new
#endif
#include <boost/optional.hpp>
#if CPPUTEST_USE_NEW_MACROS
    #include <CppUTest/MemoryLeakDetectorNewMacros.h>
#endif

namespace dust {

    class WithLengthPacketBuffer {
    public:
        WithLengthPacketBuffer(char delimiter);
        bool Write(const std::string &data);
        std::size_t Count();
        boost::optional<std::string> Pop();

    private:
        bool hasDelimiterInBuf();

        boost::optional<std::string> readPacketFromBuf();

        char _delimiter;
        std::string _buf;
        std::queue<std::string> _packets;
    };
}


#endif //DUST_WITHLENGTHPACKETBUFFER_H
