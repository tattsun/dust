//
// Created by tattsun on 15/07/03.
//

#include "PacketBuffer.h"

namespace dust {

    PacketBuffer::PacketBuffer(char delimiter)
    : _delimiter(delimiter)
    , _packets()
    , _buf() {
    }

    void PacketBuffer::Write(const ByteChars& str) {
        appendToBuffer(str);

        while(1) {
            std::shared_ptr<ByteChars> packet = popPacketFromBuffer();
            if(packet == nullptr) {
                break;
            }

            _packets.push_back(ByteChars(*packet));
        }
    }

    void PacketBuffer::appendToBuffer(const ByteChars& input) {
        _buf.Append(input);
    }

    std::shared_ptr<ByteChars> PacketBuffer::popPacketFromBuffer() {
        size_t dpos = _buf.FindCharFirstPos(_delimiter);

        if (dpos == -1) {
            return nullptr;
        }

        ByteChars packet(_buf.Substr(0, dpos));
        ByteChars left(_buf.Substr(dpos+1));

        _buf = left;
        return std::make_shared<ByteChars>(packet);
    }

    size_t PacketBuffer::Count() {
        return _packets.size();
    }

    std::shared_ptr<ByteChars> PacketBuffer::Pop() {
        if (_packets.size() == 0) {
            return nullptr;
        }
        ByteChars front(_packets.front());
        _packets.pop_front();
        return std::make_shared<ByteChars>(front);
    }

}