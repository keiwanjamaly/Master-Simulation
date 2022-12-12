//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_TREE_H
#define SIMULATION_TREE_H

#include "GraphLibrary_Types.h"

namespace gl {
    template<class T>
    class Tree : public std::enable_shared_from_this<T> {
    public:
        Tree() = default;

        explicit Tree(shared_ptr<T> parent) : m_parent{parent} {}

        void attachLeaves() {
            if (hasChildren()) {
                throw std::runtime_error("tried to attach children, but there are already children attached!");
            } else
                m_children[nw] = make_shared<T>(this->shared_from_this());
            m_children[ne] = make_shared<T>(this->shared_from_this());
            m_children[sw] = make_shared<T>(this->shared_from_this());
            m_children[se] = make_shared<T>(this->shared_from_this());
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        void getAllLeafs(std::vector<shared_ptr<T>> &vec) {
            vec.push_back(this->shared_from_this());
            if (hasChildren()) {
                this->getChild(nw)->getAllLeafs(vec);
                this->getChild(ne)->getAllLeafs(vec);
                this->getChild(sw)->getAllLeafs(vec);
                this->getChild(se)->getAllLeafs(vec);
            }
        }

#pragma clang diagnostic pop

        bool isRoot() {
            if (m_parent == nullptr)
                return true;
            else
                return false;
        }

        shared_ptr<T> getChildOfParent(DiagonalDirection dir) {
            if (isRoot())
                throw std::runtime_error("there is no parent, this is root");
            else
                return m_parent->getChild(dir)->shared_from_this();
        }


        virtual shared_ptr<T> getChild(DiagonalDirection dir) {
            if (hasChildren())
                return m_children[dir];
            else
                return nullptr;
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        int getDepth() {
            if (isRoot())
                return 0;
            else
                return m_parent->getDepth() + 1;
        }

#pragma clang diagnostic pop

        bool hasChildren() {
            return !m_children.empty();
        }

        shared_ptr<T> getParent() const { return m_parent; };

    private:
        shared_ptr<T> m_parent{nullptr};
        // make sure, that the children are only accessed with getChild, even within the class!
        map<DiagonalDirection, shared_ptr<T>> m_children;
    };
}
#endif //SIMULATION_TREE_H
