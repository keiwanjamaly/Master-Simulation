//
// Created by Keiwan Jamaly on 26.10.22.
//

#include "System.h"
#include <functional>
#include <algorithm>
#include <utility>
#include <memory>

namespace phy {
    Derivative::Derivative(const std::shared_ptr<std::function<double(double, double)>> &left_boundary,
                           const std::shared_ptr<std::function<double(double, double)>> &right_boundary,
                           const dbl_vec &points,
                           double dx) {
        int N = int(points.size());
        div.reserve(N + 2);
        double left = (points[0] - (*left_boundary)(points[0], points[1])) / dx;
        double right = ((*right_boundary)(points[N - 2], points[N - 1]) - points[N - 1]) / dx;
        div.push_back(left);
        for (int i = 0; i < N - 1; i++) {
            div.push_back((points[i + 1] - points[i]) / dx);
        }
        div.push_back(right);
    }

    double &Derivative::operator[](int index) {
        return div[index + 1];
    }

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

    double System::P_j_plus_1_2(double t, Derivative &ux, const int &j) const {
        return Q(t, ux[j]);
    }

    void System::operator()(const dbl_vec &points, dbl_vec &dpointsdt, const double t) {
        Derivative ux(std::make_shared<std::function<double(double, double)>>(lbc),
                      std::make_shared<std::function<double(double, double)>>(rbc), points, dx);
        // handle diffusion
        dbl_vec P_j_plus_1_2_vec;
        P_j_plus_1_2_vec.reserve(ux.div.size());
        for (int i = -1; i <= N - 1; i++)
            P_j_plus_1_2_vec.push_back(P_j_plus_1_2(t, ux, i));
        for (int i = 0; i < N; i++)
            dpointsdt[i] = (P_j_plus_1_2_vec[i + 1] - P_j_plus_1_2_vec[i]) / (dx);

        // handle source
        if (difference_implementation) {
            dbl_vec S_vec;
            S_vec.reserve(ux.div.size());
            S_vec.push_back(S(t, x_points[0] - dx * 0.5));
            for (int i = 0; i <= N - 1; i++)
                S_vec.push_back(S(t, x_points[i] + dx * 0.5));
            for (int i = 0; i < N; i++) {
                double test = (S_vec[i + 1] - S_vec[i]) / (dx);
                dpointsdt[i] += test;
            }
        } else {
            for (int i = 0; i < points.size(); i++)
                dpointsdt[i] += S(t, x_points[i]);
        }
    }


} // phy
