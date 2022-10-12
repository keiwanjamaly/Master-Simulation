//
// Created by Keiwan Jamaly on 06.10.22.
//

#ifndef SIMULATION_TYPES_H
#define SIMULATION_TYPES_H

template<class T>
concept Graph_Data = requires(T data, const double x, const double y) {
    data.splitDecisionData();
    data.compute();
    data.value;
    data.x;
    data.y;
};

enum Direction {
    nw, ne, sw, se
};

#endif //SIMULATION_TYPES_H

