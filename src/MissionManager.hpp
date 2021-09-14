#ifndef MISSION_MANAGER_HPP_
#define MISSION_MANAGER_HPP_

#include "sfr.hpp"
#include "constants.hpp"
#include "Control Tasks/TimedControlTask.hpp"

class MissionManager : public TimedControlTask<void>{
    public:
        MissionManager(unsigned int offset);
        void execute();
        void dispatch_standby();
        void dispatch_deployment();

        static void transition_to_standby();
        static void transition_to_deployment();
};

#endif