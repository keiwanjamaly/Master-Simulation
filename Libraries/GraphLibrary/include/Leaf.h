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
        double box_size;
        std::vector<Leaf<T>> children;
        Leaf<T> *parent;
        T data;
        double x, y;

        bool (*split_condition)(std::vector<double>, std::vector<double>);


        // Default constructor
        explicit Leaf();

        explicit Leaf(double x_, double y_, double initial_box_size_,
                      bool (*split_condition_)(std::vector<double>, std::vector<double>));

        explicit Leaf(ChildDirection dir,
                      const Leaf *parent_);

        void attach_leaves();

        void compute();

        bool isRoot();

        Leaf<T> *get_child_of_parent(ChildDirection dir);

        Leaf<T> *north_neighbour();

        Leaf<T> *east_neighbour();

        Leaf<T> *south_neighbour();

        Leaf<T> *west_neighbour();

        bool north_comparison();

        bool east_comparison();

        bool south_comparison();

        bool west_comparison();

        bool should_be_split();

        bool balance_tree(bool force = false);

    };

} // dp

#endif //SIMULATION_LEAF_H
