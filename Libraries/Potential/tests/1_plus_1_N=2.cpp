//
// Created by Keiwan Jamaly on 28.10.22.
//
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "Flow.h"
#include "System.h"
#include "Types_Potential.h"
#include "Get_Test_Data.h"
#include <string>
#include <memory>


namespace phy {

    using std::vector, std::shared_ptr, std::make_shared;


    class OnePlusOneTestDetailedFixture {

    public:
        OnePlusOneTestDetailedFixture() {
            std::string filename = "../Libraries/Potential/tests/data/flow_N=2,T=0.1,mu=0.1.json";
            get_test_data(filename, sigma, u_vector, t_vector);
        }

        const double T = 0.1;
        const double mu = 0.1;
        const double Lambda = 1e5;
        double t_max;
        const double t_start = 0.0;
        const double sigma_min = 0.0;
        const double sigma_max = 6.0;
        const int N_grid = 1000;
        const double N_flavor = 2.0;

        shared_ptr<System> solver;
        shared_ptr<Flow> config;
        vector<double> sigma;
        vector<vector<double>> u_vector;
        vector<double> t_vector;

    };

    BOOST_FIXTURE_TEST_CASE(TestSigmaArray, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[0];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        BOOST_TEST(sigma.size() == config->get_N(), tt::tolerance(1e-15));
        for (int i = 0; i < config->get_N(); i++)
            BOOST_TEST(sigma[i] == config->get_x_points()[i], tt::tolerance(1e-15));
    }


    BOOST_FIXTURE_TEST_CASE(TestInitialCondition, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[0];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = make_shared<System>(config);
        BOOST_TEST(u_vector[0].size() == config->get_N(), tt::tolerance(1e-8));
        for (int i = 0; i < config->get_N(); i++)
            BOOST_TEST(u_vector[1][i] == solver->get_u_pointer()[i], tt::tolerance(1e-8));

    }
//
    BOOST_FIXTURE_TEST_CASE(TestSourceTerm, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[0];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        BOOST_TEST(config->S(1.87674, 3.88856) == 1.491985000487865e8 / 2, tt::tolerance(1e-14));
        BOOST_TEST(config->S(11.7463, 4.59578) == 0.06778105648726529 / 2, tt::tolerance(1e-14));
        BOOST_TEST(config->S(5.75602, 0.812431) == 63718.16255440156 / 2, tt::tolerance(1e-14));
        BOOST_TEST(config->S(3.09129, 3.36587) == 1.314678697658328e7 / 2, tt::tolerance(1e-14));
//        EXPECT_NEAR(f->source()(1.87674, 3.88856), -1.237767929469203, 1e-5);
//        EXPECT_NEAR(f->source()(11.7463, 4.59578), -0.00716250554559492, 1e-5);
//        EXPECT_NEAR(f->source()(5.75602, 0.812431), -0.2586023231985309, 1e-5);
//        EXPECT_NEAR(f->source()(3.09129, 3.36587), -1.071389841937635, 1e-5);
    }

    BOOST_FIXTURE_TEST_CASE(TestDiffusionTerm, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[0];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        BOOST_TEST(config->Q(1.87674, 3.88856) == -1.864971958479753e7, tt::tolerance(1e-4));
        BOOST_TEST(config->Q(11.7463, 4.59578) == -0.01729131284274761, tt::tolerance(1e-3));
        BOOST_TEST(config->Q(5.75602, 0.812431) == -7964.734848642339, tt::tolerance(1e-4));
        BOOST_TEST(config->Q(3.09129, 3.36587) == -1.643358841565547e6, tt::tolerance(1e-4));
    }

    BOOST_FIXTURE_TEST_CASE(OnePlusOnet3, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[3];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = make_shared<System>(config);
        solver->solve();
        for (int n = 0; n < config->get_N(); n++) {
            BOOST_TEST(solver->get_u_pointer()[n] == u_vector[3][n], tt::tolerance(1e-3));
        }
    }


    BOOST_FIXTURE_TEST_CASE(OnePlusOnet5, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[5];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = make_shared<System>(config);
        solver->solve();
        for (int n = 0; n < config->get_N(); n++) {
            BOOST_TEST(solver->get_u_pointer()[n] == u_vector[5][n], tt::tolerance(1e-3));
        }
    }

    BOOST_FIXTURE_TEST_CASE(OnePlusOnetLast, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        t_max = t_vector[t_vector.size() - 1];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = make_shared<System>(config);
        solver->solve();
        for (int n = 0; n < config->get_N(); n++) {
            BOOST_TEST(solver->get_u_pointer()[n] == u_vector[t_vector.size() - 1][n], tt::tolerance(1e-3));
        }
    }

// TODO: check that the time gets updated after computation
} // phy