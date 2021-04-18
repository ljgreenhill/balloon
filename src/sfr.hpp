#ifndef SFR_HPP_
#define SFR_HPP_

#include "Arduino.h"
#include "Modes/mission_mode_type.enum"
#include "Modes/rockblock_mode_type.enum"
#include "Modes/burnwire_mode_type.enum"
#include "constants.hpp"
#include "MissionManager.hpp"

namespace sfr
{
    namespace photoresistor
    {
        extern bool covered;
    }
    namespace mission
    {
        extern mission_mode_type mode;
    }
    namespace burnwire
    {
        extern bool fire;
        extern burnwire_mode_type mode;
        extern int attempts;
        extern int start_time;
    }
    namespace camera
    {
        extern bool take_photo;
        extern bool photo_taken;
        extern uint8_t buffer[255];
        extern uint16_t current_serial;
        extern uint8_t fragment_number;
        extern uint8_t max_fragments;
        extern uint8_t data_length;
        extern uint8_t fragment_number_requested;
        extern uint8_t serial_requested;
        extern bool fragment_requested;
        extern uint8_t images_written;
        extern uint16_t image_lengths[255];
        extern bool report_ready;
        extern bool full_image_written;
        extern bool report_downlinked;
    }
    namespace rockblock
    {
        extern unsigned long last_downlink;
        extern unsigned long downlink_period;
        extern rockblock_mode_type mode;
        extern bool waiting_message;
        extern char buffer[constants::rockblock::buffer_size];
        extern uint8_t report[constants::rockblock::packet_size];
        extern int commas[constants::rockblock::num_commas];
        extern unsigned char data_length[4];
        extern unsigned char opcode[2];
        extern unsigned char arg_1[4];
        extern unsigned char arg_2[4];


        extern int num_iter;
        extern bool waiting_command;
    }
    namespace gps
    {
        extern float altitude;
    }
};

#endif