//
// Created by Keiwan Jamaly on 17.10.22.
//
#include <boost/test/unit_test.hpp>
#include "Leaf.h"
#include "Types_Leaf.h"
#include "TestData.h"

#include <set>

namespace dp {

    using std::shared_ptr, std::make_shared;

    class NeighbourLeafTestFixture {
        // I'm going to test the neighbours of the following points
        // test points      test labels
        // x, 0, 0, x       nw_nw, nw_ne, ne_nw, ne_ne
        // 0, x, 0, 0       nw_sw, nw_se, ne_sw, ne_se
        // 0, 0, x, 0       sw_nw, sw_ne, se_nw, se_ne
        // x, 0, 0, x       sw_sw, sw_se, se_sw, se_se

        // testing values outside the boundary should result in a null-pointer

    public:
        NeighbourLeafTestFixture() {
            x = 0.0;
            y = 0.0;
            box_size = 1.0;
            config = make_shared<Empty_Config>(Empty_Config());
            test_leaf = make_shared<CurrLeaf>(x, y, box_size, box_size, split_decision, config);

            test_leaf->attach_leaves();
            leaf_nw = test_leaf->children[nw];
            leaf_nw->attach_leaves();
            leaf_ne = test_leaf->children[ne];
            leaf_ne->attach_leaves();
            leaf_sw = test_leaf->children[sw];
            leaf_sw->attach_leaves();
            leaf_se = test_leaf->children[se];
            leaf_se->attach_leaves();

            leaf_nw_nw = leaf_nw->children[nw];
            leaf_nw_ne = leaf_nw->children[ne];
            leaf_nw_sw = leaf_nw->children[sw];
            leaf_nw_se = leaf_nw->children[se];

            leaf_ne_nw = leaf_ne->children[nw];
            leaf_ne_ne = leaf_ne->children[ne];
            leaf_ne_sw = leaf_ne->children[sw];
            leaf_ne_se = leaf_ne->children[se];

            leaf_sw_nw = leaf_sw->children[nw];
            leaf_sw_ne = leaf_sw->children[ne];
            leaf_sw_sw = leaf_sw->children[sw];
            leaf_sw_se = leaf_sw->children[se];

            leaf_se_nw = leaf_se->children[nw];
            leaf_se_ne = leaf_se->children[ne];
            leaf_se_sw = leaf_se->children[sw];
            leaf_se_se = leaf_se->children[se];

            leaf_nw_se->attach_leaves();
        }

        shared_ptr<CurrLeaf> test_leaf;
        shared_ptr<Empty_Config> config;
        shared_ptr<CurrLeaf> test_child;
        double x{}, y{}, box_size{};
        shared_ptr<CurrLeaf> leaf_nw_nw, leaf_nw_ne, leaf_nw_sw, leaf_nw_se, leaf_ne_nw, leaf_ne_ne, leaf_ne_sw, leaf_ne_se, leaf_sw_nw, leaf_sw_ne, leaf_sw_sw, leaf_sw_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se;
        shared_ptr<CurrLeaf> leaf_nw, leaf_ne, leaf_sw, leaf_se;
    };


    // test get_all_leafs
    BOOST_FIXTURE_TEST_CASE(getAllLeafes, NeighbourLeafTestFixture) {
        std::vector<shared_ptr<CurrLeaf>> all_leafs = test_leaf->get_all_leafs();
        std::set < shared_ptr<CurrLeaf> > all_leafs_set(all_leafs.begin(), all_leafs.end());
        // reference set
        std::set < shared_ptr<CurrLeaf> >
        reference_set(
                {test_leaf, leaf_nw_nw, leaf_nw_ne, leaf_nw_sw, leaf_nw_se,
                 leaf_ne_nw,
                 leaf_ne_ne, leaf_ne_sw, leaf_ne_se, leaf_sw_nw, leaf_sw_ne, leaf_sw_sw,
                 leaf_sw_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se, leaf_nw,
                 leaf_ne, leaf_sw, leaf_se, leaf_nw_se->children[nw], leaf_nw_se->children[ne],
                 leaf_nw_se->children[sw], leaf_nw_se->children[se]
                });

        // no doubled elements
        BOOST_CHECK_EQUAL(all_leafs_set.size(), all_leafs.size());
        // all elements are included
        BOOST_TEST(all_leafs_set == reference_set);

        // check, that it also work on a sub_tree and, that it does include only the leafs in the subtree
        std::vector<shared_ptr<CurrLeaf>> sub_leafs = leaf_se->get_all_leafs();
        std::set<shared_ptr<CurrLeaf>> sub_leafs_set(sub_leafs.begin(), sub_leafs.end());
        std::set<shared_ptr<CurrLeaf>> sub_reference_set({leaf_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se});

        // no doubled elements
        BOOST_CHECK_EQUAL(sub_leafs.size(), sub_leafs_set.size());
        // all elements are included
        BOOST_TEST(sub_leafs_set == sub_reference_set);
    }

