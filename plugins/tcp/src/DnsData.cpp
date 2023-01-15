/*
 * DnsData.cpp
 *
 *  Created on: 11-Jun-2016
 *      Author: debashis
 */

#include "DnsData.h"

using namespace std;

DnsData::DnsData()
{
	this->_name = "DnsData";
	this->setLogLevel(Log::theLog().level());
}

DnsData::~DnsData()
{}

VOID DnsData::lockDnsMap()
{
	    pthread_mutex_lock(&mapDnsLock::lockCount);
	    while (mapDnsLock::count == 0)
	        pthread_cond_wait(&mapDnsLock::nonzero, &mapDnsLock::lockCount);
	    mapDnsLock::count = mapDnsLock::count - 1;
	    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID DnsData::unLockDnsMap()
{
    pthread_mutex_lock(&mapDnsLock::lockCount);
    if (mapDnsLock::count == 0)
        pthread_cond_signal(&mapDnsLock::nonzero);
    mapDnsLock::count = mapDnsLock::count + 1;
    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID DnsData::updateDns(string key, uint32_t userip, uint32_t resolvedip, char *url, uint64_t epochTimeSec)
{
//	std::string temp;
	int index = userip % 10;


	//Update DatabaseMap for userip vs dns ip
//	temp = key[0];
//	index = atoi((const char *)temp.c_str());

//	if(epochTimeSec == 0) printf("updateDns [%s]| [%u]| [%s]", key.c_str(), resolvedip, url);

	switch(index)
	{
		case 0:
				DNSGlobal::dnsDatabaseMap_0[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_0[key].URL, url);
				DNSGlobal::dnsDatabaseMap_0[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 1:
				DNSGlobal::dnsDatabaseMap_1[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_1[key].URL, url);
				DNSGlobal::dnsDatabaseMap_1[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 2:
				DNSGlobal::dnsDatabaseMap_2[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_2[key].URL, url);
				DNSGlobal::dnsDatabaseMap_2[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 3:
				DNSGlobal::dnsDatabaseMap_3[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_3[key].URL, url);
				DNSGlobal::dnsDatabaseMap_3[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 4:
				DNSGlobal::dnsDatabaseMap_4[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_4[key].URL, url);
				DNSGlobal::dnsDatabaseMap_4[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 5:
				DNSGlobal::dnsDatabaseMap_5[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_5[key].URL, url);
				DNSGlobal::dnsDatabaseMap_5[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 6:
				DNSGlobal::dnsDatabaseMap_6[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_6[key].URL, url);
				DNSGlobal::dnsDatabaseMap_6[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 7:
				DNSGlobal::dnsDatabaseMap_7[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_7[key].URL, url);
				DNSGlobal::dnsDatabaseMap_7[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 8:
				DNSGlobal::dnsDatabaseMap_8[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_8[key].URL, url);
				DNSGlobal::dnsDatabaseMap_8[key].pckLastTimeEpcohSec = epochTimeSec;
				break;

		case 9:
				DNSGlobal::dnsDatabaseMap_9[key].address = resolvedip;
				strcpy(DNSGlobal::dnsDatabaseMap_9[key].URL, url);
				DNSGlobal::dnsDatabaseMap_9[key].pckLastTimeEpcohSec = epochTimeSec;
				break;
	}

	//Now update Dns Lookup Map
	index = resolvedip % 10;
	switch(index)
	{
		case 0:
				DNSGlobal::dnsLookUpMap_0[resolvedip] = std::string(url);
				break;

		case 1:
				DNSGlobal::dnsLookUpMap_1[resolvedip] = std::string(url);
				break;

		case 2:
				DNSGlobal::dnsLookUpMap_2[resolvedip] = std::string(url);
				break;

		case 3:
				DNSGlobal::dnsLookUpMap_3[resolvedip] = std::string(url);
				break;

		case 4:
				DNSGlobal::dnsLookUpMap_4[resolvedip] = std::string(url);
				break;

		case 5:
				DNSGlobal::dnsLookUpMap_5[resolvedip] = std::string(url);
				break;

		case 6:
				DNSGlobal::dnsLookUpMap_6[resolvedip] = std::string(url);
				break;

		case 7:
				DNSGlobal::dnsLookUpMap_7[resolvedip] = std::string(url);
				break;

		case 8:
				DNSGlobal::dnsLookUpMap_8[resolvedip] = std::string(url);
				break;

		case 9:
				DNSGlobal::dnsLookUpMap_9[resolvedip] = std::string(url);
				break;
	}

}

VOID DnsData::getDNSUrlForIP(string key, string& url, uint32_t sIp, uint32_t dIp)
{
//	std::string temp;
	int index = sIp % 10;

	//First search in Dns Database map
//	temp = key[0];
//	index = atoi((const char *)temp.c_str());

	switch(index)
	{
		case 0:
			{
				std::map<string, dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_0.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_0.end())
				{
					DNSGlobal::dnsDatabaseMap_0[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 1:
			{
				std::map<string, dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_1.find(key);

				if( itSp != DNSGlobal::dnsDatabaseMap_1.end())
				{
					DNSGlobal::dnsDatabaseMap_1[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 2:
			{
				std::map<string, dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_2.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_2.end())
				{
					DNSGlobal::dnsDatabaseMap_2[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 3:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_3.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_3.end())
				{
					DNSGlobal::dnsDatabaseMap_3[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 4:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_4.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_4.end())
				{
					DNSGlobal::dnsDatabaseMap_4[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 5:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_5.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_5.end())
				{
					DNSGlobal::dnsDatabaseMap_5[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 6:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_6.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_6.end())
				{
					DNSGlobal::dnsDatabaseMap_6[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 7:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_7.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_7.end())
				{
					DNSGlobal::dnsDatabaseMap_7[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 8:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_8.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_8.end())
				{
					DNSGlobal::dnsDatabaseMap_8[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;

		case 9:
			{
				std::map<string,dnsUrl>::iterator itSp = DNSGlobal::dnsDatabaseMap_9.find(key);
				if( itSp != DNSGlobal::dnsDatabaseMap_9.end())
				{
					DNSGlobal::dnsDatabaseMap_9[itSp->first].pckLastTimeEpcohSec = getCurrentEpochSeconds();
					url = itSp->second.URL;
					return;
				}
			}
			break;
	}


	//If not found search in our global look up map
	index = dIp % 10;
	switch(index)
	{
		case 0:
			{
				std::map<uint32_t, string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_0.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_0.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 1:
			{
				std::map<uint32_t, string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_1.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_1.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 2:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_2.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_2.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 3:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_3.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_3.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 4:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_4.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_4.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 5:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_5.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_5.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 6:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_6.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_6.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 7:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_7.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_7.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 8:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_8.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_8.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

		case 9:
			{
				std::map<uint32_t,string>::iterator itSp1 = DNSGlobal::dnsLookUpMap_9.find(dIp);
				if( itSp1 != DNSGlobal::dnsLookUpMap_9.end())
				{
					url = itSp1->second;
					return;
				}
			}
			break;

	}


}

//VOID DnsData::dumpData()
//{
//	uint32_t counter = 0;
//	std::string data;
//
//	for(auto itrDnsUrl : dnsLookUpMap_0)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_1)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_2)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_3)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_4)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_5)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_6)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_7)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_8)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//	for(auto itrDnsUrl : dnsLookUpMap_9)
//	{
//		data.append(itrDnsUrl.first)
//			.append(",")
//			.append(itrDnsUrl.second);
//		DnsDataMap::dailyDnsDump[counter] = data;
//		counter++;
//		data.clear();
//	}
//}

//VOID DnsData::deleteDns(int processedMin, ULONG epochTimeMicroSec)
//{
//	int recordCount = 0;
//	int tCount = 0;
//	int tRecords = 0;
//
//	string ip;
//	string userSessionList[MAX_CLEAN_COUNT];
//
//	tRecords += DNSGlobal::dnsDatabaseMap_0.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_1.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_2.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_3.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_4.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_5.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_6.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_7.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_8.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_9.size();
//
//	TheLog_nc_v2(Log::Info, "TCPCleanSession", " User DNS Session clean started for minute [%02d] having [%d] records", processedMin, tRecords);
//
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_0)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_0.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_1)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_1.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_2)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_2.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_3)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_3.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_4)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_4.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_5)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_5.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_6)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_6.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_7)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_7.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_8)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_8.erase(ip);
//		userSessionList[n] = "";
//	}
//
//	recordCount = 0;
//	for(auto itrDnsUrl : DNSGlobal::dnsDatabaseMap_9)
//	{
//		if((epochTimeMicroSec - itrDnsUrl.second.pckLastTimeEpcohNanoSec) > 600 * 1000000)
//		{
//			std::string ip = itrDnsUrl.first;
//			userSessionList[recordCount] = ip;
//			recordCount++;
//			tCount++;
//			if(recordCount >= MAX_CLEAN_COUNT)
//				break;
//		}
//	}
//	//Now erase all sessions picked up
//	for(int n=0; n< recordCount; n++){
//		ip = userSessionList[n];
//		DNSGlobal::dnsDatabaseMap_9.erase(ip);
//		userSessionList[n] = "";
//	}
//
//
//	tRecords = 0;
//	tRecords += DNSGlobal::dnsDatabaseMap_0.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_1.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_2.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_3.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_4.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_5.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_6.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_7.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_8.size();
//	tRecords += DNSGlobal::dnsDatabaseMap_9.size();
//
//	TheLog_nc_v3(Log::Info, "TCPCleanSession", " User DNS Session clean completed for minute [%02d] for [%d] records, new size [%ld]", processedMin, tCount, tRecords);
//}

string DnsData::getDNSKey(uint32_t destAddrLong, uint32_t sourceAddrLong)
{
	char dnsKey[25];
	sprintf(dnsKey,"%010u-%010u",destAddrLong,sourceAddrLong);
	return std::string(dnsKey);
}

//uint32_t DnsData::getDNSResolvedLookupSize()
//{
//	lockDnsMap();
//	uint32_t totalSize = DNSGlobal::dnsLookUpMap_0.size() +
//						 DNSGlobal::dnsLookUpMap_1.size() +
//						 DNSGlobal::dnsLookUpMap_2.size() +
//						 DNSGlobal::dnsLookUpMap_3.size() +
//						 DNSGlobal::dnsLookUpMap_4.size() +
//						 DNSGlobal::dnsLookUpMap_5.size() +
//						 DNSGlobal::dnsLookUpMap_6.size() +
//						 DNSGlobal::dnsLookUpMap_7.size() +
//						 DNSGlobal::dnsLookUpMap_9.size();
//	unLockDnsMap();
//
//	return totalSize;
//}
