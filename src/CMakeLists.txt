if (APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    set(OPENSSL_LIBRARIES "/usr/local/opt/openssl/lib")
endif()

find_package(cpprestsdk REQUIRED)
find_package (OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_CXX_FLAGS "-D_TURN_OFF_PLATFORM_STRING")

add_executable(TrashMoverClient main.cpp ArgumentParser.cpp ArgsDefinition.cpp ServerCommunication.cpp)
TARGET_LINK_LIBRARIES(TrashMoverClient PRIVATE cpprestsdk::cpprest OpenSSL::SSL Boost::system OpenSSL::Crypto)