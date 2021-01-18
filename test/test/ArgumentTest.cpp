//
// Created by KangDroid on 2021/01/18.
//

#include <iostream>
#include <gtest/gtest.h>
#include "ArgumentParser.h"
using namespace std;

class ArgumentTesting : public testing::Test {
protected:
    ArgumentParser argumentParser;
    ArgsDefinition* argsDefinition = argumentParser.getArgsDefinition();

    void SetUp() {
        argsDefinition->setIsVerbose(false);
        argsDefinition->setIsForce(false);
        argsDefinition->setIsRecursive(false);
    }
};

TEST_F(ArgumentTesting, SingleArgumentTrue) {
    // Let
    int argc = 2;
    char* args[] = {
            "./test",
            "-r"
    };

    // do work
    argumentParser.parse_main(argc, args);


    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}

TEST_F(ArgumentTesting, SingleArgumentFalse) {
    int argc = 2;
    char* args[] = {
            "./test",
            "-a"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), false);
}

TEST_F(ArgumentTesting, MultipleArgumentTrue) {
    int argc = 2;
    char* args[] = {
            "./test",
            "-rf"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), true);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}

TEST_F(ArgumentTesting, MultipleArgumentFalse) {
    // Let
    int argc = 2;
    char* args[] = {
            "./test",
            "-as"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), false);
}
