#include "GPSMonitor.hpp"

//Green goes with white
//Yellow goes with green

TinyGPS gps;

GPSMonitor::GPSMonitor(){
    Serial1.begin(constants::gps::baud);
}

void GPSMonitor::execute(){  
    while(Serial1.available()){
        gps.encode(Serial1.read());
    }

    sfr::gps::altitude = 3.28084 * gps.f_altitude();

    num_entries = num_entries + 1.0;
    sum = sum + sfr::gps::altitude;

    if(num_entries >= 5){
        sfr::gps::altitude_average = sum/num_entries;
        num_entries = 0;
        sum = 0;
    }

}