//
// Created by Keiwan Jamaly on 25.10.22.
//

#ifndef SIMULATION_TYPES_POTENTIAL_H
#define SIMULATION_TYPES_POTENTIAL_H

#include <vector>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace phy {
    using namespace boost::numeric::odeint;

    typedef std::vector<double> dbl_vec;


    typedef boost::numeric::ublas::vector<double> local_vector_type;
    typedef boost::numeric::ublas::matrix<double> local_matrix_type;

    typedef boost::numeric::odeint::rosenbrock4<double> error_stepper_type;

} // phy

#endif //SIMULATION_TYPES_POTENTIAL_H
