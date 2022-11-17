//
// Created by Keiwan Jamaly on 28.10.22.
//
#include <fstream>
#include <boost/test/unit_test.hpp>
#include "Flow.h"
#include "Types_Potential.h"
#include "Get_Test_Data.h"
#include <string>


namespace phy {


    class OnePlusOneTestDetailedFixture {

    public:
        OnePlusOneTestDetailedFixture() {
            std::string filename = "../Libraries/Potential/tests/data/flow_N=2,T=0.1,mu=0.1.json";
            get_test_data(filename, sigma, u_vector, t_vector);

            config = std::make_shared<Configuration>();

            config->Lambda = 1e5;
            config->sigma_max = 6.0;
            config->N_grid = 1000;
            config->N_flavor = 2;
        }

        const double T = 0.1;
        const double mu = 0.1;
        std::shared_ptr<Configuration> config;
        dbl_vec sigma;
        std::vector<dbl_vec> u_vector;
        dbl_vec t_vector;
        std::shared_ptr<Flow> f;

    };

    BOOST_FIXTURE_TEST_CASE(TestSigmaArray, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        BOOST_TEST(sigma.size() == f->sigma_points.size(), tt::tolerance(1e-15));
        for (int i = 0; i < sigma.size(); i++)
            BOOST_TEST(sigma[i] == f->sigma_points[i], tt::tolerance(1e-15));
    }


    BOOST_FIXTURE_TEST_CASE(TestInitialCondition, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        BOOST_TEST(u_vector[0].size() == f->u.size(), tt::tolerance(1e-8));
        for (int i = 0; i < f->u.size(); i++)
            BOOST_TEST(u_vector[1][i] == f->u[i], tt::tolerance(1e-8));

    }

    BOOST_FIXTURE_TEST_CASE(TestSourceTerm, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        BOOST_TEST(f->source()(1.87674, 3.88856) == 1.491985000487865e8 / 2, tt::tolerance(1e-14));
        BOOST_TEST(f->source()(11.7463, 4.59578) == 0.06778105648726529 / 2, tt::tolerance(1e-14));
        BOOST_TEST(f->source()(5.75602, 0.812431) == 63718.16255440156 / 2, tt::tolerance(1e-14));
        BOOST_TEST(f->source()(3.09129, 3.36587) == 1.314678697658328e7 / 2, tt::tolerance(1e-14));
//        EXPECT_NEAR(f->source()(1.87674, 3.88856), -1.237767929469203, 1e-5);
//        EXPECT_NEAR(f->source()(11.7463, 4.59578), -0.00716250554559492, 1e-5);
//        EXPECT_NEAR(f->source()(5.75602, 0.812431), -0.2586023231985309, 1e-5);
//        EXPECT_NEAR(f->source()(3.09129, 3.36587), -1.071389841937635, 1e-5);
    }

    BOOST_FIXTURE_TEST_CASE(TestDiffusionTerm, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        BOOST_TEST(f->diffusion()(1.87674, 3.88856) == -1.864971958479753e7, tt::tolerance(1e-4));
        BOOST_TEST(f->diffusion()(11.7463, 4.59578) == -0.01729131284274761, tt::tolerance(1e-3));
        BOOST_TEST(f->diffusion()(5.75602, 0.812431) == -7964.734848642339, tt::tolerance(1e-4));
        BOOST_TEST(f->diffusion()(3.09129, 3.36587) == -1.643358841565547e6, tt::tolerance(1e-4));
    }

    BOOST_FIXTURE_TEST_CASE(OnePlusOnet1, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[1];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[1][n], tt::tolerance(1e-8));
        }
    }

    BOOST_FIXTURE_TEST_CASE(OnePlusOnet3, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[3];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[3][n], tt::tolerance(1e-6));
        }
    }

    BOOST_FIXTURE_TEST_CASE(OnePlusOnet5, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[5];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[5][n], tt::tolerance(1e-6));
        }
    }

    BOOST_FIXTURE_TEST_CASE(OnePlusOnetLast, OnePlusOneTestDetailedFixture) {
        namespace tt = boost::test_tools;
        config->t_max = t_vector[t_vector.size() - 1];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[t_vector.size() - 1][n], tt::tolerance(1e-5));
        }
    }

// TODO: check that the time gets updated after computation
} // phy