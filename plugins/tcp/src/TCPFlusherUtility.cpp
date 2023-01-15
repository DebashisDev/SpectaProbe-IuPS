/*
  * TCPFlusherUtility.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: Deb
 */

#include "TCPFlusherUtility.h"

TCPFlusherUtility::TCPFlusherUtility() {
	pGtpUserInfo = new GTPUserInfo();
}

TCPFlusherUtility::~TCPFlusherUtility() {
	delete(pGtpUserInfo);
}

VOID
TCPFlusherUtility::lockDnsMap()
{
	pthread_mutex_lock(&mapDnsLock::lockCount);
	while (mapDnsLock::count == 0)
		pthread_cond_wait(&mapDnsLock::nonzero, &mapDnsLock::lockCount);
	mapDnsLock::count = mapDnsLock::count - 1;
	pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID
TCPFlusherUtility::unLockDnsMap()
{
    pthread_mutex_lock(&mapDnsLock::lockCount);
    if (mapDnsLock::count == 0)
        pthread_cond_signal(&mapDnsLock::nonzero);
    mapDnsLock::count = mapDnsLock::count + 1;
    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID TCPFlusherUtility::lockgSession()
{
	pthread_mutex_lock(&gSessionLock::lockCount);
	while (gSessionLock::count == 0){
		pthread_cond_wait(&gSessionLock::nonzero, &gSessionLock::lockCount);
	}
	gSessionLock::count = gSessionLock::count - 1;
	pthread_mutex_unlock(&gSessionLock::lockCount);
}

VOID TCPFlusherUtility::unLockgSession()
{
    pthread_mutex_lock(&gSessionLock::lockCount);
    if (gSessionLock::count == 0)
        pthread_cond_signal(&gSessionLock::nonzero);
    gSessionLock::count = gSessionLock::count + 1;
    pthread_mutex_unlock(&gSessionLock::lockCount);
}

//VOID TCPFlusherUtility::buildGTPuIPCsvBuffer(int flushOrgId, uint64_t flushTime, ipXdrData *pIpXdrData, char *csvBuffer)
//{
//	std::string URL;
//	std::string userIP_resolveIP_key;
//
//	if(pIpXdrData->teidLookUp)
//	{
//		lockDnsMap();
//		userIP_resolveIP_key = getDNSKey(pIpXdrData->sourceIP, pIpXdrData->destIP);
//		getDNSUrlForIP(userIP_resolveIP_key, URL, pIpXdrData->destIP);
//		unLockDnsMap();
//	}
//
//	if(!URL.length())
//		URL = "NULL";
//
//		if(pIpXdrData->teidLookUp)
//		{
//			lockgSession();
//			getGtpData(pGtpUserInfo, pIpXdrData);
//			unLockgSession();
//		}
//		sprintf(csvBuffer, "%s,%s,%s,%s,%s,%d,%s,%d,%d,%d,%d,%d,%d,%u",
//				pIpXdrData->xdrData, URL.c_str(), pGtpUserInfo->imsi.c_str(),pGtpUserInfo->msisdn.c_str(), pGtpUserInfo->imei.c_str(), pGtpUserInfo->rat, pGtpUserInfo->ratDesc.c_str(),
//				pGtpUserInfo->MCC, pGtpUserInfo->MNC, pGtpUserInfo->LAC, pGtpUserInfo->CI, pGtpUserInfo->activeState,flushOrgId, flushTime);
//}


VOID TCPFlusherUtility::getVolPerSec(ipSession *pIpSession)
{
	char timeBuffer[100];

	uint32_t packets, volume, c_pickThrPut, f_pickThrPut;
	uint32_t c_up_pickThrPut, f_up_pickThrPut, c_dn_pickThrPut, f_dn_pickThrPut;
	uint32_t uppackets, upvolume, dnpackets, dnvolume;
	uint32_t tcpUpPacket, tcpDnPacket;
	uint16_t tcpUpCount, tcpDnCount;

	int timeDiff = 0;

	tcpUpPacket = tcpDnPacket = 0;
	tcpUpCount = tcpDnCount = 0;
	ULONG firstSec = 0;

	int packetTSCount = pIpSession->packTimeMap.size();
	int packetCount = 0;
	packets = volume = c_pickThrPut = f_pickThrPut = 0;
	c_up_pickThrPut = f_up_pickThrPut = c_dn_pickThrPut = f_dn_pickThrPut = 0;

	for(auto elem : pIpSession->packTimeMap)
	{
		packetCount ++;
		packets = elem.second.totalPackets;
		volume = elem.second.totalVolume;
		upvolume = elem.second.upVolume;
		dnvolume = elem.second.dnVolume;

		c_pickThrPut = volume;
		if (c_pickThrPut > f_pickThrPut)
			f_pickThrPut = c_pickThrPut;

		if(upvolume > 0) {
			tcpUpCount += 1;
			tcpUpPacket = elem.second.upPackets;
			upvolume = elem.second.upVolume;
			c_up_pickThrPut = upvolume;
			if (c_up_pickThrPut > f_up_pickThrPut)
				f_up_pickThrPut = c_up_pickThrPut;
		}

		if(dnvolume > 0){
			tcpDnCount += 1;
			tcpDnPacket = elem.second.dnPackets;
			dnvolume = elem.second.dnVolume;
			c_dn_pickThrPut = dnvolume;
			if (c_dn_pickThrPut > f_dn_pickThrPut)
				f_dn_pickThrPut = c_dn_pickThrPut;
		}

		if(packetCount == 1 ) {
			firstSec = elem.first;
			pIpSession->dnVolPerSec[0] = 0;
			sprintf(pIpSession->dnVolPerSec, "%u=", firstSec);
			pIpSession->upVolPerSec[0] = 0;
			sprintf(pIpSession->upVolPerSec, "%u=", firstSec);
		}

		if(dnvolume > 0 && strlen(pIpSession->dnVolPerSec) < (VPS_MAX_LEN - 200))
		{
			timeDiff = elem.first - firstSec;
			if(timeDiff >= 0){
				timeBuffer[0] = 0;
				sprintf(timeBuffer, "%d#%u#%u;", timeDiff, tcpDnPacket, dnvolume);	//Volume only, keep in Bytes
				strcat(pIpSession->dnVolPerSec, timeBuffer);
//				dnVolPerSec.append(std::string(timeBuffer));
				timeBuffer[0] = 0;    // Clear Internal Buffer
				pIpSession->pckTotalTimeSec = tcpDnCount;
			}
		}


		if(upvolume > 0 && strlen(pIpSession->upVolPerSec) < (VPS_MAX_LEN - 200))
		{
			timeDiff = elem.first - firstSec;
			if(timeDiff >= 0)
			{
				timeBuffer[0] = 0;
				sprintf(timeBuffer, "%d#%u#%u;", timeDiff, tcpUpPacket, upvolume);	//Volume only, keep in Bytes
				strcat(pIpSession->upVolPerSec, timeBuffer);
//				upVolPerSec.append(std::string(timeBuffer));
				timeBuffer[0] = 0;    // Clear Internal Buffer
				pIpSession->pckTotalTimeSec = tcpUpCount;
			}
		}
		dnvolume = upvolume = 0;
	}

	pIpSession->packTimeMap.clear();

	if(tcpDnCount == 0)
		strcpy(pIpSession->dnVolPerSec, "NULL");

	if(tcpUpCount == 0)
		strcpy(pIpSession->upVolPerSec, "NULL");

	/* Pick Throughput / Sec */
	pIpSession->peakSessionTP = f_pickThrPut * 8;		//Converting to bps
	pIpSession->upPeakSessionTP = f_up_pickThrPut * 8;	//Converting to bps
	pIpSession->dnPeakSessionTP = f_dn_pickThrPut * 8;	//Converting to bps

	if(packetTSCount > 0 && pIpSession->frameSize > 0)
		pIpSession->sessionTP = (pIpSession->frameSize * 8) / packetTSCount;		//Converting to bps
	else
		pIpSession->sessionTP = 0;

	if(tcpUpPacket > 0 && pIpSession->upFrameSize > 0)
		pIpSession->upSessionTP = (pIpSession->upFrameSize * 8) / tcpUpPacket;	//Converting to bps
	else
		pIpSession->upSessionTP = 0;

	if(tcpDnPacket > 0 && pIpSession->dnFrameSize > 0)
		pIpSession->dnSessionTP = (pIpSession->dnFrameSize * 8) / tcpDnPacket;	//Converting to bps
	else
		pIpSession->dnSessionTP = 0;

	if(!f_dn_pickThrPut)
		pIpSession->dnPeakSessionTP = pIpSession->dnSessionTP;

	if(!f_up_pickThrPut)
		pIpSession->upPeakSessionTP = pIpSession->upSessionTP;
}

VOID TCPFlusherUtility::buildGTPuIPCsvBuffer(ipSession *pIpSession, char *xdr)
{
	ULONG dataLatency = 0;
	ULONG sumWeightage = 0;
	xdr[0] = 0;

	/* Get Volume / Sec */
	getVolPerSec(pIpSession);

	/* Get GTPc Info */
	if(pIpSession->causeCode != FIN_NO_SESSION)
		getGTPcData(pIpSession);

	/* get URL */
	getDnsData(pIpSession);

	if((pIpSession->pshLatency > 0) && (pIpSession->payloadPacket > 0))
		ULONG dataLatency = (pIpSession->pshLatency /  pIpSession->payloadPacket);

	if(strlen(pIpSession->contentType) == 0)
		strcpy(pIpSession->contentType, "NULL");

	if(strlen(pIpSession->IMSI) == 0)
		strcpy(pIpSession->IMSI, "NA");
	if(strlen(pIpSession->MSISDN) == 0)
		strcpy(pIpSession->MSISDN, "NA");
	if(strlen(pIpSession->IMEI) == 0)
		strcpy(pIpSession->IMEI, "NA");

	if(GContainer::config->GN_PROBE)
	{
		sprintf(xdr, "%d,%d,%d,TCP,"
					 "%d,%s-%d,"
					 "%s,%s,"
					 "%u,%d,%u,%d,"
					 "%u,%d,%u,%d,"
					 "%u,%u,%d,"
					 "%d,%d,%d,"
					 "%u,%u,%u,"
					 "%d,%d,%d,"
					 "%u,%u,%u,"
					 "%llu,%llu,%d,"
					 "%u,%u,"
					 "%u,%u,%u,%u,"
					 "%u,0,0,"
					 "%d,%s,%s,"
					 "%d,%llu,"
					 "%d,%llu,"
					 "%d,%llu,"
					 "%d,%llu,"
					 "%s,%u,"
					 "%s,%s,%s,%s,%d,%s,%d,%d,%d,%d,%d,%d,%u",
					 //Last NULL is APP_IP
				IPGlobal::PROBE_ID,XDR_ID_IP_SESSION,pIpSession->protocolType,
				pIpSession->destPort, pIpSession->sessionKey, pIpSession->sliceCounter,
				pIpSession->sourceMacAddr, pIpSession->destMacAddr,
				pIpSession->sgsnIPAddr, pIpSession->sgsnPort, pIpSession->ggsnIPAddr, pIpSession->ggsnPort,
				pIpSession->sourceIP, pIpSession->sourcePort, pIpSession->destIP, pIpSession->destPort,
				pIpSession->teid_up,pIpSession->teid_dn,pIpSession->sliceCounter,
				pIpSession->frameCount, pIpSession->upFrameCount, pIpSession->dnFrameCount,
				pIpSession->frameSize, pIpSession->upFrameSize, pIpSession->dnFrameSize,
				pIpSession->payloadPacket, pIpSession->upPayloadPacket, pIpSession->dnPayloadPacket,
				pIpSession->payloadSize, pIpSession->upPayloadSize, pIpSession->dnPayloadSize,
				pIpSession->startTimeEpochNanoSec, pIpSession->endTimeEpochNanoSec, pIpSession->pckTotalTimeSec,
				pIpSession->sessionTP, pIpSession->peakSessionTP,
				pIpSession->upSessionTP, pIpSession->upPeakSessionTP, pIpSession->dnSessionTP, pIpSession->dnPeakSessionTP,
				pIpSession->synLatency,// dataLatency, sumWeightage,
				pIpSession->causeCode, pIpSession->contentType, pIpSession->dnVolPerSec,
				pIpSession->synRcv, pIpSession->synTimeEpochNanoSec,
				pIpSession->synAckRcv, pIpSession->synAckTimeEpochNanoSec,
				pIpSession->dataRcv, pIpSession->firstDataTimeEpochNanoSec,
				pIpSession->finRcv, pIpSession->finTimeEpochNanoSec,
				pIpSession->upVolPerSec, pIpSession->appIp,
				pIpSession->URL, pIpSession->IMSI, pIpSession->MSISDN, pIpSession->IMEI, pIpSession->RAT, RAT_TYPES[pIpSession->RAT].c_str(),
				pIpSession->MCC, pIpSession->MNC, pIpSession->LAC, pIpSession->CI, pIpSession->activeState,pIpSession->flushOrgId, pIpSession->flushTime);
	}
}

VOID TCPFlusherUtility::getDnsData(ipSession *pIpSession)
{
	std::string URL;
	std::string userIP_resolveIP_key;

	userIP_resolveIP_key = getDNSKey(pIpSession->sourceIP, pIpSession->destIP);

	lockDnsMap();
	getDNSUrlForIP(userIP_resolveIP_key, URL, pIpSession->sourceIP, pIpSession->destIP);
	unLockDnsMap();

	if(!URL.length())
		strcpy(pIpSession->URL, "NULL");
	else
		strcpy(pIpSession->URL, URL.c_str());

}


VOID TCPFlusherUtility::getGTPcData(ipSession *pIpSession)
{
	lockgSession();
	getGtpData(pIpSession);
	unLockgSession();
}


VOID TCPFlusherUtility::buildDnsCsvBuffer(dnsSession *pDnsSession, char *csvXDR)
{
	uint32_t dnsResTimeMilliSec = 0;

	uint128_t sTime = pDnsSession->queryStartEpochNanoSec;
	uint128_t eTime = pDnsSession->queryEndEpochNanoSec;

	csvXDR[0] = 0;

	if(eTime > 0 && sTime > 0 && (eTime > sTime)){
		if(sTime > 1000000){
			sTime = sTime / (1000 * 1000);
			if(eTime > 1000000){
				eTime = eTime / (1000 * 1000);
				dnsResTimeMilliSec = (uint32_t) (eTime - sTime);
			}
		}
	}
//	else{
//		if(pDnsSession->queryEndEpochNanoSec > 0  && pDnsSession->queryStartEpochNanoSec == 0)
//			pDnsSession->queryStartEpochNanoSec = pDnsSession->queryEndEpochNanoSec;
//	}

//	pDnsSession->URL.erase(std::remove(pDnsSession->URL.begin(), pDnsSession->URL.end(), ','), pDnsSession->URL.end());

	sprintf(csvXDR, "%d,%d,17,DNS,"
					"%u,%d,%u,%d,"
					"%s,%d,%s,"
					"%s,"
					"%llu,%llu,%u",
					IPGlobal::PROBE_ID,XDR_ID_IP_DNS_SESSION,
					pDnsSession->sourceIP, pDnsSession->sourcePort, pDnsSession->destIP, pDnsSession->destPort,
					pDnsSession->URL, pDnsSession->errorCode, pDnsSession->errorDesc,
					pDnsSession->address,
					pDnsSession->queryStartEpochNanoSec, pDnsSession->queryEndEpochNanoSec, dnsResTimeMilliSec);
}

void TCPFlusherUtility::createOTRXdr(ipSession *pIpSession, string& xdr)
{

}

VOID TCPFlusherUtility::openDNSXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
{
//	char *filePath = (char *)malloc(300);
	TCHAR filePath[300];
//	filePath[0] = 0;

	sprintf(filePath, "%s%s/%s_%d-%02d-%02d-%02d-%02d.csv",
					GContainer::config->XDR_DIR.c_str(),
					prefix.c_str(),
					prefix.c_str(),
					currentYear,
					currentMonth,
					currentDay,
					currentHour,
					currentMin);
	IPGlobal::dnsCsvHandler.open((char *)filePath, ios :: out | ios :: app);

	if(IPGlobal::dnsCsvHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] DNS Xdr file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] DNS Xdr file Open Success. !!!", filePath);
	}

//	filePath[0] = 0;

//	delete(filePath);
}

