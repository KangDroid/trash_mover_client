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

TEST_F(ArgumentTesting, ShortSingleArgumentFalse) {
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

TEST_F(ArgumentTesting, ShortMultipleArgumentTrue) {
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

TEST_F(ArgumentTesting, ShortMultipleArgumentFalse) {
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

TEST_F(ArgumentTesting, LongSingleArgumentTrue) {
    // Let
    int argc = 2;
    char* args[] = {
            "./test",
            "--recursive"
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
            "./test",
            "--unknown-option"
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
            "./test",
            "--recursive",
            "--autorun_server",
            "--force",
            "--verbose"

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
            "./test",
            "--autorun_server",
            "--recursive",
            "-vf"
    };

    // do work
    argumentParser.parse_main(argc, args);

    // Assert
    EXPECT_EQ(argsDefinition->isVerbose(), true);
    EXPECT_EQ(argsDefinition->isServerOn(), true);
    EXPECT_EQ(argsDefinition->isForce(), true);
    EXPECT_EQ(argsDefinition->isRecursive(), true);
}