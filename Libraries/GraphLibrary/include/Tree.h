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
                m_children[nw] = make_shared<T>(this->shared_from_this(), nw);
                m_children[ne] = make_shared<T>(this->shared_from_this(), ne);
                m_children[sw] = make_shared<T>(this->shared_from_this(), sw);
                m_children[se] = make_shared<T>(this->shared_from_this(), se);
            } else
                throw std::runtime_error("failed to attach leafs, leafs already attached.");
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

        bool isRoot() const {
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