VOID TCPFlusherUtility::closeDNSXdrFile()
{
	IPGlobal::dnsCsvHandler.close();
}

//VOID TCPFlusherUtility::getGtpData(GTPUserInfo *pGtpData, ipXdrData *pIpXdrData)
//{
//	GTPSession *pGlbSession = NULL;
//	pGtpUserInfo->reset();
//
////	GTPStats::gtp_get_imsi_req_cnt++;
//
//	if(pIpXdrData->teid_up > 0)
//		pGlbSession = globalLookup(pIpXdrData->teid_up);
//
//	if(pGlbSession == NULL)
//	{
//		if(pIpXdrData->teid_dn > 0)
//			pGlbSession = globalLookup(pIpXdrData->teid_dn);
//	}
//
//	if(pGlbSession != NULL) {
////			GTPStats::gtp_get_imsi_suc_cnt++;
//			pGtpData->imsi = std::string(pGlbSession->IMSI);
//			pGtpData->msisdn = std::string(pGlbSession->MSISDN);
//			pGtpData->imei = std::string(pGlbSession->IMEI);
//			pGtpData->rat = pGlbSession->RAT;
//			pGtpData->ratDesc = std::string(RAT_TYPES[pGlbSession->RAT]);
//			pGtpData->MCC = pGlbSession->MCC;
//			pGtpData->MNC = pGlbSession->MNC;
//			pGtpData->LAC = pGlbSession->LAC;
//			pGtpData->CI = pGlbSession->CI;
//			pGtpData->activeState = pGlbSession->active_session;
//
//			pGlbSession->lastActivityTime = pIpXdrData->lastActivityTimeEpohSec;
//			pGlbSession->lastActivityTimeGtpu = pIpXdrData->lastActivityTimeEpohSec;
//
//			GTPStore::GTPGlb_IMSI_MAP[pGtpData->imsi] = 1;
//	}
//}

