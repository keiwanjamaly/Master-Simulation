#ifndef SIMULATION_TREEWITHDATA_H
#define SIMULATION_TREEWITHDATA_H

#include "TreeWithCoordinates.h"
#include "GraphLibrary_Types.h"
#include "BS_thread_pool.hpp"

namespace gl {
    template<class T, DataConcept Data, class Config>
    class TreeWithData : public TreeWithCoordinates<T> {
    public:
        TreeWithData(double x, double y, double width, double height, shared_ptr<Config> config) :
                TreeWithCoordinates<T>(x, y, width, height), m_config{config} {
            m_pool = make_shared<BS::thread_pool>();
            initializeDataAndCompute();
        }

        TreeWithData(shared_ptr<T> parent, DiagonalDirection dir) :
                TreeWithCoordinates<T>(parent, dir) {
            m_pool = this->getParent()->getPoolPointer();
            m_config = this->getParent()->getConfigPointer();
            initializeDataAndCompute();
        }

        void initializeDataAndCompute() {
            m_data = make_shared<Data>(this->getX(), this->getY(), m_config);
            m_computing = m_pool->submit([this]() -> void { m_data->compute(); });
        }

        shared_ptr<BS::thread_pool> getPoolPointer() { return m_pool; };

        shared_ptr<Config> getConfigPointer() { return m_config; };

        shared_ptr<Config> getConfig() { return m_config; };

        void waitForComputationComplete() {
            m_computing.wait();
        }

        shared_ptr<Data> getDataPointer() {
            waitForComputationComplete();
            return m_data;
        }

    private:
        shared_ptr<Data> m_data;
        shared_ptr<Config> m_config;

        shared_ptr<BS::thread_pool> m_pool;
        std::shared_future<void> m_computing;
    };
}

#endif //SIMULATION_TREEWITHDATA_H