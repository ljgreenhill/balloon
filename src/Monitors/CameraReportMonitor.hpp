#ifndef CAMERA_REPORT_MONITOR_HPP_
#define CAMERA_REPORT_MONITOR_HPP_

#include "sfr.hpp"

class CameraReportMonitor
{
public:
    CameraReportMonitor();
    void execute();
    File imgFile;
};

#endif