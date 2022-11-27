//
// Created by Keiwan Jamaly on 28.10.22.
//

#include <boost/test/unit_test.hpp>
#include "Flow.h"


namespace phy {
//    class TestFlowFixture {
//    public:
//        TestFlowFixture() {
//            config = std::make_shared<Configuration>();
//            config->Lambda = 1e10;
//            config->t_max = 20;
//            config->sigma_max = 6.0;
//            config->N_grid = 200;
//            config->N_flavor = 2;
//        }
//
//        const double mu = 0.1;
//        const double T = 0.2;
//
//        std::shared_ptr<Configuration> config;
//    };
//
//    BOOST_FIXTURE_TEST_CASE(TestConstructor, TestFlowFixture) {
//        namespace tt = boost::test_tools;
//        Flow f(mu, T, config);
//        BOOST_CHECK_EQUAL(f.x, mu);
//        BOOST_CHECK_EQUAL(f.y, T);
//        BOOST_CHECK_EQUAL(f.c, config);
//        BOOST_CHECK_EQUAL(f.t, 0.0);
//        for (int i = 0; i < config->N_grid; i++)
//            BOOST_TEST(f.sigma_points[i] == config->sigma_max / (config->N_grid - 1) * i,
//                       tt::tolerance(1e-15));
//    }
//
//    BOOST_FIXTURE_TEST_CASE(TestLeftBoundayCondition, TestFlowFixture) {
//        Flow f(mu, T, config);
//        BOOST_CHECK_EQUAL(f.left_boundary_condition()(0.5, 1.0), -1.0);
//        BOOST_CHECK_EQUAL(f.left_boundary_condition()(3.2341, 10.3), -10.3);
//    }
//
//    BOOST_FIXTURE_TEST_CASE(TestRightBoundayCondition, TestFlowFixture) {
//        Flow f(mu, T, config);
//        BOOST_TEST(f.right_boundary_condition()(4.0, 5.0) == 6.0);
//        BOOST_TEST(f.right_boundary_condition()(1001.0, 1002.0) == 1003.0);
//        BOOST_TEST(f.right_boundary_condition()(90.0, 85.0) == 80.0);
//    }
//
//    BOOST_AUTO_TEST_CASE(TestBosonDencity) {
//        namespace tt = boost::test_tools;
//        BOOST_TEST(Flow::n_b(1.2) == 0.4310127606933332, tt::tolerance(1e-15));
//        BOOST_TEST(Flow::n_b(15.324892) == 2.210467147176071e-7, tt::tolerance(1e-15));
//    }
//
//    BOOST_AUTO_TEST_CASE(TestFermionDencity) {
//        namespace tt = boost::test_tools;
//        BOOST_TEST(Flow::n_f(0) == 1.0 / 2.0, tt::tolerance(1e-15));
//        BOOST_TEST(Flow::n_f(15.324892) == 2.210466169943501e-7, tt::tolerance(1e-15));
//    }
//
//    BOOST_AUTO_TEST_CASE(TestFermionEnergy) {
//        BOOST_TEST(Flow::E_f(3, 0) == 3);
//        BOOST_TEST(Flow::E_f(3, 4) == 5.0);
//        BOOST_TEST(Flow::E_f(0, 0) == 0);
//    }
//
//    BOOST_AUTO_TEST_CASE(TestBosonEnergy) {
//        BOOST_TEST(Flow::E_b(3, 0) == 3);
//        BOOST_TEST(Flow::E_b(0, 2) == M_SQRT2);
//        BOOST_TEST(Flow::E_b(3, 16) == 5);
//    }
//
//    BOOST_FIXTURE_TEST_CASE(TestRGImpulseFunction, TestFlowFixture) {
//        namespace tt = boost::test_tools;
//        Flow f(mu, T, config);
//        BOOST_TEST(f.k(1.1) == 3.328710836980795e9, tt::tolerance(1e-15));
//        BOOST_TEST(f.k(12.12) == 54494.27503696815, tt::tolerance(1e-15));
//        BOOST_TEST(f.k(123.123) == 3.375674045869994e-44, tt::tolerance(1e-15));
//    }


} // phy