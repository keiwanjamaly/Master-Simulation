//
// Created by Keiwan Jamaly on 28.10.22.
//
#include <fstream>
#include "gtest/gtest.h"
#include "Flow.h"
#include "Types_Potential.h"
#include <string>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "simdjson.h"

using namespace simdjson; // optional

namespace phy {


    class OnePlusOneTestFixture : public ::testing::Test {

    protected:
        virtual void SetUp() {
            std::string filename = "../Libraries/Potential/tests/data/flow_N=2,T=0.1,mu=0.1.json";

            auto json = padded_string::load(filename);
            ondemand::document doc = parser.iterate(json); // position a pointer at the beginning of the JSON data

            auto graphs = doc.find_field("graphs").get_array();
            int experiments = graphs.count_elements();

//            for (int i = 0; i < experiments; i += 2) {
            for (auto element: graphs) {
                sigma.clear();
                u.clear();
                // store sigma values
                for (auto x_val: element.find_field("x").get_array()) {
                    sigma.push_back(x_val.get_double());
                }
                // store u values
                for (auto y_val: element.find_field("y").get_array()) {
                    u.push_back(y_val.get_double());
                }
                u_vector.push_back(u);
                t_vector.push_back(t);
            }
        }

        static void transform_line(std::string &line, const int N, double &t, dbl_vec &x, dbl_vec &y) {
            std::vector<std::string> tokens;
            boost::split(tokens, line, boost::is_any_of(","), boost::token_compress_on);
            t = std::stod(tokens[0]);
            for (int i = 0; i < N; i++)
                x.push_back(std::stod(tokens[i + 1]));
            for (int i = 0; i < N; i++)
                y.push_back(std::stod(tokens[i + 1 + N]));
        }

        const double Lambda = 1e5;
        const double T = 0.1;
        const double mu = 0.1;
        const int N_flavor = 2;
        const int N_grid = 1000;
        const double sigma_max = 6.0;
        dbl_vec sigma;
        dbl_vec u;
        std::vector<dbl_vec> u_vector;
        double t = 0;
        dbl_vec t_vector;
        Flow f;
        ondemand::parser parser;
    };

    TEST_F(OnePlusOneTestFixture, TestSigmaArray) {
        f = Flow(mu, T, Lambda, t_vector[0], N_flavor, N_grid, sigma_max);
        EXPECT_EQ(sigma.size(), f.sigma_points.size());
        for (int i = 0; i < sigma.size(); i++)
            EXPECT_DOUBLE_EQ(sigma[i], f.sigma_points[i]);
    }


    TEST_F(OnePlusOneTestFixture, TestInitialCondition) {
        f = Flow(mu, T, Lambda, t_vector[0], N_flavor, N_grid, sigma_max);
        EXPECT_EQ(u_vector[0].size(), f.u.size());
        for (int i = 0; i < f.u.size(); i++)
            EXPECT_NEAR(u_vector[1][i], f.u[i], 1e-7);

    }

//    TEST_F(OnePlusOneTestFixture, 1Plus1MF) {
//
//
//        for (int i = 0; i < t_vector.size(); i++) {
//            f = Flow(T, mu, Lambda, t_vector[i], N_flavor, N_grid, sigma_max);
//            f.compute();
//            for (int n = 0; n < N_grid; n++) {
//                EXPECT_NEAR(f.u[n], u_vector[i][n], 1e-4)
//                                    << "Vectors differ at index " << i << "for integration time " << t;
//            }
//
//        }
//    }
} // phy