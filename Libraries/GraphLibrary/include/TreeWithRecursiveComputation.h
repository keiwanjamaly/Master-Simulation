//
// Created by Keiwan Jamaly on 14.12.22.
//

#ifndef SIMULATION_TREEWITHRECURSIVECOMPUTATION_H
#define SIMULATION_TREEWITHRECURSIVECOMPUTATION_H

#include "TreeWithComparisons.h"

namespace gl {
    template<class T, DataConcept Data, class Config>
    class TreeWithRecursiveComputation : public TreeWithComparisons<T, Data, Config> {
    public:
        TreeWithRecursiveComputation(double x, double y, double width, double height, shared_ptr<Config> config,
                                     int maxDepth = 5) :
                TreeWithComparisons<T, Data, Config>(x, y, width, height, config),
                m_maxDepth{maxDepth} {
        }

        TreeWithRecursiveComputation(shared_ptr<T> parent, DiagonalDirection dir) :
                TreeWithComparisons<T, Data, Config>(parent, dir) {
            m_maxDepth = this->getParent()->getMaxDepth();
        }

        int getMaxDepth() { return m_maxDepth; };
    private:
        int m_maxDepth;
    };
}


#endif //SIMULATION_TREEWITHRECURSIVECOMPUTATION_H
