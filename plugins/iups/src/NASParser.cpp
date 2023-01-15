/*
 * NASParser.cpp
 *
 *  Created on: 16-Jul-2016
 *      Author: Deb
 */

#include "NASParser.h"

NASParser::NASParser() {
	cout << "Calling NASParser::NASParser() Constructor" << endl;
//	sm = new SCCPSessionManager();
//	msgObj = NULL;
}

NASParser::~NASParser() {
//	delete (sm);
}

void NASParser::parsePacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo){

	const char* identifier = "RANAP NAS";
	sctpMsgObj->iups_sessiontype = GMM_SESSION;


	//General message organization example
	//	Octet 1
	//		First (MSB) 4 bits - transaction identifier / Skip Indicator
	//		Next  (LSB) 4 bits - protocol discriminator
	//	Octet 2
	//		message type
	//  ...

	//Transaction Identifier first 4 bits (MSB)
	int transaction_skip_indicator = 0xf0 & packet[0];
	//Protocol Discriminator last 4 bits (LSB)
	int protocolDiscriminator  =  0x0f & packet[0];

	if (PCons::P_NAS && PCons::DEBUG) printf("         		: NAS-PDU Skip Indicator [%d]\n", transaction_skip_indicator);
	if (PCons::P_NAS && PCons::DEBUG) printf("         		: NAS-PDU Protocol Discriminator - %d [%s]\n", protocolDiscriminator,IUPSGlobal::PD_Val_String[protocolDiscriminator]);

	if(protocolDiscriminator == PD_GPRS_mobility_management_messages)
		process_GPRS_MM_Message(packet, sctpMsgObj->iups_packetLengthNAS, msgObj, sctpMsgObj, chunkNo);
	else if(protocolDiscriminator == PD_GPRS_session_management_messages)
		process_GPRS_SM_Message(packet, sctpMsgObj->iups_packetLengthNAS, msgObj, sctpMsgObj, chunkNo);
}


