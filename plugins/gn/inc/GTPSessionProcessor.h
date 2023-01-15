/*
 * GTPSessionProcessor.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPSESSIONPROCESSOR_H_
#define PLUGINS_GN_SRC_GTPSESSIONPROCESSOR_H_

#include <map>
#include <queue>
#include <time.h>


#include "Log.h"
#include "IPGlobal.h"
#include "SessionStore.h"
#include "GTPGlobal.h"
#include "GTPMsg.h"

using namespace std;

#define ACCEPT 128

/*
 * *** GTP-V1 Maps ***
 */
typedef std::shared_ptr<controlpacket> sh_controlpacket;
typedef std::map<uint32_t, sh_controlpacket> GTPcMap;


class GTPSessionProcessor : public SessionStore
{
	public:
		GTPSessionProcessor(int id);
		~GTPSessionProcessor();

		int		instanceId;
		VOID 	setLogLevel (int level) {_thisLogLevel = level;}
		VOID	updateGtpV1Session(MPacket *msgObj);

		int		cleanGTPCreateRecords(int processedMin, ULONG epochTimeMicroSec);
		int		cleanGTPUpdateRecords(int processedMin, ULONG epochTimeMicroSec);
		int		cleanGTPDeleteRecords(int processedMin, ULONG epochTimeMicroSec);

		VOID 	getProcedureMapSize(int *createCount, int *updateCount, int *deleteCount);

		VOID	lockgSession();
		VOID	unLockgSession();

	private:
		int _thisLogLevel;
		string _name;

		GTPSession *pGtpGlobalSession;
		GTPSession *pLocalGtpGlobalSession;
		GTPSession *gtpSession;

		sh_controlpacket pktstruct, emptyPktStruct;

		//typedef std::map<uint32_t, sh_controlpacket> map_global_gtp;

		/* GTP-V1 Session Maps */
		GTPcMap pdp_req_map = GTPcMap();
		GTPcMap pdp_upd_map = GTPcMap();
		GTPcMap pdp_del_map = GTPcMap();


//		inline int thisLogLevel () const {return _thisLogLevel;}
//		inline string name() const {return _name;}

		VOID 	createProcedure(sh_controlpacket pktstruct, MPacket *msgObj);

		VOID 	updateProcedure(sh_controlpacket pktstruct, MPacket *msgObj);
		VOID	updateOnlyResponse(GTPSession *pGtpSession, MPacket *msgObj);

		VOID	writeXDR(GTPSession *pGtpSession);
		VOID 	packetDump(MPacket *p);

		VOID 	createPDPReq(MPacket *msgObj);
		VOID 	createPDPRsp(MPacket *msgObj);
		VOID 	updateReq(MPacket *msgObj);

		VOID 	updatePDPReq(MPacket *msgObj);
		VOID 	updatePDPRsp(MPacket *msgObj);

		VOID 	deletePDPReq(MPacket *msgObj);
		VOID 	deletePDPRsp(MPacket *msgObj);

		VOID	gtpuPacket(MPacket *msgObj);

		string 	generateKey(MPacket *msgObj);
		void    initialize(sh_controlpacket pktstruct);

		VOID 	copyGTPData(sh_controlpacket pGtpSession, GTPSession *sendBuffer);
		VOID 	flushGTPSession(int min, GTPSession *gtpSession);
		VOID 	flushGTPSecSession(int sec, GTPSession *gtpSession);

};

#endif /* PLUGINS_GN_SRC_GTPSESSIONPROCESSOR_H_ */
