#include "BurnwireControlTask.hpp"

BurnwireControlTask::BurnwireControlTask(unsigned int offset) : TimedControlTask<void>(offset)
{
    pinMode(constants::burnwire::pin, OUTPUT);
}

void BurnwireControlTask::execute()
{
    burnwire_mode_type mode = sfr::burnwire::mode;

    switch (mode)
    {
    case burnwire_mode_type::standby:
    {
        if (sfr::mission::mode == mission_mode_type::deployment)
        {
            dispatch_burn();
        }
        else
        {
            transition_to_standby();
        }
        break;
    }
    case burnwire_mode_type::burn:
    {
        if (sfr::mission::mode == mission_mode_type::deployment)
        {
            if (millis() - sfr::burnwire::start_time >= (uint32_t)constants::burnwire::burn_time)
            {
                sfr::burnwire::mode = burnwire_mode_type::delay;
                digitalWrite(constants::burnwire::pin, LOW);
                sfr::burnwire::start_time = millis();
            }
            else
            {
                dispatch_burn();
            }
        }
        else
        {
            transition_to_standby();
        }
        break;
    }
    case burnwire_mode_type::delay:
    {
        if (sfr::mission::mode == mission_mode_type::deployment)
        {
            if (millis() - sfr::burnwire::start_time >= constants::burnwire::burn_wait)
            {
                dispatch_burn();
            }
            else
            {
                digitalWrite(constants::burnwire::pin, LOW);
            }
        }
        else
        {
            transition_to_standby();
        }
        break;
    }
    }
}

void BurnwireControlTask::dispatch_burn()
{
    sfr::burnwire::camera_attempts = 0;
    sfr::burnwire::mode = burnwire_mode_type::burn;
    sfr::burnwire::start_time = millis();
    if (sfr::burnwire::attempts > constants::burnwire::max_attempts)
    {
        transition_to_standby();
    }
    else
    {
        if (sfr::burnwire::attempts % 2 == 0)
        {
            digitalWrite(constants::burnwire::pin, HIGH);
        }
        else
        {
            digitalWrite(constants::burnwire::pin, LOW);
        }
        sfr::burnwire::attempts++;
    }
}

void BurnwireControlTask::transition_to_standby()
{
    sfr::burnwire::mode = burnwire_mode_type::standby;
    digitalWrite(constants::burnwire::pin, LOW);
    sfr::burnwire::attempts = 0;
}