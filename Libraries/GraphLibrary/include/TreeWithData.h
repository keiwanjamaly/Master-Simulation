#ifndef SIMULATION_TREEWITHDATA_H
#define SIMULATION_TREEWITHDATA_H

#include "TreeWithCoordinates.h"
#include "TreeWithNeighbours.h"
#include "GraphLibrary_Types.h"
#include "BS_thread_pool.hpp"

namespace gl {
    template<GraphConcept T, ConfigConcept Config>
    class TreeWithData
            : public TreeWithCoordinates<TreeWithData<T, Config>>,
              public TreeWithNeighbours<TreeWithData<T, Config>> {
    public:
        TreeWithData(double x, double y, double width, double height, shared_ptr<Config> config, int maxDepth = 5) :
                TreeWithNeighbours<TreeWithData<T, Config>>(),
                TreeWithCoordinates<TreeWithData<T, Config>>(x, y, width, height),
                m_maxDepth{maxDepth}, m_config{config} {
            m_pool = make_shared<BS::thread_pool>();
        }

        TreeWithData(shared_ptr<TreeWithData> parent, DiagonalDirection dir) :
                TreeWithNeighbours<TreeWithData<T, Config>>(parent, dir),
                TreeWithCoordinates<TreeWithData<T, Config>>(parent, dir) {
            m_pool = this->getParent()->getPoolPointer();
            m_maxDepth = this->getParent()->getMaxDepth();
            m_config = this->getParent()->getConfigPointer();
        }

        shared_ptr<BS::thread_pool> getPoolPointer() { return m_pool; };

        int getMaxDepth() { return m_maxDepth; };

        shared_ptr<Config> getConfigPointer() { return m_config; };

    private:
        shared_ptr<T> m_data;
        shared_ptr<BS::thread_pool> m_pool;
        shared_ptr<Config> m_config;
        int m_maxDepth;
    };
}

#endif //SIMULATION_TREEWITHDATA_H
