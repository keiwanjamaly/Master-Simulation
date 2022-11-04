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
                // get t value
                std::string_view t_string = element.find_field("label").get_string();
                std::string t_value(t_string);
                t_value.replace(0, 2, "");
                t = std::stod(t_value);
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

    TEST_F(OnePlusOneTestFixture, TestSourceTerm) {
        f = Flow(mu, T, Lambda, t_vector[0], N_flavor, N_grid, sigma_max);
        EXPECT_NEAR(f.source()(1.87674, 3.88856), -1.237767929469203, 1e-5);
        EXPECT_NEAR(f.source()(11.7463, 4.59578), -0.00716250554559492, 1e-5);
        EXPECT_NEAR(f.source()(5.75602, 0.812431), -0.2586023231985309, 1e-5);
        EXPECT_NEAR(f.source()(3.09129, 3.36587), -1.071389841937635, 1e-5);
    }

    TEST_F(OnePlusOneTestFixture, TestDiffusionTerm) {
        f = Flow(mu, T, Lambda, t_vector[0], N_flavor, N_grid, sigma_max);
        EXPECT_NEAR(f.diffusion()(1.87674, 3.88856), -1.864971958479753e7, 1e2);
        EXPECT_NEAR(f.diffusion()(11.7463, 4.59578), -0.01729131284274761, 1e-1);
        EXPECT_NEAR(f.diffusion()(5.75602, 0.812431), -7964.734848642339, 1e1);
        EXPECT_NEAR(f.diffusion()(3.09129, 3.36587), -1.643358841565547e6, 1e2);
    }

    TEST_F(OnePlusOneTestFixture, 1Plus1MFt1) {
        f = Flow(mu, T, Lambda, t_vector[1], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[1][n], 1e-7)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneTestFixture, 1Plus1MFt3) {
        f = Flow(mu, T, Lambda, t_vector[3], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[3][n], 1e-5)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneTestFixture, 1Plus1MFt5) {
        f = Flow(mu, T, Lambda, t_vector[5], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[5][n], 1e-5)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

    TEST_F(OnePlusOneTestFixture, 1Plus1MFtLast) {
        f = Flow(mu, T, Lambda, t_vector[t_vector.size() - 1], N_flavor, N_grid, sigma_max);
        f.compute();
        for (int n = 0; n < N_grid; n++) {
            EXPECT_NEAR(f.u[n], u_vector[t_vector.size() - 1][n], 1e-2)
                                << "Vectors differ at index " << n << " for integration time ";
        }
    }

// TODO: check that the time gets updated after computation
} // phy