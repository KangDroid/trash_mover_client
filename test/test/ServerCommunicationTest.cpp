//
// Created by KangDroid on 2021/01/18.
//

#include <cpprest/http_client.h>
#include <gtest/gtest.h>
#include <fstream>
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
    bool assert_this = request_server(request_type, client, [](string response) {
        return response.find("github") != string::npos;
    });

    // assert
    EXPECT_EQ(assert_this, true);
}

#if defined(KDR_PRIVATE_TEST)
TEST_F(ServerCommunicationTest, CheckPostingWorks) {
    args_def = new ArgsDefinition();
    // First create files
    string base_name = "KDR_TESTING_FILES_";
    int file_count = 10;

    for (int i = 0; i < file_count; i++) {
        string file_name = "/tmp/" + base_name + to_string(i);
        ofstream test_file(file_name);
        test_file << "test using" << endl;

        // assert
        bool assert_this = _post_data(file_name);
        EXPECT_EQ(assert_this, true);
        test_file.close();

        // cleanup
        if (filesystem::exists(file_name)) {
            filesystem::remove(file_name);
        }
    }
    delete args_def;
}

TEST_F(ServerCommunicationTest, CheckVerboseWorks) {
    args_def = new ArgsDefinition();
    args_def->setIsVerbose(true);
    // First create files
    string base_name = "KDR_TESTING_FILES_";
    int file_count = 10;

    for (int i = 0; i < file_count; i++) {
        string file_name = "/tmp/" + base_name + to_string(i);
        ofstream test_file(file_name);
        test_file << "test using" << endl;

        // assert
        bool assert_this = _post_data(file_name);
        EXPECT_EQ(assert_this, true);
        test_file.close();

        // cleanup
        if (filesystem::exists(file_name)) {
            filesystem::remove(file_name);
        }
    }
    delete args_def;
}
#endif
