//
// Created by Keiwan Jamaly on 06.10.22.
//

#ifndef SIMULATION_TYPES_H
#define SIMULATION_TYPES_H

template<class T>
concept Graph_Data = requires(T data, const double x, const double y) {
    data.splitDecisionData();
    // .compute() should check first, if it is already computed and reuse its result.
    data.compute();
    data.value;
    data.x;
    data.y;
};

enum ChildDirection {
    nw, ne, sw, se
};

#endif //SIMULATION_TYPES_H

