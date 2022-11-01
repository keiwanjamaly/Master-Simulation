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

        // diffusion_flux
        double (*Q)(double t, double u_x);

        // source
        double (*S)(double t, double x);

        // left and right boundary condition
        double (*lbc)(double u1, double u2);

        double (*rbc)(double u1, double u2);

        System() = default;

        System(dbl_vec &x_points_,
               double (*diffusion_flux)(double t, double u_x),
               double (*source)(double t, double x),
               double (*left_boundary)(double u1, double u2),
               double (*right_boundary)(double u1, double u2));

        void operator()(const dbl_vec &points, dbl_vec &dpointsdt,
                        const double t); // NOLINT(readability-avoid-const-params-in-decls)

    private:
        double P_j_plus_1_2(double t, const dbl_vec &points, const int &j) const;
    };

} // phy

#endif //SIMULATION_SYSTEM_H
