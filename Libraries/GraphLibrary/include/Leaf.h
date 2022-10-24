//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAF_H
#define SIMULATION_LEAF_H

#include "Types.h"
#include <array>
#include <map>
#include <thread>

namespace dp {


    template<Graph_Data T>
    class Leaf {
    public:
        double box_size{};
        std::vector<Leaf<T>> children;
        Leaf<T> *parent{nullptr};
        T data;
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
                      bool (*split_condition_)(std::vector<double>, std::vector<double>));

        explicit Leaf(DiagonalDirection dir, Leaf<T> *parent_);

        void attach_leaves();

        std::vector<Leaf<T> *> get_all_leafs();

        bool isRoot();

        Leaf<T> *get_child_of_parent(DiagonalDirection dir);

        int get_depth();

        Leaf<T> *get_neighbour(Direction dir, bool initial = true);

        Leaf<T> *get_diagonal_neighbour(DiagonalDirection dir);

        bool comparison(Direction dir);

        bool comparison(DiagonalDirection dir);

        bool should_be_split();

        void balance_tree(bool force = false);

    };

    template<Graph_Data T>
    Leaf<T>::Leaf(double x_, double y_, double initial_box_size_,
                  bool (*split_condition_)(std::vector<double>, std::vector<double>)) : x{x_}, y{y_},
                                                                                        box_size{initial_box_size_},
                                                                                        split_condition{
                                                                                                split_condition_} {
        data = T(x, y);
    }

    template<Graph_Data T>
    Leaf<T>::Leaf(DiagonalDirection dir, Leaf<T> *parent_) : parent{parent_} {
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
        data = T(x, y);

        split_condition = parent->split_condition;
    }

    template<Graph_Data T>
    void Leaf<T>::attach_leaves() {
        if (children.size() == 0) {
            children.push_back(Leaf<T>(nw, this));
            children.push_back(Leaf<T>(ne, this));
            children.push_back(Leaf<T>(sw, this));
            children.push_back(Leaf<T>(se, this));
        }
    }

    template<Graph_Data T>
    std::vector<Leaf<T> *> Leaf<T>::get_all_leafs() {
        std::vector<Leaf<T> *> v = {};
        if (this->children.size() == 4) {
            std::vector<Leaf<T> *> leaf_nw = this->children[nw].get_all_leafs();
            std::vector<Leaf<T> *> leaf_ne = this->children[ne].get_all_leafs();
            std::vector<Leaf<T> *> leaf_sw = this->children[sw].get_all_leafs();
            std::vector<Leaf<T> *> leaf_se = this->children[se].get_all_leafs();
            v.insert(v.end(), leaf_nw.begin(), leaf_nw.end());
            v.insert(v.end(), leaf_ne.begin(), leaf_ne.end());
            v.insert(v.end(), leaf_sw.begin(), leaf_sw.end());
            v.insert(v.end(), leaf_se.begin(), leaf_se.end());
        }
        v.push_back(this);
        return v;
    }

    template<Graph_Data T>
    bool Leaf<T>::isRoot() {
        if (parent == nullptr)
            return true;
        else
            return false;
    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::get_child_of_parent(DiagonalDirection dir) {
        if (parent == nullptr)
            return nullptr;
        else
            return &(parent->children[dir]);
    }

    template<Graph_Data T>
    int Leaf<T>::get_depth() {
        if (parent == nullptr)
            return 0;
        else
            return parent->get_depth() + 1;
    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::get_neighbour(Direction dir, bool initial) {
        if (this == nullptr)
            return nullptr;

        // if leaf is a root itself
        if (this->isRoot()) {
            return nullptr;
        }
        // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
        if (this->get_child_of_parent(nm[dir][0]) == this) {
            return this->get_child_of_parent(nm[dir][1]);
        } else if (this->get_child_of_parent(nm[dir][2]) == this) {
            return this->get_child_of_parent(nm[dir][3]);
        }
        // find recursively the north get_diagonal_neighbour
        Leaf<T> *mu = parent->get_neighbour(dir, false);
        Leaf<T> *result;
        if (mu == nullptr or mu->children.size() == 0) {
            result = mu;
        } else if (this->get_child_of_parent(nm[dir][4]) == this) {
            result = &(mu->children[nm[dir][5]]);
        } else {
            result = &(mu->children[nm[dir][6]]);
        }

        if (!initial)
            return result;
        else if (result != nullptr and this->get_depth() == result->get_depth())
            return result;
        else
            return nullptr;
    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::get_diagonal_neighbour(DiagonalDirection dir) {
        Leaf<T> *intermediate_neighbour;
        switch (dir) {
            case nw:
                intermediate_neighbour = this->get_neighbour(west);
                return intermediate_neighbour->get_neighbour(north);
            case ne:
                intermediate_neighbour = this->get_neighbour(east);
                return intermediate_neighbour->get_neighbour(north);
            case se:
                intermediate_neighbour = this->get_neighbour(east);
                return intermediate_neighbour->get_neighbour(south);
            case sw:
                intermediate_neighbour = this->get_neighbour(west);
                return intermediate_neighbour->get_neighbour(south);
        }
    }

    template<Graph_Data T>
    bool Leaf<T>::comparison(Direction dir) {
        Leaf<T> *neighbour = this->get_neighbour(dir);
        if (neighbour == nullptr)
            return false;
        else
            return split_condition(this->data.splitDecisionData(), neighbour->data.splitDecisionData());
    }

    template<Graph_Data T>
    bool Leaf<T>::comparison(DiagonalDirection dir) {
        Leaf<T> *neighbour = this->get_diagonal_neighbour(dir);
        if (neighbour == nullptr)
            return false;
        else
            return split_condition(this->data.splitDecisionData(), neighbour->data.splitDecisionData());
    }

    template<Graph_Data T>
    bool Leaf<T>::should_be_split() {
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

    template<Graph_Data T>
    void Leaf<T>::balance_tree(bool force) {
        if (this->children.size() == 0) {
            if (force || this->should_be_split()) {
                this->attach_leaves();
            }
        } else {
            this->children[nw].balance_tree(force);
            this->children[ne].balance_tree(force);
            this->children[sw].balance_tree(force);
            this->children[se].balance_tree(force);
        }
    }


} // dp

#endif //SIMULATION_LEAF_H
