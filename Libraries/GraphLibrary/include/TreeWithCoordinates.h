//
// Created by Keiwan Jamaly on 12.12.22.
//

#ifndef SIMULATION_TREEWITHCOMPARISON_H
#define SIMULATION_TREEWITHCOMPARISON_H

#include "TreeWithNeighbours.h"

namespace gl {

    template<class T>
    class TreeWithCoordinates : public TreeWithNeighbours<T> {
    public:
        TreeWithCoordinates() = delete;

        TreeWithCoordinates(double x, double y, double width, double height)
                : TreeWithNeighbours<T>(), m_x{x}, m_y{y}, m_width{width},
                  m_height{height} {}

        TreeWithCoordinates(shared_ptr<T> parent, DiagonalDirection dir) : TreeWithNeighbours<T>(parent, dir) {
            m_x = this->getParent()->getX();
            m_y = this->getParent()->getY();
            m_width = this->getParent()->getWidth() / 2;
            m_height = this->getParent()->getHeight() / 2;

            switch (dir) {
                case nw:
                    m_x -= getWidth();
                    m_y += getHeight();
                    break;
                case ne:
                    m_x += getWidth();
                    m_y += getHeight();
                    break;
                case sw:
                    m_x -= getWidth();
                    m_y -= getHeight();
                    break;
                case se:
                    m_x += getWidth();
                    m_y -= getHeight();
                    break;
            }
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
