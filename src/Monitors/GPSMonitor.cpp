#include "GPSMonitor.hpp"

GPSMonitor::GPSMonitor(unsigned int offset): TimedControlTask<void>(offset){
    Serial3.begin(constants::gps::baud);
    while(!ready){
        Serial3.write((uint8_t *)&constants::gps::CheckNav, sizeof(constants::gps::CheckNav));

        Serial3.flush();
        delay(200);

        Serial3.write( (uint8_t *)&constants::gps::SetCfgNav5, sizeof(constants::gps::SetCfgNav5));

        Serial3.flush();
        delay(200);

        Serial3.write((uint8_t *)&constants::gps::CheckNav, sizeof(constants::gps::CheckNav));

        Serial3.flush();
        delay(200);

        while(Serial3.available()){
            if(Serial3.read() == 255 && Serial3.read() == 255 && Serial3.read() == 6 && Serial3.read() == 3){
                ready = true;
            }
        }
    } 
}

void GPSMonitor::execute(){ 
    while(Serial3.available()){
        gps.encode(Serial3.read());
    }

    float reading = gps.f_altitude();
    if(reading != 1000000){
        sfr::gps::altitude_buffer.push_front(reading);
        if (sfr::gps::altitude_buffer.size() > constants::sensor::collect){
            sfr::gps::altitude_buffer.pop_back();
        }
        float altitude_sum = std::accumulate(sfr::gps::altitude_buffer.begin(), sfr::gps::altitude_buffer.end(), 0.0);
        sfr::gps::altitude_average = altitude_sum / sfr::gps::altitude_buffer.size();
    }
}