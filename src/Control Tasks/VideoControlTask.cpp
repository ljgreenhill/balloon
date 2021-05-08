#include "VideoControlTask.hpp"

VideoControlTask::VideoControlTask(){
    pinMode(constants::video::pin, OUTPUT);
    digitalWrite(constants::video::pin, HIGH);
}

void VideoControlTask::execute(){    
    if(sfr::video::on == true || (millis() - sfr::rockblock::last_downlink <= constants::video::four_hours)){
        (constants::video::pin, HIGH);
    } else{
        Serial.println("Turn off cameras");
        digitalWrite(constants::video::pin, LOW);
    }
}