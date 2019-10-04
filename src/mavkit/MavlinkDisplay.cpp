#include <mavkit/MavlinkDisplay.h>

#include <iostream>

//----------------------------------------------------------------------------//
MavlinkDisplay::MavlinkDisplay()
{}
//----------------------------------------------------------------------------//
MavlinkDisplay::~MavlinkDisplay()
{}
//----------------------------------------------------------------------------//
void MavlinkDisplay::append_listener(MavMessengerInterface* listener)
{}
//----------------------------------------------------------------------------//
void MavlinkDisplay::start()
{}
//----------------------------------------------------------------------------//
void MavlinkDisplay::join()
{}
//----------------------------------------------------------------------------//
bool MavlinkDisplay::send_message(mavlink_message_t &msg)
{
    mutex.lock();
    switch(msg.msgid)
    {
        case MAVLINK_MSG_ID_HEARTBEAT:
        {
            mavlink_heartbeat_t heartbeat;
            mavlink_msg_heartbeat_decode(&msg, &heartbeat);
            std::cout << "HEARTBEAT (#0)" << std::endl;
            //std::cout << "----------------------" << std::endl;
            //std::cout << "    type:            "  << (uint)heartbeat.type << std::endl;
            //std::cout << "    autopilot:       "  << (uint)heartbeat.autopilot << std::endl;
            //std::cout << "    base_mode:       "  << (uint)heartbeat.base_mode << std::endl;
            //std::cout << "    custom_mode:     "  << (uint)heartbeat.custom_mode << std::endl;
            //std::cout << "    system_status:   "  << (uint)heartbeat.system_status << std::endl;
            //std::cout << "    mavlink_version: "  << (uint)heartbeat.mavlink_version << std::endl;
            break;
        }
        case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
        {
            mavlink_param_request_list_t param_request_list;
            mavlink_msg_param_request_list_decode(&msg, &param_request_list);
            std::cout << "PARAM_REQUEST_LIST (#21)" << std::endl;
            break;
        }
        case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:
        {
            mavlink_mission_request_list_t mission_request_list;
            mavlink_msg_mission_request_list_decode(&msg, &mission_request_list);
            std::cout << "MISSION_REQUEST_LIST (#43)" << std::endl;
            break;
        }
        case MAVLINK_MSG_ID_COMMAND_LONG:
        {
            mavlink_command_long_t command_long;
            mavlink_msg_command_long_decode(&msg, &command_long);
            std::cout << "COMMAND_LONG (#76)"       << std::endl;
            std::cout << "----------------------"   << std::endl;
            std::cout << "    command: " << (uint)command_long.command << std::endl;
            break;
        }
        default:
        {
            std::cout << "SYS: "      << (int)msg.sysid;
            std::cout << ", COMP: "   << (int)msg.compid;
            std::cout << ", SEQ: "    << (int)msg.seq;
            std::cout << ", LEN: "    << (int)msg.len;
            std::cout << ", MSG ID: " << (int)msg.msgid << std::endl;
            break;
        }
    }
    std::cout << "----------------------" << std::endl;
    mutex.unlock();

    return true;
}
//----------------------------------------------------------------------------//
