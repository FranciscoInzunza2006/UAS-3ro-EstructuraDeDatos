
#include "command_line.hpp"
#include <gtest/gtest.h>

TEST(TokenizerTest, normalInput) {
    const std::string input = "mov /A/B/C /BIN";
    const Tokens tokens = CommandLine::Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "mov");
    EXPECT_EQ(tokens[1], "/A/B/C");
    EXPECT_EQ(tokens[2], "/BIN");
}

TEST(TokenizerTest, spaceAround) {
    const std::string input = "        mov      /A/B/C /BIN           ";
    const Tokens tokens = CommandLine::Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "mov");
    EXPECT_EQ(tokens[1], "/A/B/C");
    EXPECT_EQ(tokens[2], "/BIN");
}

TEST(TokenizerTest, stringWithQuotes) {
    const std::string input = R"(mov "Some document.txt" "/Folder/Boring Homework/")";
    const Tokens tokens = CommandLine::Tokenizer::tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "mov");
    EXPECT_EQ(tokens[1], "Some document.txt");
    EXPECT_EQ(tokens[2], "/Folder/Boring Homework/");
}

TEST(TokenizerTest, unclosedStringWithQuotes) {
    const std::string input = R"(mov "Some document.txt" "/Folder/Boring Homework/)";
    EXPECT_THROW(CommandLine::Tokenizer::tokenize(input), std::runtime_error);
}