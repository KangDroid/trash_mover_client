//
// Created by KangDroid on 2021/01/18.
//

#include <cpprest/http_client.h>
#include <gtest/gtest.h>
#include "ServerCommunication.h"

class ServerCommunicationTest : public testing::Test, protected ServerCommunication {
};

TEST_F(ServerCommunicationTest, CheckURINormal) {
    uri_builder testCase = custom_uri_builder("api/alive");
    EXPECT_EQ(testCase.to_string(), "http://localhost:8080/api/alive");
}

TEST_F(ServerCommunicationTest, CheckRequestNormal) {
    // Let
    string response;
    http_request request_type(methods::GET);

    // URI Building
    http_client client("https://github.com");

    // do work
    bool assert_this = request_server(request_type, client, "github");

    // assert
    EXPECT_EQ(assert_this, true);
}
