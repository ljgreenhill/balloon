#include "NormalReportMonitor.hpp"

NormalReportMonitor::NormalReportMonitor(unsigned int offset): TimedControlTask<void>(offset){}

void NormalReportMonitor::execute(){
    uint8_t downlink_period = map(sfr::rockblock::downlink_period, constants::rockblock::min_downlink_period, constants::rockblock::max_downlink_period, 0, 255);

    sfr::rockblock::report[0] = 21;
    sfr::rockblock::report[1] = sfr::photoresistor::covered;
    sfr::rockblock::report[2] = sfr::button::pressed;
    sfr::rockblock::report[3] = (uint8_t) sfr::mission::mode;
    sfr::rockblock::report[4] = sfr::burnwire::burn_time;
    sfr::rockblock::report[5] = (uint8_t) sfr::burnwire::mode;
    sfr::rockblock::report[6] = sfr::burnwire::attempts;
    sfr::rockblock::report[7] = downlink_period;
    sfr::rockblock::report[8] = sfr::rockblock::waiting_message;
    sfr::rockblock::report[9] = sfr::rockblock::waiting_command;
    sfr::rockblock::report[10] = sfr::camera::take_photo;
    sfr::rockblock::report[11] = sfr::camera::powered;
}