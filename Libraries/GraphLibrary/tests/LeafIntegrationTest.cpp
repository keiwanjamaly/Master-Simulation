//
// Created by Keiwan Jamaly on 17.10.22.
//
#include "gtest/gtest.h"
#include "Leaf.h"
#include "Types.h"
#include "TestData.h"

namespace dp {

    class NeighbourLeafTestFixture_H : public ::testing::Test {
        // I'm going to test the neighbours of the following points
        // test points      test labels
        // x, 0, 0, x       nw_nw, nw_ne, ne_nw, ne_ne
        // 0, x, 0, 0       nw_sw, nw_se, ne_sw, ne_se
        // 0, 0, x, 0       sw_nw, sw_ne, se_nw, se_ne
        // x, 0, 0, x       sw_sw, sw_se, se_sw, se_se

        // testing values outside the boundary should result in a null-pointer

    protected:
        void SetUp() override {
            x = 0.0;
            y = 0.0;
            box_size = 1.0;
            test_leaf = Leaf<Data_H>(x, y, box_size, split_decision);

            test_leaf.attach_leaves();
            leaf_nw = &(test_leaf.children[nw]);
            leaf_nw->attach_leaves();
            leaf_ne = &(test_leaf.children[ne]);
            leaf_ne->attach_leaves();
            leaf_sw = &(test_leaf.children[sw]);
            leaf_sw->attach_leaves();
            leaf_se = &(test_leaf.children[se]);
            leaf_se->attach_leaves();

            leaf_nw_nw = &(leaf_nw->children[nw]);
            leaf_nw_ne = &(leaf_nw->children[ne]);
            leaf_nw_sw = &(leaf_nw->children[sw]);
            leaf_nw_se = &(leaf_nw->children[se]);

            leaf_ne_nw = &(leaf_ne->children[nw]);
            leaf_ne_ne = &(leaf_ne->children[ne]);
            leaf_ne_sw = &(leaf_ne->children[sw]);
            leaf_ne_se = &(leaf_ne->children[se]);

            leaf_sw_nw = &(leaf_sw->children[nw]);
            leaf_sw_ne = &(leaf_sw->children[ne]);
            leaf_sw_sw = &(leaf_sw->children[sw]);
            leaf_sw_se = &(leaf_sw->children[se]);

            leaf_se_nw = &(leaf_se->children[nw]);
            leaf_se_ne = &(leaf_se->children[ne]);
            leaf_se_sw = &(leaf_se->children[sw]);
            leaf_se_se = &(leaf_se->children[se]);

            leaf_nw_se->attach_leaves();
        }

        Leaf<Data_H> test_leaf;
        Leaf<Data_H> *test_child;
        double x{}, y{}, box_size{};
        Leaf<Data_H> *leaf_nw_nw, *leaf_nw_ne, *leaf_nw_sw, *leaf_nw_se, *leaf_ne_nw, *leaf_ne_ne, *leaf_ne_sw, *leaf_ne_se, *leaf_sw_nw, *leaf_sw_ne, *leaf_sw_sw, *leaf_sw_se, *leaf_se_nw, *leaf_se_ne, *leaf_se_sw, *leaf_se_se;
        Leaf<Data_H> *leaf_nw, *leaf_ne, *leaf_sw, *leaf_se;
    };

    class NeighbourLeafTestFixture : public ::testing::Test {
        // I'm going to test the neighbours of the following points
        // test points      test labels
        // x, 0, 0, x       nw_nw, nw_ne, ne_nw, ne_ne
        // 0, x, 0, 0       nw_sw, nw_se, ne_sw, ne_se
        // 0, 0, x, 0       sw_nw, sw_ne, se_nw, se_ne
        // x, 0, 0, x       sw_sw, sw_se, se_sw, se_se

        // testing values outside the boundary should result in a null-pointer

