//
// Created by Keiwan Jamaly on 30.11.22.
//

/* -----------------------------------------------------------------------------
 * Programmer(s): David J. Gardner @ LLNL
 * -----------------------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2022, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------------------
 * Kvaerno-Prothero-Robinson ODE test problem:
 *
 *   [u]' = [ a  b ] [ (-1 + u^2 - r(t)) / (2u) ] + [ r'(t) / (2u) ]
 *   [v]    [ c  d ] [ (-2 + v^2 - s(t)) / (2v) ]   [ s'(t) / (2v) ]
 *
 * This problem has analytical solution given by
 *
 *   u(t) = sqrt(1 + r(t))
 *   v(t) = sqrt(2 + s(t))
 *
 * where, in this test, we use the functions
 *
 *   r(t) = 0.5 * cos(t)
 *   s(t) = cos(2t)
 * ---------------------------------------------------------------------------*/

#include "cv_kpr.h"

// Include integrator, matrix, linear solver, and vector headers
#include <cvode/cvode.h>
#include <nvector/nvector_serial.h>
#include <sunmatrix/sunmatrix_dense.h>
#include <sunmatrix/sunmatrix_band.h>
#include <sunlinsol/sunlinsol_dense.h>
#include <sunlinsol/sunlinsol_band.h>

// -----------------------------------------------------------------------------
// Functions provided to the SUNDIALS integrators
// -----------------------------------------------------------------------------

// ODE right-hand side function
int f(realtype t, N_Vector y, N_Vector ydot, void *user_data);

// Jacobian of RHS function
int J(realtype t, N_Vector y, N_Vector fy, SUNMatrix J, void *user_data,
      N_Vector tmp1, N_Vector tmp2, N_Vector tmp3);

// -----------------------------------------------------------------------------
// Main Program
// -----------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    // SUNDIALS context object for this simulation
    sundials::Context sunctx;

    // Read input options
    Options opts;
    std::vector<std::string> args(argv + 1, argv + argc);

    // Create initial condition vector
    N_Vector y = N_VNew_Serial(opts.N, sunctx);

    realtype *ydata = N_VGetArrayPointer(y);
    for (int i = 0; i < opts.N; i++)
        ydata[i] = true_sol(ZERO, &opts, i);

    // Create matrix and linear solver
//    SUNMatrix A = SUNDenseMatrix(opts.N, opts.N, sunctx);
    SUNMatrix A = SUNBandMatrix(opts.N, 1, 1, sunctx);

//    SUNLinearSolver LS = SUNLinSol_Dense(y, A, sunctx);
    SUNLinearSolver LS = SUNLinSol_Band(y, A, sunctx);

    // Create CVODE memory structure
    void *cvode_mem = CVodeCreate(CV_BDF, sunctx);

    // Attach RHS function and set initial condition
    CVodeInit(cvode_mem, f, ZERO, y);

    // Set integration tolerances
    CVodeSStolerances(cvode_mem, opts.rtol, opts.atol);

    // Attach matrix and linear solver
    CVodeSetLinearSolver(cvode_mem, LS, A);

    // Set Jacobian function
//    CVodeSetJacFn(cvode_mem, J);

    // Attach user data pointer
//    realtype udata[4] = {-TWO, HALF, HALF, -ONE};
    CVodeSetUserData(cvode_mem, (void *) &opts);

    // Initial time and fist output time
    realtype tret = ZERO;
    realtype tout = tret + opts.dtout;

    // Output initial contion
    std::cout << std::scientific;
    std::cout << std::setprecision(std::numeric_limits<realtype>::digits10);
    std::cout << "           t              ";
    std::cout << "          u              ";
    std::cout << "       true_sol[mid]" << std::endl;
    for (int i = 0; i < 6; i++)
        std::cout << "--------------";
    std::cout << std::endl;

    std::cout << std::setw(22) << tret
              << std::setw(25) << ydata[int(opts.N / 2)]
              << std::setw(25) << true_sol(ZERO, &opts, int(opts.N / 2))
              << std::endl;

    // Advance in time
    for (int i = 0; i < opts.nout; i++) {
        CVode(cvode_mem, tout, y, &tret, CV_NORMAL);

        std::cout << std::setw(22) << tret
                  << std::setw(25) << ydata[int(opts.N / 2)]
                  << std::setw(25) << true_sol(tout, &opts, int(opts.N / 2))
                  << std::endl;

        // update output time
        tout += opts.dtout;
    }

    for (int i = 0; i < 9; i++)
        std::cout << "--------------";
    std::cout << std::endl;

    // Print some final statistics
    CVodePrintAllStats(cvode_mem, stdout, SUN_OUTPUTFORMAT_TABLE);

    // Clean up and return with successful completion
    N_VDestroy(y);
    SUNMatDestroy(A);
    SUNLinSolFree(LS);
    CVodeFree(&cvode_mem);

    return 0;
}


int f(realtype t, N_Vector y, N_Vector ydot, void *user_data) {
    auto udata = static_cast<Options *>(user_data);

    realtype *ydata = N_VGetArrayPointer(y);
    realtype *fdata = N_VGetArrayPointer(ydot);

    fdata[0] = 0.0;
    for (int i = 1; i < udata->N - 1; i++)
        fdata[i] = (ydata[i + 1] - 2 * ydata[i] + ydata[i - 1]) / (udata->dx * udata->dx);
    fdata[udata->N - 1] = 0.0;
    return 0;
}

int J(realtype t, N_Vector y, N_Vector fy, SUNMatrix J, void *user_data,
      N_Vector tmp1, N_Vector tmp2, N_Vector tmp3) {
    auto udata = static_cast<Options *>(user_data);
//    SUNMatZero(J);
    auto J_cols = SUNBandMatrix_Cols(J);
    sunindextype smu = SM_SUBAND_B(J);

    // set center line
    for (sunindextype i = 0; i < udata->N; i++) {
        J_cols[i][smu] = -2 / (udata->dx * udata->dx);
    }

    // set upper band line
    for (sunindextype i = 1; i < udata->N; i++) {
        J_cols[i][-1 + smu] = 1 / (udata->dx * udata->dx);
    }

    for (sunindextype i = 0; i < udata->N - 1; i++) {
        J_cols[i][1 + smu] = 1 / (udata->dx * udata->dx);
    }

    return 0;
}

/*---- end of file ----*/