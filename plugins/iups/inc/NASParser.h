/*
 * NASParser.h
 *
 *  Created on: 16-Jul-2016
 *      Author: Deb
 */

#ifndef PLUGINS_IUPS_SRC_NASPARSER_H_
#define PLUGINS_IUPS_SRC_NASPARSER_H_

#include "NASConstants.h"
#include "SpectaTypedef.h"
#include "BaseConfig.h"
#include "IPGlobal.h"
#include "SCCPGlobal.h"
#include "SCCPSessionManager.h"

class NASParser : public BaseConfig {

	private:
//		MPacket *msgObj;
//		SCCPSessionManager *sm;

		long MM_SM_Message_Id_Counter[100] = {0};

		int		process_GPRS_MM_Message(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int 	process_GPRS_SM_Message(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Attach_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Attach_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Attach_complete(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Attach_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Detach_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Detach_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Authentication_and_ciphering_request(const BYTE packet, unsigned int length, MPacket *msgObj);
		void	decode_MM_Authentication_and_ciphering_response(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Authentication_and_ciphering_failure(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Authentication_and_ciphering_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Routing_area_update_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Routing_area_update_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Routing_area_update_complete(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Routing_area_update_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_MM_Identity_request(const BYTE packet, unsigned int length, MPacket *msgObj);
		void	decode_MM_Identity_response(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);

		void	decode_SM_Activate_PDP_context_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_SM_Activate_PDP_context_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_SM_Activate_PDP_context_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_SM_Request_PDP_context_activation(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_SM_Request_PDP_context_activation_reject(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_SM_Deactivate_PDP_context_request(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		void	decode_SM_Deactivate_PDP_context_accept(const BYTE packet, unsigned int length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);


		int extractTLVPacket(int offset, const BYTE packet, const char *strval);
		int extractPacket(int offset, int length, const BYTE packet, const char *key);

		void extractOptionalParams(int offset, int length, const BYTE packet, MPacket *msgObj);

		int extractPDPAddress(int offset, const BYTE packet, bool requested, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractQoS(int offset, const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractAPN(int offset, const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractRAI(int offset, const BYTE packet, bool old_rai, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractMobileIdentity(int offset, const BYTE packet, bool update_session, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractIMSI(int offset, int length, const BYTE packet, int digit_1, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractIMEI(int offset, int length, const BYTE packet, int digit_1, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		int extractTMSI(int offset, int length, const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
		//void processIMEI(int data_pointer, int mobile_identity_digit_1);
		//void processIMSI(int data_pointer, int mobile_identity_digit_1);
		void printPacketBytes(const BYTE packet, int size);


	public:
		NASParser();
		~NASParser();

		VOID parsePacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo);
};

#endif /* PLUGINS_IUPS_SRC_NASPARSER_H_ */
