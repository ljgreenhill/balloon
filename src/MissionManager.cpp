#include "MissionManager.hpp"

MissionManager::MissionManager(unsigned int offset): TimedControlTask<void>(offset){
    transition_to_standby();
}

void MissionManager::execute(){
    mission_mode_type mode = sfr::mission::mode;

    switch(mode){
        case mission_mode_type::standby:
            dispatch_standby();
            break;
        case mission_mode_type::deployment:
            dispatch_deployment();
            break;
    }
}

void MissionManager::dispatch_standby(){}

void MissionManager::dispatch_deployment(){
    if(!sfr::button::pressed && !sfr::photoresistor::covered){
        sfr::camera::take_photo = true;
        BurnwireControlTask::transition_to_standby();
        transition_to_standby();
    }
}

void MissionManager::transition_to_standby(){
    sfr::mission::mode = mission_mode_type::standby;
    sfr::rockblock::downlink_period = constants::rockblock::ten_minutes;
}

void MissionManager::transition_to_deployment(){
    sfr::camera::turn_off = true;
    sfr::mission::mode = mission_mode_type::deployment;
    sfr::rockblock::downlink_period = constants::rockblock::ten_minutes;
}

