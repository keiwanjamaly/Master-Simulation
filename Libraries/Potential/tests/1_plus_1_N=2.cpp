//
// Created by Keiwan Jamaly on 28.10.22.
//
#include <fstream>
#include "gtest/gtest.h"
#include "Flow.h"
#include "Types_Potential.h"
#include "Get_Test_Data.h"
#include <string>


namespace phy {


    class OnePlusOneTestDetailedFixture : public ::testing::Test {

    protected:
        virtual void SetUp() {
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

    TEST_F(OnePlusOneTestDetailedFixture, TestSigmaArray) {
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        EXPECT_EQ(sigma.size(), f->sigma_points.size());
        for (int i = 0; i < sigma.size(); i++)
            EXPECT_DOUBLE_EQ(sigma[i], f->sigma_points[i]);
    }


    TEST_F(OnePlusOneTestDetailedFixture, TestInitialCondition) {
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        EXPECT_EQ(u_vector[0].size(), f->u.size());
        for (int i = 0; i < f->u.size(); i++)
            EXPECT_NEAR(u_vector[1][i], f->u[i], 1e-7);

    }

    TEST_F(OnePlusOneTestDetailedFixture, TestSourceTerm) {
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        EXPECT_NEAR(f->source()(1.87674, 3.88856), 1.491985000487865e8, 1e-5);
        EXPECT_NEAR(f->source()(11.7463, 4.59578), 0.06778105648726529, 1e-5);
        EXPECT_NEAR(f->source()(5.75602, 0.812431), 63718.16255440156, 1e-5);
        EXPECT_NEAR(f->source()(3.09129, 3.36587), 1.314678697658328e7, 1e-5);
//        EXPECT_NEAR(f->source()(1.87674, 3.88856), -1.237767929469203, 1e-5);
//        EXPECT_NEAR(f->source()(11.7463, 4.59578), -0.00716250554559492, 1e-5);
//        EXPECT_NEAR(f->source()(5.75602, 0.812431), -0.2586023231985309, 1e-5);
//        EXPECT_NEAR(f->source()(3.09129, 3.36587), -1.071389841937635, 1e-5);
    }

    TEST_F(OnePlusOneTestDetailedFixture, TestDiffusionTerm) {
        config->t_max = t_vector[0];
        f = std::make_shared<Flow>(mu, T, config);
        EXPECT_NEAR(f->diffusion()(1.87674, 3.88856), -1.864971958479753e7, 1e2);
        EXPECT_NEAR(f->diffusion()(11.7463, 4.59578), -0.01729131284274761, 1e-1);
        EXPECT_NEAR(f->diffusion()(5.75602, 0.812431), -7964.734848642339, 1e1);
        EXPECT_NEAR(f->diffusion()(3.09129, 3.36587), -1.643358841565547e6, 1e2);
    }

    TEST_F(OnePlusOneTestDetailedFixture, 1Plus1MFt1) {
        config->t_max = t_vector[1];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            EXPECT_NEAR(f->u[n], u_vector[1][n], 1e-7)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneTestDetailedFixture, 1Plus1MFt3) {
        config->t_max = t_vector[3];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            EXPECT_NEAR(f->u[n], u_vector[3][n], 1e-5)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneTestDetailedFixture, 1Plus1MFt5) {
        config->t_max = t_vector[5];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            EXPECT_NEAR(f->u[n], u_vector[5][n], 1e-5)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneTestDetailedFixture, 1Plus1MFtLast) {
        config->t_max = t_vector[t_vector.size() - 1];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            EXPECT_NEAR(f->u[n], u_vector[t_vector.size() - 1][n], 1e-6)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

// TODO: check that the time gets updated after computation
} // phy