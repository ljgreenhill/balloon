#include "PinControlTask.hpp"

PinControlTask::PinControlTask(){

    //serial for rockblock?
    //i2c for imu?
    //serial for camera?

    pinMode(constants::camera::power_on_pin, OUTPUT);
    pinMode(constants::camera::rx, OUTPUT);
    pinMode(constants::camera::tx, OUTPUT);
    pinMode(constants::button::button_pin, INPUT);
    pinMode(constants::photoresistor::pin, INPUT);
    pinMode(constants::burnwire::pin, OUTPUT);
    pinMode(constants::rockblock::sleep_pin, OUTPUT);
}
        
void PinControlTask::execute(){   
    digitalWrite(constants::camera::power_on_pin, LOW);
    digitalWrite(constants::burnwire::pin, LOW);
    digitalWrite(constants::rockblock::sleep_pin, HIGH);
}