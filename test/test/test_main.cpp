//
// Created by KangDroid on 2021/01/18.
//

#include <gtest/gtest.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <filesystem>
#include <unistd.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

#define SERVER_DEST "/tmp/testServer.jar"
#define TRASH_DIR_TEST "/tmp/kdr_trash_tmp"
#define SERVER_SETTINGS "/tmp/custom_settings.properties"
#define BOOTUP_TIME 20

pid_t child_pid;

void _download_server() {
    if (filesystem::exists(SERVER_DEST)) {
        filesystem::remove(SERVER_DEST);
    }
    uri_builder uri_target;
    uri_target.set_scheme("https");
    uri_target.set_host("api.github.com");
    uri_target.set_path("repos/KangDroid/kotlin_trash_server/releases/latest");

    http_request req_type(methods::GET);
    http_client client(uri_target.to_string());

    // Request
    json::value root_value;

    try {
        client.request(req_type).then([&root_value](http_response hr) {
            root_value = hr.extract_json().get();
        }).wait();
    } catch (const exception& expn) {
        cerr << "Error: ";
        cerr << expn.what() << endl;
    }

    // Download!
    json::value assets = root_value["assets"][0];
    string command = "wget " + assets["browser_download_url"].as_string() + " -O " + SERVER_DEST;
    cout << command << endl;
    system(command.c_str());
}

void _init_server() {
    if (filesystem::exists(SERVER_SETTINGS)) {
        filesystem::remove(SERVER_SETTINGS);
    }

    ofstream ofs(SERVER_SETTINGS);
    ofs << "kdr.trash-path=" << TRASH_DIR_TEST << endl;
    ofs.close();

    if (!filesystem::exists(TRASH_DIR_TEST)) {
        filesystem::create_directories(TRASH_DIR_TEST);
    }
    execlp("java", "java", "-jar", SERVER_DEST, "--spring.config.location=" SERVER_SETTINGS , 0);
}

void init_server() {
    cout << "Downloading.." << endl;
    _download_server();

    child_pid = fork();

    if (child_pid == 0) {
        // Child code
        _init_server();
    } else {
        sleep(BOOTUP_TIME);
    }
}

void destroy_server() {
    if (filesystem::exists(TRASH_DIR_TEST)) {
        filesystem::remove_all(TRASH_DIR_TEST);
    }

    if (filesystem::exists(SERVER_SETTINGS)) {
        filesystem::remove(SERVER_SETTINGS);
    }

    if (filesystem::exists(SERVER_DEST)) {
        filesystem::remove(SERVER_DEST);
    }
}

int main(int argc, char** argv) {
    init_server();
    ::testing::InitGoogleTest(&argc, argv);
    int ret_val = RUN_ALL_TESTS();

    const string kill_command = "kill -TERM " + to_string(child_pid);
    system(kill_command.c_str());
    wait(&child_pid);

    // Another test with server off
    ret_val = RUN_ALL_TESTS();

    // destroy server
    destroy_server();

    return ret_val;
}