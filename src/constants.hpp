#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

namespace constants
{
    namespace mission
    {
        constexpr int one_hour = 3600000;
    }
    namespace photoresistor
    {
        constexpr int pin = 22;
        constexpr int light_val = 300;
    }
    namespace burnwire
    {
        constexpr int pin = 35;
        constexpr int burn_time = 200;
        constexpr int burn_wait = 2000;
        constexpr int max_attempts = 20;
    }
    namespace rockblock
    {
        constexpr int baud = 19200;
        constexpr unsigned long ten_minutes = 600000;
        constexpr unsigned long one_minute = 60000;
        constexpr int buffer_size = 63;
        constexpr int packet_size = 70;
        constexpr int max_iter = 2000;
        constexpr int num_commas = 5;
    }
    namespace gps
    {
        constexpr float max_altitude = 150000;
        constexpr float min_altitude = 0.0;
        constexpr int baud = 9600;
        constexpr int mand_deploy = 89062;
        constexpr int awaiting_uplink = 83190;
        constexpr uint8_t SetCfgNav5[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0x01, 0x01, // Note two 0x01's.  Don't know if the bitmask is little-endian or not.
                                          0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, // Set dyn mode to 6 - airborne <1g.  That's plenty for balloons.
                                          0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00,
                                          0x64, 0x00, 0x2C, 0x01, 0x00, 0x3C, 0x00, 0x00, // Note, Flextrack has 0x00 where the T-Beam defaults to 0x3c.
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x56, 0x76};
        constexpr uint8_t CheckNav[] = {0xB5, 0x62, 0x06, 0x24, 0x00, 0x00, 0x2A, 0x84};
    }
    namespace video
    {
        constexpr int pin = 26;
        constexpr int six_hours = 21600000;
    }  
};

#endif
