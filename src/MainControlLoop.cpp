#include "MainControlLoop.hpp"

MainControlLoop::MainControlLoop()
{
    delay(1000);
}

void MainControlLoop::execute()
{
    //start_time = millis();
    //pass in to execute

    //gps_monitor.execute();
    Serial.println("GPS MONITOR EXECUTED");
    Serial.println(sfr::gps::altitude);

    photoresistor_monitor.execute();
    Serial.println(sfr::photoresistor::covered);

    delay(500);
    //Serial.println("PHOTORESISTOR MONITOR EXECUTED");
    
    //camera_report_monitor.execute();
    //Serial.println("CAMERA REPORT MONITOR EXECUTED");
    
    //mission_manager.execute();
    //Serial.println("MISSION MANAGER EXECUTED");

    //burnwire_control_task.execute();
    //Serial.println("BURNWIRE CONTROL TASK EXECUTED");

    //camera_control_task.execute();
    //Serial.println("CAMERA CONTROL TASK EXECUTED");

    //rockblock_control_task.execute();
    delay(50);
    //Serial.println("ROCKBLOCK CONTROL EXECUTED");
}