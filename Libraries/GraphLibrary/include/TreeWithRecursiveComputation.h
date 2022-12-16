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
                m_maxDepth{maxDepth} {}

        TreeWithRecursiveComputation(shared_ptr<T> parent, DiagonalDirection dir) :
                TreeWithComparisons<T, Data, Config>(parent, dir) {
            m_maxDepth = this->getParent()->getMaxDepth();
        }

        void compute(bool force = true) {
//            std::cout << this->printPath() << " " << this->should_be_split() << std::endl;
            if (this->getDepth() <= getMaxDepth()) {
                if (this->should_be_split() or force) {
                    if (!Tree<T>::hasChildren())
                        this->attachLeaves();
                    m_splittingPromise.set_value();

                    // all this below is for calculating with trees, which have not 4 leafs;
                    auto child_nw = Tree<T>::getChild(nw);
                    if (child_nw != nullptr)
                        m_computeFutureNW = std::async(std::launch::async,
                                                       [child_nw]() -> void { child_nw->compute(false); });
                    auto child_ne = Tree<T>::getChild(ne);
                    if (child_ne != nullptr)
                        m_computeFutureNE = std::async(std::launch::async,
                                                       [child_ne]() -> void { child_ne->compute(false); });
                    auto child_sw = Tree<T>::getChild(sw);
                    if (child_sw != nullptr)
                        m_computeFutureSW = std::async(std::launch::async,
                                                       [child_sw]() -> void { child_sw->compute(false); });
                    auto child_se = Tree<T>::getChild(se);
                    if (child_se != nullptr)
                        m_computeFutureSE = std::async(std::launch::async,
                                                       [child_se]() -> void { child_se->compute(false); });
                    if (child_nw != nullptr)
                        m_computeFutureNW.wait();
                    if (child_ne != nullptr)
                        m_computeFutureNE.wait();
                    if (child_sw != nullptr)
                        m_computeFutureSW.wait();
                    if (child_se != nullptr)
                        m_computeFutureSE.wait();
                } else {
                    m_splittingPromise.set_value();
                }
            } else {
                m_splittingPromise.set_value();
            }
        }

        bool hasChildren() {
            waitForSplittingToFinish();
            return Tree<T>::hasChildren();
        }

        shared_ptr<T> getChild(DiagonalDirection dir) final {
            shared_ptr<T> child = Tree<T>::getChild(dir);
            if (child != nullptr)
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
        std::shared_future<void> m_finishedSplitting = m_splittingPromise.get_future();
        std::future<void> m_computeFutureNW, m_computeFutureNE, m_computeFutureSW, m_computeFutureSE;
    };
}


#endif //SIMULATION_TREEWITHRECURSIVECOMPUTATION_H
