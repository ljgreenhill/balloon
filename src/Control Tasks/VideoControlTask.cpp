#include "VideoControlTask.hpp"

VideoControlTask::VideoControlTask(unsigned int offset): TimedControlTask<void>(offset){
    pinMode(constants::video::pin, OUTPUT);
    digitalWrite(constants::video::pin, HIGH);
}

void VideoControlTask::execute(){    
    if(millis() - sfr::timer::start_time > constants::video::four_hours){
        digitalWrite(constants::video::pin, LOW);
    } else{
        digitalWrite(constants::video::pin, HIGH);
    }
}