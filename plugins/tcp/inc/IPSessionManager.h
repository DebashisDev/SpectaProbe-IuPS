/*
 * IPSessionManager.h
 *
 *  Created on: 20-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_TCP_SRC_IPSESSIONMANAGER_H_
#define PLUGINS_TCP_SRC_IPSESSIONMANAGER_H_

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#include "SpectaTypedef.h"
#include "Log.h"
#include "IPGlobal.h"
#include "TCPUDPGlobal.h"
#include "GTPGlobal.h"
#include "BaseConfig.h"
#include "TCPFlusherUtility.h"

#define IP_SESSION_ARRAY_SIZE 10000					//Possible values 10, 100, 1000, 10000, 100000....
#define DNS_SESSION_ARRAY_SIZE 1000					//Possible values 10, 100, 1000, 10000, 100000....

#define DNS_NO_ERROR	0




class IPSessionManager : BaseConfig{

	private:

			ULONG freeIndexTime = 0;

			TCPFlusherUtility *tcpFlusherUtility;

			timeval curTime;
			int today = 0;

//uint128_t MULTI_1		=		10000000000;
//uint128_t MULTI_2		=		100000;
//uint128_t key_1;
//uint128_t key_2;

//			std::map<uint64_t, fData> emptypackTimeMap;

			int instanceId = 0;
//			int curSecGlb = 0;

//			uint32_t getSessionArrayIndex(bool direction, uint16_t sourcePort, uint16_t destPort);

			/* -- DNS Declaration -- */
//			uint32_t freeBitPosDns = -1;
//			uint32_t freeBitPosMaxDns;
//			std::bitset<DNS_SESSION_POOL_ARRAY_ELEMENTS> repoFlagsDns[DNS_SESSION_POOL_ARRAY_SIZE];
//			std::vector<dnsSession*> dnsSessionRepository[DNS_SESSION_POOL_ARRAY_SIZE];

			std::map<uint32_t, dnsSession> dnsSessionMap;
			std::map<uint32_t, uint32_t> dnsSessionCleanUpMap;
			uint32_t dnsSessionCleanUpMap_cnt = 0;
			std::map<uint32_t, string> dnsDatabaseCleanMap;
			uint32_t dnsDatabaseCleanMap_cnt = 0;

			VOID		createDnsSession(dnsSession *pDnsSession, MPacket *msgObj);
			VOID 		updateDnsSession(dnsSession *pDnsSession, MPacket *msgObj);
			dnsSession* getDnsSession(MPacket *msgObj, bool *found);

//			uint32_t 	getFreeDnsIndex();
//			VOID 		releaseDnsIndex(uint32_t index);
			VOID 		flushDnsSession(dnsSession *pDnsSession);

			/* -- IP Declaration -- */
//			uint32_t freeBitPosIp = -1;
//			uint32_t freeBitPosMaxIp;
//			std::bitset<IP_SESSION_POOL_ARRAY_ELEMENTS> repoFlagsIp[IP_SESSION_POOL_ARRAY_SIZE];
//			std::vector<ipSession*> ipSessionRepository[IP_SESSION_POOL_ARRAY_SIZE];
			typedef struct _cleanObj
			{
				std::string key;
				int index;
			}cleanObj;

			std::map<uint32_t, cleanObj> ipSessionCleanUpMap;
