#include "RockblockControlTask.hpp"
#include <sstream>

RockblockControlTask::RockblockControlTask(){
    Serial4.begin(constants::rockblock::baud);
}

void RockblockControlTask::execute(){
    if(sfr::rockblock::num_iter > constants::rockblock::max_iter){
        transition_to(rockblock_mode_type::standby);
    }
    rockblock_mode_type mode = sfr::rockblock::mode;
    sfr::rockblock::num_iter++;
    switch(mode){
        case rockblock_mode_type::standby:
            Serial.println("standby");
            dispatch_standby();
            break;
        case rockblock_mode_type::send_at:
            Serial.println("send_at");
            dispatch_send_at();
            break;
        case rockblock_mode_type::await_at:
            Serial.println("await_at");
            dispatch_await_at();
            break;
        case rockblock_mode_type::send_signal_strength:
            Serial.println("send_signal_strength");
            dispatch_send_signal_strength();
            break;
        case rockblock_mode_type::await_signal_strength:
            // Serial.println("await_signal_strength");
            dispatch_await_signal_strength();
            break;
        case rockblock_mode_type::send_flow_control:
            Serial.println("send_flow_control");
            dispatch_send_flow_control();
            break;
        case rockblock_mode_type::await_flow_control:
            Serial.println("await_flow_control");
            dispatch_await_flow_control();
            break;
        case rockblock_mode_type::send_message:
            Serial.println("send_message");
            dispatch_send_message(); 
            break;
        case rockblock_mode_type::await_message:
            Serial.println("await_message");
            dispatch_await_message();
            break; 
        case rockblock_mode_type::send_response:
            Serial.println("send_response");
            dispatch_send_response(); 
            break;
        case rockblock_mode_type::create_buffer:
            Serial.println("create_buffer");
            dispatch_create_buffer(); 
            break;
        case rockblock_mode_type::process_mo_status:
            Serial.println("process_mo_status");
            dispatch_process_mo_status(); 
            break;
        case rockblock_mode_type::process_mt_status:
            Serial.println("process_mt_status");
            dispatch_process_mt_status();
            break;
        case rockblock_mode_type::read_message:
            Serial.println("read_message");
            dispatch_read_message();
            break;
        case rockblock_mode_type::process_command:
            Serial.println("process_command");
            dispatch_process_command();
            break;
        case rockblock_mode_type::end_transmission:
            Serial.println("end_transmission");
            dispatch_end_transmission();
            break;
    }
}

bool RockblockControlTask::check_ready(){
    if(millis() - sfr::rockblock::last_downlink >= sfr::rockblock::downlink_period){
        return true;
    } else{
        return false;
    }
}

void RockblockControlTask::dispatch_standby(){
    if(sfr::rockblock::waiting_message || check_ready()){
        transition_to(rockblock_mode_type::send_at);
    }
}

void RockblockControlTask::dispatch_send_at(){
    Serial4.print("AT\r");
    transition_to(rockblock_mode_type::await_at);
}

void RockblockControlTask::dispatch_await_at(){
    if(Serial4.read()=='K'){
        transition_to(rockblock_mode_type::send_signal_strength);
    }
}

void RockblockControlTask::dispatch_send_signal_strength(){
    Serial4.print("AT+CSQ\r");
    transition_to(rockblock_mode_type::await_signal_strength);

}

void RockblockControlTask::dispatch_await_signal_strength(){
    if(Serial4.read()==':'){
        char signal = Serial4.read();
        Serial.print("SIGNAL: ");
        Serial.println(signal);
        if(signal =='3' || signal =='4' || signal =='5'){
            transition_to(rockblock_mode_type::send_flow_control);
        } else{
            transition_to(rockblock_mode_type::send_signal_strength);
        }
    }
    
}

void RockblockControlTask::dispatch_send_flow_control(){
    Serial4.print("AT&K0\r");
    transition_to(rockblock_mode_type::await_flow_control);
}

void RockblockControlTask::dispatch_await_flow_control(){
    if(Serial4.read()=='K'){
        transition_to(rockblock_mode_type::send_message);
    } 
}

