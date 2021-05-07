#ifndef MAIN_CONTROL_LOOP_HPP_
#define MAIN_CONTROL_LOOP_HPP_

#include "sfr.hpp"
#include "constants.hpp"
#include "MissionManager.hpp"
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "Control Tasks/RockblockControlTask.hpp"
#include "Control Tasks/VideoControlTask.hpp"
#include "Monitors/CommandMonitor.hpp"
#include "Monitors/GPSMonitor.hpp"
#include "Monitors/NormalReportMonitor.hpp"
#include "Monitors/PhotoresistorMonitor.hpp"

class MainControlLoop
{
protected:
    MissionManager mission_manager;

    BurnwireControlTask burnwire_control_task;
    CameraControlTask camera_control_task;
    RockblockControlTask rockblock_control_task;
    VideoControlTask video_control_task;

    CommandMonitor command_monitor;
    GPSMonitor gps_monitor;
    NormalReportMonitor normal_report_monitor;
    PhotoresistorMonitor photoresistor_monitor;

public:
    MainControlLoop();
    void execute();
};

#endif