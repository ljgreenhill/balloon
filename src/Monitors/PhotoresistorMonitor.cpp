#include "PhotoresistorMonitor.hpp"

PhotoresistorMonitor::PhotoresistorMonitor(){}

void PhotoresistorMonitor::execute(){
    if(analogRead(constants::photoresistor::pin) < constants::photoresistor::light_val){
        sfr::photoresistor::covered = true;
    }
    else{
        sfr::photoresistor::covered = false;
    }
}