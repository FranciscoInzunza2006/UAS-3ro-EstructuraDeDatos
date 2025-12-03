#include "file.hpp"
#include <gtest/gtest.h>

/// ChatGPT generated most of the tests

class FileSystemTester : public testing::Test
{
protected:
    Folder* root{};
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
        root = new Folder("", nullptr);
        a = new Folder("A", root);
        b = new Folder("B", a);
        c = new Folder("C", b);

        _1 = new Folder("1", root);
        _2 = new Folder("2", _1);

        f1 = new File("File 1.txt", _2);
        f2 = new File("File 2.txt", _2);
        f3 = new File("File 3.txt", _2);

        f_root = new File("File.txt", root);
    }

    void TearDown() override
    {
        delete root;
    }

public:
    ~FileSystemTester() override= default;
};

// Tree Structure
TEST_F(FileSystemTester, subtreePrinting_doesNotCrash)
{
    EXPECT_NO_THROW(root->showContents());
}

// Path
TEST_F(FileSystemTester, getPath_basic)
{
    ASSERT_EQ(a->getPath(), "/A");
    ASSERT_EQ(b->getPath(), "/A/B");
    ASSERT_EQ(c->getPath(), "/A/B/C");

    ASSERT_EQ(_2->getPath(), "/1/2");
    ASSERT_EQ(f1->getPath(), "/1/2/File 1.txt");
}

TEST_F(FileSystemTester, getPath_rootFile)
{
    ASSERT_EQ(f_root->getPath(), "/File.txt");
}

// Searching
TEST_F(FileSystemTester, search)
{
    ASSERT_NE(root, nullptr);

    EXPECT_NE(root->search("A"), nullptr);
    EXPECT_NE(root->search("1"), nullptr);
    EXPECT_NE(root->search("File.txt"), nullptr);
}

TEST_F(FileSystemTester, search_deep)
{
    EXPECT_NE(root->search("C"), nullptr);
    EXPECT_NE(a->search("C"), nullptr);
    EXPECT_NE(b->search("C"), nullptr);

    EXPECT_EQ(root->search("NonExistent"), nullptr);
}

TEST_F(FileSystemTester, search_after_structure_mutations)
{
    b->move(root);
    c->move(_2);
    f3->move(root);
    f_root->move(a);

    EXPECT_NE(root->search("B"), nullptr);
    EXPECT_NE(_2->search("C"), nullptr);
    EXPECT_NE(root->search("File 3.txt"), nullptr);
    EXPECT_NE(a->search("File.txt"), nullptr);

    EXPECT_EQ(b->search("C"), nullptr);
    EXPECT_EQ(_1->search("File.txt"), nullptr);
}

// Moving
TEST_F(FileSystemTester, move_simple)
{
    ASSERT_EQ(f_root->father, root);

    f_root->move(_1);
    EXPECT_EQ(f_root->father, _1);
    EXPECT_NE(_1->search("File.txt"), nullptr);
    EXPECT_EQ(root->search("File.txt"), nullptr);
}

TEST_F(FileSystemTester, move_between_branches)
{
    ASSERT_EQ(f1->father, _2);

    f1->move(a);
    EXPECT_EQ(f1->father, a);
    EXPECT_NE(a->search("File 1.txt"), nullptr);
    EXPECT_EQ(_2->search("File 1.txt"), nullptr);
}

TEST_F(FileSystemTester, movingIntoDescendant)
{
    // Move A into C (illegal, C is descendant of A)
    EXPECT_THROW(a->move(c), std::invalid_argument);

    // Should NOT have moved
    EXPECT_EQ(a->father, root);
    EXPECT_NE(root->search("A"), nullptr);
    EXPECT_NE(a->search("C"), nullptr); // Ensure original structure intact
}

TEST_F(FileSystemTester, move_subtree_and_check_contents)
{
    // Move B under root (bringing C along)
    b->move(root);
    EXPECT_EQ(b->father, root);
    EXPECT_NE(root->search("B"), nullptr);
    EXPECT_NE(b->search("C"), nullptr);

    // Then move C elsewhere
    c->move(_1);
    EXPECT_EQ(c->father, _1);
    EXPECT_EQ(b->search("C"), nullptr);
    EXPECT_NE(_1->search("C"), nullptr);
}

TEST_F(FileSystemTester, move_folder_with_many_children)
{
    // Add more files under _1
    std::vector<File*> extraFiles;
    extraFiles.reserve(20);
    for (int i = 0; i < 20; ++i)
        extraFiles.push_back(new File("F" + std::to_string(i), _1));

    const size_t originalCount = _1->children.size();

    // Move entire folder _1 (containing 2, f1, f2, f3, and 20 extra files)
    _1->move(a);

    EXPECT_EQ(_1->father, a);
    EXPECT_EQ(_1->children.size(), originalCount);
    EXPECT_NE(a->search("1"), nullptr);

    // All those files should still belong to _1
    for (auto* f : extraFiles)
        EXPECT_NE(_1->search(f->name), nullptr);
}

