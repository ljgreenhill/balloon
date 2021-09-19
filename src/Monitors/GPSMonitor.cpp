#include "GPSMonitor.hpp"

TinyGPS gps;

GPSMonitor::GPSMonitor(unsigned int offset) : TimedControlTask<void>(offset)
{
    Serial3.begin(constants::gps::baud);
    delay(1000);

    Serial3.write((unsigned char *)&constants::gps::SetCfgNav5, sizeof(constants::gps::SetCfgNav5));
    delay(1000);
}

void GPSMonitor::execute()
{
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
        sfr::gps::latitude = flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat;
        sfr::gps::longitude = flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon;
        sfr::gps::altitude = gps.f_altitude() == TinyGPS::GPS_INVALID_ALTITUDE ? 0 : gps.f_altitude();

        MissionManager::add_sensor_value(sfr::gps::latitude_buffer, sfr::gps::latitude, sfr::gps::latitude_average);
        MissionManager::add_sensor_value(sfr::gps::longitude_buffer, sfr::gps::longitude, sfr::gps::longitude_average);
        MissionManager::add_sensor_value(sfr::gps::altitude_buffer, sfr::gps::altitude, sfr::gps::altitude_average);
    }
}
