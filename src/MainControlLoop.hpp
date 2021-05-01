#ifndef MAIN_CONTROL_LOOP_HPP_
#define MAIN_CONTROL_LOOP_HPP_

#include "sfr.hpp"
#include "constants.hpp"
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "MissionManager.hpp"
#include "Monitors/PhotoresistorMonitor.hpp"
#include "Control Tasks/RockblockControlTask.hpp"
#include "Control Tasks/VideoControlTask.hpp"
#include "Monitors/GPSMonitor.hpp"
#include "Monitors/NormalReportMonitor.hpp"
#include "Monitors/CommandMonitor.hpp"

class MainControlLoop
{
protected:

    PhotoresistorMonitor photoresistor_monitor;
    GPSMonitor gps_monitor;

    MissionManager mission_manager;

    NormalReportMonitor normal_report_monitor;

    CommandMonitor command_monitor;

    BurnwireControlTask burnwire_control_task;
    CameraControlTask camera_control_task;
    RockblockControlTask rockblock_control_task;
    VideoControlTask video_control_task;

public:
    MainControlLoop();
    void execute();
};

#endif