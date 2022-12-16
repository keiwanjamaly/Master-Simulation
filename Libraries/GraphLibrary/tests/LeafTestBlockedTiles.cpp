#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

#include "TreeWithBlocking.h"
#include "TestData.h"

#include <fstream>
#include <string>
#include <set>

namespace gl {

    template<DataConcept Data, class Config>
    class TestTreeWithBlocking
            : public TreeWithBlocking<TestTreeWithBlocking<Data, Config>, Data, Config> {
        using TreeWithBlocking<TestTreeWithBlocking<Data, Config>, Data, Config>::TreeWithBlocking;
    };

    class LeafTestFixtureWithBlocking {
    public:
        LeafTestFixtureWithBlocking() {
            x = 2.5;
            y = 2.5;
            box_size = 5.0;
            config = std::make_shared<dp::Empty_Config>();
            root = TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>::generate_root(x, y, box_size,
                                                                                          box_size,
                                                                                          config, 1);
            root->compute();
        }

        std::shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>> root;
        std::shared_ptr<dp::Empty_Config> config;
        std::shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>> test_child;
        double x{}, y{}, box_size{};
    };

    BOOST_FIXTURE_TEST_CASE(testConstructorWithBlocking, LeafTestFixtureWithBlocking) {
        BOOST_TEST(root->hasChildren());

        BOOST_TEST(root->getChild(nw)->hasChildren());
        BOOST_TEST(root->getChild(ne)->hasChildren());
        BOOST_TEST(root->getChild(sw)->hasChildren());
        BOOST_TEST(root->getChild(se)->hasChildren());

        // test nw blocking
        test_child = root->getChild(nw);
        BOOST_TEST(test_child->getX() == 0);
        BOOST_TEST(test_child->getY() == 5);
        BOOST_TEST(test_child->getChild(nw) == nullptr);
        BOOST_TEST(test_child->getChild(ne) == nullptr);
        BOOST_TEST(test_child->getChild(sw) == nullptr);
        BOOST_TEST(test_child->getChild(se));

        // test ne blocking
        test_child = root->getChild(ne);
        BOOST_TEST(test_child->getX() == 5);
        BOOST_TEST(test_child->getY() == 5);
        BOOST_TEST(test_child->getChild(nw) == nullptr);
        BOOST_TEST(test_child->getChild(ne) == nullptr);
        BOOST_TEST(test_child->getChild(sw));
        BOOST_TEST(test_child->getChild(se) == nullptr);

        // test sw blocking
        test_child = root->getChild(sw);
        BOOST_TEST(test_child->getX() == 0);
        BOOST_TEST(test_child->getY() == 0);
        BOOST_TEST(test_child->getChild(nw) == nullptr);
        BOOST_TEST(test_child->getChild(ne));
        BOOST_TEST(test_child->getChild(sw) == nullptr);
        BOOST_TEST(test_child->getChild(se) == nullptr);

        // test se blocking
        test_child = root->getChild(se);
        BOOST_TEST(test_child->getX() == 5);
        BOOST_TEST(test_child->getY() == 0);
        BOOST_TEST(test_child->getChild(nw));
        BOOST_TEST(test_child->getChild(ne) == nullptr);
        BOOST_TEST(test_child->getChild(sw) == nullptr);
        BOOST_TEST(test_child->getChild(se) == nullptr);
    }

    BOOST_FIXTURE_TEST_CASE(testNeighbourFunctionithBlocking, LeafTestFixtureWithBlocking) {
        // test nw neighbour
        test_child = root->getChild(nw);
        BOOST_TEST(test_child->getChild(se)->getNeighbour(north) == nullptr);
        BOOST_TEST(test_child->getChild(se)->getNeighbour(east) == root->getChild(ne)->getChild(sw));
        BOOST_TEST(test_child->getChild(se)->getNeighbour(south) == root->getChild(sw)->getChild(ne));
        BOOST_TEST(test_child->getChild(se)->getNeighbour(west) == nullptr);

        // test ne neighbour
        test_child = root->getChild(ne);
        BOOST_TEST(test_child->getChild(sw)->getNeighbour(north) == nullptr);
        BOOST_TEST(test_child->getChild(sw)->getNeighbour(east) == nullptr);
        BOOST_TEST(test_child->getChild(sw)->getNeighbour(south) == root->getChild(se)->getChild(nw));
        BOOST_TEST(test_child->getChild(sw)->getNeighbour(west) == root->getChild(nw)->getChild(se));

        // test sw neighbour
        test_child = root->getChild(sw);
        BOOST_TEST(test_child->getChild(ne)->getNeighbour(north) == root->getChild(nw)->getChild(se));
        BOOST_TEST(test_child->getChild(ne)->getNeighbour(east) == root->getChild(se)->getChild(nw));
        BOOST_TEST(test_child->getChild(ne)->getNeighbour(south) == nullptr);
        BOOST_TEST(test_child->getChild(ne)->getNeighbour(west) == nullptr);

        // test se neighbour
        test_child = root->getChild(se);
        BOOST_TEST(test_child->getChild(nw)->getNeighbour(north) == root->getChild(ne)->getChild(sw));
        BOOST_TEST(test_child->getChild(nw)->getNeighbour(east) == nullptr);
        BOOST_TEST(test_child->getChild(nw)->getNeighbour(south) == nullptr);
        BOOST_TEST(test_child->getChild(nw)->getNeighbour(west) == root->getChild(sw)->getChild(ne));
    }

    BOOST_FIXTURE_TEST_CASE(testGetAllLeafsWithBlocking, LeafTestFixtureWithBlocking) {
        std::vector<std::shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>>> allLeafs;
        root->getAllLeafs(allLeafs);
        std::set < shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>> >
        all_leafs_set(allLeafs.begin(), allLeafs.end());
        // reference set
        std::set < shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>> >
        reference_set({
                              root,
                              root->getChild(nw),
                              root->getChild(ne),
                              root->getChild(sw),
                              root->getChild(se),
                              root->getChild(nw)->getChild(se),
                              root->getChild(ne)->getChild(sw),
                              root->getChild(sw)->getChild(ne),
                              root->getChild(se)->getChild(nw)
                      });

        // no doubled elements
        BOOST_CHECK_EQUAL(all_leafs_set.size(), allLeafs.size());
        // all elements are included
        BOOST_TEST(all_leafs_set == reference_set);
    }

    BOOST_AUTO_TEST_CASE(TestOnDataWithBlocking) {
//        std::ofstream myFile("../Libraries/GraphLibrary/tests/data/data_with_blocking.csv");
        std::ifstream test_stream;
        test_stream.open("../Libraries/GraphLibrary/tests/data/data_with_blocking.csv");
        std::string content((std::istreambuf_iterator<char>(test_stream)),
                            (std::istreambuf_iterator<char>()));
        output_test_stream output;

        double x = 2.0;
        double y = 2.5;
        double box_size_x = 4.0;
        double box_size_y = 5.0;
        std::shared_ptr<dp::Empty_Config> config = std::make_shared<dp::Empty_Config>();
        std::shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>> root = TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>::generate_root(
                x, y,
                box_size_x,
                box_size_y,
                config, 4);


        vector<shared_ptr<TestTreeWithBlocking<dp::TestDensity, dp::Empty_Config>>> allLeafs;

        root->compute();
        root->getAllLeafs(allLeafs);
        for (const auto &leaf: allLeafs) {
            output << leaf->getX() << "," << leaf->getY() << "," << leaf->getDataPointer()->value[0] << "\n";
        }

        BOOST_TEST(output.is_equal(content));
    }

} // dp