    protected:
        void SetUp() override {
            x = 0.0;
            y = 0.0;
            box_size = 1.0;
            test_leaf = Leaf<Data>(x, y, box_size, split_decision);

            test_leaf.attach_leaves();
            leaf_nw = &(test_leaf.children[nw]);
            leaf_nw->attach_leaves();
            leaf_ne = &(test_leaf.children[ne]);
            leaf_ne->attach_leaves();
            leaf_sw = &(test_leaf.children[sw]);
            leaf_sw->attach_leaves();
            leaf_se = &(test_leaf.children[se]);
            leaf_se->attach_leaves();

            leaf_nw_nw = &(leaf_nw->children[nw]);
            leaf_nw_ne = &(leaf_nw->children[ne]);
            leaf_nw_sw = &(leaf_nw->children[sw]);
            leaf_nw_se = &(leaf_nw->children[se]);

            leaf_ne_nw = &(leaf_ne->children[nw]);
            leaf_ne_ne = &(leaf_ne->children[ne]);
            leaf_ne_sw = &(leaf_ne->children[sw]);
            leaf_ne_se = &(leaf_ne->children[se]);

            leaf_sw_nw = &(leaf_sw->children[nw]);
            leaf_sw_ne = &(leaf_sw->children[ne]);
            leaf_sw_sw = &(leaf_sw->children[sw]);
            leaf_sw_se = &(leaf_sw->children[se]);

            leaf_se_nw = &(leaf_se->children[nw]);
            leaf_se_ne = &(leaf_se->children[ne]);
            leaf_se_sw = &(leaf_se->children[sw]);
            leaf_se_se = &(leaf_se->children[se]);

            leaf_nw_se->attach_leaves();
        }

        Leaf<Data> test_leaf;
        Leaf<Data> *test_child;
        double x{}, y{}, box_size{};
        Leaf<Data> *leaf_nw_nw, *leaf_nw_ne, *leaf_nw_sw, *leaf_nw_se, *leaf_ne_nw, *leaf_ne_ne, *leaf_ne_sw, *leaf_ne_se, *leaf_sw_nw, *leaf_sw_ne, *leaf_sw_sw, *leaf_sw_se, *leaf_se_nw, *leaf_se_ne, *leaf_se_sw, *leaf_se_se;
        Leaf<Data> *leaf_nw, *leaf_ne, *leaf_sw, *leaf_se;
    };

    TEST_F(NeighbourLeafTestFixture, GetDepthFunction) {
        ASSERT_EQ(test_leaf.get_depth(), 0);
        ASSERT_EQ(leaf_nw->get_depth(), 1);
        ASSERT_EQ(leaf_ne->get_depth(), 1);
        ASSERT_EQ(leaf_sw->get_depth(), 1);
        ASSERT_EQ(leaf_se->get_depth(), 1);

        ASSERT_EQ(leaf_nw_nw->get_depth(), 2);
        ASSERT_EQ(leaf_nw_ne->get_depth(), 2);
        ASSERT_EQ(leaf_nw_sw->get_depth(), 2);
        ASSERT_EQ(leaf_nw_se->get_depth(), 2);
        ASSERT_EQ(leaf_ne_nw->get_depth(), 2);
        ASSERT_EQ(leaf_ne_ne->get_depth(), 2);
        ASSERT_EQ(leaf_ne_sw->get_depth(), 2);
        ASSERT_EQ(leaf_ne_se->get_depth(), 2);
        ASSERT_EQ(leaf_sw_nw->get_depth(), 2);
        ASSERT_EQ(leaf_sw_ne->get_depth(), 2);
        ASSERT_EQ(leaf_sw_sw->get_depth(), 2);
        ASSERT_EQ(leaf_sw_se->get_depth(), 2);
        ASSERT_EQ(leaf_se_nw->get_depth(), 2);
        ASSERT_EQ(leaf_se_ne->get_depth(), 2);
        ASSERT_EQ(leaf_se_sw->get_depth(), 2);
        ASSERT_EQ(leaf_se_se->get_depth(), 2);

        // leaf_nw_se
        ASSERT_EQ(leaf_nw_se->children[nw].get_depth(), 3);
        ASSERT_EQ(leaf_nw_se->children[ne].get_depth(), 3);
        ASSERT_EQ(leaf_nw_se->children[sw].get_depth(), 3);
        ASSERT_EQ(leaf_nw_se->children[se].get_depth(), 3);
    }

