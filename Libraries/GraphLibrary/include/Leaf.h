//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAF_H
#define SIMULATION_LEAF_H

#include "Types.h"
#include <vector>
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


        // Default constructor
        explicit Leaf() = default;

        explicit Leaf(double x_, double y_, double initial_box_size_,
                      bool (*split_condition_)(std::vector<double>, std::vector<double>));

        explicit Leaf(ChildDirection dir, Leaf<T> *parent_);

        void attach_leaves();

        void compute();

        bool isRoot();

        Leaf<T> *get_child_of_parent(ChildDirection dir);

        int get_depth();

        Leaf<T> *north_neighbour(bool initial = true);

        Leaf<T> *east_neighbour(bool initial = true);

        Leaf<T> *south_neighbour(bool initial = true);

        Leaf<T> *west_neighbour(bool initial = true);

        bool north_comparison();

        bool east_comparison();

        bool south_comparison();

        bool west_comparison();

        bool should_be_split();

        bool balance_tree(bool force = false);

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
    Leaf<T>::Leaf(ChildDirection dir, Leaf<T> *parent_) : parent{parent_} {
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
    void Leaf<T>::compute() {
        data.compute();
        if (children.size() == 4) {
            std::thread thread_nw = std::thread(&Leaf<T>::compute, &children[nw]);
            std::thread thread_ne = std::thread(&Leaf<T>::compute, &children[ne]);
            std::thread thread_sw = std::thread(&Leaf<T>::compute, &children[sw]);
            std::thread thread_se = std::thread(&Leaf<T>::compute, &children[se]);

            thread_nw.join();
            thread_ne.join();
            thread_sw.join();
            thread_se.join();
        }
    }

    template<Graph_Data T>
    bool Leaf<T>::isRoot() {
        if (parent == nullptr)
            return true;
        else
            return false;
    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::get_child_of_parent(ChildDirection dir) {
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
    Leaf<T> *Leaf<T>::north_neighbour(bool initial) {
        // if leaf is a root itself
        if (this->isRoot()) {
            return nullptr;
        }
        // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
        if (this->get_child_of_parent(sw) == this) {
            return this->get_child_of_parent(nw);
        } else if (this->get_child_of_parent(se) == this) {
            return this->get_child_of_parent(ne);
        }
        // find recursively the north neighbour
        Leaf<T> *mu = parent->north_neighbour(false);
        Leaf<T> *result;
        if (mu == nullptr or mu->children.size() == 0) {
            result = mu;
        } else if (this->get_child_of_parent(nw) == this) {
            result = &(mu->children[sw]);
        } else {
            result = &(mu->children[se]);
        }

        if (!initial)
            return result;
        else if (result != nullptr and this->get_depth() == result->get_depth())
            return result;
        else
            return nullptr;

    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::east_neighbour(bool initial) {
        // if leaf is a root itself
        if (this->isRoot()) {
            return nullptr;
        }
        // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
        if (this->get_child_of_parent(nw) == this) {
            return this->get_child_of_parent(ne);
        } else if (this->get_child_of_parent(sw) == this) {
            return this->get_child_of_parent(se);
        }
        // find recursively the north neighbour
        Leaf<T> *mu = parent->east_neighbour(false);
        Leaf<T> *result;
        if (mu == nullptr or mu->children.size() == 0) {
            result = mu;
        } else if (this->get_child_of_parent(ne) == this) {
            result = &(mu->children[nw]);
        } else {
            result = &(mu->children[sw]);
        }

        if (!initial)
            return result;
        else if (result != nullptr and this->get_depth() == result->get_depth())
            return result;
        else
            return nullptr;

    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::south_neighbour(bool initial) {
        // if leaf is a root itself
        if (this->isRoot()) {
            return nullptr;
        }
        // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
        if (this->get_child_of_parent(nw) == this) {
            return this->get_child_of_parent(sw);
        } else if (this->get_child_of_parent(ne) == this) {
            return this->get_child_of_parent(se);
        }
        // find recursively the north neighbour
        Leaf<T> *mu = parent->south_neighbour(false);
        Leaf<T> *result;
        if (mu == nullptr or mu->children.size() == 0) {
            result = mu;
        } else if (this->get_child_of_parent(sw) == this) {
            result = &(mu->children[nw]);
        } else {
            result = &(mu->children[ne]);
        }

        if (!initial)
            return result;
        else if (result != nullptr and this->get_depth() == result->get_depth())
            return result;
        else
            return nullptr;
    }

    template<Graph_Data T>
    Leaf<T> *Leaf<T>::west_neighbour(bool initial) {
        // if leaf is a root itself
        if (this->isRoot()) {
            return nullptr;
        }
        // if leaf is sw (or se) child of parend, just return nw (or ne) child of parent
        if (this->get_child_of_parent(ne) == this) {
            return this->get_child_of_parent(nw);
        } else if (this->get_child_of_parent(se) == this) {
            return this->get_child_of_parent(sw);
        }
        // find recursively the north neighbour
        Leaf<T> *mu = parent->west_neighbour(false);
        Leaf<T> *result;
        if (mu == nullptr or mu->children.size() == 0) {
            result = mu;
        } else if (this->get_child_of_parent(nw) == this) {
            result = &(mu->children[ne]);
        } else {
            result = &(mu->children[se]);
        }

        if (!initial)
            return result;
        else if (result != nullptr and this->get_depth() == result->get_depth())
            return result;
        else
            return nullptr;
    }

    template<Graph_Data T>
    bool Leaf<T>::north_comparison() {
        return false;
    }

    template<Graph_Data T>
    bool Leaf<T>::east_comparison() {
        return false;
    }

    template<Graph_Data T>
    bool Leaf<T>::south_comparison() {
        return false;
    }

    template<Graph_Data T>
    bool Leaf<T>::west_comparison() {
        return false;
    }

    template<Graph_Data T>
    bool Leaf<T>::should_be_split() {
        return false;
    }

    template<Graph_Data T>
    bool Leaf<T>::balance_tree(bool force) {
        return false;
    }


} // dp

#endif //SIMULATION_LEAF_H
