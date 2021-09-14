#ifndef VIDEO_CONTROL_TASK_HPP_
#define VIDEO_CONTROL_TASK_HPP_

#include "sfr.hpp"

class VideoControlTask : public TimedControlTask<void>{

    public:
        VideoControlTask(unsigned int offset);
        void execute();
       
};

#endif