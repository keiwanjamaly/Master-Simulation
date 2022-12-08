//
// Created by Keiwan Jamaly on 28.10.22.
//

#ifndef SIMULATION_FLOW_H
#define SIMULATION_FLOW_H

#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include "Config.h"
#include "Types_Potential.h"

namespace phy {

    class Flow : public Config_Base {
    public:
        Flow(sunrealtype mu, sunrealtype T, sunrealtype Lambda, sunrealtype N_flavor, sunrealtype t,
             sunrealtype t_final, sunrealtype x_min, sunrealtype x_max,
             int N) : m_mu{mu}, m_T{T}, m_Lambda{Lambda}, m_N_flavor{N_flavor}, Config_Base(t, t_final,
                                                                                            x_min,
                                                                                            x_max,
                                                                                            N, 1.0e-3, 1.0e-3) {}

        sunrealtype initial_condition(sunrealtype sigma) final {
            double value = sqrt(1.0 + 1 / pow(m_Lambda, 2));
            double multiplier = (atanh(1 / value) - 1 / value) / M_PI;
            return sigma * multiplier;
        }

        sunrealtype Q(sunrealtype t, sunrealtype ux) const final {
            if (std::isinf(m_N_flavor))
                return 0;
            else {
                double k = t2k(t);
                double E = E_b(k, ux);
                double b = 1 / m_T; // beta
//                if (std::isnan(E))
//                    throw std::runtime_error("There is a shock wave in the system!");
                double return_value = -pow(k, 3) * coth(E * b / 2) /
                                      (M_PI * m_N_flavor * 2 * E);
//                if (std::isnan(return_value))
//                    throw std::runtime_error("non value here");
                return return_value;
            }
        }

        sunrealtype Q_prime(sunrealtype t, sunrealtype ux) const {
            if (std::isinf(m_N_flavor))
                return 0;
            else {
                double k = t2k(t);
                double E = E_b(k, ux);
                double b = 1. / m_T; // beta
                if (std::isnan(E))
                    throw std::runtime_error("There is a shock wave in the system!");
//                double return_value = -pow(k, 3) * (1 + 2 * n_b(E / m_T)) /
//                                      (M_PI * m_N_flavor * 2 * E);
                double left = -Q(t, ux) / (2 * E * E);
//                double one = pow(k, 3.0);
//                double two = exp(b * E);
//                double three = pow(n_b(E * b), 2.0);
                double right =
                        -(pow(k, 3.0) * b * pow(csch(E * b / 2), 2.0)) / (8 * m_N_flavor * M_PI * pow(E, 3.0));
                double return_value = left + right;
//                if (std::isnan(return_value))
//                    throw std::runtime_error("non value here");
                return return_value;
            }
        }

        sunrealtype S(sunrealtype t, sunrealtype sigma) const final {
            double k = t2k(t);
            double E = E_f(k, sigma);
            double b = 1 / m_T; // beta
//            double plus_term = b * E * (pow(sech(b * (E - mu) / 2), 2) + pow(sech(b * (E + mu) / 2), 2));
//            double minus_term = 2 * (tanh(b * (E - mu) / 2) + tanh(b * (E + mu) / 2));
//            double return_value = pow(k(t_val), 3) / (4 * M_PI * pow(E, 3)) * sigma * (plus_term - minus_term);
//            return return_value;
            double return_value =
                    pow(k, 3) / (2 * M_PI * E) * (tanh(b * (E - m_mu) * 0.5) + tanh(b * (E + m_mu) * 0.5));
//            if (std::isnan(return_value))
//                throw std::runtime_error("non value here");
            return return_value;
        }

        Implementation S_Implementation() const final {
            return numerically;
        }

        sunrealtype t2k(sunrealtype t) const {
            return m_Lambda * exp(-t);
        }

        static sunrealtype E_b(sunrealtype k, sunrealtype ux) {
            return sqrt(pow(k, 2) + ux);
        }

        static sunrealtype E_f(sunrealtype k_val, sunrealtype sigma_val) {
            return sqrt(pow(k_val, 2) + pow(sigma_val, 2));
        }

        static sunrealtype n_b(sunrealtype val) {
            return 1 / (exp(val) - 1);
        }

        static sunrealtype coth(sunrealtype val) {
            return 1 / tanh(val);
        }

        static sunrealtype csch(sunrealtype val) {
            return 1 / sinh(val);
        }

        sunrealtype lbc(sunrealtype u0, sunrealtype u1) final {
            return -u1;
        }

        sunrealtype rbc(sunrealtype u_N_minus_2, sunrealtype u_N_minus_1) final {
            return 2 * u_N_minus_1 - u_N_minus_2;
        }

        sunrealtype get_T() const { return m_T; };

        sunrealtype get_mu() const { return m_mu; };

        sunrealtype get_Lambda() const { return m_Lambda; };

        sunrealtype get_N_flavor() const { return m_N_flavor; };

        void monitor(sunrealtype t) const final {
            std::cout << "t = " << t << "\t k = " << t2k(t) << "\n";
        }

    private:
        sunrealtype m_T, m_mu;
        sunrealtype m_Lambda;
        sunrealtype m_N_flavor;
    };

//    class Configuration {
//    public:
//        double Lambda, t_max;
//        double sigma_max;
//        int N_grid;
//        double N_flavor;
//    };
//
//    class Flow {
//    public:
//        double y, x;
//        double T, mu;
//        double t = 0;
//        int i = 0;
//        dbl_vec sigma_points, u;
//        std::shared_ptr<Configuration> c;
//
//        std::shared_ptr<System> heat_solver;
//
//        Flow() = default;
//
//        Flow(double mu_, double T_, std::shared_ptr<Configuration> c_);
//
//        void compute();
//
//        dbl_vec splitDecisionData();
//
//        std::function<double(double, double)> diffusion();
//
//        std::function<double(double, double)> source();
//
//        static std::function<double(double, double)> left_boundary_condition();
//
//        static std::function<double(double, double)> right_boundary_condition();
//
//        dbl_vec get_minimum();
//
//        dbl_vec get_pressure();
//
//        void set_initial_condition();
//
//        static double n_b(double val);
//
//        static double n_f(double val);
//
//        static double E_b(double k_val, double u_x_val);
//
//        static double E_f(double k_val, double sigma_val);
//
//        double k(double t_val);
//
//        static double sech(double x);
//
//        std::function<void(const dbl_vec &, const double)> observer(std::ostream &m_out);
//    };

}

#endif //SIMULATION_FLOW_H
