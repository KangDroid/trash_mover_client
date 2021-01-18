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

TEST_F(ArgumentTesting, ShortSingleArgumentTrue) {
    // Let
    int argc = 2;
    char* args[] = {
            (char*)"./test",
            (char*)"-r"
    };

    // do work
    argumentParser.parse_main(argc, args);


    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}

TEST_F(ArgumentTesting, ShortSingleArgumentFalse) {
    int argc = 2;
    char* args[] = {
            (char*)"./test",
            (char*)"-a"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), false);
}

TEST_F(ArgumentTesting, ShortMultipleArgumentTrue) {
    int argc = 2;
    char* args[] = {
            (char*)"./test",
            (char*)"-rf"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), true);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}

TEST_F(ArgumentTesting, ShortMultipleArgumentFalse) {
    // Let
    int argc = 2;
    char* args[] = {
            (char*)"./test",
            (char*)"-as"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), false);
}

TEST_F(ArgumentTesting, LongSingleArgumentTrue) {
    // Let
    int argc = 2;
    char* args[] = {
            (char*)"./test",
            (char*)"--recursive"
    };

    // do work
    argumentParser.parse_main(argc, args);
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}

TEST_F(ArgumentTesting, LongSingleArgumentFalse) {
    // Let
    int argc = 2;
    char* args[] = {
            (char*)"./test",
            (char*)"--unknown-option"
    };

    // do work
    argumentParser.parse_main(argc, args);
    EXPECT_EQ(argsDefinition->isServerOn(), false);
    EXPECT_EQ(argsDefinition->isForce(), false);
    EXPECT_EQ(argsDefinition->isRecursive(), false);
}

TEST_F(ArgumentTesting, LongMultipleArgumentTrue) {
    // Let
    int argc = 5;
    char* args[] = {
            (char*)"./test",
            (char*)"--recursive",
            (char*)"--autorun_server",
            (char*)"--force",
            (char*)"--verbose"

    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isVerbose(), true);
    EXPECT_EQ(argsDefinition->isServerOn(), true);
    EXPECT_EQ(argsDefinition->isForce(), true);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}

TEST_F(ArgumentTesting, ShortLongCombined) {
    // Let
    int argc = 4;
    char* args[] = {
            (char*)"./test",
            (char*)"--autorun_server",
            (char*)"--recursive",
            (char*)"-vf"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isVerbose(), true);
    EXPECT_EQ(argsDefinition->isServerOn(), true);
    EXPECT_EQ(argsDefinition->isForce(), true);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}