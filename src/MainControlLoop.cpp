#include "MainControlLoop.hpp"


MainControlLoop::MainControlLoop()
{    
    //delay(30000);
    //Serial.println("delay over");
    sfr::mission::time = millis();

    //MAKE SURE TO REMOVE
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
    
}

void MainControlLoop::execute()
{    
    //if(millis() - sfr::mission::time > constants::mission::one_hour){
        burnwire_control_task.execute();
    //}

    mission_manager.execute();

    command_monitor.execute();
    gps_monitor.execute();
    normal_report_monitor.execute();
    photoresistor_monitor.execute();
    
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();

    //Serial.print("GPS ALTITUDE: ");
    Serial.println(sfr::gps::altitude);

    //Serial.print("GPS AVERAGE ALTITUDE: ");
    //Serial.println(sfr::gps::altitude_average);

    //Serial.print("PHOTORESISTOR COVERED?: ");
    //Serial.println(sfr::photoresistor::covered);

    //Serial.println(sfr::gps::altitude_average);
    //Serial.println(sfr::gps::altitude);
       
    //delay(100);

}