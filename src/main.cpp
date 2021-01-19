#include <iostream>
#include "ArgumentParser.h"
#include "ServerCommunication.h"

using namespace std;

int main(int argc, char** argv) {
    // Communication bridge with backend-server
    ServerCommunication server_communication;

    // Custom parser
    ArgumentParser argument_parser;

    // Parse Arguments
    argument_parser.parse_main(argc, argv);

    // Post to server.
    server_communication.post_data(argument_parser.get_to_delete(), argument_parser.getArgsDefinition());
    return 0;
}