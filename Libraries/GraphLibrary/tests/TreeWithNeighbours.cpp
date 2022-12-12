#include <boost/test/unit_test.hpp>

#include "TreeWithNeighbours.h"
#include "GraphLibrary_Types.h"

namespace gl {

    class TreeWithNeighbourTestFixture {
        // I'm going to test the neighbours of the following points
        // test points      test labels
        // x, 0, 0, x       nw_nw, nw_ne, ne_nw, ne_ne
        // 0, x, 0, 0       nw_sw, nw_se, ne_sw, ne_se
        // 0, 0, x, 0       sw_nw, sw_ne, se_nw, se_ne
        // x, 0, 0, x       sw_sw, sw_se, se_sw, se_se

        // testing values outside the boundary should result in a null-pointer

    public:
        TreeWithNeighbourTestFixture() {
            test_leaf = make_shared<TreeWithNeighbours>();

            test_leaf->attachLeaves();
            leaf_nw = test_leaf->getChild(nw);
            leaf_nw->attachLeaves();
            leaf_ne = test_leaf->getChild(ne);
            leaf_ne->attachLeaves();
            leaf_sw = test_leaf->getChild(sw);
            leaf_sw->attachLeaves();
            leaf_se = test_leaf->getChild(se);
            leaf_se->attachLeaves();

            leaf_nw_nw = leaf_nw->getChild(nw);
            leaf_nw_ne = leaf_nw->getChild(ne);
            leaf_nw_sw = leaf_nw->getChild(sw);
            leaf_nw_se = leaf_nw->getChild(se);

            leaf_ne_nw = leaf_ne->getChild(nw);
            leaf_ne_ne = leaf_ne->getChild(ne);
            leaf_ne_sw = leaf_ne->getChild(sw);
            leaf_ne_se = leaf_ne->getChild(se);

            leaf_sw_nw = leaf_sw->getChild(nw);
            leaf_sw_ne = leaf_sw->getChild(ne);
            leaf_sw_sw = leaf_sw->getChild(sw);
            leaf_sw_se = leaf_sw->getChild(se);

            leaf_se_nw = leaf_se->getChild(nw);
            leaf_se_ne = leaf_se->getChild(ne);
            leaf_se_sw = leaf_se->getChild(sw);
            leaf_se_se = leaf_se->getChild(se);

            leaf_nw_se->attachLeaves();
        }

        shared_ptr<TreeWithNeighbours> test_leaf;
        shared_ptr<TreeWithNeighbours> test_child;
        shared_ptr<TreeWithNeighbours> leaf_nw_nw, leaf_nw_ne, leaf_nw_sw, leaf_nw_se, leaf_ne_nw, leaf_ne_ne, leaf_ne_sw, leaf_ne_se, leaf_sw_nw, leaf_sw_ne, leaf_sw_sw, leaf_sw_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se;
        shared_ptr<TreeWithNeighbours> leaf_nw, leaf_ne, leaf_sw, leaf_se;
    };

