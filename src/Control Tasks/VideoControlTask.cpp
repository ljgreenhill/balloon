#include "VideoControlTask.hpp"

VideoControlTask::VideoControlTask(){
    pinMode(constants::video::pin, OUTPUT);
    digitalWrite(constants::video::pin, HIGH);
}

void VideoControlTask::execute(){    
    if(millis() - sfr::mission::time > constants::video::four_hours){
        Serial.println("Cameras off");
        digitalWrite(constants::video::pin, LOW);
    } else{
        Serial.println("Cameras on");
        digitalWrite(constants::video::pin, HIGH);
    }
}