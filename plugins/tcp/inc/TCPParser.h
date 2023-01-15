/*
 * PTCP.h
 *
 *  Created on: Nov 29, 2015
 *      Author: debashis
 */

#ifndef INC_TCPPROBE_H_
#define INC_TCPPROBE_H_

#include "SpectaTypedef.h"
//#include "BaseConfig.h"
#include "IPGlobal.h"
#include "TCPUDPGlobal.h"
#include "ProbeUtility.h"
#include "PacketSSL.h"


#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define TCPHDR 20
#define MAX_TCP_PAYLOAD 20

#define LF              10
#define CR				13

typedef enum {
    SSL_V_1         = 769,	//0x03, 0x01
    SSL_V_1_2       = 771	//0x03, 0x03
} sslVersion;

class TCPParser : public PacketSSL
{
	private:
		ULONG 		tsval, tsecr;
		uint16_t 	psh, rst, syn, fin, window, ack, urg, ackNo, check, urgPtr;
		tcphdr 		*tcpHeader;

	public:
		TCPParser();
		~TCPParser();

		VOID parsePacket(const BYTE packet, MPacket *msgObj);
		void checkContentType(const BYTE packet, MPacket *msgObj);
		vector<string> split(string str, char delimiter);
};

#endif  /* INC_TCPPROBE_H_ */
