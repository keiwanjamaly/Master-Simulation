//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_TREEWITHNEIGHBOURS_H
#define SIMULATION_TREEWITHNEIGHBOURS_H

#include "Tree.h"

namespace gl {

    class TreeWithNeighbours : private Tree {
    public:
        using Tree::Tree;

        shared_ptr<TreeWithNeighbours> getNeighbour(Direction dir, bool initial = true) {

            shared_ptr<TreeWithNeighbours> result;
            // if leaf is a root itself
            if (this->isRoot()) {
                return nullptr;
            }
            // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
            if (this->getChildOfParent(nm[dir][0]) == this->shared_from_this()) {
                result = this->getChildOfParent(nm[dir][1]);
            } else if (this->getChildOfParent(nm[dir][2]) == this->shared_from_this()) {
                result = this->getChildOfParent(nm[dir][3]);
            } else {
                // find recursively the north get_diagonal_neighbour
                shared_ptr<TreeWithNeighbours> mu = getParent()->getNeighbour(dir, false);
                if (mu == nullptr or mu->hasChildren()) {
                    result = mu;
                } else if (this->getChildOfParent(nm[dir][4]) == this->shared_from_this()) {
                    result = mu->getChild(nm[dir][5]);
                } else {
                    result = mu->getChild(nm[dir][6]);
                }
            }

            if (!initial)
                return result;
            else if (result != nullptr and this->getDepth() == result->getDepth()) {
                return result;
            } else
                return nullptr;
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
