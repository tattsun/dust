//
// Created by tattsun on 15/07/03.
//

#include "PacketBuffer.h"
#include <iostream>


namespace dust {

    PacketBuffer::PacketBuffer(char delimiter)
    : _delimiter(delimiter)
    , _packets()
    , _buf() {
    }

    void PacketBuffer::Write(std::string str) {
        appendToBuffer(str);

        while(1) {
            std::shared_ptr<std::string> packet = popPacketFromBuffer();
            if(packet == nullptr) {
                break;
            }
            _packets.push_back(std::string(*packet));
        }
    }

    void PacketBuffer::appendToBuffer(std::string input) {
        std::stringstream s;
        s << _buf << input;
        _buf = s.str();

    }

    std::shared_ptr<std::string> PacketBuffer::popPacketFromBuffer() {
        std::size_t dpos = _buf.find_first_of(_delimiter);
        if (dpos == std::string::npos) {
            return nullptr;
        }

        std::string packet(_buf.substr(0, dpos));
        std::string left(_buf.substr(dpos+1));

        _buf = left;
        return std::make_shared<std::string>(packet);
    }

    size_t PacketBuffer::Count() {
        return _packets.size();
    }

    std::shared_ptr<std::string> PacketBuffer::Pop() {
        if (_packets.size() == 0) {
            return nullptr;
        }
        std::string front(_packets.front());
        _packets.pop_front();
        return std::make_shared<std::string>(front);
    }

}