#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

#include "Leaf.h"
#include "TestData.h"

#include <fstream>
#include <string>

namespace dp {

    class LeafTestFixtureWithBlocking {
    public:
        LeafTestFixtureWithBlocking() {
            x = 2.5;
            y = 2.5;
            box_size = 5.0;
            config = std::make_shared<Empty_Config>();
            root = Leaf<Data, Empty_Config>::generate_root(x, y, box_size,
                                                           box_size,
                                                           split_decision,
                                                           config);
        }

        std::shared_ptr<Leaf<Data, Empty_Config>> root;
        std::shared_ptr<Empty_Config> config;
        std::shared_ptr<Leaf<Data, Empty_Config>> test_child;
        double x{}, y{}, box_size{};
    };

    BOOST_FIXTURE_TEST_CASE(testConstructorWithBlocking, LeafTestFixtureWithBlocking) {
        BOOST_TEST(root->children.size() == 4);

        BOOST_TEST(root->children[nw]->children.size() == 4);
        BOOST_TEST(root->children[ne]->children.size() == 4);
        BOOST_TEST(root->children[sw]->children.size() == 4);
        BOOST_TEST(root->children[se]->children.size() == 4);

        // test nw blocking
        test_child = root->children[nw];
        BOOST_TEST(test_child->x == 0);
        BOOST_TEST(test_child->y == 5);
        BOOST_TEST(test_child->children[nw]->block == true);
        BOOST_TEST(test_child->children[ne]->block == true);
        BOOST_TEST(test_child->children[sw]->block == true);
        BOOST_TEST(test_child->children[se]->block == false);

        // test ne blocking
        test_child = root->children[ne];
        BOOST_TEST(test_child->x == 5);
        BOOST_TEST(test_child->y == 5);
        BOOST_TEST(test_child->children[nw]->block == true);
        BOOST_TEST(test_child->children[ne]->block == true);
        BOOST_TEST(test_child->children[sw]->block == false);
        BOOST_TEST(test_child->children[se]->block == true);

        // test sw blocking
        test_child = root->children[sw];
        BOOST_TEST(test_child->x == 0);
        BOOST_TEST(test_child->y == 0);
        BOOST_TEST(test_child->children[nw]->block == true);
        BOOST_TEST(test_child->children[ne]->block == false);
        BOOST_TEST(test_child->children[sw]->block == true);
        BOOST_TEST(test_child->children[se]->block == true);

        // test se blocking
        test_child = root->children[se];
        BOOST_TEST(test_child->x == 5);
        BOOST_TEST(test_child->y == 0);
        BOOST_TEST(test_child->children[nw]->block == false);
        BOOST_TEST(test_child->children[ne]->block == true);
        BOOST_TEST(test_child->children[sw]->block == true);
        BOOST_TEST(test_child->children[se]->block == true);


        // check, that there are not too many leafs
        BOOST_TEST(root->children.size() == 4);

        test_child = root->children[nw];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 0);

