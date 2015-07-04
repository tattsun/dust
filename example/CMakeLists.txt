
project(example)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(tcpserver tcpserver.cpp)
target_link_libraries(tcpserver dust event)