#ifndef MAIN_CONTROL_LOOP_HPP_
#define MAIN_CONTROL_LOOP_HPP_

#include "sfr.hpp"
#include "constants.hpp"
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "MissionManager.hpp"
#include "Monitors/PhotoresistorMonitor.hpp"
#include "Control Tasks/RockblockControlTask.hpp"
#include "Monitors/CameraReportMonitor.hpp"
#include "Monitors/GPSMonitor.hpp"

class MainControlLoop
{
protected:

    CameraReportMonitor camera_report_monitor;
    PhotoresistorMonitor photoresistor_monitor;
    GPSMonitor gps_monitor;

    MissionManager mission_manager;

    BurnwireControlTask burnwire_control_task;
    CameraControlTask camera_control_task;
    RockblockControlTask rockblock_control_task;

public:
    MainControlLoop();
    void execute();
};

#endif