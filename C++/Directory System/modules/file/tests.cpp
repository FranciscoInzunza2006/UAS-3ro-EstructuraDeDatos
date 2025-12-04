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
    Folder* d{};
    Folder* e{};

    File* f1{};
    File* f2{};
    File* f3{};
    File* f4{};

    void SetUp() override
    {
        root = new Folder("", nullptr);
        a = new Folder("A", root);
        b = new Folder("B", a);
        c = new Folder("C", b);

        d = new Folder("1", root);
        e = new Folder("2", d);

        f1 = new File("File 1.txt", e);
        f2 = new File("File 2.txt", e);
        f3 = new File("File 3.txt", e);

        f4 = new File("File.txt", root);
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

    ASSERT_EQ(e->getPath(), "/1/2");
    ASSERT_EQ(f1->getPath(), "/1/2/File 1.txt");
}

TEST_F(FileSystemTester, getPath_rootFile)
{
    ASSERT_EQ(f4->getPath(), "/File.txt");
}

// Searching
TEST_F(FileSystemTester, search)
{
    ASSERT_NE(root, nullptr);

    EXPECT_NE(root->findEntry("A"), nullptr);
    EXPECT_NE(root->findEntry("1"), nullptr);
    EXPECT_NE(root->findEntry("File.txt"), nullptr);
}

TEST_F(FileSystemTester, search_deep)
{
    EXPECT_NE(root->findEntry("C"), nullptr);
    EXPECT_NE(a->findEntry("C"), nullptr);
    EXPECT_NE(b->findEntry("C"), nullptr);

    EXPECT_EQ(root->findEntry("NonExistent"), nullptr);
}

TEST_F(FileSystemTester, search_after_structure_mutations)
{
    b->moveTo(root);
    c->moveTo(e);
    f3->moveTo(root);
    f4->moveTo(a);

    EXPECT_NE(root->findEntry("B"), nullptr);
    EXPECT_NE(e->findEntry("C"), nullptr);
    EXPECT_NE(root->findEntry("File 3.txt"), nullptr);
    EXPECT_NE(a->findEntry("File.txt"), nullptr);

    EXPECT_EQ(b->findEntry("C"), nullptr);
    EXPECT_EQ(d->findEntry("File.txt"), nullptr);
}

// Moving
TEST_F(FileSystemTester, move_simple)
{
    ASSERT_EQ(f4->parent, root);

    f4->moveTo(d);
    EXPECT_EQ(f4->parent, d);
    EXPECT_NE(d->findEntry("File.txt"), nullptr);
    EXPECT_EQ(root->findEntry("File.txt"), nullptr);
}

TEST_F(FileSystemTester, move_between_branches)
{
    ASSERT_EQ(f1->parent, e);

    f1->moveTo(a);
    EXPECT_EQ(f1->parent, a);
    EXPECT_NE(a->findEntry("File 1.txt"), nullptr);
    EXPECT_EQ(e->findEntry("File 1.txt"), nullptr);
}

TEST_F(FileSystemTester, movingIntoDescendant)
{
    // Move A into C (illegal, C is descendant of A)
    EXPECT_THROW(a->moveTo(c), std::invalid_argument);

    // Should NOT have moved
    EXPECT_EQ(a->parent, root);
    EXPECT_NE(root->findEntry("A"), nullptr);
    EXPECT_NE(a->findEntry("C"), nullptr); // Ensure original structure intact
}

TEST_F(FileSystemTester, move_subtree_and_check_contents)
{
    // Move B under root (bringing C along)
    b->moveTo(root);
    EXPECT_EQ(b->parent, root);
    EXPECT_NE(root->findEntry("B"), nullptr);
    EXPECT_NE(b->findEntry("C"), nullptr);

    // Then move C elsewhere
    c->moveTo(d);
    EXPECT_EQ(c->parent, d);
    EXPECT_EQ(b->findEntry("C"), nullptr);
    EXPECT_NE(d->findEntry("C"), nullptr);
}

TEST_F(FileSystemTester, move_folder_with_many_children)
{
    // Add more files under _1
    std::vector<File*> extraFiles;
    extraFiles.reserve(20);
    for (int i = 0; i < 20; ++i)
        extraFiles.push_back(new File("F" + std::to_string(i), d));

    const size_t originalCount = d->entries.size();

    // Move entire folder _1 (containing 2, f1, f2, f3, and 20 extra files)
    d->moveTo(a);

    EXPECT_EQ(d->parent, a);
    EXPECT_EQ(d->entries.size(), originalCount);
    EXPECT_NE(a->findEntry("1"), nullptr);

    // All those files should still belong to _1
    for (auto* f : extraFiles)
        EXPECT_NE(d->findEntry(f->filename), nullptr);
}

