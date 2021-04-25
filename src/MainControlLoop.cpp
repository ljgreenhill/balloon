#include "MainControlLoop.hpp"

MainControlLoop::MainControlLoop()
{
    sfr::burnwire::fire = true; 
    
}

void MainControlLoop::execute()
{
    
    burnwire_control_task.execute();

}