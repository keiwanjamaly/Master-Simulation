//
// Created by Keiwan Jamaly on 26.10.22.
//

#include "System.h"

namespace phy {
    System::System(grid &x_points_,
                   double (*diffusion_flux)(double u, double u_x), double (*left_boundary)(double u1, double u2),
                   double (*right_boundary)(double u1, double u2)) : x_points{x_points_}, Q{diffusion_flux},
                                                                     lbc{left_boundary},
                                                                     rbc{right_boundary} {
        N = int(x_points.size());
        dx = (x_points[N - 1] - x_points[0]) / double(N - 1);
    }

    double System::P_j_plus_1_2(double t, const grid &u, const int &j) {
        double derivative;
        if (j == -1)
            derivative = (u[j + 1] - lbc(u[j + 1], u[j + 2])) / dx;
        else if (j == N - 1)
            derivative = (rbc(u[j - 1], u[j]) - u[j]) / dx;
        else
            derivative = (u[j + 1] - u[j]) / dx;

        return Q(t, derivative);
    }

    void System::operator()(const grid &points, grid &dpointsdt, const double t) {
        dpointsdt[0] = (P_j_plus_1_2(t, points, 0) - P_j_plus_1_2(t, points, -1)) / (dx);
        for (int i = 1; i < points.size() - 1; i++)
            dpointsdt[i] = (P_j_plus_1_2(t, points, i) - P_j_plus_1_2(t, points, i - 1)) / (dx);
        dpointsdt[N - 1] = (P_j_plus_1_2(t, points, N - 1) - P_j_plus_1_2(t, points, N - 2)) / (dx);
    }
} // phy
