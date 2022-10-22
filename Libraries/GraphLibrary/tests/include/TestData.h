//
// Created by Keiwan Jamaly on 21.10.22.
//

#ifndef SIMULATION_TESTDATA_H
#define SIMULATION_TESTDATA_H

namespace dp {

    class Data {
    public:
        double x{}, y{};
        std::vector<double> value;
        bool computed = false;

        Data() = default;

        Data(double x_, double y_);

        void compute();

        std::vector<double> splitDecisionData();
    };

    class Data_H {
    public:
        double x{}, y{};
        std::vector<double> value;
        bool computed = false;

        Data_H() = default;

        Data_H(double x_, double y_);

        void compute();

        std::vector<double> splitDecisionData();
    };

    class Line {
    public:
        double x{}, y{};
        std::vector<double> value;

        Line() = default;

        Line(double x_, double y_);

        void compute();

        std::vector<double> splitDecisionData();
    };

    bool split_decision(std::vector<double> v_0, std::vector<double> v_1);

} //dp
#endif //SIMULATION_TESTDATA_H
