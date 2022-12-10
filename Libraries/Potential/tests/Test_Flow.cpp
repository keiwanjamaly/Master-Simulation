//
// Created by Keiwan Jamaly on 28.10.22.
//

#include <boost/test/unit_test.hpp>
#include "System.h"
#include "Flow.h"


namespace phy {
    class TestFlowFixture {
    public:
        TestFlowFixture() {
            config = std::make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
            solver = make_shared<System>(config);
        }

        const double mu = 0.1;
        const double T = 0.2;
        const double Lambda = 1e10;
        const double t_max = 20;
        const double t_start = 0.0;
        const double sigma_min = 0.0;
        const double sigma_max = 6.0;
        const int N_grid = 200;
        const double N_flavor = 2.0;

        std::shared_ptr<System> solver;
        std::shared_ptr<Flow> config;
    };

    BOOST_FIXTURE_TEST_CASE(TestConstructor, TestFlowFixture) {
        namespace tt = boost::test_tools;
        BOOST_CHECK_EQUAL(config->get_mu(), mu);
        BOOST_CHECK_EQUAL(config->get_T(), T);
        BOOST_CHECK_EQUAL(solver->get_Config(), config);
        BOOST_CHECK_EQUAL(config->get_t(), 0.0);
        BOOST_CHECK_EQUAL(config->get_rel_tol(), 1.0e-9);
        BOOST_CHECK_EQUAL(config->get_abs_tol(), 1.0e-9);
        BOOST_CHECK_EQUAL(config->get_Lambda(), 1e10);
        BOOST_CHECK_EQUAL(config->get_N_flavor(), 2.0);
    }

    BOOST_FIXTURE_TEST_CASE(TestLeftBoundayCondition, TestFlowFixture) {
        BOOST_CHECK_EQUAL(config->lbc(0.5, 1.0), -1.0);
        BOOST_CHECK_EQUAL(config->lbc(3.2341, 10.3), -10.3);
    }

    BOOST_FIXTURE_TEST_CASE(TestRightBoundayCondition, TestFlowFixture) {
        BOOST_TEST(config->rbc(4.0, 5.0) == 6.0);
        BOOST_TEST(config->rbc(1001.0, 1002.0) == 1003.0);
        BOOST_TEST(config->rbc(90.0, 85.0) == 80.0);
    }

    BOOST_AUTO_TEST_CASE(TestBosonDencity) {
        namespace tt = boost::test_tools;
        BOOST_TEST(Flow::n_b(1.2) == 0.4310127606933332, tt::tolerance(1e-15));
        BOOST_TEST(Flow::n_b(15.324892) == 2.210467147176071e-7, tt::tolerance(1e-15));
    }

    BOOST_AUTO_TEST_CASE(TestFermionEnergy) {
        BOOST_TEST(Flow::E_f(3, 0) == 3);
        BOOST_TEST(Flow::E_f(3, 4) == 5.0);
        BOOST_TEST(Flow::E_f(0, 0) == 0);
    }

    BOOST_AUTO_TEST_CASE(TestBosonEnergy) {
        BOOST_TEST(Flow::E_b(3, 0) == 3);
        BOOST_TEST(Flow::E_b(0, 2) == M_SQRT2);
        BOOST_TEST(Flow::E_b(3, 16) == 5);
    }

    BOOST_FIXTURE_TEST_CASE(TestRGImpulseFunction, TestFlowFixture) {
        namespace tt = boost::test_tools;
        BOOST_TEST(config->t2k(1.1) == 3.328710836980795e9, tt::tolerance(1e-15));
        BOOST_TEST(config->t2k(12.12) == 54494.27503696815, tt::tolerance(1e-15));
        BOOST_TEST(config->t2k(123.123) == 3.375674045869994e-44, tt::tolerance(1e-15));
    }

    BOOST_FIXTURE_TEST_CASE(TestFlowCopy, TestFlowFixture) {
        std::shared_ptr<Flow> newFlow = config->copyAndSetXY(0.3, 0.5);
        BOOST_TEST(newFlow.get() != config.get());
        BOOST_TEST(newFlow->get_T() == 0.5);
        BOOST_TEST(newFlow->get_mu() == 0.3);
        BOOST_TEST(newFlow->get_Lambda() == Lambda);
        BOOST_TEST(newFlow->get_N_flavor() == N_flavor);
        BOOST_TEST(newFlow->get_N() == N_grid);
        BOOST_TEST(newFlow->get_t_final() == t_max);
        BOOST_TEST(newFlow->get_t_start() == t_start);
        BOOST_TEST(newFlow->get_x_min() == sigma_min);
        BOOST_TEST(newFlow->get_x_max() == sigma_max);
    }


} // phy