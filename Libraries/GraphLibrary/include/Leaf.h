//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAF_H
#define SIMULATION_LEAF_H

#include "Types.h"
#include <vector>

namespace dp {

    template<Graph_Data T>
    class Leaf {
    public:
        std::vector<Leaf<T>> children;
        Leaf<T> *parent;
        T data;
        double x, y;
        double x_min, x_max, y_min, y_max;


        // Default constructor
        explicit Leaf();

        explicit Leaf(const T &data, double x_, double y_, double x_min, double x_max, double y_min, double y_max,
                      const Leaf *parent_);

        explicit Leaf(const T &data, double x_, double y_, double x_min, double x_max, double y_min, double y_max);

        void attach_leaves();

        void compute();


    };

    template<Graph_Data T>
    Leaf<T>::Leaf() {

    }

    template<Graph_Data T>
    Leaf<T>::Leaf(const T &data, double x_, double y_, double x_min, double x_max, double y_min, double y_max,
                  const Leaf *parent_) {

    }

    template<Graph_Data T>
    Leaf<T>::Leaf(const T &data, double x_, double y_, double x_min, double x_max, double y_min, double y_max) {

    }

    template<Graph_Data T>
    void Leaf<T>::attach_leaves() {

    }

    template<Graph_Data T>
    void Leaf<T>::compute() {

    }

} // dp

void test();

#endif //SIMULATION_LEAF_H
