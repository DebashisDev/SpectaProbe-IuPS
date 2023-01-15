/*
 * GxGyConfig.cpp
 *
 *  Created on: Oct 13, 2016
 *      Author: Debashis
 */

#include "GXConfig.h"
#include "IPGlobal.h"

GxConfig::GxConfig() {
	GX_INTERFACE_TYPE = 0;
	GX_INTERFACE_NAME.clear();
	GX_SF_VIRTUAL_INTERFACES = 0;
	GX_FLUSH_FLAG = false;
	GX_FLUSH_PORT.clear();
	GX_WRITE_XDR = false;
	GX_FILE_PREFIX.clear();
	GX_IDLE_SESSION_TIMEOUT_IN_SEC = 0;
	GX_ACTIVE_SESSION_TIMEOUT_IN_SEC = 0;
	GX_SESSION_PACKET_LIMIT = 0;
}

GxConfig::~GxConfig() {
}

void GxConfig::loadGXConfig(ifstream& fp)
{
	string Key, Value, interfaceName;

	/* ** GN Configuration file ** */
	printf("  Loading GX  configurations...\n");

	while(!fp.eof())
	{
		fp >> Key;
		if(Key.compare("GX_INTERFACE_TYPE") == 0)
		{
			fp >> Value;
			GX_INTERFACE_TYPE = atoi(Value.c_str());
			switch(GX_INTERFACE_TYPE)
			{
				case 0:
					interfaceName.assign("PCAP");
					break;

				case 1:
					interfaceName.assign("ETH");
					break;

				case 2:
					interfaceName.assign("SOLARFLARE");
					break;

				default:
					interfaceName.assign("UNKNOWN");
					break;
			}

			printf("\tGX_INTERFACE_TYPE\t\t:: %s\n", interfaceName.c_str());
		}
		else if(Key.compare("GX_INTERFACE_NAME") == 0)
		{
				fp >> Value;
				GX_INTERFACE_NAME = Value;
				printf("\tGX_INTERFACE_NAME\t\t:: %s\n", GX_INTERFACE_NAME.c_str());
		}
		else if(Key.compare("GX_SF_VIRTUAL_INTERFACES") == 0)
		{
				fp >> Value;
				GX_SF_VIRTUAL_INTERFACES = atoi(Value.c_str());;
				printf("\tGX_SF_VIRTUAL_INTERFACES\t:: %d\n", GX_SF_VIRTUAL_INTERFACES);
		}
		else if(Key.compare("GX_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GX_FLUSH_FLAG = true;
			else
				GX_FLUSH_FLAG = false;
			printf("\tGX_FLUSH_FLAG\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GX_FLUSH_PORT") == 0)
		{
				fp >> Value;
				GX_FLUSH_PORT = Value;
				printf("\tGX_GTPC_FLUSH_PORT\t\t:: %s\n", GX_FLUSH_PORT.c_str());
		}
		else if(Key.compare("GX_FILE_PREFIX") == 0)
		{
				fp >> Value;
				GX_FILE_PREFIX = Value;
				printf("\tGX_FILE_PREFIX\t\t:: %s\n", GX_FILE_PREFIX.c_str());
		}
		else if(Key.compare("GX_WRITE_XDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GX_WRITE_XDR = true;
			else
				GX_WRITE_XDR = false;
			printf("\tGX_WRITE_XDR\t\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GX_IDLE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			GX_IDLE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str()) * 1000000;
			printf("\tGX_IDLE_SESSION_TIMEOUT_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		else if(Key.compare("GX_IDLE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			GX_IDLE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str()) * 1000000;
			printf("\tGX_IDLE_SESSION_TIMEOUT_IN_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		else if(Key.compare("GX_ACTIVE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			GX_ACTIVE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str()) * 1000000;
			printf("\tGX_ACTIVE_SESSION_TIMEOUT_IN_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		else if(Key.compare("GX_SESSION_PACKET_LIMIT") == 0)
		{
			fp >> Value;
			GX_SESSION_PACKET_LIMIT = atoi(Value.c_str());
			printf("\tGX_SESSION_PACKET_LIMIT\t\t:: %d\n", GX_SESSION_PACKET_LIMIT);
		}
	}
}

