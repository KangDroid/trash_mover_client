cmake_minimum_required(VERSION 3.17)
project(TrashMoverTest)

if (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
endif()

find_package(cpprestsdk REQUIRED)
find_package (OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-DKDR_TESTING -D_TURN_OFF_PLATFORM_STRING")

if(DEFINED KDRTESTING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKDR_PRIVATE_TEST")
endif(DEFINED KDRTESTING)

        #Add the google test subdirectory
add_subdirectory(googletest)

include_directories(../src)

#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

#Define your executable
add_executable(TrashMoverTest test/test_main.cpp test/ArgumentTest.cpp ../src/ArgsDefinition.cpp ../src/ArgumentParser.cpp ../src/ServerCommunication.cpp test/ServerCommunicationTest.cpp)

#Link with GoogleTest
target_link_libraries(TrashMoverTest gtest gtest_main)

#Link with GoogleMock
target_link_libraries(TrashMoverTest gmock gmock_main)

TARGET_LINK_LIBRARIES(TrashMoverTest cpprestsdk::cpprest OpenSSL::SSL Boost::system OpenSSL::Crypto)