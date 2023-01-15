/*
 * BroadBandConfig.cpp
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#include "BroadBandConfig.h"
#include "IPGlobal.h"

#include <unistd.h>
#include <string>

BroadBandConfig::BroadBandConfig() {
	BROADBAND_INTERFACE_TYPE = false;
	BROADBAND_WRITE_XDR = false;
	BROADBAND_IP_FLUSH_FLAG = false;
	BROADBAND_DNS_FLUSH_FLAG = false;
	BROADBAND_IDLE_SESSION_TIMEOUT_IN_SEC = 0;
	BROADBAND_ACTIVE_SESSION_TIMEOUT_IN_SEC = 0;
	BROADBAND_SESSION_PACKET_LIMIT = 0;
	BROADBAND_SF_VIRTUAL_INTERFACES = 0;
	BROADBAND_QUEUE = false;
}

BroadBandConfig::~BroadBandConfig() {
}

void BroadBandConfig::loadConfig(ifstream& fp)
{
	string Key, Value, interface;

	/* ** BroadBand Configuration file ** */
	printf("  Loading Broad-Band Configurations...\n");

	while(!fp.eof())
	{
		fp >> Key;
		if(Key.compare("BROADBAND_INTERFACE_TYPE") == 0)
		{
			fp >> Value;
			BROADBAND_INTERFACE_TYPE = atoi(Value.c_str());
			switch(BROADBAND_INTERFACE_TYPE)
			{
				case 0:
					interface.assign("PCAP");
					break;

				case 1:
					interface.assign("ETH");
					break;

				case 2:
					interface.assign("SOLARFLARE");
					break;

				default:
					interface.assign("UNKNOWN");
					break;
			}
			printf("\tINTERFACE_TYPE\t\t\t:: %s\n", interface.c_str());
		}
		else if(Key.compare("BROADBAND_INTERFACE_NAME") == 0)
		{
				fp >> Value;
				BROADBAND_INTERFACE_NAME = Value;
				printf("\tINTERFACE_NAME\t\t\t:: %s\n", BROADBAND_INTERFACE_NAME.c_str());
		}
		else if(Key.compare("BROADBAND_SF_VIRTUAL_INTERFACES") == 0)
		{
				fp >> Value;
				BROADBAND_SF_VIRTUAL_INTERFACES = atoi(Value.c_str());;
				printf("\tSF_VIRTUAL_INTERFACES\t\t:: %d\n", BROADBAND_SF_VIRTUAL_INTERFACES);
		}
		if(Key.compare("BROADBAND_IP_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				BROADBAND_IP_FLUSH_FLAG = true;
			else
				BROADBAND_IP_FLUSH_FLAG = false;
			printf("\tIP_FLUSH_FLAG\t\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("BROADBAND_IP_FLUSH_PORT") == 0)
		{
				fp >> Value;
				BROADBAND_IP_FLUSH_PORT = Value;
				printf("\tIP_FLUSH_PORT\t\t\t:: %s\n", BROADBAND_IP_FLUSH_PORT.c_str());
		}
		if(Key.compare("BROADBAND_DNS_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				BROADBAND_DNS_FLUSH_FLAG = true;
			else
				BROADBAND_DNS_FLUSH_FLAG = false;
			printf("\tIP_FLUSH_FLAG\t\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("BROADBAND_DNS_FLUSH_PORT") == 0)
		{
				fp >> Value;
				BROADBAND_DNS_FLUSH_PORT = Value;
				printf("\tDNS_FLUSH_PORT\t\t\t:: %s\n", BROADBAND_DNS_FLUSH_PORT.c_str());
		}
		if(Key.compare("BROADBAND_QUEUE") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				BROADBAND_QUEUE = true;
			else
				BROADBAND_QUEUE = false;
			printf("\tBROADBAND_QUEUE\t\t\t:: %s\n", Value.c_str());
		}
		if(Key.compare("BROADBAND_WRITE_XDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				BROADBAND_WRITE_XDR = true;
			else
				BROADBAND_WRITE_XDR = false;
			printf("\tWRITE_XDR\t\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("BROADBAND_FILE_PREFIX") == 0)
		{
				fp >> Value;
				BROADBAND_FILE_PREFIX = Value;
				printf("\tFILE_PREFIX\t\t\t:: %s\n", BROADBAND_FILE_PREFIX.c_str());
		}
		if(Key.compare("BROADBAND_IDLE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			BROADBAND_IDLE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str()) * 1000000;
			printf("\tIDLE_SESSION_TIMEOUT_IN_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		if(Key.compare("BROADBAND_ACTIVE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			BROADBAND_ACTIVE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str()) * 1000000;
			printf("\tACTIVE_SESSION_TIMEOUT_IN_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		if(Key.compare("BROADBAND_SESSION_PACKET_LIMIT") == 0)
		{
			fp >> Value;
			BROADBAND_SESSION_PACKET_LIMIT = atoi(Value.c_str());
			printf("\tSESSION_PACKET_LIMIT\t\t:: %d\n", BROADBAND_SESSION_PACKET_LIMIT);
		}
	}

	// Read IP Range List from File and store in Vector

	std::string range, mask;
	int i = 0;

	TCHAR configPath[100];

	configPath[0] = 0;

	sprintf(configPath, "%s/%s", GConstant::probeBaseDir, "ipRange.txt");
	ifstream ipRangeFile(configPath);

#if 1
	while (ipRangeFile >> range) {
	        IPGlobal::ipRange.push_back(range);
	}

	ipRangeFile.close();

    for (unsigned n = 0; n < IPGlobal::ipRange.size(); ++n) {
       printf("  IP Range        : %s\n", IPGlobal::ipRange.at(n).c_str());
    }
#endif

#if 0
	while(!ipRangeFile.eof())
	{
		range.clear(); mask.clear();

		ipRangeFile >> range;
		ipRangeFile >> mask;

		ipRange::ipRange[i].startIp = (int) strtol(range.c_str(), nullptr, 0);
		ipRange::ipRange[i].mask = (int) strtol(mask.c_str(), nullptr, 0);

		if(ipRange::ipRange[i].startIp == 0&& ipRange::ipRange[i].mask == 0)
			break;

		i++;
	}

	ipRange::totalIps = i;

	for (unsigned j = 0; j < ipRange::totalIps; ++j)
	{
		printf("Total :: %d| Start IP: %x| Mask: %d\n", ipRange::totalIps, ipRange::ipRange[j].startIp, ipRange::ipRange[j].mask);

	}

	sleep(5);
#endif
}
