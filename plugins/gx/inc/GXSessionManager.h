/*
 * GXSessionManager.h
 *
 *  Created on: Oct 15, 2016
 *      Author: Debashis
 */

#ifndef PLUGINS_GX_SRC_GXSESSIONMANAGER_H_
#define PLUGINS_GX_SRC_GXSESSIONMANAGER_H_

#include "Log.h"
#include "IPGlobal.h"
#include "GXGlobal.h"
#include "SessionStore.h"

class GXSessionManager : public SessionStore {

public:
	GXSessionManager();
	~GXSessionManager();

	VOID updateGxSession(MPacket *msgObj, int selfId);
	VOID closeGxSession(MPacket *msgObj, int selfId);
	VOID createGxSession(MPacket *msgObj, int selfId);
	VOID initialize(sh_GxPacket pktstruct);
	VOID createSession(sh_GxPacket pGxSession, MPacket *msgObj);
	VOID buildCSVData(gxSession *pGxSession, string& csvBuffer);
};

#endif /* PLUGINS_GX_SRC_GXSESSIONMANAGER_H_ */
