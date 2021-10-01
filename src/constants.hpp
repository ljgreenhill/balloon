#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

namespace constants
{
    namespace timer
    {
        constexpr int fail_safe_deploy = 5400000;
    }
    namespace photoresistor
    {
        constexpr int pin = 22;
        constexpr int light_val = 400;
    }
    namespace burnwire
    {
        constexpr int pin = 30;
        constexpr int burn_wait = 500;
        constexpr int max_attempts = 10;
        constexpr int burn_time = 200;
    }
    namespace rockblock
    {
        constexpr unsigned long one_second = 1000;

        constexpr unsigned long one_minute = 60 * one_second;
        constexpr unsigned long ten_minutes = 10 * one_minute;
        constexpr unsigned long five_minutes = 5 * one_minute;

        constexpr int sleep_pin = 29;

        constexpr int min_sleep_period = 2 * one_minute;

        constexpr int min_downlink_period = one_second;
        constexpr int max_downlink_period = ten_minutes;

        constexpr int baud = 19200;
        constexpr size_t buffer_size = 63;
        constexpr size_t packet_size = 70;
        constexpr size_t num_commas = 5;
        constexpr size_t max_iter = 200;
        constexpr size_t num_commands = 4;
        constexpr size_t opcode_len = 2;
        constexpr size_t arg1_len = 4;
        constexpr size_t arg2_len = 4;
        constexpr size_t command_len = opcode_len + arg1_len + arg2_len;
        constexpr size_t max_conseq_read = 3;

        constexpr int num_initial_downlinks = 2;

        constexpr uint8_t mission_mode[opcode_len] = {0x00, 0x00};
        constexpr uint8_t rockblock_downlink_period[opcode_len] = {0x01, 0x00};
        constexpr uint8_t request_image_fragment[opcode_len] = {0x02, 0x00};

        constexpr uint8_t standby[arg1_len] = {0x00, 0x00, 0x00, 0x00};
        constexpr uint8_t high_altitude[arg1_len] = {0x01, 0x00, 0x00, 0x00};
        constexpr uint8_t deployment[arg1_len] = {0x02, 0x00, 0x00, 0x00};
        constexpr uint8_t post_deployment[arg1_len] = {0x03, 0x00, 0x00, 0x00};

        constexpr uint8_t true_arg[arg1_len] = {0x01, 0x00, 0x00, 0x00};
        constexpr uint8_t false_arg[arg1_len] = {0x00, 0x00, 0x00, 0x00};

        constexpr uint8_t active[arg1_len] = {0x01, 0x00, 0x00, 0x00};
        constexpr uint8_t inactive[arg1_len] = {0x00, 0x00, 0x00, 0x00};

        constexpr uint8_t no_arg_2[arg2_len] = {0x00, 0x00, 0x00, 0x00};

        constexpr uint8_t mission_mode_high_altitude[command_len] = {
            mission_mode[0], mission_mode[1],
            high_altitude[0], high_altitude[1], high_altitude[2], high_altitude[3],
            no_arg_2[0], no_arg_2[1], no_arg_2[2], no_arg_2[3]};

        constexpr uint8_t mission_mode_deployment[command_len] = {
            mission_mode[0], mission_mode[1],
            deployment[0], deployment[1], deployment[2], deployment[3],
            no_arg_2[0], no_arg_2[1], no_arg_2[2], no_arg_2[3]};

        constexpr uint8_t mission_mode_standby[command_len] = {
            mission_mode[0], mission_mode[1],
            standby[0], standby[1], standby[2], standby[3],
            no_arg_2[0], no_arg_2[1], no_arg_2[2], no_arg_2[3]};

        constexpr uint8_t mission_mode_post_deployment[command_len] = {
            mission_mode[0], mission_mode[1],
            post_deployment[0], post_deployment[1], post_deployment[2], post_deployment[3],
            no_arg_2[0], no_arg_2[1], no_arg_2[2], no_arg_2[3]};

