#include "PinControlTask.hpp"

PinControlTask::PinControlTask(){
    pinMode(constants::photoresistor::pin, INPUT);
    pinMode(constants::burnwire::pin, OUTPUT);
    pinMode(constants::rockblock::sleep_pin, OUTPUT);
    pinMode(constants::video::pin, OUTPUT);
}
        
void PinControlTask::execute(){   
    digitalWrite(constants::burnwire::pin, LOW);
    digitalWrite(constants::rockblock::sleep_pin, HIGH);
    digitalWrite(constants::video::pin, HIGH);
}