//
// Created by Keiwan Jamaly on 25.10.22.
//

#ifndef SIMULATION_SYSTEM_H
#define SIMULATION_SYSTEM_H

#include "Types_Potential.h"
#include "Config.h"

#include <memory>
#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <sunmatrix/sunmatrix_dense.h>
#include <sunmatrix/sunmatrix_band.h>
#include <sunlinsol/sunlinsol_dense.h>
#include <sunlinsol/sunlinsol_band.h>


namespace phy {

    using std::shared_ptr, std::function;

    class System {
    public:
        System() = delete;

        explicit System(const shared_ptr<Config_Base> &config) : m_config{config} {
            // declare and fill u with initial conditions
            m_u = N_VNew_Serial(config->get_N(), m_sunctx);
            realtype *m_u_data = get_u_pointer();
            auto x_points = config->get_x_points();
            for (int i = 0; i < config->get_N(); i++)
                m_u_data[i] = config->initial_condition(x_points[i]);

            // declare band matrix
            m_band_matrix = SUNDenseMatrix(config->get_N(), config->get_N(), m_sunctx);
//            m_band_matrix = SUNBandMatrix(config->get_N(), 1, 1, m_sunctx);

            // Create Linear solver
            m_LS = SUNLinSol_Dense(m_u, m_band_matrix, m_sunctx);
//            m_LS = SUNLinSol_Band(m_u, m_band_matrix, m_sunctx);

            // Create CVODE memory structure
            m_cvode_mem = CVodeCreate(CV_BDF, m_sunctx);

            // Attach RHS function and set initial condition
            m_flag_init = CVodeInit(m_cvode_mem, f, config->get_t(), m_u);

            // Set integration tolerances
            m_set_flag_SStolerances = CVodeSStolerances(m_cvode_mem, config->get_rel_tol(), config->get_abs_tol());

            // Attach matrix and linear solver
            m_flag_SetLinearSolver = CVodeSetLinearSolver(m_cvode_mem, m_LS, m_band_matrix);

            // Set Jacobian function
            m_flag_SetJacFn = CVodeSetJacFn(m_cvode_mem, Jacobian);

            // Attach user data pointer
            m_flag_SetUserData = CVodeSetUserData(m_cvode_mem, (void *) config.get());

            // test all flags
            if (m_flag_init != CV_SUCCESS)
                throw std::runtime_error("RHS function could not be initialized");
            if (m_set_flag_SStolerances != CV_SUCCESS)
                throw std::runtime_error("failed to set tolerances");
            if (m_flag_SetLinearSolver != CVLS_SUCCESS)
                throw std::runtime_error("failed to attach linear solver");
            if (m_flag_SetJacFn != CVLS_SUCCESS)
                throw std::runtime_error("failed to attach jacobian");
            if (m_flag_SetUserData != CV_SUCCESS)
                throw std::runtime_error("failed to set user data");
        }

        ~System() {
            // free memory of CVODE objects
            N_VDestroy(m_u);
            SUNMatDestroy(m_band_matrix);
            SUNLinSolFree(m_LS);
            CVodeFree(&m_cvode_mem);
        }

        void solve() {
            auto flag = CVode(m_cvode_mem, m_config->get_t_final(), m_u, m_config->get_t_pointer(), CV_NORMAL);
            if (flag != CV_SUCCESS)
                throw std::runtime_error("failed to integrate");
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
            N_VPrint_Serial(ydot);
        }

        static int
        Jacobian(realtype t, N_Vector y, N_Vector /* fy */, SUNMatrix Jac, void *user_data, N_Vector /* tmp1 */,
                 N_Vector /* tmp2 */,
                 N_Vector /* tmp3 */) {

            // setup
            auto udata = static_cast<Config_Base *>(user_data);
            realtype *ydata = N_VGetArrayPointer(y);
            auto J_cols = SUNBandMatrix_Cols(Jac);
            sunindextype smu = SM_SUBAND_B(Jac);
            sunrealtype dx = udata->get_dx();
            int N = udata->get_N();
            sunrealtype y_x;
            sunrealtype low, high;

            // prepare loop
            y_x = (ydata[0] - udata->lbc(ydata[0], ydata[1])) / dx;
            low = udata->Q_prime(t, y_x);

            // calculate jacobian
            for (int i = 0; i < N; i++) {
                if (i != N - 1)
                    y_x = (ydata[i + 1] - ydata[i]) / dx;
                else
                    y_x = (udata->rbc(ydata[N - 2], ydata[N - 1]) - ydata[N - 1]) / dx;

                high = udata->Q_prime(t, y_x);

                // set center
                J_cols[i][smu] = -(high + low) / (dx * dx);
                // set upper
                if (i >= 1)
                    J_cols[i][-1 + smu] = high / (dx * dx);
                // set lower
                if (i < N - 1)
                    J_cols[i][1 + smu] = low / (dx * dx);
                low = high;
            }
            SUNBandMatrix_Print(Jac, stdout);

            return 0;
        }

        shared_ptr<Config_Base> get_Config() { return m_config; };

        int get_flag_init() { return m_flag_init; };

        int get_set_flag_SStolerances() { return m_set_flag_SStolerances; };

        int get_flag_SetLinearSolver() { return m_flag_SetLinearSolver; };

        int get_flag_SetJacFn() { return m_flag_SetJacFn; };

        int get_flag_SetUserData() { return m_flag_SetUserData; };

        void *get_cvode_mem() { return m_cvode_mem; };

        SUNLinearSolver get_LS() { return m_LS; };

        N_Vector get_u() { return m_u; };

        realtype *get_u_pointer() { return N_VGetArrayPointer(m_u); };

    private:
        // CVODE objects
        sundials::Context m_sunctx;
        void *m_cvode_mem;
        SUNLinearSolver m_LS;
        SUNMatrix m_band_matrix;
        N_Vector m_u;

        shared_ptr<Config_Base> m_config;

        // some test flags
        int m_flag_init = -100,
                m_set_flag_SStolerances = -100,
                m_flag_SetLinearSolver = -100,
                m_flag_SetJacFn = -100,
                m_flag_SetUserData = -100;

    };

} // phy

#endif //SIMULATION_SYSTEM_H