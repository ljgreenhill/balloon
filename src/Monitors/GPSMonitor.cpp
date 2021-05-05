#include "GPSMonitor.hpp"

// TX -> RX
// RX -> TX

TinyGPS gps;
boolean ready = false;

GPSMonitor::GPSMonitor(){
    while(!ready){
        Serial1.begin(constants::gps::baud);
        delay(200);

        Serial1.write((uint8_t *)&constants::gps::CheckNav, sizeof(constants::gps::CheckNav));

        Serial1.flush();
        delay(200);

        Serial1.write( (uint8_t *)&constants::gps::SetCfgNav5, sizeof(constants::gps::SetCfgNav5));

        Serial1.flush();
        delay(200);

        Serial1.write((uint8_t *)&constants::gps::CheckNav, sizeof(constants::gps::CheckNav));

        Serial1.flush();
        delay(200);

        while(Serial1.available()){
            if(Serial1.read() == 255 && Serial1.read() == 255 && Serial1.read() == 6 && Serial1.read() == 3){
                ready = true;
            }
        }

    }
    
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