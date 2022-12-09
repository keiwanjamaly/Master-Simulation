//
// Created by Keiwan Jamaly on 04.11.22.
//

#include "Flow.h"
#include "System.h"
#include <boost/test/unit_test.hpp>
#include "Get_Test_Data.h"
#include <limits>

namespace phy {
    using std::vector, std::shared_ptr, std::make_shared;

    class OnePlusOneMultipleFlowsFixture {
    public:
        double T;
        double mu;
        const double Lambda = 1e5;
        double t_max;
        const double t_start = 0.0;
        const double sigma_min = 0.0;
        const double sigma_max = 6.0;
        const int N_grid = 1000;
        double N_flavor;

        shared_ptr<System> solver;
        shared_ptr<Flow> config;
        vector<double> sigma;
        vector<vector<double>> u_vector;
        vector<double> t_vector;
    };

    BOOST_FIXTURE_TEST_CASE(MeanFieldTest, OnePlusOneMultipleFlowsFixture) {
        namespace tt = boost::test_tools;
        std::string filename = "../Libraries/Potential/tests/data/flow_MF_T=0.0125,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        T = 0.0125;
        mu = 0.6;
        N_flavor = std::numeric_limits<double>::infinity();
        t_max = t_vector[i];
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = std::make_shared<System>(config);
        solver->solve();
        for (int n = 0; n < config->get_N(); n++) {
            BOOST_TEST(solver->get_u_pointer()[n] == u_vector[i][n], tt::tolerance(1e-1));
        }
    }

    BOOST_FIXTURE_TEST_CASE(N2SmallTemperature, OnePlusOneMultipleFlowsFixture) {
        namespace tt = boost::test_tools;
        std::string filename = "../Libraries/Potential/tests/data/flow_MF_T=0.0125,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        t_max = t_vector[i];
        T = 0.00625;
        mu = 0.6;
        N_flavor = 2;
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = std::make_shared<System>(config);
        solver->solve();
        for (int n = 0; n < config->get_N(); n++) {
            BOOST_TEST(solver->get_u_pointer()[n] == u_vector[i][n], tt::tolerance(1e-1));
        }
    }

    BOOST_FIXTURE_TEST_CASE(N16SmallTemperature, OnePlusOneMultipleFlowsFixture) {
        namespace tt = boost::test_tools;
        std::string filename = "../Libraries/Potential/tests/data/flow_N=16,T=0.00625,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        N_flavor = 16;
        int i = t_vector.size() - 1;
        t_max = t_vector[i];
        T = 0.00625;
        mu = 0.6;
        N_flavor = 2;
        config = make_shared<Flow>(mu, T, Lambda, N_flavor, t_start, t_max, sigma_min, sigma_max, N_grid);
        solver = std::make_shared<System>(config);
        solver->solve();
        for (int n = 0; n < config->get_N(); n++) {
            BOOST_TEST(solver->get_u_pointer()[n] == u_vector[i][n], tt::tolerance(1e-1));
        }
    }


} // phy