TEST_F(FileSystemTester, movingToSamePlace)
{
    ASSERT_EQ(a->father, root);

    a->move(root); // Should be no-op
    EXPECT_EQ(a->father, root);
    EXPECT_NE(root->search("A"), nullptr);
}

TEST_F(FileSystemTester, children_integrity_after_moves)
{
    f1->move(root);
    f2->move(root);

    EXPECT_EQ(root->search("File 1.txt"), f1);
    EXPECT_EQ(root->search("File 2.txt"), f2);
    EXPECT_EQ(_2->search("File 1.txt"), nullptr);
    EXPECT_EQ(_2->search("File 2.txt"), nullptr);
}

TEST_F(FileSystemTester, repeated_moves_file)
{
    ASSERT_EQ(f1->father, _2);

    f1->move(a);
    EXPECT_EQ(f1->father, a);
    EXPECT_NE(a->search("File 1.txt"), nullptr);

    f1->move(_1);
    EXPECT_EQ(f1->father, _1);
    EXPECT_NE(_1->search("File 1.txt"), nullptr);
    EXPECT_EQ(a->search("File 1.txt"), nullptr);

    f1->move(root);
    EXPECT_EQ(f1->father, root);
    EXPECT_NE(root->search("File 1.txt"), nullptr);
    EXPECT_EQ(_1->search("File 1.txt"), nullptr);
}

TEST_F(FileSystemTester, repeated_moves_folder)
{
    ASSERT_EQ(c->father, b);

    c->move(root);
    EXPECT_EQ(c->father, root);
    EXPECT_NE(root->search("C"), nullptr);

    c->move(_1);
    EXPECT_EQ(c->father, _1);
    EXPECT_NE(_1->search("C"), nullptr);

    c->move(a);
    EXPECT_EQ(c->father, a);
    EXPECT_NE(a->search("C"), nullptr);
    EXPECT_EQ(_1->search("C"), nullptr);
}

TEST_F(FileSystemTester, chain_move_back_and_forth)
{
    // Back and forth multiple times
    for (int i = 0; i < 10; ++i)
    {
        f1->move(a);
        EXPECT_EQ(f1->father, a);
        EXPECT_NE(a->search("File 1.txt"), nullptr);

        f1->move(_2);
        EXPECT_EQ(f1->father, _2);
        EXPECT_NE(_2->search("File 1.txt"), nullptr);
    }
}

// Removing
TEST_F(FileSystemTester, remove)
{
    ASSERT_NE(root, nullptr);
    const std::size_t children_count = root->children.size();

    auto* ap = dynamic_cast<Folder*>(root->search("A"));
    ASSERT_NE(ap, nullptr);
    root->removeChild(ap);
    EXPECT_EQ(children_count-1, root->children.size());
}

TEST_F(FileSystemTester, remove_folder)
{
    ASSERT_NE(a->father, nullptr);

    const std::size_t count_before = a->father->children.size();
    a->father->removeChild(a);
    EXPECT_EQ(a->father->children.size(), count_before - 1);

    // A still exists but is detached
    EXPECT_EQ(root->search("A"), nullptr);
    EXPECT_EQ(a->father->children.end(),
              std::find(a->father->children.begin(), a->father->children.end(), a));
}

TEST_F(FileSystemTester, deletion_cascades)
{
    // Delete subtree /A
    delete a;

    // A must be removed from root
    EXPECT_EQ(root->search("A"), nullptr);

    // B and C should have been destroyed internally
    // Not checking destruction messages, but ensure structure is stable
    EXPECT_NO_THROW(root->showContents());
}

TEST_F(FileSystemTester, remove_child_after_moves)
{
    f1->move(root);
    f2->move(root);

    const size_t before = root->children.size();

    root->removeChild(f1);
    EXPECT_EQ(root->children.size(), before - 1);
    EXPECT_EQ(root->search("File 1.txt"), nullptr);

    // Ensure others remain intact
    EXPECT_NE(root->search("File 2.txt"), nullptr);
    EXPECT_NE(root->search("A"), nullptr);
}

TEST_F(FileSystemTester, deleting_folder_after_many_operations)
{
    c->move(root);
    f1->move(a);
    f2->move(root);
    f3->move(b);
    _2->move(root);

    EXPECT_NO_THROW(delete a);  // Delete subtree A

    EXPECT_EQ(root->search("A"), nullptr);
    EXPECT_EQ(root->search("File 1.txt"), nullptr); // was under A after move
    EXPECT_NE(root->search("File 2.txt"), nullptr); // unaffected
    EXPECT_NE(b->search("File 3.txt"), nullptr);    // unaffected
}
