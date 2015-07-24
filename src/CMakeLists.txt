cmake_minimum_required(VERSION 2.8)
project(dust)

add_library(dust
    Human.cpp
    Human.h
    Tuple.h
    async/Event.cpp
    async/Event.h
    thread/PThread.cpp
    thread/PThread.h
network/TCPServer.cpp network/TCPServer.h async/AsyncTCPServer.cpp async/AsyncTCPServer.h network/PacketBuffer.cpp network/PacketBuffer.h ByteChars.cpp ByteChars.h dust.h debug/DebugUtil.cpp debug/DebugUtil.h network/WithLengthPacketBuffer.cpp network/WithLengthPacketBuffer.h)

INSTALL(TARGETS dust
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

INSTALL(DIRECTORY ./ DESTINATION include/dust
    FILES_MATCHING PATTERN "*.h")