/*
 * GTPSessionManager.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPSESSIONMANAGER_H_
#define PLUGINS_GN_SRC_GTPSESSIONMANAGER_H_

#include <queue>
#include <time.h>
#include <sys/time.h>
#include <sstream>
#include <locale.h>
#include "IPSessionManager.h"
#include "Log.h"
#include "IPGlobal.h"
//#include "SessionStore.h"
#include "GTPGlobal.h"
#include "GTPMsg.h"

using namespace std;

#define ACCEPT 128

#define LOCAL_SESSION_ARRAY_SIZE 100000 				//Poosible values 10, 100, 1000, 10000, 100000....

class GTPSessionManager : BaseConfig {

public:
		GTPSessionManager(int id, int coreid);
		~GTPSessionManager();

		VOID	run();
		VOID	updateGtpV1Session(MPacket *msgObj, int smid);


		BOOL  		isRepositoryInitialized();
		VOID 		getProcedureMapSize(int *createCount, int *updateCount, int *deleteCount);
//		GTPSession* globalLookup(const uint32_t pkt_tunnel_id, TIED_TYPE type);
		VOID 		cleanTimedOutSessionsGTPcv1();

		VOID		dumpGlobalSession();
		VOID		uploadGlobalSession();

		int 		getGlobalIndex(uint32_t tunnelId, TIED_TYPE teidType);

	private:
		string _name;

		int		instanceId;
		int		coreId;

		BOOL repoInitStatus = false;

		long processStartEpochSec = 0;

//		int activeSessionCntTotal = 0;
//		int activeSessionCntUtran = 0;
//		int activeSessionCntGeran = 0;

		timeval curTime;

		IPSessionManager	*ipSMgr;

		VOID	lockgSession();
		VOID	unLockgSession();

		VOID	lockDnsMap();
		VOID	unLockDnsMap();

		fstream		teidFile;
		BOOL fileWritten = false;

		VOID 	processMessage(MPacket *msgObj);

		VOID 	processQueue_sm(bool &gtp_msg_sm_busy, uint32_t &gtp_msg_sm_cnt,std::vector<MPacket> &gtp_msg_sm);
		VOID 	processQueue_sm(bool &gtp_msg_sm_busy, uint32_t &gtp_msg_sm_cnt, std::map<uint32_t, MPacket> &gtp_msg_sm);

		VOID 	processQueue(int t_index);

		VOID	processQueue_sm_0_i_0_r_0(int t_index);
		VOID	processQueue_sm_0_i_0_r_1(int t_index);
		VOID	processQueue_sm_0_i_0_r_2(int t_index);
		VOID	processQueue_sm_0_i_0_r_3(int t_index);
		VOID	processQueue_sm_0_i_1_r_0(int t_index);
		VOID	processQueue_sm_0_i_1_r_1(int t_index);
		VOID	processQueue_sm_0_i_1_r_2(int t_index);
		VOID	processQueue_sm_0_i_1_r_3(int t_index);
		VOID	processQueue_sm_0_i_2_r_0(int t_index);
		VOID	processQueue_sm_0_i_2_r_1(int t_index);
		VOID	processQueue_sm_0_i_2_r_2(int t_index);
		VOID	processQueue_sm_0_i_2_r_3(int t_index);
		VOID	processQueue_sm_0_i_3_r_0(int t_index);
		VOID	processQueue_sm_0_i_3_r_1(int t_index);
		VOID	processQueue_sm_0_i_3_r_2(int t_index);
		VOID	processQueue_sm_0_i_3_r_3(int t_index);


		VOID	processQueue_sm_1_i_0_r_0(int t_index);
		VOID	processQueue_sm_1_i_0_r_1(int t_index);
		VOID	processQueue_sm_1_i_0_r_2(int t_index);
		VOID	processQueue_sm_1_i_0_r_3(int t_index);
		VOID	processQueue_sm_1_i_1_r_0(int t_index);
		VOID	processQueue_sm_1_i_1_r_1(int t_index);
		VOID	processQueue_sm_1_i_1_r_2(int t_index);
		VOID	processQueue_sm_1_i_1_r_3(int t_index);
		VOID	processQueue_sm_1_i_2_r_0(int t_index);
		VOID	processQueue_sm_1_i_2_r_1(int t_index);
		VOID	processQueue_sm_1_i_2_r_2(int t_index);
		VOID	processQueue_sm_1_i_2_r_3(int t_index);
		VOID	processQueue_sm_1_i_3_r_0(int t_index);
		VOID	processQueue_sm_1_i_3_r_1(int t_index);
		VOID	processQueue_sm_1_i_3_r_2(int t_index);
		VOID	processQueue_sm_1_i_3_r_3(int t_index);

		VOID	processQueue_sm_2_i_0_r_0(int t_index);
		VOID	processQueue_sm_2_i_0_r_1(int t_index);
		VOID	processQueue_sm_2_i_0_r_2(int t_index);
		VOID	processQueue_sm_2_i_0_r_3(int t_index);
		VOID	processQueue_sm_2_i_1_r_0(int t_index);
		VOID	processQueue_sm_2_i_1_r_1(int t_index);
		VOID	processQueue_sm_2_i_1_r_2(int t_index);
		VOID	processQueue_sm_2_i_1_r_3(int t_index);
		VOID	processQueue_sm_2_i_2_r_0(int t_index);
		VOID	processQueue_sm_2_i_2_r_1(int t_index);
		VOID	processQueue_sm_2_i_2_r_2(int t_index);
		VOID	processQueue_sm_2_i_2_r_3(int t_index);
		VOID	processQueue_sm_2_i_3_r_0(int t_index);
		VOID	processQueue_sm_2_i_3_r_1(int t_index);
		VOID	processQueue_sm_2_i_3_r_2(int t_index);
		VOID	processQueue_sm_2_i_3_r_3(int t_index);

		VOID	processQueue_sm_3_i_0_r_0(int t_index);
		VOID	processQueue_sm_3_i_0_r_1(int t_index);
		VOID	processQueue_sm_3_i_0_r_2(int t_index);
		VOID	processQueue_sm_3_i_0_r_3(int t_index);
		VOID	processQueue_sm_3_i_1_r_0(int t_index);
		VOID	processQueue_sm_3_i_1_r_1(int t_index);
		VOID	processQueue_sm_3_i_1_r_2(int t_index);
		VOID	processQueue_sm_3_i_1_r_3(int t_index);
		VOID	processQueue_sm_3_i_2_r_0(int t_index);
		VOID	processQueue_sm_3_i_2_r_1(int t_index);
		VOID	processQueue_sm_3_i_2_r_2(int t_index);
		VOID	processQueue_sm_3_i_2_r_3(int t_index);
		VOID	processQueue_sm_3_i_3_r_0(int t_index);
		VOID	processQueue_sm_3_i_3_r_1(int t_index);
		VOID	processQueue_sm_3_i_3_r_2(int t_index);
		VOID	processQueue_sm_3_i_3_r_3(int t_index);

		VOID	processQueue_sm_4_i_0_r_0(int t_index);
		VOID	processQueue_sm_4_i_0_r_1(int t_index);
		VOID	processQueue_sm_4_i_0_r_2(int t_index);
		VOID	processQueue_sm_4_i_0_r_3(int t_index);
		VOID	processQueue_sm_4_i_1_r_0(int t_index);
		VOID	processQueue_sm_4_i_1_r_1(int t_index);
		VOID	processQueue_sm_4_i_1_r_2(int t_index);
		VOID	processQueue_sm_4_i_1_r_3(int t_index);
		VOID	processQueue_sm_4_i_2_r_0(int t_index);
		VOID	processQueue_sm_4_i_2_r_1(int t_index);
		VOID	processQueue_sm_4_i_2_r_2(int t_index);
		VOID	processQueue_sm_4_i_2_r_3(int t_index);
		VOID	processQueue_sm_4_i_3_r_0(int t_index);
		VOID	processQueue_sm_4_i_3_r_1(int t_index);
		VOID	processQueue_sm_4_i_3_r_2(int t_index);
		VOID	processQueue_sm_4_i_3_r_3(int t_index);

		VOID 	processRequestProcedure(GTPSession *gtpSession, MPacket *msgObj);
		VOID 	processResponseProcedure(GTPSession *gtpSession, MPacket *msgObj);

		VOID	writeXDR(GTPSession *pGtpSession);
		VOID 	packetDump(MPacket *p);

		GTPSession* getGtpSession(uint8_t type, uint32_t key, bool *found);

		VOID 	createPDPReq(MPacket *msgObj);
		VOID 	createPDPRsp(MPacket *msgObj);
		VOID 	updateReq(MPacket *msgObj);

		VOID 	updatePDPReq(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap);
		VOID 	updatePDPRsp(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap);

		VOID 	deletePDPReq(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap);
		VOID 	deletePDPRsp(MPacket *msgObj, std::map<uint16_t, GTPSession> &GTPcMap);

		VOID	gtpuPacket(MPacket *msgObj);

//		uint32_t storeFlushSessionInRepo(
//				GTPSession *pGTPSession,
//				uint32_t &gtpcV1FlushFreeBitPos_sm,
//				std::bitset<GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS> (&gtpcV1FlushRepoFlags_sm)[GTPC_V1_FLUSH_POOL_ARRAY_SIZE],
//				std::map<int, GTPSession*> (&gtpcV1FlushRepository_sm)[GTPC_V1_FLUSH_POOL_ARRAY_SIZE]);
//
		VOID 	countFlushSession(GTPSession *pGTPSession);
		VOID 	flushGTPSession(GTPSession *pGTPSession, int flushType);
		string  getSessionKey(MPacket *msgObj);


//		std::bitset<GTPC_SESSION_POOL_ARRAY_ELEMENTS> repoFlags[GTPC_SESSION_POOL_ARRAY_SIZE];
//		uint32_t freeBitPos = -1;
//		uint32_t freeBitPosMax;
//		std::vector<GTPSession*> gtpSessionRepository[GTPC_SESSION_POOL_ARRAY_SIZE];

		std::map<uint32_t, GTPSession> GTPcMapCR;
		std::map<uint16_t, GTPSession> GTPcMapUP_Z;
		std::map<uint16_t, GTPSession> GTPcMapUP_E;
		std::map<uint16_t, GTPSession> GTPcMapDL_Z;
		std::map<uint16_t, GTPSession> GTPcMapDL_E;

//		uint32_t gtpcSessionCleanUpMap[GTPC_V1_MAX_FLUSH_COUNT];
//		int gtpcSessionCleanUpMap_cnt = 0;

		VOID 		processGlobalSession(int opId, MPacket *msgObj, GTPSession *pGtpSession, const uint32_t teid, TIED_TYPE type);
		VOID 		createGlobalSession(GTPSession *pGtpSession);
		VOID 		updateGlobalSession(GTPSession *gtpSession, MPacket *msgObj);
		VOID 		removeGlobalSession(GTPSession *pGtpSession);
		VOID 		deleteGlobalSession(int glbIndex, GTPSession *pGtpGlobalSession);
//		VOID 		getDataFromGlobalSession(GTPSession *pGtpSession, MPacket *msgObj);
//		VOID		cleanUpDeletedGlobalSessions();

		std::map<int, cleanUpTeidData> cleanUpmap;
		VOID 		cleanUpGTPcLkuSessions();
		VOID 		cleanUpGTPcGlobalSessions(long curTimeEpochSec);

		uint32_t 	getGlbFreeIndex();
		VOID 		releaseGlbIndex(int index);
		VOID 		getGlobalSessionCount();
		VOID		getGlobalLkuSessionCount();

		VOID 		updateTotalSessionCnt();
		uint32_t 	getFreeIndex();
		VOID 		releaseIndex(uint32_t index);

		VOID		getGTPcLocalSessionCount();

		VOID 		initializeGtpRepository();
//		VOID 		initializeGtpMpktRepository_i_0(int intfid);
//		VOID 		initializeGtpMpktRepository_i_1(int intfid);
//		VOID 		initializeGtpMpktRepository_i_2(int intfid);
//		VOID 		initializeGtpMpktRepository_i_3(int intfid);

		VOID		initializeGTPcLocalRepository();
		VOID		initializeGtpMpktRepository();
		VOID 		initializeGtpGlobalRepository();
		VOID		initializeGtpFlusherRepository();

		VOID 		readTeidGlbDataTmp();

		VOID		readGNTunnelData(std::string filename);
		VOID		dumpTeidDump();
		VOID		readTeidGlbDataUp();
		VOID		readTeidGlbDataDn();
		VOID 		dumpTeidGlobalLku();
		VOID 		updatePDPOperationsCounters(uint8_t id);
		VOID		resetPDPOperationsCounters();
};

#endif /* PLUGINS_GN_SRC_GTPSESSIONMANAGER_H_ */
