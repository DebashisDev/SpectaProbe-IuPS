/*
 * GTPMessage.h
 *
 *  Created on: Jun 9, 2016
 *      Author: soumen
 */

#ifndef INCLUDE_GTPMESSAGE_H_
#define INCLUDE_GTPMESSAGE_H_

#include <string>
#include <map>
#include "GTPGlobal.h"
#include "SpectaTypedef.h"

typedef std::map<uint32_t, std::string> intstrmap;
//typedef size_t (*pfn)(const BYTE packet, uint32_t offset, TPacket*);
//typedef std::map<uint32_t, pfn> inf_table;
typedef std::map<uint32_t, std::string> msgType;


class GTPMessage {

public:

	GTPMessage() { };
	~GTPMessage() { };

	/*
	 * init the cause table
	 */
	void init_cause_type();
	/*
	 * intialize the decoder function pointer map
	 * we are concerned about the following information element types
	 *
	 */
//	void init_ie_table();

	void	init_msg_type();
	char* get_ip_str(uint32_t inputStr);
	char* get_ip6_str(char* inputStr);
	uint8_t* decode_apn(uint8_t * m_data, uint16_t length);
	char* decode_msisdn(uint8_t *m_data);
//	void decode_msisdn(uint8_t *m_data, char* msisdn);
	char* decode_imei(uint8_t *m_data);
//	void decode_imei(uint8_t *m_data, char *imei);

	char* decode_e164_msisdn(uint8_t *m_data, int offset);
	char* bcd_to_str(const BYTE packet, uint32_t offset, uint32_t no_of_octet);
//	void bcd_to_str(const BYTE packet, uint32_t offset, uint32_t no_of_octet, char *imsi_str);
	intstrmap get_cause_type_map() { return gtp_cause_type; }
	msgType get_msg_type_map() { return gtpMsgType; }

	//map_response_ctl get_control_response_map() { return res_ctl_map; }
//	inf_table& get_information_decoder_table() { return ie_table; }
	/*
	 * generic call to get length of different header based on it's type
	 * No need to decode here
	 */
	size_t get_message_type_length(uint8_t);
	// information decoder methods
	size_t get_cause_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_imsi_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_teardown_indication_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_routing_area_msg_len(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_recovery_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_selection_mode_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_tied_ctl_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_tied_data1_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_tied_data2_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_end_user_addr_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_nsapi_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_gsn_addr_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_protocol_config_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_msisdn_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_private_data_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_ssgn_no_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_charging_gateway_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_charging_ID_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
	{
		return 4;
	}
	size_t get_trace_type_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
		{
			return 2;
		}
	size_t get_trace_ref_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
		{
			return 2;
		}
	size_t get_auth_tip_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
		{
			return 28;
		}
	size_t get_rab_context_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
		{
			return 9;
		}
	size_t get_rab_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_access_pt_name_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_qos_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_tft_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_charg_charc_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
		{
			return 2;
		}
	size_t get_reording_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_RANAP_cause_info(const BYTE packet, uint32_t offset, MPacket *msgObj)
	{
		return 1;
	}

	size_t get_RAT_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_ULI_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_timezone_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_IMEI_info(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_common_flag(const BYTE packet, uint32_t offset, MPacket *msgObj);
	size_t get_apn_restriction(const BYTE packet, uint32_t offset, MPacket *msgObj);

private:
	char* tbcd_to_int(uint8_t imsi, uint32_t);
	intstrmap gtp_cause_type;
//	inf_table ie_table;
	msgType gtpMsgType;
};


#endif /* INCLUDE_GTPMESSAGE_H_ */
