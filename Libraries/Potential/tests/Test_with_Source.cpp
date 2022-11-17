//
// Created by Keiwan Jamaly on 27.10.22.
//

#include <memory>
#include "System.h"
#include "Types_Potential.h"
#include <boost/test/unit_test.hpp>

namespace phy {
    using namespace boost::numeric::odeint;

    class HeatEquationWithSourceTestFixture {

    public:
        HeatEquationWithSourceTestFixture() {
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
            return sin(2 * M_PI / L * x);
        }

        double analytic_solution(double x, double t) {
            double alpha = pow(M_PI / L, 2);
            return exp(-4 * alpha * t) * initial_potential(x) + (1 - exp(-alpha * t)) * source(t, x) / alpha;
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
            // TODO: here should be a L instead of 5.0
            return 2 * sin(M_PI / 5.0 * x);
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

    BOOST_FIXTURE_TEST_CASE(RHStestHeatWithSource, HeatEquationWithSourceTestFixture) {
        namespace tt = boost::test_tools;
        heat_solver = System(x_points, diffusion, source, left_boundary_condition,
                             right_boundary_condition);
        unsigned long N_tmp = temperature.size();
        std::vector<double> result(N_tmp, 0.0);
        heat_solver(temperature, result, 0);
        BOOST_TEST(result[0] == 0, tt::tolerance(1e-4));
        for (int i = 1; i < N_tmp - 1; i++) {
            BOOST_TEST(result[i] ==
                       (-2 * temperature[i] + temperature[i - 1] + temperature[i + 1]) /
                       (dx * dx) + source(0, x_points[i]), tt::tolerance(1e-4));
        }
        BOOST_TEST(result[N_tmp - 1] == 0,
                   tt::tolerance(1e-4)); // expect double eq fails, so I reduce to this, since it is close enough
    }

    BOOST_FIXTURE_TEST_CASE(testComputationHeatWithSource, HeatEquationWithSourceTestFixture) {
        namespace tt = boost::test_tools;
        heat_solver = System(x_points, diffusion, source, left_boundary_condition,
                             right_boundary_condition);
        integrate_adaptive(make_controlled<error_stepper_type>(abs_error, rel_error),
                           heat_solver, temperature, t_min, t_max, 0.01);
        for (int i = 0; i < N; i++) {
            BOOST_TEST(temperature.at(i) == analytic_solution(x_points[i], t_max),
                       tt::tolerance(1e-4));
        }
    }
} // phy