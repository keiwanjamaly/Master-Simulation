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

namespace phy {

    void transform_line(std::string &line, const int N, double &t, dbl_vec &x, dbl_vec &y) {
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_any_of(","), boost::token_compress_on);
        t = std::stod(tokens[0]);
        for (int i = 0; i < N; i++)
            x.push_back(std::stod(tokens[i + 1]));
        for (int i = 0; i < N; i++)
            y.push_back(std::stod(tokens[i + 1 + N]));
    }

    TEST(TestPhysicalCases, 1Plus1MF) {
        const double Lambda = 1e5;
        const double T = 0.1;
        const double mu = 0.1;
        const int N_flavor = 2;
        const int N_grid = 1000;
        const double sigma_max = 6.0;
        std::ifstream file("../Libraries/Flow/tests/data/flow_N=2,T=0.1,mu=0.1.txt");
        std::string line;

        dbl_vec sigma;
        std::vector<dbl_vec> sigma_vector;
        dbl_vec u;
        std::vector<dbl_vec> u_vector;
        double t;
        dbl_vec t_vector;
        Flow f;


        while (getline(file, line)) {
            transform_line(line, N_grid, t, sigma, u);


            u_vector.push_back(u);
            sigma_vector.push_back(sigma);
            t_vector.push_back(t);

            sigma.clear();
            u.clear();

            for (int i = 0; i < t_vector.size(); i++) {
                f = Flow(T, mu, Lambda, t_vector[i], N_flavor, N_grid, sigma_max);
                f.compute();
                for (int n = 0; n < N_grid; n++) {
                    EXPECT_NEAR(f.u[n], u_vector[i][n], 1e-4)
                                        << "Vectors differ at index " << i << "for integration time " << t;
                }
            }
        }
    }
} // phy