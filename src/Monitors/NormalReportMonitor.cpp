#include "NormalReportMonitor.hpp"

NormalReportMonitor::NormalReportMonitor(unsigned int offset) : TimedControlTask<void>(offset) {}

void NormalReportMonitor::execute()
{
    uint8_t downlink_period = map(sfr::rockblock::downlink_period, constants::rockblock::min_downlink_period, constants::rockblock::max_downlink_period, 0, 255);
    uint8_t altitude = map(sfr::gps::altitude_average, constants::gps::min_altitude_average, constants::gps::max_altitude_average, 0, 255);
    uint8_t longitude = map(sfr::gps::longitude_average, constants::gps::min_longitude_average, constants::gps::max_longitude_average, 0, 255);
    uint8_t latitude = map(sfr::gps::latitude_average, constants::gps::min_latitude_average, constants::gps::max_longitude_average, 0, 255);

    sfr::rockblock::report[0] = 21;
    sfr::rockblock::report[1] = altitude;
    sfr::rockblock::report[2] = longitude;
    sfr::rockblock::report[3] = latitude;
    sfr::rockblock::report[4] = sfr::photoresistor::covered;
    sfr::rockblock::report[5] = (uint8_t)sfr::mission::mode;
    sfr::rockblock::report[6] = (uint8_t)sfr::burnwire::mode;
    sfr::rockblock::report[7] = sfr::burnwire::attempts;
    sfr::rockblock::report[8] = downlink_period;
}