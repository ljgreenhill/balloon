#include "MainControlLoop.hpp"
#include "sfr.hpp"

MainControlLoop mcl;

void setup(){
    delay(2000); 
}

void loop(){
    mcl.execute();
}


