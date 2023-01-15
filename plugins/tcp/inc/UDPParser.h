/*
 * PUDP.h
 *
 *  Created on: Nov 29, 2015
 *      Author: Debashis
 */

#ifndef INC_UDPPROBE_H_
#define INC_UDPPROBE_H_

//#include "BaseConfig.h"
#include "ProbeUtility.h"
#include "IPGlobal.h"
#include "TCPUDPGlobal.h"
#include "DnsData.h"
#include "Log.h"

using namespace std;

//#define UDP_HDR_LEN		8
//#define DNS_HDR_LEN		12
//#define IP4LEN			4
//#define IP6LEN			16
//#define	STUN_PORT		3478
//
//#define UDP_NO_ERROR	0

enum
{
  IP4_LEN = 4,
  IP6_LEN = 16
};


#define INDICATION      		0x0115

#define MAGIC_COOKIE            0x000f
#define REMOTE_ADDRESS        	0x0012
//#define DATA                    0x0013

#define STUN_PKT_HEADER 20

struct stun_packet_header {
  uint16_t msgType, msgLen;
  uint32_t cookie;
  uint8_t  transactionId[8];
};


class UDPParser : public DnsData
{
	private:
		ProbeUtility 	*utility;
		DnsData 		*dnsData;

		timeval curTime;
		long beginEpochSec = 0;
		int beginSec = 0;

		int instanceId = 0;
		uint16_t qdcount = 0, ancount = 0, nscount = 0, arcount = 0;

		ULONG convIP2Long(char *ipAddress);
		VOID  insertStunData(string key, string addr, ULONG epochTimeSec);

	public:

		UDPParser();
		~UDPParser();

		VOID	parsePacket(const BYTE packet, MPacket *tPacket);
		VOID	parsePacketDNS(const BYTE packet, MPacket *);
		BOOL	parsePacketDNSQueries(uint32_t, uint32_t, MPacket *msg, const UCHAR *, uint32_t *retPos);
		string 	read_rr_name(const uint8_t * packet, uint32_t * packet_p, uint32_t id_pos, uint32_t len);
		VOID	parsePacketDNSAnswers(uint32_t pos, MPacket *msgObj, const BYTE packet);
		VOID	lockDnsMap();
		VOID	unLockDnsMap();
		VOID	decodeStunMsg(const BYTE packet, MPacket *msgObj);
};

#endif	/* INC_UDPPROBE_H_ */