VOID TCPFlusherUtility::getGtpData(ipSession *pIpSession)
{
	GTPSession *pGlbSession = NULL;

	if(pIpSession->teid_up > 0)
		pGlbSession = globalLookup(pIpSession->teid_up);

	if(pGlbSession == NULL)
	{
		if(pIpSession->teid_dn > 0)
			pGlbSession = globalLookup(pIpSession->teid_dn);
	}

	if(pGlbSession != NULL) {
//			GTPStats::gtp_get_imsi_suc_cnt++;
			strcpy(pIpSession->IMSI, pGlbSession->IMSI);
			strcpy(pIpSession->MSISDN, pGlbSession->MSISDN);
			strcpy(pIpSession->IMEI, pGlbSession->IMEI);
			pIpSession->RAT = pGlbSession->RAT;
			pIpSession->MCC = pGlbSession->MCC;
			pIpSession->MNC = pGlbSession->MNC;
			pIpSession->LAC = pGlbSession->LAC;
			pIpSession->CI = pGlbSession->CI;
			pIpSession->activeState = pGlbSession->active_session;

			pGlbSession->lastActivityTime = pIpSession->lastActivityTimeEpohSec;
			pGlbSession->lastActivityTimeGtpu = pIpSession->lastActivityTimeEpohSec;

			GTPStore::GTPGlb_IMSI_MAP[pIpSession->IMSI] = 1;
	}
}

