//
// Created by Keiwan Jamaly on 28.10.22.
//

#ifndef SIMULATION_FLOW_H
#define SIMULATION_FLOW_H

#include <vector>
#include <memory>
#include "System.h"
#include "Types_Potential.h"

namespace phy {

    class Flow {
    public:
        double Lambda, t_max;
        double sigma_max;
        int N_grid;
        int N_flavor;
        double y, x;
        double T, mu;
        double t = 0;
        dbl_vec sigma_points, u;

        std::shared_ptr<System> heat_solver;

        Flow() = default;

        Flow(double mu_, double T_, double Lambda_, double t_max_, int N_flavor_, int N_grid, double sigma_max_);

        void compute();

        dbl_vec splitDecisionData();


        std::function<double(double, double)> diffusion();

        std::function<double(double, double)> source();

        std::function<double(double, double)> left_boundary_condition();

        std::function<double(double, double)> right_boundary_condition();

        dbl_vec get_minimum();

        dbl_vec get_pressure();

        void set_initial_condition();


        static double n_b(double val);

        static double n_f(double val);

        static double E_b(double k_val, double u_x_val);

        static double E_f(double k_val, double sigma_val);

        double k(double t_val);

        static double sech(double x);

    private:
        double one_over_N;
    };

}

#endif //SIMULATION_FLOW_H
