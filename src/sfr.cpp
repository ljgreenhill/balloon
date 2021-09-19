#include "sfr.hpp"

namespace sfr
{
    namespace timer
    {
        float start_time = 0.0;
    }
    namespace photoresistor
    {
        bool covered = true;
    }
    namespace mission
    {
        mission_mode_type mode = mission_mode_type::standby;
    }
    namespace burnwire
    {
        burnwire_mode_type mode = burnwire_mode_type::standby;
        int attempts = 0;
        int start_time = 0;
        int camera_attempts = 0;
        int burn_time = 500;
    }
    namespace camera
    {
        bool photo_taken_sd_failed = false;
        bool take_photo = false;
        bool turn_on = false;
        bool turn_off = false;
        bool powered = false;
        uint8_t buffer[255] = {0};
        int current_serial = 0;
        int fragment_number = 0;
        int fragment_number_requested = 3;
        int serial_requested = 0;
        bool fragment_requested = false;
        int images_written = 0;
        int fragments_written = 0;
        int image_lengths[255];
        bool report_ready = false;
        bool full_image_written = false;
        bool report_downlinked = true;
        char filename[15];
        uint16_t jpglen = 0;
    }
    namespace rockblock
    {
        unsigned long last_communication = 0;
        bool last_downlink_normal = false;
        int camera_commands[99][constants::rockblock::command_len] = {};
        int camera_max_fragments[99] = {};
        bool downlink_camera = false;
        unsigned long last_downlink = 0;
        unsigned long downlink_period = 0;
        unsigned long camera_downlink_period = 0;
        rockblock_mode_type mode = rockblock_mode_type::send_at;
        bool waiting_message = false;
        char buffer[constants::rockblock::buffer_size] = {0};
        uint8_t report[constants::rockblock::packet_size] = {0};
        uint8_t camera_report[constants::rockblock::packet_size] = {0};
        int commas[constants::rockblock::num_commas] = {0};
        uint8_t opcode[2] = {0};
        uint8_t arg_1[4] = {0};
        uint8_t arg_2[4] = {0};
#ifndef SIMULATOR
        HardwareSerial serial = Serial1;
#else
        RockblockSimulator serial;
#endif
        bool flush_status = false;
        bool waiting_command = false;
        size_t conseq_reads = 0;
        uint16_t f_opcode = 0;
        uint32_t f_arg_1 = 0;
        uint32_t f_arg_2 = 0;
        int timeout = 10 * constants::rockblock::one_minute;
        int start_time = 0;
        bool last_timed_out = false;
        int num_downlinks = 0;
    }
    namespace gps
    {
        float altitude = 0.0;
        std::deque<float> altitude_buffer;
        float altitude_average = 0.0;
        float latitude = 0.0;
        std::deque<float> latitude_buffer;
        float latitude_average = 0.0;
        float longitude = 0.0;
        std::deque<float> longitude_buffer;
        float longitude_average = 0.0;
        bool new_data = false;
    }
}