    TEST_F(NeighbourLeafTestFixture, testNorthNeighbourFunction) {
        // testing nw_nw neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->north_neighbour(), nullptr);

        // testing ne_ne neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->north_neighbour(), nullptr);

        // testing nw_se neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->north_neighbour(), leaf_nw_ne);

        // testing se_nw neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->north_neighbour(), leaf_ne_sw);

        // testing sw_sw neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->north_neighbour(), leaf_sw_nw);

        // testing se_se neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->north_neighbour(), leaf_se_ne);

        // test, that only it gives the neighbour only on one level
        ASSERT_EQ(leaf_nw->north_neighbour(), nullptr);
        ASSERT_EQ(leaf_ne->north_neighbour(), nullptr);
        ASSERT_EQ(leaf_sw->north_neighbour(), leaf_nw);
        ASSERT_EQ(leaf_se->north_neighbour(), leaf_ne);

        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[nw].north_neighbour(), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testEastNeighbourFunction) {
// testing nw_nw neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->east_neighbour(), leaf_nw_ne);

// testing ne_ne neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->east_neighbour(), nullptr);

// testing nw_se neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->east_neighbour(), leaf_ne_sw);

// testing se_nw neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->east_neighbour(), leaf_se_ne);

// testing sw_sw neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->east_neighbour(), leaf_sw_se);

// testing se_se neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->east_neighbour(), nullptr);

// test, that only it gives the neighbour only on one level
        ASSERT_EQ(leaf_nw->east_neighbour(), leaf_ne);
        ASSERT_EQ(leaf_ne->east_neighbour(), nullptr);
        ASSERT_EQ(leaf_sw->east_neighbour(), leaf_se);
        ASSERT_EQ(leaf_se->east_neighbour(), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[ne].east_neighbour(), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testSouthNeighbourFunction) {
// testing nw_nw neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->south_neighbour(), leaf_nw_sw);

// testing ne_ne neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->south_neighbour(), leaf_ne_se);

// testing nw_se neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->south_neighbour(), leaf_sw_ne);

// testing se_nw neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->south_neighbour(), leaf_se_sw);

// testing sw_sw neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->south_neighbour(), nullptr);

// testing se_se neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->south_neighbour(), nullptr);

// test, that only it gives the neighbour only on one level
        ASSERT_EQ(leaf_nw->south_neighbour(), leaf_sw);
        ASSERT_EQ(leaf_ne->south_neighbour(), leaf_se);
        ASSERT_EQ(leaf_sw->south_neighbour(), nullptr);
        ASSERT_EQ(leaf_se->south_neighbour(), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[se].south_neighbour(), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testWestNeighbourFunction) {
// testing nw_nw neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->west_neighbour(), nullptr);

// testing ne_ne neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->west_neighbour(), leaf_ne_nw);

// testing nw_se neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->west_neighbour(), leaf_nw_sw);

// testing se_nw neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->west_neighbour(), leaf_sw_ne);

// testing sw_sw neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->west_neighbour(), nullptr);

// testing se_se neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->west_neighbour(), leaf_se_sw);

// test, that only it gives the neighbour only on one level
        ASSERT_EQ(leaf_nw->west_neighbour(), nullptr);
        ASSERT_EQ(leaf_ne->west_neighbour(), leaf_nw);
        ASSERT_EQ(leaf_sw->west_neighbour(), nullptr);
        ASSERT_EQ(leaf_se->west_neighbour(), leaf_sw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[sw].west_neighbour(), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture_H, TestNorthComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->north_comparison());

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->north_comparison());

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_FALSE(test_child->north_comparison());

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->north_comparison());

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->north_comparison());

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->north_comparison());

// test, on top level leaves
        ASSERT_FALSE(leaf_nw->north_comparison());
        ASSERT_FALSE(leaf_ne->north_comparison());
        ASSERT_FALSE(leaf_sw->north_comparison());
        ASSERT_FALSE(leaf_se->north_comparison());
    }

    TEST_F(NeighbourLeafTestFixture, TestEastComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->east_comparison());

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->east_comparison());

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->east_comparison());

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_FALSE(test_child->east_comparison());

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->east_comparison());

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->east_comparison());