TEST_F(FileSystemTester, movingToSamePlace)
{
    ASSERT_EQ(a->parent, root);

    a->moveTo(root); // Should be no-op
    EXPECT_EQ(a->parent, root);
    EXPECT_NE(root->findEntry("A"), nullptr);
}

TEST_F(FileSystemTester, children_integrity_after_moves)
{
    f1->moveTo(root);
    f2->moveTo(root);

    EXPECT_EQ(root->findEntry("File 1.txt"), f1);
    EXPECT_EQ(root->findEntry("File 2.txt"), f2);
    EXPECT_EQ(e->findEntry("File 1.txt"), nullptr);
    EXPECT_EQ(e->findEntry("File 2.txt"), nullptr);
}

TEST_F(FileSystemTester, repeated_moves_file)
{
    ASSERT_EQ(f1->parent, e);

    f1->moveTo(a);
    EXPECT_EQ(f1->parent, a);
    EXPECT_NE(a->findEntry("File 1.txt"), nullptr);

    f1->moveTo(d);
    EXPECT_EQ(f1->parent, d);
    EXPECT_NE(d->findEntry("File 1.txt"), nullptr);
    EXPECT_EQ(a->findEntry("File 1.txt"), nullptr);

    f1->moveTo(root);
    EXPECT_EQ(f1->parent, root);
    EXPECT_NE(root->findEntry("File 1.txt"), nullptr);
    EXPECT_EQ(d->findEntry("File 1.txt"), nullptr);
}

TEST_F(FileSystemTester, repeated_moves_folder)
{
    ASSERT_EQ(c->parent, b);

    c->moveTo(root);
    EXPECT_EQ(c->parent, root);
    EXPECT_NE(root->findEntry("C"), nullptr);

    c->moveTo(d);
    EXPECT_EQ(c->parent, d);
    EXPECT_NE(d->findEntry("C"), nullptr);

    c->moveTo(a);
    EXPECT_EQ(c->parent, a);
    EXPECT_NE(a->findEntry("C"), nullptr);
    EXPECT_EQ(d->findEntry("C"), nullptr);
}

TEST_F(FileSystemTester, chain_move_back_and_forth)
{
    // Back and forth multiple times
    for (int i = 0; i < 10; ++i)
    {
        f1->moveTo(a);
        EXPECT_EQ(f1->parent, a);
        EXPECT_NE(a->findEntry("File 1.txt"), nullptr);

        f1->moveTo(e);
        EXPECT_EQ(f1->parent, e);
        EXPECT_NE(e->findEntry("File 1.txt"), nullptr);
    }
}

// Removing
TEST_F(FileSystemTester, remove)
{
    ASSERT_NE(root, nullptr);
    const std::size_t children_count = root->entries.size();

    auto* ap = dynamic_cast<Folder*>(root->findEntry("A"));
    ASSERT_NE(ap, nullptr);
    root->removeEntry(ap);
    EXPECT_EQ(children_count-1, root->entries.size());
}

TEST_F(FileSystemTester, remove_folder)
{
    ASSERT_NE(a->parent, nullptr);

    const std::size_t count_before = a->parent->entries.size();
    a->parent->removeEntry(a);
    EXPECT_EQ(a->parent->entries.size(), count_before - 1);

    // A still exists but is detached
    EXPECT_EQ(root->findEntry("A"), nullptr);
    EXPECT_EQ(a->parent->entries.end(),
              std::find(a->parent->entries.begin(), a->parent->entries.end(), a));
}

TEST_F(FileSystemTester, deletion_cascades)
{
    // Delete subtree /A
    delete a;

    // A must be removed from root
    EXPECT_EQ(root->findEntry("A"), nullptr);

    // B and C should have been destroyed internally
    // Not checking destruction messages, but ensure structure is stable
    EXPECT_NO_THROW(root->showContents());
}

TEST_F(FileSystemTester, remove_child_after_moves)
{
    f1->moveTo(root);
    f2->moveTo(root);

    const size_t before = root->entries.size();

    root->removeEntry(f1);
    EXPECT_EQ(root->entries.size(), before - 1);
    EXPECT_EQ(root->findEntry("File 1.txt"), nullptr);

    // Ensure others remain intact
    EXPECT_NE(root->findEntry("File 2.txt"), nullptr);
    EXPECT_NE(root->findEntry("A"), nullptr);
}

TEST_F(FileSystemTester, deleting_folder_after_many_operations)
{
    c->moveTo(root);
    f1->moveTo(a);
    f2->moveTo(root);
    f3->moveTo(b);
    e->moveTo(root);

    EXPECT_NO_THROW(delete a);  // Delete subtree A

    EXPECT_EQ(root->findEntry("A"), nullptr);
    EXPECT_EQ(root->findEntry("File 1.txt"), nullptr); // was under A after move
    EXPECT_NE(root->findEntry("File 2.txt"), nullptr); // unaffected
    EXPECT_NE(b->findEntry("File 3.txt"), nullptr);    // unaffected
}
