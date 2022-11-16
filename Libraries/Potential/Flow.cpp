//
// Created by Keiwan Jamaly on 28.10.22.
//

#include "Flow.h"
#include <cmath>

using namespace boost::numeric::odeint;

namespace phy {

    Flow::Flow(double mu_, double T_, std::shared_ptr<Configuration> c_) :
            x{mu_}, y{T_}, c{c_} {
        sigma_points.reserve(c->N_grid);
        for (int i = 0; i < c->N_grid; i++)
            sigma_points.push_back(i * c->sigma_max / (c->N_grid - 1));
        heat_solver = std::make_shared<System>(sigma_points, diffusion(), source(), left_boundary_condition(),
                                               right_boundary_condition());
        set_initial_condition();
        T = y;
        mu = x;
    }

    std::function<double(double, double)> Flow::left_boundary_condition() {
        return [](double u0, double u1) -> double {
            return -u1;
        };
    }

    std::function<double(double, double)> Flow::right_boundary_condition() {
        return [](double u_N_minus_2, double u_N_minus_1) -> double {
            return 2 * u_N_minus_1 - u_N_minus_2;
        };
    }

    std::function<double(double, double)> Flow::diffusion() {
        return [this](double t_val, double u_x) -> double {
            auto test = c;
            if (std::isinf(c->N_flavor))
                return 0;
            double E = E_b(k(t_val), u_x);
            if (std::isnan(E))
                throw std::runtime_error("There is a shock wave in the system!");
            double return_value = -pow(k(t_val), 3) * (1 + 2 * n_b(E / T)) /
                                  (M_PI * c->N_flavor * 2 * E);

            return return_value;
        };
    }

    std::function<double(double, double)> Flow::source() {
        return [this](double t_val, double sigma) -> double {
            double E = E_f(k(t_val), sigma);
            double b = 1 / T; // betta
            double plus_term = b * E * (pow(sech(b * (E - mu) / 2), 2) + pow(sech(b * (E + mu) / 2), 2));
            double minus_term = 2 * (tanh(b * (E - mu) / 2) + tanh(b * (E + mu) / 2));
            double return_value = pow(k(t_val), 3) / (4 * M_PI * pow(E, 3)) * sigma * (plus_term - minus_term);
            return return_value;
        };
    }

    void Flow::compute() {
        integrate_adaptive(make_controlled<error_stepper_type>(1.0e-10, 1.0e-10),
                           *heat_solver, u, t, c->t_max, 0.01, observer(std::cout));
    }

    std::function<void(const dbl_vec &, const double)> Flow::observer(std::ostream &m_out) {
        return [this](const dbl_vec &u_points, const double t_val) -> void {
            i++;
            if (i % 300 == 0)
                std::cout << std::setprecision(4) << "Currently at t = " << t_val << " (k=" << k(t_val) << ")"
                          << std::endl;
        };
    }

    void Flow::set_initial_condition() {
        u.clear();
        u.reserve(sigma_points.size());
        double value = sqrt(1.0 + 1 / pow(c->Lambda, 2));
        double multiplier = (atanh(1 / value) - 1 / value) / M_PI;
        for (double &sigma: sigma_points) {
            u.push_back(sigma * multiplier);
        }
    }

    double Flow::n_b(double val) {
        return 1 / (exp(val) - 1);
    }

    double Flow::n_f(double val) {
        return 1 / (exp(val) + 1);
    }

    double Flow::E_b(double k_val, double u_x_val) {
        return sqrt(pow(k_val, 2) + u_x_val);
    }

    double Flow::E_f(double k_val, double sigma_val) {
        return sqrt(pow(k_val, 2) + pow(sigma_val, 2));
    }

    double Flow::k(double t_val) {
        return c->Lambda * exp(-t_val);
    }

    double Flow::sech(double x) {
        return 1 / cosh(x);
    }


}