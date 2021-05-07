#include "MainControlLoop.hpp"


MainControlLoop::MainControlLoop()
{    
    //delay(30000);
    //Serial.println("delay over");
    sfr::mission::time = millis();
}

void MainControlLoop::execute()
{    
    if(millis() - sfr::mission::time > constants::mission::one_hour){
        burnwire_control_task.execute();
    }

    mission_manager.execute();

    gps_monitor.execute();
    normal_report_monitor.execute();
    command_monitor.execute();
    photoresistor_monitor.execute();
    
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
}