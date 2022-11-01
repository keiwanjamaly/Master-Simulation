//
// Created by Keiwan Jamaly on 28.10.22.
//

#include "gtest/gtest.h"
#include "Flow.h"


namespace phy {


    class TestFlowFixture : public ::testing::Test {
    protected:
        const double mu = 0.1;
        const double T = 0.2;
        const double Lambda = 1e10;
        const double t_max = 20.0;
        const int N_flavor = 2;
        const int N_grid = 200;
        const double sigma_max = 6.0;
    };

    TEST_F(TestFlowFixture, TestConstructor) {
        Flow f(mu, T, Lambda, t_max, N_flavor, N_grid, sigma_max);
        ASSERT_EQ(f.x, mu);
        ASSERT_EQ(f.y, T);
        ASSERT_EQ(f.Lambda, Lambda);
        ASSERT_EQ(f.t_max, t_max);
        ASSERT_EQ(f.N_flavor, N_flavor);
        ASSERT_EQ(f.N_grid, N_grid);
        ASSERT_EQ(f.sigma_max, sigma_max);
        for (int i = 0; i < N_grid; i++)
            EXPECT_EQ(f.x_points[i], sigma_max / N_grid * i) << "x_points are not equal at index " << i;
    }

    TEST_F(TestFlowFixture, TestLeftBoundayCondition) {
        Flow f(mu, T, Lambda, t_max, N_flavor, N_grid, sigma_max);
        ASSERT_EQ(f.left_boundary_condition(0.5, 1.0), -1.0);
        ASSERT_EQ(f.left_boundary_condition(3.2341, 10.3), -10.3);
    }

    TEST_F(TestFlowFixture, TestRightBoundayCondition) {
        Flow f(mu, T, Lambda, t_max, N_flavor, N_grid, sigma_max);
        ASSERT_DOUBLE_EQ(f.right_boundary_condition(4.0, 5.0), 6.0);
        ASSERT_DOUBLE_EQ(f.right_boundary_condition(1001.0, 1002.0), 1003.0);
    }


} // phy