int NASParser::process_GPRS_MM_Message(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	int messageType = packet[1];

	if(messageType > MAX_GMM_ID_VALUE){
		if (PCons::P_NAS && PCons::DEBUG) printf("         		: Invalid GPRS MM Message Type - %d\n", messageType);
		return 0;
	}

	sctpMsgObj->iups_mmsm_id = messageType;
	MM_SM_Message_Id_Counter[messageType]++;
	strcpy( sctpMsgObj->iups_mmsm_desc, IUPSGlobal::MM_SM_Message_Id_Val_String[messageType]);

	if(PCons::P_SCCP && PCons::TRACE) printf("      NAS Parser      	: MM_SM_Id [%d] [%s]\n", sctpMsgObj->iups_mmsm_id,  sctpMsgObj->iups_mmsm_desc);

	switch(messageType){
		case MM_Attach_request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Attach_request;
			decode_MM_Attach_request(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Attach_accept:
			 sctpMsgObj->iups_gmmsessionintmd = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Attach_request;
			decode_MM_Attach_accept(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Attach_complete:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Attach_request;
			decode_MM_Attach_complete(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Attach_reject:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Attach_request;
			decode_MM_Attach_reject(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Detach_request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Detach_request;
			decode_MM_Detach_request(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Detach_accept:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Detach_request;
			decode_MM_Detach_accept(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Routing_area_update_request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Routing_area_update_request;
			decode_MM_Routing_area_update_request(packet,length,msgObj,sctpMsgObj, chunkNo);
			break;
		case MM_Routing_area_update_accept:
			 sctpMsgObj->iups_gmmsessionintmd = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Routing_area_update_request;
			decode_MM_Routing_area_update_accept(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Routing_area_update_complete:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Routing_area_update_request;
			decode_MM_Routing_area_update_complete(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Routing_area_update_reject:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Routing_area_update_request;
			decode_MM_Routing_area_update_reject(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Service_Request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Service_Request;
			break;
		case MM_Service_Accept:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Service_Request;
			break;
		case MM_Service_Reject:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Service_Request;
			break;
		case MM_P_TMSI_reallocation_command:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_P_TMSI_reallocation_command;
			break;
		case MM_P_TMSI_reallocation_complete:
			 sctpMsgObj->iups_session_mmsm_id = MM_P_TMSI_reallocation_command;
			break;
		case MM_Authentication_and_ciphering_req:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Authentication_and_ciphering_req;
			decode_MM_Authentication_and_ciphering_request(packet,length,msgObj);
			break;
		case MM_Authentication_and_ciphering_resp:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Authentication_and_ciphering_req;
			decode_MM_Authentication_and_ciphering_response(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Authentication_and_ciphering_rej:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Authentication_and_ciphering_req;
			decode_MM_Authentication_and_ciphering_reject(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Authentication_and_ciphering_failure:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Authentication_and_ciphering_req;
			decode_MM_Authentication_and_ciphering_failure(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_Identity_request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Identity_request;
			decode_MM_Identity_request(packet,length,msgObj);
			break;
		case MM_Identity_response:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = MM_Identity_request;
			decode_MM_Identity_response(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case MM_GMM_status:
			break;
		case MM_GMM_information:
			break;
    	default:
//    		if(P_NAS && PCons::WARNING) printf("         		: NAS-PDU Message Type - %d [%s] Skipping...\n", messageType,PCons::MM_SM_Message_Id_Val_String[messageType]);
    		break;
	}
	return 1;
}

int NASParser::process_GPRS_SM_Message(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	int messageType = packet[1];
	if(messageType > MAX_GMM_ID_VALUE){
		if (PCons::P_NAS && PCons::DEBUG) printf("         		: Invalid GPRS SM Message Type - %d\n", messageType);
		return 0;
	}

	 sctpMsgObj->iups_mmsm_id = messageType;
	MM_SM_Message_Id_Counter[messageType]++;
	strcpy( sctpMsgObj->iups_mmsm_desc, IUPSGlobal::MM_SM_Message_Id_Val_String[messageType]);

	if(PCons::P_SCCP && PCons::TRACE) printf("      NAS Parser      	: MM_SM_Id [%d] [%s]\n", sctpMsgObj->iups_mmsm_id,  sctpMsgObj->iups_mmsm_desc);

	switch(messageType){
		case SM_Activate_PDP_context_request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Activate_PDP_context_request;
			decode_SM_Activate_PDP_context_request(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
		case SM_Activate_PDP_context_accept:
			 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Activate_PDP_context_request;
			decode_SM_Activate_PDP_context_accept(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
	    case SM_Activate_PDP_context_reject:
	    	 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Activate_PDP_context_request;
	    	decode_SM_Activate_PDP_context_reject(packet,length,msgObj, sctpMsgObj, chunkNo);
	    	break;
	    case SM_Request_PDP_context_activation:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Request_PDP_context_activation;
			decode_SM_Request_PDP_context_activation(packet,length,msgObj, sctpMsgObj, chunkNo);
	    	break;
	    case SM_Request_PDP_context_activation_rej:
	    	 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Request_PDP_context_activation;
	    	decode_SM_Request_PDP_context_activation_reject(packet,length,msgObj, sctpMsgObj, chunkNo);
	    	break;
	    case SM_Deactivate_PDP_context_request:
			 sctpMsgObj->iups_gmmsessionstart = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Deactivate_PDP_context_request;
			decode_SM_Deactivate_PDP_context_request(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
	    case SM_Deactivate_PDP_context_accept:
	    	 sctpMsgObj->iups_gmmsessionend = true;
			 sctpMsgObj->iups_session_mmsm_id = SM_Deactivate_PDP_context_request;
	    	decode_SM_Deactivate_PDP_context_accept(packet,length,msgObj, sctpMsgObj, chunkNo);
			break;
	    case SM_Modify_PDP_context_request_Network_to_MS_direction:
	    	break;
	    case SM_Modify_PDP_context_accept_MS_to_network_direction:
	    	break;
	    case SM_Modify_PDP_context_request_MS_to_network_direction:
	    	break;
	    case SM_Modify_PDP_context_accept_Network_to_MS_direction:
	    	break;
	    case SM_Modify_PDP_context_reject:
	    	break;
	    case SM_Activate_secondary_PDP_context_request:
	    	break;
	    case SM_Activate_secondary_PDP_context_accept:
	    	break;
	    case SM_Activate_secondary_PDP_context_reject:
	    	break;
	    case SM_SM_Status:
	    	break;
	    case SM_Activate_MBMS_Context_Request:
	    	break;
	    case SM_Activate_MBMS_Context_Accept:
	    	break;
	    case SM_Activate_MBMS_Context_Reject:
	    	break;
	    case SM_Request_MBMS_Context_Activation:
	    	break;
	    case SM_Request_MBMS_Context_Activation_Reject:
	    	break;
	    case SM_Request_Secondary_PDP_Context_Activation:
	    	break;
	    case SM_Request_Secondary_PDP_Context_Activation_Reject:
	    	break;
	    case SM_Notification:
	    	break;
	    default:
	    	if (PCons::P_NAS && PCons::DEBUG) printf("         		: NAS-PDU Message Type - %d [%s] Skipping...\n", messageType,IUPSGlobal::MM_SM_Message_Id_Val_String[messageType]);
	    	break;
	}
	return 1;
}

//
// IMPORTANT
// As a rule set offset to the last processed packet pointer
// So the next process should increase the offset to extract packets
//

//Attach request
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Attach request message identity		M			V			1
//				MS network capability				M			LV			3-9
//				Attach type							M			V			1/2
//				GPRS ciphering key seq number		M			V			1/2
//				DRX parameter						M			V			2
//				Mobile identity						M			LV			6-9
//				Old routing area identification		M			V			6
//				MS Radio Access capability			M			LV			6-51
//				...
// **************************************************************************
void	NASParser::decode_MM_Attach_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//080102F56059410805F4EA60245404F422A0B62A111653432B25918804CC960C43EE6630621E19E7D7DD
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 01 : Attach Request (0x01)
	// 02F560 MS Network Capability
	// 59 01011001
	//    0101.... - GPRS ciphering key sequence number (5)
	//    ....0... -
	//    .....001 - Attach type  001 (GPRS attach)
	// 4108 DRX parameter
	// 05F4EA602454 Mobile identity 05-Length f4 11110100		TMSI/P-TMSI: 0xea602454
	//											 1111....	Unused
	//											 .... 0... = Odd/even indication: 0 -Even number of identity digits
	//											 .... .100 = Mobile Identity Type: TMSI/P-TMSI/M-TMSI (4)
	// 04F422A0B62A	- Old routing area identification - RAI: 404-22-41142-42
	// ...
	//PDU-Example 2
	//080103E5E034710A0008494220411397065504F429FFFEFF1C1B13432B37159EF98800D002376318CC40068011A312C6620034008817055804E060C0405D0100

	int offset = 1;			//Pointing to 2nd byte which is id of this operation

	int len = packet[++offset];
	if (PCons::P_NAS && PCons::DEBUG) printf("     			: MS Network Capability len - %d\n", len);

	offset+=len;			//Skip MS network capability

	//Attach type
	unsigned char c = packet[++offset];
	if (PCons::P_NAS && PCons::DEBUG) printf("     			: Attach Type - %0x\n", c);
	int attach_type = c & 0x07;		//And with 0000 0111 to get attach type
	 sctpMsgObj->iups_AttachDetachId = attach_type;
	strcpy( sctpMsgObj->iups_AttachDetachDesc, IUPSGlobal::Attach_Type_Val_String[attach_type]);
	if (PCons::P_NAS && PCons::DEBUG) printf("     			: Attach Type - %d [%s]\n", sctpMsgObj->iups_AttachDetachId,  sctpMsgObj->iups_AttachDetachDesc);

	offset+=2;				//Skip DRX parameter

	//Mobile identity
	//data_pointer++
	offset = extractMobileIdentity(offset,packet,true,msgObj,sctpMsgObj, chunkNo);

	//Extract Old Routing Area Identification
	offset = extractRAI(offset,packet, true, msgObj, sctpMsgObj, chunkNo);
//	if (PCons::P_NAS && PCons::DEBUG) printf("     			: Old Routing area identification - %s\n", msgObj->mmsmdata_val[data_pointer]);

	//MS Radio Access capability
	//len = packet[++offset];
	if (PCons::P_NAS && PCons::DEBUG) printf("     			: MS Radio Access capability len - %d\n", len);
	//offset+=len;
	//exit(0);
}

//Attach accept
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Attach accept message identity		M			V			1
//				Attach result						M			V			1/2
//				Force to standby					M			V			1/2
//				Periodic RA update timer			M			V			1
//				Radio priority for SMS				M			V			1/2
//				Radio priority for TOM8				M			V			1/2
//				Routing area identification			M			V			6
//		19		P-TMSI signature					O			TV			4
//		17		Negotiated READY timer value		O			TV			2
//		18		Allocated P-TMSI					O			TLV			7
//		23		MS identity							O			TLV			7-10
//		25		GMM cause							O			TV			2
//		2A		T3302 value
//		8C		Cell Notification
//		4A		Equivalent PLMNs
//		B-		Network feature support
//		34		Emergency Number List
//		A-		Requested MS Information
//		37		T3319 value
//		38		T3323 value
//		39		T3312 extended value
//		66		Additional network feature support
//		6A		T3324 value
// **************************************************************************
void	NASParser::decode_MM_Attach_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//0802015E0104F422A0900419CC870B1805F4D4DF4483B0
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 02 : Attach accept (0x02)
	// 01 0000 0 001 - Attach result (GPRS only attach)
	// 5E Periodic RA update timer
	// 01 Radio priority for SMS + Radio priority for TOM8
	// 04F422A09004	- Routing area identification - RAI: 404-22-41104-04
	// ...

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int len = 0;

	//Attach result
	unsigned char c = packet[++offset];
	int attach_type = c & 0x07;		//And with 0000 0111 to get attach result
	//data_pointer++;
	 sctpMsgObj->iups_EndCauseId = attach_type;
	strcpy( sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::Attach_Result_Val_String[attach_type]);
	//if (PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n", sctpMsgObj->mmsmdata_key[data_pointer],  sctpMsgObj->mmsmdata_val[data_pointer]);

	++offset;		//Skip Periodic RA update timer
	++offset;		//Skip Radio priority for SMS + Radio priority for TOM8

	//Extract Routing Area Identification
	offset = extractRAI(offset,packet,false,msgObj, sctpMsgObj, chunkNo);
	//if (PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n", sctpMsgObj->mmsmdata_key[data_pointer],  sctpMsgObj->mmsmdata_val[data_pointer]);

	//extractOptionalParams(offset,length,packet);
	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
		if (PCons::P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);

		switch(op_c){
			case 0x19:				//P-TMSI signature
				op_len = 3; 			//total 4 including Tag
				//offset = extractPacket(offset,op_len,packet,"Old P-TMSI signature");
				offset+=op_len;
				//if (PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
				break;
			case 0x17:				//READY timer value
				offset+=2;
				break;
			case 0x18:				//P-TMSI
				offset = extractMobileIdentity(offset,packet,false,msgObj,sctpMsgObj,chunkNo);
				//if (PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);			//"Allocated P-TMSI"
				break;
			case 0x23:				//MS identity
				offset = extractMobileIdentity(offset,packet,true,msgObj,sctpMsgObj,chunkNo);
				break;
			case 0x25:				//GMM cause
				offset+=2;
				break;
			default:
				offset=length;
				break;
		}
	}
	//exit(0);
}

//Attach complete
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Attach complete message identity	M			V			1
//		27		Inter RAT handover information		O			TLV			3-250
//		2B		E-UTRAN inter RAT handover info		O			TLV			3-257
// **************************************************************************
void	NASParser::decode_MM_Attach_complete(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 0x : Attach Request (0x0x)
	// ...

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	unsigned char c;
	if(offset < length-1){
		c = packet[++offset];					//Next Optional params
		if (PCons::P_NAS && PCons::DEBUG) printf("     			: Next Optional param tag %0x\n",c);
	}
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc,"Attach Success");
}

//Attach reject
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Attach reject message identity		M			V			1
//				GMM cause							M			V			1
//				...
// **************************************************************************
void	NASParser::decode_MM_Attach_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 0x : Attach Request (0x0x)
	// ...

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int cause_code = packet[++offset];
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer], "GMM cause");
	//msgObj->mmsmdata_val[data_pointer], GMM_Cause_Codes_Val_String[cause_code]);
	//msgObj->mmsmdata_len[data_pointer] = 1;
	sctpMsgObj->iups_EndCauseId = cause_code;
	strcpy(sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::MM_Cause_Codes_Val_String[cause_code]);
	if (PCons::P_NAS && PCons::DEBUG) printf("     			: Attach reject GMM cause - %s [%d]\n", IUPSGlobal::MM_Cause_Codes_Val_String[cause_code], cause_code);

}

//Detach request
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Detach request message identity		M			V			1
//	Network to MS
//				Detach type							M			V			1/2
//				Force to standby					M			V			1/2
//		25		GMM cause							O			TV			2
// MS to network
//				Detach type							M			V			1/2
//				Spare half octet					M			V			1/2
//		18		P-TMSI								O			TLV			7
//		19		P-TMSI signature					O			TLV			5
// **************************************************************************
void	NASParser::decode_MM_Detach_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//0805091805f4e00f4ce21903c9443c
	// 08 0000 1000
	//    0000 .... - Skip indicator No indication of selected PLMN (0)
	//    .... 1000 - GPRS Mobility Management Message Type
	// 05 DTAP GPRS Mobility Management Message Type: Detach Request (0x05)
	// MS to Network
	// 09 00001001	Detach type
	//    0000....	Spare
	//    ....1...  Power Off
	//    .....001  Detach Type
	//080502

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	char c = packet[++offset];
	//printf("%d %d\n",c,msgObj->flow_dir_rnc_sgsn);
	 sctpMsgObj->iups_AttachDetachId = c & 0x07;
	if(msgObj->dirUserNetwork){
		int pw_off = (c >> 3 & 0x01);

		sprintf( sctpMsgObj->iups_AttachDetachDesc, "%s%s", IUPSGlobal::Detach_Type_MS_NW_Val_String[ sctpMsgObj->iups_AttachDetachId],
										  IUPSGlobal::Detach_Power_Off_Type_MS_NW_Val_String[pw_off]);

		strcpy( sctpMsgObj->iups_AttachDetachDir, "MS initiated");
	}else{
		//sprintf(msgObj->AttachDetachDesc,"%s (NW->MS)",Detach_Type_MS_NW_Val_String[msgObj->iups_AttachDetachId]);
		strcpy( sctpMsgObj->iups_AttachDetachDesc, IUPSGlobal::Detach_Type_NW_MS_Val_String[ sctpMsgObj->iups_AttachDetachId]);
		strcpy( sctpMsgObj->iups_AttachDetachDir, "Network initiated");
	}
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer], "Detach Type");
	//msgObj->mmsmdata_val[data_pointer], msgObj->AttachDetachDesc);
	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->AttachDetachDesc);
	//if(P_NAS && PCons::DEBUG) printf("     			: Detach Type - %s\n", msgObj->mmsmdata_val[data_pointer]);
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer], "Detach Dir");
	//msgObj->mmsmdata_val[data_pointer], msgObj->AttachDetachDir);
	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->AttachDetachDir);
	//if(P_NAS && PCons::DEBUG) printf("     			: Detach Dir - %s\n", msgObj->mmsmdata_val[data_pointer]);
	//if(strcmp(msgObj->sccp_slr, "0xc44d98")==1) exit(0);
}

//Detach accept
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Detach accept message identity		M			V			1
// **************************************************************************
void	NASParser::decode_MM_Detach_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc,"Detach accepted");
}

