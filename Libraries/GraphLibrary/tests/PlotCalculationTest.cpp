#include <boost/test/unit_test.hpp>
//#include <boost/test/output_test_stream.hpp>

//using boost::test_tools::output_test_stream;

#include "TreeWithRecursiveComputation.h"
#include "TestData.h"
#include <fstream>

namespace gl {

    template<DataConcept Data, class Config>
    class Test2TreeWithRecursiveComputation
            : public TreeWithRecursiveComputation<Test2TreeWithRecursiveComputation<Data, Config>, Data, Config> {
        using TreeWithRecursiveComputation<Test2TreeWithRecursiveComputation<Data, Config>, Data, Config>::TreeWithRecursiveComputation;
    };

    BOOST_AUTO_TEST_CASE(testdensityplot) {
        std::ofstream myFile("../Libraries/GraphLibrary/tests/data/data.csv");
        shared_ptr<dp::Empty_Config> config = std::make_shared<dp::Empty_Config>();
        shared_ptr<Test2TreeWithRecursiveComputation<dp::TestDensity, dp::Empty_Config>> root = make_shared<Test2TreeWithRecursiveComputation<dp::TestDensity, dp::Empty_Config>>(
                2.5, 2.5, 5.0,
                5.0, config);
        

        vector<shared_ptr<Test2TreeWithRecursiveComputation<dp::TestDensity, dp::Empty_Config>>> allLeafs;

        root->compute();
        root->getAllLeafs(allLeafs);
        for (const auto &leaf: allLeafs) {
            myFile << leaf->getX() << "," << leaf->getY() << "," << leaf->getDataPointer()->value[0] << "\n";
        }

//        output_test_stream output;
//        std::ifstream test_stream;
//        test_stream.open("../Libraries/GraphLibrary/tests/data/data.csv");
//        BOOST_TEST(true);
    }

//    BOOST_AUTO_TEST_CASE(testdensityplot) {
//        std::string content((std::istreambuf_iterator<char>(test_stream)),
//                            (std::istreambuf_iterator<char>()));
//        std::shared_ptr<dp::Empty_Config> config = std::make_shared<dp::Empty_Config>();
//        std::shared_ptr<Test2TreeWithRecursiveComputation<dp::TestDensity, dp::Empty_Config>> root = std::make_shared<Test2TreeWithRecursiveComputation<dp::TestDensity, dp::Empty_Config>>(
//                2.5,
//                2.5,
//                5.0,
//                5.0,
//                config);
//
//        root->compute();
//        root->balance_tree(true);
//        for (int k = 0; k < 5; k++) {
//            for (const auto &i: root->get_all_leafs()) {
//                i->data->compute();
//            }
//            root->balance_tree();
//        }
//        for (const auto &i: root->get_all_leafs()) {
//            i->data->compute();
//        }
//        for (const auto &i: root->get_all_leafs()) {
//            output << i->data->configuration->x << "," << i->data->configuration->y << "," << i->data->value[0] << "\n";
//        }
//        BOOST_TEST(output.is_equal(content));
//    }

} // dp