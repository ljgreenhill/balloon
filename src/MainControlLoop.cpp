#include "MainControlLoop.hpp"

MainControlLoop::MainControlLoop()
{
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
    sfr::mission::mode = mission_mode_type::awaiting_uplink;
    
}

void MainControlLoop::execute()
{
    gps_monitor.execute();

    normal_report_monitor.execute();

    rockblock_control_task.execute();

    command_monitor.execute();
    
    mission_manager.execute();

    delay(100);

}