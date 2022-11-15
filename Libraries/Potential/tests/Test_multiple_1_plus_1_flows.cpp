//
// Created by Keiwan Jamaly on 04.11.22.
//

#include "Flow.h"
#include "gtest/gtest.h"
#include "Get_Test_Data.h"
#include <limits>

namespace phy {

    class OnePlusOneMultipleFlowsFixture : public ::testing::Test {
    protected:
        const double Lambda = 1e5;
        double T;
        double mu;
        double N_flavor;
        const int N_grid = 1000;
        const double sigma_max = 6.0;
        dbl_vec sigma;
        std::vector<dbl_vec> u_vector;
        dbl_vec t_vector;
        Flow f;
    };

    TEST_F(OnePlusOneMultipleFlowsFixture, MeanFieldTest) {
        T = 0.0125;
        mu = 0.6;
        N_flavor = std::numeric_limits<double>::infinity();
        std::string filename = "../Libraries/Potential/tests/data/flow_MF_T=0.0125,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        f = Flow(mu, T, Lambda, t_vector[i], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[i][n], 1e-4)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneMultipleFlowsFixture, N2SmallTemperature) {
        T = 0.00625;
        mu = 0.6;
        N_flavor = 2;
        std::string filename = "../Libraries/Potential/tests/data/flow_N=2,T=0.00625,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        f = Flow(mu, T, Lambda, t_vector[i], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[i][n], 1e-5)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneMultipleFlowsFixture, N16SmallTemperature) {
        T = 0.00625;
        mu = 0.6;
        N_flavor = 16;
        std::string filename = "../Libraries/Potential/tests/data/flow_N=16,T=0.00625,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        f = Flow(mu, T, Lambda, t_vector[i], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[i][n], 1e-5)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }


} // phy
