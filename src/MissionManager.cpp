#include "MissionManager.hpp"

MissionManager::MissionManager(){}

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

void MissionManager::dispatch_awaiting_uplink(){
    if(sfr::gps::altitude > constants::gps::awaiting_uplink){
        sfr::mission::mode = mission_mode_type::awaiting_uplink;
        transition_to_awaiting_uplink();
    }
}

void MissionManager::dispatch_awaiting_uplink(){
    if(sfr::gps::altitude > constants::gps::mand_deploy){
        sfr::mission::mode = mission_mode_type::deployment;
        transition_to_deployment();
    }
}

void MissionManager::dispatch_deployment(){
    if(!sfr::photoresistor::covered){
        sfr::mission::mode = mission_mode_type::standby;
        sfr::burnwire::fire = false;
        sfr::camera::take_photo = true;
        sfr::mission::mode = mission_mode_type::standby;
        transition_to_standby();
    }
}

void MissionManager::transition_to_standby(){
    sfr::rockblock::downlink_period = constants::rockblock::ten_minutes;
}

void MissionManager::transition_to_awaiting_uplink(){
    sfr::rockblock::downlink_period = constants::rockblock::one_minute;
}

void MissionManager::transition_to_deployment(){}
