//
// Created by Keiwan Jamaly on 11.10.22.
//

#include <gtest/gtest.h>
#include "Graph.h"
#include "Data.cpp"
#include <vector>
#include <cmath>

namespace dp {

    bool decision(std::vector<double> x_1, std::vector<double> x_2) {
        if (std::abs(x_1[0] - x_2[0]) < 0.5) {
            return true;
        } else {
            return false;
        }
    }

    class GraphTestFixture : public ::testing::Test {

    protected:
        void SetUp() override {
            x = 0.5;
            y = 0.5;
            x_min = 0.0;
            x_max = 1.0;
            y_min = 0.0;
            y_max = 1.0;
            test_graph = Graph<Data>(decision, x, y, x_min, x_max, y_min, y_max);
        }

        Graph<Data> test_graph;
        double x{}, y{};
        double x_min{}, x_max{}, y_min{}, y_max{};
    };

    // test constructor
    TEST_F(GraphTestFixture, PositionsAreCorrect) {
        EXPECT_EQ(test_graph.root.x, 0.5);
        EXPECT_EQ(test_graph.root.y, 0.5);
        EXPECT_EQ(test_graph.root.data.x, 0.5);
        EXPECT_EQ(test_graph.root.data.y, 0.5);
    }
}