    BOOST_FIXTURE_TEST_CASE(testNorthNeighbourFunction, TreeWithNeighbourTestFixture) {
        // testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(north), nullptr);

        // testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(north), nullptr);

        // testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(north), leaf_nw_ne);

        // testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(north), leaf_ne_sw);

        // testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(north), leaf_sw_nw);

        // testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(north), leaf_se_ne);

        // test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getNeighbour(north), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->getNeighbour(north), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->getNeighbour(north), leaf_nw);
        BOOST_CHECK_EQUAL(leaf_se->getNeighbour(north), leaf_ne);

        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(nw)->getNeighbour(north), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testEastNeighbourFunction, TreeWithNeighbourTestFixture) {
// testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(east), leaf_nw_ne);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(east), nullptr);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(east), leaf_ne_sw);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(east), leaf_se_ne);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(east), leaf_sw_se);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(east), nullptr);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getNeighbour(east), leaf_ne);
        BOOST_CHECK_EQUAL(leaf_ne->getNeighbour(east), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->getNeighbour(east), leaf_se);
        BOOST_CHECK_EQUAL(leaf_se->getNeighbour(east), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(ne)->getNeighbour(east), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testSouthNeighbourFunction, TreeWithNeighbourTestFixture) {
// testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(south), leaf_nw_sw);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(south), leaf_ne_se);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(south), leaf_sw_ne);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(south), leaf_se_sw);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(south), nullptr);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(south), nullptr);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getNeighbour(south), leaf_sw);
        BOOST_CHECK_EQUAL(leaf_ne->getNeighbour(south), leaf_se);
        BOOST_CHECK_EQUAL(leaf_sw->getNeighbour(south), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->getNeighbour(south), nullptr);

        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(se)->getNeighbour(south), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testWestNeighbourFunction, TreeWithNeighbourTestFixture) {
// testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(west), nullptr);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(west), leaf_ne_nw);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(west), leaf_nw_sw);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(west), leaf_sw_ne);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(west), nullptr);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getNeighbour(west), leaf_se_sw);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getNeighbour(west), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->getNeighbour(west), leaf_nw);
        BOOST_CHECK_EQUAL(leaf_sw->getNeighbour(west), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->getNeighbour(west), leaf_sw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(sw)->getNeighbour(west), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testNorthWestNeighbour, TreeWithNeighbourTestFixture) {
        // testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(nw), nullptr);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(nw), nullptr);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(nw), leaf_nw_nw);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(nw), leaf_nw_se);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(nw), nullptr);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(nw), leaf_se_nw);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getDiagonalNeighbour(nw), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->getDiagonalNeighbour(nw), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->getDiagonalNeighbour(nw), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->getDiagonalNeighbour(nw), leaf_nw);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(sw)->getDiagonalNeighbour(nw), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testNorthEastNeighbour, TreeWithNeighbourTestFixture) {
        // testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(ne), nullptr);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(ne), nullptr);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(ne), leaf_ne_nw);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(ne), leaf_ne_se);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(ne), leaf_sw_ne);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(ne), nullptr);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getDiagonalNeighbour(ne), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->getDiagonalNeighbour(ne), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->getDiagonalNeighbour(ne), leaf_ne);
        BOOST_CHECK_EQUAL(leaf_se->getDiagonalNeighbour(ne), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(ne)->getDiagonalNeighbour(ne), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testSouthEastNeighbour, TreeWithNeighbourTestFixture) {
        // testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(se), leaf_nw_se);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(se), nullptr);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(se), leaf_se_nw);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(se), leaf_se_se);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(se), nullptr);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(se), nullptr);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getDiagonalNeighbour(se), leaf_se);
        BOOST_CHECK_EQUAL(leaf_ne->getDiagonalNeighbour(se), nullptr);
        BOOST_CHECK_EQUAL(leaf_sw->getDiagonalNeighbour(se), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->getDiagonalNeighbour(se), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(sw)->getDiagonalNeighbour(se), nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testSouthWestNeighbour, TreeWithNeighbourTestFixture) {
        // testing nw_nw getDiagonalNeighbour function
        test_child = leaf_nw_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(sw), nullptr);

// testing ne_ne getDiagonalNeighbour function
        test_child = leaf_ne_ne;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(sw), leaf_ne_sw);

// testing nw_se getDiagonalNeighbour function
        test_child = leaf_nw_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(sw), leaf_sw_nw);

// testing se_nw getDiagonalNeighbour function
        test_child = leaf_se_nw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(sw), leaf_sw_se);

// testing sw_sw getDiagonalNeighbour function
        test_child = leaf_sw_sw;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(sw), nullptr);

// testing se_se getDiagonalNeighbour function
        test_child = leaf_se_se;
        BOOST_CHECK_EQUAL(test_child->getDiagonalNeighbour(sw), nullptr);

// test, that only it gives the getDiagonalNeighbour only on one level
        BOOST_CHECK_EQUAL(leaf_nw->getDiagonalNeighbour(sw), nullptr);
        BOOST_CHECK_EQUAL(leaf_ne->getDiagonalNeighbour(sw), leaf_sw);
        BOOST_CHECK_EQUAL(leaf_sw->getDiagonalNeighbour(sw), nullptr);
        BOOST_CHECK_EQUAL(leaf_se->getDiagonalNeighbour(sw), nullptr);


        // test, that it returns a nullptr, when there is no leaf on the same level
        BOOST_CHECK_EQUAL(leaf_nw_se->getChild(sw)->getDiagonalNeighbour(sw), nullptr);
    }
}