//Authentication and ciphering request
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Auth and ciphering req msg id		M			V			1
//				Ciphering algorithm					M			V			1/2
//				IMEISV request						M			V			1/2
//				...
// **************************************************************************
void	NASParser::decode_MM_Authentication_and_ciphering_request(const BYTE packet, unsigned int length, MPacket *msgObj)
{
	//PDU-Example 1
	//081210602103b0483f8acbfe1585b6c784b41897a181
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 12 Authentication and Ciphering Req (0x12)
	// 10 0001 0000
	//    0... .... = Spare bit(s): 0
	//    ......001 = IMEISV request: IMEISV requested (1)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	unsigned char c = packet[++offset];
	int type = c & 0x07;
//	if(P_NAS && PCons::TRACE) printf("     			: %s [%d]\n",PCons::IMEISV_Type_Val_String[type], type);
}


//Authentication and ciphering response
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Auth and ciphering response msg id	M			V			1
//				A&C reference number				M			V			1/2
//				Spare half octet					M			V			1/2
//		22		Authentication parameter Response 	O			TV			5
//		23		IMEISV								O			TLV			11
//		29		Authentication Resp param (ext)		O			TLV			3-14
// **************************************************************************
void	NASParser::decode_MM_Authentication_and_ciphering_response(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//081210602103b0483f8acbfe1585b6c784b41897a181
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 13 Authentication and Ciphering response (0x13)
	// 10 0001 0000
	//    0... .... = Spare bit(s): 0
	//    ......001 = IMEISV request: IMEISV requested (1)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation

	offset++;		//Skip A&C reference number and Spare half octet

	//extractOptionalParams(offset,length,packet);
	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
//		if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);

		switch(op_c){
			case 0x22:				//Authentication parameter Response
				offset+=4;			//Skip , in TV length includes the Tag
				break;
			case 0x23:				//MS identity
				offset = extractMobileIdentity(offset,packet,true,msgObj,sctpMsgObj,chunkNo);
				break;
			default:
				offset=length;
				break;
		}
	}
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc, "Request complete");
}


//Authentication and Ciphering Failure
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Auth and ciphering Failure msg id	M			V			1
//				GMM cause							M			V			1
//		30		Authentication Failure parameter	O			TLV			16
// **************************************************************************
void	NASParser::decode_MM_Authentication_and_ciphering_failure(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 0x : ... (0x0x)
	// ...

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int cause_code = packet[++offset];
	 sctpMsgObj->iups_EndCauseId = cause_code;
	strcpy( sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::MM_Cause_Codes_Val_String[cause_code]);
	if (PCons::P_NAS && PCons::DEBUG) printf("     			: Auth and ciphering failure GMM cause - %s [%d]\n", IUPSGlobal::MM_Cause_Codes_Val_String[cause_code], cause_code);
}



//Authentication and ciphering reject
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Auth and ciphering Reject msg id	M			V			1
// **************************************************************************
void	NASParser::decode_MM_Authentication_and_ciphering_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 0x : ...... (0x0x)
	// ...

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc, "Rejected");

}

//Routing area update request
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Routing area update request msg id	M			V			1
//				Update type							M			V			1/2
//				GPRS ciphering key sequence no		M			V			1/2
//				Old routing area identification		M			V			6
//				MS Radio Access capability			M			LV			6-51
//		19		Old P-TMSI signature				O			TV			4
//				...
//		9-		TMSI status							O			TV			1
//		18		P-TMSI								O			TLV			7
//				...
// **************************************************************************
void	NASParser::decode_MM_Routing_area_update_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//08080004F422A0B82C0D1733432B259188018F95992F0019BDC9471805F4D28BACCB3103F5E10032020000
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 08 : Routing area update request (0x08)
	// 00 : 00000000
	//		0000.... GPRS ciphering key sequence no (0)
	//	    ....0... No follow-on request pending
	//			.000 Update type value - RA updating
	// 04F422A0B82C - Old routing area identification (404-22-A0B8-2C) - 404-22-41144-44
	// 0D1733432B259188018F95992F00 - MS Radio Access capability of length 13 bytes
	// 19BDC947 - Old P-TMSI signature
	// ...
	// 1805F4D28BACCB - P-TMSI
	// ...

	//PDU-Example 2
	//08081804F4222762011918B3432B2596620060809AC2C662006080BAC8C66200608000196B0BDA2708021805F4CCE9B3243102F5E032022000
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 08 : Routing area update request (0x08)
	// 18 : 00011000
	//		0001.... GPRS ciphering key sequence no (1)
	//	    ....1... Follow-on request pending
	//			.000 Update type value - RA updating

	int offset = 1;			//Pointing to 2nd byte which is id of this operation

	unsigned char c = packet[++offset];
//	if(P_NAS && PCons::TRACE) printf("     			: update_type %d\n",c);

	int update_type = c & 0x07;		//And with 0000 0111 to get update type
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer],"Update Type");
	//msgObj->mmsmdata_val[data_pointer],RA_Update_Type_Val_String[update_type]);
	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->mmsmdata_val[data_pointer]);
	//msgObj->RAUpdateId = update_type;
	//msgObj->RAUpdateDesc,RA_Update_Type_Val_String[update_type]);

	//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);

	offset = extractRAI(offset,packet,true,msgObj,sctpMsgObj,chunkNo);
	//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);

	int len = packet[++offset];
//	if(P_NAS && PCons::DEBUG) printf("     			: MS Radio Access capability len - %d\n",len);
	offset+=len;

	//extractOptionalParams(offset,length,packet);
	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
//		if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);

		switch(op_c){
			case 0x19:				//P-TMSI signature
				op_len = 3; 			//total 4 including Tag
				//offset = extractPacket(offset,op_len,packet,"Old P-TMSI signature");
				offset+=op_len;
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
				break;
			case 0x18:				//P-TMSI
				offset = extractMobileIdentity(offset,packet,false,msgObj,sctpMsgObj,chunkNo);
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);			//"Allocated P-TMSI"
				break;
			case 0x90:				//TMSI status
				offset+=1;
				break;
			default:
				offset=length;
				break;
		}
	}

}

//Routing area update accept
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Routing area update accept msg id	M			V			1
//				Force to standby					M			V			1/2
//				Update result						M			V			1/2
//				Periodic RA update timer			M			V			1
//				Routing area identification			M			V			6
//		19		P-TMSI signature					O			TV			4
//		18		Allocated P-TMSI					O			TLV			7
//		23		MS identity 						O			TLV			7-10
//		26		List of Receive N‑PDU Numbers		O			TLV			4-19
//		17		Negotiated READY timer value		O			TV			2
//		25		GMM cause							O			TV			2
//				...
//		32		PDP context status					O			TLV			4
//				...
//		B-		Network feature support				0			TV			1
// **************************************************************************
void	NASParser::decode_MM_Routing_area_update_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//0809005E04F422A0B5291934FC9E1805F4E9F8B7C132020000B0
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 09 : Routing area update accept (0x09)
	// 00 : 00000000
	//		0000.... GPRS ciphering key sequence no (0)
	//	    ....0... No follow-on request pending
	//			.000 Update type value - RA updating
	// 5E : Force to standby + Update result
	// 04F422A0B529 - Routing area identification (404-22-A0B5-29) - 404-22-41141-41
	// 0D1733432B259188018F95992F00 - MS Radio Access capability of length 13 bytes
	// 1934FC9E - P-TMSI signature
	// 1805F4E9F8B7C1
	// 32020000 - PDP context status length 2 value 00 00
	// B0	- Network feature support
	// ...

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	unsigned char c = packet[++offset];
//	if(P_NAS && PCons::TRACE) printf("     			: Update result %d\n",c);

	++offset;		//Periodic RA update timer

	offset = extractRAI(offset,packet,false,msgObj, sctpMsgObj,chunkNo);
	//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);

	//extractOptionalParams(offset,length,packet);
	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
