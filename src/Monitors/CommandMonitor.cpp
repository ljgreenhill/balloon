#include "CommandMonitor.hpp"

CommandMonitor::CommandMonitor(){}

void CommandMonitor::execute(){
    if(sfr::rockblock::waiting_command){
        switch(sfr::rockblock::opcode_p){
            case 1:
                dispatch_change_burnwire();
                break;
            case 2:
                dispatch_change_camera();
                break;
            case 3:
                dispatch_change_rockblock();
                break;
            case 4:
                dispatch_change_mission();
                break;
            case 5:
                dispatch_change_video();
                break;
        }
        sfr::rockblock::waiting_command = false;
    }
}

void CommandMonitor::dispatch_change_burnwire(){
    sfr::burnwire::fire = sfr::rockblock::arg_1_p;
}

void CommandMonitor::dispatch_change_camera(){
    sfr::camera::take_photo = sfr::rockblock::arg_1_p;
}

void CommandMonitor::dispatch_change_rockblock(){
    switch(sfr::rockblock::arg_1_p){
        case 0:
            sfr::rockblock::downlink_period = constants::rockblock::one_minute * sfr::rockblock::arg_2_p;
            break;
        case 1:
            sfr::rockblock::downlink_period = constants::rockblock::one_minute / sfr::rockblock::arg_2_p;
            break;
    }
}

void CommandMonitor::dispatch_change_mission(){
    switch(sfr::rockblock::arg_1_p){
        case 0:
            sfr::mission::mode = mission_mode_type::standby;
            sfr::rockblock::downlink_period = constants::rockblock::ten_minutes;
            //MissionManager::transition_to_standby();
            break;
        case 1:
            sfr::mission::mode = mission_mode_type::awaiting_uplink;
            sfr::rockblock::downlink_period = constants::rockblock::one_minute;
            //MissionManager::transition_to_awaiting_uplink();
            break;
        case 2:
            sfr::mission::mode = mission_mode_type::standby;
            //MissionManager::transition_to_standby();
            break;
    }
}

void CommandMonitor::dispatch_change_video(){
    sfr::video::on = sfr::rockblock::arg_1_p;
}