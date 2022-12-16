#include <boost/test/unit_test.hpp>

#include "TreeWithRecursiveComputation.h"
#include "GraphLibrary_Types.h"
#include "TestData.h"

namespace gl {
    template<DataConcept Data, class Config>
    class TestTreeWithRecursiveComputation
            : public TreeWithRecursiveComputation<TestTreeWithRecursiveComputation<Data, Config>, Data, Config> {
        using TreeWithRecursiveComputation<TestTreeWithRecursiveComputation<Data, Config>, Data, Config>::TreeWithRecursiveComputation;
    };

    class TreeWithRecursiveComputationTestFixture {
    public:
        TreeWithRecursiveComputationTestFixture() {
            x = 0.0;
            y = 0.0;
            width = 1.0;
            height = 1.0;
            config = make_shared<dp::Empty_Config>();
        }

        shared_ptr<TestTreeWithRecursiveComputation<dp::Test_Data, dp::Empty_Config>> test_leaf, test_child;
        shared_ptr<dp::Empty_Config> config;
        double x, y;
        double width, height;
    };

    BOOST_FIXTURE_TEST_CASE(TestConstructorOfRecursiveCalculationTree, TreeWithRecursiveComputationTestFixture) {
        test_leaf = make_shared<TestTreeWithRecursiveComputation<dp::Test_Data, dp::Empty_Config>>(x, y, width, height,
                                                                                                   config, 1);
        test_leaf->compute();
        BOOST_TEST(test_leaf->getMaxDepth() == 1);
        BOOST_TEST(test_leaf->hasChildren() == true);
    }

    BOOST_FIXTURE_TEST_CASE(TestRecursiveCalculationTreeWithBigDepth, TreeWithRecursiveComputationTestFixture) {
        test_leaf = make_shared<TestTreeWithRecursiveComputation<dp::Test_Data, dp::Empty_Config>>(x, y, width, height,
                                                                                                   config, 10);
        BOOST_TEST(test_leaf->getMaxDepth() == 10);
        test_leaf->compute();
        test_child = test_leaf->getChild(nw);
        BOOST_TEST(test_child->hasChildren() == true);
        test_child = test_leaf->getChild(ne);
        BOOST_TEST(test_child->hasChildren() == true);
        test_child = test_leaf->getChild(sw);
        BOOST_TEST(test_child->hasChildren() == true);
        test_child = test_leaf->getChild(se);
        BOOST_TEST(test_child->hasChildren() == true);

        test_child = test_leaf->getChild(nw)->getChild(nw);
        BOOST_TEST(test_child->hasChildren() == false);
        test_child = test_leaf->getChild(sw)->getChild(se);
        BOOST_TEST(test_child->hasChildren() == true);
        test_child = test_leaf->getChild(ne)->getChild(nw);
        BOOST_TEST(test_child->hasChildren() == true);
    }
}

