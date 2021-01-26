//
// Created by KangDroid on 2021/01/18.
//

#ifndef TRASHMOVERCLIENT_ARGUMENTPARSER_H
#define TRASHMOVERCLIENT_ARGUMENTPARSER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include "ArgsDefinition.h"

using namespace std;

class ArgumentParser {
protected:
    // The Argument Booleans
    ArgsDefinition args_definition;
    vector<string> to_delete;

protected:
    // Hashmap to store work.
    unordered_map<char, function<void (void)>> shortargs_map {
        {'r', [this]() {
                args_definition.setIsRecursive(true);
            }
        },
        {'f', [this]() {
                args_definition.setIsForce(true);
            }
        },
        {'v', [this]() {
                args_definition.setIsVerbose(true);
            }
        },
        { 's', [this]() {
                args_definition.setShowAll(true);
            }
        },
        { 'R', [this]() {
            args_definition.setRestoreMenu(true);
            }
        },
        { 'C', [this]() {
                args_definition.setClearAll(true);
            }
        }
    };

    // Hashmap to store long-args work
    unordered_map<string, function<void (void)>> longargs_map {
        {
            "autorun_server", [this]() {
                args_definition.setServerOn(true);
            }
        },
        {
            "recursive", [this]() {
                args_definition.setIsRecursive(true);
            }
        },
        {
            "force", [this]() {
                args_definition.setIsForce(true);
            }
        },
        {
            "verbose", [this]() {
                args_definition.setIsVerbose(true);
            }
        },
        {
            "version", [this]() {
                args_definition.setShowVersion(true);
            }
        },
        {
            "show", [this]() {
                args_definition.setShowAll(true);
            }
        },
        {
            "restore", [this]() {
                args_definition.setRestoreMenu(true);
            }
        },
        {
            "clear", [this]() {
                args_definition.setClearAll(true);
            }
        }
    };

protected:
    void parse_short(string arg);
    void _parse_short(char single_var);
    void parse_long(string arg);
    void check_push(string arg);

public:
    ArgsDefinition* getArgsDefinition();
    vector<string>& get_to_delete();

public:
    void parse_main(int argc, char** argv);
};


#endif //TRASHMOVERCLIENT_ARGUMENTPARSER_H
