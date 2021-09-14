#ifndef MAIN_CONTROL_LOOP_HPP_
#define MAIN_CONTROL_LOOP_HPP_

#include "sfr.hpp"
#include "ClockManager.hpp"
#include "Monitors/CameraReportMonitor.hpp"
#include "Monitors/CommandMonitor.hpp"
#include "Monitors/NormalReportMonitor.hpp"
#include "Monitors/PhotoresistorMonitor.hpp"
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "Control Tasks/RockblockControlTask.hpp"

class MainControlLoop : ControlTask<void>
{
protected:
    
    ClockManager clock_manager;

    CameraReportMonitor camera_report_monitor;
    CommandMonitor command_monitor;
    NormalReportMonitor normal_report_monitor;
    PhotoresistorMonitor photoresistor_monitor;

    BurnwireControlTask burnwire_control_task;
    CameraControlTask camera_control_task;
    RockblockControlTask rockblock_control_task;

    MissionManager mission_manager;

public:
    MainControlLoop();
    void execute() override;
};

#endif