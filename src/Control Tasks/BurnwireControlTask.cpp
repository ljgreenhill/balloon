#include "BurnwireControlTask.hpp"

BurnwireControlTask::BurnwireControlTask(){
    pinMode(constants::burnwire::pin, OUTPUT);
}

void BurnwireControlTask::execute(){    
    burnwire_mode_type mode = sfr::burnwire::mode;

    switch(mode){
        case burnwire_mode_type::standby:
            { 
                if(sfr::burnwire::fire == true){
                    sfr::burnwire::start_time = millis();
                    sfr::burnwire::mode = burnwire_mode_type::burn;
                    digitalWrite(constants::burnwire::pin, HIGH);
                }
                else{
                    digitalWrite(constants::burnwire::pin, LOW);
                }
                break;
            }
        case burnwire_mode_type::burn:
            {
                Serial.println("burn");
                if(millis()-sfr::burnwire::start_time >= constants::burnwire::burn_time){
                    sfr::burnwire::mode = burnwire_mode_type::delay;
                    digitalWrite(constants::burnwire::pin, LOW);
                    sfr::burnwire::start_time = millis();
                }
                else{
                    digitalWrite(constants::burnwire::pin, HIGH);
                }
                break;
            }
        case burnwire_mode_type::delay:
            {
                Serial.println("delay");
                Serial.println(sfr::burnwire::attempts);
                if(millis()-sfr::burnwire::start_time >= constants::burnwire::burn_wait){
                    sfr::burnwire::mode = burnwire_mode_type::burn;
                    Serial.println(sfr::burnwire::attempts);
                    Serial.println(constants::burnwire::max_attempts);
                    if(sfr::burnwire::attempts >= constants::burnwire::max_attempts){
                        sfr::burnwire::fire = false;
                        sfr::burnwire::attempts = 0;
                        sfr::burnwire::mode = burnwire_mode_type::standby;
                    }
                    sfr::burnwire::attempts++;
                    digitalWrite(constants::burnwire::pin, HIGH);
                    sfr::burnwire::start_time = millis();
                }
                else{
                    digitalWrite(constants::burnwire::pin, LOW);
                }
                break;
            }
    }
}
