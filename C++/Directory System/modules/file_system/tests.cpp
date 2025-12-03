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

    File* f0{};
    File* f1{};
    File* f2{};
    File* f3{};

    File* f_root{};
    void SetUp() override
    {
        a = new Folder("A", system.root);
        b = new Folder("B", a);
        c = new Folder("C", b);
        f1 = new File("File 0.txt", c);

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

TEST_F(PathParserTester, tokenizeNothing)
{
    const std::string input = "";
    const Tokens tokens = parser.tokenize(input);

    EXPECT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0], "");
}

TEST_F(PathParserTester, parseFolder)
{
    const std::string input = "A";
    const Tokens tokens = parser.tokenize(input);
    const auto [folder, name] = parser.parse(tokens);

    EXPECT_EQ(folder, a);
    EXPECT_EQ(name, "");
    EXPECT_TRUE(parser.isFolder({folder, name}));
}

TEST_F(PathParserTester, parseFile)
{
    const std::string input = "File 4.txt";
    const Tokens tokens = parser.tokenize(input);
    const auto [folder, name] = parser.parse(tokens);

    EXPECT_EQ(folder, system.root);
    EXPECT_EQ(name, "File 4.txt");
    EXPECT_TRUE(parser.isFileOrName({folder, name}));
}

TEST_F(PathParserTester, parseNested)
{
    const std::string input = "1/2/File 1.txt";
    const Tokens tokens = parser.tokenize(input);
    const auto [folder, name] = parser.parse(tokens);

    EXPECT_EQ(folder, _2);
    EXPECT_EQ(name, "File 1.txt");
}

TEST_F(PathParserTester, parseRelative)
{
    system.setWorkingDirectory(_2);

    const std::string input = "File 1.txt";
    const Tokens tokens = parser.tokenize(input);
    const auto [folder, name] = parser.parse(tokens);

    EXPECT_EQ(folder, _2);
    EXPECT_EQ(name, "File 1.txt");
}

TEST_F(PathParserTester, parseAbsolute)
{
    system.setWorkingDirectory(_2);

    const std::string input = "/A/B/C/File 0.txt";
    const Tokens tokens = parser.tokenize(input);
    const auto [folder, name] = parser.parse(tokens);

    EXPECT_EQ(folder, c);
    EXPECT_EQ(name, "File 0.txt");
}

TEST_F(PathParserTester, parseNothing)
{
    const std::string input = "";
    const Tokens tokens = parser.tokenize(input);
    const auto [folder, name] = parser.parse(tokens);

    EXPECT_EQ(folder, system.getWorkingDirectory());
    EXPECT_EQ(name, "");
}