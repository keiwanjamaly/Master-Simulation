#include <boost/test/unit_test.hpp>
#include "Leaf.h"
#include "Types_Leaf.h"
#include "TestData.h"


namespace dp {

    using std::shared_ptr, std::make_shared;

    class LeafTestFixture {
    public:
        LeafTestFixture() {
            x = 0.5;
            y = 0.5;
            box_size = 2.0;
            test_leaf = make_shared<CurrLeaf>(CurrLeaf(x, y, box_size, split_decision,
                                                       std::make_shared<Empty_Config>(
                                                               config)));
        }

        shared_ptr<CurrLeaf> test_leaf;
        Empty_Config config{};
        double x{}, y{}, box_size{};
    };


// test constructors
    BOOST_FIXTURE_TEST_CASE(PositionsAreCorrect, LeafTestFixture) {
        BOOST_CHECK_EQUAL(test_leaf->x, 0.5);
        BOOST_CHECK_EQUAL(test_leaf->y, 0.5);
        BOOST_CHECK_EQUAL(test_leaf->box_size, 2.0);
        BOOST_CHECK_EQUAL(test_leaf->split_condition, split_decision);
    }

    BOOST_FIXTURE_TEST_CASE(LeafParentTestConstructor, LeafTestFixture) {
        double x = 0.5;
        double y = 0.5;
        double box_size = 2.0;
        double child_x = x - box_size / 4.0;
        double child_y = y + box_size / 4.0;
        Empty_Config config{};
        shared_ptr<CurrLeaf> parent_leaf = std::make_shared<CurrLeaf>(
                CurrLeaf(x, y, box_size, split_decision,
                         std::make_shared<Empty_Config>(config)));
        shared_ptr<CurrLeaf> test_leaf = std::make_shared<CurrLeaf>(CurrLeaf(nw, parent_leaf,
                                                                             std::make_shared<Empty_Config>(config)));
        BOOST_CHECK_EQUAL(parent_leaf, test_leaf->parent);

        BOOST_TEST(test_leaf->x == child_x, boost::test_tools::tolerance(0.0));
        BOOST_TEST(test_leaf->y == child_y, boost::test_tools::tolerance(0.0));
        BOOST_TEST(parent_leaf->box_size * 0.5 == test_leaf->box_size);

        BOOST_CHECK_EQUAL(test_leaf->children.size(), 0);
    }

    BOOST_FIXTURE_TEST_CASE(attatchLeavesIsWorking, LeafTestFixture) {
        double x_child_pos, y_child_pos;
        double child_box_size = test_leaf->box_size / 2;


        test_leaf->attach_leaves();
        shared_ptr<CurrLeaf> test_child;

        // testing north-west coordinates
        x_child_pos = x - child_box_size / 2.0;
        y_child_pos = y + child_box_size / 2.0;
        test_child = test_leaf->children[nw];
        BOOST_CHECK_EQUAL(test_child->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->parent, test_leaf);

        // testing north-east coordinates
        x_child_pos = x + child_box_size / 2.0;
        y_child_pos = y + child_box_size / 2.0;
        test_child = test_leaf->children[ne];
        BOOST_CHECK_EQUAL(test_child->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->parent, test_leaf);

        // testing south-west coordinates
        x_child_pos = x - child_box_size / 2.0;
        y_child_pos = y - child_box_size / 2.0;
        test_child = test_leaf->children[sw];
        BOOST_CHECK_EQUAL(test_child->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->parent, test_leaf);

        // testing south-east coordinates
        x_child_pos = x + child_box_size / 2.0;
        y_child_pos = y - child_box_size / 2.0;
        test_child = test_leaf->children[se];
        BOOST_CHECK_EQUAL(test_child->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->x, x_child_pos);
        BOOST_CHECK_EQUAL(test_child->data->y, y_child_pos);
        BOOST_CHECK_EQUAL(test_child->parent, test_leaf);
    }

    BOOST_FIXTURE_TEST_CASE(testTwiceAttatchLeaves, LeafTestFixture) {
        test_leaf->attach_leaves();
        test_leaf->attach_leaves();

        // test, that leaf has only 4 children
        BOOST_CHECK_EQUAL(test_leaf->children.size(), 4);

        // test, that children have no other children
        BOOST_CHECK_EQUAL(test_leaf->children[nw]->children.size(), 0);
        BOOST_CHECK_EQUAL(test_leaf->children[ne]->children.size(), 0);
        BOOST_CHECK_EQUAL(test_leaf->children[sw]->children.size(), 0);
        BOOST_CHECK_EQUAL(test_leaf->children[se]->children.size(), 0);
    }

    BOOST_FIXTURE_TEST_CASE(testIsRoot, LeafTestFixture) {
        test_leaf->attach_leaves();
        BOOST_TEST(test_leaf->isRoot() == true);

        BOOST_TEST(test_leaf->children[nw]->isRoot() == false);
        BOOST_TEST(test_leaf->children[ne]->isRoot() == false);
        BOOST_TEST(test_leaf->children[sw]->isRoot() == false);
        BOOST_TEST(test_leaf->children[se]->isRoot() == false);
    }

    // test get_children_of_parent()
    BOOST_FIXTURE_TEST_CASE(testGetChildrenOfParent, LeafTestFixture) {
        test_leaf->attach_leaves();

        shared_ptr<CurrLeaf> test_child;
        shared_ptr<CurrLeaf> test_child_nw = test_leaf->children[nw];
        shared_ptr<CurrLeaf> test_child_ne = test_leaf->children[ne];
        shared_ptr<CurrLeaf> test_child_sw = test_leaf->children[sw];
        shared_ptr<CurrLeaf> test_child_se = test_leaf->children[se];

        // test from nw child direction
        test_child = test_child_nw;
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(nw), test_child_nw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(ne), test_child_ne);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(sw), test_child_sw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(se), test_child_se);

        // test from ne child direction
        test_child = test_child_ne;
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(nw), test_child_nw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(ne), test_child_ne);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(sw), test_child_sw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(se), test_child_se);

        // test from sw child direction
        test_child = test_child_sw;
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(nw), test_child_nw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(ne), test_child_ne);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(sw), test_child_sw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(se), test_child_se);

        // test from se child direction
        test_child = test_child_se;
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(nw), test_child_nw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(ne), test_child_ne);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(sw), test_child_sw);
        BOOST_CHECK_EQUAL(test_child->get_child_of_parent(se), test_child_se);

        // getting the children of a root, a null-pointer should be returned
        BOOST_CHECK_EQUAL(test_leaf->get_child_of_parent(nw), nullptr);
        BOOST_CHECK_EQUAL(test_leaf->get_child_of_parent(ne), nullptr);
        BOOST_CHECK_EQUAL(test_leaf->get_child_of_parent(sw), nullptr);
        BOOST_CHECK_EQUAL(test_leaf->get_child_of_parent(se), nullptr);
    }

} // dp