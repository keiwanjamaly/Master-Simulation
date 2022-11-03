//
// Created by Keiwan Jamaly on 25.10.22.
//

#include "System.h"
#include "Types_Potential.h"
#include "gtest/gtest.h"
#include <cmath>

namespace phy {

    using namespace boost::numeric::odeint;

    class HeatEquationTestFixture : public ::testing::Test {

    protected:
        virtual void SetUp() {
            double x;
            L = x_max - x_min;
            dx = L / N;
            for (int i = 0; i <= N; i++) {
                x = i * dx;
                x_points.push_back(x);
                temperature.push_back(initial_potential(x));
            }

        }

    public:
        double initial_potential(double x) {
            return sin(M_PI / L * x);
        }

        double analytic_solution(double x, double t) {
            return exp(-pow(M_PI / L, 2.0) * t) * initial_potential(x);
        }

        static double diffusion(double t, double u_x) {
            return u_x;
        }

        static double left_boundary_condition(double u0, double u1) {
            return 2 * u0 - u1;
        }

        static double right_boundary_condition(double uN_minus_2, double uN_minus_1) {
            return 2 * uN_minus_1 - uN_minus_2;
        }

        static double source(double t, double x) {
            return 0;
        }

        dbl_vec temperature;
        dbl_vec x_points;
        double x_min = 0.0, x_max = 5.0;
        double dx;
        double t_min = 0.0, t_max = 5.0;
        double L;
        double abs_error = 1.0e-11, rel_error = 1.0e-7;
        int N = 200;
        phy::System heat_solver;
    };

    TEST_F(HeatEquationTestFixture, testConstructor) {
        heat_solver = System(x_points, diffusion, source, left_boundary_condition,
                             right_boundary_condition);
        ASSERT_EQ(heat_solver.x_points, x_points);
        ASSERT_FLOAT_EQ(heat_solver.dx, dx);
    }

    TEST_F(HeatEquationTestFixture, RHStest) {
        heat_solver = System(x_points, diffusion, source, left_boundary_condition,
                             right_boundary_condition);
        unsigned long N_tmp = temperature.size();
        std::vector<double> result(N_tmp, 0.0);
        heat_solver(temperature, result, 0);
        EXPECT_DOUBLE_EQ(result[0], 0);
        for (int i = 1; i < N_tmp - 1; i++) {
            EXPECT_FLOAT_EQ(result[i],
                            (-2 * temperature[i] + temperature[i - 1] + temperature[i + 1]) /
                            (dx * dx)) << "Vectors differ at index " << i;
        }
        EXPECT_NEAR(result[N_tmp - 1], 0,
                    1e-14); // expect double eq fails, so I reduce to this, since it is close enough
    }

    TEST_F(HeatEquationTestFixture, RHStestRandom) {
        heat_solver = System(x_points, diffusion, source, left_boundary_condition,
                             right_boundary_condition);
        unsigned long N_tmp = temperature.size();

        // initial vector with random numbers
        // Modify as needed
        constexpr int MIN = -10;
        constexpr int MAX = 10;
        std::srand(1);
        std::vector<double> temperature_random(N_tmp);
        for (double &elem: temperature_random)
            elem = MIN + (double) (rand()) / ((double) (RAND_MAX / (MAX - MIN)));

        std::vector<double> result(N_tmp, 0.0);
        heat_solver(temperature_random, result, 0);
        EXPECT_DOUBLE_EQ(result[0], 0);
        for (int i = 1; i < N_tmp - 1; i++) {
            EXPECT_FLOAT_EQ(result[i],
                            (-2 * temperature_random[i] + temperature_random[i - 1] + temperature_random[i + 1]) /
                            (dx * dx)) << "Vectors differ at index " << i;
        }
        EXPECT_DOUBLE_EQ(result[N_tmp - 1], 0); // expect double eq fails, so I reduce to this, since it is close enough
    }

    TEST_F(HeatEquationTestFixture, testComputation) {
        heat_solver = System(x_points, diffusion, source, left_boundary_condition,
                             right_boundary_condition);
        integrate_adaptive(make_controlled<error_stepper_type>(abs_error, rel_error),
                           heat_solver, temperature, t_min, t_max, 0.01);
        for (int i = 0; i < N; i++) {
            EXPECT_NEAR(temperature.at(i), analytic_solution(x_points[i], t_max), 1e-5)
                                << "Vectors differ at index " << i;
        }
    }

} // phy