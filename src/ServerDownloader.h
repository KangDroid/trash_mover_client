//
// Created by KangDroid on 2021/02/07.
//

#ifndef TRASHMOVERCLIENT_SERVERDOWNLOADER_H
#define TRASHMOVERCLIENT_SERVERDOWNLOADER_H

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

class ServerDownloader {
private:
    static pid_t child_pid;
    static void _download_server();
    static void _init_server();
public:
    static void init_server();
    static void destroy_server();
};


#endif //TRASHMOVERCLIENT_SERVERDOWNLOADER_H
