cmake_minimum_required(VERSION 2.8)
project(dust)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")
set(CPPUTEST_CXXFLAGS "${CPPUTEST_CXXFLAGS} -include test/PreIncludeFiles.h")
enable_testing()


# dust library
add_subdirectory(src)

# dust test
add_executable(dust_test test/PreIncludeFiles.h test/RunAllTests.cpp test/network/PacketBufferTest.h test/ByteCharsTest.h test/network/WithLengthPacketBufferTest.h)
target_link_libraries(dust_test CppUTest)
set_target_properties(dust_test PROPERTIES CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -static -fprofile-arcs -ftest-coverage")
target_link_libraries(dust_test dust)
add_test(dust_test dust_test)

# install


#set(SOURCE_FILES main.cpp)
#add_executable(dust ${SOURCE_FILES} src/Human.cpp src/Human.h)