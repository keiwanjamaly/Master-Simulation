//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAF_H
#define SIMULATION_LEAF_H

#include "Types.h"
#include <vector>

namespace dp {
    template <Graph_Data T> class Leaf {
    public:
        std::vector<Leaf<T>> children;
        Leaf<T> parent;
        T data;
        double x, y;

        explicit Leaf(T const& data, double x_, double y_, Leaf const& parent_);
        explicit Leaf(T const& data, double x_, double y_);

        void attach_leaves();
        void compute();
    };



} // dp

#endif //SIMULATION_LEAF_H
