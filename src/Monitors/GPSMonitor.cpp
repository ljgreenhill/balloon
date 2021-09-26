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

        sfr::gps::latitude_buffer.push_front(sfr::gps::latitude);
        if (sfr::gps::latitude_buffer.size() > constants::sensor::collect)
        {
            sfr::gps::latitude_buffer.pop_back();
        }
        float latitude_sum = std::accumulate(sfr::gps::latitude_buffer.begin(), sfr::gps::latitude_buffer.end(), 0.0);
        sfr::gps::latitude_average = latitude_sum / sfr::gps::latitude_buffer.size();

        sfr::gps::longitude_buffer.push_front(sfr::gps::longitude);
        if (sfr::gps::longitude_buffer.size() > constants::sensor::collect)
        {
            sfr::gps::longitude_buffer.pop_back();
        }
        float longitude_sum = std::accumulate(sfr::gps::longitude_buffer.begin(), sfr::gps::longitude_buffer.end(), 0.0);
        sfr::gps::longitude_average = longitude_sum / sfr::gps::longitude_buffer.size();

        sfr::gps::altitude_buffer.push_front(sfr::gps::altitude);
        if (sfr::gps::altitude_buffer.size() > constants::sensor::collect)
        {
            sfr::gps::altitude_buffer.pop_back();
        }
        float altitude_sum = std::accumulate(sfr::gps::altitude_buffer.begin(), sfr::gps::altitude_buffer.end(), 0.0);
        sfr::gps::altitude_average = altitude_sum / sfr::gps::altitude_buffer.size();
    }
}
