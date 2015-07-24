//
// Created by tattsun on 15/06/29.
//

#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"

// TestCases
#include "ByteCharsTest.h"
#include "network/PacketBufferTest.h"
#include "network/WithLengthPacketBufferTest.h"

int main(int argc, char* argv[]) {
    return RUN_ALL_TESTS(argc, argv);
}