/*
 * GTPConfig.cpp
 *
 *  Created on: 04-Aug-2016
 *      Author: deb
 */

#include "IPGlobal.h"
#include "GTPConfig.h"


GTPConfig::GTPConfig() {
	GN_INTERFACE_TYPE = 0;
	GN_INTERFACE_NAME.clear();

	GN_GTPC_MAX_SESSIONS = 0;

	GN_GTPC_FLUSH_FLAG = 0;
	GN_GTPC_FLUSH_PORT.clear();
	GN_GTPC_WRITE_XDR = false;
	GN_GTPC_FILE_PREFIX.clear();

	GN_GTPU_FLUSH_FLAG = false;
	GN_GTPU_FLUSH_PORT.clear();
	GN_GTPU_WRITE_XDR = false;
	GN_GTPU_FILE_PREFIX.clear();

	GN_DNS_WRITE_XDR = false;
	GN_DNS_FILE_PREFIX.clear();
	GN_DNS_FLUSH_FLAG = false;
	GN_DNS_FLUSH_PORT.clear();
	GN_GTPU_ZMQ_FLUSER_TPS = 0;
	GTPC_FLUSH_MAP_REPO_SIZE = 0;
	GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE = 0;

	GN_GTPU_IDLE_SESSION_TIMEOUT_IN_SEC = 0;
	GN_GTPU_ACTIVE_SESSION_TIMEOUT_IN_SEC = 0;
	GN_GTPU_SESSION_PACKET_LIMIT = 0;

	GN_GTPC_MAX_SESSIONS = 0;
	GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC = 0;
	GN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC = 3600;
}

GTPConfig::~GTPConfig() {
}

