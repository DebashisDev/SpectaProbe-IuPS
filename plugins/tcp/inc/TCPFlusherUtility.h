/*
 * TCPFlusherUtility.h
 *
 *  Created on: Dec 21, 2016
 *      Author: Deb
 */

#ifndef PLUGINS_TCP_SRC_TCPFLUSHERUTILITY_H_
#define PLUGINS_TCP_SRC_TCPFLUSHERUTILITY_H_

#include <unistd.h>
#include "IPGlobal.h"
#include "TCPUDPGlobal.h"
#include "DnsData.h"
#include "ProbeUtility.h"
#include "GTPGlobal.h"

using namespace std;

class TCPFlusherUtility : public DnsData{
	private:
			GTPUserInfo 		  *pGtpUserInfo;
			GTPSession* globalLookup(const uint32_t tunnelId);
//			VOID 		getGtpData(GTPUserInfo *pGtpData, ipXdrData *pIpXdrData);
			VOID 		getGtpData(ipSession *pIpSession);
			VOID 		createTCPXdr(ipSession *pIpSession, char *xdr, string upVol, string dnVol);
			VOID 		createUDPXdr(ipSession *pIpSession, char *xdr, string upVol, string dnVol);
			VOID 		createOTRXdr(ipSession *pIpSession, string& xdr);
			VOID		getVolPerSec(ipSession *pIpSession);

			VOID lockDnsMap();
			VOID unLockDnsMap();

			VOID lockgSession();
			VOID unLockgSession();
	public:
			TCPFlusherUtility();
			~TCPFlusherUtility();

			VOID 		buildGTPuIPCsvBuffer(ipSession *pIpSession, char *csvXDR);
//			VOID 		getDnsData(ipSession *pIpSession);
			VOID 		getDnsData(ipSession *pIpSession);
			VOID 		getGTPcData(ipSession *pIpSession);
			VOID 		buildDnsCsvBuffer(dnsSession *pDnsSession, char *csvXDR);
			static VOID	openDNSXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
			static VOID closeDNSXdrFile();
//			VOID		initializeIPFlushRepository();
//			VOID		initializeDnsFlushRepository();
};

#endif /* PLUGINS_TCP_SRC_TCPFLUSHERUTILITY_H_ */
