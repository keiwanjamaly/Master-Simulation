//
// Created by Keiwan Jamaly on 11.10.22.
//

#include <vector>


class Data {
public:
    double x{}, y{};
    std::vector<double> value;

    Data() = default;

    Data(double x_, double y_) : x(x_), y(y_) {}

    void compute() {
        if (x < 0.0)
            value = {0.0};
        else if (x >= 0.0)
            value = {1.0};
    }

    [[nodiscard]] std::vector<double> splitDecisionData() const {
        return value;
    }
};