// test, on top level leaves
        ASSERT_TRUE(leaf_nw->east_comparison());
        ASSERT_FALSE(leaf_ne->east_comparison());
        ASSERT_TRUE(leaf_sw->east_comparison());
        ASSERT_FALSE(leaf_se->east_comparison());
    }

    TEST_F(NeighbourLeafTestFixture_H, TestSouthComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->south_comparison());

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->south_comparison());

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->south_comparison());

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_FALSE(test_child->south_comparison());

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->south_comparison());

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->south_comparison());

// test, on top level leafs
        ASSERT_FALSE(leaf_nw->south_comparison());
        ASSERT_FALSE(leaf_ne->south_comparison());
        ASSERT_FALSE(leaf_sw->south_comparison());
        ASSERT_FALSE(leaf_se->south_comparison());
    }

    TEST_F(NeighbourLeafTestFixture, TestWestComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->west_comparison());

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->west_comparison());

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_FALSE(test_child->west_comparison());

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->west_comparison());

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->west_comparison());

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->west_comparison());

// test, that only it gives the neighbour only on one level
        ASSERT_FALSE(leaf_nw->west_comparison());
        ASSERT_TRUE(leaf_ne->west_comparison());
        ASSERT_FALSE(leaf_sw->west_comparison());
        ASSERT_TRUE(leaf_se->west_comparison());
    }

    TEST_F(NeighbourLeafTestFixture, TestSplitLeafDecision) {
// testing nw_nw split function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->should_be_split());

// testing ne_ne split function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->should_be_split());

// testing nw_se neighbour function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->should_be_split());

// testing se_nw neighbour function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->should_be_split());

// testing sw_sw neighbour function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->should_be_split());

// testing se_se neighbour function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->should_be_split());

// test, on top level leafs
        ASSERT_TRUE(leaf_nw->should_be_split());
        ASSERT_TRUE(leaf_ne->should_be_split());
        ASSERT_TRUE(leaf_sw->should_be_split());
        ASSERT_TRUE(leaf_se->should_be_split());
    }

    TEST_F(NeighbourLeafTestFixture, testBalanceTree) {
        test_leaf.balance_tree();
        // test that the root leaf and its children are not further split
        ASSERT_EQ(test_leaf.children.size(), 4);
        ASSERT_EQ(leaf_nw->children.size(), 4);
        ASSERT_EQ(leaf_ne->children.size(), 4);
        ASSERT_EQ(leaf_sw->children.size(), 4);
        ASSERT_EQ(leaf_se->children.size(), 4);

        // test, that the sub leafs which should not be split are not split
        ASSERT_EQ(leaf_nw_nw->children.size(), 0);
        ASSERT_EQ(leaf_ne_ne->children.size(), 0);
        ASSERT_EQ(leaf_sw_sw->children.size(), 0);
        ASSERT_EQ(leaf_se_se->children.size(), 0);

        // test, that leafs are correctly split
        ASSERT_EQ(leaf_nw_se->children.size(), 4);
        ASSERT_EQ(leaf_se_nw->children.size(), 4);
    }

    TEST_F(NeighbourLeafTestFixture, testBalanceTreeWithForceOption) {
        test_leaf.balance_tree(true);
        // test that the root leaf and its children are not further split
        ASSERT_EQ(test_leaf.children.size(), 4);
        ASSERT_EQ(leaf_nw->children.size(), 4);
        ASSERT_EQ(leaf_ne->children.size(), 4);
        ASSERT_EQ(leaf_sw->children.size(), 4);
        ASSERT_EQ(leaf_se->children.size(), 4);

        // test, that sub leafs are split
        ASSERT_EQ(leaf_nw_nw->children.size(), 4);
        ASSERT_EQ(leaf_ne_ne->children.size(), 4);
        ASSERT_EQ(leaf_sw_sw->children.size(), 4);
        ASSERT_EQ(leaf_se_se->children.size(), 4);
        ASSERT_EQ(leaf_nw_se->children.size(), 4);
        ASSERT_EQ(leaf_se_nw->children.size(), 4);
    }

} // dp