//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_LEAF2_H
#define SIMULATION_LEAF2_H

#include "BS_thread_pool.hpp"
#include "GraphLibrary_Types.h"

namespace Leaf {
//    std::map<Direction, vector<DiagonalDirection>> nm{
//            {north, {sw, nw, se, ne, nw, sw, se}},
//            {east,  {nw, ne, sw, se, ne, nw, sw}},
//            {south, {nw, sw, ne, se, sw, nw, ne}},
//            {west,  {ne, nw, se, sw, nw, ne, se}}
//    };



//    template<Graph_Data T, Config_Data Config>
//    class Leaf : public std::enable_shared_from_this<Leaf<T, Config>> {
//    public:
//        explicit Leaf() = delete;
//
//        explicit Leaf(double x, double y, double initialBoxSizeX, double initialBoxSizeY,
//                      shared_ptr<Config> config)
//                : m_x{x}, m_y{y},
//                  m_boxSizeX{initialBoxSizeX},
//                  m_boxSizeY{initialBoxSizeY},
//                  m_config{config} {
//
//            m_pool = std::make_shared<BS::thread_pool>();
//            m_data = std::make_shared<T>(config->copyAndSetXY(x, y));
//        }
//
//    private:
//        // variables for position estimation
//        double m_boxSizeX, m_boxSizeY;
//        double m_x, m_y;
//
//        shared_ptr<Config> m_config;
//        shared_ptr<T> m_data;
//        bool m_block = false;
//
//        // variables for threaded calculation
//        shared_ptr<BS::thread_pool> m_pool;
//        future<void> m_finishedCalculatingFuture;
//    };

}
#endif //SIMULATION_LEAF2_H
