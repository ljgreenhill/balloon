#ifndef BURNWIRE_CONTROL_TASK_HPP_
#define BURNWIRE_CONTROL_TASK_HPP_

#include "sfr.hpp"

class BurnwireControlTask{
    public:
        BurnwireControlTask();
        void execute();
        void dispatch_burn();
};

#endif