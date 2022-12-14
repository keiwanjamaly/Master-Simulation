#include <boost/test/unit_test.hpp>

#include "TreeWithComparisons.h"
#include "GraphLibrary_Types.h"
#include "TestData.h"

namespace gl {
    template<DataConcept Data, class Config>
    class TestTreeWithComparisons : public TreeWithComparisons<TestTreeWithComparisons<Data, Config>, Data, Config> {
        using TreeWithComparisons<TestTreeWithComparisons<Data, Config>, Data, Config>::TreeWithComparisons;
    };

    class TreeWithComparisonsTestFixture {
        // I'm going to test the neighbours of the following points
        // test points      test labels
        // x, 0, 0, x       nw_nw, nw_ne, ne_nw, ne_ne
        // 0, x, 0, 0       nw_sw, nw_se, ne_sw, ne_se
        // 0, 0, x, 0       sw_nw, sw_ne, se_nw, se_ne
        // x, 0, 0, x       sw_sw, sw_se, se_sw, se_se

        // testing values outside the boundary should result in a null-pointer

    public:
        TreeWithComparisonsTestFixture(int mode_ = 0) : mode{mode_} {
            x = 0.0;
            y = 0.0;
            box_size = 1.0;

            config = make_shared<dp::Empty_Config>();
            config->mode = mode;

            test_leaf = make_shared<TestTreeWithComparisons<dp::Test_Data, dp::Empty_Config>>(x, y, box_size, box_size,
                                                                                              config);

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

        int mode;
        double x, y, box_size;
        shared_ptr<dp::Empty_Config> config;
        shared_ptr<TestTreeWithComparisons<dp::Test_Data, dp::Empty_Config>> test_leaf;
        shared_ptr<TestTreeWithComparisons<dp::Test_Data, dp::Empty_Config>> test_child;
        shared_ptr<TestTreeWithComparisons<dp::Test_Data, dp::Empty_Config>> leaf_nw_nw, leaf_nw_ne, leaf_nw_sw, leaf_nw_se, leaf_ne_nw, leaf_ne_ne, leaf_ne_sw, leaf_ne_se, leaf_sw_nw, leaf_sw_ne, leaf_sw_sw, leaf_sw_se, leaf_se_nw, leaf_se_ne, leaf_se_sw, leaf_se_se;
        shared_ptr<TestTreeWithComparisons<dp::Test_Data, dp::Empty_Config>> leaf_nw, leaf_ne, leaf_sw, leaf_se;
    };

    class H_TreeWithComparisonsTestFixture : public TreeWithComparisonsTestFixture {
    public:
        H_TreeWithComparisonsTestFixture() : TreeWithComparisonsTestFixture(1) {

        }
    };

    BOOST_FIXTURE_TEST_CASE(TestNorthComparison, H_TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestEastComparison, TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestSouthComparison, H_TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestWestComparison, TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestNorthWestComparison, TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestNorthEastComparison, TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestSouthEastComparison, TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestSouthWestComparison, TreeWithComparisonsTestFixture) {
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

    BOOST_FIXTURE_TEST_CASE(TestSplitLeafDecision, TreeWithComparisonsTestFixture) {
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

}