//
// Created by tattsun on 15/07/03.
//

#ifndef DUST_PACKETBUFFER_H
#define DUST_PACKETBUFFER_H

#include <list>
#include <memory>
#include <string>
#include <sstream>

namespace dust {
    class PacketBuffer {
    public:
        PacketBuffer(char delimiter);

        void Write(std::string str);
        size_t Count();
        std::shared_ptr<std::string> Pop();

    private:
        void appendToBuffer(std::string input);
        std::shared_ptr<std::string> popPacketFromBuffer();

        char _delimiter;
        std::list<std::string> _packets;
        std::string _buf;
    };
}


#endif //DUST_PACKETBUFFER_H
