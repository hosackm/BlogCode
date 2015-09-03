#include <vector>

#include <gtest/gtest.h>
#include "btree.h"

class btreeFixture : public ::testing::Test
{
public:
    void SetUp(){
        bt = btree_create();
    }
    void TearDown(){
        btree_destroy(bt);
    }
    btree bt;
};

TEST_F(btreeFixture, CreateThrowsNoError)
{
    EXPECT_EQ(NULL, bt);
}

TEST_F(btreeFixture, InsertOneNodeNoError)
{
    EXPECT_EQ(0, btree_insert(&bt, 0));
}

TEST_F(btreeFixture, InsertManyNodesNoError)
{
    for(int i = 0; i < 2000; ++i)
    {
        EXPECT_EQ(0, btree_insert(&bt, i));
    }
}

TEST_F(btreeFixture, InsertOneAndFindIt)
{
    /* If you insert 42 you should be able to find it */
    btree_insert(&bt, 42);
    EXPECT_EQ(1, btree_find(bt, 42));
}

TEST_F(btreeFixture, InsertOneAndDontFindADifferentValue)
{
    /* You shouldn't be able to find 1337 if you insert 42 */
    btree_insert(&bt, 42);
    EXPECT_EQ(0, btree_find(bt, 1337));
}

TEST_F(btreeFixture, InsertManyAndFindThem)
{
    /* Insert multiple numbers and make sure you can find them all */
    std::vector<int> inputs;
    inputs.push_back(42);
    inputs.push_back(1337);
    inputs.push_back(1987);
    inputs.push_back(-4096);
    inputs.push_back(-30000000);
    inputs.push_back(0);
    inputs.push_back(13);
    inputs.push_back(7);
    
    for (size_t i = 0; i < inputs.size(); ++i) {
        btree_insert(&bt, inputs[i]);
    }

    for (size_t i = 0; i < inputs.size(); ++i) {
        EXPECT_EQ(1, btree_find(bt, inputs[i]));
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
