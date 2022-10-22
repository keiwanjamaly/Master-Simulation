//
// Created by Keiwan Jamaly on 17.10.22.
//

#include <vector>
#include <cmath>

#include "TestData.h"

namespace dp {
    Data::Data(double x_, double y_) : x(x_), y(y_) {}

    void Data::compute() {
        if (!computed) {
            if (x < 0.0)
                value = {0.0};
            else if (x >= 0.0)
                value = {1.0};
            computed = true;
        }
    }

    std::vector<double> Data::splitDecisionData() {
        return value;
    }

    Line::Line(double x_, double y_) : x(x_), y(y_) {}

    void Line::compute() {
        if (y >= x) {
            value = {0.0};
        } else {
            value = {1.0};
        }
    }

    std::vector<double> Line::splitDecisionData() {
        return value;
    }

    bool split_decision(std::vector<double> v_0, std::vector<double> v_1) {
        if (abs(v_0[0] - v_1[0]) <= 0.1) {
            return false;
        } else {
            return true;
        }
    }

    Data_H::Data_H(double x_, double y_) : x(x_), y(y_) {}

    void Data_H::compute() {
        if (!computed) {
            if (y < 0.0)
                value = {0.0};
            else if (y >= 0.0)
                value = {1.0};
            computed = true;
        }
    }

    std::vector<double> Data_H::splitDecisionData() {
        return value;
    }
} // dp