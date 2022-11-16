//
// Created by Keiwan Jamaly on 21.10.22.
//

#ifndef SIMULATION_TESTDATA_H
#define SIMULATION_TESTDATA_H

#include "Leaf.h"

namespace dp {

    class Empty_Config {
    public:
        int mode = 0;
    };

    class Data {
    public:
        double x{}, y{};
        std::vector<double> value;
        bool computed = false;
        std::shared_ptr<Empty_Config> configuration;

        Data() = default;

        Data(double x_, double y_, std::shared_ptr<Empty_Config> config);

        void compute();

        std::vector<double> splitDecisionData();
    };


    bool split_decision(std::vector<double> v_0, std::vector<double> v_1);


    typedef Leaf<Data, Empty_Config> CurrLeaf;

} //dp
#endif //SIMULATION_TESTDATA_H
