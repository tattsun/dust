//
// Created by tattsun on 15/07/24.
//

#ifndef DUST_WITHLENGTHPACKETBUFFERTEST_H
#define DUST_WITHLENGTHPACKETBUFFERTEST_H


#include <CppUTest/CommandLineTestRunner.h>
#include <sstream>
#include "../../src/network/WithLengthPacketBuffer.h"

using namespace dust;


TEST_GROUP(WithLengthPacketBufferTest) {
};

TEST(WithLengthPacketBufferTest, Works) {

    WithLengthPacketBuffer buf(0xa);

    std::stringstream s;
    s   << (char)0x0 << (char)0x1
        << (char)0x1
        << (char)0xa;
    std::stringstream s2;
    s2  << (char)0x0 << (char)0x5
        << (char)0x1 << (char)0x2 << (char)0x3 << (char)0x4
        << (char)0x5
        << (char)0xa;
    std::stringstream s3;
    s3  << (char)0x0 << (char)0x2
        << (char)0xa << (char)0x2;

    CHECK(buf.Write(s.str()));
    CHECK(buf.Write(s2.str()));
    CHECK(!buf.Write(s3.str()));

    LONGS_EQUAL(2, buf.Count());
    auto pkt1 = buf.Pop();
    CHECK(pkt1->c_str()[0] == 0x1);

    LONGS_EQUAL(1, buf.Count());
    auto pkt2 = buf.Pop();

    CHECK(pkt2->c_str()[0] == 0x1);
    CHECK(pkt2->c_str()[1] == 0x2);
    CHECK(pkt2->c_str()[2] == 0x3);
    CHECK(pkt2->c_str()[3] == 0x4);
    CHECK(pkt2->c_str()[4] == 0x5);

    LONGS_EQUAL(0, buf.Count());
}


#endif //DUST_WITHLENGTHPACKETBUFFERTEST_H
