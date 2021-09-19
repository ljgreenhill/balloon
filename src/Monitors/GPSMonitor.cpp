#include "GPSMonitor.hpp"

TinyGPS gps;

GPSMonitor::GPSMonitor(unsigned int offset) : TimedControlTask<void>(offset)
{
    Serial3.begin(constants::gps::baud);
    /*while(!ready){
        Serial3.write((uint8_t *)&constants::gps::CheckNav, sizeof(constants::gps::CheckNav));

        Serial3.flush();
        delay(200);

        Serial3.write( (uint8_t *)&constants::gps::SetCfgNav5, sizeof(constants::gps::SetCfgNav5));

        Serial3.flush();
        delay(200);

        Serial3.write((uint8_t *)&constants::gps::CheckNav, sizeof(constants::gps::CheckNav));

        Serial3.flush();
        delay(1000);

        while(Serial3.available()){
            if(Serial3.read() == 255 && Serial3.read() == 255 && Serial3.read() == 6 && Serial3.read() == 3){
                ready = true;
            }
        }
    } */
}

void GPSMonitor::execute()
{
    Serial.println(sfr::gps::altitude);
    Serial.println(sfr::gps::altitude_average);
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
        while (Serial3.available())
        {
            char c = Serial3.read();
            if (gps.encode(c))
                sfr::gps::new_data = true;
        }
    }
    if (sfr::gps::new_data)
    {
        float flat, flon;
        gps.f_get_position(&flat, &flon);
        sfr::gps::latitude = flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
        sfr::gps::longitude = flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
        sfr::gps::altitude = gps.f_altitude() == TinyGPS::GPS_INVALID_ALTITUDE ? 0 : gps.f_altitude();

        MissionManager::add_sensor_value(sfr::gps::latitude_buffer, sfr::gps::latitude, sfr::gps::latitude_average);
        MissionManager::add_sensor_value(sfr::gps::longitude_buffer, sfr::gps::longitude, sfr::gps::longitude_average);
        MissionManager::add_sensor_value(sfr::gps::altitude_buffer, sfr::gps::altitude, sfr::gps::altitude_average);
    }
}
