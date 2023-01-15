/*
 * MMENASParser.h
 *
 *  Created on: 11-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_S1MME_SRC_MMENASPARSER_H_
#define PLUGINS_S1MME_SRC_MMENASPARSER_H_

#include "MMENASConstants.h"
#include "SpectaTypedef.h"
#include "IPGlobal.h"

class MMENASParser {

	private:
		TPacket *msgObj;

		long EPS_MM_SM_Message_Id_Counter[100] = {0};

		int		process_GPRS_MM_Message(const BYTE packet, unsigned int length);
		int 	process_GPRS_SM_Message(const BYTE packet, unsigned int length);
		void	decode_MM_Attach_request(const BYTE packet, unsigned int length);
		void	decode_MM_Attach_accept(const BYTE packet, unsigned int length);
		void	decode_MM_Attach_complete(const BYTE packet, unsigned int length);
		void	decode_MM_Attach_reject(const BYTE packet, unsigned int length);
		void	decode_MM_Detach_request(const BYTE packet, unsigned int length);
		void	decode_MM_Detach_accept(const BYTE packet, unsigned int length);
		void	decode_MM_Authentication_and_ciphering_request(const BYTE packet, unsigned int length);
		void	decode_MM_Authentication_and_ciphering_response(const BYTE packet, unsigned int length);
		void	decode_MM_Routing_area_update_request(const BYTE packet, unsigned int length);
		void	decode_MM_Routing_area_update_accept(const BYTE packet, unsigned int length);
		void	decode_MM_Routing_area_update_complete(const BYTE packet, unsigned int length);
		void	decode_MM_Routing_area_update_reject(const BYTE packet, unsigned int length);
		void	decode_MM_Identity_request(const BYTE packet, unsigned int length);
		void	decode_MM_Identity_response(const BYTE packet, unsigned int length);

		void	decode_SM_Activate_PDP_context_request(const BYTE packet, unsigned int length);
		void	decode_SM_Activate_PDP_context_accept(const BYTE packet, unsigned int length);
		void	decode_SM_Activate_PDP_context_reject(const BYTE packet, unsigned int length);
		void	decode_SM_Request_PDP_context_activation(const BYTE packet, unsigned int length);
		void	decode_SM_Request_PDP_context_activation_reject(const BYTE packet, unsigned int length);
		void	decode_SM_Deactivate_PDP_context_request(const BYTE packet, unsigned int length);
		void	decode_SM_Deactivate_PDP_context_accept(const BYTE packet, unsigned int length);


		int extractTLVPacket(int offset, const BYTE packet, const char *strval);
		int extractPacket(int offset, int length, const BYTE packet, const char *key);

		void extractOptionalParams(int offset, int length, const BYTE packet);

		int extractPDPAddress(int offset, const BYTE packet, bool requested);
		int extractAPN(int offset, const BYTE packet);
		int extractRAI(int offset, const BYTE packet, bool old_rai);
		int extractMobileIdentity(int offset, const BYTE packet, bool update_session);
		int extractIMSI(int offset, int length, const BYTE packet, int digit_1);
		int extractIMEI(int offset, int length, const BYTE packet, int digit_1);
		int extractTMSI(int offset, int length, const BYTE packet);
		//void processIMEI(int data_pointer, int mobile_identity_digit_1);
		//void processIMSI(int data_pointer, int mobile_identity_digit_1);
		void printPacketBytes(const BYTE packet, int size);

	public:
		MMENASParser();
		virtual ~MMENASParser();
		VOID parsePacket(const BYTE packet, TPacket *msgObj);
};

#endif /* PLUGINS_S1MME_SRC_MMENASPARSER_H_ */
