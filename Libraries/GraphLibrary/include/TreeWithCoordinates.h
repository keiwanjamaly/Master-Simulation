//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_TREEWITHCOMPARISON_H
#define SIMULATION_TREEWITHCOMPARISON_H

#include "Tree.h"

namespace gl {

    class TreeWithCoordinates : public Tree<TreeWithCoordinates> {
    public:
        TreeWithCoordinates() = delete;

        TreeWithCoordinates(double x, double y, double width, double height) : Tree(), m_x{x}, m_y{y}, m_width{width},
                                                                               m_height{height} {}

        TreeWithCoordinates(DiagonalDirection dir, shared_ptr<TreeWithCoordinates> parent) : Tree(parent) {

            m_x = getParent()->m_x;
            m_y = getParent()->m_y;
            m_width = getParent()->m_width;
            m_height = getParent()->m_height;

            switch (dir) {
                case nw:
                    m_x -= getParent()->getWidth() / 2;
                    m_y += getParent()->getHeight() / 2;
                    break;
                case ne:
                    m_x += getParent()->getWidth() / 2;
                    m_y += getParent()->getHeight() / 2;
                    break;
                case sw:
                    m_x -= getParent()->getWidth() / 2;
                    m_y -= getParent()->getHeight() / 2;
                    break;
                case se:
                    m_x += getParent()->getWidth() / 2;
                    m_y -= getParent()->getHeight() / 2;
                    break;
            }

            m_width /= 2;
            m_height /= 2;
        }

        double getX() const { return m_x; }

        double getY() const { return m_y; }

        double getWidth() const { return m_width; }

        double getHeight() const { return m_height; }

    private:
        double m_x, m_y;
        double m_width, m_height;
    };

}

#endif //SIMULATION_TREEWITHCOMPARISON_H
