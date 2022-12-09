//
// Created by Keiwan Jamaly on 25.10.22.
//

#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H

#include "Config.h"

#include <memory>
#include <cvode/cvode.h>
#include <arkode/arkode.h>
#include <arkode/arkode_erkstep.h>
#include <nvector/nvector_serial.h>
#include <sunmatrix/sunmatrix_band.h>
#include <sunlinsol/sunlinsol_band.h>
#include <string>
#include <climits>


namespace phy {

    using std::shared_ptr, std::function;

    class System {
    public:
        System() = delete;

        explicit System(const shared_ptr<Config_Base> &config) : m_config{config} {
            // declare and fill u with initial conditions
            m_u = N_VNew_Serial(m_config->get_N(), m_sunctx);
            realtype *m_u_data = get_u_pointer();
            auto x_points = m_config->get_x_points();
            for (int i = 0; i < m_config->get_N(); i++)
                m_u_data[i] = m_config->initial_condition(x_points[i]);

            // Create ERKStep memory structure and set function parameters
            m_erk_mem = ERKStepCreate(f, m_config->get_t(), m_u, m_sunctx);

            // Set integration tolerances
            m_set_flag_SStolerances = ERKStepSStolerances(m_erk_mem, m_config->get_rel_tol(),
                                                          m_config->get_abs_tol());

            // Attach user data pointer
            m_flag_SetUserData = ERKStepSetUserData(m_erk_mem, (void *) m_config.get());

            // setting the maximum number of steps to the largest value possible

            // test all flags
            if (m_set_flag_SStolerances != CV_SUCCESS)
                throw std::runtime_error("failed to set tolerances");
            if (m_flag_SetUserData != CV_SUCCESS)
                throw std::runtime_error("failed to set user data");
        }

        ~System() {
            N_VDestroy(m_u);
            ERKStepFree(&m_erk_mem);
        }

        void solve() {
            auto flag = ERKStepEvolve(m_erk_mem, m_config->get_t_final(), m_u, m_config->get_t_pointer(),
                                      ARK_ONE_STEP);
            std::cout << m_config->get_t() << std::endl;
            if (flag != CV_SUCCESS)
                throw std::runtime_error("failed to integrate with error " + std::to_string(flag));
        }

        static int f(realtype t, N_Vector y, N_Vector ydot, void *user_data) {
            // setup
            auto udata = static_cast<Config_Base *>(user_data);
            realtype *ydata = N_VGetArrayPointer(y);
            realtype *fdata = N_VGetArrayPointer(ydot);
            auto x_points = udata->get_x_points();
            sunrealtype dx = udata->get_dx();
            int N = udata->get_N();
            sunrealtype y_x;
            sunrealtype low, high;

            // handle diffusion
            y_x = (ydata[0] - udata->lbc(ydata[0], ydata[1])) / dx;
            low = udata->Q(t, y_x);
            for (int i = 0; i < N; i++) {
                if (i != N - 1)
                    y_x = (ydata[i + 1] - ydata[i]) / dx;
                else
                    y_x = (udata->rbc(ydata[N - 2], ydata[N - 1]) - ydata[N - 1]) / dx;
                high = udata->Q(t, y_x);
                fdata[i] = (high - low) / (dx);
                low = high;
            }

//          handle source
            switch (udata->S_Implementation()) {
                case analytically:
                    for (int i = 0; i < N; i++)
                        fdata[i] += udata->S(t, x_points[i]);
                    break;
                case numerically:
                    low = udata->S(t, x_points[0] - dx * 0.5);
                    for (int i = 0; i < N; i++) {
                        high = udata->S(t, x_points[i] + dx * 0.5);
                        fdata[i] += (high - low) / dx;
                        low = high;
                    }
                    break;
            }

            return 0;
        }

        shared_ptr<Config_Base> get_Config() { return m_config; };

        int get_set_flag_SStolerances() { return m_set_flag_SStolerances; };

        int get_flag_SetUserData() { return m_flag_SetUserData; };

        void *get_erk_mem() { return m_erk_mem; };

        N_Vector get_u() { return m_u; };

        realtype *get_u_pointer() { return N_VGetArrayPointer(m_u); };

    private:
        // CVODE objects
        sundials::Context m_sunctx;
        void *m_erk_mem;
        N_Vector m_u;

        shared_ptr<Config_Base> m_config;

        // some test flags
        int m_set_flag_SStolerances = -100,
                m_flag_SetUserData = -100;

    };

} // phy

#endif //SIMULATION_SYSTEM_H