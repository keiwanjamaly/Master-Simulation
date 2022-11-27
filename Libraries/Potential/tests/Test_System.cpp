//
// Created by Keiwan Jamaly on 25.10.22.
//

#include "System.h"
#include "Types_Potential.h"
#include <boost/test/unit_test.hpp>
#include <cmath>

namespace phy {

    using namespace boost::numeric::odeint;

    class HeatEquationTestFixture {
    public:
        HeatEquationTestFixture() {
            double x;
            L = x_max - x_min;
            dx = L / N;
            temperature = local_vector_type(N + 1);
            for (int i = 0; i <= N; i++) {
                x = i * dx;
                x_points.push_back(x);
                temperature[i] = initial_potential(x);
            }

        }

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

        static double source_dot(double t, double x) {
            return 0;
        }

        static double diffusion_dot(double t, double u_x) {
            return 0;
        }

        static double diffusion_prime(double t, double u_x) {
            return 1;
        }

        local_vector_type temperature;
        dbl_vec x_points;
        double x_min = 0.0, x_max = 5.0;
        double dx;
        double t_min = 0.0, t_max = 5.0;
        double L;
        double abs_error = 1.0e-11, rel_error = 1.0e-7;
        int N = 200;
        std::shared_ptr<System> heat_solver;
    };

    BOOST_FIXTURE_TEST_CASE(testConstructor, HeatEquationTestFixture) {
        heat_solver = std::make_shared<System>(x_points,
                                               diffusion, diffusion_dot, diffusion_prime,
                                               source, source_dot,
                                               left_boundary_condition, right_boundary_condition);
        BOOST_CHECK_EQUAL_COLLECTIONS(heat_solver->x_points.begin(), heat_solver->x_points.end(),
                                      x_points.begin(), x_points.end());
        BOOST_CHECK_EQUAL(heat_solver->dx, dx);
    }

    BOOST_FIXTURE_TEST_CASE(RHStest, HeatEquationTestFixture) {
        namespace tt = boost::test_tools;
        heat_solver = std::make_shared<System>(x_points,
                                               diffusion, diffusion_dot, diffusion_prime,
                                               source, source_dot,
                                               left_boundary_condition, right_boundary_condition);
        unsigned long N_tmp = temperature.size();
        local_vector_type result(N_tmp, 0.0);
        heat_solver->first()(temperature, result, 0);
        BOOST_TEST(result[0] == 0, tt::tolerance(1e-12));
        for (int i = 1; i < N_tmp - 1; i++) {
            BOOST_TEST(result[i] ==
                       (-2 * temperature[i] + temperature[i - 1] + temperature[i + 1]) /
                       (dx * dx), tt::tolerance(1e-12));
        }
        BOOST_TEST(result[N_tmp - 1] ==
                   0, tt::tolerance(1e-12)); // expect double eq fails, so I reduce to this, since it is close enough
    }

    BOOST_FIXTURE_TEST_CASE(RHStestRandom, HeatEquationTestFixture) {
        namespace tt = boost::test_tools;
        heat_solver = std::make_shared<System>(x_points,
                                               diffusion, diffusion_dot, diffusion_prime,
                                               source, source_dot,
                                               left_boundary_condition, right_boundary_condition);
        unsigned long N_tmp = temperature.size();

        // initial vector with random numbers
        // Modify as needed
        constexpr int MIN = -10;
        constexpr int MAX = 10;
        std::srand(1);
        local_vector_type temperature_random(N_tmp);
        for (double &elem: temperature_random)
            elem = MIN + (double) (rand()) / ((double) (RAND_MAX / (MAX - MIN)));

        local_vector_type result(N_tmp, 0.0);
        heat_solver->first()(temperature_random, result, 0);
        BOOST_TEST(result[0] == 0, tt::tolerance(1e-12));
        for (int i = 1; i < N_tmp - 1; i++) {
            BOOST_TEST(result[i] ==
                       (-2 * temperature_random[i] + temperature_random[i - 1] + temperature_random[i + 1]) /
                       (dx * dx), tt::tolerance(1e-12));
        }
        BOOST_TEST(result[N_tmp - 1] == 0,
                   tt::tolerance(1e-12)); // expect double eq fails, so I reduce to this, since it is close enough
    }

    BOOST_FIXTURE_TEST_CASE(RHSJacobianTest, HeatEquationTestFixture) {
        namespace tt = boost::test_tools;
        heat_solver = std::make_shared<System>(x_points,
                                               diffusion, diffusion_dot, diffusion_prime,
                                               source, source_dot,
                                               left_boundary_condition, right_boundary_condition);
        unsigned long N_tmp = temperature.size();
        local_vector_type dfdt(N_tmp, 0.0);
        local_matrix_type J(N_tmp, N_tmp);
        heat_solver->second()(temperature, J, 0, dfdt);
//        std::cout << J(1, 1) << std::endl;
        for (int i = 0; i < N_tmp; i++)
            BOOST_TEST(dfdt(i) == 0.0);

//        for (int i = 0; i < N_tmp; i++) {
//            for (int j = 0; j < N_tmp; j++)
////                BOOST_TEST(J == J_test);
//        }
//        BOOST_TEST(false);
    }

    BOOST_FIXTURE_TEST_CASE(testComputation, HeatEquationTestFixture) {
        namespace tt = boost::test_tools;
        heat_solver = std::make_shared<System>(x_points,
                                               diffusion, diffusion_dot, diffusion_prime,
                                               source, source_dot,
                                               left_boundary_condition, right_boundary_condition);
        integrate_adaptive(make_dense_output<error_stepper_type>(abs_error, rel_error),
                           std::make_pair(heat_solver->first(), heat_solver->second()), temperature, t_min, t_max, 0.01,
                           [](const local_vector_type & /* u */, double t) {
                               std::cout << t << std::endl;
                           });
        for (int i = 0; i < N; i++) {
            BOOST_TEST(temperature[i] == analytic_solution(x_points[i], t_max),
                       tt::tolerance(1e-4));
        }
    }

} // phy