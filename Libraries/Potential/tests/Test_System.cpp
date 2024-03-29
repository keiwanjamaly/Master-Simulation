//
// Created by Keiwan Jamaly on 25.10.22.
//

#include "System.h"
#include "Heat_Equation_Config_Base.h"
#include <boost/test/unit_test.hpp>
#include <cmath>

namespace phy {

    using std::shared_ptr, std::make_shared;

    class HeatEquationTestFixture {
    public:
        HeatEquationTestFixture() {
            config = std::make_shared<Heat_Equation_Config>(t_start, t_final, x_min, x_max, N);
            heat_solver = make_shared<System>(config);
            vec1 = N_VNew_Serial(config->get_N(), context_1);
            vec2 = N_VNew_Serial(config->get_N(), context_2);
        }

        ~HeatEquationTestFixture() {
            N_VDestroy(vec1);
            N_VDestroy(vec2);
        }

        sunrealtype t_start = RCONST(0.0);
        sunrealtype t_final = RCONST(2.0);
        sunrealtype x_min = RCONST(0.0);
        sunrealtype x_max = RCONST(5.0);
        int N = 11;
        std::shared_ptr<Heat_Equation_Config> config;
        std::shared_ptr<System> heat_solver;
        N_Vector vec1, vec2;
        sundials::Context context_3, context_2, context_1;
    };

    BOOST_FIXTURE_TEST_CASE(testConstructor, HeatEquationTestFixture) {
        // test config
        BOOST_TEST(heat_solver->get_Config() == config);
        // setup N_Vector
        auto x_points = config->get_x_points();
        auto u = heat_solver->get_u_pointer();
        for (int i = 0; i < N; i++)
            BOOST_TEST(config->initial_condition(x_points[i]) == u[i]);
        // setup of Band matrix
        // setup of ERK memory structure
        BOOST_TEST(heat_solver->get_erk_mem());
        // setup of Tolerances
        BOOST_TEST(heat_solver->get_set_flag_SStolerances() == ARK_SUCCESS);
        // setup of user data
        BOOST_TEST(heat_solver->get_flag_SetUserData() == ARK_SUCCESS);
        // set max steps
        BOOST_TEST(heat_solver->get_flag_SetMaxSteps() == ARK_SUCCESS);

    }

    BOOST_FIXTURE_TEST_CASE(RHStest, HeatEquationTestFixture) {
        // test setup
        namespace tt = boost::test_tools;
        realtype *u_data = heat_solver->get_u_pointer();
        sunrealtype dx = config->get_dx();

        // run calculation
        heat_solver->f(0.0, heat_solver->get_u(), vec1, (void *) config.get());

        //test
        realtype *result_data = N_VGetArrayPointer(vec1);
        BOOST_TEST(result_data[0] == 0, tt::tolerance(1e-12));
        for (int i = 1; i < config->get_N() - 1; i++) {
            BOOST_TEST(result_data[i] ==
                       (-2 * u_data[i] + u_data[i - 1] + u_data[i + 1]) /
                       (dx * dx), tt::tolerance(1e-12));
        }
        BOOST_TEST(result_data[config->get_N() - 1] ==
                   0, tt::tolerance(1e-12)); // expect double eq fails, so I reduce to this, since it is close enough
    }

    BOOST_FIXTURE_TEST_CASE(RHStestRandom, HeatEquationTestFixture) {
        // test setup
        namespace tt = boost::test_tools;
        realtype *u_data = heat_solver->get_u_pointer();
        sunrealtype dx = config->get_dx();
        realtype *input_data = N_VGetArrayPointer(vec1);

        // initial vector with random numbers
        constexpr int MIN = -10;
        constexpr int MAX = 10;
        std::srand(1);
        for (int i = 0; i < N; i++)
            input_data[i] = MIN + (sunrealtype) (rand()) / ((sunrealtype) (RAND_MAX / (MAX - MIN)));

        // run calculation
        heat_solver->f(0.0, vec1, vec2, (void *) config.get());

        // test
        realtype *result_data = N_VGetArrayPointer(vec2);
        BOOST_TEST(result_data[0] == 0, tt::tolerance(1e-12));
        for (int i = 1; i < config->get_N() - 1; i++) {
            BOOST_TEST(result_data[i] ==
                       (-2 * input_data[i] + input_data[i - 1] + input_data[i + 1]) /
                       (dx * dx), tt::tolerance(1e-12));
        }
        BOOST_TEST(result_data[config->get_N() - 1] == 0,
                   tt::tolerance(1e-12)); // expect double eq fails, so I reduce to this, since it is close enough
    }


    BOOST_FIXTURE_TEST_CASE(testComputation, HeatEquationTestFixture) {
        namespace tt = boost::test_tools;
        auto x_points = config->get_x_points();

        heat_solver->solve();

        realtype *u = heat_solver->get_u_pointer();

        for (int i = 0; i < config->get_N() - 1; i++) {
            BOOST_TEST(u[i] == config->analytic_solution(config->get_t_final(), x_points[i]),
                       tt::tolerance(1e-1));
        }
        BOOST_CHECK_SMALL(u[config->get_N() - 1], 1e-5);
    }

} // phy