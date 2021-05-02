#include "MainControlLoop.hpp"


MainControlLoop::MainControlLoop()
{    
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
    sfr::mission::mode = mission_mode_type::awaiting_uplink;
}

void MainControlLoop::execute()
{
    //Serial.println(sfr::rockblock::report);
    mission_manager.execute();
    
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();

    command_monitor.execute();
    gps_monitor.execute();
    normal_report_monitor.execute();
    photoresistore_monitor.execute();

    delay(50);
}