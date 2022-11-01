//
// Created by Keiwan Jamaly on 28.10.22.
//

#include "Flow.h"

using namespace boost::numeric::odeint;

namespace phy {

    Flow::Flow(double mu_, double T_, double Lambda_, double t_max_, int N_flavor_, int N_grid, double sigma_max_) {
        heat_solver = System(x_points, diffusion(), source(), left_boundary_condition(), right_boundary_condition());
        System(x_points, diffusion(), source(), left_boundary_condition(), right_boundary_condition());
    }

}