//
// Created by Keiwan Jamaly on 14.12.22.
//

#ifndef SIMULATION_TREEWITHCOMPARISONS_H
#define SIMULATION_TREEWITHCOMPARISONS_H

#include "TreeWithData.h"

namespace gl {
    template<class T, DataConcept Data, class Config>
    class TreeWithComparisons : public TreeWithData<T, Data, Config> {
    public:
        using TreeWithData<T, Data, Config>::TreeWithData;

        bool comparison(Direction dir) {
            shared_ptr<T> neighbour = this->getNeighbour(dir);
            if (neighbour == nullptr)
                return false;
            else {
                if (this->getDataPointer()->splitDecisionData().size() == 0 or
                    neighbour->getDataPointer()->splitDecisionData().size() == 0)
                    throw std::runtime_error("data was not calculated");
                return this->getConfig()->splitDecision(this->getDataPointer()->splitDecisionData(),
                                                        neighbour->getDataPointer()->splitDecisionData());
            }
        }

        bool comparison(DiagonalDirection dir) {
            shared_ptr<T> neighbour = this->getDiagonalNeighbour(dir);
            if (neighbour == nullptr)
                return false;
            else
                return this->getConfig()->splitDecision(this->getDataPointer()->splitDecisionData(),
                                                        neighbour->getDataPointer()->splitDecisionData());
        }

        bool should_be_split() {
            bool north_comparison = this->comparison(north);
            bool east_comparison = this->comparison(east);
            bool south_comparison = this->comparison(south);
            bool west_comparison = this->comparison(west);
            bool northWest_comparison = this->comparison(nw);
            bool northEast_comparison = this->comparison(ne);
            bool southEast_comparison = this->comparison(se);
            bool southWest_comparison = this->comparison(sw);
            return north_comparison || east_comparison || south_comparison || west_comparison || northWest_comparison ||
                   northEast_comparison || southEast_comparison || southWest_comparison;
        }
    };
}

#endif //SIMULATION_TREEWITHCOMPARISONS_H
