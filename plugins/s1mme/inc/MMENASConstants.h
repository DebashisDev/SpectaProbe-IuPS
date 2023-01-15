/*
 * NASConstantsMME.h
 *
 *  Created on: 11-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_S1MME_INC_MMENASCONSTANTS_H_
#define PLUGINS_S1MME_INC_MMENASCONSTANTS_H_


#define EPS_PD_Group_call_control 0x00
#define EPS_PD_Broadcast_call_control 0x01
#define EPS_PD_EPS_session_management_messages 0x02
#define EPS_PD_Call_control_Call_related_SS_messages 0x03
#define EPS_PD_GPRS_Transparent_Transport_Protocol_GTTP 0x04
#define EPS_PD_Mobility_management_messages 0x05
#define EPS_PD_Radio_resources_management_messages 0x06
#define EPS_PD_EPS_mobility_management_messages 0x07
#define EPS_PD_GPRS_mobility_management_messages 0x08
#define EPS_PD_SMS_messages 0x09
#define EPS_PD_GPRS_session_management_messages 0x0a
#define EPS_PD_Non_call_related_SS_messages 0x0b
#define EPS_PD_Location_services 0x0c
#define EPS_PD_Reserved_for_extension_of_the_PD_to_one_octet_length 0x0d
#define EPS_PD_Used_by_tests_procedures 0x0f


//EPS mobility management messages
#define EPS_MM_Attach_request 0x41
#define EPS_MM_Attach_accept 0x42
#define EPS_MM_Attach_complete 0x43
#define EPS_MM_Attach_reject 0x44
#define EPS_MM_Detach_request 0x45
#define EPS_MM_Detach_accept 0x46

#define EPS_MM_Tracking_area_update_request 0x48
#define EPS_MM_Tracking_area_update_accept 0x49
#define EPS_MM_Tracking_area_update_complete 0x4a
#define EPS_MM_Tracking_area_update_reject 0x4b

#define EPS_MM_Extended_service_request 0x4c
#define EPS_MM_Service_reject 0x4e

#define EPS_MM_GUTI_reallocation_command 0x50
#define EPS_MM_GUTI_reallocation_complete 0x51
#define EPS_MM_Authentication_request 0x52
#define EPS_MM_Authentication_response 0x53
#define EPS_MM_Authentication_reject 0x54
#define EPS_MM_Authentication_failure 0x5c
#define EPS_MM_Identity_request 0x55
#define EPS_MM_Identity_response 0x56
#define EPS_MM_Security_mode_command 0x5d
#define EPS_MM_Security_mode_complete 0x5e
#define EPS_MM_Security_mode_reject 0x5f

#define EPS_MM_EMM_status 0x60
#define EPS_MM_EMM_information 0x61
#define EPS_MM_Downlink_NAS_transport 0x62
#define EPS_MM_Uplink_NAS_transport 0x63
#define EPS_MM_CS_Service_notification 0x64
#define EPS_MM_Downlink_generic_NAS_transport 0x68
#define EPS_MM_Uplink_generic_NAS_transport 0x69



//EPS session management messages
#define EPS_SM_Activate_default_EPS_bearer_context_request 0xc1
#define EPS_SM_Activate_default_EPS_bearer_context_accept 0xc2
#define EPS_SM_Activate_default_EPS_bearer_context_reject 0xc3

#define EPS_SM_Activate_dedicated_EPS_bearer_context_request 0xc5
#define EPS_SM_Activate_dedicated_EPS_bearer_context_accept 0xc6
#define EPS_SM_Activate_dedicated_EPS_bearer_context_reject 0xc7

#define EPS_SM_Modify_EPS_bearer_context_request 0xc9
#define EPS_SM_Modify_EPS_bearer_context_accept 0xca
#define EPS_SM_Modify_EPS_bearer_context_reject 0xcb

#define EPS_SM_Deactivate_EPS_bearer_context_request 0xcd
#define EPS_SM_Deactivate_EPS_bearer_context_accept 0xce

#define EPS_SM_PDN_connectivity_request 0xd0
#define EPS_SM_PDN_connectivity_reject 0xd1

#define EPS_SM_PDN_disconnect_request 0xd2
#define EPS_SM_PDN_disconnect_reject 0xd3

#define EPS_SM_Bearer_resource_allocation_request 0xd4
#define EPS_SM_Bearer_resource_allocation_reject 0xd5

#define EPS_SM_Bearer_resource_modification_request 0xd6
#define EPS_SM_Bearer_resource_modification_reject 0xd7

#define EPS_SM_ESM_information_request 0xd9
#define EPS_SM_ESM_information_response 0xda

#define EPS_SM_Notification 0xdb

#define EPS_SM_ESM_status 0xe8


#endif /* PLUGINS_S1MME_INC_MMENASCONSTANTS_H_ */
