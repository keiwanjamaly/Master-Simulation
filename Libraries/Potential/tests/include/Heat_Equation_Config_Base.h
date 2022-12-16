//
// Created by Keiwan Jamaly on 01.12.22.
//

#ifndef SIMULATION_HEAT_EQUATION_CONFIG_BASE_H
#define SIMULATION_HEAT_EQUATION_CONFIG_BASE_H

#include "Config.h"
#include <cmath>

namespace phy {

    class Heat_Equation_Config : public Config_Base {
    public:
        Heat_Equation_Config(sunrealtype t, sunrealtype t_final, sunrealtype x_min, sunrealtype x_max, int N)
                : Config_Base(t, t_final,
                              x_min, x_max,
                              N) {
            m_L = x_max - x_min;
        }

        auto get_L() { return m_L; };

        // implementing physics
        sunrealtype Q(sunrealtype /* t */, sunrealtype ux) const final { return ux; };

        sunrealtype Q_prime(sunrealtype /* t */, sunrealtype /* ux */) const final { return 1; };

        sunrealtype S(sunrealtype /* t */, sunrealtype /* x */) const override { return 0; };

        Implementation S_Implementation() const final { return analytically; };

        sunrealtype lbc(sunrealtype u0, sunrealtype u1) final { return 2 * u0 - u1; };

        sunrealtype rbc(sunrealtype uN_minus_2, sunrealtype uN_minus_1) final { return 2 * uN_minus_1 - uN_minus_2; };

        sunrealtype initial_condition(sunrealtype x) final { return analytic_solution(RCONST(0.0), x); };

        virtual sunrealtype analytic_solution(sunrealtype t, sunrealtype x) const {
            return exp(-pow(M_PI / m_L, RCONST(2.0)) * t) * sin(M_PI / m_L * x);
        };

    protected:
        sunrealtype m_L;
    };

    class Heat_Equation_With_Source_Config : public Heat_Equation_Config {
    public:
        using Heat_Equation_Config::Heat_Equation_Config;

        sunrealtype S(sunrealtype /* t */, sunrealtype x) const final { return 2 * sin(M_PI / m_L * x); };

        sunrealtype analytic_solution(sunrealtype t, sunrealtype x) const override {
            double alpha = pow(M_PI / m_L, 2);
            return exp(-4 * alpha * t) * sin(2 * M_PI / m_L * x) + (1 - exp(-alpha * t)) * S(t, x) / alpha;
        }
    };

} // phy
#endif //SIMULATION_HEAT_EQUATION_CONFIG_BASE_H
