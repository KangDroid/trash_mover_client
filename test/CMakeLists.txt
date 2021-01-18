cmake_minimum_required(VERSION 3.17)
project(TrashMoverTest)

set(CMAKE_CXX_STANDARD 20)

#Add the google test subdirectory
add_subdirectory(googletest)

#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

#Define your executable
add_executable(TrashMoverTest test/test_main.cpp)

#Link with GoogleTest
target_link_libraries(TrashMoverTest gtest gtest_main)

#Link with GoogleMock
target_link_libraries(TrashMoverTest gmock gmock_main)