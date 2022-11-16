#include "gtest/gtest.h"
#include "Leaf.h"
#include "Types_Leaf.h"
#include "TestData.h"


namespace dp {

    using std::shared_ptr, std::make_shared;

    class LeafTestFixture : public ::testing::Test {

    protected:
        void SetUp() override {
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
    TEST_F(LeafTestFixture, PositionsAreCorrect) {
        ASSERT_EQ(test_leaf->x, 0.5);
        ASSERT_EQ(test_leaf->y, 0.5);
        ASSERT_EQ(test_leaf->box_size, 2.0);
        ASSERT_EQ(test_leaf->split_condition, split_decision);
    }

    TEST(LeafParentTestSiute, LeafParentTestConstructor) {
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
        ASSERT_EQ(parent_leaf, test_leaf->parent);

        ASSERT_DOUBLE_EQ(test_leaf->x, child_x);
        ASSERT_DOUBLE_EQ(test_leaf->y, child_y);
        ASSERT_DOUBLE_EQ(parent_leaf->box_size / 2.0, test_leaf->box_size);

        ASSERT_EQ(test_leaf->children.size(), 0);
    }

// test attach_leaves
    TEST_F(LeafTestFixture, attatchLeavesIsWorking) {
        double x_child_pos, y_child_pos;
        double child_box_size = test_leaf->box_size / 2;


        test_leaf->attach_leaves();
        shared_ptr<CurrLeaf> test_child;

        // testing north-west coordinates
        x_child_pos = x - child_box_size / 2.0;
        y_child_pos = y + child_box_size / 2.0;
        test_child = test_leaf->children[nw];
        ASSERT_DOUBLE_EQ(test_child->x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->y, y_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.y, y_child_pos);
        ASSERT_EQ(test_child->parent, test_leaf);

        // testing north-east coordinates
        x_child_pos = x + child_box_size / 2.0;
        y_child_pos = y + child_box_size / 2.0;
        test_child = test_leaf->children[ne];
        ASSERT_DOUBLE_EQ(test_child->x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->y, y_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.y, y_child_pos);
        ASSERT_EQ(test_child->parent, test_leaf);

        // testing south-west coordinates
        x_child_pos = x - child_box_size / 2.0;
        y_child_pos = y - child_box_size / 2.0;
        test_child = test_leaf->children[sw];
        ASSERT_DOUBLE_EQ(test_child->x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->y, y_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.y, y_child_pos);
        ASSERT_EQ(test_child->parent, test_leaf);

        // testing south-east coordinates
        x_child_pos = x + child_box_size / 2.0;
        y_child_pos = y - child_box_size / 2.0;
        test_child = test_leaf->children[se];
        ASSERT_DOUBLE_EQ(test_child->x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->y, y_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.x, x_child_pos);
        ASSERT_DOUBLE_EQ(test_child->data.y, y_child_pos);
        ASSERT_EQ(test_child->parent, test_leaf);
    }

    TEST_F(LeafTestFixture, testTwiceAttatchLeaves) {
        test_leaf->attach_leaves();
        test_leaf->attach_leaves();

        // test, that leaf has only 4 children
        ASSERT_EQ(test_leaf->children.size(), 4);

        // test, that children have no other children
        ASSERT_EQ(test_leaf->children[nw]->children.size(), 0);
        ASSERT_EQ(test_leaf->children[ne]->children.size(), 0);
        ASSERT_EQ(test_leaf->children[sw]->children.size(), 0);
        ASSERT_EQ(test_leaf->children[se]->children.size(), 0);
    }

    // test isRoot()
    TEST_F(LeafTestFixture, testIsRoot) {
        test_leaf->attach_leaves();
        ASSERT_TRUE(test_leaf->isRoot());

        ASSERT_FALSE(test_leaf->children[nw]->isRoot());
        ASSERT_FALSE(test_leaf->children[ne]->isRoot());
        ASSERT_FALSE(test_leaf->children[sw]->isRoot());
        ASSERT_FALSE(test_leaf->children[se]->isRoot());
    }

    // test get_children_of_parent()
    TEST_F(LeafTestFixture, testGetChildrenOfParent) {
        test_leaf->attach_leaves();

        shared_ptr<CurrLeaf> test_child;
        shared_ptr<CurrLeaf> test_child_nw = test_leaf->children[nw];
        shared_ptr<CurrLeaf> test_child_ne = test_leaf->children[ne];
        shared_ptr<CurrLeaf> test_child_sw = test_leaf->children[sw];
        shared_ptr<CurrLeaf> test_child_se = test_leaf->children[se];

        // test from nw child direction
        test_child = test_child_nw;
        ASSERT_EQ(test_child->get_child_of_parent(nw), test_child_nw);
        ASSERT_EQ(test_child->get_child_of_parent(ne), test_child_ne);
        ASSERT_EQ(test_child->get_child_of_parent(sw), test_child_sw);
        ASSERT_EQ(test_child->get_child_of_parent(se), test_child_se);

        // test from ne child direction
        test_child = test_child_ne;
        ASSERT_EQ(test_child->get_child_of_parent(nw), test_child_nw);
        ASSERT_EQ(test_child->get_child_of_parent(ne), test_child_ne);
        ASSERT_EQ(test_child->get_child_of_parent(sw), test_child_sw);
        ASSERT_EQ(test_child->get_child_of_parent(se), test_child_se);

        // test from sw child direction
        test_child = test_child_sw;
        ASSERT_EQ(test_child->get_child_of_parent(nw), test_child_nw);
        ASSERT_EQ(test_child->get_child_of_parent(ne), test_child_ne);
        ASSERT_EQ(test_child->get_child_of_parent(sw), test_child_sw);
        ASSERT_EQ(test_child->get_child_of_parent(se), test_child_se);

        // test from se child direction
        test_child = test_child_se;
        ASSERT_EQ(test_child->get_child_of_parent(nw), test_child_nw);
        ASSERT_EQ(test_child->get_child_of_parent(ne), test_child_ne);
        ASSERT_EQ(test_child->get_child_of_parent(sw), test_child_sw);
        ASSERT_EQ(test_child->get_child_of_parent(se), test_child_se);

        // getting the children of a root, a null-pointer should be returned
        ASSERT_EQ(test_leaf->get_child_of_parent(nw), nullptr);
        ASSERT_EQ(test_leaf->get_child_of_parent(ne), nullptr);
        ASSERT_EQ(test_leaf->get_child_of_parent(sw), nullptr);
        ASSERT_EQ(test_leaf->get_child_of_parent(se), nullptr);
    }

} // dp