//
// Created by Keiwan Jamaly on 05.10.22.
//

#include "Graph.h"

namespace dp {
    template<Graph_Data T>
    Graph<T>::Graph(bool (*func)(std::vector<double>, std::vector<double>), double x_, double y_, double x_min,
                    double x_max, double y_min, double y_max) {}

    template<Graph_Data T>
    void Graph<T>::graph_split(bool force) {}

    template<Graph_Data T>
    void Graph<T>::compute_leaves() {}
} // dp