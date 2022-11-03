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

        std::function<double(double, double)> Q;

        std::function<double(double, double)> S;

        std::function<double(double, double)> lbc;

        std::function<double(double, double)> rbc;

        System() = default;

        System(dbl_vec &x_points_,
               std::function<double(double, double)> diffusion_flux,
               std::function<double(double, double)> source,
               std::function<double(double, double)> left_boundary,
               std::function<double(double, double)> right_boundary);

        void operator()(const dbl_vec &points, dbl_vec &dpointsdt,
                        const double t); // NOLINT(readability-avoid-const-params-in-decls)

    private:
        double P_j_plus_1_2(double t, const dbl_vec &points, const int &j) const;
    };

} // phy

#endif //SIMULATION_SYSTEM_H