//		if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);

		switch(op_c){
			case 0x19:				//P-TMSI signature
				op_len = 3; 			//total 4 including Tag
				//offset = extractPacket(offset,op_len,packet,"Old P-TMSI signature");
				offset+=op_len;
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
				break;
			case 0x18:				//P-TMSI
				offset = extractMobileIdentity(offset,packet,false,msgObj,sctpMsgObj,chunkNo);
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);			//"Allocated P-TMSI"
				break;
			case 0x23:				//MS identity
				offset = extractMobileIdentity(offset,packet,true,msgObj,sctpMsgObj,chunkNo);
				break;
			case 0x25:				//GMM cause
				offset+=2;
				break;
			default:
				offset=length;
				break;
		}
	}
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc, "Update Accepted");
}

//Routing area update complete
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Routing area upd complete msg id	M			V			1
//		26		List of Receive N‑PDU Numbers		O			TLV			4-19
//		27		Inter RAT handover information		O			TLV			3-250
//		2B		E-UTRAN inter RAT handover info		O			TLV			3-257
// **************************************************************************
void	NASParser::decode_MM_Routing_area_update_complete(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 0a : Routing area update complete (0x0a)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	//int cause_code = packet[offset];
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer], "GMM cause");
	//msgObj->mmsmdata_val[data_pointer], GMM_Cause_Codes_Val_String[cause_code]);
	//msgObj->mmsmdata_len[data_pointer] = 1;
	//if(P_NAS && PCons::DEBUG) printf("     			: Routing area update reject GMM cause %s [%d]\n", msgObj->mmsmdata_val[data_pointer], cause_code);
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc, "Update Completed");
}

//Routing area update reject
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Routing area upd reject msg id		M			V			1
//				GMM cause							M			V			1
//				...
// **************************************************************************
void	NASParser::decode_MM_Routing_area_update_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 0b : Routing area update reject (0x0b)
	// 00 - GMM Cause

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int cause_code = packet[++offset];
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer], "GMM cause");
	//msgObj->mmsmdata_val[data_pointer], GMM_Cause_Codes_Val_String[cause_code]);
	//msgObj->mmsmdata_len[data_pointer] = 1;
	 sctpMsgObj->iups_EndCauseId = cause_code;
	strcpy( sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::MM_Cause_Codes_Val_String[cause_code]);
	//if(P_NAS && PCons::DEBUG) printf("     			: Routing area update reject GMM cause %s [%d]\n", msgObj->mmsmdata_val[data_pointer], cause_code);
}

//Identity request
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Identity Request message type		M			V			1
//				Identity type						M			V			1/2
//				Spare half octet					M			V			1/2
// **************************************************************************
void	NASParser::decode_MM_Identity_request(const BYTE packet, unsigned int length, MPacket *msgObj)
{
	//PDU-Example 1
	//081501
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 15 Identity Request (0x15)
	// 01 0000 0001
	//    0... .... = Spare bit(s): 0
	//    .000 .... = Force to standby: Force to standby not indicated (0)
	//    .... 0... = Spare bit(s): 0
	//    .... .001 = Type of identity: IMSI (1)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	unsigned char c = packet[++offset];
	int type = c & 0x01;
//	if(P_NAS && PCons::TRACE) printf("     			: Mobile identity type %d\n",type);
	//data_pointer++;
	//msgObj->mmsmdata_key[data_pointer], "Mobile Identity Type");
	//msgObj->mmsmdata_val[data_pointer], Mobile_Id_Type_Val_String[type]);
	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->mmsmdata_val[data_pointer]);
}


//Identity response
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Identity response message type		M			V			1
//				Mobile identity						M			LV			4-10
// **************************************************************************
void	NASParser::decode_MM_Identity_response(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//081608FAFFFFFFFFFFFF0F
	// 08 0000 - Skip indicator, 8 - GPRS Mobility Management Message Type
	// 16 Identity Response (0x16)
	// 08 Mobile Identity length

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	offset = extractMobileIdentity(offset,packet,true,msgObj,sctpMsgObj,chunkNo);
	//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);			//"Allocated P-TMSI"
	//exit(0);
}


/*
 * Activate PDP context request
 * **************************************************************************
		IEI		Information Element					Presence	Format		Length
				Protocol discriminator				M			V			1/2
				Transaction identifier				M			V			1/2-3/2
				Activate PDP context req msg id		M			V			1
				Requested NSAPI						M			V			1
				Requested LLC SAPI					M			V			1
				Requested QoS						M			LV			13-21
				Requested PDP address				M			LV			3-23
		28		Access point name					O			TLV			3-102
				...
* **************************************************************************
*/
void	NASParser::decode_SM_Activate_PDP_context_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//0A4105030E0000000000000000000000000000020121280908696E7465726E6574272680C0230601000006000080211001000010810600000000830600000000000D00000A00000500
	// 0A 0000 1010
	//    .... 1010 - Protocol discriminator (GPRS_session_management_messages) (0xa),
	//    0... .... = TI flag: allocated by sender
	//	  .000 .... = TIO: 0
	// 41 0100 0001   DTAP GPRS Session Management Message Type: Activate PDP Context Request (0x41)
	//    01.. .... = Sequence number: 1
	// 05 NSAPI: 0x05 (5)
	// 03 0000 0011
	//    0000 .... = Spare bit(s): 0
	//    .... 0011 = LLC SAPI: SAPI 3 (3)
	// 0E Quality Of Service - Requested QoS length-14 VAlue-0000000000000000000000000000
	// 020121 - Requested PDP address Lenght-2 Value-0121
	//   01 0000 0001
	//		0000 .... = Spare bit(s): 0
	//		.... 0001 = PDP type organization: IETF allocated address (1)
	//   31 PDP type number: IPv4 address (33)
	// 28 0908696E7465726E6574 Access Point Name Lenght-9 Value-8696E7465726E6574 (internet)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation

	++offset;						//Skip Requested NSAPI
	++offset;						//Skip Requested LLC SAPI

	offset = extractQoS(offset,packet,msgObj, sctpMsgObj,chunkNo);

//	int len = packet[++offset];		//Qos Length
//	offset+=len; 					//Skip Requested QoS

//	printf("Inside decode_SM_Activate_PDP_context_request\n");

	//len = packet[++offset];			//Requested PDP address
	offset = extractPDPAddress(offset, packet, true, msgObj, sctpMsgObj,chunkNo);
	//if(P_NAS && PCons::DEBUG) printf("     			: % = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
	//extractPacket(offset, len, packet, "Requested PDP address");
	//msgObj->PDPAddressRequested,msgObj->mmsmdata_val[data_pointer]);

	//extractOptionalParams(offset,length,packet);
	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
		//if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);
//		printf("     			: Optional param tag %0x\n",op_c);
		switch(op_c){
			case 0x28:				//Access point name
				offset = extractAPN(offset,packet,msgObj, sctpMsgObj,chunkNo);
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
				break;

			default:
				offset=length;
				break;
		}
	}
}

/*
 * Activate PDP context accept
 * **************************************************************************
		IEI		Information Element					Presence	Format		Length
				Protocol discriminator				M			V			1/2
				Transaction identifier				M			V			1/2-3/2
				Activate PDP context accept msg id	M			V			1
				Negotiated LLC SAPI					M			V			1
				Negotiated QoS						M			LV			13-21
				Radio priority						M			V			1/2
				Spare half octet					M			V			1/2
		2B		PDP address							O			TLV			4-24
				...
* **************************************************************************
*/
void	NASParser::decode_SM_Activate_PDP_context_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//8A42030E0B921F7396FEFE74F9FEFE004F00022B0601210A648CA8271880802110030100108106706EF9C18306706EF90500050101
	// 8A 1000 1010
	//    .... 1010 - Protocol discriminator (GPRS_session_management_messages) (0xa),
	//    1... .... = TI flag: allocated by receiver
	//	  .000 .... = TIO: 0
	// 42 0100 0010   DTAP GPRS Session Management Message Type: Activate PDP Context Accept (0x42)
	//    01.. .... = Sequence number: 1
	// 03 LLC Service Access Point Identifier - Negotiated LLC SAPI
	//    0000 .... = Spare bit(s): 0
	//    .... 0011 = LLC SAPI: SAPI 3 (3)
	// 0E0B921F7396FEFE74F9FEFE004F00 Quality Of Service - Negotiated QoS Length-14
	// 02 Radio Priority
	// 2B 06 01210A648CA8 Packet Data Protocol Address - PDP address, Length-6 Value-01210A648CA8
	//       01 0000 0001	0000 .... = Spare bit(s): 0, .... 0001 = PDP type organization: IETF allocated address (1)
	//		 21 PDP type number: IPv4 address (33)
	//		 0A648CA8 IPv4 address: 10.100.140.168 (10.100.140.168)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation

	++offset;						//Skip Negotiated LLC SAPI

