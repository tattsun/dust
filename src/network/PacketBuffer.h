//
// Created by tattsun on 15/07/03.
//

#ifndef DUST_PACKETBUFFER_H
#define DUST_PACKETBUFFER_H

#include <list>
#include <memory>
#include <string>
#include <sstream>
#include "../ByteChars.h"

namespace dust {
    class PacketBuffer {
    public:
        PacketBuffer(char delimiter);

        void Write(const ByteChars& bs);


        size_t Count();
        std::shared_ptr<ByteChars> Pop();

    private:
        void appendToBuffer(const ByteChars& input);
        std::shared_ptr<ByteChars> popPacketFromBuffer();

        char _delimiter;
        std::list<ByteChars> _packets;
        ByteChars _buf;
    };
}


#endif //DUST_PACKETBUFFER_H
