#ifndef MAIN_CONTROL_LOOP_HPP_
#define MAIN_CONTROL_LOOP_HPP_

#include "sfr.hpp"
#include "ClockManager.hpp"
#include "Monitors/CameraReportMonitor.hpp"
#include "Monitors/CommandMonitor.hpp"
#include "Monitors/NormalReportMonitor.hpp"
#include "Monitors/PhotoresistorMonitor.hpp"
#include "Monitors/GPSMonitor.hpp"
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "Control Tasks/RockblockControlTask.hpp"
#include "Control Tasks/VideoControlTask.hpp"

class MainControlLoop : ControlTask<void>
{
protected:
    
    ClockManager clock_manager;

    CameraReportMonitor camera_report_monitor;
    CommandMonitor command_monitor;
    GPSMonitor gps_monitor;
    NormalReportMonitor normal_report_monitor;
    PhotoresistorMonitor photoresistor_monitor;

    BurnwireControlTask burnwire_control_task;
    CameraControlTask camera_control_task;
    RockblockControlTask rockblock_control_task;
    VideoControlTask video_control_task;

    MissionManager mission_manager;

public:
    MainControlLoop();
    void execute() override;
};

#endif