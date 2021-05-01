#include "NormalReportMonitor.hpp"

NormalReportMonitor::NormalReportMonitor(){}

void NormalReportMonitor::execute(){
    sfr::rockblock::report = "ALTITUDE: " + (String)sfr::gps::altitude + ", PHOTORESISTOR: " + (String)sfr::photoresistor::covered;
    
}
