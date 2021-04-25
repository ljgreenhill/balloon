#include "MainControlLoop.hpp"

MainControlLoop::MainControlLoop()
{
    delay(1000);    
}

void MainControlLoop::execute()
{
    //start_time = millis();
    //pass in to execute

    /*if(!sfr::photoresistor::covered){
        sfr::burnwire::fire = true;
    }else{
        sfr::burnwire::fire = false;

    }*/

    digitalWrite(26, LOW);


    
    //gps_monitor.execute();
    //Serial.println("GPS MONITOR EXECUTED");
    //Serial.println(sfr::gps::altitude);

    //photoresistor_monitor.execute();
    //Serial.println(sfr::photoresistor::covered);

    //rockblock_control_task.execute();

    

    //burnwire_control_task.execute();

    //delay(500);
    //digitalWrite(35, HIGH);

    //delay(5000);
    //digitalWrite(35, HIGH);
    //Serial.println("PHOTORESISTOR MONITOR HIGH");
    
    //camera_report_monitor.execute();
    //Serial.println("CAMERA REPORT MONITOR EXECUTED");
    
    //mission_manager.execute();
    //Serial.println("MISSION MANAGER EXECUTED");

    //sfr::burnwire::fire = true;

    //burnwire_control_task.execute();
    //Serial.println("BURNWIRE CONTROL TASK EXECUTED");

    //camera_control_task.execute();
    //Serial.println("CAMERA CONTROL TASK EXECUTED");

    //rockblock_control_task.execute();
    //delay(50);
    //Serial.println("ROCKBLOCK CONTROL EXECUTED");
}