        test_child = root->children[ne];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 0);

        test_child = root->children[sw];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 0);

        test_child = root->children[se];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 0);
    }

    BOOST_FIXTURE_TEST_CASE(testNeighbourFunctionithBlocking, LeafTestFixtureWithBlocking) {
        // test nw neighbour
        test_child = root->children[nw];
        BOOST_TEST(test_child->children[se]->get_neighbour(north) == nullptr);
        BOOST_TEST(test_child->children[se]->get_neighbour(east) == root->children[ne]->children[sw]);
        BOOST_TEST(test_child->children[se]->get_neighbour(south) == root->children[sw]->children[ne]);
        BOOST_TEST(test_child->children[se]->get_neighbour(west) == nullptr);

        // test ne neighbour
        test_child = root->children[ne];
        BOOST_TEST(test_child->children[sw]->get_neighbour(north) == nullptr);
        BOOST_TEST(test_child->children[sw]->get_neighbour(east) == nullptr);
        BOOST_TEST(test_child->children[sw]->get_neighbour(south) == root->children[se]->children[nw]);
        BOOST_TEST(test_child->children[sw]->get_neighbour(west) == root->children[nw]->children[se]);

        // test sw neighbour
        test_child = root->children[sw];
        BOOST_TEST(test_child->children[ne]->get_neighbour(north) == root->children[nw]->children[se]);
        BOOST_TEST(test_child->children[ne]->get_neighbour(east) == root->children[se]->children[nw]);
        BOOST_TEST(test_child->children[ne]->get_neighbour(south) == nullptr);
        BOOST_TEST(test_child->children[ne]->get_neighbour(west) == nullptr);

        // test se neighbour
        test_child = root->children[se];
        BOOST_TEST(test_child->children[nw]->get_neighbour(north) == root->children[ne]->children[sw]);
        BOOST_TEST(test_child->children[nw]->get_neighbour(east) == nullptr);
        BOOST_TEST(test_child->children[nw]->get_neighbour(south) == nullptr);
        BOOST_TEST(test_child->children[nw]->get_neighbour(west) == root->children[sw]->children[ne]);
    }

    BOOST_FIXTURE_TEST_CASE(testGetAllLeafsWithBlocking, LeafTestFixtureWithBlocking) {
        std::vector<std::shared_ptr<Leaf<Data, Empty_Config>>> list_of_leafs = root->get_all_leafs();
        std::set < shared_ptr<CurrLeaf> > all_leafs_set(list_of_leafs.begin(), list_of_leafs.end());
        // reference set
        std::set < shared_ptr<CurrLeaf> >
        reference_set({
                              root,
                              root->children[nw],
                              root->children[ne],
                              root->children[sw],
                              root->children[se],
                              root->children[nw]->children[se],
                              root->children[ne]->children[sw],
                              root->children[sw]->children[ne],
                              root->children[se]->children[nw]
                      });

        // no doubled elements
        BOOST_CHECK_EQUAL(all_leafs_set.size(), list_of_leafs.size());
        // all elements are included
        BOOST_TEST(all_leafs_set == reference_set);
    }

    BOOST_FIXTURE_TEST_CASE(testForceBalanceTreeWithBlocking, LeafTestFixtureWithBlocking) {
        root->balance_tree(true);

        BOOST_TEST(root->children.size() == 4);

        test_child = root->children[nw];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 4);

        test_child = root->children[ne];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 4);
        BOOST_TEST(test_child->children[se]->children.size() == 0);

        test_child = root->children[sw];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 0);
        BOOST_TEST(test_child->children[ne]->children.size() == 4);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 0);

        test_child = root->children[se];
        BOOST_TEST(test_child->children.size() == 4);
        BOOST_TEST(test_child->children[nw]->children.size() == 4);
        BOOST_TEST(test_child->children[ne]->children.size() == 0);
        BOOST_TEST(test_child->children[sw]->children.size() == 0);
        BOOST_TEST(test_child->children[se]->children.size() == 0);
    }

    BOOST_AUTO_TEST_CASE(TestOnDataWithBlocking) {
        double x = 2.0;
        double y = 2.5;
        double box_size_x = 4.0;
        double box_size_y = 5.0;
        std::shared_ptr<Empty_Config> config = std::make_shared<Empty_Config>();
        std::shared_ptr<Leaf<TestDensity, Empty_Config>> root = Leaf<TestDensity, Empty_Config>::generate_root(x, y,
                                                                                                               box_size_x,
                                                                                                               box_size_y,
                                                                                                               split_decision,
                                                                                                               config);

        std::ifstream test_stream;
        test_stream.open("../Libraries/GraphLibrary/tests/data/data_with_blocking.csv");
        std::string content((std::istreambuf_iterator<char>(test_stream)),
                            (std::istreambuf_iterator<char>()));
        output_test_stream output;
        
        for (int k = 0; k < 5; k++) {
            for (const auto &i: root->get_all_leafs()) {
                i->data->compute();
            }
            root->balance_tree();
        }
        for (const auto &i: root->get_all_leafs()) {
            i->data->compute();
        }

        for (const auto &i: root->get_all_leafs()) {
            output << i->data->x << "," << i->data->y << "," << i->data->value[0] << "\n";
        }

        BOOST_TEST(output.is_equal(content));
    }

} // dp