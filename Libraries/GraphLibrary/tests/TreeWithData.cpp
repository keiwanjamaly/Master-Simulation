#include <boost/test/unit_test.hpp>

#include "TreeWithData.h"
#include "GraphLibrary_Types.h"
#include "TestData.h"

namespace gl {
    template<DataConcept Data, class Config>
    class TestTreeWithData : public TreeWithData<TestTreeWithData<Data, Config>, Data, Config> {
        using TreeWithData<TestTreeWithData<Data, Config>, Data, Config>::TreeWithData;
    };

    class TreeWithDataTestFixture {
    public:
        TreeWithDataTestFixture() {
            x = 0.5;
            y = 0.5;
            width = 2.0;
            height = 1.0;
            config = make_shared<dp::Empty_Config>();
            test_leaf = make_shared<TestTreeWithData<dp::Test_Data, dp::Empty_Config>>(x, y, width, height, config);
        }

        shared_ptr<TestTreeWithData<dp::Test_Data, dp::Empty_Config>> test_leaf, test_child;
        shared_ptr<dp::Empty_Config> config;
        double x, y;
        double width, height;
    };

    BOOST_FIXTURE_TEST_CASE(TestConstructorOfDataTree, TreeWithDataTestFixture) {
        BOOST_TEST(test_leaf->getConfig() == config);
        BOOST_TEST(test_leaf->getPoolPointer()->get_thread_count() == std::thread::hardware_concurrency());
        BOOST_TEST(test_leaf->getDataPointer()->value[0] == 1.0);
    }

    BOOST_FIXTURE_TEST_CASE(TestChildConstructorOfDataTree, TreeWithDataTestFixture) {
        test_child = make_shared<TestTreeWithData<dp::Test_Data, dp::Empty_Config>>(test_leaf, nw);
        BOOST_TEST(test_child->getConfig() == config);
        BOOST_TEST(test_child->getPoolPointer()->get_thread_count() == std::thread::hardware_concurrency());
        BOOST_TEST(test_child->getDataPointer()->value[0] == 0.0);
    }

}

