//
// Created by Keiwan Jamaly on 17.10.22.
//

#include <vector>
#include <cmath>
#include <memory>

#include "TestData.h"

namespace dp {
    Data::Data(double x_, double y_, std::shared_ptr<Empty_Config> config) : x(x_), y(y_), configuration(config) {}

    void Data::compute() {
        switch (configuration->mode) {
            case 0:
                if (!computed) {
                    if (x < 0.0)
                        value = {0.0};
                    else if (x >= 0.0)
                        value = {1.0};
                    computed = true;
                }
                break;
            case 1:
                if (!computed) {
                    if (y < 0.0)
                        value = {0.0};
                    else if (y >= 0.0)
                        value = {1.0};
                    computed = true;
                }
            case 2:
                if (!computed) {
                    if (y >= x) {
                        value = {0.0};
                    } else {
                        value = {1.0};
                    }
                }
                break;
        }
    }

    std::vector<double> Data::splitDecisionData() {
        if (!computed)
            this->compute();
        return value;
    }

    bool split_decision(std::vector<double> v_0, std::vector<double> v_1) {
        if (abs(v_0[0] - v_1[0]) <= 0.1) {
            return false;
        } else {
            return true;
        }
    }

    TestDensity::TestDensity(double x_, double y_, std::shared_ptr<Empty_Config> config) : x(x_), y(y_),
                                                                                           configuration(config) {}

    void TestDensity::compute() {
        value = {1 / (1 + exp(10 * (sqrt(x * x + y * y) - 3)))};
    }

    std::vector<double> TestDensity::splitDecisionData() {
        return value;
    }


} // dp