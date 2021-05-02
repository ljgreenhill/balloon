#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

namespace constants
{
    namespace photoresistor
    {
        constexpr int pin = 22;
        constexpr int light_val = 800;
    }
    namespace burnwire
    {
        constexpr int pin = 35;
        constexpr int burn_time = 500;
        constexpr int burn_wait = 2000;
        constexpr int max_attempts = 120;
    }
    namespace rockblock
    {
        constexpr int baud = 19200;
        constexpr unsigned long ten_minutes = 600000;
        constexpr unsigned long one_minute = 60000;
        constexpr int buffer_size = 63;
        constexpr int packet_size = 70;
        constexpr int max_iter = 500;
        constexpr int num_commas = 5;
    }
    namespace gps
    {
        constexpr float max_altitude = 150000;
        constexpr float min_altitude = 0.0;
        constexpr int baud = 9600;
        constexpr int mand_deploy = 90000;
        constexpr int awaiting_uplink = 70000;
    }
    namespace video
    {
        constexpr int pin = 26;
        constexpr int four_hours = 14400000;
    }
    
    
    
};

#endif
