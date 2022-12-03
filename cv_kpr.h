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
 * Kvaerno-Prothero-Robinson ODE test problem, see .cpp file for details
 * ---------------------------------------------------------------------------*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

// SUNDIALS types
#include <sundials/sundials_types.h>
#include <sundials/sundials_nvector.h>

// Common utility functions
//#include <example_utilities.hpp>

// Macros for problem constants
#define ZERO    RCONST(0.0)
#define HALF    RCONST(0.5)
#define ONE     RCONST(1.0)
#define TWO     RCONST(2.0)
#define TWENTY  RCONST(20.0)

// -----------------------------------------------------------------------------
// Problem options
// -----------------------------------------------------------------------------

struct Options {
    // Relative and absolute tolerances
    sunrealtype rtol = sunrealtype(1.0e-7);
    sunrealtype atol = RCONST(1.0e-11);

    // Output options
    sunrealtype dtout = RCONST(0.1); // output interval
    int nout = 20;  // number of outputs
    int N = 11;
    sunrealtype L = 5.0;
    sunrealtype dx = L / (N - 1);
};

// Compute the true solution
inline double true_sol(sunrealtype t, Options *opts, int i) {
    return exp(-pow(M_PI / opts->L, 2.0) * t) * sin(M_PI / opts->L * i * opts->dx);
}
/*---- end of file ----*/