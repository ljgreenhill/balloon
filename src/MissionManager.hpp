#ifndef MISSION_MANAGER_HPP_
#define MISSION_MANAGER_HPP_

#include "sfr.hpp"

class MissionManager{
    public:
        MissionManager();
        void execute();
        void dispatch_standby();
        void dispatch_awaiting_uplink();
        void dispatch_deployment();
        void transition_to_standby();
        void transition_to_awaiting_uplink();
        void transition_to_deployment();
};

#endif