//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_GRAPH_H
#define SIMULATION_GRAPH_H

#include "Leaf.h"
#include "Types.h"

namespace dp {

    template <Graph_Data T> class Graph {
    private:
        Leaf<T> root;
    public:
        explicit Graph(bool (*func)(std::vector<double>, std::vector<double>));
        void graph_split(bool force = false);
        void compute_leaves();


    };

} // dp

#endif //SIMULATION_GRAPH_H