//	int len = packet[++offset];		//Qos Length
//	offset+=len; 					//Skip Negotiated QoS
	offset = extractQoS(offset,packet,msgObj, sctpMsgObj,chunkNo);

	++offset;						//Skip Radio Priority

//	printf("Inside decode_SM_Activate_PDP_context_accept\n");


	//extractOptionalParams(offset,length,packet);
	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
//		if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);

		switch(op_c){
			case 0x2B:				//PDP address
				offset = extractPDPAddress(offset,packet,false,msgObj,sctpMsgObj,chunkNo);
				//printf("3-1\n");
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
				//printf("4\n");
				break;
			default:
				offset=length;
				break;
		}
	}
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc, "Request Accepted");
}


/*
 * Activate PDP context reject
 * **************************************************************************
		IEI		Information Element					Presence	Format		Length
				Protocol discriminator				M			V			1/2
				Transaction identifier				M			V			1/2-3/2
				Activate PDP context reject			M			V			1
				SM cause							M			V			1
		27		Protocol configuration options		O			TLV			3 - 253
		37		Back-off timer value				O			TLV			3
		6B		Re-attempt indicator				O			TLV			3
* **************************************************************************
*/
void	NASParser::decode_SM_Activate_PDP_context_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//8a4326
	// 8a 1000 1010
	//    1000 .... - Skip indicator
	//    .... 1010 - Protocol discriminator (GPRS_session_management_messages) (0xa),
	// 43 Activate PDP Context Reject
	// 26 SM Cause - Network Failure

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int cause_code = packet[++offset];
	 sctpMsgObj->iups_EndCauseId = cause_code;
	strcpy( sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::SM_Cause_Codes_Val_String[cause_code]);
}


/*
 * Request PDP context activation
 * **************************************************************************
		IEI		Information Element					Presence	Format		Length
				Protocol discriminator				M			V			1/2
				Transaction identifier				M			V			1/2-3/2
				Request PDP context act msg id		M			V			1
				Offered PDP address					M			LV			3-23
		28		Access point name					O			TLV			3-102
		27		Protocol configuration options		O			TLV			3-253
* **************************************************************************
*/
void	NASParser::decode_SM_Request_PDP_context_activation(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//
	// 0A 0000 1010
	//    .... 1010 - Protocol discriminator (GPRS_session_management_messages) (0xa),
	//    0... .... = TI flag: allocated by sender
	//	  .000 .... = TIO: 0
	// 41 0100 0001   DTAP GPRS Session Management Message Type: Activate PDP Context Request (0x41)
	//    01.. .... = Sequence number: 1
	// 020121 - Requested PDP address Lenght-2 Value-0121
	//   01 0000 0001
	//		0000 .... = Spare bit(s): 0
	//		.... 0001 = PDP type organization: IETF allocated address (1)
	//   31 PDP type number: IPv4 address (33)
	// 28 0908696E7465726E6574 Access Point Name Lenght-9 Value-8696E7465726E6574 (internet)

	int offset = 1;			//Pointing to 2nd byte which is id of this operation

	offset = extractPDPAddress(offset, packet, true, msgObj, sctpMsgObj,chunkNo);
	//if(P_NAS && PCons::DEBUG) printf("     			: % = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);

	unsigned char op_c;
	int op_len = 0;
	while(offset < length-1){			//Optional params
		op_c = packet[++offset];
//		if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);

		switch(op_c){
			case 0x28:				//Access point name
				offset = extractAPN(offset,packet,msgObj, sctpMsgObj,chunkNo);
				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
				break;
			default:
				offset=length;
				break;
		}
	}
}

/*
 * Request PDP context activation reject
 * **************************************************************************
		IEI		Information Element					Presence	Format		Length
				Protocol discriminator				M			V			1/2
				Transaction identifier				M			V			1/2-3/2
				Request PDP context act rej msg id	M			V			1
				SM cause							M			V			1
		27		Protocol configuration options		O			TLV			3-253
* **************************************************************************
*/
void	NASParser::decode_SM_Request_PDP_context_activation_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//8a4326
	// 8a 1000 1010
	//    1000 .... - Skip indicator
	//    .... 1010 - Protocol discriminator (GPRS_session_management_messages) (0xa),
	// 43 Activate PDP Context Reject
	// 26 SM Cause - Network Failure

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int cause_code = packet[++offset];
	 sctpMsgObj->iups_EndCauseId = cause_code;
	strcpy( sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::SM_Cause_Codes_Val_String[cause_code]);
}

/*
 * Deactivate PDP context request
 * **************************************************************************
		IEI		Information Element					Presence	Format		Length
				Protocol discriminator				M			V			1/2
				Transaction identifier				M			V			1/2-3/2
				Deactivate PDP context req msg id	M			V			1
				SM cause							M			V			1
		9-		Tear down indicator					O			TV			1
		27		Protocol configuration options		O			TLV			3-253
				...
* **************************************************************************
*/
void	NASParser::decode_SM_Deactivate_PDP_context_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1
	//8a4326
	// 8a 1000 1010
	//    1000 .... - Skip indicator
	//    .... 1010 - Protocol discriminator (GPRS_session_management_messages) (0xa),
	// 43 Activate PDP Context Reject
	// 26 SM Cause - Network Failure

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	int cause_code = packet[++offset];
	 sctpMsgObj->iups_EndCauseId = cause_code;
	strcpy( sctpMsgObj->iups_EndCauseDesc, IUPSGlobal::SM_Cause_Codes_Val_String[cause_code]);
}

//Deactivate PDP context accept
// **************************************************************************
//		IEI		Information Element					Presence	Format		Length
//				Protocol discriminator				M			V			1/2
//				Skip indicator						M			V			1/2
//				Deactivate PDP cntx accept msg id	M			V			1
//		27		Protocol configuration options		O			TLV			3-253
//				...
// **************************************************************************
void	NASParser::decode_SM_Deactivate_PDP_context_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//PDU-Example 1

	int offset = 1;			//Pointing to 2nd byte which is id of this operation
	 sctpMsgObj->iups_EndCauseId = 0;
	strcpy( sctpMsgObj->iups_EndCauseDesc, "Detach accepted");
}

//Not used, ignore
//void NASParser::extractOptionalParams(int offset, int length, const BYTE packet, MPacket *msgObj)
//{
//	unsigned char op_c;
//	int op_len = 0;
//	while(offset < length-1){			//Optional params
//		op_c = packet[++offset];
////		if(P_NAS && PCons::DEBUG) printf("     			: Optional param tag %0x\n",op_c);
//
//		switch(op_c){
//			case 0x19:				//P-TMSI signature
//				op_len = 3; 			//total 4 including Tag
//				//offset = extractPacket(offset,op_len,packet,"Old P-TMSI signature");
//				offset+=op_len;
//				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
//				break;
//			case 0x17:				//READY timer value
//				offset+=2;
//				break;
//			case 0x18:				//P-TMSI
//				offset = extractMobileIdentity(offset, packet, false,msgObj);
//				//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);			//"Allocated P-TMSI"
//				break;
//			case 0x22:				//Authentication parameter Response
//				offset+=4;			//Skip , in TV length includes the Tag
//				break;
//			case 0x23:				//MS identity
//				offset = extractMobileIdentity(offset,packet,true,msgObj);
//				break;
//			case 0x27:				//DRX parameter
//				offset+=3;
//				break;
//			case 0x28:				//Access point name
//				offset = extractAPN(offset,packet,msgObj);
//				break;
//			case 0x90:				//TMSI status
//				offset+=1;
//				break;
//			case 0x25:				//GMM cause
//				offset+=2;
//				break;
//			default:
//				offset=length;
//				break;
//		}
//	}
//
//}

/*int NASParser::extractTLVPacket(int offset, const BYTE packet, const char *key)
{
	int length = packet[++offset];
	if(P_NAS && PCons::DEBUG) printf("     			: %s len - %d\n",key, length);
	return extractPacket(offset, length, packet, key);
}*/

/*int NASParser::extractPacket(int offset, int length, const BYTE packet, const char *key)
{
	//msgObj->mmsmdata_key[data_pointer],key);
	char data[3];
	for(int i=0; i<length; i++){
		sprintf(data,"%02x",packet[++offset]);
		strcat(msgObj->mmsmdata_val[data_pointer],data);
	}
	msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->mmsmdata_val[data_pointer]);
	//if(P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
	return offset;
}*/


