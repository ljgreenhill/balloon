#include "MainControlLoop.hpp"

MainControlLoop::MainControlLoop()
: ControlTask<void>(),
clock_manager(constants::timecontrol::control_cycle_time), 
camera_report_monitor(constants::timecontrol::camera_report_monitor_offset),
command_monitor(constants::timecontrol::command_monitor_offset),
normal_report_monitor(constants::timecontrol::normal_report_monitor_offset),
photoresistor_monitor(constants::timecontrol::photoresistor_monitor_offset),
burnwire_control_task(constants::timecontrol::burnwire_control_task_offset),
camera_control_task(constants::timecontrol::camera_control_task_offset),
rockblock_control_task(constants::timecontrol::rockblock_control_task_offset),
mission_manager(constants::timecontrol::mission_manager_offset)
{
    delay(1000);
}

void MainControlLoop::execute()
{
    clock_manager.execute();

    camera_report_monitor.execute_on_time();
    command_monitor.execute_on_time();
    normal_report_monitor.execute_on_time();
    photoresistor_monitor.execute_on_time();

    burnwire_control_task.execute_on_time();
    camera_control_task.execute_on_time();
    rockblock_control_task.execute_on_time();

    mission_manager.execute_on_time(); 
}