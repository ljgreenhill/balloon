#ifndef GPS_MONITOR_HPP_
#define GPS_MONITOR_HPP_

#include "sfr.hpp"

class GPSMonitor{
    public:
        GPSMonitor();
        void execute();
    private:
        float num_entries = 0;
        float sum = 0;
};

#endif