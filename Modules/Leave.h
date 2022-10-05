//
// Created by Keiwan Jamaly on 05.10.22.
//

#ifndef SIMULATION_LEAVE_H
#define SIMULATION_LEAVE_H

namespace dp {
    template <class T> class Leave {
    public:
        Leave(T const&, Leave const&);
        Leave(T const&);
    };

} // dp

#endif //SIMULATION_LEAVE_H
