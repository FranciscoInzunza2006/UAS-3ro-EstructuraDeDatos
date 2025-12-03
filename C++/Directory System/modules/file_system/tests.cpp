#include "file.hpp"
#include <gtest/gtest.h>

#include "file_system.hpp"

class FileSystemTester : public testing::Test
{
protected:
    FileSystem system{};

    Folder* a{};
    Folder* b{};
    Folder* c{};

    Folder* _1{};
    Folder* _2{};

    File* f1{};
    File* f2{};
    File* f3{};
    File* f_root{};

    void SetUp() override
    {
        a = new Folder("A", system.root);
        b = new Folder("B", a);
        c = new Folder("C", b);

        _1 = new Folder("1", system.root);
        _2 = new Folder("2", _1);

        f1 = new File("File 1.txt", _2);
        f2 = new File("File 2.txt", _2);
        f3 = new File("File 3.txt", _2);
        f_root = new File("File 4.txt", system.root);
    }

    void TearDown() override
    {
    }

public:
    ~FileSystemTester() override = default;
};

class PathParserTester : public FileSystemTester
{
protected:
    PathParser parser = PathParser(&system);
};

// Tree Structure
TEST_F(FileSystemTester, printTestStructure)
{
    EXPECT_NO_THROW(system.root->showContents());
}

// Path parser
TEST_F(PathParserTester, tokenize)
{
    const std::string input = "A/B/C/";
    const Tokens tokens = parser.tokenize(input);

    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "A");
    EXPECT_EQ(tokens[1], "B");
    EXPECT_EQ(tokens[2], "C");
}

TEST_F(PathParserTester, tokenizeRoot)
{
    const std::string input = "/A";
    const Tokens tokens = parser.tokenize(input);

    EXPECT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0], "");
    EXPECT_EQ(tokens[1], "A");
}