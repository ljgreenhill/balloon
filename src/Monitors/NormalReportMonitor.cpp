#include "NormalReportMonitor.hpp"

NormalReportMonitor::NormalReportMonitor(){}

void NormalReportMonitor::execute(){
    uint8_t altitude = map(sfr::gps::altitude, constants::gps::max_altitude, constants::gps::min_altitude, 0, 255);

    uint8_t report[70] = {altitude};
    
}