void GTPConfig::loadGNConfig(ifstream& fp)
{
	std::string Key, Value, channel;

	/* ** GN Configuration file ** */
	printf("\n");

	while(!fp.eof())
	{
		fp >> Key;
		Value.clear();
		if(Key.compare("GN_SESSION_MANAGER_INSTANCES") == 0)
		{
			fp >> Value;
			IPGlobal::GN_SESSION_MANAGER_INSTANCES = atoi(Value.c_str());
			printf("	GN_SESSION_MANAGER_INSTANCES		:: %d\n", IPGlobal::GN_SESSION_MANAGER_INSTANCES);
		}
		else if(Key.compare("GN_SESSION_MANAGER_CPU_CORE") == 0)
		{
			fp >> Value;
			char * pch1;
			int cnt = 0;
			pch1 = strtok((char *)Value.c_str(),",");
			while (pch1 != NULL)
			{
				IPGlobal::GN_SESSION_MANAGER_CPU_CORE[cnt] = atoi(pch1);
				printf("\tGN_SESSION_MANAGER_CPU_CORE[%d]     	:: %d\n", cnt, IPGlobal::GN_SESSION_MANAGER_CPU_CORE[cnt]);
				pch1 = strtok (NULL, ",");
				cnt++;
			}
		}
		else if(Key.compare("GTPC_FLUSH_MAP_REPO_SIZE") == 0)
		{
				fp >> Value;
				GTPC_FLUSH_MAP_REPO_SIZE = atoi(Value.c_str());;
				printf("\tGTPC_FLUSH_MAP_REPO_SIZE\t:: %d\n", GTPC_FLUSH_MAP_REPO_SIZE);
		}

		else if(Key.compare("GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE") == 0)
		{
				fp >> Value;
				GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE = atoi(Value.c_str());;
				printf("\tGTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE\t:: %d\n", GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
		}
		else if(Key.compare("GN_GTPC_MAX_SESSIONS") == 0)
		{
			fp >> Value;
			GN_GTPC_MAX_SESSIONS = atoi(Value.c_str());;
			printf("\tGN_GTPC_MAX_SESSIONS\t\t:: %d\n", GN_GTPC_MAX_SESSIONS);
		}
		else if(Key.compare("GN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC") == 0)
		{
			fp >> Value;
			GN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC = atoi(Value.c_str());;
			printf("\tGN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC\t:: %d\n", GN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC);
		}
		/* ************ GTPC ************ */
		else if(Key.compare("GN_GTPC_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GN_GTPC_FLUSH_FLAG = true;
			else
				GN_GTPC_FLUSH_FLAG = false;
			printf("\tGN_GTPC_FLUSH_FLAG\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPC_WRITE_XDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GN_GTPC_WRITE_XDR = true;
			else
				GN_GTPC_WRITE_XDR = false;
			printf("\tGN_GTPC_WRITE_XDR\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPC_FLUSH_PORT") == 0)
		{
				fp >> Value;
				GN_GTPC_FLUSH_PORT = Value;
				printf("\tGN_GTPC_FLUSH_PORT\t\t:: %s\n", GN_GTPC_FLUSH_PORT.c_str());
		}
		else if(Key.compare("GN_GTPC_FILE_PREFIX") == 0)
		{
				fp >> Value;
				GN_GTPC_FILE_PREFIX = Value;
				printf("\tGN_GTPC_FILE_PREFIX\t\t:: %s\n", GN_GTPC_FILE_PREFIX.c_str());
		}
		/* ************ GTPU ************ */
		else if(Key.compare("GN_GTPU_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GN_GTPU_FLUSH_FLAG = true;
			else
				GN_GTPU_FLUSH_FLAG = false;
			printf("\tGN_GTPU_FLUSH_FLAG\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPU_WRITE_XDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GN_GTPU_WRITE_XDR = true;
			else
				GN_GTPU_WRITE_XDR = false;
			printf("\tGN_GTPU_WRITE_XDR\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPU_FLUSH_PORT") == 0)
		{
				fp >> Value;
				GN_GTPU_FLUSH_PORT = Value;
				printf("\tGN_GTPU_FLUSH_PORT\t\t:: %s\n", GN_GTPU_FLUSH_PORT.c_str());
		}
		else if(Key.compare("GN_GTPU_FILE_PREFIX") == 0)
		{
				fp >> Value;
				GN_GTPU_FILE_PREFIX = Value;
				printf("\tGN_GTPU_FILE_PREFIX\t\t:: %s\n", GN_GTPU_FILE_PREFIX.c_str());
		}
		else if(Key.compare("GN_GTPU_FLUSHER_NO") == 0)
		{
				fp >> Value;
				IPGlobal::GN_GTPU_FLUSHER_NO = atoi(Value.c_str());
				printf("\t\tGN_GTPU_FLUSHER_NO\t\t:: %d\n", IPGlobal::GN_GTPU_FLUSHER_NO);
		}
		else if(Key.compare("GN_GTPU_FLUSHER_CPU_CORE") == 0)
		{
			fp >> Value;
			char * pch1;
			int cnt = 0;
			pch1 = strtok((char *)Value.c_str(),",");
			while (pch1 != NULL)
			{
				IPGlobal::GN_GTPU_FLUSHER_CPU_CORE[cnt] = atoi(pch1);
				printf("\tGN_GTPU_FLUSHER_CPU_CORE[%d]     	:: %d\n", cnt, IPGlobal::GN_GTPU_FLUSHER_CPU_CORE[cnt]);
				pch1 = strtok (NULL, ",");
				cnt++;
			}
		}
		else if(Key.compare("GN_GTPC_FLUSHER_CPU_CORE") == 0)
		{
				fp >> Value;
				IPGlobal::GN_GTPC_FLUSHER_CPU_CORE = atoi(Value.c_str());
				printf("\tGN_GTPC_FLUSHER_CPU_CORE\t\t:: %d\n", IPGlobal::GN_GTPC_FLUSHER_CPU_CORE);
		}
		else if(Key.compare("GN_ZMQ_FLUSHER_CPU_CORE") == 0)
		{
				fp >> Value;
				IPGlobal::GN_ZMQ_FLUSHER_CPU_CORE = atoi(Value.c_str());
				printf("\tGN_ZMQ_FLUSHER_CPU_CORE\t\t\t:: %d\n", IPGlobal::GN_ZMQ_FLUSHER_CPU_CORE);
		}
		else if(Key.compare("GN_XDR_FLUSHER_CPU_CORE") == 0)
		{
				fp >> Value;
				IPGlobal::GN_XDR_FLUSHER_CPU_CORE = atoi(Value.c_str());
				printf("\tGN_XDR_FLUSHER_CPU_CORE\t\t\t:: %d\n", IPGlobal::GN_XDR_FLUSHER_CPU_CORE);
		}

		/* ************ DNS ************ */
		else if(Key.compare("GN_DNS_WRITE_XDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GN_DNS_WRITE_XDR = true;
			else
				GN_DNS_WRITE_XDR = false;
			printf("\tGN_DNS_WRITE_XDR\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GN_DNS_FILE_PREFIX") == 0)
		{
				fp >> Value;
				GN_DNS_FILE_PREFIX = Value;
				printf("\tGN_DNS_FILE_PREFIX\t\t:: %s\n", GN_DNS_FILE_PREFIX.c_str());
		}
		else if(Key.compare("GN_DNS_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				GN_DNS_FLUSH_FLAG = true;
			else
				GN_DNS_FLUSH_FLAG = false;
			printf("\tGN_DNS_FLUSH_FLAG\t\t:: %s\n", Value.c_str());
		}
		else if(Key.compare("GN_DNS_FLUSH_PORT") == 0)
		{
				fp >> Value;
				GN_DNS_FLUSH_PORT = Value;
				printf("\tGN_DNS_FLUSH_PORT\t\t:: %s\n", GN_DNS_FLUSH_PORT.c_str());
		}
		else if(Key.compare("GTP_ZMQ_FLUSER_TPS") == 0)
		{
				fp >> Value;
				GN_GTPU_ZMQ_FLUSER_TPS = atoi(Value.c_str());
				printf("\tGTP_ZMQ_FLUSER_TPS\t\t:: %d\n", GN_GTPU_ZMQ_FLUSER_TPS);
		}
		else if(Key.compare("GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str());
			printf("\tGN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPU_IDLE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			GN_GTPU_IDLE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str());
			printf("\tGN_GTPU_IDLE_SESSION_TIMEOUT_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPU_ACTIVE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			fp >> Value;
			GN_GTPU_ACTIVE_SESSION_TIMEOUT_IN_SEC = atoi(Value.c_str());
			printf("\tGN_GTPU_ACTIVE_SESSION_TIMEOUT_SEC\t:: %s Sec(s)\n", Value.c_str());
		}
		else if(Key.compare("GN_GTPU_SESSION_PACKET_LIMIT") == 0)
		{
			fp >> Value;
			GN_GTPU_SESSION_PACKET_LIMIT = atoi(Value.c_str());
			printf("\tGN_GTPU_SESSION_PACKET_LIMIT\t\t:: %d\n", GN_GTPU_SESSION_PACKET_LIMIT);
		}
	}
}

