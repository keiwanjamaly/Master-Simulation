//
// Created by Keiwan Jamaly on 01.12.22.
//

#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include <memory>
#include <functional>
#include <vector>
#include <iostream>

#include <cvode/cvode.h>


namespace phy {

    enum Implementation {
        analytically,
        numerically
    };

    using std::shared_ptr, std::function;

    class Config_Base {
    public:

        Config_Base() = delete;

        Config_Base(sunrealtype t_start, sunrealtype t_final, sunrealtype x_min, sunrealtype x_max, int N,
                    sunrealtype abs_tol = RCONST(1e-5), sunrealtype rel_tol = RCONST(1e-10)) : m_t_start{t_start},
                                                                                               m_t{t_start},
                                                                                               m_t_final{t_final},
                                                                                               m_x_min{x_min},
                                                                                               m_x_max{x_max}, m_N{N},
                                                                                               m_abs_tol{abs_tol},
                                                                                               m_rel_tol{rel_tol} {
            m_calculate_dx();
            m_calculate_x_points();
        }


        // getter methods for private member variables
        int get_N() const { return m_N; };

        sunrealtype get_dx() const { return m_dx; };

        sunrealtype get_x_min() const { return m_x_min; };

        sunrealtype get_x_max() const { return m_x_max; };

        const std::vector<sunrealtype> &get_x_points() { return m_x_points; };

        sunrealtype get_abs_tol() const { return m_abs_tol; };

        sunrealtype get_rel_tol() const { return m_rel_tol; };

        sunrealtype get_t() const { return m_t; };

        sunrealtype get_t_start() const { return m_t_start; };

        sunrealtype *get_t_pointer() { return &m_t; };

        sunrealtype get_t_final() const { return m_t_final; };

        // these need to be initialized by the derived class
        // Q(t, ux)
        virtual sunrealtype Q(sunrealtype, sunrealtype) const = 0;

        // Q(t, ux)
        virtual sunrealtype Q_prime(sunrealtype, sunrealtype) const = 0;

        // S(t, x)
        virtual sunrealtype S(sunrealtype, sunrealtype) const = 0;

        virtual Implementation S_Implementation() const = 0;

        virtual sunrealtype lbc(sunrealtype, sunrealtype) = 0;

        virtual sunrealtype lbc_1_0(sunrealtype, sunrealtype) = 0;

        virtual sunrealtype lbc_0_1(sunrealtype, sunrealtype) = 0;

        virtual sunrealtype rbc(sunrealtype, sunrealtype) = 0;

        virtual sunrealtype rbc_1_0(sunrealtype, sunrealtype) = 0;

        virtual sunrealtype rbc_0_1(sunrealtype, sunrealtype) = 0;

        virtual sunrealtype initial_condition(sunrealtype) = 0;

        virtual void monitor(sunrealtype t) const {
            std::cout << t << '\n';
        }

    private:
        void m_calculate_x_points() {
            m_x_points.reserve(m_N);
            for (int i = 0; i < m_N; i++)
                m_x_points.push_back(m_dx * i);
        }

        void m_calculate_dx() {
            m_dx = (m_x_max - m_x_min) / (m_N - 1);
        }

        sunrealtype m_t_start, m_t, m_t_final;
        sunrealtype m_abs_tol, m_rel_tol;
        sunrealtype m_x_min, m_x_max;
        int m_N;
        std::vector<sunrealtype> m_x_points;
        sunrealtype m_dx;
    };
} // phy
#endif //SIMULATION_CONFIG_H
