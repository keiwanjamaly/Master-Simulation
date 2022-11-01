//
// Created by Keiwan Jamaly on 28.10.22.
//

#ifndef SIMULATION_FLOW_H
#define SIMULATION_FLOW_H

#include <vector>
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
        double t = 0;
        dbl_vec x_points, u;

        System heat_solver;

        Flow() = default;

        Flow(double mu_, double T_, double Lambda_, double t_max_, int N_flavor_, int N_grid, double sigma_max_);

        void compute();

        dbl_vec splitDecisionData();

        dbl_vec set_initial_condition();

        double (*diffusion())(double, double);

        double (*source())(double, double);

        double (*left_boundary_condition())(double, double);

        double (*right_boundary_condition())(double, double);

        dbl_vec get_minimum();

        dbl_vec get_pressure();

    private:
        double one_over_N;
    };

}

#endif //SIMULATION_FLOW_H
