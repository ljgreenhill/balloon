#include "MainControlLoop.hpp"
#include "Control Tasks/PinControlTask.hpp"

MainControlLoop mcl;
PinControlTask pin_control_task;

#ifndef UNIT_TEST
void setup(){
    pin_control_task.execute();  
    delay(2000);
}

void loop(){
    mcl.execute();
}
#endif



