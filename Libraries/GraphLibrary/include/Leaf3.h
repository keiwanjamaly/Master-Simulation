//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAF3_H
#define SIMULATION_LEAF3_H

#include "GraphLibrary_Types.h"
#include "BS_thread_pool.hpp"
#include <vector>
#include <array>
#include <map>
#include <thread>
#include <memory>

namespace dp {

    using std::shared_ptr;

    template<Graph_Data T, Config_Data Config>
    class Leaf : public std::enable_shared_from_this<Leaf<T, Config>> {
    public:
        double box_size_x, box_size_y;
        std::vector<shared_ptr<Leaf<T, Config>>> children;
        shared_ptr<Leaf<T, Config>> parent{nullptr};
        shared_ptr<T> data;
        shared_ptr<Config> config;
        std::future<void> finished_splitting_future;
        shared_ptr<BS::thread_pool> pool;
        int max_depth;

        bool block = false;

        double x{}, y{};

        bool (*split_condition)(std::vector<double>, std::vector<double>){};

        std::map<Direction, std::array<DiagonalDirection, 7>> nm{
                {north, {sw, nw, se, ne, nw, sw, se}},
                {east,  {nw, ne, sw, se, ne, nw, sw}},
                {south, {nw, sw, ne, se, sw, nw, ne}},
                {west,  {ne, nw, se, sw, nw, ne, se}}
        };

        // Default constructor
        explicit Leaf() = default;

        explicit Leaf(double x_, double y_, double initial_box_size_x_, double initial_box_size_y_,
                      bool (*split_condition_)(std::vector<double>, std::vector<double>), shared_ptr<Config> config_,
                      int max_depth_)
                : x{x_}, y{y_},
                  box_size_x{initial_box_size_x_},
                  box_size_y{initial_box_size_y_},
                  split_condition{split_condition_},
                  config{config_},
                  max_depth{max_depth_} {

            pool = std::make_shared<BS::thread_pool>();
            data = std::make_shared<T>(config->copyAndSetXY(x, y));
            compute();
        }

        explicit Leaf(DiagonalDirection dir, shared_ptr<Leaf<T, Config>> parent_, shared_ptr<Config> config_) : parent{
                parent_}, config{
                config_} {
            box_size_x = parent->box_size_x / 2.0;
            box_size_y = parent->box_size_y / 2.0;
            double position_offset_x = box_size_x / 2.0;
            double position_offset_y = box_size_y / 2.0;
            switch (dir) {
                case nw:
                    x = parent->x - position_offset_x;
                    y = parent->y + position_offset_y;
                    break;
                case ne:
                    x = parent->x + position_offset_x;
                    y = parent->y + position_offset_y;
                    break;
                case sw:
                    x = parent->x - position_offset_x;
                    y = parent->y - position_offset_y;
                    break;
                case se:
                    x = parent->x + position_offset_x;
                    y = parent->y - position_offset_y;
                    break;
            }

            data = std::make_shared<T>(config->copyAndSetXY(x, y));
            pool = parent->pool;
            split_condition = parent->split_condition;
            max_depth = parent->max_depth;
            compute();
        }


        static shared_ptr<Leaf<T, Config>> generate_root(double x_, double y_,
                                                         double initial_box_size_x_,
                                                         double initial_box_size_y_,
                                                         bool (*split_condition_)(std::vector<double>,
                                                                                  std::vector<double>),
                                                         shared_ptr<Config> config_) {
            shared_ptr<Leaf<T, Config>> root = std::make_shared<Leaf<T, Config>>(x_, y_, initial_box_size_x_ * 2,
                                                                                 initial_box_size_y_ * 2,
                                                                                 split_condition_, config_);

            root->attach_leaves();
            for (shared_ptr<Leaf<T, Config>> &child: root->children)
                child->attach_leaves();

            // block nw children
            root->children[nw]->children[nw]->block = true;
            root->children[nw]->children[ne]->block = true;
            root->children[nw]->children[sw]->block = true;

            // block ne children
            root->children[ne]->children[nw]->block = true;
            root->children[ne]->children[ne]->block = true;
            root->children[ne]->children[se]->block = true;

            // block sw children
            root->children[sw]->children[nw]->block = true;
            root->children[sw]->children[sw]->block = true;
            root->children[sw]->children[se]->block = true;

            // block se children
            root->children[se]->children[ne]->block = true;
            root->children[se]->children[sw]->block = true;
            root->children[se]->children[se]->block = true;

            return root;
        }

        void attach_leaves() {
            if (children.size() == 0) {
                children.reserve(4);
                children.push_back(
                        std::make_shared<Leaf<T, Config>>(Leaf<T, Config>(nw, this->shared_from_this(), config)));
                children.push_back(
                        std::make_shared<Leaf<T, Config>>(Leaf<T, Config>(ne, this->shared_from_this(), config)));
                children.push_back(
                        std::make_shared<Leaf<T, Config>>(Leaf<T, Config>(sw, this->shared_from_this(), config)));
                children.push_back(
                        std::make_shared<Leaf<T, Config>>(Leaf<T, Config>(se, this->shared_from_this(), config)));
            }
        }

