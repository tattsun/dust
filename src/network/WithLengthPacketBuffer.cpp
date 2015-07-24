//
// Created by tattsun on 15/07/24.
//

#include "WithLengthPacketBuffer.h"
#include <sstream>

namespace dust {
    std::size_t addSizeBytes(char ch0, char ch1) {
        return (std::size_t) ch0 * 0x100 + ch1;
    }

    WithLengthPacketBuffer::WithLengthPacketBuffer(char delimiter)
            : _delimiter(delimiter) {
    }

    bool WithLengthPacketBuffer::Write(const std::string &data) {
        _buf += data;

        bool newpacket = false;
        while (hasDelimiterInBuf()) {
            auto pkt = readPacketFromBuf();
            if (pkt) {
                newpacket = true;
                _packets.push(*pkt);
            } else {
                break;
            }
        }
        return newpacket;
    }

    std::size_t WithLengthPacketBuffer::Count() {
        return _packets.size();
    }

    boost::optional<std::string> WithLengthPacketBuffer::Pop() {
        if (_packets.size() == 0)
            return boost::optional<std::string>();

        std::string packet = _packets.front();
        _packets.pop();
        return boost::optional<std::string>(packet);
    }

    bool WithLengthPacketBuffer::hasDelimiterInBuf() {
        const char* buf = _buf.c_str();

        for(std::size_t i=0; i < _buf.length(); i++) {
            if(buf[i] == _delimiter)
                return true;
        }
        return false;
    }

    boost::optional<std::string> WithLengthPacketBuffer::readPacketFromBuf() {
        if (_buf.length() < 2)
            return boost::optional<std::string>();


        const char *buf = _buf.c_str();
        std::size_t length = _buf.length();

        std::size_t packet_len = addSizeBytes(buf[0], buf[1]);


        if (length - 3 < packet_len)
            return boost::optional<std::string>();

        std::stringstream spacket;
        for (std::size_t i = 0; i < packet_len; i++)
            spacket << buf[i + 2];

        std::stringstream sleft;
        for (std::size_t i = packet_len + 3; i < length; i++) {
            sleft << buf[i];
        }

        _buf = std::string(sleft.str());

        return boost::optional<std::string>(spacket.str());
    }
}