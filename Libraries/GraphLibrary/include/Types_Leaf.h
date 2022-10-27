//
// Created by Keiwan Jamaly on 06.10.22.
//

#ifndef SIMULATION_TYPES_LEAF_H
#define SIMULATION_TYPES_LEAF_H


template<class T>
concept Graph_Data = requires(T data, const double x, const double y) {
    data.splitDecisionData();
    data.x;
    data.y;
};

enum DiagonalDirection {
    nw, ne, sw, se
};

enum Direction {
    north, east, south, west
};

#endif //SIMULATION_TYPES_LEAF_H

