#include "VideoControlTask.hpp"

VideoControlTask::VideoControlTask(unsigned int offset): TimedControlTask<void>(offset){
    pinMode(constants::video::pin, OUTPUT);
    digitalWrite(constants::video::pin, HIGH);
}

void VideoControlTask::execute(){    
    if(millis() - sfr::timer::start_time > constants::video::four_hours){
        Serial.println("Cameras off");
        digitalWrite(constants::video::pin, LOW);
    } else{
        Serial.println("Cameras on");
        digitalWrite(constants::video::pin, HIGH);
    }
}