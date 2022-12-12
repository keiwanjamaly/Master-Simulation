//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_TREEWITHNEIGHBOURS_H
#define SIMULATION_TREEWITHNEIGHBOURS_H

#include "Tree.h"

namespace gl {

    class TreeWithNeighbours : public Tree<TreeWithNeighbours> {
    public:
        using Tree::Tree;

        shared_ptr<TreeWithNeighbours> getNeighbour(Direction dir, bool initial = true) {

            shared_ptr<TreeWithNeighbours> result, mu;
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
                if (result == nullptr)
                    return result;
                else if (this->getDepth() == result->getDepth())
                    return result;
                else
                    return nullptr;
            } else
                return result;
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
