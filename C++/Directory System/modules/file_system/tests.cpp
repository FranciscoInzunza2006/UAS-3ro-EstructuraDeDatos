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

class FileSystemCommandsTester : public FileSystemTester
{
    protected:
    FileSystemCommands cmds = FileSystemCommands(&system);
};

// Tree Structure
TEST_F(FileSystemTester, printTestStructure)
{
    EXPECT_NO_THROW(system.root->showContents());
}

//region Path parser
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
    const ParsingResult result = parser.parse(tokens);

    EXPECT_EQ(result.file, a);
    EXPECT_EQ(result.name, "");
    EXPECT_TRUE(result.isFolder());
}

TEST_F(PathParserTester, parseFile)
{
    const std::string input = "File 4.txt";
    const Tokens tokens = parser.tokenize(input);
    const ParsingResult result = parser.parse(tokens);

    EXPECT_TRUE(result.exists());
    EXPECT_FALSE(result.isFolder());

    EXPECT_EQ(result.file, _2);
    EXPECT_EQ(result.file, f_root);
    EXPECT_EQ(result.file->name, "File 4.txt");
}

TEST_F(PathParserTester, parseNested)
{
    const std::string input = "1/2/File 1.txt";
    const Tokens tokens = parser.tokenize(input);
    const ParsingResult result = parser.parse(tokens);

    EXPECT_EQ(result.file, f1);
    EXPECT_EQ(result.file->name, "File 1.txt");
}

TEST_F(PathParserTester, parseRelative)
{
    system.setWorkingDirectory(_2);

    const std::string input = "File 1.txt";
    const Tokens tokens = parser.tokenize(input);
    const ParsingResult result = parser.parse(tokens);

    EXPECT_EQ(result.file, f1);
    EXPECT_EQ(result.file->name, "File 1.txt");
}

TEST_F(PathParserTester, parseAbsolute)
{
    system.setWorkingDirectory(_2);

    const std::string input = "/A/B/C/File 0.txt";
    const Tokens tokens = parser.tokenize(input);
    const ParsingResult result = parser.parse(tokens);

    EXPECT_EQ(result.file, f0);
    EXPECT_EQ(result.file->name, "File 0.txt");
}

TEST_F(PathParserTester, parseNothing)
{
    const std::string input{};
    const Tokens tokens = parser.tokenize(input);
    const ParsingResult result = parser.parse(tokens);

    EXPECT_EQ(result.file, system.getWorkingDirectory());
    EXPECT_EQ(result.name, "");
}

TEST_F(PathParserTester, parseNonExistant)
{
    const std::string input = "A/B/X/C";
    const Tokens tokens = parser.tokenize(input);

    EXPECT_THROW(parser.parse(tokens), std::runtime_error);
}

TEST_F(PathParserTester, parseFileUsedAsDirectory)
{
    const std::string input = "File 4.txt/Another folder";
    const Tokens tokens = parser.tokenize(input);

    EXPECT_THROW(parser.parse(tokens), std::invalid_argument);
}

//endregion

//region UI
// TEST_F(FileSystemCommandsTester, createFile)
// {
//     const Tokens tokens = {"A/B/New.txt"};
//     cmds.createFile(tokens);
//
//     b->showContents();
//     EXPECT_EQ(b->children.size(), 2);
// }
//
// TEST_F(FileSystemCommandsTester, createExistingFile)
// {
//     const Tokens tokens = {"File 4.txt"};
//
//     b->showContents();
// }

//endregion
