#ifndef COMMAND_MONITOR_HPP_
#define COMMAND_MONITOR_HPP_

#include "sfr.hpp"

class CommandMonitor{
    public:
        CommandMonitor();
        void execute();
        void dispatch_change_burnwire();
        void dispatch_change_camera();
        void dispatch_change_rockblock();
        void dispatch_change_mission();
        void dispatch_change_video();
};

#endif