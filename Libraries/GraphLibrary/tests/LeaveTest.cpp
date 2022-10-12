#include "gtest/gtest.h"
#include "Leaf.h"
#include "Types.h"
#include "Data.cpp"


namespace dp {

    class LeafTestFixture : public ::testing::Test {

    protected:
        void SetUp() override {
            x = 0.5;
            y = 0.5;
            x_min = 0.0;
            x_max = 1.0;
            y_min = 0.0;
            y_max = 1.0;
            test_leaf = Leaf<Data>(Data(x, y), x, y, x_min, x_max, y_min, y_max);
        }

        Leaf<Data> test_leaf;
        double x{}, y{};
        double x_min{}, x_max{}, y_min{}, y_max{};
    };


// test constructors
    TEST_F(LeafTestFixture, PositionsAreCorrect) {
        EXPECT_EQ(test_leaf.x, 0.5);
        EXPECT_EQ(test_leaf.y, 0.5);
        EXPECT_EQ(test_leaf.x_min, 0.0);
        EXPECT_EQ(test_leaf.x_min, 1.0);
        EXPECT_EQ(test_leaf.y_min, 0.0);
        EXPECT_EQ(test_leaf.y_min, 1.0);
    }


    TEST(LeafParentTestSiute, LeafParentTestConstructor) {
        double x = 0.5;
        double y = 0.5;
        double x_min = 0.0;
        double x_max = 1.0;
        double y_min = 0.0;
        double y_max = 1.0;
        Leaf<Data> parent_leaf = Leaf<Data>(Data(x, y), x, y, x_min, x_max, y_min, y_max);
        Leaf<Data> test_leaf = Leaf<Data>(Data(x, y), x, y, x_min, x_max, y_min, y_max, &parent_leaf);
        EXPECT_EQ(&parent_leaf, test_leaf.parent);

        EXPECT_EQ(test_leaf.x, 0.5);
        EXPECT_EQ(test_leaf.y, 0.5);
        EXPECT_EQ(test_leaf.x_min, 0.0);
        EXPECT_EQ(test_leaf.x_min, 1.0);
        EXPECT_EQ(test_leaf.y_min, 0.0);
        EXPECT_EQ(test_leaf.y_min, 1.0);
    }
// test attach_leaves
    TEST_F(LeafTestFixture, attatchLeavesIsWorking) {
        const double x_abs = x_max - x_min;
        const double y_abs = y_max - y_min;
        const double x_offset = x_abs / 4;
        const double y_offset = y_abs / 4;
        double x_child_pos, y_child_pos;


        test_leaf.attach_leaves();
        Leaf<Data> test_child;

        // testing north-west coordinates
        x_child_pos = x - x_offset;
        y_child_pos = y + y_offset;
        test_child = test_leaf.children[nw];
        EXPECT_FLOAT_EQ(test_child.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.y, y_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.y, y_child_pos);
        EXPECT_EQ(test_child.parent, &test_leaf);

        // testing north-east coordinates
        x_child_pos = x + x_offset;
        y_child_pos = y + y_offset;
        test_child = test_leaf.children[ne];
        EXPECT_FLOAT_EQ(test_child.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.y, y_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.y, y_child_pos);
        EXPECT_EQ(test_child.parent, &test_leaf);

        // testing south-west coordinates
        x_child_pos = x - x_offset;
        y_child_pos = y - y_offset;
        test_child = test_leaf.children[sw];
        EXPECT_FLOAT_EQ(test_child.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.y, y_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.y, y_child_pos);
        EXPECT_EQ(test_child.parent, &test_leaf);

        // testing south-east coordinates
        x_child_pos = x + x_offset;
        y_child_pos = y - y_offset;
        test_child = test_leaf.children[se];
        EXPECT_FLOAT_EQ(test_child.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.y, y_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.x, x_child_pos);
        EXPECT_FLOAT_EQ(test_child.data.y, y_child_pos);
        EXPECT_EQ(test_child.parent, &test_leaf);
    }

// test compute
    TEST_F(LeafTestFixture, computeIsWorking) {
        test_leaf.compute();
        EXPECT_EQ(test_leaf.data.value[0], 1.0);
    }

} // dp