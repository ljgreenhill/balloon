#include "MissionManager.hpp"

MissionManager::MissionManager(unsigned int offset): TimedControlTask<void>(offset){
    transition_to_standby();
    sfr::timer::start_time = millis();
}

void MissionManager::execute(){
    mission_mode_type mode = sfr::mission::mode;

    switch(mode){
        case mission_mode_type::standby:
            dispatch_standby();
            break;
        case mission_mode_type::high_altitude:
            dispatch_high_altitude();
            break;
        case mission_mode_type::deployment:
            dispatch_deployment();
            break;
    }
}

void MissionManager::dispatch_standby(){
    if((millis() - sfr::timer::start_time) >= constants::timer::fail_safe_deploy || sfr::gps::altitude_average  > constants::gps::mand_deploy){
        transition_to_deployment();
    }
    if(sfr::gps::altitude_average  > constants::gps::high_altitude){
        transition_to_high_altitude();
    }
}

void MissionManager::dispatch_high_altitude(){
    if((millis() - sfr::timer::start_time) >= constants::timer::fail_safe_deploy || sfr::gps::altitude_average  > constants::gps::mand_deploy){
        transition_to_deployment();
    }
}

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
    sfr::rockblock::camera_downlink_period = constants::rockblock::ten_minutes;
}

void MissionManager::transition_to_deployment(){
    sfr::camera::turn_off = true;
    sfr::mission::mode = mission_mode_type::deployment;
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
    sfr::rockblock::camera_downlink_period = constants::rockblock::one_minute;
}

void MissionManager::transition_to_high_altitude(){
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
    sfr::rockblock::camera_downlink_period = constants::rockblock::one_minute;
}