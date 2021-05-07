#include "VideoControlTask.hpp"

VideoControlTask::VideoControlTask(){}

void VideoControlTask::execute(){    
    if(sfr::video::on == true || (millis() - sfr::rockblock::last_downlink <= constants::video::six_hours)){
        digitalWrite(constants::video::pin, HIGH);
    } else{
        digitalWrite(constants::video::pin, LOW);
    }
}