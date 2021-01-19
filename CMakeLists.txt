cmake_minimum_required(VERSION 3.17)
project(TrashMoverClient)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

if (DEFINED TESTING)
    set(KDRTESTING ON)
endif(DEFINED TESTING)
add_subdirectory(test)