#ifndef SFR_HPP_
#define SFR_HPP_

#include "Arduino.h"
#include "Modes/mission_mode_type.enum"
#include "Modes/rockblock_mode_type.enum"
#include "Modes/burnwire_mode_type.enum"
#include "constants.hpp"
#include "MissionManager.hpp"
#include <SD.h>
#include <Adafruit_VC0706.h>
#include <iostream>
#include <string>
#include "TinyGPS.h"

namespace sfr
{
    namespace photoresistor
    {
        extern bool covered;
    }
    namespace mission
    {
        extern mission_mode_type mode;
        extern int time;
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
        extern uint8_t buffer[255];
    }
    namespace rockblock
    {
        extern unsigned long last_downlink;
        extern unsigned long downlink_period;
        extern rockblock_mode_type mode;
        extern bool waiting_message;
        extern int num_iter;
        extern bool waiting_command;

        extern char buffer[constants::rockblock::buffer_size];
        extern String report;

        extern int commas[constants::rockblock::num_commas];

        extern unsigned char opcode[1];
        extern unsigned char arg_1[1];
        extern unsigned char arg_2[1];

        extern int opcode_p;
        extern int arg_1_p;
        extern int arg_2_p;

    }
    namespace gps
    {
        extern float altitude;
        extern float altitude_average;
    }
    namespace video
    {
        extern bool on;
    }
};

#endif