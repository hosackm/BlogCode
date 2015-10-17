#include <gtest/gtest.h>
#include "graph.h"

class graphFixture : public ::testing::Test
{
public:
    void SetUp(){
        g = graph_create();
    }
    void TearDown(){
        graph_destroy(g);
    }

    graph g;
};

TEST_F(graphFixture, CreateThrowsNoError)
{
    EXPECT_NE(nullptr, g);
}

TEST_F(graphFixture, AddVertex)
{
    graph_add_vertex(g, 3);
    graph_add_vertex(g, 4);
    graph_add_vertex(g, 5);
    graph_add_edge(g, 3, 5);
    graph_add_edge(g, 3, 4);
    graph_add_edge(g, 4, 3);
    graph_add_edge(g, 4, 5);
    graph_list_vertices(g);
    graph_list_edges(g);

    EXPECT_EQ(1, graph_reachable(g, 3, 5));
    EXPECT_EQ(0, graph_reachable(g, 3, 9));
    EXPECT_EQ(0, graph_reachable(g, 5, 3));
}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