GTPSession* TCPFlusherUtility::globalLookup(const uint32_t tunnelId)
{
	std::map<uint32_t, int>::iterator itr;

	itr = GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(tunnelId)].find(tunnelId);
	if (itr != GTPStore::GTPGlbMap_DATA_UP[INDEX_TEID(tunnelId)].end()) {
		int arrid = itr->second / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
		int elemid = itr->second % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
		return GTPStore::GTPGlbSession[arrid][elemid];
	}

	itr = GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(tunnelId)].find(tunnelId);
	if (itr != GTPStore::GTPGlbMap_DATA_DW[INDEX_TEID(tunnelId)].end()) {
		int arrid = itr->second / GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
		int elemid = itr->second % GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS;
		return GTPStore::GTPGlbSession[arrid][elemid];
	}

	std::map<uint32_t, GTPSession>::iterator itrLku;
	itrLku = GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(tunnelId)].find(tunnelId);
	if (itrLku != GTPStore::GTPGlbMap_LKU_DATA_UP[INDEX_TEID(tunnelId)].end()) {
		return &itrLku->second;
	}

	itrLku = GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(tunnelId)].find(tunnelId);
	if (itrLku != GTPStore::GTPGlbMap_LKU_DATA_DW[INDEX_TEID(tunnelId)].end()) {
		return &itrLku->second;
	}

	return (NULL);
}


