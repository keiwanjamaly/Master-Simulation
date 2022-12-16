//
// Created by Keiwan Jamaly on 16.12.22.
//

#ifndef SIMULATION_TREEWITHBLOCKING_H
#define SIMULATION_TREEWITHBLOCKING_H

#include "TreeWithRecursiveComputation.h"

namespace gl {
    template<class T, DataConcept Data, class Config>
    class TreeWithBlocking : public TreeWithRecursiveComputation<T, Data, Config> {
    public:
        using TreeWithRecursiveComputation<T, Data, Config>::TreeWithRecursiveComputation;

        static shared_ptr<T> generate_root(double x, double y,
                                           double width,
                                           double height,
                                           shared_ptr<Config> config, int maxDepth = 5) {
            auto root = make_shared<T>(x, y, width * 2, height * 2, config, maxDepth);
            auto childNW = make_shared<T>(root, nw);
            root->setChild(childNW, nw);
            auto childNE = make_shared<T>(root, ne);
            root->setChild(childNE, ne);
            auto childSW = make_shared<T>(root, sw);
            root->setChild(childSW, sw);
            auto childSE = make_shared<T>(root, se);
            root->setChild(childSE, se);

            childNW->setChild(make_shared<T>(childNW, se), se);
            childNE->setChild(make_shared<T>(childNE, sw), sw);
            childSW->setChild(make_shared<T>(childSW, ne), ne);
            childSE->setChild(make_shared<T>(childSE, nw), nw);

            return root;
        }

        void block() {
            m_blocked = true;
        }

        bool isBlocked() {
            return m_blocked;
        }

    private:
        bool m_blocked = false;
    };
}

#endif //SIMULATION_TREEWITHBLOCKING_H
