//
// Created by tattsun on 15/07/03.
//

#ifndef DUST_PACKETBUFFERTEST_H
#define DUST_PACKETBUFFERTEST_H

#include <CppUTest/CommandLineTestRunner.h>
#include "../../src/network/PacketBuffer.h"

using namespace dust;

TEST_GROUP(PacketBufferTest) {

};

TEST(PacketBufferTest, Works) {
    PacketBuffer pb1('\n');
    pb1.Write("Hello\nTest\n");
    pb1.Write("World\n");
    STRCMP_EQUAL("Hello", pb1.Pop()->c_str());
    STRCMP_EQUAL("Test", pb1.Pop()->c_str());
    STRCMP_EQUAL("World", pb1.Pop()->c_str());
    CHECK(pb1.Pop() == nullptr);
}

TEST(PacketBufferTest, Empty) {
    PacketBuffer pb1('x');
    CHECK(pb1.Pop() == nullptr);
    CHECK(pb1.Pop() == nullptr);
    CHECK(pb1.Pop() == nullptr);
}

TEST(PacketBufferTest, NonContinuousInput) {
    PacketBuffer pb1('X');
    pb1.Write("ABCDE");
    pb1.Write("DEFXGHI");
    pb1.Write("JKLMX");
    pb1.Write("NOP");
    STRCMP_EQUAL("ABCDEDEF", pb1.Pop()->c_str());
    STRCMP_EQUAL("GHIJKLM", pb1.Pop()->c_str());
    CHECK(pb1.Pop() == nullptr);
    CHECK(pb1.Pop() == nullptr);
}
#endif //DUST_PACKETBUFFERTEST_H
