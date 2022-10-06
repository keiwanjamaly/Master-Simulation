//
// Created by Keiwan Jamaly on 06.10.22.
//

#ifndef SIMULATION_TYPES_H
#define SIMULATION_TYPES_H

template <class T>
concept Graph_Data = requires(T data) {
    data.splitDecisionData();
    data.compute();
};

enum Direction {NW, NO, SW, SO};

#endif //SIMULATION_TYPES_H