    BOOST_FIXTURE_TEST_CASE(GetDepthFunction, NeighbourLeafTestFixture) {
        BOOST_CHECK_EQUAL(test_leaf->get_depth(), 0);
        BOOST_CHECK_EQUAL(leaf_nw->get_depth(), 1);
        BOOST_CHECK_EQUAL(leaf_ne->get_depth(), 1);
        BOOST_CHECK_EQUAL(leaf_sw->get_depth(), 1);
        BOOST_CHECK_EQUAL(leaf_se->get_depth(), 1);

        BOOST_CHECK_EQUAL(leaf_nw_nw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_nw_ne->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_nw_sw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_nw_se->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_ne_nw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_ne_ne->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_ne_sw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_ne_se->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_sw_nw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_sw_ne->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_sw_sw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_sw_se->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_se_nw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_se_ne->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_se_sw->get_depth(), 2);
        BOOST_CHECK_EQUAL(leaf_se_se->get_depth(), 2);

        // leaf_nw_se
        BOOST_CHECK_EQUAL(leaf_nw_se->children[nw]->get_depth(), 3);
        BOOST_CHECK_EQUAL(leaf_nw_se->children[ne]->get_depth(), 3);
        BOOST_CHECK_EQUAL(leaf_nw_se->children[sw]->get_depth(), 3);
        BOOST_CHECK_EQUAL(leaf_nw_se->children[se]->get_depth(), 3);
    }

    BOOST_FIXTURE_TEST_CASE(testNorthNeighbourFunction, NeighbourLeafTestFixture) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(north), nullptr);

        // testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(north), nullptr);

        // testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(north), leaf_nw_ne);

        // testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(north), leaf_ne_sw);

        // testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(north), leaf_sw_nw);

        // testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(north), leaf_se_ne);

        // test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_neighbour(north), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->get_neighbour(north), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->get_neighbour(north), leaf_nw);
        BOOST_CHECK_EQUAL(leaf_se->get_neighbour(north), leaf_ne);

        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[nw]->get_neighbour(north), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testEastNeighbourFunction, NeighbourLeafTestFixture) {
// testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(east), leaf_nw_ne);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(east), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(east), leaf_ne_sw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(east), leaf_se_ne);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(east), leaf_sw_se);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(east), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_neighbour(east), leaf_ne);
        BOOST_CHECK_EQUAL(leaf_ne->get_neighbour(east), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->get_neighbour(east), leaf_se);
        BOOST_CHECK_EQUAL(leaf_se->get_neighbour(east), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[ne]->get_neighbour(east), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testSouthNeighbourFunction, NeighbourLeafTestFixture) {
// testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(south), leaf_nw_sw);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(south), leaf_ne_se);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(south), leaf_sw_ne);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(south), leaf_se_sw);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(south), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(south), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_neighbour(south), leaf_sw);
        BOOST_CHECK_EQUAL(leaf_ne->get_neighbour(south), leaf_se);
        BOOST_CHECK_EQUAL(leaf_sw->get_neighbour(south), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->get_neighbour(south), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[se]->get_neighbour(south), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testWestNeighbourFunction, NeighbourLeafTestFixture) {
// testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(west), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(west), leaf_ne_nw);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(west), leaf_nw_sw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(west), leaf_sw_ne);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(west), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_neighbour(west), leaf_se_sw);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_neighbour(west), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->get_neighbour(west), leaf_nw);
        BOOST_CHECK_EQUAL(leaf_sw->get_neighbour(west), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->get_neighbour(west), leaf_sw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[sw]->get_neighbour(west), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testNorthWestNeighbour, NeighbourLeafTestFixture) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(nw), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(nw), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(nw), leaf_nw_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(nw), leaf_nw_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(nw), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(nw), leaf_se_nw);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_diagonal_neighbour(nw), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->get_diagonal_neighbour(nw), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->get_diagonal_neighbour(nw), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->get_diagonal_neighbour(nw), leaf_nw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[sw]->get_diagonal_neighbour(nw), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testNorthEastNeighbour, NeighbourLeafTestFixture) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(ne), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(ne), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(ne), leaf_ne_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(ne), leaf_ne_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(ne), leaf_sw_ne);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(ne), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_diagonal_neighbour(ne), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->get_diagonal_neighbour(ne), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->get_diagonal_neighbour(ne), leaf_ne);
        BOOST_CHECK_EQUAL(leaf_se->get_diagonal_neighbour(ne), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[ne]->get_diagonal_neighbour(ne), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testSouthEastNeighbour, NeighbourLeafTestFixture) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(se), leaf_nw_se);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(se), nullptr);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(se), leaf_se_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(se), leaf_se_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(se), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(se), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_diagonal_neighbour(se), leaf_se);
        BOOST_CHECK_EQUAL(leaf_ne->get_diagonal_neighbour(se), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->get_diagonal_neighbour(se), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->get_diagonal_neighbour(se), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[sw]->get_diagonal_neighbour(se), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testSouthWestNeighbour, NeighbourLeafTestFixture) {
        // testing nw_nw get_diagonal_neighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(sw), nullptr);

// testing ne_ne get_diagonal_neighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(sw), leaf_ne_sw);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(sw), leaf_sw_nw);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(sw), leaf_sw_se);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(sw), nullptr);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->get_diagonal_neighbour(sw), nullptr);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->get_diagonal_neighbour(sw), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->get_diagonal_neighbour(sw), leaf_sw);
        BOOST_CHECK_EQUAL(leaf_sw->get_diagonal_neighbour(sw), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->get_diagonal_neighbour(sw), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->children[sw]->get_diagonal_neighbour(sw), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(TestNorthComparison, NeighbourLeafTestFixture) {
        config->mode = 1;
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(north) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(north) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(north) == false);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(north) == true);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(north) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(north) == false);

