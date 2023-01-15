/*
 * DnsData.h
 *
 *  Created on: 11-Jun-2016
 *      Author: deb
 */

#ifndef INC_DNSDATA_H_
#define INC_DNSDATA_H_

#include <string.h>    //strlen
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "Log.h"

#include "BaseConfig.h"
#include "IPGlobal.h"
#include "TCPUDPGlobal.h"

class DnsData : public BaseConfig {
	private:
		VOID	lockDnsMap();
		VOID	unLockDnsMap();

	public:
		DnsData();
		~DnsData();

		VOID 		updateDns(string key, uint32_t userip, uint32_t resolvedip, char *url, uint64_t epochTimeSec);
		VOID 		getDNSUrlForIP(string str, string& url, uint32_t sIp, uint32_t dIp);
//		VOID 		deleteDns(int processedMin, ULONG epochTimeMicroSec);
//		VOID 		dumpData();
		string 		getDNSKey(uint32_t destAddrLong, uint32_t sourceAddrLong);
//		uint32_t	getDNSResolvedLookupSize();
};

#endif /* INC_DNSDATA_H_ */
