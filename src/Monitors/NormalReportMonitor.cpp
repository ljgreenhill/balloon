#include "NormalReportMonitor.hpp"

NormalReportMonitor::NormalReportMonitor(){}

void NormalReportMonitor::execute(){

    String mission_mode;

    if(sfr::mission::mode == mission_mode_type::standby){
        mission_mode = "standby";
    }
    else if(sfr::mission::mode == mission_mode_type::awaiting_uplink){
        mission_mode = "awaiting uplink";
    }
    else{
        mission_mode = "deployment";
    }

    sfr::rockblock::report = (String)sfr::gps::altitude + 
                             ", " + mission_mode +
                             ", r" + (String)sfr::photoresistor::covered +
                             ", f" + (String)sfr::burnwire::fire +
                              ", p" + (String)sfr::camera::take_photo +
                              ", d" + (String)sfr::rockblock::downlink_period +
                              ", v" + (String)sfr::video::on;
}
