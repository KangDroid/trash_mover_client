//
// Created by KangDroid on 2021/01/18.
//

#include "ArgsDefinition.h"

bool ArgsDefinition::isServerOn() const {
    return server_on;
}

void ArgsDefinition::setServerOn(bool serverOn) {
    server_on = serverOn;
}

bool ArgsDefinition::isRecursive() const {
    return is_recursive;
}

void ArgsDefinition::setIsRecursive(bool isRecursive) {
    is_recursive = isRecursive;
}

bool ArgsDefinition::isForce() const {
    return is_force;
}

void ArgsDefinition::setIsForce(bool isForce) {
    is_force = isForce;
}

ArgsDefinition::ArgsDefinition() {
    this->server_on = false;
    this->is_recursive = false;
    this->is_force = false;
    this->show_version = false;
}

bool ArgsDefinition::isVerbose() const {
    return is_verbose;
}

void ArgsDefinition::setIsVerbose(bool isVerbose) {
    is_verbose = isVerbose;
}

bool ArgsDefinition::isShowVersion() const {
    return show_version;
}

void ArgsDefinition::setShowVersion(bool showVersion) {
    show_version = showVersion;
}
