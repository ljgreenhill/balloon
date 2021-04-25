#include "VideoControlTask.hpp"

VideoControlTask::VideoControlTask(){}

void VideoControlTask::execute(){    
    if(sfr::video::on == true){
        Serial.println("video on");
        digitalWrite(constants::video::pin, HIGH);
    } else{
        Serial.println("video off");
        digitalWrite(constants::video::pin, LOW);
    }
}