        constexpr int known_commands[num_commands][command_len] = {
            {mission_mode_deployment[0], mission_mode_deployment[1], mission_mode_deployment[2], mission_mode_deployment[3], mission_mode_deployment[4], mission_mode_deployment[5], mission_mode_deployment[6], mission_mode_deployment[7], mission_mode_deployment[8], mission_mode_deployment[9]},
            {mission_mode_standby[0], mission_mode_standby[1], mission_mode_standby[2], mission_mode_standby[3], mission_mode_standby[4], mission_mode_standby[5], mission_mode_standby[6], mission_mode_standby[7], mission_mode_standby[8], mission_mode_standby[9]},
            {mission_mode_high_altitude[0], mission_mode_high_altitude[1], mission_mode_high_altitude[2], mission_mode_high_altitude[3], mission_mode_high_altitude[4], mission_mode_high_altitude[5], mission_mode_high_altitude[6], mission_mode_high_altitude[7], mission_mode_high_altitude[8], mission_mode_high_altitude[9]},
            {mission_mode_post_deployment[0], mission_mode_post_deployment[1], mission_mode_post_deployment[2], mission_mode_post_deployment[3], mission_mode_post_deployment[4], mission_mode_post_deployment[5], mission_mode_post_deployment[6], mission_mode_post_deployment[7], mission_mode_post_deployment[8], mission_mode_post_deployment[9]}};
    }
    namespace camera
    {
        constexpr int content_length = 64;
        constexpr int bytes_allocated_serial_opcode = 2;
        constexpr int bytes_allocated_fragment = 4;
    }
    namespace timecontrol
    {
        // Environment-based initializations of the control loop time.
        // control_cycle_time is the value actually used for timing. The
        // other constants are just informational.
        constexpr unsigned int control_cycle_time_ms = 100;
        constexpr unsigned int control_cycle_time_us = control_cycle_time_ms * 1000;
        constexpr unsigned int control_cycle_time = control_cycle_time_us;

        static constexpr unsigned int base_offset = 30000;
        // Control cycle time offsets, in microseconds
        static constexpr unsigned int acs_monitor_offset = 0;
        static constexpr unsigned int battery_monitor_offset = 1 * base_offset;
        static constexpr unsigned int button_monitor_offset = 2 * base_offset;
        static constexpr unsigned int camera_report_monitor_offset = 3 * base_offset;
        static constexpr unsigned int command_monitor_offset = 4 * base_offset;
        static constexpr unsigned int current_monitor_offset = 5 * base_offset;
        static constexpr unsigned int fault_monitor_offset = 6 * base_offset;
        static constexpr unsigned int imu_monitor_offset = 7 * base_offset;
        static constexpr unsigned int normal_report_monitor_offset = 8 * base_offset;
        static constexpr unsigned int photoresistor_monitor_offset = 9 * base_offset;
        static constexpr unsigned int temperature_monitor_offset = 10 * base_offset;

        static constexpr unsigned int acs_control_task_offset = 11 * base_offset;
        static constexpr unsigned int burnwire_control_task_offset = 12 * base_offset;
        static constexpr unsigned int camera_control_task_offset = 13 * base_offset;
        static constexpr unsigned int rockblock_control_task_offset = 14 * base_offset;
        static constexpr unsigned int temperature_control_task_offset = 15 * base_offset;

        static constexpr unsigned int mission_manager_offset = 16 * base_offset;
    }
    namespace gps
    {
        constexpr int baud = 9600;
        constexpr int mand_deploy = 27143;
        constexpr int high_altitude = 20000;
        const unsigned char SetCfgNav5[] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0x01, 0x01,
                                            0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27,
                                            0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00,
                                            0x64, 0x00, 0x2C, 0x01, 0x00, 0x3C, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x56, 0x76};
        constexpr uint8_t CheckNav[] = {0xB5, 0x62, 0x06, 0x24, 0x00, 0x00, 0x2A, 0x84};
        constexpr float min_altitude_average = 0;
        constexpr float max_altitude_average = 2000000;
        constexpr float min_longitude_average = -180;
        constexpr float max_longitude_average = 180;
        constexpr float min_latitude_average = -90;
        constexpr float max_latitude_average = 90;

    }
    namespace sensor
    {
        constexpr int collect = 3;
    }
    namespace video
    {
        constexpr int pin = 2;
        constexpr int four_hours = 14400000;
    }
};

#endif