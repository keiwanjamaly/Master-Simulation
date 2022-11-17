//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAF_H
#define SIMULATION_LEAF_H

#include "Types_Leaf.h"
#include <vector>
#include <array>
#include <map>
#include <thread>
#include <memory>

namespace dp {

    using std::shared_ptr;

    template<Graph_Data T, class Config>
    class Leaf : public std::enable_shared_from_this<Leaf<T, Config>> {
    public:
        double box_size{};
        std::vector<shared_ptr<Leaf<T, Config>>> children;
        shared_ptr<Leaf<T, Config>> parent{nullptr};
        shared_ptr<T> data;
        shared_ptr<Config> config;

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

        explicit Leaf(double x_, double y_, double initial_box_size_,
                      bool (*split_condition_)(std::vector<double>, std::vector<double>), shared_ptr<Config> config_)
                : x{x_}, y{y_},
                  box_size{initial_box_size_},
                  split_condition{split_condition_},
                  config{config_} {
            data = std::make_shared<T>(x, y, config);
        }

        explicit Leaf(DiagonalDirection dir, shared_ptr<Leaf<T, Config>> parent_, shared_ptr<Config> config_) : parent{
                parent_}, config{
                config_} {
            box_size = parent->box_size / 2.0;
            double position_offset = box_size / 2.0;
            switch (dir) {
                case nw:
                    x = parent->x - position_offset;
                    y = parent->y + position_offset;
                    break;
                case ne:
                    x = parent->x + position_offset;
                    y = parent->y + position_offset;
                    break;
                case sw:
                    x = parent->x - position_offset;
                    y = parent->y - position_offset;
                    break;
                case se:
                    x = parent->x + position_offset;
                    y = parent->y - position_offset;
                    break;
            }
            data = std::make_shared<T>(x, y, config);

            split_condition = parent->split_condition;
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

            // if leaf is a root itself
            if (this->isRoot()) {
                return nullptr;
            }
            // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
            if (this->get_child_of_parent(nm[dir][0]) == this->shared_from_this()) {
                return this->get_child_of_parent(nm[dir][1]);
            } else if (this->get_child_of_parent(nm[dir][2]) == this->shared_from_this()) {
                return this->get_child_of_parent(nm[dir][3]);
            }
            // find recursively the north get_diagonal_neighbour
            shared_ptr<Leaf<T, Config>> mu = parent->get_neighbour(dir, false);
            shared_ptr<Leaf<T, Config>> result;
            if (mu == nullptr or mu->children.size() == 0) {
                result = mu;
            } else if (this->get_child_of_parent(nm[dir][4]) == this->shared_from_this()) {
                result = mu->children[nm[dir][5]];
            } else {
                result = mu->children[nm[dir][6]];
            }

            if (!initial)
                return result;
            else if (result != nullptr and this->get_depth() == result->get_depth())
                return result;
            else
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

        void balance_tree(bool force = false) {
            if (this->children.size() == 0) {
                if (force || this->should_be_split()) {
                    this->attach_leaves();
                }
            } else {
                this->children[nw]->balance_tree(force);
                this->children[ne]->balance_tree(force);
                this->children[sw]->balance_tree(force);
                this->children[se]->balance_tree(force);
            }
        }
    };


} // dp

#endif //SIMULATION_LEAF_H