//VOID TCPFlusherUtility::initializeDnsFlushRepository(){
//
//	IPFlushRepository::dnsFlushFreeBitPosMax = DNS_FLUSH_POOL_ARRAY_ELEMENTS * DNS_FLUSH_POOL_ARRAY_SIZE;
//	long perTimeIndexPerSMRecords = 50000;
//
//	printf("GTPFlusher            Initializing DNS Flusher Repository [%'08lu] x 4 ...\n", IPFlushRepository::dnsFlushFreeBitPosMax);
//	for(int n = 0; n < DNS_FLUSH_POOL_ARRAY_SIZE; n++){
//
//		IPFlushRepository::DNSFlushRepoFlags_sm_0[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_1[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_2[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_3[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_4[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_5[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_6[n].reset();
//		IPFlushRepository::DNSFlushRepoFlags_sm_7[n].reset();
//
//
//		IPFlushRepository::dnsFlushRepository_sm_0[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_1[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_2[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_3[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_4[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_5[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_6[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//		IPFlushRepository::dnsFlushRepository_sm_7[n].reserve(DNS_FLUSH_POOL_ARRAY_ELEMENTS);
//
//		for(int i = 0; i < DNS_FLUSH_POOL_ARRAY_ELEMENTS; i++)
//		{
//			IPFlushRepository::dnsFlushRepository_sm_0[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_1[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_2[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_3[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_4[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_5[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_6[n][i] = new dnsSession();
//			IPFlushRepository::dnsFlushRepository_sm_7[n][i] = new dnsSession();
//
//		}
//	}
//	printf("GTPFlusher            Initializing DNS Flusher Repository [%'08lu] x 4 ...Completed\n", IPFlushRepository::dnsFlushFreeBitPosMax);
//
//	printf("GTPFlusher            Initializing DNS Flusher TimeIndex Map [%'08lu] x 4 x 10 ...\n", perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_0_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_1_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_1_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_2_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_2_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_3_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_3_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_4_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_4_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_5_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_5_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_6_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_6_t_9.reserve(perTimeIndexPerSMRecords);
//
//	IPFlushRepository::dnsFlushMap_sm_7_t_0.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_1.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_2.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_3.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_4.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_5.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_6.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_7.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_8.reserve(perTimeIndexPerSMRecords);
//	IPFlushRepository::dnsFlushMap_sm_7_t_9.reserve(perTimeIndexPerSMRecords);
//
//	printf("GTPFlusher            Initializing DNS Flusher TimeIndex Map [%'08lu] x 4 x 10 ...Completed\n", perTimeIndexPerSMRecords);
//}
