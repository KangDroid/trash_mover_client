//
// Created by KangDroid on 2021/02/07.
//

#include "ServerDownloader.h"

void ServerDownloader::_download_server() {
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

void ServerDownloader::_init_server() {
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

void ServerDownloader::init_server() {
    cout << "Downloading.." << endl;
    _download_server();

    child_pid = fork();

    if (child_pid == 0) {
        // Child code
        _init_server();
    } else {
        cout << "Waiting for server to boot up.." << endl;
        sleep(BOOTUP_TIME);
    }
}

void ServerDownloader::destroy_server() {
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
