#include "CommandMonitor.hpp"

CommandMonitor::CommandMonitor(unsigned int offset) : TimedControlTask<void>(offset) {}

void CommandMonitor::execute()
{
    if (sfr::rockblock::waiting_command)
    {
        if (sfr::rockblock::f_opcode == get_decimal_opcode(constants::rockblock::mission_mode))
        {
            dispatch_change_mission_mode();
        }
        else if (sfr::rockblock::f_opcode == get_decimal_opcode(constants::rockblock::burnwire_time))
        {
            dispatch_change_burnwire_time();
        }
        else if (sfr::rockblock::f_opcode == get_decimal_opcode(constants::rockblock::burnwire_timeout))
        {
            dispatch_change_burnwire_timeout();
        }
        else if (sfr::rockblock::f_opcode == get_decimal_opcode(constants::rockblock::rockblock_downlink_period))
        {
            dispatch_change_rockblock_downlink_period();
        }
        else if (sfr::rockblock::f_opcode == get_decimal_opcode(constants::rockblock::request_image_fragment))
        {
            dispatch_request_image_fragment();
        }
        sfr::rockblock::waiting_command = false;
    }
}

void CommandMonitor::dispatch_change_mission_mode()
{
    if (sfr::rockblock::f_arg_1 == get_decimal_arg(constants::rockblock::deployment))
    {
        MissionManager::transition_to_deployment();
    }
    else if (sfr::rockblock::f_arg_1 == get_decimal_arg(constants::rockblock::standby))
    {
        MissionManager::transition_to_standby();
    }
    else if (sfr::rockblock::f_arg_1 == get_decimal_arg(constants::rockblock::high_altitude))
    {
        MissionManager::transition_to_high_altitude();
    }
}

void CommandMonitor::dispatch_change_true_false(bool &value)
{
    value = sfr::rockblock::f_arg_1;
}

void CommandMonitor::dispatch_request_image_fragment()
{
    if (sfr::rockblock::f_arg_2 < sfr::rockblock::camera_max_fragments[sfr::rockblock::f_arg_1])
    {
        sfr::camera::fragment_requested = true;
        sfr::camera::fragment_number_requested = sfr::rockblock::f_arg_2;
        sfr::camera::serial_requested = sfr::rockblock::f_arg_1;

#ifdef VERBOSE
        Serial.print("Fragment requested: ");
        Serial.println(sfr::camera::fragment_number_requested);
        Serial.print("Serial requested: ");
        Serial.println(sfr::camera::serial_requested);
#endif
    }
}

void CommandMonitor::dispatch_change_rockblock_downlink_period()
{
    if (sfr::rockblock::f_arg_1 < constants::rockblock::max_downlink_period && sfr::rockblock::f_arg_1 > constants::rockblock::min_downlink_period)
    {
        sfr::rockblock::downlink_period = sfr::rockblock::f_arg_1;
    }
}

void CommandMonitor::dispatch_change_burnwire_time()
{
    if (sfr::rockblock::f_arg_1 < constants::burnwire::max_burnwire_time && sfr::rockblock::f_arg_1 > constants::burnwire::min_burnwire_time)
    {
        sfr::burnwire::burn_time = sfr::rockblock::f_arg_1;
    }
}

uint16_t CommandMonitor::get_decimal_opcode(const uint8_t *hex_opcode_bytes)
{
    return (hex_opcode_bytes[1] << 8) | (hex_opcode_bytes[0]);
}

uint32_t CommandMonitor::get_decimal_arg(const uint8_t *hex_arg_bytes)
{
    return (hex_arg_bytes[3] << 24) | (hex_arg_bytes[2]) << 16 | (hex_arg_bytes[1] << 8) | (hex_arg_bytes[0]);
}

void CommandMonitor::dispatch_change_burnwire_timeout()
{
    if (sfr::rockblock::f_arg_1 < constants::burnwire::max_armed_time && sfr::rockblock::f_arg_1 > constants::burnwire::min_armed_time)
    {
        sfr::burnwire::burn_time = sfr::rockblock::f_arg_1;
    }
}