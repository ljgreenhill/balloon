#include "MainControlLoop.hpp"


MainControlLoop::MainControlLoop()
{    
    //delay(30000);
    //Serial.println("delay over");
    sfr::mission::time = millis();

    //MAKE SURE TO REMOVE
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
    //sfr::burnwire::fire = true;    
}

void MainControlLoop::execute()
{    
    //if(millis() - sfr::mission::time > constants::mission::one_hour){
    if(millis() - sfr::mission::time > 120000) {
        burnwire_control_task.execute();
    }

    mission_manager.execute();

    command_monitor.execute();
    gps_monitor.execute();
    normal_report_monitor.execute();
    photoresistor_monitor.execute();
    
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();

}