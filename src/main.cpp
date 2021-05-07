#include "MainControlLoop.hpp"
#include "sfr.hpp"

MainControlLoop mcl;
//TinyGPS gps;

void setup(){
    //TODO: Add long delay
    //Serial1.begin(9600);
    delay(2000); 
}

void loop(){
   mcl.execute();
    /*while(Serial1.available()){
        gps.encode(Serial1.read());
    }
    Serial.println(gps.f_altitude());*/
}












