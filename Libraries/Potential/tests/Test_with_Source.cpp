//
// Created by Keiwan Jamaly on 27.10.22.
//

#include <memory>
#include "System.h"
#include "Heat_Equation_Config_Base.h"
#include <boost/test/unit_test.hpp>

namespace phy {
    using std::shared_ptr, std::make_shared;

    class HeatEquationWithSourceTestFixture {

    public:
        HeatEquationWithSourceTestFixture() {
            config = std::make_shared<Heat_Equation_With_Source_Config>(t_start, t_final, x_min, x_max, N);
            heat_solver = make_shared<System>(config);
            vec1 = N_VNew_Serial(config->get_N(), context_1);
        }

        ~HeatEquationWithSourceTestFixture() {
            N_VDestroy(vec1);
        }

    public:
        sunrealtype t_start = RCONST(0.0);
        sunrealtype t_final = RCONST(2.0);
        sunrealtype x_min = RCONST(0.0);
        sunrealtype x_max = RCONST(5.0);
        int N = 11;
        std::shared_ptr<Heat_Equation_With_Source_Config> config;
        std::shared_ptr<System> heat_solver;
        N_Vector vec1;
        sundials::Context context_1;
    };

    BOOST_FIXTURE_TEST_CASE(RHStestHeatWithSource, HeatEquationWithSourceTestFixture) {
        // test setup
        namespace tt = boost::test_tools;
        realtype *u_data = heat_solver->get_u_pointer();
        sunrealtype dx = config->get_dx();

        // run calculation
        heat_solver->f(0.0, heat_solver->get_u(), vec1, (void *) config.get());

        //test
        realtype *result_data = N_VGetArrayPointer(vec1);
        BOOST_TEST(result_data[0] == 0, tt::tolerance(1e-4));
        for (int i = 1; i < config->get_N() - 1; i++) {
            BOOST_TEST(result_data[i] ==
                       (-2 * u_data[i] + u_data[i - 1] + u_data[i + 1]) /
                       (dx * dx) + config->S(0, config->get_x_points()[i]), tt::tolerance(1e-4));
        }
        BOOST_TEST(result_data[config->get_N() - 1] == 0,
                   tt::tolerance(1e-4)); // expect double eq fails, so I reduce to this, since it is close enough
    }

    BOOST_FIXTURE_TEST_CASE(testComputationHeatWithSource, HeatEquationWithSourceTestFixture) {
        namespace tt = boost::test_tools;
        auto x_points = config->get_x_points();

        heat_solver->solve();

        realtype *u = heat_solver->get_u_pointer();

        for (int i = 0; i < config->get_N() - 1; i++) {
            BOOST_TEST(u[i] == config->analytic_solution(config->get_t_final(), x_points[i]),
                       tt::tolerance(1e-2));
        }
        BOOST_CHECK_SMALL(u[config->get_N() - 1], 1e-4);
    }
} // phy