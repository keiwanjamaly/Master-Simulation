//
// Created by Keiwan Jamaly on 25.10.22.
//

#ifndef SIMULATION_TYPES_POTENTIAL_H
#define SIMULATION_TYPES_POTENTIAL_H

#include <vector>
#include <boost/numeric/odeint.hpp>

namespace phy {
    using namespace boost::numeric::odeint;

    typedef std::vector<double> dbl_vec;

    typedef boost::numeric::odeint::runge_kutta_cash_karp54<dbl_vec> error_stepper_type;

} // phy


#endif //SIMULATION_TYPES_POTENTIAL_H
