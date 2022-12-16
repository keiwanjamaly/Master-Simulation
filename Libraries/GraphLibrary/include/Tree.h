#ifndef SIMULATION_TREE_H
#define SIMULATION_TREE_H

#include "GraphLibrary_Types.h"

namespace gl {
    template<class T>
    class Tree : public std::enable_shared_from_this<T> {
    public:
        Tree() = default;

        Tree(shared_ptr<T> parent, DiagonalDirection /* dir */) : m_parent{parent} {}

        void attachLeaves() {
            if (m_children.empty()) {
                setChild(make_shared<T>(this->shared_from_this(), nw), nw);
                setChild(make_shared<T>(this->shared_from_this(), ne), ne);
                setChild(make_shared<T>(this->shared_from_this(), sw), sw);
                setChild(make_shared<T>(this->shared_from_this(), se), se);
            } else
                throw std::runtime_error("failed to attach leafs, leafs already attached.");
        }

        void setChild(shared_ptr<T> child, DiagonalDirection dir) {
            m_children[dir] = child;
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        void getAllLeafs(std::vector<shared_ptr<T>> &vec) {
            vec.push_back(this->shared_from_this());
            if (hasChildren()) {
                if (this->getChild(nw) != nullptr)
                    this->getChild(nw)->getAllLeafs(vec);
                if (this->getChild(ne) != nullptr)
                    this->getChild(ne)->getAllLeafs(vec);
                if (this->getChild(sw) != nullptr)
                    this->getChild(sw)->getAllLeafs(vec);
                if (this->getChild(se) != nullptr)
                    this->getChild(se)->getAllLeafs(vec);
            }
        }

#pragma clang diagnostic pop

        bool isRoot() const {
            if (m_parent == nullptr)
                return true;
            else
                return false;
        }

        shared_ptr<T> getChildOfParent(DiagonalDirection dir) {
            if (isRoot())
                throw std::runtime_error("there is no parent, this is root");
            else {
                if (m_parent->getChild(dir) != nullptr)
                    return m_parent->getChild(dir)->shared_from_this();
                else
                    return nullptr;
            }
        }


        virtual shared_ptr<T> getChild(DiagonalDirection dir) {
            // check if child exist
            if (m_children.find(dir) != m_children.end())
                return m_children[dir];
            else
                return nullptr;
        }

        shared_ptr<T> getParent() const { return m_parent; };

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        int getDepth() {
            if (isRoot())
                return 0;
            else
                return m_parent->getDepth() + 1;
        }

#pragma clang diagnostic pop

        virtual bool hasChildren() {
            return !m_children.empty();
        }

        [[maybe_unused]] std::string printPath(std::string stream = "") {
            if (isRoot()) {
                return "root" + stream;
            } else {
                if (this->shared_from_this() == getChildOfParent(nw)) {
                    return getParent()->printPath(" -> " + ("nw" + stream));
                } else if (this->shared_from_this() == getChildOfParent(ne)) {
                    return getParent()->printPath(" -> " + ("ne" + stream));
                } else if (this->shared_from_this() == getChildOfParent(sw)) {
                    return getParent()->printPath(" -> " + ("sw" + stream));
                } else if (this->shared_from_this() == getChildOfParent(se)) {
                    return getParent()->printPath(" -> " + ("se" + stream));
                } else {
                    throw std::runtime_error("something went wrong");
                }
            }
        }

    private:
        shared_ptr<T> m_parent{nullptr};
        // make sure, that the children are only accessed with getChild, even within the class!
        map<DiagonalDirection, shared_ptr<T>> m_children;
    };
}
#endif //SIMULATION_TREE_H
