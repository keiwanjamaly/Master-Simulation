//
// Created by Keiwan Jamaly on 26.10.22.
//

#include "System.h"
#include <functional>
#include <utility>
#include <memory>

namespace phy {
    System::System(dbl_vec &x_points_,
                   std::function<double(double, double)> diffusion_flux,
                   std::function<double(double, double)> source,
                   std::function<double(double, double)> left_boundary,
                   std::function<double(double, double)> right_boundary,
                   bool di) : x_points{x_points_},
                              Q{std::move(diffusion_flux)},
                              S{std::move(source)},
                              lbc{std::move(left_boundary)},
                              rbc{std::move(right_boundary)},
                              difference_implementation{di} {
        N = int(x_points.size());
        if (N == 0 || N == 1) {
            throw std::invalid_argument("The sigma_points vector has one (no) element(s)!");
        }
        dx = (x_points[N - 1] - x_points[0]) / double(N - 1);
    }

    void System::operator()(const dbl_vec &points, dbl_vec &dpointsdt, const double t) {
        // handle diffusion
        double point_x;
        point_x = (points[0] - lbc(points[0], points[1])) / dx;
        double low, high;
        low = Q(t, point_x);
        for (int i = 0; i < N; i++) {
            if (i != N - 1)
                point_x = (points[i + 1] - points[i]) / dx;
            else
                point_x = (rbc(points[N - 2], points[N - 1]) - points[N - 1]) / dx;
            high = Q(t, point_x);
            dpointsdt[i] = (high - low) / (dx);
            low = high;
        }
        // handle source
        if (difference_implementation) {
            low = S(t, x_points[0] - dx * 0.5);
            for (int i = 0; i < N; i++) {
                high = S(t, x_points[i] + dx * 0.5);
                dpointsdt[i] += (high - low) / dx;
                low = high;
            }
        } else {
            for (int i = 0; i < points.size(); i++)
                dpointsdt[i] += S(t, x_points[i]);
        }
    }


} // phy
