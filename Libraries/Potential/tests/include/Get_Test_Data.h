//
// Created by Keiwan Jamaly on 04.11.22.
//

#ifndef SIMULATION_GET_TEST_DATA_H
#define SIMULATION_GET_TEST_DATA_H

#include <string>
#include <vector>

namespace phy {
    void
    get_test_data(const std::string &filename, std::vector<double> &sigma, std::vector<std::vector<double>> &u_vector,
                  std::vector<double> &t_vector);
} // phy
#endif //SIMULATION_GET_TEST_DATA_H
