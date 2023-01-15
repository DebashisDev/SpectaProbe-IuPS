/*
 * NASConstants.h
 *
 *  Created on: 17-Jul-2016
 *      Author: Deb
 */

#ifndef PLUGINS_IUPS_INC_NASCONSTANTS_H_
#define PLUGINS_IUPS_INC_NASCONSTANTS_H_


#define PD_Group_call_control 0x00
#define PD_Broadcast_call_control 0x01
#define PD_EPS_session_management_messages 0x02
#define PD_Call_control_Call_related_SS_messages 0x03
#define PD_GPRS_Transparent_Transport_Protocol_GTTP 0x04
#define PD_Mobility_management_messages 0x05
#define PD_Radio_resources_management_messages 0x06
#define PD_EPS_mobility_management_messages 0x07
#define PD_GPRS_mobility_management_messages 0x08
#define PD_SMS_messages 0x09
#define PD_GPRS_session_management_messages 0x0a
#define PD_Non_call_related_SS_messages 0x0b
#define PD_Location_services 0x0c
#define PD_Reserved_for_extension_of_the_PD_to_one_octet_length 0x0d
#define PD_Used_by_tests_procedures 0x0f

#define MAX_GMM_ID_VALUE 0x5d

#define MM_Attach_request 0x01
#define MM_Attach_accept 0x02
#define MM_Attach_complete 0x03
#define MM_Attach_reject 0x04
#define MM_Detach_request 0x05
#define MM_Detach_accept 0x06
#define MM_Routing_area_update_request 0x08
#define MM_Routing_area_update_accept 0x09
#define MM_Routing_area_update_complete 0x0a
#define MM_Routing_area_update_reject 0x0b
#define MM_Service_Request 0x0c
#define MM_Service_Accept 0x0d
#define MM_Service_Reject 0x0e
#define MM_P_TMSI_reallocation_command 0x10
#define MM_P_TMSI_reallocation_complete 0x11
#define MM_Authentication_and_ciphering_req 0x12
#define MM_Authentication_and_ciphering_resp 0x13
#define MM_Authentication_and_ciphering_rej 0x14
#define MM_Authentication_and_ciphering_failure 0x1b
#define MM_Identity_request 0x15
#define MM_Identity_response 0x16
#define MM_GMM_status 0x20
#define MM_GMM_information 0x21

#define SM_Activate_PDP_context_request 0x41
#define SM_Activate_PDP_context_accept 0x42
#define SM_Activate_PDP_context_reject 0x43
#define SM_Request_PDP_context_activation 0x44
#define SM_Request_PDP_context_activation_rej 0x45
#define SM_Deactivate_PDP_context_request 0x46
#define SM_Deactivate_PDP_context_accept 0x47
#define SM_Modify_PDP_context_request_Network_to_MS_direction 0x48
#define SM_Modify_PDP_context_accept_MS_to_network_direction 0x49
#define SM_Modify_PDP_context_request_MS_to_network_direction 0x4a
#define SM_Modify_PDP_context_accept_Network_to_MS_direction 0x4b
#define SM_Modify_PDP_context_reject 0x4c
#define SM_Activate_secondary_PDP_context_request 0x4d
#define SM_Activate_secondary_PDP_context_accept 0x4e
#define SM_Activate_secondary_PDP_context_reject 0x4f

//public static final byte SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol 0x50
//public static final byte SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol 0x51
//public static final byte SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol 0x52
//public static final byte SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol 0x53
//public static final byte SM_Reserved_was_allocated_in_earlier_phases_of_the_protocol 0x54

#define SM_SM_Status 0x55
#define SM_Activate_MBMS_Context_Request 0x56
#define SM_Activate_MBMS_Context_Accept 0x57
#define SM_Activate_MBMS_Context_Reject 0x58
#define SM_Request_MBMS_Context_Activation 0x59
#define SM_Request_MBMS_Context_Activation_Reject 0x5a
#define SM_Request_Secondary_PDP_Context_Activation 0x5b
#define SM_Request_Secondary_PDP_Context_Activation_Reject 0x5c
#define SM_Notification 0x5d

//Need validation
#define MM_Status 0x71
#define UNKNOWN_Reserved 0x66



#endif /* PLUGINS_IUPS_INC_NASCONSTANTS_H_ */
