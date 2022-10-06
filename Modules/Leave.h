//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAVE_H
#define SIMULATION_LEAVE_H

#include "Types.h"
#include <vector>

namespace dp {
    template <Graph_Data T> class Leave {
    public:
        std::vector<Leave<T>> children;
        Leave<T> parent;
        T data;
        double x, y;

        explicit Leave(T const& data, Leave const& parent_, double x_, double y_);
        explicit Leave(T const& data, double x_, double y_);

        void attach_leaves();
        void compute();
    };



} // dp

#endif //SIMULATION_LEAVE_H
