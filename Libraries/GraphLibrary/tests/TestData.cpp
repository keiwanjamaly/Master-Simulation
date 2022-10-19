//
// Created by Keiwan Jamaly on 17.10.22.
//

#include <vector>
#include <cmath>

namespace dp {
    class Data {
    public:
        double x{}, y{};
        std::vector<double> value;
        bool computed = false;

        Data() = default;

        Data(double x_, double y_) : x(x_), y(y_) {}

        void compute() {
            if (!computed) {
                if (x < 0.0)
                    value = {0.0};
                else if (x >= 0.0)
                    value = {1.0};
                computed = true;
            }
        }

        std::vector<double> splitDecisionData() {
            return value;
        }
    };

    class Line {
    public:
        double x{}, y{};
        std::vector<double> value;

        Line() = default;

        Line(double x_, double y_) : x(x_), y(y_) {}

        void compute() {
            if (y >= x) {
                value = {0.0};
            } else {
                value = {1.0};
            }
        }

        std::vector<double> splitDecisionData() {
            return value;
        }
    };

    bool split_decision(std::vector<double> v_0, std::vector<double> v_1) {
        if (abs(v_0[0] - v_1[0]) <= 0.1) {
            return false;
        } else {
            return true;
        }
    }
} // dp