#include "BurnwireControlTask.hpp"

BurnwireControlTask::BurnwireControlTask(){
    pinMode(constants::burnwire::first_pin, OUTPUT);
}

void BurnwireControlTask::execute(){    
    burnwire_mode_type mode = sfr::burnwire::mode;

    switch(mode){
        case burnwire_mode_type::standby:
            { 
                if(sfr::burnwire::fire){
                    sfr::burnwire::start_time = millis();
                    dispatch_burn();
                    sfr::burnwire::mode = burnwire_mode_type::burn;
                }
                else{
                    digitalWrite(constants::burnwire::first_pin, LOW);
                }
                break;
            }
        case burnwire_mode_type::burn:
            {
                if(millis()-sfr::burnwire::start_time >= constants::burnwire::burn_time){
                    sfr::burnwire::mode = burnwire_mode_type::delay;
                    digitalWrite(constants::burnwire::first_pin, LOW);
                    sfr::burnwire::start_time = millis();
                }
                else{
                    dispatch_burn();
                }
                break;
            }
        case burnwire_mode_type::delay:
            {
                if(millis()-sfr::burnwire::start_time >= constants::burnwire::burn_wait){
                    sfr::burnwire::mode = burnwire_mode_type::burn;
                    dispatch_burn();
                    sfr::burnwire::start_time = millis();
                }
                else{
                    digitalWrite(constants::burnwire::first_pin, LOW);
                }
                break;
            }
    }
}

void BurnwireControlTask::dispatch_burn(){
    if(sfr::burnwire::attempts >= constants::burnwire::max_attempts){
        sfr::burnwire::mode = burnwire_mode_type::standby;
        digitalWrite(constants::burnwire::first_pin, LOW);
        sfr::burnwire::attempts = 0;
        sfr::burnwire::fire = false;
    }
    else{
        digitalWrite(constants::burnwire::first_pin, HIGH);
        sfr::burnwire::attempts++;
    }
}