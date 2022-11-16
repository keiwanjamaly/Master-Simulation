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

    class Configuration {
    public:
        double Lambda, t_max;
        double sigma_max;
        int N_grid;
        double N_flavor;
    };

    class Flow {
    public:
        double y, x;
        double T, mu;
        double t = 0;
        int i = 0;
        dbl_vec sigma_points, u;
        std::shared_ptr<Configuration> c;

        std::shared_ptr<System> heat_solver;

        Flow() = default;

        Flow(double mu_, double T_, std::shared_ptr<Configuration> c_);

        void compute();

        dbl_vec splitDecisionData();

        std::function<double(double, double)> diffusion();

        std::function<double(double, double)> source();

        static std::function<double(double, double)> left_boundary_condition();

        static std::function<double(double, double)> right_boundary_condition();

        dbl_vec get_minimum();

        dbl_vec get_pressure();

        void set_initial_condition();

        static double n_b(double val);

        static double n_f(double val);

        static double E_b(double k_val, double u_x_val);

        static double E_f(double k_val, double sigma_val);

        double k(double t_val);

        static double sech(double x);

        std::function<void(const dbl_vec &, const double)> observer(std::ostream &m_out);
    };

}

#endif //SIMULATION_FLOW_H
