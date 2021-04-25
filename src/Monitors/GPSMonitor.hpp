#ifndef GPS_MONITOR_HPP_
#define GPS_MONITOR_HPP_

#include "sfr.hpp"

class GPSMonitor{
    public:
        GPSMonitor();
        void execute();
        TinyGPSPlus gps;
    private:
        int num_commas = 0;
};

#endif