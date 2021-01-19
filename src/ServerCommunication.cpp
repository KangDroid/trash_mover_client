//
// Created by KangDroid on 2021/01/18.
//

#include "ServerCommunication.h"

#include <utility>

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

void ServerCommunication::post_data(vector<string> to_delete) {
    for (string target : to_delete) {
        _post_data(target);
    }
}

bool ServerCommunication::_post_data(string delete_target) {
    // Client
    http_client client_req(custom_uri_builder("api/trash/data").to_string());

    // The body
    http_request request_type(methods::POST);
    json::value main_post = json::value::object();
    main_post["cwdLocation"] = json::value::string("/Users/kangdroid");
    main_post["originalFileDirectory"] = json::value::string(std::move(delete_target));
    request_type.set_body(main_post);

    // Return value
    return request_server(request_type, client_req, [](string response) {
        return !response.empty() && all_of(response.begin(), response.end(), ::isdigit);
    });
}
