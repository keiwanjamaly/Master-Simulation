//
// Created by Keiwan Jamaly on 21.10.22.
//

#ifndef SIMULATION_TESTDATA_H
#define SIMULATION_TESTDATA_H

#include <vector>

#include "Leaf3.h"

namespace dp {

    class Empty_Config {
    public:
        Empty_Config(const Empty_Config &empty_configObj) = default;

        Empty_Config() = default;

        Empty_Config(double x_, double y_) : x{x_}, y{y_} {}

        std::shared_ptr<Empty_Config> copyAndSetXY(double x_, double y_) {
            std::shared_ptr<Empty_Config> newFlow = std::make_shared<Empty_Config>(*this);
            newFlow->x = x_;
            newFlow->y = y_;
            return newFlow;
        }

        double x{}, y{};
        int mode = 0;
    };

    class Data {
    public:
        std::vector<double> value;
        std::shared_ptr<Empty_Config> configuration;

        Data() = default;

        Data(std::shared_ptr<Empty_Config> config) : configuration(config) {}

        void compute() {
            switch (configuration->mode) {
                case 0:
                    if (configuration->x < 0.0)
                        value = {0.0};
                    else if (configuration->x >= 0.0)
                        value = {1.0};

                    break;
                case 1:
                    if (configuration->y < 0.0)
                        value = {0.0};
                    else if (configuration->y >= 0.0)
                        value = {1.0};
                    break;
                case 2:
                    if (configuration->y >= configuration->x) {
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


    inline bool split_decision(std::vector<double> v_0, std::vector<double> v_1) {
        if (abs(v_0[0] - v_1[0]) <= 0.1) {
            return false;
        } else {
            return true;
        }
    }


    typedef Leaf<Data, Empty_Config> CurrLeaf;

    class TestDensity {
    public:
        std::shared_ptr<Empty_Config> configuration;
        std::vector<double> value;

        TestDensity(std::shared_ptr<Empty_Config> config) : configuration(config) {}

        void compute() {
            double x = configuration->x;
            double y = configuration->y;
            value = {1 / (1 + exp(10 * (sqrt(x * x + y * y) - 3)))};
        }

        std::vector<double> splitDecisionData() const {
            return value;
        }
    };

} //dp
#endif //SIMULATION_TESTDATA_H
