/*
 * SCCPParser.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCTP_SRC_SCCPPARSER_H_
#define PLUGINS_SCTP_SRC_SCCPPARSER_H_

#include <stdlib.h>    //malloc
#include <stdio.h>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include <vector>
#include <algorithm>

#include "IPGlobal.h"
#include "SCCPGlobal.h"
#include "ProbeUtility.h"
#include "SCCPConstants.h"
#include "RANAPParser.h"
#include "SCCPSessionManager.h"
#include "ProbeUtility.h"


struct sccp {
	unsigned char msg_type;
	unsigned int dest_local_ref:3;
	unsigned int source_local_ref:3;
	unsigned char msg_class;
	unsigned char ptr_to_opt_param;
}__attribute__((packed));

struct sccp_cr {
	unsigned char msg_type;			// 1 byte
	unsigned char slr_B_1;			// 1 byte
	unsigned char slr_B_2;			// 1 byte
	unsigned char slr_B_3;			// 1 byte
	unsigned char protocol_class;	// 1 byte
	unsigned char ptr_called_party;	// 1 byte
	unsigned char ptr_to_opt_param;	// 1 byte
	unsigned char payload[0];
}__attribute__((packed));

struct sccp_cc {
	unsigned char msg_type;			// 1 byte
	unsigned char dlr_B_1;			// 1 byte
	unsigned char dlr_B_2;			// 1 byte
	unsigned char dlr_B_3;			// 1 byte
	unsigned char slr_B_1;			// 1 byte
	unsigned char slr_B_2;			// 1 byte
	unsigned char slr_B_3;			// 1 byte
	unsigned char protocol_class;	// 1 byte
	unsigned char payload[0];
}__attribute__((packed));

struct sccp_dt1 {
	unsigned char msg_type;			// 1 byte
	unsigned char dlr_B_1;			// 1 byte
	unsigned char dlr_B_2;			// 1 byte
	unsigned char dlr_B_3;			// 1 byte
	unsigned char uk_B_4;			// 1 byte
	unsigned char uk_B_5;			// 1 byte
	unsigned char msg_length;		// 1 byte
	unsigned char payload[0];
}__attribute__((packed));

struct sccp_rlsd {
	unsigned char msg_type;			// 1 byte
	unsigned char dlr_B_1;			// 1 byte
	unsigned char dlr_B_2;			// 1 byte
	unsigned char dlr_B_3;			// 1 byte
	unsigned char slr_B_1;			// 1 byte
	unsigned char slr_B_2;			// 1 byte
	unsigned char slr_B_3;			// 1 byte
	unsigned char rel_cause;		// 1 byte
	unsigned char ptr_to_opt_param;		// 1 byte
}__attribute__((packed));

struct sccp_rlc {
	unsigned char msg_type;			// 1 byte
	unsigned char dlr_B_1;			// 1 byte
	unsigned char dlr_B_2;			// 1 byte
	unsigned char dlr_B_3;			// 1 byte
	unsigned char slr_B_1;			// 1 byte
	unsigned char slr_B_2;			// 1 byte
	unsigned char slr_B_3;			// 1 byte
}__attribute__((packed));


struct sccp_udt {
	unsigned char msg_type;			// 1 byte
	unsigned char protocol_class;	// 1 byte
	unsigned char ptr_first_mp;		// 1 byte
	unsigned char ptr_second_mp;	// 1 byte
	unsigned char ptr_third_mp;		// 1 byte
	unsigned char payload[0];
}__attribute__((packed));

/*struct sccp_calledparty {
	unsigned char address_indicator;	// 1 byte
	unsigned short PC;					// 2 bytes
	unsigned char ssn;					// 1 byte
}__attribute__((packed));*/

struct sccp_calledparty {
	unsigned char is_pointcode_present:1;			// 1 bit
	unsigned char is_ssn_present:1;	// 1 bit
	unsigned int global_title:4;		// 4 bit
	unsigned char route_ssn:1;		// 1 bit
	unsigned char national_use:1;			// 1 bit
	unsigned short PC;
	unsigned char ssn;
}__attribute__((packed));

struct sccp_callingparty {
	unsigned char is_pointcode_present:1;			// 1 bit
	unsigned char is_ssn_present:1;	// 1 bit
	unsigned int global_title:4;		// 4 bit
	unsigned char route_ssn:1;		// 1 bit
	unsigned char national_use:1;			// 1 bit
	unsigned short PC;
	unsigned char ssn;
}__attribute__((packed));



class SCCPParser : public ProbeUtility {
	private:

		RANAPParser *ranapParser;
//		SCCPSessionManager *sm;

//		int SGSN_PC[16];
//		int NO_OF_SGSN = 0;

		//void write_session(const char *name, const char *str);
		void traceSession(const char *str, MPacket *msgObj);
		void write_imsi_session(const char *name);
		void read_imsi_session(const char *name);
		void write_tmsi_session(const char *name);
		void read_tmsi_session(const char *name);
		//char * read_imsi_session(const char *name);
		//char * read_tmsi_session(const char *name);
		void write_imsi_tmsi_map();
		char * read_imsi_tmsi_map(const char *name);
		void delete_session(const char *s_slr, const char *s_dlr);
		void write_release_dr();
		void resetXDRValues();
		void loadTraceSessionIds();
		void loadSGSNPointCodes();

		/*void create_session(const char *slr);
		void update_session(const char *col, const char *val, const char *wherecol, const char *whereval);
		void delete_session(const char *ref);
		const unsigned char * select_session(const char *col, const char *wherecol, const char *whereval);*/

	public:
		SCCPParser();
		~SCCPParser();

		void processPacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo, unsigned int length);
};

#endif /* PLUGINS_SCTP_SRC_SCCPPARSER_H_ */
