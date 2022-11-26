//
// Created by Keiwan Jamaly on 04.11.22.
//

#include "Flow.h"
#include <boost/test/unit_test.hpp>
#include "Get_Test_Data.h"
#include <limits>

namespace phy {

    class OnePlusOneMultipleFlowsFixture {
    public:
        OnePlusOneMultipleFlowsFixture() {
            config = std::make_shared<Configuration>();

            config->Lambda = 1e5;
            config->sigma_max = 6.0;
            config->N_grid = 1000;
        }

        double T;
        double mu;
        dbl_vec sigma;
        std::vector<dbl_vec> u_vector;
        std::shared_ptr<Configuration> config;
        dbl_vec t_vector;
        std::shared_ptr<Flow> f;
    };

    BOOST_FIXTURE_TEST_CASE(MeanFieldTest, OnePlusOneMultipleFlowsFixture) {
        namespace tt = boost::test_tools;
        T = 0.0125;
        mu = 0.6;
        std::string filename = "../Libraries/Potential/tests/data/flow_MF_T=0.0125,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        config->N_flavor = std::numeric_limits<double>::infinity();
        config->t_max = t_vector[i];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[i][n], tt::tolerance(1e-1));
        }
    }

    BOOST_FIXTURE_TEST_CASE(N2SmallTemperature, OnePlusOneMultipleFlowsFixture) {
        namespace tt = boost::test_tools;
        T = 0.00625;
        mu = 0.6;
        std::string filename = "../Libraries/Potential/tests/data/flow_N=2,T=0.00625,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        config->N_flavor = 2;
        config->t_max = t_vector[i];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[i][n], tt::tolerance(1e-2));
        }
    }

    BOOST_FIXTURE_TEST_CASE(N16SmallTemperature, OnePlusOneMultipleFlowsFixture) {
        namespace tt = boost::test_tools;
        T = 0.00625;
        mu = 0.6;
        std::string filename = "../Libraries/Potential/tests/data/flow_N=16,T=0.00625,mu=0.6.json";
        get_test_data(filename, sigma, u_vector, t_vector);
        int i = t_vector.size() - 1;
        config->N_flavor = 16;
        config->t_max = t_vector[i];
        f = std::make_shared<Flow>(mu, T, config);
        f->compute();
        for (int n = 0; n < config->N_grid; n++) {
            BOOST_TEST(f->u[n] == u_vector[i][n], tt::tolerance(1e-4));
        }
    }


} // phy
