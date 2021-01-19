#include <iostream>
#include "ArgumentParser.h"
#include "ServerCommunication.h"

using namespace std;

int main(int argc, char** argv) {
    // Custom parser
    ArgumentParser argument_parser;

    // Communication bridge with backend-server
    ServerCommunication server_communication(argument_parser.getArgsDefinition());

    // Parse Arguments
    argument_parser.parse_main(argc, argv);

    // Post to server.
    server_communication.post_data(argument_parser.get_to_delete());
    return 0;
}