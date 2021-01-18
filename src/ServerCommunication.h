//
// Created by KangDroid on 2021/01/18.
//

#ifndef TRASHMOVERCLIENT_SERVERCOMMUNICATION_H
#define TRASHMOVERCLIENT_SERVERCOMMUNICATION_H

#include <iostream>
#include <cpprest/http_client.h>

using namespace std;
using namespace web::http;
using namespace web::http::client;

class ServerCommunication {
// Member Fields
protected:
    bool server_alive;

protected:
    void check_server_alive();
    bool request_server(http_request& request_type, http_client& client, string target);
    uri_builder custom_uri_builder(string path);

public:
    ServerCommunication();
};


#endif //TRASHMOVERCLIENT_SERVERCOMMUNICATION_H
