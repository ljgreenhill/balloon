#ifndef GPS_MONITOR_HPP_
#define GPS_MONITOR_HPP_

#include "sfr.hpp"

class GPSMonitor : public TimedControlTask<void>{
    public:
        GPSMonitor(unsigned int offset);
        void execute();
    private:
        float num_entries = 0;
        float sum = 0;
        boolean ready = false;
        TinyGPS gps;
};

#endif