int NASParser::extractPDPAddress(int offset, const BYTE packet, bool requested, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	int length = packet[++offset];
	if(PCons::P_NAS && PCons::DEBUG) printf("     			: PDP Address len - %d\n",length);

	++offset;		//Skip next byte

	int pdp_type = packet[++offset];
	char pdp_type_desc[20];
	if(pdp_type==33)
		strcpy(pdp_type_desc,"IPv4 address");
	else
		strcpy(pdp_type_desc,"Unknown");

	if(PCons::P_NAS && PCons::DEBUG) printf("     			: PDP Address type %s [%d]\n",pdp_type_desc, pdp_type);

	if(length > 2){
		int addr_length = length-2;
		char addr[addr_length];
		char data[6];
		strcpy(addr,"");
		for(int i=0; i<addr_length; i++){
			int a = packet[++offset];
			sprintf(data, "%d",a);
			//printf("%s\n",data);
			strcat(addr,data);
			if(i<addr_length-1)
				strcat(addr,".");
			//printf("%s\n",addr);
		}
		//printf("%s [%s]\n",addr,pdp_type_desc);
		if(requested){
			char pdpaddr[200];
			//sprintf(XDR::PDPAddressRequested,"%s [%s]", addr, pdp_type_desc);
			strcpy( sctpMsgObj->iups_PDPAddressRequested, addr);
			strcpy( sctpMsgObj->iups_PDPAddressRequested, "[");
			strcat( sctpMsgObj->iups_PDPAddressRequested, pdp_type_desc);
			strcat( sctpMsgObj->iups_PDPAddressRequested, "]");
//			msgObj->iups_PDPAddressRequested.append("[").append(pdp_type_desc).append("]");
			if(strlen(addr)>5){
				 sctpMsgObj->iups_PDPStaticAddressRequested = 1;
			}
			//else
			//	XDR::PDPStaticAddressRequested = false;
		}else{
			//sprintf(XDR::PDPAddressAllocated,"%s [%s]", addr, pdp_type_desc);
			strcpy( sctpMsgObj->iups_PDPAddressAllocated, addr);
			strcpy( sctpMsgObj->iups_PDPAddressRequested, "[");
			strcat( sctpMsgObj->iups_PDPAddressRequested, pdp_type_desc);
			strcat( sctpMsgObj->iups_PDPAddressRequested, "]");

//			msgObj->iups_PDPAddressAllocated.append("[").append(pdp_type_desc).append("]");
		}
	}

//	printf("PDPAddressRequested : %s| PDPAddressAllocated : %s\n", sctpMsgObj->iups_PDPAddressRequested, sctpMsgObj->iups_PDPAddressAllocated);

	return offset;
}


int NASParser::extractQoS(int offset, const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	int qos_len = packet[++offset]; //(uint16_t)*(packet + offset);

//	printf("QoS Length : %d\n", qos_len);

	// one more octet for retention

	uint16_t mbrupl = *(packet + offset + 6); // Maximum bit rate for uplink
	uint16_t mbrdnl = *(packet + offset + 7); // Maximum bit rate for dnlink

	if(qos_len > 8) {

		if(mbrupl >= 1 && mbrupl <= 63 )
		{
			// giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.
			sctpMsgObj->iups_pdp_Mbrupl = mbrupl;
		}
		else if(mbrupl >= 64 && mbrupl <= 127)
		{
			// giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.
			sctpMsgObj->iups_pdp_Mbrupl = 64 + (mbrupl - 64) * 8;
		}
		else if(mbrupl >= 128 && mbrupl <= 254)
		{
			// giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.
			sctpMsgObj->iups_pdp_Mbrupl = 576 + (mbrupl - 128) * 64;
		}
		else
		{
			// 0 kbps
			sctpMsgObj->iups_pdp_Mbrupl = 0;
		}

		if(mbrdnl >= 1 && mbrdnl <= 63 )
			sctpMsgObj->iups_pdp_Mbrdnl = mbrdnl;
		else if(mbrdnl >= 64 && mbrdnl <= 127)
			sctpMsgObj->iups_pdp_Mbrdnl = 64 + (mbrdnl - 64) * 8;
		else if(mbrdnl >= 128 && mbrdnl <= 254)
			sctpMsgObj->iups_pdp_Mbrdnl = 576 + (mbrdnl - 128) * 64;
		else
			sctpMsgObj->iups_pdp_Mbrdnl = 0;
	}

	if(qos_len >= 13) {
		uint16_t max_dl_ext = 	*(packet + offset + 13); // Ext Maximum bit rate for down link

        /* Octet 15 */
        if ((max_dl_ext > 0) && (max_dl_ext <= 74))
        	sctpMsgObj->iups_pdp_ExtMbrdnl = 8600 + max_dl_ext * 100;
        else if ((max_dl_ext > 74) && (max_dl_ext <= 186))
        	sctpMsgObj->iups_pdp_ExtMbrdnl = 16000 + (max_dl_ext - 74) * 1000;
        else if ((max_dl_ext > 186) && (max_dl_ext <= 250))
        	sctpMsgObj->iups_pdp_ExtMbrdnl = 128000 + (max_dl_ext - 186) * 2000;
	}

//	printf("[QOS] Uplink = %d kbps| Dnlink = %d kbps| Ext = %d kbps \n",
//			sctpMsgObj->iups_pdp_Mbrupl, sctpMsgObj->iups_pdp_Mbrdnl, sctpMsgObj->iups_pdp_ExtMbrdnl);

	offset += qos_len;
	return offset;
}

int NASParser::extractAPN(int offset, const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	char apn[100];
	int length = packet[++offset];
	int apn_offset = offset;
	if(PCons::P_NAS && PCons::DEBUG) printf("     			: APN total len - %d\n",length);
	int apn_length = packet[++apn_offset];
	if(PCons::P_NAS && PCons::DEBUG) printf("     			: APN content len - %d\n",apn_length);
	const u_char *data = packet+apn_offset;
	for(int i=0; i<apn_length; i++){
		char c = packet[++apn_offset];
		apn[i]=c;
	}
	//data[apn_length]='\0';
	apn[apn_length]='\0';
	strcpy(sctpMsgObj->iups_APN, apn);
	//strcpy(XDR::APN,data);
	//strcpy(XDR::mmsmdata_key[data_pointer],"APN");
	//strcpy(XDR::mmsmdata_val[data_pointer],XDR::APN);
	//XDR::mmsmdata_len[data_pointer] = strlen(XDR::mmsmdata_val[data_pointer]);

	if(PCons::P_NAS && PCons::DEBUG) printf("     			: APN - %s\n",sctpMsgObj->iups_APN);
	return offset+length;
}