        std::vector<shared_ptr<Leaf<T, Config>>> get_all_leafs() {
            std::vector<shared_ptr<Leaf<T, Config>>> v = {};
            if (this->children.size() == 4) {
                std::vector<shared_ptr<Leaf<T, Config>>> leaf_nw = this->children[nw]->get_all_leafs();
                std::vector<shared_ptr<Leaf<T, Config>>> leaf_ne = this->children[ne]->get_all_leafs();
                std::vector<shared_ptr<Leaf<T, Config>>> leaf_sw = this->children[sw]->get_all_leafs();
                std::vector<shared_ptr<Leaf<T, Config>>> leaf_se = this->children[se]->get_all_leafs();
                v.insert(v.end(), leaf_nw.begin(), leaf_nw.end());
                v.insert(v.end(), leaf_ne.begin(), leaf_ne.end());
                v.insert(v.end(), leaf_sw.begin(), leaf_sw.end());
                v.insert(v.end(), leaf_se.begin(), leaf_se.end());
            }
            if (!block)
                v.push_back(this->shared_from_this());
            return v;
        }

        bool isRoot() {
            if (parent == nullptr)
                return true;
            else
                return false;
        }

        shared_ptr<Leaf<T, Config>> get_child_of_parent(DiagonalDirection dir) {
            if (parent == nullptr)
                return nullptr;
            else
                return parent->children[dir]->shared_from_this();
        }

        int get_depth() {
            if (parent == nullptr)
                return 0;
            else
                return parent->get_depth() + 1;
        }

        shared_ptr<Leaf<T, Config>> get_neighbour(Direction dir, bool initial = true) {

            shared_ptr<Leaf<T, Config>> result;
            // if leaf is a root itself
            if (this->isRoot()) {
                return nullptr;
            }
            // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
            if (this->get_child_of_parent(nm[dir][0]) == this->shared_from_this()) {
                result = this->get_child_of_parent(nm[dir][1]);
            } else if (this->get_child_of_parent(nm[dir][2]) == this->shared_from_this()) {
                result = this->get_child_of_parent(nm[dir][3]);
            } else {
                // find recursively the north get_diagonal_neighbour
                shared_ptr<Leaf<T, Config>> mu = parent->get_neighbour(dir, false);
                if (mu == nullptr or mu->children.size() == 0) {
                    result = mu;
                } else if (this->get_child_of_parent(nm[dir][4]) == this->shared_from_this()) {
                    result = mu->children[nm[dir][5]];
                } else {
                    result = mu->children[nm[dir][6]];
                }
            }

            if (!initial)
                return result;
            else if (result != nullptr and this->get_depth() == result->get_depth() and !(result->block) and
                     !(this->block)) {
                return result;
            } else
                return nullptr;
        }

        shared_ptr<Leaf<T, Config>> get_diagonal_neighbour(DiagonalDirection dir) {
            shared_ptr<Leaf<T, Config>> intermediate_neighbour;
            switch (dir) {
                case nw:
                    intermediate_neighbour = this->get_neighbour(west);
                    break;
                case ne:
                    intermediate_neighbour = this->get_neighbour(east);
                    break;
                case se:
                    intermediate_neighbour = this->get_neighbour(east);
                    break;
                case sw:
                    intermediate_neighbour = this->get_neighbour(west);
                    break;
            }

            if (intermediate_neighbour == nullptr)
                return intermediate_neighbour;

            switch (dir) {
                case nw:
                    return intermediate_neighbour->get_neighbour(north);
                case ne:
                    return intermediate_neighbour->get_neighbour(north);
                case se:
                    return intermediate_neighbour->get_neighbour(south);
                case sw:
                    return intermediate_neighbour->get_neighbour(south);
            }
        }

        bool comparison(Direction dir) {
            shared_ptr<Leaf<T, Config>> neighbour = this->get_neighbour(dir);
            if (neighbour == nullptr)
                return false;
            else
                return split_condition(this->data->splitDecisionData(), neighbour->data->splitDecisionData());
        }

        bool comparison(DiagonalDirection dir) {
            shared_ptr<Leaf<T, Config>> neighbour = this->get_diagonal_neighbour(dir);
            if (neighbour == nullptr)
                return false;
            else
                return split_condition(this->data->splitDecisionData(), neighbour->data->splitDecisionData());
        }

        bool should_be_split() {
            bool north_comparison = this->comparison(north);
            bool east_comparison = this->comparison(east);
            bool south_comparison = this->comparison(south);
            bool west_comparison = this->comparison(west);
            bool northWest_comparison = this->comparison(nw);
            bool northEast_comparison = this->comparison(ne);
            bool southEast_comparison = this->comparison(se);
            bool southWest_comparison = this->comparison(sw);
            return north_comparison || east_comparison || south_comparison || west_comparison || northWest_comparison ||
                   northEast_comparison || southEast_comparison || southWest_comparison;
        }

    private:
        void compute() {
            std::future<void> is_computed = pool->submit([this]() { data->compute(); });
            is_computed.wait();
        }
    };


} // dp

#endif //SIMULATION_LEAF3_H
