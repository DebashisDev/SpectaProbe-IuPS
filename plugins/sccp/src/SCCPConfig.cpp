/*
 * IUPSConfig.cpp
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#include "SCCPConfig.h"
#include "IPGlobal.h"

SCCPConfig::SCCPConfig() {
}

SCCPConfig::~SCCPConfig() {
}

void SCCPConfig::loadConfig(ifstream &fp){

	printf("\nLoading SCCP configurations...\n");

	string Key, Value;

	while(!fp.eof())
	{
		fp >> Key;
		if(Key.compare("SCCP_WRITE_SESSION_TRACE") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				SCCP_WRITE_SESSION_TRACE = true;
			else
				SCCP_WRITE_SESSION_TRACE = false;
			printf("	SCCP_WRITE_SESSION_TRACE		:: %d\n", SCCP_WRITE_SESSION_TRACE);
		}
		else if(Key.compare("SCCP_WRITE_SESSION_DIR_PREFIX") == 0)
		{
			fp >> Value;
			SCCP_WRITE_SESSION_DIR_PREFIX = Value;
			printf("	SCCP_WRITE_SESSION_DIR_PREFIX		:: %s\n", SCCP_WRITE_SESSION_DIR_PREFIX.c_str());
		}
		else if(Key.compare("SCCP_TRACE_SESSION_IDS") == 0)
		{
			fp >> Value;
			SCCP_TRACE_SESSION_IDS.assign(Value);
			printf("	SCCP_TRACE_SESSION_IDS			:: %s\n", SCCP_TRACE_SESSION_IDS.c_str());
		}
		else if(Key.compare("SGSN_POINT_CODES") == 0)
		{
			fp >> Value;
			int i = 0;
			char * pch;
			pch = strtok((char *)Value.c_str(),",");
			while (pch != NULL)
			{
				IPGlobal::SGSN_PC[i] = atoi(pch);
				printf("	SGSN_POINT_CODES			:: %s\n", pch);
				pch = strtok (NULL, ",");
				i++;
			}
			IPGlobal::TOTAL_SGSN_PC = i;
		}
	}
}
