//
// Created by Keiwan Jamaly on 09.12.22.
//

#ifndef SIMULATION_PHASEDIAGRAM_H
#define SIMULATION_PHASEDIAGRAM_H

#include <iostream>
#include <iomanip>

#include "BS_thread_pool.hpp"
#include "Leaf3.h"
#include "System.h"
#include "Flow.h"

template<class T>
class PhaseDiagram {
public:
    PhaseDiagram() = delete;

    PhaseDiagram(double mu_left, double T_bottom, double mu_right, double T_top) : m_mu_left{mu_left},
                                                                                   m_mu_right{mu_right},
                                                                                   m_T_bottom{T_bottom},
                                                                                   m_T_top{T_top} {

    }

    void compute() {
        information_message();
    }

private:
    void information_message() {
        using std::cout;
        cout << std::setprecision(1) << std::fixed
             << "Phase diagram is calculated with " << m_pool.get_thread_count() << " cores." << "\n"
             << "The corners of the phase diagram are:" << "\n"
             << "(" << m_mu_left << "," << m_T_top << ")"
             << " |-----------------------| "
             << "(" << m_mu_right << "," << m_T_top << ")" << "\n"
             << "    |                                   | \n"
             << "    |         x               x         | \n"
             << "    |      \\                     /      | \n"
             << "    |       \\-------------------/       | \n"
             << "    |                                   | \n"
             << "    |                                   | \n"
             << "(" << m_mu_left << "," << m_T_bottom << ")"
             << " |-----------------------| "
             << "(" << m_mu_right << "," << m_T_bottom << ")" << std::endl;
    }

    BS::thread_pool m_pool;
//    dp::Leaf<phy::System, phy::Flow> root;
    double m_mu_left, m_mu_right, m_T_bottom, m_T_top;
};


#endif //SIMULATION_PHASEDIAGRAM_H
