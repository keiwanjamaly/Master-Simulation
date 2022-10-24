//
// Created by Keiwan Jamaly on 17.10.22.
//
#include "gtest/gtest.h"
#include "Leaf.h"
#include "Types.h"
#include "TestData.h"

#include <set>

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


    // test get_all_leafs
    TEST_F(NeighbourLeafTestFixture, getAllLeafes) {
        std::vector<Leaf<Data> *> all_leafs = test_leaf.get_all_leafs();
        std::set<Leaf<Data> *> all_leafs_set(all_leafs.begin(), all_leafs.end());
        // reference set
        std::set<Leaf<Data> *> reference_set({&test_leaf, leaf_nw_nw, leaf_nw_ne, leaf_nw_sw, leaf_nw_se, leaf_ne_nw,
                                              leaf_ne_ne, leaf_ne_sw, leaf_ne_se, leaf_sw_nw, leaf_sw_ne, leaf_sw_sw,
                                              leaf_sw_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se, leaf_nw,
                                              leaf_ne, leaf_sw, leaf_se, &(leaf_nw_se->children[nw]),
                                              &(leaf_nw_se->children[ne]), &(leaf_nw_se->children[sw]),
                                              &(leaf_nw_se->children[se])});

        // no doubled elements
        ASSERT_EQ(all_leafs_set.size(), all_leafs.size());
        // all elements are included
        ASSERT_EQ(all_leafs_set, reference_set);

        // check, that it also work on a sub_tree and, that it does include only the leafs in the subtree
        std::vector<Leaf<Data> *> sub_leafs = leaf_se->get_all_leafs();
        std::set<Leaf<Data> *> sub_leafs_set(sub_leafs.begin(), sub_leafs.end());
        std::set<Leaf<Data> *> sub_reference_set({leaf_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se});

        // no doubled elements
        ASSERT_EQ(sub_leafs.size(), sub_leafs_set.size());
        // all elements are included
        ASSERT_EQ(sub_leafs_set, sub_reference_set);
    }

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
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_neighbour(north), nullptr);

        // testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_neighbour(north), nullptr);

        // testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_neighbour(north), leaf_nw_ne);

        // testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_neighbour(north), leaf_ne_sw);

        // testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_neighbour(north), leaf_sw_nw);

        // testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_neighbour(north), leaf_se_ne);

        // test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_neighbour(north), nullptr);
        ASSERT_EQ(leaf_ne->get_neighbour(north), nullptr);
        ASSERT_EQ(leaf_sw->get_neighbour(north), leaf_nw);
        ASSERT_EQ(leaf_se->get_neighbour(north), leaf_ne);

        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[nw].get_neighbour(north), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testEastNeighbourFunction) {
// testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_neighbour(east), leaf_nw_ne);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_neighbour(east), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_neighbour(east), leaf_ne_sw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_neighbour(east), leaf_se_ne);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_neighbour(east), leaf_sw_se);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_neighbour(east), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_neighbour(east), leaf_ne);
        ASSERT_EQ(leaf_ne->get_neighbour(east), nullptr);
        ASSERT_EQ(leaf_sw->get_neighbour(east), leaf_se);
        ASSERT_EQ(leaf_se->get_neighbour(east), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[ne].get_neighbour(east), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testSouthNeighbourFunction) {
// testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_neighbour(south), leaf_nw_sw);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_neighbour(south), leaf_ne_se);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_neighbour(south), leaf_sw_ne);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_neighbour(south), leaf_se_sw);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_neighbour(south), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_neighbour(south), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_neighbour(south), leaf_sw);
        ASSERT_EQ(leaf_ne->get_neighbour(south), leaf_se);
        ASSERT_EQ(leaf_sw->get_neighbour(south), nullptr);
        ASSERT_EQ(leaf_se->get_neighbour(south), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[se].get_neighbour(south), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testWestNeighbourFunction) {
// testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_neighbour(west), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_neighbour(west), leaf_ne_nw);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_neighbour(west), leaf_nw_sw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_neighbour(west), leaf_sw_ne);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_neighbour(west), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_neighbour(west), leaf_se_sw);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_neighbour(west), nullptr);
        ASSERT_EQ(leaf_ne->get_neighbour(west), leaf_nw);
        ASSERT_EQ(leaf_sw->get_neighbour(west), nullptr);
        ASSERT_EQ(leaf_se->get_neighbour(west), leaf_sw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[sw].get_neighbour(west), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testNorthWestNeighbour) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(nw), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_diagonal_neighbour(nw), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(nw), leaf_nw_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(nw), leaf_nw_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(nw), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(nw), leaf_se_nw);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_diagonal_neighbour(nw), nullptr);
        ASSERT_EQ(leaf_ne->get_diagonal_neighbour(nw), nullptr);
        ASSERT_EQ(leaf_sw->get_diagonal_neighbour(nw), nullptr);
        ASSERT_EQ(leaf_se->get_diagonal_neighbour(nw), leaf_nw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[sw].get_diagonal_neighbour(nw), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testNorthEastNeighbour) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(ne), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_diagonal_neighbour(ne), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(ne), leaf_ne_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(ne), leaf_ne_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(ne), leaf_sw_ne);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(ne), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_diagonal_neighbour(ne), nullptr);
        ASSERT_EQ(leaf_ne->get_diagonal_neighbour(ne), nullptr);
        ASSERT_EQ(leaf_sw->get_diagonal_neighbour(ne), leaf_ne);
        ASSERT_EQ(leaf_se->get_diagonal_neighbour(ne), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[ne].get_diagonal_neighbour(ne), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testSouthEastNeighbour) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(se), leaf_nw_se);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_diagonal_neighbour(se), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(se), leaf_se_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(se), leaf_se_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(se), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(se), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_diagonal_neighbour(se), leaf_se);
        ASSERT_EQ(leaf_ne->get_diagonal_neighbour(se), nullptr);
        ASSERT_EQ(leaf_sw->get_diagonal_neighbour(se), nullptr);
        ASSERT_EQ(leaf_se->get_diagonal_neighbour(se), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[sw].get_diagonal_neighbour(se), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture, testSouthWestNeighbour) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(sw), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        ASSERT_EQ(test_child->get_diagonal_neighbour(sw), leaf_ne_sw);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(sw), leaf_sw_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(sw), leaf_sw_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_EQ(test_child->get_diagonal_neighbour(sw), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        ASSERT_EQ(test_child->get_diagonal_neighbour(sw), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_EQ(leaf_nw->get_diagonal_neighbour(sw), nullptr);
        ASSERT_EQ(leaf_ne->get_diagonal_neighbour(sw), leaf_sw);
        ASSERT_EQ(leaf_sw->get_diagonal_neighbour(sw), nullptr);
        ASSERT_EQ(leaf_se->get_diagonal_neighbour(sw), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        ASSERT_EQ(leaf_nw_se->children[sw].get_diagonal_neighbour(sw), nullptr);
    }

    TEST_F(NeighbourLeafTestFixture_H, TestNorthComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(north));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(north));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_FALSE(test_child->comparison(north));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->comparison(north));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(north));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(north));

