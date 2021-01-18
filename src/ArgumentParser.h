//
// Created by KangDroid on 2021/01/18.
//

#ifndef TRASHMOVERCLIENT_ARGUMENTPARSER_H
#define TRASHMOVERCLIENT_ARGUMENTPARSER_H

#include <iostream>
#include <unordered_map>
#include "ArgsDefinition.h"

using namespace std;

class ArgumentParser {
private:
    // The Argument Booleans
    ArgsDefinition args_definition;

private:
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
        }
    };

public:
    ArgsDefinition* getArgsDefinition();

public:
    void parse_main(int argc, char** argv);

private:
    void parse_short(string arg);
    void _parse_short(char single_var);
};


#endif //TRASHMOVERCLIENT_ARGUMENTPARSER_H