void RockblockControlTask::dispatch_send_message(){
    Serial.println(sfr::rockblock::report);
    Serial4.write("AT+SBDWT=");
    for (int i = 0; i < sfr::rockblock::report.length(); i++){
        Serial4.write(sfr::rockblock::report[i]);  
    }
    Serial4.write("\r");
    transition_to(rockblock_mode_type::await_message);
}

void RockblockControlTask::dispatch_await_message(){
    if(Serial4.read()=='K'){
        transition_to(rockblock_mode_type::send_response);
    } 
}

void RockblockControlTask::dispatch_send_response(){
    Serial4.print("AT+SBDIX\r");
    transition_to(rockblock_mode_type::create_buffer);
}

void RockblockControlTask::dispatch_create_buffer(){
    if(Serial4.read() == ':'){
        int relevant_chars = Serial4.available()-8;
        int buffer_iter = 0;
        int comma_iter = 0;
        for (int i=0; i<relevant_chars; ++i){
            char c = Serial4.read();
            if(c != ' '){
                sfr::rockblock::buffer[buffer_iter] = c;
                Serial.println( sfr::rockblock::buffer[buffer_iter]);
                if(c == ','){
                    sfr::rockblock::commas[comma_iter] = buffer_iter;
                    comma_iter++;
                }
                buffer_iter++;
            }
        }
        if(comma_iter != 5){
            transition_to(rockblock_mode_type::send_response);
        }
        else{
            transition_to(rockblock_mode_type::process_mo_status);
        }
                    
    }
}

void RockblockControlTask::dispatch_process_mo_status(){
    if(sfr::rockblock::commas[0] > 1){
        Serial.println("there is another character");
        transition_to(rockblock_mode_type::send_signal_strength);
    }
    else if(sfr::rockblock::buffer[0] != '0' && sfr::rockblock::buffer[0] != '1' && sfr::rockblock::buffer[0] != '2'){
        Serial.println("mo status is greater than 2");
        transition_to(rockblock_mode_type::send_signal_strength);
    } else{
        transition_to(rockblock_mode_type::process_mt_status);
    }             
}

void RockblockControlTask::dispatch_process_mt_status(){
    switch(sfr::rockblock::buffer[sfr::rockblock::commas[1]+1]){
        case '2':
            Serial.println("error during check");
            transition_to(rockblock_mode_type::send_response);
            break;
        case '1':
            Serial.println("there are messages waiting");
            transition_to(rockblock_mode_type::read_message);
            break;
        case '0':
            Serial.println("there were no messages to retrieve");
            transition_to(rockblock_mode_type::end_transmission);
            break;
    }              
}

void RockblockControlTask::dispatch_read_message(){
    Serial4.print("AT+SBDRB\r");
    transition_to(rockblock_mode_type::process_command);
}

void RockblockControlTask::dispatch_process_command(){
    if(Serial4.read() == 'S' && Serial4.read() == 'B' && Serial4.read() == 'D' && Serial4.read() == 'R' && Serial4.read() == 'B'){
        Serial4.read();
        Serial4.read();
        Serial4.read();

        sfr::rockblock::opcode_p = Serial4.read();
        Serial.print("OPCODE: ");
        Serial.println(sfr::rockblock::opcode_p);

        sfr::rockblock::arg_1_p = Serial4.read();
        Serial.print("ARG_1: ");
        Serial.println(sfr::rockblock::arg_1_p);

        sfr::rockblock::arg_2_p = Serial4.read();
        Serial.print("ARG_2: ");
        Serial.println(sfr::rockblock::arg_2_p);

        sfr::rockblock::waiting_command = true;

        transition_to(rockblock_mode_type::end_transmission);
    } 
}

void RockblockControlTask::dispatch_end_transmission(){
    sfr::rockblock::last_downlink = millis();
    transition_to(rockblock_mode_type::standby);
}


void RockblockControlTask::transition_to(rockblock_mode_type new_mode){
    sfr::rockblock::mode = new_mode;
    sfr::rockblock::num_iter = 0;
}