// test, on top level leaves
        ASSERT_FALSE(leaf_nw->comparison(north));
        ASSERT_FALSE(leaf_ne->comparison(north));
        ASSERT_TRUE(leaf_sw->comparison(north));
        ASSERT_TRUE(leaf_se->comparison(north));
    }

    TEST_F(NeighbourLeafTestFixture, TestEastComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(east));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(east));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->comparison(east));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_FALSE(test_child->comparison(east));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(east));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(east));

// test, on top level leaves
        ASSERT_TRUE(leaf_nw->comparison(east));
        ASSERT_FALSE(leaf_ne->comparison(east));
        ASSERT_TRUE(leaf_sw->comparison(east));
        ASSERT_FALSE(leaf_se->comparison(east));
    }

    TEST_F(NeighbourLeafTestFixture_H, TestSouthComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(south));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(south));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->comparison(south));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_FALSE(test_child->comparison(south));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(south));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(south));

// test, on top level leafs
        ASSERT_TRUE(leaf_nw->comparison(south));
        ASSERT_TRUE(leaf_ne->comparison(south));
        ASSERT_FALSE(leaf_sw->comparison(south));
        ASSERT_FALSE(leaf_se->comparison(south));
    }

    TEST_F(NeighbourLeafTestFixture, TestWestComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(west));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(west));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_FALSE(test_child->comparison(west));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->comparison(west));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(west));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(west));

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_FALSE(leaf_nw->comparison(west));
        ASSERT_TRUE(leaf_ne->comparison(west));
        ASSERT_FALSE(leaf_sw->comparison(west));
        ASSERT_TRUE(leaf_se->comparison(west));
    }

    TEST_F(NeighbourLeafTestFixture, TestNorthWestComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(nw));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(nw));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_FALSE(test_child->comparison(nw));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->comparison(nw));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(nw));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(nw));

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_FALSE(leaf_nw->comparison(nw));
        ASSERT_FALSE(leaf_ne->comparison(nw));
        ASSERT_FALSE(leaf_sw->comparison(nw));
        ASSERT_TRUE(leaf_se->comparison(nw));
    }

    TEST_F(NeighbourLeafTestFixture, TestNorthEastComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(ne));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(ne));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->comparison(ne));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_FALSE(test_child->comparison(ne));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(ne));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(ne));

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_FALSE(leaf_nw->comparison(ne));
        ASSERT_FALSE(leaf_ne->comparison(ne));
        ASSERT_TRUE(leaf_sw->comparison(ne));
        ASSERT_FALSE(leaf_se->comparison(ne));
    }

    TEST_F(NeighbourLeafTestFixture, TestSouthEastComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(se));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(se));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->comparison(se));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_FALSE(test_child->comparison(se));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(se));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(se));

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_TRUE(leaf_nw->comparison(se));
        ASSERT_FALSE(leaf_ne->comparison(se));
        ASSERT_FALSE(leaf_sw->comparison(se));
        ASSERT_FALSE(leaf_se->comparison(se));
    }

    TEST_F(NeighbourLeafTestFixture, TestSouthWestComparison) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->comparison(sw));

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->comparison(sw));

// testing nw_se comparison function
        test_child = leaf_nw_se;
        ASSERT_FALSE(test_child->comparison(sw));

// testing se_nw comparison function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->comparison(sw));

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->comparison(sw));

// testing se_se comparison function
        test_child = leaf_se_se;
        ASSERT_FALSE(test_child->comparison(sw));

// test, that only it gives the get_diagonal_neighbour only on one level
        ASSERT_FALSE(leaf_nw->comparison(sw));
        ASSERT_TRUE(leaf_ne->comparison(sw));
        ASSERT_FALSE(leaf_sw->comparison(sw));
        ASSERT_FALSE(leaf_se->comparison(sw));
    }

    TEST_F(NeighbourLeafTestFixture, TestSplitLeafDecision) {
// testing nw_nw split function
        test_child = leaf_nw_nw;
        ASSERT_FALSE(test_child->should_be_split());

// testing ne_ne split function
        test_child = leaf_ne_ne;
        ASSERT_FALSE(test_child->should_be_split());

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        ASSERT_TRUE(test_child->should_be_split());

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        ASSERT_TRUE(test_child->should_be_split());

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        ASSERT_FALSE(test_child->should_be_split());

// testing se_se get_diagonal_neighbour function
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