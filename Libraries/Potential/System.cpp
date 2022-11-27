//
// Created by Keiwan Jamaly on 26.10.22.
//

#include "System.h"
#include <functional>
#include <utility>
#include <memory>


double delta(int i, int j) {
    if (i == j)
        return 1;
    else
        return 0;
}

namespace phy {
    System::System(dbl_vec &x_points_,
                   std::function<double(double, double)> diffusion_flux,
                   std::function<double(double, double)> diffusion_flux_dot,
                   std::function<double(double, double)> diffusion_flux_prime,
                   std::function<double(double, double)> source,
                   std::function<double(double, double)> source_dot,
                   std::function<double(double, double)> left_boundary,
                   std::function<double(double, double)> right_boundary,
                   bool di) : x_points{x_points_},
                              Q{std::move(diffusion_flux)},
                              Q_dot{std::move(diffusion_flux_dot)},
                              Q_prime{std::move(diffusion_flux_prime)},
                              S{std::move(source)},
                              S_dot{std::move(source_dot)},
                              lbc{std::move(left_boundary)},
                              rbc{std::move(right_boundary)},
                              difference_implementation{di} {
        N = int(x_points.size());
        if (N == 0 || N == 1) {
            throw std::invalid_argument("The sigma_points vector has one (no) element(s)!");
        }
        dx = (x_points[N - 1] - x_points[0]) / double(N - 1);
    }

    std::function<void(const local_vector_type &, local_vector_type &, double)> System::first() {
        return [this](const local_vector_type &u, local_vector_type &dudt, double t) {
            // handle diffusion
            double point_x;
            point_x = (u[0] - lbc(u[0], u[1])) / dx;
            double low, high;
            low = Q(t, point_x);
            for (int i = 0; i < N; i++) {
                if (i != N - 1)
                    point_x = (u[i + 1] - u[i]) / dx;
                else
                    point_x = (rbc(u[N - 2], u[N - 1]) - u[N - 1]) / dx;
                high = Q(t, point_x);
                dudt[i] = (high - low) / (dx);
                low = high;
            }
            // handle source
            if (difference_implementation) {
                low = S(t, x_points[0] - dx * 0.5);
                for (int i = 0; i < N; i++) {
                    high = S(t, x_points[i] + dx * 0.5);
                    dudt[i] += (high - low) / dx;
                    low = high;
                }
            } else {
                for (int i = 0; i < u.size(); i++)
                    dudt[i] += S(t, x_points[i]);
            }
        };
    }

    std::function<void(const local_vector_type &, local_matrix_type &, const double &,
                       local_vector_type &)> System::second() {
        return [this](const local_vector_type &u, local_matrix_type &J, const double &t,
                      local_vector_type &dfdt) -> void {
            double point_x;
            double low, high;
            double low_prime, high_prime;

            // prepare loop
            point_x = (u[0] - lbc(u[0], u[1])) / dx;
            low = Q_dot(t, point_x) + S(t, x_points[0] - dx * 0.5);
            low_prime = Q_prime(t, point_x);

            for (int i = 0; i < dfdt.size(); i++) {
                if (i != N - 1)
                    point_x = (u[i + 1] - u[i]) / dx;
                else
                    point_x = (rbc(u[N - 2], u[N - 1]) - u[N - 1]) / dx;

                // handle t dependence
                high = Q_dot(t, point_x) + S_dot(t, x_points[i] + dx * 0.5);
                dfdt[i] = (high - low) / dx;
                low = high;

                // handle jacobi
                high_prime = Q_prime(t, point_x);
                J(i, i) = -(high_prime + low_prime) / (dx * dx);
                if (i + 1 < N)
                    J(i, i + 1) = high_prime / (dx * dx);
                if (i - 1 >= 0)
                    J(i, i - 1) = low_prime / (dx * dx);
                low_prime = high_prime;

            }

            // handle source
//            if (difference_implementation) {
//                low = S(t, x_points[0] - dx * 0.5);
//                for (int i = 0; i < N; i++) {
//                    high = S_dot(t, x_points[i] + dx * 0.5);
//                    dfdt[i] += (high - low) / dx;
//                    low = high;
//                }
//            } else {
//                for (int i = 0; i < u.size(); i++)
//                    dfdt[i] += S_dot(t, x_points[i]);
//            }

        };
    }


} // phy
