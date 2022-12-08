#include "Heat_Equation_Config_Base.h"
#include "System.h"

#include <boost/test/unit_test.hpp>

namespace phy {

    class TestConfigFixture {
    public:
        TestConfigFixture() {
            config = std::make_shared<Heat_Equation_Config>(t_start, t_final, x_min, x_max, N);
        }

        double t_start = 0.0;
        double t_final = 10.0;
        double x_min = 0.0;
        double x_max = 5.0;
        int N = 200;
        std::shared_ptr<Heat_Equation_Config> config;
    };

    BOOST_FIXTURE_TEST_CASE(TestConfig, TestConfigFixture) {
        BOOST_TEST(t_start == config->get_t());
        BOOST_TEST(t_final == config->get_t_final());
        BOOST_TEST(x_min == config->get_x_min());
        BOOST_TEST(x_max == config->get_x_max());
        BOOST_TEST(N == config->get_N());
        BOOST_TEST((x_max - x_min) / (N - 1) == config->get_dx());
        BOOST_TEST(x_max - x_min == config->get_L());
        BOOST_TEST(1e-5 == config->get_abs_tol());
        BOOST_TEST(1e-10 == config->get_rel_tol());

        auto x_points = config->get_x_points();
        BOOST_TEST(x_min == x_points.front());
        BOOST_TEST(x_max == x_points.back());
        BOOST_TEST(x_min + (x_max - x_min) / (N - 1) == x_points[1]);
        BOOST_TEST(N == x_points.size());
    }


} // phy