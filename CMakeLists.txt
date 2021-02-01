cmake_minimum_required(VERSION 3.15)
project(TrashMoverClient)

set(CMAKE_CXX_STANDARD 20)

set(TM_VERSION "V1.0.0")
execute_process(COMMAND git rev-parse --short HEAD OUTPUT_VARIABLE LATEST_COMMIT)
string(REGEX REPLACE "\n$" "" LATEST_COMMIT "${LATEST_COMMIT}")

set(CMAKE_CXX_FLAGS "-DKDR_TRASH_MOVER_VER=\"\\\"${TM_VERSION}\\\"\" -DKDR_LATEST_COMMIT=\"\\\"${LATEST_COMMIT}\\\"\"")

add_subdirectory(src)

if (DEFINED TESTING)
    set(KDRTESTING ON)
endif(DEFINED TESTING)
add_subdirectory(test)