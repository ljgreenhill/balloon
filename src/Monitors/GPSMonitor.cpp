#include "GPSMonitor.hpp"

//Green goes with white
//Yellow goes with green

GPSMonitor::GPSMonitor(){
    Serial1.begin(constants::gps::baud);
}

void GPSMonitor::execute(){  
    while(Serial1.available() > 0){
        gps.encode(Serial1.read());
    } 
    sfr::gps::altitude = gps.altitude.feet();
    Serial.println(gps.altitude.feet());
    Serial.println(gps.altitude.meters());
}