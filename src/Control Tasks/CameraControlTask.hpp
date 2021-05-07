#ifndef CAMERA_CONTROL_TASK_HPP_
#define CAMERA_CONTROL_TASK_HPP_

#include "sfr.hpp"

class CameraControlTask{

    public:
        CameraControlTask();
        void execute();
        Adafruit_VC0706 adaCam;
};

#endif