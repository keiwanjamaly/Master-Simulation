//
// Created by Keiwan Jamaly on 28.10.22.
//

#include "gtest/gtest.h"
#include "Flow.h"


namespace phy {
    class TestFlowFixture : public ::testing::Test {
    protected:
        virtual void SetUp() {
            config = std::make_shared<Configuration>();
            config->Lambda = 1e10;
            config->t_max = 20;
            config->sigma_max = 6.0;
            config->N_grid = 200;
            config->N_flavor = 2;
        }

        const double mu = 0.1;
        const double T = 0.2;

        std::shared_ptr<Configuration> config;
    };

    TEST_F(TestFlowFixture, TestConstructor) {
        Flow f(mu, T, config);
        ASSERT_EQ(f.x, mu);
        ASSERT_EQ(f.y, T);
        ASSERT_EQ(f.c, config);
        ASSERT_EQ(f.t, 0.0);
        for (int i = 0; i < config->N_grid; i++)
            EXPECT_DOUBLE_EQ(f.sigma_points[i], config->sigma_max / (config->N_grid - 1) * i)
                                << "sigma_points are not equal at index " << i;
    }

    TEST_F(TestFlowFixture, TestLeftBoundayCondition) {
        Flow f(mu, T, config);
        ASSERT_EQ(f.left_boundary_condition()(0.5, 1.0), -1.0);
        ASSERT_EQ(f.left_boundary_condition()(3.2341, 10.3), -10.3);
    }

    TEST_F(TestFlowFixture, TestRightBoundayCondition) {
        Flow f(mu, T, config);
        ASSERT_DOUBLE_EQ(f.right_boundary_condition()(4.0, 5.0), 6.0);
        ASSERT_DOUBLE_EQ(f.right_boundary_condition()(1001.0, 1002.0), 1003.0);
        ASSERT_DOUBLE_EQ(f.right_boundary_condition()(90.0, 85.0), 80.0);
    }

    TEST(TestStaticFlowFunctions, TestBosonDencity) {
        EXPECT_FLOAT_EQ(Flow::n_b(1.2), 0.4310127606933332);
        EXPECT_FLOAT_EQ(Flow::n_b(15.324892), 2.210467147176071e-7);
    }

    TEST(TestStaticFlowFunctions, TestFermionDencity) {
        EXPECT_FLOAT_EQ(Flow::n_f(0), 1.0 / 2.0);
        EXPECT_FLOAT_EQ(Flow::n_f(15.324892), 2.210466169943501e-7);
    }

    TEST(TestStaticFlowFunctions, TestFermionEnergy) {
        EXPECT_FLOAT_EQ(Flow::E_f(3, 0), 3);
        EXPECT_FLOAT_EQ(Flow::E_f(3, 4), 5.0);
        EXPECT_FLOAT_EQ(Flow::E_f(0, 0), 0);
    }

    TEST(TestStaticFlowFunctions, TestBosonEnergy) {
        EXPECT_FLOAT_EQ(Flow::E_b(3, 0), 3);
        EXPECT_FLOAT_EQ(Flow::E_b(0, 2), M_SQRT2);
        EXPECT_FLOAT_EQ(Flow::E_b(3, 16), 5);
    }

    TEST_F(TestFlowFixture, TestRGImpulseFunction) {
        Flow f(mu, T, config);
        EXPECT_DOUBLE_EQ(f.k(1.1), 3.328710836980795e9);
        EXPECT_DOUBLE_EQ(f.k(12.12), 54494.27503696815);
        EXPECT_DOUBLE_EQ(f.k(123.123), 3.375674045869994e-44);
    }


} // phy