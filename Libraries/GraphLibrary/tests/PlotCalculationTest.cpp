#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

#include "Leaf.h"
#include "TestData.h"
#include <cmath>
#include <fstream>
#include <string>

namespace dp {

    BOOST_AUTO_TEST_CASE(testdensityplot) {
        output_test_stream output;
        std::ifstream test_stream;
        test_stream.open("../Libraries/GraphLibrary/tests/data/data.csv");
        std::string content((std::istreambuf_iterator<char>(test_stream)),
                            (std::istreambuf_iterator<char>()));
        std::shared_ptr<Empty_Config> config = std::make_shared<Empty_Config>();
        std::shared_ptr<Leaf<TestDensity, Empty_Config>> root = std::make_shared<Leaf<TestDensity, Empty_Config>>(2.5,
                                                                                                                  2.5,
                                                                                                                  5,
                                                                                                                  5,
                                                                                                                  split_decision,
                                                                                                                  config);

        root->data->compute();
        root->balance_tree(true);
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
            output << i->data->configuration->x << "," << i->data->configuration->y << "," << i->data->value[0] << "\n";
        }
        BOOST_TEST(output.is_equal(content));
    }

} // dp