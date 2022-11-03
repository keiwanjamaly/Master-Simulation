//
// Created by Keiwan Jamaly on 26.10.22.
//

#include "System.h"

#include <utility>

namespace phy {
    System::System(dbl_vec &x_points_,
                   std::function<double(double, double)> diffusion_flux,
                   std::function<double(double, double)> source,
                   std::function<double(double, double)> left_boundary,
                   std::function<double(double, double)> right_boundary) : x_points{x_points_},
                                                                           Q{std::move(diffusion_flux)},
                                                                           S{std::move(source)},
                                                                           lbc{std::move(left_boundary)},
                                                                           rbc{std::move(right_boundary)} {
        N = int(x_points.size());
        if (N == 0 || N == 1) {
            throw std::invalid_argument("The sigma_points vector has one (no) element(s)!");
        }
        dx = (x_points[N - 1] - x_points[0]) / double(N - 1);
    }

    double System::P_j_plus_1_2(double t, const dbl_vec &u, const int &j) const {
        double derivative;
        if (j == -1)
            derivative = (u[j + 1] - lbc(u[j + 1], u[j + 2])) / dx;
        else if (j == N - 1)
            derivative = (rbc(u[j - 1], u[j]) - u[j]) / dx;
        else
            derivative = (u[j + 1] - u[j]) / dx;

        return Q(t, derivative);
    }

    void System::operator()(const dbl_vec &points, dbl_vec &dpointsdt, const double t) {
        // handle diffusion
        dpointsdt[0] = (P_j_plus_1_2(t, points, 0) - P_j_plus_1_2(t, points, -1)) / (dx);
        for (int i = 1; i < points.size() - 1; i++)
            dpointsdt[i] = (P_j_plus_1_2(t, points, i) - P_j_plus_1_2(t, points, i - 1)) / (dx);
        dpointsdt[N - 1] = (P_j_plus_1_2(t, points, N - 1) - P_j_plus_1_2(t, points, N - 2)) / (dx);

        // handle source
        for (int i = 0; i < points.size(); i++)
            dpointsdt[i] += S(t, x_points[i]);
    }


} // phy
