/*
 * GConfig.cpp
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#include "GConfig.h"
#include "IPGlobal.h"

GConfig::GConfig(char *fileName) {
	bbConfig 	= new BroadBandConfig();
	gtpConfig 	= new GTPConfig();
	sccpConfig 	= new SCCPConfig();
	iupsConfig 	= new IUPSConfig();

	initialize(fileName);
}

GConfig::~GConfig() {
	delete (bbConfig);
	delete (gtpConfig);
	delete (sccpConfig);
	delete (iupsConfig);
}

void GConfig::initialize(char *fileName)
{
		printf("\nLoading configurations...\n");
		int i = 0;

		char writeXdr[10];
		char flushFlag1[10];

		writeXdr[0] = flushFlag1[0] = 0;
		string Key, Value;

		openConfigFile(fileName);

		while(!fp.eof())
		{
			fp >> Key;

			if(Key.compare("BROADBAND_PROBE") == 0)
			{
				fp >> Value;
				BROADBAND_PROBE = Value.compare("true") == 0 ? true : false;
				printf("	BROADBAND_PROBE				:: %s\n", Value.c_str());
			}
			else if(Key.compare("GX_PROBE") == 0)
			{
				fp >> Value;
				GX_PROBE = Value.compare("true") == 0 ? true : false;
				printf("	GX_PROBE				:: %s\n", Value.c_str());
			}
			else if(Key.compare("RADIUS_PROBE") == 0)
			{
				fp >> Value;
				RADIUS_PROBE = Value.compare("true") == 0 ? true : false;
				printf("	RADIUS_PROBE				:: %s\n", Value.c_str());
			}
			else if(Key.compare("IUPS_PROBE") == 0)
			{
				fp >> Value;
				IUPS_PROBE = Value.compare("true") == 0 ? true : false;
				printf("	IUPS_PROBE				:: %s\n", Value.c_str());
			}
			else if(Key.compare("GN_PROBE") == 0)
			{
				fp >> Value;
				GN_PROBE = Value.compare("true") == 0 ? true : false;
				printf("	GN_PROBE				:: %s\n", Value.c_str());
			}
			else if(Key.compare("S1MME_PROBE") == 0)
			{
				fp >> Value;
				S1MME_PROBE = Value.compare("true") == 0 ? true : false;
				printf("	S1MME_PROBE				:: %s\n", Value.c_str());
			}

			else if(Key.compare("PROBE_ID") == 0)
			{
				fp >> Value;
				IPGlobal::PROBE_ID = atoi(Value.c_str());
				printf("\tPROBE_ID               			:: %d\n", IPGlobal::PROBE_ID);

			}
			else if(Key.compare("ACTIVE_INTERFACE") == 0)
			{
				fp >> Value;
				IPGlobal::ACTIVE_INTERFACE = atol(Value.c_str());
				printf("\tACTIVE_INTERFACE             		:: %d\n", IPGlobal::ACTIVE_INTERFACE);

			}
			else if(Key.compare("PCAP_FILE_NAME") == 0)
			{
				fp >> Value;
				IPGlobal::PCAP_FILE_NAME = Value;
				printf("\tPCAP_FILE_NAME             		:: %s\n", IPGlobal::PCAP_FILE_NAME.c_str());

			}
			else if(Key.compare("PCAP_REPEAT") == 0)
			{
				fp >> Value;
				IPGlobal::PCAP_REPEAT = atol(Value.c_str());
				printf("\tPCAP_REPEAT             		:: %d\n", IPGlobal::PCAP_REPEAT);

			}
			else if(Key.compare("ETHERNET_INTERFACE") == 0)
			{
				fp >> Value;
				//Read number of interfaces
				char * pch;
				int cnt = 0;
				pch = strtok((char *)Value.c_str(),",");
				while (pch != NULL)
				{
					if(cnt > 3)
					{
						printf("Maximum [4] Interface allowed ... exiting\n");
						exit(1);
					}
					IPGlobal::ETHERNET_INTERFACES[cnt] = std::string(pch);
					pch = strtok (NULL, ",");
					printf("\tETHERNET_INTERFACES[%d]     		:: %s\n", cnt, IPGlobal::ETHERNET_INTERFACES[cnt].c_str());
					cnt++;
				}
				if(IPGlobal::ACTIVE_INTERFACE == 1)
					IPGlobal::NO_OF_INTERFACES = cnt;
			}
			else if(Key.compare("SOLAR_INTERFACE") == 0)
			{
				fp >> Value;
				//Read number of interfaces
				char * pch;
				int cnt = 0;
				pch = strtok((char *)Value.c_str(),",");
				while (pch != NULL)
				{
					if(cnt > 3)
					{
						printf("Maximum [4] Interface allowed ... exiting\n");
						exit(1);
					}
					IPGlobal::SOLAR_INTERFACES[cnt] = std::string(pch);
					pch = strtok (NULL, ",");
					printf("\tSOLAR_INTERFACES[%d] 			:: %s\n", cnt, IPGlobal::SOLAR_INTERFACES[cnt].c_str());
					cnt++;
				}
				if(IPGlobal::ACTIVE_INTERFACE == 2)
					IPGlobal::NO_OF_INTERFACES = cnt;
			}
			else if(Key.compare("ROUTER_PER_INTERFACE") == 0)
			{
				fp >> Value;
				char * pch1;
				int cnt = 0;
				pch1 = strtok((char *)Value.c_str(),",");
				while (pch1 != NULL)
				{
					IPGlobal::ROUTER_PER_INTERFACE[cnt] = atoi(pch1);
					printf("\tROUTER_PER_INTERFACE[%d]			:: %d\n", cnt, IPGlobal::ROUTER_PER_INTERFACE[cnt]);
					pch1 = strtok (NULL, ",");
					cnt++;
				}
			}
			else if(Key.compare("PKT_LISTENER_CPU_CORE") == 0)
			{
				fp >> Value;
				char * pch1;
				int cnt = 0;
				pch1 = strtok((char *)Value.c_str(),",");
				while (pch1 != NULL)
				{
					IPGlobal::PKT_LISTENER_CPU_CORE[cnt] = atoi(pch1);
					printf("\tPKT_LISTENER_CPU_CORE[%d]		:: %d\n", cnt, IPGlobal::PKT_LISTENER_CPU_CORE[cnt]);
					pch1 = strtok (NULL, ",");
					cnt++;
				}
			}
			else if(Key.compare("PKT_ROUTER_CPU_CORE") == 0)
			{
				fp >> Value;
				char *pchHash, *pchComma;
				int cnt, cnt1;

				cnt = cnt1 = 0;
				size_t pos = 0;
				std::string token;

				while ((pos = Value.find("-")) != std::string::npos) {

				    token = Value.substr(0, pos);
				    pchHash = strtok((char *)token.c_str(),",");
					while (pchHash != NULL)
					{
						IPGlobal::PKT_ROUTER_CPU_CORE[cnt1][cnt] = atoi(pchHash);
						printf("\tPKT_ROUTER_CPU_CORE[%d][%d]		:: %d\n", cnt1, cnt, IPGlobal::PKT_ROUTER_CPU_CORE[cnt1][cnt]);
						pchHash = strtok (NULL, ",");
						cnt++;
					}
					cnt1++;
				    Value.erase(0, pos + 1);
				}
				cnt = 0;
				pchComma = strtok((char *)Value.c_str(),",");
				while (pchComma != NULL)
				{
					IPGlobal::PKT_ROUTER_CPU_CORE[cnt1][cnt] = atoi(pchComma);
					printf("\tPKT_ROUTER_CPU_CORE[%d][%d]		:: %d\n", cnt1, cnt, IPGlobal::PKT_ROUTER_CPU_CORE[cnt1][cnt]);
					pchComma = strtok (NULL, ",");
					cnt++;
				}
			}
			else if(Key.compare("LINE_RATE_PER_INTERFACE") == 0)
			{
				fp >> Value;
				char * pch1;
				int cnt = 0;
				pch1 = strtok((char *)Value.c_str(),",");
				while (pch1 != NULL)
				{
					IPGlobal::LINE_RATE_PER_INTERFACE[cnt] = atoi(pch1);
					printf("\tLINE_RATE_PER_INTERFACE[%d]     		:: %d\n", cnt, IPGlobal::LINE_RATE_PER_INTERFACE[cnt]);
					pch1 = strtok (NULL, ",");
					cnt++;
				}
			}
			else if(Key.compare("PPS_PER_INTERFACE") == 0)
			{
				fp >> Value;
				char * pch1;
				int cnt = 0;
				pch1 = strtok((char *)Value.c_str(),",");
				while (pch1 != NULL)
				{
					IPGlobal::PPS_PER_INTERFACE[cnt] = atoi(pch1);
					printf("\tPPS_PER_INTERFACE[%d]     		:: %d\n", cnt, IPGlobal::PPS_PER_INTERFACE[cnt]);
					pch1 = strtok (NULL, ",");
					cnt++;
				}
			}
			else if(Key.compare("PPS_CAP_PERCENTAGE") == 0)
			{
				fp >> Value;
				char * pch1;
				int cnt = 0;
				pch1 = strtok((char *)Value.c_str(),",");
				while (pch1 != NULL)
				{
					IPGlobal::PPS_CAP_PERCENTAGE[cnt] = atoi(pch1);
					printf("\tPPS_CAP_PERCENTAGE[%d]     		:: %d\n", cnt, IPGlobal::PPS_CAP_PERCENTAGE[cnt]);
					pch1 = strtok (NULL, ",");
					cnt++;
				}
			}
			else if(Key.compare("SOURCE_MAC") == 0)
			{
				fp >> Value;
				i = 0;
				char * pch;
				pch = strtok((char *)Value.c_str(),",");
				while (pch != NULL)
				{
					if(GN_PROBE)
					{
						strcpy(IPGlobal::SGSN_MAC[i], pch);
					}
					else
					{
						if(IUPS_PROBE)
						{
							strcpy(IPGlobal::RNC_MAC[i], pch);
						}
					}

					printf("\tSOURCE_MAC     				:: %s\n", pch);
					pch = strtok (NULL, ",");
					i++;
				}
				IPGlobal::SRC_MAC_NOS = i;
			}
			else if(Key.compare("DESTINATION_MAC") == 0)
			{
				fp >> Value;
				i = 0;
				char * pch;
				pch = strtok((char *)Value.c_str(),",");
				while (pch != NULL)
				{
					if(GN_PROBE)
					{
						strcpy(IPGlobal::GGSN_MAC[i], pch);
					}
					else
					{
						if(IUPS_PROBE)
						{
							strcpy(IPGlobal::SGSN_MAC[i], pch);
						}
					}
					printf("\tDESTINATION_MAC     			:: %s\n", pch);
					pch = strtok (NULL, ",");
					i++;
				}
				IPGlobal::DST_MAC_NOS = i;
			}
			else if(Key.compare("SESSION_MANAGER_TIMEINDEX") == 0)
			{
				fp >> Value;
				IPGlobal::SESSION_MANAGER_TIMEINDEX = atoi(Value.c_str());
				printf("	SESSION_MANAGER_TIMEINDEX		:: %d\n", IPGlobal::SESSION_MANAGER_TIMEINDEX);
			}
			else if(Key.compare("SESSION_MANAGER_PER_TIMEINDEX_PKTS") == 0)
			{
				fp >> Value;
				IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS = atoi(Value.c_str());
				printf("	SESSION_MANAGER_PER_TIMEINDEX_PKTS	:: %d\n", IPGlobal::SESSION_MANAGER_PER_TIMEINDEX_PKTS);
			}
			else if(Key.compare("FLUSHER_TIMEINDEX") == 0)
			{
				fp >> Value;
				IPGlobal::FLUSHER_TIMEINDEX = atoi(Value.c_str());
				printf("	FLUSHER_TIMEINDEX   			:: %d\n", IPGlobal::FLUSHER_TIMEINDEX);
			}
			else if(Key.compare("ZMQ_FLUSHER_TIMEINDEX") == 0)
			{
				fp >> Value;
				IPGlobal::ZMQ_FLUSHER_TIMEINDEX = atoi(Value.c_str());
				printf("	ZMQ_FLUSHER_TIMEINDEX			:: %d\n", IPGlobal::ZMQ_FLUSHER_TIMEINDEX);
			}

			else if(Key.compare("SESSION_MANAGER_WRITE_INDEX_ADV") == 0)
			{
				fp >> Value;
				IPGlobal::SESSION_MANAGER_WRITE_INDEX_ADV = atoi(Value.c_str());
				printf("	SESSION_MANAGER_WRITE_INDEX_ADV		:: %d\n", IPGlobal::SESSION_MANAGER_WRITE_INDEX_ADV);
			}
			else if(Key.compare("SESSION_MANAGER_READ_INDEX_LAG") == 0)
			{
				fp >> Value;
				IPGlobal::SESSION_MANAGER_READ_INDEX_LAG = atoi(Value.c_str());
				printf("	SESSION_MANAGER_READ_INDEX_LAG		:: %d\n", IPGlobal::SESSION_MANAGER_READ_INDEX_LAG);
			}
			else if(Key.compare("IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE") == 0)
			{
				fp >> Value;
				IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE = atoi(Value.c_str());
				printf("	IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE	:: %d\n", IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
			}
			else if(Key.compare("IP_SESSION_PKT_LIMIT") == 0)
			{
				fp >> Value;
				IPGlobal::IP_SESSION_PKT_LIMIT = atoi(Value.c_str());
				printf("	IP_SESSION_PKT_LIMIT			:: %d\n", IPGlobal::IP_SESSION_PKT_LIMIT);
			}
			else if(Key.compare("IP_SESSION_REPO_MAX_LIMIT") == 0)
			{
				fp >> Value;
				IPGlobal::IP_SESSION_REPO_MAX_LIMIT = atoi(Value.c_str());
				printf("	IP_SESSION_REPO_MAX_LIMIT		:: %d\n", IPGlobal::IP_SESSION_REPO_MAX_LIMIT);
			}
			else if(Key.compare("IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC") == 0)
			{
				fp >> Value;
				IPGlobal::IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC = atoi(Value.c_str());
				printf("	IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC	:: %d\n", IPGlobal::IP_SESSION_CLEAN_UP_SCAN_FREQ_SEC);
			}
			else if(Key.compare("IP_SESSION_CLEAN_UP_BATCH_LIMIT") == 0)
			{
				fp >> Value;
				IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT = atoi(Value.c_str());
				printf("	IP_SESSION_CLEAN_UP_BATCH_LIMIT		:: %d\n", IPGlobal::IP_SESSION_CLEAN_UP_BATCH_LIMIT);
			}
			else if(Key.compare("IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC") == 0)
			{
				fp >> Value;
				IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC = atoi(Value.c_str());
				printf("	IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC		:: %d\n", IPGlobal::IP_SESSION_DNS_LOOKUP_TIMEOUT_SEC);
			}
			else if(Key.compare("LOG_LEVEL") == 0)
			{
				fp >> Value;
				LOG_LEVEL = atoi(Value.c_str());
				printf("\tLOG_LEVEL               		:: %d\n", LOG_LEVEL);

			}
			else if(Key.compare("PRINT_STATS") == 0)
			{
				fp >> Value;
				IPGlobal::PRINT_STATS = Value.compare("true") == 0 ? true : false;
				printf("	PRINT_STATS				:: [%d] [%s]\n", IPGlobal::PRINT_STATS, Value.c_str());
			}
			else if(Key.compare("PRINT_STATS_FREQ_SEC") == 0)
			{
				fp >> Value;
				IPGlobal::PRINT_STATS_FREQ_SEC = atoi(Value.c_str());
				printf("	PRINT_STATS_FREQ_SEC			:: %d\n", IPGlobal::PRINT_STATS_FREQ_SEC);
			}

			else if(Key.compare("XDR_DIR") == 0)
			{
				fp >> Value;
				XDR_DIR = Value;
				printf("\tXDR_DIR               			:: %s\n", XDR_DIR.c_str());
			}
			else if(Key.compare("LOG_DIR") == 0)
			{
				fp >> Value;
				LOG_DIR = Value;
				printf("\tLOG_DIR               			:: %s\n", LOG_DIR.c_str());
			}
			else if(Key.compare("DATA_DIR") == 0)
			{
				fp >> Value;
				DATA_DIR = Value;
				printf("\tDATA_DIR               			:: %s\n", DATA_DIR.c_str());
			}
			else if(Key.compare("TRACE_DIR") == 0)
			{
				fp >> Value;
				TRACE_DIR = Value;
				printf("	TRACE_DIR				:: %s\n", TRACE_DIR.c_str());
			}
		}
		// Close the file descriptor before passing to other class
		closeConfigFile();

		// Load configs of all plugins
		loadPuglinConfigs(fileName);
}

void GConfig::loadPuglinConfigs(char *fileName)
{
		if(BROADBAND_PROBE) {
			openConfigFile(fileName);
			bbConfig->loadConfig(fp);
			closeConfigFile();
		}

		if(GN_PROBE) {
			openConfigFile(fileName);
			gtpConfig->loadGNConfig(fp);
			closeConfigFile();
		}

		if(IUPS_PROBE) {
			openConfigFile(fileName);
			sccpConfig->loadConfig(fp);
			closeConfigFile();

			openConfigFile(fileName);
			iupsConfig->loadConfig(fp);
			closeConfigFile();
		}
}

void GConfig::openConfigFile(char *fileName)
{
	char probeConfigBaseDir[100];
	char *probeConfigDir;
	char *probeRootEnv;

	probeConfigDir = getenv("PROBE_CONF");
	probeRootEnv = getenv("PROBE_ROOT");

	strcpy(GConstant::probeBaseDir, probeRootEnv);
	sprintf(probeConfigBaseDir, "%s/%s", probeConfigDir, fileName);
	fp.open(probeConfigBaseDir);

	if(fp.fail())
	{
		printf("  Error in Opening Configuration File : %s\n", probeConfigBaseDir);
		exit(1);
	}
}
void GConfig::closeConfigFile()
{
	fp.close();
}
