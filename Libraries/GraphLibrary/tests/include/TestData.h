//
// Created by Keiwan Jamaly on 21.10.22.
//

#ifndef SIMULATION_TESTDATA_H
#define SIMULATION_TESTDATA_H

#include <vector>
#include <cmath>

namespace dp {

    class Empty_Config {
    public:
        Empty_Config() = default;

        int mode = 0;

        static bool splitDecision(std::vector<double> v_0, std::vector<double> v_1) {
            if (abs(v_0[0] - v_1[0]) <= 0.1) {
                return false;
            } else {
                return true;
            }
        }
    };

    class Test_Data {
    public:
        std::vector<double> value;
        std::shared_ptr<Empty_Config> configuration;
        double x, y;

        Test_Data() = default;

        explicit Test_Data(double x_, double y_, std::shared_ptr<Empty_Config> config) : configuration(config), x{x_},
                                                                                         y{y_} {}

        virtual void compute() {
            switch (configuration->mode) {
                case 0:
                    if (x < 0.0)
                        value = {0.0};
                    else if (x >= 0.0)
                        value = {1.0};

                    break;
                case 1:
                    if (y < 0.0)
                        value = {0.0};
                    else if (y >= 0.0)
                        value = {1.0};
                    break;
                case 2:
                    if (y >= x) {
                        value = {0.0};
                    } else {
                        value = {1.0};

                    }
                    break;
            }
        }

        std::vector<double> splitDecisionData() const {
            return value;
        }
    };


    class TestDensity : public Test_Data {
    public:
        void compute() {
            value = {1 / (1 + exp(10 * (sqrt(x * x + y * y) - 3)))};
        }
    };

} //dp
#endif //SIMULATION_TESTDATA_H
