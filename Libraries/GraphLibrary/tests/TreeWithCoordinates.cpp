#include <boost/test/unit_test.hpp>

#include "TreeWithCoordinates.h"
#include "GraphLibrary_Types.h"

namespace gl {

    class TestTreeWithCoordinates : public TreeWithCoordinates<TestTreeWithCoordinates> {
        using TreeWithCoordinates::TreeWithCoordinates;
    };

    class TreeWithCoordinatesTestFixture {
    public:
        TreeWithCoordinatesTestFixture() {
            x = 0.5;
            y = 0.5;
            width = 2.0;
            height = 1.0;
            test_leaf = make_shared<TestTreeWithCoordinates>(x, y, width, height);
        }

        shared_ptr<TestTreeWithCoordinates> test_leaf, test_child;
        double x, y;
        double width, height;
    };

    BOOST_FIXTURE_TEST_CASE(TestPositionsAreCorrect, TreeWithCoordinatesTestFixture) {
        BOOST_TEST(test_leaf->getX() == x);
        BOOST_TEST(test_leaf->getY() == y);
        BOOST_TEST(test_leaf->getWidth() == width);
        BOOST_TEST(test_leaf->getHeight() == height);
    }

    BOOST_FIXTURE_TEST_CASE(TestChildConstructor, TreeWithCoordinatesTestFixture) {
        test_child = make_shared<TestTreeWithCoordinates>(test_leaf, nw);
        BOOST_TEST(test_child->getX() == 0.0);
        BOOST_TEST(test_child->getY() == 0.75);
        BOOST_TEST(test_child->getWidth() == width / 2);
        BOOST_TEST(test_child->getHeight() == height / 2);
    }

    BOOST_FIXTURE_TEST_CASE(TestAttatchLeafs, TreeWithCoordinatesTestFixture) {
        double x_child_pos, y_child_pos;
        double child_box_size_x = test_leaf->getWidth() / 2;
        double child_box_size_y = test_leaf->getHeight() / 2;

        test_leaf->attachLeaves();

        // testing north-west coordinates
        x_child_pos = x - child_box_size_x / 2;
        y_child_pos = y + child_box_size_y / 2;
        test_child = test_leaf->getChild(nw);
        BOOST_CHECK_EQUAL(test_child->getX(), x_child_pos);
        BOOST_CHECK_EQUAL(test_child->getY(), y_child_pos);

        // testing north-east coordinates
        x_child_pos = x + child_box_size_x / 2;
        y_child_pos = y + child_box_size_y / 2;
        test_child = test_leaf->getChild(ne);
        BOOST_CHECK_EQUAL(test_child->getX(), x_child_pos);
        BOOST_CHECK_EQUAL(test_child->getY(), y_child_pos);

        // testing south-west coordinates
        x_child_pos = x - child_box_size_x / 2;
        y_child_pos = y - child_box_size_y / 2;
        test_child = test_leaf->getChild(sw);
        BOOST_CHECK_EQUAL(test_child->getX(), x_child_pos);
        BOOST_CHECK_EQUAL(test_child->getY(), y_child_pos);

        // testing south-east coordinates
        x_child_pos = x + child_box_size_x / 2;
        y_child_pos = y - child_box_size_y / 2;
        test_child = test_leaf->getChild(se);
        BOOST_CHECK_EQUAL(test_child->getX(), x_child_pos);
        BOOST_CHECK_EQUAL(test_child->getY(), y_child_pos);
    }
}
