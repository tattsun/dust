cmake_minimum_required(VERSION 3.2)
project(dust)

add_subdirectory(async)

add_library( dust SHARED
    Human.cpp
    Human.h
    Tuple.h
)

link_libraries(dust async)

INSTALL(TARGETS dust LIBRARY DESTINATION lib)
#INSTALL(FILES *.h DESTINATION include/dust)
INSTALL(DIRECTORY ./ DESTINATION include/dust
    FILES_MATCHING PATTERN "*.h")