/*
 * IUPSSessionManager.h
 *
 *  Created on: 19-Jul-2016
 *      Author: Deb
 */

#ifndef PLUGINS_IUPS_SRC_IUPSSESSIONMANAGER_H_
#define PLUGINS_IUPS_SRC_IUPSSESSIONMANAGER_H_

#include <vector>
#include <algorithm>
#include <time.h>
#include <sys/time.h>

#include "Log.h"
#include "IPGlobal.h"
#include "IUPSGlobal.h"
#include "SCCPGlobal.h"
#include "SCCPConstants.h"
#include "NASConstants.h"

//#include "RANAPConstants.h"

#define FLOW_DIR_RNC_SGSN	"RNC->SGSN"
#define FLOW_DIR_SGSN_RNC	"SGSN->RNC"

#define IUPS_SESSION_ARRAY_SIZE 1000 					//Possible values 10, 100, 1000, 10000, 100000....

#define RANAP_SESSION 101
#define GMM_SESSION 102
#define SCCP_SESSION 103

using namespace std;


class IUPSSessionManager : BaseConfig{

	private:
		timeval curTime;


		VOID 	loadImsiTmsiMap();

		//VOID flushSession(int min, sccpSession *pSccpSession, iupsTrxSession *strx);
		VOID makeAndFlushSession(int type, sccpSession *sglb, iupsTrxSession *strx);
		//VOID buildCSVData(sccpSession *sglb, iupsTrxSession *strx);

		VOID processIupsSessionFlush(sccpSession *pSccpSession, bool flush_type_gmm, bool flush_type_ranap);
		VOID processSCCPSessionFlush(sccpSession *pSccpSession);
		VOID writeTraceTdr(string sccpSessionId, string str);
		VOID flushIupsSession(string csvxdr);
		uint32_t storeIupsFlushSession(iupsSession *pIupsSession);
		void writeXdr(string str);

	public:
		IUPSSessionManager();
		virtual ~IUPSSessionManager();

		VOID	dumpImsiTmsiMap();

		VOID 	countImsiTmsiEnrty();
		VOID 	updateImsiTmsiMap(std::string imsi, std::string tmsi);

		VOID 	updateSession(sccpSession *pSccpSession, MPacket *msgObj, SCTP *pSctpPacket);
		string 	buildCSVData(iupsSession *pIupsSession);
		string 	buildTDRData(iupsSession *pIupsSession);
		VOID 	flushSession(sccpSession *pSccpSession);
		VOID 	initializeIUPSFlushRepository();
};

#endif /* PLUGINS_IUPS_SRC_IUPSSESSIONMANAGER_H_ */
