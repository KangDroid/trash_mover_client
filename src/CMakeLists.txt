if (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
endif()

find_package(cpprestsdk REQUIRED)
find_package (OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

set(TM_VERSION 1.0.0)

execute_process(COMMAND git rev-parse --short HEAD OUTPUT_VARIABLE LATEST_COMMIT)
string(REGEX REPLACE "\n$" "" LATEST_COMMIT "${LATEST_COMMIT}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_TURN_OFF_PLATFORM_STRING")

add_executable(TrashMoverClient main.cpp ArgumentParser.cpp ArgsDefinition.cpp ServerCommunication.cpp ServerDownloader.cpp ServerDownloader.h)
TARGET_LINK_LIBRARIES(TrashMoverClient PRIVATE cpprestsdk::cpprest OpenSSL::SSL Boost::system OpenSSL::Crypto)