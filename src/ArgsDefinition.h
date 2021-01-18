//
// Created by KangDroid on 2021/01/18.
//

#ifndef TRASHMOVERCLIENT_ARGSDEFINITION_H
#define TRASHMOVERCLIENT_ARGSDEFINITION_H

#include <iostream>

using namespace std;

class ArgsDefinition {
private:
    // --autorun_server
    bool server_on;

    // --recursive | -r
    bool is_recursive;

    // --force | -f
    bool is_force;

    // --verbose | -v
    bool is_verbose;

public:
    // Default Constructor
    ArgsDefinition();

// Getters and Setters
public:
    bool isServerOn() const;
    void setServerOn(bool serverOn);
    bool isRecursive() const;
    void setIsRecursive(bool isRecursive);
    bool isForce() const;
    void setIsForce(bool isForce);
    bool isVerbose() const;
    void setIsVerbose(bool isVerbose);
};


#endif //TRASHMOVERCLIENT_ARGSDEFINITION_H
