//
// Created by Keiwan Jamaly on 06.10.22.
//

#ifndef SIMULATION_GRAPHLIBRARY_TYPES_H
#define SIMULATION_GRAPHLIBRARY_TYPES_H

#include <memory>
#include <map>
#include <future>
#include <vector>

namespace gl {
    using std::shared_ptr, std::make_shared, std::vector, std::future, std::map;

    template<class T>
    concept DataConcept = requires(T data) {
        data.splitDecisionData();
        data.compute();
    };

    enum DiagonalDirection {
        nw, ne, sw, se
    };

    enum Direction {
        north, east, south, west
    };
}

#endif //SIMULATION_GRAPHLIBRARY_TYPES_H

