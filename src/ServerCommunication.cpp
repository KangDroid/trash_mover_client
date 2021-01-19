//
// Created by KangDroid on 2021/01/18.
//

#include "ServerCommunication.h"

void ServerCommunication::check_server_alive() {
    string response;
    // Basic http request variable building
    http_request request_type(methods::GET);
    http_client client(custom_uri_builder("api/alive").to_string());

    // Check whether server is alive.
    server_alive = request_server(request_type, client, [](const string& input) {
        return input.find("Server is Running!") != string::npos;
    });
}

uri_builder ServerCommunication::custom_uri_builder(string path) {
    uri_builder uri_target;
    uri_target.set_scheme("http");
    uri_target.set_host("localhost");
    uri_target.set_port(8080);
    uri_target.set_path(path);

    return uri_target;
}

bool ServerCommunication::request_server(http_request &request_type, http_client &client, function<bool (string)> checker) {
    string response;
    try {
        client.request(request_type).then([&response] (http_response hr) {
            response = hr.extract_string().get();
        }).wait();
    } catch (const exception& expn) {
        cerr << "Error occurred when connecting backend server." << endl;
        cerr << expn.what() << endl;
        return false;
    }
    return checker(response);
}

ServerCommunication::ServerCommunication() {
    check_server_alive();
}