//			std::map<uint32_t, std::string> ipSessionCleanUpMap;
			uint32_t ipSessionCleanUpMap_cnt = 0;

			std::map<std::string, ipSession> ipSessionMap[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap;

//			std::map<std::string, ipSession> ipSessionMap_0[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_1[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_2[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_3[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_4[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_5[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_6[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_7[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_8[IP_SESSION_ARRAY_SIZE];
//			std::map<std::string, ipSession> ipSessionMap_9[IP_SESSION_ARRAY_SIZE];


//			uint32_t 	getFreeIndex();
//			VOID 		releaseIndex(uint32_t index);
			ipSession* 	getIpSession(MPacket *msgObj, bool *found, bool create);
//			uint32_t 	getMapIndex(BOOL dir, uint32_t sIP, uint32_t dIP);
//			uint32_t 	getIpSessionMapArrayIndex(ULONG sIp, ULONG dIp, bool isUpDir);
//			void 		getIpSessionMapArrayIndex(uint32_t sIp, uint32_t dIp, bool isUpDir, uint32_t *mapIndex, int *mapId);
			VOID 		eraseIpSession(ipSession *pIpSession);

			VOID 		updateSessionCnt(bool create);

			VOID 		initializeIpVolumeData(ipSession *pIpSession);
			VOID 		initializeTcpSession(ipSession *pIpSession, MPacket *msgObj);
			VOID		updateTcpFrame(ipSession *pIpSession, MPacket *msgObj);

			VOID 		createUdpSession(ipSession *pIpSession, MPacket *msgObj);
			VOID 		updateUdpFrame(ipSession *pIpSession, MPacket *msgObj);

			VOID 		flushIpSession(int id, ipSession *pIpSession, bool erase, bool ignoreSessionFlush);
			VOID 		storeIpSession(int index, ipSession *pIpSession);
			VOID 		storeIpSession_f_0(int index, ipSession *pIpSession);
			VOID 		storeIpSession_f_1(int index, ipSession *pIpSession);
			VOID 		storeIpSession_f_2(int index, ipSession *pIpSession);
			VOID 		storeIpSession_f_3(int index, ipSession *pIpSession);

			VOID 		storeDnsSession(int index, dnsSession *pDnsSession);
			VOID 		storeDnsSession_f_0(int index, dnsSession *pDnsSession);
			VOID 		storeDnsSession_f_1(int index, dnsSession *pDnsSession);
			VOID 		storeDnsSession_f_2(int index, dnsSession *pDnsSession);
			VOID 		storeDnsSession_f_3(int index, dnsSession *pDnsSession);

//			uint32_t 	storeIPFlushSession(ipSession *pIpSession);
//			uint32_t	storeDnsFlushSession(dnsSession *pDnsSession);

			VOID 		processCleanTimedOutSessionsIP(int mapId, int mapArrId, ipSession *pIpSession);
			VOID 		eraseCleanedSessions();

//			VOID 		buildIpCsvBuffer(ipSession *pIpSession, char *csvBuffer);
			VOID 		getVolPerSec(ipSession *pIpSession);

			VOID 		createTCPXdr(ipSession *pIpSession, char *xdr, string dnVol, string upVol);
			void 		createUDPXdr(ipSession *pIpSession, char *xdr, string dnVol, string upVol);

			VOID 		countFinOnlySessions();

			VOID 		initializeIPFlushRepository();
			VOID 		initializeDNSFlushRepository();

	public:
			IPSessionManager(int id);
			~IPSessionManager();

			long busyCnt = 0;

			VOID 	countActiveIPSessions();

			VOID 	setLogLevel (int level) {_thisLogLevel = level;}

			VOID 	processTcpSession(MPacket *msgObj);
			VOID 	processUdpSession(MPacket *msgObj);
			VOID 	processDnsSession(MPacket *msgObj);
			VOID 	processOtrSession(MPacket *msgObj);

			int		getSessionKey(MPacket *msgObj, char *key);
			VOID 	cleanTimedOutSessionsIP();
			VOID 	cleanTimedOutSessionsDns();
			VOID 	cleanDnsDatabaseMap();
			bool 	sessionSizeInLimit();
			VOID 	getSessionSize();
			VOID 	resetFinOnlySessionsCount();
			VOID 	dumpDnsLookupMap();
			VOID 	loadDnsLookupMap();
			VOID	getDnsLookUpMapSize();
			VOID 	getDnsDatabaseMapSize();
};

#endif /* PLUGINS_TCP_SRC_IPSESSIONMANAGER_H_ */
