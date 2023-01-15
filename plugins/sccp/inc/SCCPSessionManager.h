/*
 * SCCPSessionManager.h
 *
 *  Created on: 17-Jul-2016
 *      Author: Deb
 */

#ifndef PLUGINS_SCCP_SRC_SCCPSESSIONMANAGER_H_
#define PLUGINS_SCCP_SRC_SCCPSESSIONMANAGER_H_

#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include "IUPSSessionManager.h"
#include "SCCPConstants.h"
#include "SCCPGlobal.h"
#include "IPGlobal.h"
#include "ProbeUtility.h"

using namespace std;

#define IMEI_LENGTH_MIN 16

typedef struct _s_imsi{

	string	tmsi;
	string	imei;
	string	msisdn;

	_s_imsi()
	{ reset(); }

	void reset()
	{
		tmsi.assign("NA");
		imei.assign("NA");
		msisdn.assign("NA");
	}
}s_imsi;


class SCCPSessionManager : BaseConfig{

	private:

		int		instanceId;
		int		coreId;

		IUPSSessionManager *iupsSm;

		timeval curTime;
		long processStartEpochSec = 0;

		std::map<std::string, sccpSession> sccpSessionMap;
		std::map<string, string> S_MAP_KEY1;
		std::map<string, string> S_MAP_KEY2;
		std::map<string, string> S_IMSI_IMEI_MAP;

		VOID 			create_sccp_session(MPacket *msgObj, SCTP *sctpPacket, sccpSession *pSccpSession);
		VOID 			update_sccp_session(MPacket *msgObj, SCTP *sctpPacket, sccpSession *pSccpSession);
		sccpSession* 	getSccpSession(string sessionKey, bool *found);
		VOID 			eraseSCCPKey(string sessionKey);

		VOID 			processMessage(MPacket *msgObj, SCTPChunkMap sctpChunkMap);
		VOID 			processChunk(MPacket *msgObj, std::map<int, SCTP> &chunkMap);

		VOID 			create_session_key_lookup(MPacket *msgObj, SCTP *sctpPacket);
		string 			get_session_id_from_lookup(SCTP *sctpPacket);

		void 			traceSession(const char *sender, const char *str, MPacket *msgObj, SCTP *sctpPacket);
		void			loadTraceSessionIds();

		VOID 			processQueue_sm(bool &sccp_msg_sm_busy, int &sccp_msg_sm_cnt, std::map<int, MPacket> &sccp_msg_sm, std::map<uint64_t, SCTPChunkMap> &sctpChunkMap_sm);

		VOID 			processQueue(int t_index);
		VOID 			processQueue_sm_0_i_0_r_0(int t_index);
		VOID 			processQueue_sm_0_i_0_r_1(int t_index);
		VOID 			processQueue_sm_0_i_1_r_0(int t_index);
		VOID 			processQueue_sm_0_i_1_r_1(int t_index);

//		VOID 			initializeRepository();
//		VOID 			initializeMpktRepository_i_0(int intfid);
//		VOID 			initializeMpktRepository_i_1(int intfid);
		VOID			cleanTimedOutSccpSessions();

		VOID 			cleanKEYMap(sccpSession *pSccpSession);

		VOID 			flushSession(sccpSession *pSccpSession);
		VOID 			delete_sccp_lookup(MPacket *msgObj, SCTP *sctpPacket);
		string 			select_from_sccp_lookup(int id, char *sccp_session_Id);
		VOID 			writeCustomTDR(bool f_type_sccp, bool f_type_gmm, bool f_type_ranap, MPacket *msgObj);

	public:
		SCCPSessionManager(int id, int coreid);
		virtual ~SCCPSessionManager();

		VOID run();

};

#endif /* PLUGINS_SCCP_SRC_SCCPSESSIONMANAGER_H_ */
