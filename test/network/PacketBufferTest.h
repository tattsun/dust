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
    pb1.Write(ByteChars("Hello\nTest\n"));
    pb1.Write(ByteChars("World\n"));

    LONGS_EQUAL(3, pb1.Count());
    STRCMP_EQUAL("Hello", pb1.Pop()->c_str());
    LONGS_EQUAL(2, pb1.Count());
    STRCMP_EQUAL("Test", pb1.Pop()->c_str());
    LONGS_EQUAL(1, pb1.Count());
    STRCMP_EQUAL("World", pb1.Pop()->c_str());
    LONGS_EQUAL(0, pb1.Count());
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
    pb1.Write(ByteChars("ABCDE"));
    pb1.Write(ByteChars("DEFXGHI"));
    pb1.Write(ByteChars("JKLMX"));
    pb1.Write(ByteChars("NOP"));
    STRCMP_EQUAL("ABCDEDEF", pb1.Pop()->c_str());
    STRCMP_EQUAL("GHIJKLM", pb1.Pop()->c_str());
    CHECK(pb1.Pop() == nullptr);
    CHECK(pb1.Pop() == nullptr);
    pb1.Write(ByteChars("QRSXT"));
    STRCMP_EQUAL("NOPQRS", pb1.Pop()->c_str());
    CHECK(pb1.Pop() == nullptr);
}

TEST(PacketBufferTest, WriteTest) {
    char bytes[100];
    for(int i=0; i<100; i++) {
        bytes[i] = (char)(i+5);
        if(i%5==0) { bytes[i] = (char)2; }
    }
    bytes[99] = '\0';

    PacketBuffer pb((char)2);
    for(int i=0; i<100; i++) {
        pb.Write(ByteChars(bytes, 100));
    }
}


TEST(PacketBufferTest, BinaryTest) {
    char bytes[10];
    bytes[0] = (char)0xffffff92;
    bytes[1] = (char)0x0;
    bytes[2] = (char)0x0;
    bytes[3] = (char)0xa;

    bytes[4] = (char)0xffffffeb;
    bytes[5] = (char)0x62;
    bytes[6] = (char)0xa;

    bytes[7] = (char)0x62;
    bytes[8] = (char)0x62;
    bytes[9] = (char)0x62;


    PacketBuffer pb1((char)0xa);
    for(int i=0; i < 10; i++) {
        pb1.Write(ByteChars(bytes[i]));
    }

    auto bc = pb1.Pop();
    CHECK(bc->c_str()[0] == bytes[0]);
    CHECK(bc->c_str()[1] == bytes[1]);
    CHECK(bc->c_str()[2] == bytes[2]);
    LONGS_EQUAL(3, bc->length());

    auto bc2 = pb1.Pop();
    CHECK(bc2->c_str()[0] == bytes[4]);
    CHECK(bc2->c_str()[1] == bytes[5]);
    LONGS_EQUAL(2, bc2->length());

    CHECK(pb1.Pop() == nullptr);
}

#endif //DUST_PACKETBUFFERTEST_H
