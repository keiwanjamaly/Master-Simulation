//
// Created by Keiwan Jamaly on 04.11.22.
//

#ifndef SIMULATION_GET_TEST_DATA_H
#define SIMULATION_GET_TEST_DATA_H

#include <string>
#include "Types_Potential.h"

namespace phy {
    void get_test_data(std::string filename, dbl_vec &sigma, std::vector<dbl_vec> &u_vector, dbl_vec &t_vector);
} // phy
#endif //SIMULATION_GET_TEST_DATA_H
