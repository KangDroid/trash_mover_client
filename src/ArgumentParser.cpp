//
// Created by KangDroid on 2021/01/18.
//

#include "ArgumentParser.h"

void ArgumentParser::parse_main(int argc, char **argv) {
    // Assert if there is no argument.
    if (argc < 2) {
        exit(0);
    }

    // Iterate through argument
    for (int i = 1; i < argc; i++) {
        string arg_cxx = string(argv[i]);
        if (argv[i][0] == '-' && argv[i][1] != '-') {
            // Short Argument.
            parse_short(arg_cxx.substr(1, arg_cxx.length()));
        } else if (argv[i][0] == '-' && argv[i][1] == '-') {
            // Long Argument
            parse_long(arg_cxx.substr(2, arg_cxx.length()));
        }
    }
}

// The input string should trail those prefix '-'
void ArgumentParser::parse_short(string arg) {
    for (char single : arg) {
        _parse_short(single);
    }
}

void ArgumentParser::_parse_short(char single_var) {
    function<void (void)> invoke_function = (shortargs_map.contains(single_var)) ?
            shortargs_map[single_var] : [single_var]() {
                cerr << "Args " << single_var << " is not on argument list." << endl;
            };

    invoke_function();
}

// The input string should trail those prefix "--"
void ArgumentParser::parse_long(string arg) {
    function<void (void)> invoke_function = (longargs_map.contains(arg)) ?
            longargs_map[arg] : [arg](){
                cerr << "Args " << arg << " is not on argument list." << endl;
            };

    invoke_function();
}

ArgsDefinition* ArgumentParser::getArgsDefinition() {
    return &args_definition;
}
