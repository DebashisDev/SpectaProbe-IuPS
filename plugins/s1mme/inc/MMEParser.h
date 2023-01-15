/*
 * MMEParser.h
 *
 *  Created on: Aug 1, 2016
 *      Author: Deb
 */

#ifndef PLUGINS_S1MME_MMEPARSER_H_
#define PLUGINS_S1MME_MMEPARSER_H_

#include "IPGlobal.h"
#include "s1ap.h"

class MMEParser {
	private:
		TPacket *msgObj;

		OssGlobal	w, *world = &w;						/* structure ossGlobal */
		mmeS1AP_PDU *DecodedDataPtr;

		void parseMMEProcedures(int proc_id, std::string xmlin, int length);
		string processIMSI(string imsi);
		void setRABCauseId();
		BYTE packStringToByteArray(string input);
		string get_value(std::string inxml, std::string cmptag);
		void initialize();
		void parsePacketToXml(const BYTE packet, int length);
		string decode_mme_packet(const BYTE packet, int length);
		void printPacketBytes(const BYTE packet, int size);

	public:
		MMEParser();
		virtual ~MMEParser();
		void parsePacket(const BYTE packet, TPacket *msgObj);
};

#endif /* PLUGINS_S1MME_MMEPARSER_H_ */