int NASParser::extractRAI(int offset, const BYTE packet, bool old_rai, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{

	char data[3];
	char raihex[20];
	char plmnhex[10];
	char result[100];

	strcpy(raihex,"");
	for(int i=0; i<6; i++){
		sprintf(data,"%02x",packet[++offset]);
		strcat(raihex,data);
		if(i==2)
			strcpy(plmnhex,raihex);
	}
	char lachex[5];
	sprintf(lachex,"%c%c%c%c",raihex[6],raihex[7],raihex[8],raihex[9]);
	//printf("lachex %s\n",lachex);

	char rachex[3];
	sprintf(rachex,"%c%c",raihex[10],raihex[11]);
	//printf("rachex %s\n",rachex);

	char plmnint[10];
	//char *raw = raihex;
	//sprintf(plmnint,"%c%c%c-%c%c",raw[1],raw[0],raw[3],raw[5],raw[4]);
	//printf("plmnint %s\n",plmnint);

	sprintf(plmnint,"%c%c%c-%c%c",plmnhex[1],plmnhex[0],plmnhex[3],plmnhex[5],plmnhex[4]);
	//printf("plmnint %s\n",plmnint);

	int lacint = (int)strtol(lachex, NULL, 16);
	int racint = (int)strtol(rachex, NULL, 16);
	if(old_rai){
		result[0]= '\0';
		//strcpy(XDR::mmsmdata_key[data_pointer],"Old Routing area identification");
		sprintf(result,"%s%s%s",plmnhex, lachex, rachex);
		strcpy( sctpMsgObj->iups_RAIOldHex, result);
		result[0] = '\0';
		sprintf(result,"%s-%d-%d",plmnint, lacint, racint);
		strcpy( sctpMsgObj->iups_RAIOldDec, result);
	}else{
		result[0] = '\0';
		//strcpy(XDR::mmsmdata_key[data_pointer],"Routing area identification");
		sprintf(result,"%s%s%s",plmnhex, lachex, rachex);
		strcpy( sctpMsgObj->iups_RAINewHex, result);
		result[0] = '\0';
		sprintf(result,"%s-%d-%d",plmnint, lacint, racint);
		strcpy( sctpMsgObj->iups_RAINewDec, result);
	}
	return offset;
}

int NASParser::extractMobileIdentity(int offset, const BYTE packet, bool update_session, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	int length = packet[++offset];								//Mobile identity length
	if(PCons::P_NAS && PCons::DEBUG) printf("     			: Mobile identity length - %d\n",length);

	unsigned char c = packet[++offset];					//Mobile identity type
	int mobile_identity_digit_1 = (c>>4 & 0x0f);
	if(PCons::P_NAS && PCons::DEBUG) printf("     			: Mobile identity digit 1 - %x\n",mobile_identity_digit_1);
	int odd_even_indicator = (c & 0x08);
	char odd_even[50] = "";
	if(odd_even_indicator == 0)
		strcpy(odd_even,"Even number of identity digits");
	else
		strcpy(odd_even,"Odd number of identity digits");

	if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s \n",odd_even);

	int type = c & 0x07;
	if(PCons::P_NAS && PCons::TRACE) printf("     			: Mobile identity type - %d [%s]\n",type,IUPSGlobal::Mobile_Id_Type_Val_String[type]);

	//bool even_digits = false;
	//if((c & 0x08) == 0) 	//Even number of digits
	//	even_digits = true;


	if(type == 1){ 	//IMSI
		//offset = extractPacket(offset, length-1, packet "IMSI");
		offset = extractIMSI(offset, length-1, packet,mobile_identity_digit_1,msgObj, sctpMsgObj, chunkNo);
		//processIMSI(mobile_identity_digit_1);
		if(PCons::P_NAS && PCons::DEBUG) printf("     			: IMSI %s\n", sctpMsgObj->iups_IMSI);
		//if(update_session)
			//parser->update_session(PCons::COL_IMSI, XDR::imsi);
			//SCCPSessionManager::update_sccp_lookup(SCCPGlobal::COL_IMSI, msgObj->IMSI, msgObj);
//		exit(0);
	}else if(type == 2){ 	//IMEI
		offset = extractIMEI(offset, length-1, packet,mobile_identity_digit_1,msgObj, sctpMsgObj,chunkNo);
		//processIMEI(mobile_identity_digit_1);
		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: IMEI %s\n", XDR::imei);
		//if(update_session)
			//parser->update_session(PCons::COL_IMEI, XDR::imei);
		//SCCPSessionManager::update_sccp_lookup(SCCPGlobal::COL_IMEI, msgObj->IMEI, msgObj);
		//exit(0);
	}else if(type == 3){ 	//IMEISV
		offset = extractIMEI(offset, length-1, packet, mobile_identity_digit_1,msgObj, sctpMsgObj,chunkNo);
		//processIMEI(mobile_identity_digit_1);
		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: IMEISV %s\n", XDR::imei);
		//if(update_session)
//			parser->update_session(PCons::COL_IMEI, XDR::imei);
		//SCCPSessionManager::update_sccp_lookup(SCCPGlobal::COL_IMEI, msgObj->IMEI, msgObj);
	}else if(type == 4){ 	//TMSI/P-TMSI/M-TMSI
		offset = extractTMSI(offset, length-1, packet,msgObj, sctpMsgObj,chunkNo);
		//strcpy(XDR::tmsi, XDR::mmsmdata_val[data_pointer]);
		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: TMSI %s\n", XDR::tmsi);
		//if(update_session)
//			parser->update_session(PCons::COL_TMSI, XDR::tmsi);
//		SCCPSessionManager::update_sccp_lookup(SCCPGlobal::COL_TMSI, msgObj->TMSI, msgObj);


	}else if(type == 5){	//TMGI and optional MBMS Session Identity
		offset+=length;
	}else{
		offset+=length;
	}
	//if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",XDR::mmsmdata_key[data_pointer], XDR::mmsmdata_val[data_pointer]);

	return offset;
}

int NASParser::extractIMSI(int offset, int length, const BYTE packet, int digit_1, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo){
	//Apend the first digit and this reversed digit to get IMEI
	char c[3];
	char imsi[20];

	imsi[0] = '\0';
	int data_length = 1;
	sprintf(imsi,"%d",digit_1);

	for(int i=0; i<length; i++){
		sprintf(c,"%02x",packet[++offset]);
		//printf("%s\n",c);
		strcat(imsi, c);
		data_length+=2;
	}
	//printf("L : %d  data L %d\n",length, data_length);
	char *raw = imsi;
	//IMSI 15 in length, except first digit, reverse rest 14
	for(int i=1; i<data_length-1; i+=2){
		char t = raw[i];
		raw[i] = raw[i+1];
		raw[i+1] = t;
	}
	//Remove the last digit which is F
	raw[data_length] = '\0';
	strcpy(sctpMsgObj->iups_IMSI, imsi);
//	printf("IMSI : %s\n",msgObj->IMSI);
	//exit(0);
	return offset;
}


int NASParser::extractIMEI(int offset, int length, const BYTE packet, int digit_1, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo){
	//Append the first digit and this reversed digit to get IMEI
	char imei[20];
	imei[0] = '\0';

	int data_length = 0;
	if(digit_1>=0 && digit_1<=9){
		sprintf(imei,"%d",digit_1);
		data_length++;
	}
	char c[3];
	for(int i=0; i<length; i++){
		sprintf(c,"%02x",packet[++offset]);
		//printf("%s\n",c);
		strcat(imei, c);
		data_length+=2;
	}
	//printf("L : %d  data L %d\n",length, data_length);
	char c1, c2;
	char *raw = imei;
	//Reversed all but the first digit to get IMEI
	for(int i=1; i<data_length-1; i+=2){
		c1 = raw[i];
		c2 = raw[i+1];
		if(c2>=48 && c2<=57){
			raw[i] = c2;
		}
		if(c1>=48 && c1<=57){
			raw[i+1] = c1;
		}
	}
	raw[data_length-1] = '\0';
	strcpy(sctpMsgObj->iups_IMEI, imei);
}

int NASParser::extractTMSI(int offset, int length, const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	char tmsi[20];
	tmsi[0] = '\0';

	//strcpy(XDR::mmsmdata_key[data_pointer],key);
	char data[3];
	for(int i=0; i<length; i++){
		sprintf(data,"%02x",packet[++offset]);
		strcat(tmsi,data);
	}
	//XDR::mmsmdata_len[data_pointer] = strlen(XDR::mmsmdata_val[data_pointer]);
	//if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",XDR::mmsmdata_key[data_pointer], XDR::mmsmdata_val[data_pointer]);
	strcpy(sctpMsgObj->iups_TMSI, tmsi);
	return offset;
}

void NASParser::printPacketBytes(const BYTE packet, int size)
{
		for(int i=0;i<size;i++){
			if((i%16 == 0)) printf("\n	%04x ", i);
			printf("%02x ", packet[i]);
		}
		printf("\n\n");
}























//int NASParser::extractPDPAddress(int offset, const BYTE packet, bool requested)
//{
//	int length = packet[++offset];
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: PDP Address len - %d\n",length);
//
//	++offset;		//Skip next byte
//
//	int pdp_type = packet[++offset];
//	std::string pdp_type_desc;
//	if(pdp_type==33)
//		pdp_type_desc.assign("IPv4 address");
//	else
//		pdp_type_desc.assign("Unknown");
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: PDP Address type %s [%d]\n",pdp_type_desc, pdp_type);
//
//
//	if(length > 2){
//		int addr_length = length-2;
//		char addr[addr_length];
//		char data[6];
//		strcpy(addr,"");
//		for(int i=0; i<addr_length; i++){
//			int a = packet[++offset];
//			sprintf(data, "%d",a);
//			//printf("%s\n",data);
//			strcat(addr,data);
//			if(i<addr_length-1)
//				strcat(addr,".");
//			//printf("%s\n",addr); append(std::string((char *)sourceHex))
//		}
//		//printf("%s [%s]\n",addr,pdp_type_desc);
//		if(requested){
//			msgObj->PDPAddressRequested.assign(std::string((char *)addr))
//												 .append(pdp_type_desc);
////			sprintf(msgObj->PDPAddressRequested,"%s [%s]", addr, pdp_type_desc);
//			if(strlen(addr)>5){
//				msgObj->PDPStaticAddressRequested = 1;
//			}
//			//else
//			//	msgObj->PDPStaticAddressRequested = false;
//		}else{
//			msgObj->PDPAddressRequested.assign(std::string((char *)addr))
//															 .append(pdp_type_desc);
////			sprintf(msgObj->PDPAddressAllocated,"%s [%s]", addr, pdp_type_desc);
//		}
//	}
//	return offset;
//}
//
//int NASParser::extractAPN(int offset, const u_char *packet)
//{
//	int length = packet[++offset];
//	int apn_offset = offset;
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: APN total len - %d\n",length);
//	int apn_length = packet[++apn_offset];
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: APN content len - %d\n",apn_length);
//	const u_char *data = packet+apn_offset;
//	for(int i=0; i<apn_length; i++){
//		char c = packet[++apn_offset];
//		msgObj->APN[i]=c;
//	}
//	//data[apn_length]='\0';
//	msgObj->APN[apn_length]='\0';
//	//msgObj->APN,data);
//	//msgObj->mmsmdata_key[data_pointer],"APN");
//	//msgObj->mmsmdata_val[data_pointer],msgObj->APN);
//	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->mmsmdata_val[data_pointer]);
//	return offset+length;
//}
//
//int NASParser::extractRAI(int offset, const BYTE packet, bool old_rai)
//{
//
//	char data[3];
//	char raihex[20];
//	char plmnhex[20];
//	strcpy(raihex,"");
//	for(int i=0; i<6; i++){
//		sprintf(data,"%02x",packet[++offset]);
//		strcat(raihex,data);
//		if(i==2)
//			strcpy(plmnhex,raihex);
//	}
//	//printf("rai %s\n",raihex);
//	//printf("plmnhex %s\n",plmnhex);
//
//	//for(int i=0; i<6; i++){
//	//		printf("%c\n",raihex[i]);
//	//}
//	char lachex[5];
//	sprintf(lachex,"%c%c%c%c",raihex[6],raihex[7],raihex[8],raihex[9]);
//	//printf("lachex %s\n",lachex);
//
//	char rachex[3];
//	sprintf(rachex,"%c%c",raihex[10],raihex[11]);
//	//printf("rachex %s\n",rachex);
//
//	char plmnint[10];
//	//char *raw = raihex;
//	//sprintf(plmnint,"%c%c%c-%c%c",raw[1],raw[0],raw[3],raw[5],raw[4]);
//	//printf("plmnint %s\n",plmnint);
//
//	sprintf(plmnint,"%c%c%c-%c%c",plmnhex[1],plmnhex[0],plmnhex[3],plmnhex[5],plmnhex[4]);
//	//printf("plmnint %s\n",plmnint);
//
//	int lacint = (int)strtol(lachex, NULL, 16);
//	int racint = (int)strtol(rachex, NULL, 16);
//
//	if(old_rai){
//		//msgObj->mmsmdata_key[data_pointer],"Old Routing area identification");
//
//		msgObj->RAIOldHex.assign(std::string(plmnhex))
//								   .append(std::string(lachex))
//								   .append(std::string(rachex));
//
//		msgObj->RAIOldDec.append(std::string(plmnint))
//								   .append("-")
//								   .append(std::to_string(lacint))
//								   .append("-")
//								   .append(std::to_string(racint));
//
//
////		sprintf(msgObj->RAIOldHex,"%s%s%s",plmnhex, lachex, rachex);
////		sprintf(msgObj->RAIOldDec,"%s-%d-%d",plmnint, lacint, racint);
//	}else{
//		//msgObj->mmsmdata_key[data_pointer],"Routing area identification");
//
//		msgObj->RAINewHex.append(std::string(plmnhex))
//								   .append(std::string(lachex))
//								   .append(std::string(rachex));
//
//		msgObj->RAINewDec.append(std::string(plmnint))
//								   .append("-")
//								   .append(std::to_string(lacint))
//								   .append("-")
//								   .append(std::to_string(racint));
//
////		sprintf(msgObj->RAINewHex,"%s%s%s",plmnhex, lachex, rachex);
////		sprintf(msgObj->RAINewDec,"%s-%d-%d",plmnint, lacint, racint);
//	}
//	//sprintf(msgObj->mmsmdata_val[data_pointer],"%s%s%s",plmnhex,lachex,rachex);
//	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->mmsmdata_val[data_pointer]);
//	//if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
//	//printf("%s %s\n",plmnint);
//	//exit(0);
//	return offset;
//
//}
//
//int NASParser::extractMobileIdentity(int offset, const BYTE packet, bool update_session)
//{
//	int length = packet[++offset];								//Mobile identity length
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: Mobile identity length - %d\n",length);
//
//	unsigned char c = packet[++offset];					//Mobile identity type
//	int mobile_identity_digit_1 = (c>>4 & 0x0f);
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: Mobile identity digit 1 - %x\n",mobile_identity_digit_1);
//	int odd_even_indicator = (c & 0x08);
//	char odd_even[50] = "";
//	if(odd_even_indicator == 0)
//		strcpy(odd_even,"Even number of identity digits");
//	else
//		strcpy(odd_even,"Odd number of identity digits");
//
////	if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s \n",odd_even);
//
//	int type = c & 0x07;
////	if(PCons::P_NAS && PCons::TRACE) printf("     			: Mobile identity type - %d [%s]\n",type,PCons::Mobile_Id_Type_Val_String[type]);
//
//	//bool even_digits = false;
//	//if((c & 0x08) == 0) 	//Even number of digits
//	//	even_digits = true;
//
//	if(type == 1){ 	//IMSI
//		//offset = extractPacket(offset, length-1, packet "IMSI");
//		offset = extractIMSI(offset, length-1, packet, mobile_identity_digit_1);
//		//processIMSI(mobile_identity_digit_1);
//		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: IMSI %s\n", msgObj->imsi);
//		//if(update_session)
//			sm->update_sccp_lookup(SCCPGlobal::COL_IMSI, msgObj->imsi, msgObj);
//
//
//	}else if(type == 2){ 	//IMEI
//		offset = extractIMEI(offset, length-1, packet,mobile_identity_digit_1);
//		//processIMEI(mobile_identity_digit_1);
//		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: IMEI %s\n", msgObj->imei);
//		//if(update_session)
//			sm->update_sccp_lookup(SCCPGlobal::COL_IMEI, msgObj->imei, msgObj);
//
//		//exit(0);
//	}else if(type == 3){ 	//IMEISV
//		offset = extractIMEI(offset, length-1, packet, mobile_identity_digit_1);
//		//processIMEI(mobile_identity_digit_1);
//		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: IMEISV %s\n", msgObj->imei);
//		//if(update_session)
//			sm->update_sccp_lookup(SCCPGlobal::COL_IMEI, msgObj->imei, msgObj);
//
//	}else if(type == 4){ 	//TMSI/P-TMSI/M-TMSI
//		offset = extractTMSI(offset, length-1, packet);
//		//msgObj->tmsi, msgObj->mmsmdata_val[data_pointer]);
//		//if(PCons::P_NAS && PCons::DEBUG) printf("     			: TMSI %s\n", msgObj->tmsi);
//		//if(update_session)
//			sm->update_sccp_lookup(SCCPGlobal::COL_TMSI, msgObj->tmsi, msgObj);
//
//	}else if(type == 5){	//TMGI and optional MBMS Session Identity
//		offset+=length;
//	}else{
//		offset+=length;
//	}
//
//	//if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
//	return offset;
//}
//
//int NASParser::extractIMSI(int offset, int length, const BYTE packet, int digit_1){
//	//Apend the first digit and this reversed digit to get IMEI
//	//printf("IMSI : %s\n",msgObj->imsi.c_str());
//	//exit(0);
//	char c[3];
//	int data_length = 1;
//	msgObj->imsi.append(std::to_string(digit_1));
//
//	for(int i=0; i<length; i++){
//		sprintf(c,"%02x",packet[++offset]);
//		//printf("%s\n",c);
//		msgObj->imsi.append(std::string(c));
//		data_length+=2;
//	}
//	//printf("L : %d  data L %d\n",length, data_length);
//	std::string raw = msgObj->imsi;
//	//IMSI 15 in length, except first digit, reverse rest 14
//	for(int i=1; i<data_length-1; i+=2){
//		char t = raw[i];
//		raw[i] = raw[i+1];
//		raw[i+1] = t;
//	}
//	//Remove the last digit which is F
//	raw[data_length] = '\0';
//	//printf("IMSI : %s\n",msgObj->imsi.c_str());
//	//exit(0);
//	return offset;
//}
//
//
//int NASParser::extractIMEI(int offset, int length, const BYTE packet, int digit_1){
//	//Apend the first digit and this reversed digit to get IMEI
//	int data_length = 0;
//	if(digit_1>=0 && digit_1<=9){
//		msgObj->imei.append(std::to_string(digit_1));
//		data_length++;
//	}
//	char c[3];
//	for(int i=0; i<length; i++){
//		sprintf(c,"%02x",packet[++offset]);
//		//printf("%s\n",c);
//		msgObj->imei.append(std::string(c));
//		data_length+=2;
//	}
//	//printf("L : %d  data L %d\n",length, data_length);
//	char c1, c2;
////	char *raw = msgObj->imei;
//	std::string raw = msgObj->imei;
//
//	//Reversed all but the first digit to get IMEI
//	for(int i=1; i<data_length-1; i+=2){
//		c1 = raw[i];
//		c2 = raw[i+1];
//		if(c2>=48 && c2<=57){
//			raw[i] = c2;
//		}
//		if(c1>=48 && c1<=57){
//			raw[i+1] = c1;
//		}
//	}
//	raw[data_length-1] = '\0';
//	//printf("IMEI : %s\n",msgObj->imei);
//}
//
//int NASParser::extractTMSI(int offset, int length, const u_char *packet)
//{
//	//msgObj->mmsmdata_key[data_pointer],key);
//	char data[3];
//	for(int i=0; i<length; i++){
//		sprintf(data,"%02x",packet[++offset]);
//		msgObj->tmsi.append(std::string(data));
//	}
//	//msgObj->mmsmdata_len[data_pointer] = strlen(msgObj->mmsmdata_val[data_pointer]);
//	//if(PCons::P_NAS && PCons::DEBUG) printf("     			: %s = %s\n",msgObj->mmsmdata_key[data_pointer], msgObj->mmsmdata_val[data_pointer]);
//	return offset;
//}
