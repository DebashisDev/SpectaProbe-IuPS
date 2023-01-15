/*
 * IUPSConfig.cpp
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#include "IUPSConfig.h"
#include "IPGlobal.h"

IUPSConfig::IUPSConfig() {
	IUPS_FLUSH_FLAG = 0;
	IUPS_FLUSH_PORT = "";
	IUPS_FILE_PREFIX = "";
	IUPS_ZMQ_FLUSER_TPS = 0;
	IUPS_WRITE_XDR = false;
	IUPS_WRITE_TDR = false;
}

IUPSConfig::~IUPSConfig() {
}

void IUPSConfig::loadConfig(ifstream &fp){

	printf("\nLoading IUPS configurations...\n");

	string Key, Value;

	while(!fp.eof())
	{
		fp >> Key;
		if(Key.compare("IUPS_SESSION_MANAGER_INSTANCES") == 0)
		{
			fp >> Value;
			IPGlobal::IUPS_SESSION_MANAGER_INSTANCES = atoi(Value.c_str());
			printf("	IUPS_SESSION_MANAGER_INSTANCES		:: %d\n", IPGlobal::IUPS_SESSION_MANAGER_INSTANCES);
		}
		else if(Key.compare("IUPS_SESSION_MANAGER_CPU_CORE") == 0)
		{
			fp >> Value;
			char * pch1;
			int cnt = 0;
			pch1 = strtok((char *)Value.c_str(),",");
			while (pch1 != NULL)
			{
				IPGlobal::IUPS_SESSION_MANAGER_CPU_CORE[cnt] = atoi(pch1);
				printf("\tIUPS_SESSION_MANAGER_CPU_CORE[%d]     	:: %d\n", cnt, IPGlobal::IUPS_SESSION_MANAGER_CPU_CORE[cnt]);
				pch1 = strtok (NULL, ",");
				cnt++;
			}
		}
		else if(Key.compare("IUPS_ZMQ_FLUSHER_CPU_CORE") == 0)
		{
				fp >> Value;
				IPGlobal::IUPS_ZMQ_FLUSHER_CPU_CORE = atoi(Value.c_str());
				printf("\tIUPS_ZMQ_FLUSHER_CPU_CORE\t\t:: %d\n", IPGlobal::IUPS_ZMQ_FLUSHER_CPU_CORE);
		}
		else if(Key.compare("IUPS_FLUSHER_CPU_CORE") == 0)
		{
				fp >> Value;
				IPGlobal::IUPS_FLUSHER_CPU_CORE = atoi(Value.c_str());
				printf("\tIUPS_FLUSHER_CPU_CORE\t\t\t:: %d\n", IPGlobal::IUPS_FLUSHER_CPU_CORE);
		}
		else if(Key.compare("IUPS_FLUSHER_NO") == 0)
		{
				fp >> Value;
				IPGlobal::IUPS_FLUSHER_NO = atoi(Value.c_str());
				printf("\tIUPS_FLUSHER_NO\t\t\t\t:: %d\n", IPGlobal::IUPS_FLUSHER_NO);
		}
		else if(Key.compare("IUPS_FLUSH_FLAG") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				IUPS_FLUSH_FLAG =  true;
			else
				IUPS_FLUSH_FLAG =  false;
			printf("	IUPS_FLUSH_FLAG				:: %s\n", Value.c_str());
		}
		else if(Key.compare("IUPS_FLUSH_PORT") == 0)
		{
			fp >> Value;
			IUPS_FLUSH_PORT =  Value;
			printf("	IUPS_FLUSH_PORT				:: %s\n", IUPS_FLUSH_PORT.c_str());
		}
		else if(Key.compare("IUPS_FILE_PREFIX") == 0)
		{
			fp >> Value;
			IUPS_FILE_PREFIX =  Value;
			printf("	IUPS_FILE_PREFIX			:: %s\n", IUPS_FILE_PREFIX.c_str());
		}
		else if(Key.compare("IUPS_WRITE_XDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				IUPS_WRITE_XDR =  true;
			else
				IUPS_WRITE_XDR =  false;
			printf("	IUPS_WRITE_XDR				:: %s\n", Value.c_str());
		}
		else if(Key.compare("IUPS_WRITE_TDR") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				IUPS_WRITE_TDR =  true;
			else
				IUPS_WRITE_TDR =  false;
			printf("	IUPS_WRITE_TDR				:: %s\n", Value.c_str());
		}
		else if(Key.compare("IUPS_ZMQ_FLUSER_TPS") == 0)
		{
			fp >> Value;
			IUPS_ZMQ_FLUSER_TPS = atoi(Value.c_str());
			printf("	IUPS_ZMQ_FLUSER_TPS			:: %d\n", IUPS_ZMQ_FLUSER_TPS);
		}
	}
}

