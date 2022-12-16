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
            m_finishedSplitting = m_splittingPromise.get_future();
        }

        TreeWithRecursiveComputation(shared_ptr<T> parent, DiagonalDirection dir) :
                TreeWithComparisons<T, Data, Config>(parent, dir) {
            m_maxDepth = this->getParent()->getMaxDepth();
            m_finishedSplitting = m_splittingPromise.get_future();
        }

        void compute(bool force = true) {
//            std::cout << this->printPath() << " " << this->should_be_split() << std::endl;
            if (this->getDepth() <= getMaxDepth()) {
                if (this->should_be_split() or force) {
                    this->attachLeaves();
                    m_splittingPromise.set_value();
                    m_computeFutureNW = std::async(std::launch::async,
                                                   [this]() -> void { Tree<T>::getChild(nw)->compute(false); });
                    m_computeFutureNE = std::async(std::launch::async,
                                                   [this]() -> void { Tree<T>::getChild(ne)->compute(false); });
                    m_computeFutureSW = std::async(std::launch::async,
                                                   [this]() -> void { Tree<T>::getChild(sw)->compute(false); });
                    m_computeFutureSE = std::async(std::launch::async,
                                                   [this]() -> void { Tree<T>::getChild(se)->compute(false); });
                    m_computeFutureNW.wait();
                    m_computeFutureNE.wait();
                    m_computeFutureSW.wait();
                    m_computeFutureSE.wait();
                } else {
                    m_splittingPromise.set_value();
                }
            } else
                m_splittingPromise.set_value();
        }

        bool hasChildren() {
            waitForSplittingToFinish();
            return Tree<T>::hasChildren();
        }

        shared_ptr<T> getChild(DiagonalDirection dir) final {
            shared_ptr<T> child = Tree<T>::getChild(dir);
            child->waitForComputationComplete();
            return child;
        }

        void waitForSplittingToFinish() {
            m_finishedSplitting.wait();
        }

        int getMaxDepth() { return m_maxDepth; };

    private:
        int m_maxDepth;
        std::promise<void> m_splittingPromise;
        std::shared_future<void> m_finishedSplitting;
        std::future<void> m_computeFutureNW, m_computeFutureNE, m_computeFutureSW, m_computeFutureSE;
    };
}


#endif //SIMULATION_TREEWITHRECURSIVECOMPUTATION_H
