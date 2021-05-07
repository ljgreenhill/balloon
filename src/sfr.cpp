#include "sfr.hpp"

namespace sfr
{
    namespace photoresistor
    {
        bool covered = true;
    }
    namespace mission
    {
        mission_mode_type mode = mission_mode_type::standby;
        int time = 0;
    }
    namespace burnwire
    {
        bool fire = false;
        burnwire_mode_type mode = burnwire_mode_type::standby;
        int attempts = 0;
        int start_time = 0;
    }
    namespace camera
    {
        bool take_photo = false;
        uint8_t buffer[255] = {0};
    }
    namespace rockblock
    {
        unsigned long last_downlink = 0;
        unsigned long downlink_period = constants::rockblock::ten_minutes;
        rockblock_mode_type mode = rockblock_mode_type::send_at;
        bool waiting_message = false;
        int num_iter = 0;
        bool waiting_command = false;

        char buffer[constants::rockblock::buffer_size] = {0};

        String report = "";
        int commas[constants::rockblock::num_commas] = {0};

        int opcode_p = 0;
        int arg_1_p = 0;
        int arg_2_p = 0;  
    }
    namespace gps
    {
        float altitude = 0.0;
        float altitude_average = 0.0;
    }
    namespace video
    {
        bool on = false;
    }
}