#include "MainControlLoop.hpp"
#include "sfr.hpp"

MainControlLoop mcl;

void setup(){
    //TODO: Add long delay
    delay(2000); 
}

void loop(){
    mcl.execute();
}