// test, on top level leaves
        BOOST_TEST(leaf_nw->comparison(north) == false);
        BOOST_TEST(leaf_ne->comparison(north) == false);
        BOOST_TEST(leaf_sw->comparison(north) == true);
        BOOST_TEST(leaf_se->comparison(north) == true);
    }

    BOOST_FIXTURE_TEST_CASE(TestEastComparison, NeighbourLeafTestFixture) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(east) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(east) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(east) == true);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(east) == false);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(east) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(east) == false);

// test, on top level leaves
        BOOST_TEST(leaf_nw->comparison(east) == true);
        BOOST_TEST(leaf_ne->comparison(east) == false);
        BOOST_TEST(leaf_sw->comparison(east) == true);
        BOOST_TEST(leaf_se->comparison(east) == false);
    }

    BOOST_FIXTURE_TEST_CASE(TestSouthComparison, NeighbourLeafTestFixture) {
        config->mode = 1;
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(south) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(south) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(south) == true);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(south) == false);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(south) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(south) == false);

// test, on top level leafs
        BOOST_TEST(leaf_nw->comparison(south) == true);
        BOOST_TEST(leaf_ne->comparison(south) == true);
        BOOST_TEST(leaf_sw->comparison(south) == false);
        BOOST_TEST(leaf_se->comparison(south) == false);
    }

    BOOST_FIXTURE_TEST_CASE(TestWestComparison, NeighbourLeafTestFixture) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(west) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(west) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(west) == false);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(west) == true);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(west) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(west) == false);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_TEST(leaf_nw->comparison(west) == false);
        BOOST_TEST(leaf_ne->comparison(west) == true);
        BOOST_TEST(leaf_sw->comparison(west) == false);
        BOOST_TEST(leaf_se->comparison(west) == true);
    }

    BOOST_FIXTURE_TEST_CASE(TestNorthWestComparison, NeighbourLeafTestFixture) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(nw) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(nw) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(nw) == false);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(nw) == true);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(nw) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(nw) == false);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_TEST(leaf_nw->comparison(nw) == false);
        BOOST_TEST(leaf_ne->comparison(nw) == false);
        BOOST_TEST(leaf_sw->comparison(nw) == false);
        BOOST_TEST(leaf_se->comparison(nw) == true);
    }

    BOOST_FIXTURE_TEST_CASE(TestNorthEastComparison, NeighbourLeafTestFixture) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(ne) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(ne) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(ne) == true);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(ne) == false);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(ne) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(ne) == false);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_TEST(leaf_nw->comparison(ne) == false);
        BOOST_TEST(leaf_ne->comparison(ne) == false);
        BOOST_TEST(leaf_sw->comparison(ne) == true);
        BOOST_TEST(leaf_se->comparison(ne) == false);
    }

    BOOST_FIXTURE_TEST_CASE(TestSouthEastComparison, NeighbourLeafTestFixture) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(se) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(se) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(se) == true);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(se) == false);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(se) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(se) == false);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_TEST(leaf_nw->comparison(se) == true);
        BOOST_TEST(leaf_ne->comparison(se) == false);
        BOOST_TEST(leaf_sw->comparison(se) == false);
        BOOST_TEST(leaf_se->comparison(se) == false);
    }

    BOOST_FIXTURE_TEST_CASE(TestSouthWestComparison, NeighbourLeafTestFixture) {
// testing nw_nw comparison function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->comparison(sw) == false);

// testing ne_ne comparison function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->comparison(sw) == false);

// testing nw_se comparison function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->comparison(sw) == false);

// testing se_nw comparison function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->comparison(sw) == true);

// testing sw_sw comparison function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->comparison(sw) == false);

// testing se_se comparison function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->comparison(sw) == false);

// test, that only it gives the get_diagonal_neighbour only on one level
        BOOST_TEST(leaf_nw->comparison(sw) == false);
        BOOST_TEST(leaf_ne->comparison(sw) == true);
        BOOST_TEST(leaf_sw->comparison(sw) == false);
        BOOST_TEST(leaf_se->comparison(sw) == false);
    }

    BOOST_FIXTURE_TEST_CASE(TestSplitLeafDecision, NeighbourLeafTestFixture) {
// testing nw_nw split function
        test_child = leaf_nw_nw;
        BOOST_TEST(test_child->should_be_split() == false);

// testing ne_ne split function
        test_child = leaf_ne_ne;
        BOOST_TEST(test_child->should_be_split() == false);

// testing nw_se get_diagonal_neighbour function
        test_child = leaf_nw_se;
        BOOST_TEST(test_child->should_be_split() == true);

// testing se_nw get_diagonal_neighbour function
        test_child = leaf_se_nw;
        BOOST_TEST(test_child->should_be_split() == true);

// testing sw_sw get_diagonal_neighbour function
        test_child = leaf_sw_sw;
        BOOST_TEST(test_child->should_be_split() == false);

// testing se_se get_diagonal_neighbour function
        test_child = leaf_se_se;
        BOOST_TEST(test_child->should_be_split() == false);

// test, on top level leafs
        BOOST_TEST(leaf_nw->should_be_split() == true);
        BOOST_TEST(leaf_ne->should_be_split() == true);
        BOOST_TEST(leaf_sw->should_be_split() == true);
        BOOST_TEST(leaf_se->should_be_split() == true);
    }

    BOOST_FIXTURE_TEST_CASE(testBalanceTree, NeighbourLeafTestFixture) {
        test_leaf->balance_tree();
        // test that the root leaf and its children are not further split
        BOOST_CHECK_EQUAL(test_leaf->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_nw->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_ne->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_sw->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_se->children.size(), 4);

        // test, that the sub leafs which should not be split are not split
        BOOST_CHECK_EQUAL(leaf_nw_nw->children.size(), 0);
        BOOST_CHECK_EQUAL(leaf_ne_ne->children.size(), 0);
        BOOST_CHECK_EQUAL(leaf_sw_sw->children.size(), 0);
        BOOST_CHECK_EQUAL(leaf_se_se->children.size(), 0);

        // test, that leafs are correctly split
        BOOST_CHECK_EQUAL(leaf_nw_se->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_se_nw->children.size(), 4);
    }

    BOOST_FIXTURE_TEST_CASE(testBalanceTreeWithForceOption, NeighbourLeafTestFixture) {
        test_leaf->balance_tree(true);
        // test that the root leaf and its children are not further split
        BOOST_CHECK_EQUAL(test_leaf->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_nw->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_ne->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_sw->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_se->children.size(), 4);

        // test, that sub leafs are split
        BOOST_CHECK_EQUAL(leaf_nw_nw->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_ne_ne->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_sw_sw->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_se_se->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_nw_se->children.size(), 4);
        BOOST_CHECK_EQUAL(leaf_se_nw->children.size(), 4);
    }

} // dp