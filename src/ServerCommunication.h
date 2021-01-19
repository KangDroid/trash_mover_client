//
// Created by KangDroid on 2021/01/18.
//

#ifndef TRASHMOVERCLIENT_SERVERCOMMUNICATION_H
#define TRASHMOVERCLIENT_SERVERCOMMUNICATION_H

#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include "ArgsDefinition.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

class ServerCommunication {
// Member Fields
protected:
    bool server_alive;

protected:
    void check_server_alive();
    bool request_server(http_request& request_type, http_client& client, function<bool (string)> checker);
    uri_builder custom_uri_builder(string path);
    bool _post_data(string delete_target);

public:
    ServerCommunication();
    void post_data(vector<string>& to_delete, ArgsDefinition* args_def);
};


#endif //TRASHMOVERCLIENT_SERVERCOMMUNICATION_H
