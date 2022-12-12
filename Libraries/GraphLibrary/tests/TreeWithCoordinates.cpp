#include <boost/test/unit_test.hpp>

#include "TreeWithCoordinates.h"
#include "GraphLibrary_Types.h"

namespace gl {
    class TreeWithCoordinatesTestFixture {
    public:
        TreeWithCoordinatesTestFixture() {
            x = 0.5;
            y = 0.5;
            width = 2.0;
            height = 1.0;
            test_leaf = make_shared<TreeWithCoordinates>(x, y, width, height);

            std::cout << "bla" << std::endl;
        }

        shared_ptr<TreeWithCoordinates> test_leaf;
        double x, y;
        double width, height;
    };

    BOOST_FIXTURE_TEST_CASE(TestPositionsAreCorrect, TreeWithCoordinatesTestFixture) {
        BOOST_TEST(test_leaf->getX() == x);

//        BOOST_CHECK_EQUAL(test_leaf->x, 0.5);
//        BOOST_CHECK_EQUAL(test_leaf->y, 0.5);
//        BOOST_CHECK_EQUAL(test_leaf->box_size_x, 2.0);
//        BOOST_CHECK_EQUAL(test_leaf->box_size_y, 2.0);
//        BOOST_CHECK_EQUAL(test_leaf->split_condition, split_decision);
    }
}

