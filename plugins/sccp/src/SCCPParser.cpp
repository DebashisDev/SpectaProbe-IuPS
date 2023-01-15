/*
 * SCCPParser.cpp
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#include "SCCPParser.h"

SCCPParser::SCCPParser() {
	ranapParser = new RANAPParser();
//	SGSN_PC[0] = 9665;
//	NO_OF_SGSN = 1;
}

SCCPParser::~SCCPParser() {
	delete (ranapParser);

}

void SCCPParser::processPacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo, unsigned int length)
{
	//Before start processing new packet, reset the XDR values
	//V.V Important !!!
	sctpMsgObj->sccp_reset();
	sctpMsgObj->iups_reset();

	struct sccp *psccp = (struct sccp*)packet;
	//First byte is message type
	int sccp_msg_type = psccp->msg_type;

	sctpMsgObj->sccp_message_type = sccp_msg_type;
	strcpy(sctpMsgObj->sccp_message_desc, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);

	//Determine flow direction
	msgObj->dirUserNetwork = false;
	for(int i=0; i< IPGlobal::TOTAL_SGSN_PC;i++){
		if(sctpMsgObj->sctp_dpc == IPGlobal::SGSN_PC[i]){
			msgObj->dirUserNetwork = true;
			break;
		}
	}
	switch(sccp_msg_type) {
		case SCCP_CR:
		{
			struct sccp_cr *ptrcr = (struct sccp_cr*)packet;
			sprintf(sctpMsgObj->sccp_slr, "%02x%02x%02x", ptrcr->slr_B_3, ptrcr->slr_B_2, ptrcr->slr_B_1);

			if(PCons::P_SCCP && PCons::TRACE) printf("     SCCP Message Type	: %d [%s]\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Source Local Ref 0x%02x%02x%02x\n", ptrcr->slr_B_3, ptrcr->slr_B_2, ptrcr->slr_B_1);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Protocol_class %d\n",ptrcr->protocol_class);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Session id : %s\n",sctpMsgObj->sccp_session_id);

			int offset=5;	//First 5 bytes are message type, source local ref & protocol class
			//Next byte is pointer to first mandatory variable length parameter which is called party address
			offset += (int)ptrcr->ptr_called_party;
			//next byte is the length of called party
			unsigned int clpd_length = packet[offset];
//			if(P_SCCP && SCCPGlobal::DEBUG) printf("			: SCCP Called Party Len	: %d\n", clpd_length);
			struct sccp_calledparty *ptr_called_party = (struct sccp_calledparty*)(packet+offset+1);
			//if(P_SCCP && SCTPGlobal::DEBUG) printf("			: Called Party Address 	 %02x %04x %d\n", ptr_called_party->address_indicator, ptr_called_party->PC, ptr_called_party->ssn);
			if(PCons::P_SCCP && PCons::DEBUG)
				printf("			: Called Party		: %d,%d,%d,%d,%d, PC [%d], SSN [%d]\n",
						ptr_called_party->national_use,
						ptr_called_party->route_ssn,
						ptr_called_party->global_title,
						ptr_called_party->is_ssn_present,
						ptr_called_party->is_pointcode_present,
						ptr_called_party->PC,
						ptr_called_party->ssn);


			int ssn = (int) ptr_called_party->ssn;

			if(PCons::P_SCCP && PCons::TRACE) printf("			: SCCP SSN %d\n", ssn);

			offset=5;	//reset offset
			//Now to get optional data
			offset += (int)ptrcr->ptr_to_opt_param;
			//next byte is parameter type / credit and byte next is the length of optional parameter
			offset++;
			while(packet[offset] != 0){
				//Keep extracting the optional parameters
				int param_type = packet[offset];
				if(ssn == 142 && param_type == SCCP_DATA){
					//Next byte is length of RANAP packet
					offset ++;
					unsigned int ranap_data_length = packet[offset];
//					if(P_SCCP && SCCPGlobal::DEBUG) printf("     RANAP Data Length	: %d\n", ranap_data_length);
					//This data is RANAP packet
					offset ++;
					//u_char* bytes = (u_char*)malloc(ranap_data_length);
					//bytes(memcpy, packet + offset, ranap_data_length);
					const BYTE bytes = (packet + offset);
//					if(PCons::P_SCCP && PCons::DEBUG) printPacketBytes(identifier, P_SCCP_PACKETS, bytes,ranap_data_length);
					offset += ranap_data_length;
					sctpMsgObj->iups_packetLengthRANAP = ranap_data_length;
					ranapParser->parsePacket(bytes, msgObj, sctpMsgObj, chunkNo);
					*bytes = NULL;
				}else if(param_type == SCCP_CALLING_PARTY_ADDRESS){
					int clnp_length = packet[offset];
//					if(P_SCCP && SCCPGlobal::DEBUG) printf("			: SCCP Calling Party Len - %d\n", clnp_length);
					offset += 2;
					struct sccp_callingparty *ptr_calling_party = (struct sccp_callingparty*)(packet+offset);
					if(PCons::P_SCCP && PCons::TRACE)
					printf("			: Calling Party - %d,%d,%d,%d,%d, PC [%d], SSN [%d]\n",
								ptr_calling_party->national_use,
								ptr_calling_party->route_ssn,
								ptr_calling_party->global_title,
								ptr_calling_party->is_ssn_present,
								ptr_calling_party->is_pointcode_present,
								ptr_calling_party->PC,
								ptr_calling_party->ssn);

					offset += clnp_length;
				}else{
					//Just keep skipping
					printf("			Skipping SCCP Packet 		\n");
					offset ++;
					int data_length = packet[offset];
					offset += data_length;
				}
			}

			break;
		}

		case SCCP_CC:
		{
			struct sccp_cc *sptrcc = (struct sccp_cc*)packet;
			sprintf(sctpMsgObj->sccp_slr, "%02x%02x%02x", sptrcc->slr_B_3, sptrcc->slr_B_2, sptrcc->slr_B_1);
			sprintf(sctpMsgObj->sccp_dlr, "%02x%02x%02x", sptrcc->dlr_B_3, sptrcc->dlr_B_2, sptrcc->dlr_B_1);

			if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d [%s]\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);
//			if(PCons::P_SCCP && PCons::DEBUG) printPacketBytes(identifier,PCons::P_SCCP_PACKETS,packet,length);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Source Local Ref %02x%02x%02x\n", sptrcc->slr_B_3, sptrcc->slr_B_2, sptrcc->slr_B_1);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Dest Local Ref %02x%02x%02x\n", sptrcc->dlr_B_3, sptrcc->dlr_B_2, sptrcc->dlr_B_1);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Protocol_class %d\n",sptrcc->protocol_class);
//			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Pointer to Opt Param %u\n", sptrcc->ptr_to_opt_param);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Session id : %s\n",sctpMsgObj->sccp_session_id);

			break;
		}

		case SCCP_RLSD:
		{
			struct sccp_rlsd *sptr = (struct sccp_rlsd*)packet;
			sprintf(sctpMsgObj->sccp_slr, "%02x%02x%02x", sptr->slr_B_3, sptr->slr_B_2, sptr->slr_B_1);
			sprintf(sctpMsgObj->sccp_dlr, "%02x%02x%02x", sptr->dlr_B_3, sptr->dlr_B_2, sptr->dlr_B_1);

			if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d [%s]\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);
//			if(PCons::P_SCCP && PCons::DEBUG) printPacketBytes(identifier,PCons::P_SCCP_PACKETS,packet,length);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Source Local Ref %02x%02x%02x\n", sptr->slr_B_3, sptr->slr_B_2, sptr->slr_B_1);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Dest Local Ref %02x%02x%02x\n", sptr->dlr_B_3, sptr->dlr_B_2, sptr->dlr_B_1);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Release Cause %u\n", sptr->rel_cause);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Pointer to Opt Param %u\n", sptr->ptr_to_opt_param);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Session id : %s\n",sctpMsgObj->sccp_session_id);

			char rel_cause[100]="";
			sprintf(rel_cause, "SCCP Release Cause : %u [%s]", sptr->rel_cause, SCCPGlobal::SCCP_REL_CAUSE_Val_String[sptr->rel_cause]);
			sctpMsgObj->sccp_release_cause = (int)sptr->rel_cause;
			strcpy(sctpMsgObj->sccp_release_desc, SCCPGlobal::SCCP_REL_CAUSE_Val_String[sptr->rel_cause]);

			break;
		}
		case SCCP_RLC:
		{
			struct sccp_rlc *ptrrlc = (struct sccp_rlc*)packet;
			sprintf(sctpMsgObj->sccp_slr, "%02x%02x%02x", ptrrlc->slr_B_3, ptrrlc->slr_B_2, ptrrlc->slr_B_1);
			sprintf(sctpMsgObj->sccp_dlr, "%02x%02x%02x", ptrrlc->dlr_B_3, ptrrlc->dlr_B_2, ptrrlc->dlr_B_1);

			if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d [%s]\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);
//			if(PCons::P_SCCP && PCons::DEBUG) printPacketBytes(identifier,PCons::P_SCCP_PACKETS,packet,length);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Source Local Ref %02x%02x%02x\n", ptrrlc->slr_B_3, ptrrlc->slr_B_2, ptrrlc->slr_B_1);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Dest Local Ref %02x%02x%02x\n", ptrrlc->dlr_B_3, ptrrlc->dlr_B_2, ptrrlc->dlr_B_1);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Session id : %s\n",sctpMsgObj->sccp_session_id);

			break;
		}
		case SCCP_DT1:
		{
			struct sccp_dt1 *srptr = (struct sccp_dt1*)packet;
			sprintf(sctpMsgObj->sccp_dlr, "%02x%02x%02x", srptr->dlr_B_3, srptr->dlr_B_2, srptr->dlr_B_1);

			if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d [%s]\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);
			if(PCons::P_SCCP && PCons::TRACE) printf("			: Dest Local Ref %02x%02x%02x\n", srptr->dlr_B_3, srptr->dlr_B_2, srptr->dlr_B_1);

			//********** DEB
			//*********************** HOW DO WE KNOW THIS IS RANAP??
			//*****************  SHALL WE EXTRACT THE SESSION DATA FROM MAP??

			//read RANAP packets
			sctpMsgObj->iups_packetLengthRANAP = srptr->msg_length;
			const BYTE bytes = (srptr->payload);
			ranapParser->parsePacket(bytes, msgObj, sctpMsgObj, chunkNo);
			*bytes = NULL;

			break;
		}
		case SCCP_UDT:
		{
			if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d [%s]\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);

			struct sccp_udt *ptrudt = (struct sccp_udt*)packet;
			int protocol_class = ptrudt->protocol_class & 0x0f;

			if(PCons::P_SCCP && PCons::TRACE) printf("			: Protocol class %d\n",protocol_class);
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: First MP [%d] Secong MP [%d] Third MP [%d]\n",ptrudt->ptr_first_mp,ptrudt->ptr_second_mp,ptrudt->ptr_third_mp);


			int offset=2;	//First two bytes are message type & protocol class
			//1st Mandatory parameter is Called party address
			offset += (int)ptrudt->ptr_first_mp;
			//next byte is the length of called party
			unsigned int clpd_length = packet[offset];
			if(PCons::P_SCCP && PCons::DEBUG) printf("			: Called Party Len	: %d\n", clpd_length);
			offset++;
			struct sccp_calledparty *ptr_called_party = (struct sccp_calledparty*)(packet+offset);
			if(PCons::P_SCCP && PCons::DEBUG)
				printf("			: Called Party	: %d,%d,%d,%d,%d, PC [%d], SSN [%d]\n",
						ptr_called_party->national_use,
						ptr_called_party->route_ssn,
						ptr_called_party->global_title,
						ptr_called_party->is_ssn_present,
						ptr_called_party->is_pointcode_present,
						ptr_called_party->PC,
						ptr_called_party->ssn);

			offset=3;	//reset offset
			//2nd Mandatory parameter is Calling party address
			offset += ptrudt->ptr_second_mp;
			//next byte is the length of calling party
			int clnp_length = packet[offset];
			offset++;
			struct sccp_callingparty *ptr_calling_party = (struct sccp_callingparty*)(packet+offset);
			if(PCons::P_SCCP && PCons::DEBUG)
				printf("			: Calling Party	: %d,%d,%d,%d,%d, PC [%d] , SSN [%d]\n",
							ptr_calling_party->national_use,
							ptr_calling_party->route_ssn,
							ptr_calling_party->global_title,
							ptr_calling_party->is_ssn_present,
							ptr_calling_party->is_pointcode_present,
							ptr_calling_party->PC,
							ptr_calling_party->ssn);


			int ssn = ptr_calling_party->ssn;
			if(ssn == 142){		//RANAP Packet
				offset=4;	//reset offset
				//3rd Mandatory parameter is RANAP Data
				offset += ptrudt->ptr_third_mp;
				//next byte is the length of RANAP Data
				int ranap_data_length = packet[offset];
//				unsigned char *bytes = (unsigned char *)malloc(ranap_data_length);
				const BYTE bytes = (packet + (offset+1));
//				memcpy(bytes, packet + (offset+1), ranap_data_length);
				sctpMsgObj->iups_packetLengthRANAP = ranap_data_length;

				ranapParser->parsePacket(bytes, msgObj, sctpMsgObj, chunkNo);

				*bytes = NULL;
			}
			else
				if(PCons::P_SCCP && PCons::WARNING) printf("			SCCP Unknown SSN	 	: %d\n", ssn);

			break;
		}
		default:
		{
			if(PCons::P_SCCP){
				if(sccp_msg_type <=21)
					 if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d [%s] Skipping...\n", psccp->msg_type, SCCPGlobal::SCCP_TYPE_Val_String[sccp_msg_type]);
				else
					if(PCons::P_SCCP && PCons::LOG) printf("     SCCP Message Type	: %d Skipping...\n", psccp->msg_type);
			}
			break;
		}
	}


}



//void SCCPParser::loadSGSNPointCodes()
//{
//	char delimiter = ',';
//	stringstream ss(GContainer::config->sccpConfig->SGSN_POINT_CODES);
//	string token;
//
//	while(getline(ss, token, delimiter)) {
//		IPGlobal::SGSN_PC[NO_OF_SGSN] = atoi(token.c_str());
//		NO_OF_SGSN++;
//	}
//
//}


//void SCCPParser::write_release_dr()
//{
//	if(!SCCPGlobal::WRITE_RELEASE_DR) return;
//
//	//Now write data to track session flows
//	char file_name[100] = "";
//	sprintf(file_name,"/home/engine/workdata/CRANAPDecoder/rlsdr/%s",msgObj->sccpData->sccp_session_id);
//	//printf("%s %s\n",name, file_name);
//	FILE* file = fopen( file_name, "a" );
//	fprintf(file, "%s %d %d %s %s %s\n", msgObj->frameData->frameTimeStamp, msgObj->sctpData->opc, msgObj->sctpData->dpc, msgObj->sccpData->sccp_slr, msgObj->sccpData->sccp_dlr, SCCP_TYPE_Val_String[msgObj->sccpData->sccp_message_type]);
//	fclose(file);
//	//if(XDR::procedure_code == 19) exit(0);
//
//}

