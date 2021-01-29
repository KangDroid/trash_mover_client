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

ServerCommunication::ServerCommunication(ArgsDefinition* argsInput) {
    this->args_def = argsInput;
//    check_server_alive();
}

ServerCommunication::ServerCommunication() {
//    check_server_alive();
}

void ServerCommunication::post_data(vector<string>& to_delete) {
    if (args_def->isShowVersion()) {
        show_version();
        return;
    } else if (args_def->isShowAll()) {
        show_all();
        return;
    } else if (args_def->isRestoreMenu()) {
        show_restore();
        return;
    } else if (args_def->isClearAll()) {
        string value;
        cout << "Really empty trashcan?[y/n] : ";
        getline(cin, value);
        if (value == "y" || value == "Y" || value == "yes") {
            clear_all_data();
        } else {
            cout << "Abort." << endl;
        }
        return;
    }

    for (string target : to_delete) {
        if (!args_def->isForce()) {
            string input_check;
            cout << "Really Delete: " << target << "?[y/n]";
            getline(cin, input_check);

            if (input_check != "y") {
                continue;
            }
        }
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
    main_post["originalFileDirectory"] = json::value::string(delete_target);
    request_type.set_body(main_post);

    // Return value
    return request_server(request_type, client_req, [delete_target, this](string response) {
        if (args_def->isVerbose()) {
            cout << delete_target << "  -->  " << response << endl;
        }
        return !response.empty() && (response.find(filesystem::path(delete_target).filename()) != string::npos);
    });
}

bool ServerCommunication::show_version() {
    string response;
    // Basic http request variable building
    http_request request_type(methods::GET);
    http_client client(custom_uri_builder("api/settings/get").to_string());

    // Response Json
    json::value root_value;

    bool isSucceed = request_server(request_type, client, [&root_value](const string& input) {
        root_value = web::json::value::parse(input);
        return !input.empty() && input.find("trashPath") != string::npos;
    });

    if (isSucceed) {
        cout << "Trash Can Path: " << root_value["trashPath"].as_string() << endl;
        cout << "Server Version: " << root_value["serverVersion"].as_string() << endl;
    } else {
        cerr << "Error: Server is not running![Trash can path, server version will not be shown]" << endl;
    }

    cout << "Client Version: " << KDR_TRASH_MOVER_VER << "[" << KDR_LATEST_COMMIT << "]" <<endl;
    cout << "Compiled with " << __VERSION__ << ",";
    cout << " on: " << __DATE__ << ", " << __TIME__ << endl;

    // Check whether server is alive.
    return isSucceed;
}

bool ServerCommunication::show_all() {
    string response;
    // Basic http request variable building
    http_request request_type(methods::GET);
    http_client client(custom_uri_builder("api/trash/data/all").to_string());

    // Response Json
    json::value root_value;

    bool isSucceed = request_server(request_type, client, [&root_value](const string& input) {
        root_value = web::json::value::parse(input);
        return !input.empty() && input.find("cwdLocation") != string::npos;
    });

    for (int i = 0; i < root_value.size(); i++) {
        restore_list.emplace_back(
                root_value[i]["cwdLocation"].as_string(),
                root_value[i]["originalFileDirectory"].as_string(),
                root_value[i]["trashFileDirectory"].as_string()
        );
        cout << "File " << i+1 << ":" << endl;
        cout << "CWD Location: " << root_value[i]["cwdLocation"].as_string() << endl;
        cout << "Original File Path: " << root_value[i]["originalFileDirectory"].as_string() << endl;
        cout << "Trash File Path: " << root_value[i]["trashFileDirectory"].as_string() << endl;
        cout << endl;
    }

    return isSucceed;
}

void ServerCommunication::show_restore() {
    int input;
    if (!show_all()) {
        return;
    }

    cout << "Enter file index number to restore! : ";
    cin >> input;

    if ((input < 1 || input > restore_list.size())) {
        cerr << "Error: Input range is between 1 ~ " << restore_list.size() << endl;
        return;
    }

    if (restore_list[input-1].originalFileDirectory == "EXTERNAL" || restore_list[input-1].cwdLocation == "EXTERNAL") {
        cerr << "Error: file " << restore_list[input-1].trashFileDirectory << " is added externally to trash folder." << endl;
        return;
    }

    restore_post(restore_list[input-1].trashFileDirectory);
}

bool ServerCommunication::restore_post(string target) {
    // Client
    http_client client_req(custom_uri_builder("api/trash/data/restore").to_string());

    // The body
    http_request request_type(methods::POST);
    json::value main_post = json::value::object();
    main_post["trashFileDirectory"] = json::value::string(target);
    request_type.set_body(main_post);

    // The response
    string response_value;

    // Return value
    return request_server(request_type, client_req, [&response_value](string response) {
        response_value = response;
        bool result = (response == RESTORE_FULL_SUCCESS);
        ((result) ? cout : cerr) << response << endl;
        return result;
    });
}

bool ServerCommunication::clear_all_data() {
    // Client
    http_client client_req(custom_uri_builder("api/trash/data/empty").to_string());

    // The body
    http_request request_type(methods::DEL);

    // The response
    string response_value;

    // Return value
    return request_server(request_type, client_req, [&response_value](string response) {
        response_value = response;
        return (response == "true");
    });
}
