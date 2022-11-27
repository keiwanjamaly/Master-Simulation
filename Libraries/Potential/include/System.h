//
// Created by Keiwan Jamaly on 25.10.22.
//

#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H

#include "Types_Potential.h"


namespace phy {

    class System {
    public:
        double dx;
        int N;
        dbl_vec x_points;
        bool difference_implementation;

        typedef typename std::function<void(const local_vector_type &, local_vector_type &, double)> first_type;
        typedef typename std::function<void(const local_vector_type &, local_matrix_type &, const double &,
                                            local_vector_type &)> second_type;

        std::function<double(double, double)> Q;

        std::function<double(double, double)> Q_dot;

        std::function<double(double, double)> Q_prime;

        std::function<double(double, double)> S;

        std::function<double(double, double)> S_dot;

        std::function<double(double, double)> lbc;

        std::function<double(double, double)> rbc;

        System() = delete;

        System(dbl_vec &x_points_,
               std::function<double(double, double)> diffusion_flux,
               std::function<double(double, double)> diffusion_flux_dot,
               std::function<double(double, double)> diffusion_flux_prime,
               std::function<double(double, double)> source,
               std::function<double(double, double)> source_dot,
               std::function<double(double, double)> left_boundary,
               std::function<double(double, double)> right_boundary,
               bool di = false);

        std::function<void(const local_vector_type &, local_vector_type &, double)> first();

        std::function<void(const local_vector_type &, local_matrix_type &, const double &,
                           local_vector_type &)> second();
    };

} // phy

#endif //SIMULATION_SYSTEM_H
