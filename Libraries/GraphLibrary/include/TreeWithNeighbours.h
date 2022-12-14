//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_TREEWITHNEIGHBOURS_H
#define SIMULATION_TREEWITHNEIGHBOURS_H

#include "Tree.h"

namespace gl {

    template<class T>
    class TreeWithNeighbours : public Tree<T> {
    public:
        using Tree<T>::Tree;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        shared_ptr<T> getNeighbour(Direction dir, bool initial = true) {

            shared_ptr<T> result, mu;
            // if leaf is a root itself
            if (this->isRoot()) {
                return nullptr;
            }
            // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
            // nm[north][0] = sw
            if (this->getChildOfParent(nm[dir][0]) == this->shared_from_this()) {
                // nm[north][1] = nw
                result = this->getChildOfParent(nm[dir][1]);
                // nm[north][2] = se
            } else if (this->getChildOfParent(nm[dir][2]) == this->shared_from_this()) {
                // nm[north][3] = ne
                result = this->getChildOfParent(nm[dir][3]);
            } else {
                // find recursively the north get_diagonal_neighbour
                mu = this->getParent()->getNeighbour(dir, false);
                if (mu == nullptr or !(mu->hasChildren())) {
                    result = mu;
                    // nm[north][4] = nw
                } else if (this->getChildOfParent(nm[dir][4]) == this->shared_from_this()) {
                    // nm[north][5] = sw
                    result = mu->getChild(nm[dir][5]);
                } else {
                    // nm[north][6] = se
                    result = mu->getChild(nm[dir][6]);
                }
            }

            if (initial) {
                if (result != nullptr and this->getDepth() == result->getDepth())
                    return result;
                else
                    return nullptr;
            } else
                return result;
        }

#pragma clang diagnostic pop

        shared_ptr<T> getDiagonalNeighbour(DiagonalDirection dir) {
            shared_ptr<T> intermediate_neighbour;
            switch (dir) {
                case nw:
                    intermediate_neighbour = this->getNeighbour(west);
                    break;
                case ne:
                    intermediate_neighbour = this->getNeighbour(east);
                    break;
                case se:
                    intermediate_neighbour = this->getNeighbour(east);
                    break;
                case sw:
                    intermediate_neighbour = this->getNeighbour(west);
                    break;
            }

            if (intermediate_neighbour == nullptr)
                return intermediate_neighbour;

            switch (dir) {
                case nw:
                    return intermediate_neighbour->getNeighbour(north);
                case ne:
                    return intermediate_neighbour->getNeighbour(north);
                case se:
                    return intermediate_neighbour->getNeighbour(south);
                case sw:
                    return intermediate_neighbour->getNeighbour(south);
            }
        }

    private:
        inline static map<Direction, vector<DiagonalDirection>> nm = {
                {north, {sw, nw, se, ne, nw, sw, se}},
                {east,  {nw, ne, sw, se, ne, nw, sw}},
                {south, {nw, sw, ne, se, sw, nw, ne}},
                {west,  {ne, nw, se, sw, nw, ne, se}}
        };
    };

}

#endif //SIMULATION_TREEWITHNEIGHBOURS_H
