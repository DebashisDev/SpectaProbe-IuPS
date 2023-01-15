/*
 * SpectaProbe.cpp
 *
 *  Created on: 29-Jan-2016
 *      Author: deb
 */

#include <signal.h>
#include <unistd.h>
#include <locale.h>
#include <zmq.h>

#include "SpectaProbe.h"

void* gtpZmqflusherThread(void* arg)
{
	GTPFlusherZmq *ft = (GTPFlusherZmq*)arg;
	ft->run();
	return NULL;
}

void* startPktRouterThread(void* arg)
{
	PacketRouter *ft = (PacketRouter*)arg;
	ft->run();
	return NULL;
}

void* gtpSMThread(void* arg)
{
	GTPSessionManager *ft = (GTPSessionManager*)arg;
	ft->run();
	return NULL;
}

void* sccpSMThread(void* arg)
{
	SCCPSessionManager *ft = (SCCPSessionManager*)arg;
	ft->run();
	return NULL;
}

void* gtpXdrThread(void* arg)
{
	GTPXdrFlusher *ft = (GTPXdrFlusher*)arg;
	ft->run();
	return NULL;
}

void* gtpcFlusherThread(void* arg)
{
	GTPcFlusher *ft = (GTPcFlusher*)arg;
	ft->run();
	return NULL;
}

void* gtpuFlusherThread(void* arg)
{
	GTPuFlusher *ft = (GTPuFlusher*)arg;
	ft->run();
	return NULL;
}

void* flusherIuPsThread(void* arg)
{
	IUPSFlusher *ft = (IUPSFlusher*)arg;
	ft->run();
	return NULL;
}

void* iupsZmqflusherThread(void* arg)
{
	IUPSFlusherZmq *ft = (IUPSFlusherZmq*)arg;
	ft->run();
	return NULL;
}

void* packetListenerThread(void* arg)
{
	PacketListener *ft = (PacketListener*)arg;
	ft->start();
	return NULL;
}

void* ethListenerThread(void* arg)
{
	EthernetSource *ft = (EthernetSource*)arg;
	ft->start();
	return NULL;
}

void* probeStatsThread(void* arg)
{
	ProbeStats *ft = (ProbeStats*)arg;
	ft->run();
	return NULL;
}

void* traceThread(void* arg)
{
	TraceListener *ft = (TraceListener*)arg;
	ft->run();
	return NULL;
}


SpectaProbe::SpectaProbe(char *fileName) {
	this->_name = "SpectaProbe";

	GContainer::config = new GConfig(fileName);
	initializeLog();
	this->setLogLevel(Log::theLog().level());
}

SpectaProbe::~SpectaProbe() {
	delete(GContainer::config);
}

VOID SpectaProbe::initializeLog() {
	TCHAR logFile[200];
	TCHAR probeName[7];
	logFile[0] = 0;
	sprintf(logFile, "%s%s_%d.log", GContainer::config->LOG_DIR.c_str(), GConstant::logFilePrefix,IPGlobal::PROBE_ID);

	Log::theLog().open(logFile);
	Log::theLog().level(GContainer::config->LOG_LEVEL);

	if(GContainer::config->GN_PROBE)
		strcpy(probeName, " GN ");
	else if (GContainer::config->IUPS_PROBE)
		strcpy(probeName, " IUPS ");

	printf(" ############################################################\n");
	printf("                                                             \n");
	printf("                    Starting SPECTA [%s] Probe             \n", probeName);
	printf("                                                             \n");
	printf(" ############################################################\n");


	TheLog_nc_v1(Log::Info, name(),"  ############################################################%s","");
	TheLog_nc_v1(Log::Info, name(),"                                                              %s","");
	TheLog_nc_v2(Log::Info, name(),"                     Starting SPECTA [%s] Probe                    %s", probeName, "");
	TheLog_nc_v1(Log::Info, name(),"                                                              %s","");
	TheLog_nc_v1(Log::Info, name(),"  ############################################################%s","");
	TheLog_nc_v1(Log::Info, name(),"  Log file initialized Level - %d", GContainer::config->LOG_LEVEL);

}


VOID SpectaProbe::start() {

	string interfaces;
	ProbeStats 			*ps;
	SCCPSessionManager 	*sccpSessionManager[1];
	GTPSessionManager 	*gtpSessionManager[8];
	IUPSFlusher			*iupsFlusher;
	GTPFlusherZmq		*gtpFlusherZmq;
	IUPSFlusherZmq		*iupsFlusherZmq;
	PCAPSource 			*pcapReader 	= new PCAPSource();
	EthernetSource 		*ethReader[4];
	PacketRouter 		*pRouter[4][4];
	PacketListener 		*sfReader[4];

	GTPXdrFlusher		*gtpXdrWritter;
	GTPcFlusher			*gtpcFlusher;
	GTPuFlusher			*gtpuFlusher[4];

	pthread_t 	thPktRouter[4][4];
	pthread_t 	pktLisThread[4];
	pthread_t 	ftThread;
	pthread_t 	ftZmqThread;
	pthread_t 	ttThread;
	pthread_t 	psThread;
	pthread_t 	threadGtpSM[8];
	pthread_t 	threadSccpSM[1];
	pthread_t 	iupsThread;

	pthread_t	gtpXdrThr;
	pthread_t 	gtpcFlusherThr;
	pthread_t 	gtpuFlusherThr[4];

	int intOfRouter[4];
	int infid = 0;
	int totalNoRouter = 0;
	int startRouterId = 0;


//	int GN_SESSION_MANAGER_CPU_CORE[5] = {1,2,3,4,5};
//	int PKT_LISTENER_CPU_CORE[2] = {6,7};
//	int PKT_ROUTER_CPU_CORE[2][2] = {{8,9},{10,11}};
////	int PKT_ROUTER_CPU_CORE[2][1] = {{8},{9}};
//	int GN_GTPU_FLUSHER_CPU_CORE[2] = {12,13};
//	int GN_ZMQ_FLUSHER_CPU_CORE = 14;
//	int GN_XDR_FLUSHER_CPU_CORE = 15;
//	int GN_GTPC_FLUSHER_CPU_CORE = 15;

//	int IUPS_MANAGER_CPU_CORE[1] = {1};
//	int IUPS_ZMQ_FLUSHER_CPU_CORE = 2;
//	int IUPS_FLUSHER_CPU_CORE = 3;

	initialize_pkt_repo();

	loadStats();

	if(GContainer::config->GN_PROBE)
	{
		if(IPGlobal::GN_GTPU_FLUSHER_NO != 2) {
			if(IPGlobal::GN_GTPU_FLUSHER_NO != 4) {
				printf("\n\nCurrent Gtpu Flusher Setting[ %d ] *** GTPu Flusher should be 2 or 4 Instances\n\n", IPGlobal::GN_GTPU_FLUSHER_NO);
				exit(1);
			}
		}

		printf("Starting [%d] GTP Session Manager Instances...\n",IPGlobal::GN_SESSION_MANAGER_INSTANCES);
		TheLog_nc_v1(Log::Info, name(),"  Starting [%d] GTP Session Manager Instances...",IPGlobal::GN_SESSION_MANAGER_INSTANCES);
		/* Create GTPC Session Manager Threads */
		for(int i = 0; i < IPGlobal::GN_SESSION_MANAGER_INSTANCES; i++) {
			IPGlobal::GN_SESSION_MANAGER_RUNNING_STATUS[i] = true;
			gtpSessionManager[i] = new GTPSessionManager(i, IPGlobal::GN_SESSION_MANAGER_CPU_CORE[i]);
			pthread_create(&threadGtpSM[i], NULL, gtpSMThread, gtpSessionManager[i]);
			pinThread(threadGtpSM[i], IPGlobal::GN_SESSION_MANAGER_CPU_CORE[i]);
			printf("GTP Session Manager Instance [%d] pinned to Core [%d]\n", i, IPGlobal::GN_SESSION_MANAGER_CPU_CORE[i]);
			TheLog_nc_v2(Log::Info, name(),"  GTP Session Manager Instance [%d] pinned to Core [%d]", i, IPGlobal::GN_SESSION_MANAGER_CPU_CORE[i]);
			while(!gtpSessionManager[i]->isRepositoryInitialized())
				sleep(1);
		}

		printf("Creating GTPFlusher ZMQ thread...\n");
		IPGlobal::GN_FLUSHER_ZMQ_RUNNING_STATUS = true;
		gtpFlusherZmq = new GTPFlusherZmq();			// Create Flusher Thread
		pthread_create(&ftZmqThread, NULL, gtpZmqflusherThread, gtpFlusherZmq);
		pinThread(ftZmqThread, IPGlobal::GN_ZMQ_FLUSHER_CPU_CORE);
		printf("GTPFlusher pinned to Core [%d]\n", IPGlobal::GN_ZMQ_FLUSHER_CPU_CORE);
		TheLog_nc_v1(Log::Info, name(),"  GTPFlusher pinned to Core [%d]", IPGlobal::GN_ZMQ_FLUSHER_CPU_CORE);
		sleep(1);

		printf("Creating GTPXdrFlusher threads...\n");
		IPGlobal::GN_XDR_RUNNING_STATUS = true;
		gtpXdrWritter = new GTPXdrFlusher();			// Create Flusher Thread
		pthread_create(&gtpXdrThr, NULL, gtpXdrThread, gtpXdrWritter);
		pinThread(gtpXdrThr, IPGlobal::GN_XDR_FLUSHER_CPU_CORE);
		printf("GTPXdrFlusher pinned to Core [%d]\n", IPGlobal::GN_XDR_FLUSHER_CPU_CORE);
		TheLog_nc_v1(Log::Info, name(),"  GTPXdrFlusher pinned to Core [%d]", IPGlobal::GN_XDR_FLUSHER_CPU_CORE);
		sleep(1);

		while(!gtpXdrWritter->isRepositoryInitialized())
			sleep(1);

		printf("Creating GTPcFlusher threads...\n");
		IPGlobal::GN_GTPC_FLUSHER_RUNNING_STATUS = true;
		gtpcFlusher = new GTPcFlusher();
		pthread_create(&gtpcFlusherThr, NULL, gtpcFlusherThread, gtpcFlusher);
		pinThread(gtpcFlusherThr, IPGlobal::GN_GTPC_FLUSHER_CPU_CORE);
		printf("GTPcFlusher pinned to Core [%d]\n", IPGlobal::GN_GTPC_FLUSHER_CPU_CORE);
		TheLog_nc_v1(Log::Info, name(),"  GTPcFlusher pinned to Core [%d]", IPGlobal::GN_GTPC_FLUSHER_CPU_CORE);
		sleep(1);

		while(!gtpcFlusher->isRepositoryInitialized())
			sleep(1);

		printf("Creating [%d] GTPu Flusher threads...\n", IPGlobal::GN_GTPU_FLUSHER_NO);
		IPGlobal::GN_GTPU_FLUSHER_RUNNING_STATUS = true;
		for(int i = 0; i < IPGlobal::GN_GTPU_FLUSHER_NO; i++)
		{
			gtpuFlusher[i] = new GTPuFlusher(i);
			pthread_create(&gtpuFlusherThr[i], NULL, gtpuFlusherThread, gtpuFlusher[i]);
			pinThread(gtpuFlusherThr[i], IPGlobal::GN_GTPU_FLUSHER_CPU_CORE[i]);
			printf("GTPuFlusher Instance [%d] pinned to Core [%d]\n", i, IPGlobal::GN_GTPU_FLUSHER_CPU_CORE[i]);
			TheLog_nc_v2(Log::Info, name(),"  GTPuFlusher Instance [%d] pinned to Core [%d]", i, IPGlobal::GN_GTPU_FLUSHER_CPU_CORE[i]);
			while(!gtpuFlusher[i]->isRepositoryInitialized())
				sleep(1);
		}
	}

	if(GContainer::config->IUPS_PROBE)
	{
		for(int i = 0; i < IPGlobal::IUPS_SESSION_MANAGER_INSTANCES; i++) {
			IPGlobal::GN_SESSION_MANAGER_RUNNING_STATUS[i] = true;
			sccpSessionManager[i] = new SCCPSessionManager(i, IPGlobal::IUPS_SESSION_MANAGER_CPU_CORE[i]);
			pthread_create(&threadSccpSM[i], NULL, sccpSMThread, sccpSessionManager[i]);
			pinThread(threadSccpSM[i], IPGlobal::IUPS_SESSION_MANAGER_CPU_CORE[i]);
			printf("IUPS Session Manager Instance [%d] pinned to Core [%d]\n", i, IPGlobal::IUPS_SESSION_MANAGER_CPU_CORE[i]);
			TheLog_nc_v2(Log::Info, name(),"  GTP Session Manager Instance [%d] pinned to Core [%d]", i, IPGlobal::IUPS_SESSION_MANAGER_CPU_CORE[i]);
			sleep(1);
		}
		printf("Creating IUPS ZMQ thread...\n");
		IPGlobal::GN_FLUSHER_ZMQ_RUNNING_STATUS = true;
		iupsFlusherZmq = new IUPSFlusherZmq();			// Create Flusher Thread
		pthread_create(&ftZmqThread, NULL, iupsZmqflusherThread, iupsFlusherZmq);
		pinThread(ftZmqThread, IPGlobal::IUPS_ZMQ_FLUSHER_CPU_CORE);
		printf("IUPSFlusher ZMQ pinned to Core [%d]\n", IPGlobal::IUPS_ZMQ_FLUSHER_CPU_CORE);
		TheLog_nc_v1(Log::Info, name(),"  IUPSFlusher ZMQ pinned to Core [%d]", IPGlobal::IUPS_ZMQ_FLUSHER_CPU_CORE);

		printf("Creating IUPS Flusher threads...\n");
		IPGlobal::FLUSHER_RUNNING_STATUS = true;
		iupsFlusher = new IUPSFlusher();			// Create Flusher Thread
		pthread_create(&iupsThread, NULL, flusherIuPsThread, iupsFlusher);
		pinThread(iupsThread, IPGlobal::IUPS_FLUSHER_CPU_CORE);
		printf("IUPSFlusher pinned to Core [%d]\n", IPGlobal::IUPS_FLUSHER_CPU_CORE);
		TheLog_nc_v1(Log::Info, name(),"  IUPSFlusher pinned to Core [%d]", IPGlobal::IUPS_FLUSHER_CPU_CORE);

	}

	sleep(10);

//	int perListenerRouters = IPGlobal::ROUTER_PER_INTERFACE[intfId] / totalNoInterfaces;
	for(int i=0; i<IPGlobal::NO_OF_INTERFACES; i++)
	{
		for(int k=0; k<IPGlobal::ROUTER_PER_INTERFACE[i]; k++)
		{
			printf("Initializing Packet Router [%d] for Interface [%d]...\n", k, i);
			IPGlobal::PKT_ROUTER_RUNNING_STATUS[i][k] = true;
			pRouter[i][k] = new PacketRouter(i, k, IPGlobal::ROUTER_PER_INTERFACE[i], IPGlobal::PKT_ROUTER_CPU_CORE[i][k]);
			pthread_create(&thPktRouter[i][k], NULL, startPktRouterThread, pRouter[i][k]);
			pinThread(thPktRouter[i][k], IPGlobal::PKT_ROUTER_CPU_CORE[i][k]);
			printf("PacketRouter Instance [%d][%d] pinned to Core [%d]\n", i, k, IPGlobal::PKT_ROUTER_CPU_CORE[i][k]);
			TheLog_nc_v3(Log::Info, name(),"  PacketRouter Instance [%d][%d] pinned to Core [%d]", i, k, IPGlobal::PKT_ROUTER_CPU_CORE[i][k]);
			while(!pRouter[i][k]->isRepositoryInitialized())
				sleep(1);
		}

		switch(IPGlobal::ACTIVE_INTERFACE) {
			case PCAP:	//0
//				pcapReader->pcapReader();
				break;

			case ETH: //1
				printf("Starting EthernetListener for Interface [%d]->[%s] with No of Routers = %d...\n", i, IPGlobal::ETHERNET_INTERFACES[i].c_str(), IPGlobal::ROUTER_PER_INTERFACE[i]);
				IPGlobal::PKT_LISTENER_RUNNING_STATUS[i] = true;
				IPGlobal::PKT_LISTENER_DAYCHANGE_INDICATION[i] = false;
				ethReader[i] = new EthernetSource(IPGlobal::ROUTER_PER_INTERFACE[i], i);
				pthread_create(&pktLisThread[i], NULL, ethListenerThread, ethReader[i]);
				pinThread(pktLisThread[i], IPGlobal::PKT_LISTENER_CPU_CORE[i]);
				break;

			case SF: //2
				printf("Starting PacketListener for Interface [%d]->[%s] with No of Routers = %d...\n", i, IPGlobal::SOLAR_INTERFACES[i].c_str(), IPGlobal::ROUTER_PER_INTERFACE[i]);
				IPGlobal::PKT_LISTENER_RUNNING_STATUS[i] = true;
				IPGlobal::PKT_LISTENER_DAYCHANGE_INDICATION[i] = false;
				sfReader[i] = new PacketListener(IPGlobal::ROUTER_PER_INTERFACE[i], i);
				pthread_create(&pktLisThread[i], NULL, packetListenerThread, sfReader[i]);
				pinThread(pktLisThread[i], IPGlobal::PKT_LISTENER_CPU_CORE[i]);
				printf("PacketListener Instance [%d] pinned to Core [%d]\n", i, IPGlobal::PKT_LISTENER_CPU_CORE[i]);
				TheLog_nc_v2(Log::Info, name(),"  PacketListener Instance [%d] pinned to Core [%d]", i, IPGlobal::PKT_LISTENER_CPU_CORE[i]);
				break;
		}
	}

	printf("Specta Probe Started.\n");
	TheLog_nc_v1(Log::Info, name(),"  Started successfully.%s","");

	if(IPGlobal::PRINT_STATS){
		ps = new ProbeStats();
		pthread_create(&psThread, NULL, probeStatsThread, ps);
		sleep(1);
	}


	int today = 0, lastday = 0;
	int sleepDur = 10;

	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	lastday = today =  now_tm->tm_mday;

	while(IPGlobal::PROBE_RUNNING_STATUS){

		sleep(sleepDur);

			gettimeofday(&curTime, NULL);
			now_tm = localtime(&curTime.tv_sec);
			today =  now_tm->tm_mday;
			IPGlobal::CURRENT_TIME_DAY = today = now_tm->tm_mday;

			if(lastday != today)
			{
				lastday = today;
				for(int i=0; i<IPGlobal::NO_OF_INTERFACES; i++)
					IPGlobal::PKT_LISTENER_DAYCHANGE_INDICATION[i] = true;
			}

	}

	TheLog_nc_v1(Log::Info, name(),"  Specta Probe Shutdown initiated...%s","");

	if(IPGlobal::PRINT_STATS){
		printf("\nSending shutdown signal to Probe Stats\n");
		TheLog_nc_v1(Log::Info, name(),"  Shutting down ProbStats process...%s","");
		IPGlobal::PROBE_STATS_RUNNING_STATUS = false;
		pthread_join(psThread, 0);
		delete ps;
	}

	for(int i=0; i<IPGlobal::NO_OF_INTERFACES; i++)
	{
		printf("\nSending shutdown signal to Packet Listener [%d]\n",i);
		TheLog_nc_v1(Log::Info, name(),"  Shutting down Packet Listener [%d]...",i);
		IPGlobal::PKT_LISTENER_RUNNING_STATUS[i] = false;

		switch(IPGlobal::ACTIVE_INTERFACE)
		{
			case ETH: //1
					pthread_join(pktLisThread[i], 0);
					delete ethReader[i];
					break;

			case SF: //2
					pthread_join(pktLisThread[i], 0);
					delete sfReader[i];
					break;
		}
	}


	for(int i=0; i<IPGlobal::NO_OF_INTERFACES; i++)
	{
		for(int k=0; k<IPGlobal::ROUTER_PER_INTERFACE[i]; k++)
		{
			printf("\nSending shutdown signal to Packet Router [%d] [%d]\n",i,k);
			TheLog_nc_v2(Log::Info, name(),"  Shutting down Packet Router [%d] [%d]...",i,k);
			IPGlobal::PKT_ROUTER_RUNNING_STATUS[i][k] = false;
			pthread_join(thPktRouter[i][k],0);
			delete pRouter[i][k];
		}
	}

	if(GContainer::config->GN_PROBE)
	{
		for(int i = 0; i < IPGlobal::GN_SESSION_MANAGER_INSTANCES; i++) {
			printf("\nSending shutdown signal to GTPSessionManager [%d]\n",i);
			TheLog_nc_v1(Log::Info, name(),"  Shutting down GTP Session Manager [%d]...",i);
			IPGlobal::GN_SESSION_MANAGER_RUNNING_STATUS[i] = false;
			pthread_join(threadGtpSM[i], 0);
			delete gtpSessionManager[i];
		}

		printf("\nSending shutdown signal to GTP XDR Writter\n");
		TheLog_nc_v1(Log::Info, name(),"  Shutting down GTP XDR...%s","");
		IPGlobal::GN_XDR_RUNNING_STATUS = false;
		pthread_join(gtpXdrThr, 0);
		delete gtpXdrWritter;

		printf("\nSending shutdown signal to GTPc Flush Threads\n");
		TheLog_nc_v1(Log::Info, name(),"  Shutting down GTP Flusher...%s","");
		IPGlobal::GN_GTPC_FLUSHER_RUNNING_STATUS = false;
		pthread_join(gtpcFlusherThr, 0);
		delete gtpcFlusher;

		for(int i = 0; i<IPGlobal::GN_GTPU_FLUSHER_NO; i++) {
			printf("\nSending shutdown signal to GTPu Flush Threads [%d\n", i);
			TheLog_nc_v1(Log::Info, name(),"  Shutting down GTP Flusher...%s","");
			IPGlobal::GN_GTPU_FLUSHER_RUNNING_STATUS = false;
			pthread_join(gtpuFlusherThr[i], 0);
			delete gtpuFlusher[i];
		}

		printf("\nSending shutdown signal to GTPFlusher Zmq\n");
		TheLog_nc_v1(Log::Info, name(),"  Shutting down GTP Flusher ZMQ...%s","");
		IPGlobal::GN_FLUSHER_ZMQ_RUNNING_STATUS = false;
		pthread_join(ftZmqThread, 0);
		delete gtpFlusherZmq;
	}


	if(GContainer::config->IUPS_PROBE)
	{
		for(int i = 0; i < 1; i++) {
			printf("\nSending shutdown signal to SCCPSessionManager [%d]\n",i);
			TheLog_nc_v1(Log::Info, name(),"  Shutting down SCCP Session Manager [%d]...",i);
			IPGlobal::GN_SESSION_MANAGER_RUNNING_STATUS[i] = false;
			pthread_join(threadSccpSM[i], 0);
			delete sccpSessionManager[i];
		}

		printf("\nSending shutdown signal to IUPSFlusher\n");
		TheLog_nc_v1(Log::Info, name(),"  Shutting down IUPS Flusher...%s","");
		IPGlobal::FLUSHER_RUNNING_STATUS = false;
		pthread_join(iupsThread, 0);
		delete iupsFlusher;
	}

	//Dump Stats
	dumpStats();
	printf("\nShutdown SpectaProbe Complete.\n");
	TheLog_nc_v1(Log::Info, name(),"  Shutdown Completed.%s","");
}


VOID SpectaProbe::dumpStats(){

	string filePath = GContainer::config->DATA_DIR + "stats.csv";
	printf("\nSpectaProbe Dumping Stats to file [%s]...\n",filePath.c_str());
	TheLog_nc_v1(Log::Info, name(),"  Dumping Stats to file [%s]...",filePath.c_str());

	ofstream stats_file;

	stats_file.open(filePath.c_str(), ios :: out);

	if(stats_file.fail())
	{
		printf("Error in Opening Stats Dump File : %s\n", filePath.c_str());
	}else{

		stats_file  << "PKTS_TOTAL_INTF_0 " << IPGlobal::PKTS_TOTAL_INTF_0 << endl;
		stats_file  << "PKTS_TOTAL_INTF_1 " << IPGlobal::PKTS_TOTAL_INTF_1 << endl;
		stats_file  << "PKTS_TOTAL_INTF_2 " << IPGlobal::PKTS_TOTAL_INTF_2 << endl;
		stats_file  << "PKTS_TOTAL_INTF_3 " << IPGlobal::PKTS_TOTAL_INTF_3 << endl;


		uint64_t totProcessed =  IPGlobal::ip_processed_packets_i_0_r_0 + IPGlobal::ip_processed_packets_i_0_r_1 + IPGlobal::ip_processed_packets_i_0_r_2 + IPGlobal::ip_processed_packets_i_0_r_3;
								+ IPGlobal::ip_processed_packets_i_1_r_0 + IPGlobal::ip_processed_packets_i_1_r_1 + IPGlobal::ip_processed_packets_i_1_r_2 + IPGlobal::ip_processed_packets_i_1_r_3;
								+ IPGlobal::ip_processed_packets_i_2_r_0 + IPGlobal::ip_processed_packets_i_2_r_1 + IPGlobal::ip_processed_packets_i_2_r_2 + IPGlobal::ip_processed_packets_i_2_r_3;
								+ IPGlobal::ip_processed_packets_i_3_r_0 + IPGlobal::ip_processed_packets_i_3_r_1 + IPGlobal::ip_processed_packets_i_3_r_2 + IPGlobal::ip_processed_packets_i_3_r_3;

		uint64_t totRej =  IPGlobal::ip_discarded_packets_i_0_r_0 + IPGlobal::ip_discarded_packets_i_0_r_1 + IPGlobal::ip_discarded_packets_i_0_r_2 + IPGlobal::ip_discarded_packets_i_0_r_3;
							+ IPGlobal::ip_discarded_packets_i_1_r_0 + IPGlobal::ip_discarded_packets_i_1_r_1 + IPGlobal::ip_discarded_packets_i_1_r_2 + IPGlobal::ip_discarded_packets_i_1_r_3;
							+ IPGlobal::ip_discarded_packets_i_2_r_0 + IPGlobal::ip_discarded_packets_i_2_r_1 + IPGlobal::ip_discarded_packets_i_2_r_2 + IPGlobal::ip_discarded_packets_i_2_r_3;
							+ IPGlobal::ip_discarded_packets_i_3_r_0 + IPGlobal::ip_discarded_packets_i_3_r_1 + IPGlobal::ip_discarded_packets_i_3_r_2 + IPGlobal::ip_discarded_packets_i_3_r_3;

		uint64_t finOnlySessions = IPStats::ip_session_fin_only_sm_0_cnt + IPStats::ip_session_fin_only_sm_1_cnt + IPStats::ip_session_fin_only_sm_2_cnt + IPStats::ip_session_fin_only_sm_3_cnt;

		stats_file  << "PROCESSED_PKTS "<< totProcessed << endl;
		stats_file  << "REJECTED_PKTS "<< totRej << endl;
		stats_file  << "FIN_NO_SESSION "<< finOnlySessions << endl;

		uint64_t totPdpCr = GTPStats::gtpc_pdp_cr_req_sm_0 + GTPStats::gtpc_pdp_cr_req_sm_1 + GTPStats::gtpc_pdp_cr_req_sm_2 + GTPStats::gtpc_pdp_cr_req_sm_3;
		uint64_t totPdpUp = GTPStats::gtpc_pdp_up_req_sm_0 + GTPStats::gtpc_pdp_up_req_sm_1 + GTPStats::gtpc_pdp_up_req_sm_2 + GTPStats::gtpc_pdp_up_req_sm_3;
		uint64_t totPdpDl = GTPStats::gtpc_pdp_dl_req_sm_0 + GTPStats::gtpc_pdp_dl_req_sm_1 + GTPStats::gtpc_pdp_dl_req_sm_2 + GTPStats::gtpc_pdp_dl_req_sm_3;

		stats_file  << "PDP_CR "<< totPdpCr << endl;
		stats_file  << "PDP_UP "<< totPdpUp << endl;
		stats_file  << "PDP_DL "<< totPdpDl << endl;

		//	IPStats::ip_session_repo_busy_sm_0_cnt
		//	IPStats::ip_session_repo_busy_sm_1_cnt
		//	IPStats::ip_session_repo_busy_sm_2_cnt
		//	IPStats::ip_session_repo_busy_sm_3_cnt
		//
		//	IPStats::ip_session_total_sm_0_cnt
		//	IPStats::ip_session_total_sm_1_cnt
		//	IPStats::ip_session_total_sm_2_cnt
		//	IPStats::ip_session_total_sm_3_cnt
		//
		//	GTPStats::gtp_glb_sessions_cnt
		//	GTPStats::gtp_glb_sessions_op_cr_cnt
		//	GTPStats::gtp_glb_sessions_op_up_cnt
		//	GTPStats::gtp_glb_sessions_op_dl_cnt

		stats_file.close();
		printf("SpectaProbe Dumping Stats to file [%s]...Completed\n",filePath.c_str());
		TheLog_nc_v1(Log::Info, name(),"  Dumping Stats to file [%s]...Completed",filePath.c_str());
	}
}

VOID SpectaProbe::loadStats(){

	string filePath = GContainer::config->DATA_DIR + "stats.csv";
	printf("SpectaProbe Loading Stats from file [%s]...\n",filePath.c_str());
	TheLog_nc_v1(Log::Info, name(),"  Loading Stats from file [%s]...\n",filePath.c_str());

	ifstream fp;
	string Key, Value;

	fp.open(filePath.c_str(), ios :: out);

	if(fp.fail())
	{
		printf("SpectaProbe Error in Opening Stats Dump File : %s\n", filePath.c_str());
		TheLog_nc_v1(Log::Error, name(),"  Error in Opening Stats from file [%s]...",filePath.c_str());

	}else{

		while(!fp.eof())
		{
			fp >> Key;

			if(Key.compare("PKTS_TOTAL_INTF_0") == 0)
			{
				fp >> Value;
				IPGlobal::PKTS_TOTAL_INTF_0 = atol(Value.c_str());
				printf("\tPKTS_TOTAL_INTF_0            	:: %llu\n", IPGlobal::PKTS_TOTAL_INTF_0);

			}
			else if(Key.compare("PKTS_TOTAL_INTF_1") == 0)
			{
				fp >> Value;
				IPGlobal::PKTS_TOTAL_INTF_1 = atol(Value.c_str());
				printf("\tPKTS_TOTAL_INTF_1            	:: %llu\n", IPGlobal::PKTS_TOTAL_INTF_1);

			}
			else if(Key.compare("PKTS_TOTAL_INTF_2") == 0)
			{
				fp >> Value;
				IPGlobal::PKTS_TOTAL_INTF_2 = atol(Value.c_str());
				printf("\tPKTS_TOTAL_INTF_2            	:: %llu\n", IPGlobal::PKTS_TOTAL_INTF_2);

			}
			else if(Key.compare("PKTS_TOTAL_INTF_3") == 0)
			{
				fp >> Value;
				IPGlobal::PKTS_TOTAL_INTF_3 = atol(Value.c_str());
				printf("\tPKTS_TOTAL_INTF_3            	:: %llu\n", IPGlobal::PKTS_TOTAL_INTF_3);

			}
		}

//		uint64_t totProcessed =  IPGlobal::ip_processed_packets_i_0_r_0 + IPGlobal::ip_processed_packets_i_0_r_1 + IPGlobal::ip_processed_packets_i_0_r_2 + IPGlobal::ip_processed_packets_i_0_r_3;
//								+ IPGlobal::ip_processed_packets_i_1_r_0 + IPGlobal::ip_processed_packets_i_1_r_1 + IPGlobal::ip_processed_packets_i_1_r_2 + IPGlobal::ip_processed_packets_i_1_r_3;
//								+ IPGlobal::ip_processed_packets_i_2_r_0 + IPGlobal::ip_processed_packets_i_2_r_1 + IPGlobal::ip_processed_packets_i_2_r_2 + IPGlobal::ip_processed_packets_i_2_r_3;
//								+ IPGlobal::ip_processed_packets_i_3_r_0 + IPGlobal::ip_processed_packets_i_3_r_1 + IPGlobal::ip_processed_packets_i_3_r_2 + IPGlobal::ip_processed_packets_i_3_r_3;
//
//		uint64_t totRej =  IPGlobal::ip_discarded_packets_i_0_r_0 + IPGlobal::ip_discarded_packets_i_0_r_1 + IPGlobal::ip_discarded_packets_i_0_r_2 + IPGlobal::ip_discarded_packets_i_0_r_3;
//							+ IPGlobal::ip_discarded_packets_i_1_r_0 + IPGlobal::ip_discarded_packets_i_1_r_1 + IPGlobal::ip_discarded_packets_i_1_r_2 + IPGlobal::ip_discarded_packets_i_1_r_3;
//							+ IPGlobal::ip_discarded_packets_i_2_r_0 + IPGlobal::ip_discarded_packets_i_2_r_1 + IPGlobal::ip_discarded_packets_i_2_r_2 + IPGlobal::ip_discarded_packets_i_2_r_3;
//							+ IPGlobal::ip_discarded_packets_i_3_r_0 + IPGlobal::ip_discarded_packets_i_3_r_1 + IPGlobal::ip_discarded_packets_i_3_r_2 + IPGlobal::ip_discarded_packets_i_3_r_3;
//
//		uint64_t finOnlySessions = IPStats::ip_session_fin_only_sm_0_cnt + IPStats::ip_session_fin_only_sm_1_cnt + IPStats::ip_session_fin_only_sm_2_cnt + IPStats::ip_session_fin_only_sm_3_cnt;
//
//		stats_file  << "PROCESSED_PKTS "<< totProcessed << endl;
//		stats_file  << "REJECTED_PKTS "<< totRej << endl;
//		stats_file  << "FIN_NO_SESSION "<< finOnlySessions << endl;
//
//		uint64_t totPdpCr = GTPStats::gtpc_pdp_cr_req_sm_0 + GTPStats::gtpc_pdp_cr_req_sm_1 + GTPStats::gtpc_pdp_cr_req_sm_2 + GTPStats::gtpc_pdp_cr_req_sm_3;
//		uint64_t totPdpUp = GTPStats::gtpc_pdp_up_req_sm_0 + GTPStats::gtpc_pdp_up_req_sm_1 + GTPStats::gtpc_pdp_up_req_sm_2 + GTPStats::gtpc_pdp_up_req_sm_3;
//		uint64_t totPdpDl = GTPStats::gtpc_pdp_dl_req_sm_0 + GTPStats::gtpc_pdp_dl_req_sm_1 + GTPStats::gtpc_pdp_dl_req_sm_2 + GTPStats::gtpc_pdp_dl_req_sm_3;
//
//		stats_file  << "PDP_CR "<< totPdpCr << endl;
//		stats_file  << "PDP_UP "<< totPdpUp << endl;
//		stats_file  << "PDP_DL "<< totPdpDl << endl;

		//	IPStats::ip_session_repo_busy_sm_0_cnt
		//	IPStats::ip_session_repo_busy_sm_1_cnt
		//	IPStats::ip_session_repo_busy_sm_2_cnt
		//	IPStats::ip_session_repo_busy_sm_3_cnt
		//
		//	IPStats::ip_session_total_sm_0_cnt
		//	IPStats::ip_session_total_sm_1_cnt
		//	IPStats::ip_session_total_sm_2_cnt
		//	IPStats::ip_session_total_sm_3_cnt
		//
		//	GTPStats::gtp_glb_sessions_cnt
		//	GTPStats::gtp_glb_sessions_op_cr_cnt
		//	GTPStats::gtp_glb_sessions_op_up_cnt
		//	GTPStats::gtp_glb_sessions_op_dl_cnt

		fp.close();
		printf("SpectaProbe Loading Stats from file [%s]...Completed\n",filePath.c_str());
		TheLog_nc_v1(Log::Info, name(),"  Loading Stats from file [%s]...Completed",filePath.c_str());
	}
}

void SpectaProbe::pinThread(pthread_t th, int i)
{
   /* Set affinity mask to include CPUs 0 to 7 */
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(i,&cpuset);

	int s = pthread_setaffinity_np(th, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
		handle_error_en(s, "ERROR!!! pthread_setaffinity_np");

	/* Check the actual affinity mask assigned to the thread */
	s = pthread_getaffinity_np(th, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
		handle_error_en(s, "ERROR!!! pthread_getaffinity_np");

	if (!CPU_ISSET(i, &cpuset)){
		printf("CPU pinning failed at core :: %d\n", i);
		TheLog_nc_v1(Log::Info, name(),"  CPU pinning failed at core :: %d",i);
	}
}

//VOID SpectaProbe::readIPRange()
//{
//	int a, b;
//	char *probeRootEnv;
//	char configPath[100];
//
//	configPath[0] = 0;
//
//	probeRootEnv = getenv("PROBE_ROOT");
//	sprintf(configPath, "%s/%s", probeRootEnv, "ipRange.txt");
//
//	std::ifstream infile(configPath);
//
//	while (infile >> a >> b)
//		IPGlobal::IPRange[a] = b;
//
//	if(IPGlobal::GN_GTPU_FLUSHER_NO != 2) {
//		if(IPGlobal::GN_GTPU_FLUSHER_NO != 4) {
//			printf("\n\nCurrent Gtpu Flusher Setting[ %d ] *** GTPu Flusher should be 2 or 4 Instances\n\n", IPGlobal::GN_GTPU_FLUSHER_NO);
//			exit(1);
//		}
//	}
//}

VOID SpectaProbe::openZmq(){

	TCHAR zmqPort[100];
	int zmqConnect = -1;

	/* ** Create BORADBAND ZMQ ** */
	if(GContainer::config->BROADBAND_PROBE) {
		if(GContainer::config->bbConfig->BROADBAND_IP_FLUSH_FLAG) {
			sprintf(zmqPort, "%s",GContainer::config->bbConfig->BROADBAND_IP_FLUSH_PORT.c_str());
			TheLog_nc_v1(Log::Info, name(),"  Opening BROADBAND IP  Zmq Connection to [%s]...", zmqPort);
			IPGlobal::tcpZmqContext = zmq_ctx_new ();
			IPGlobal::tcpZmqRequester = zmq_socket (IPGlobal::tcpZmqContext, ZMQ_PUSH);
			zmqConnect = zmq_bind(IPGlobal::tcpZmqRequester, zmqPort);
			if(!zmqConnect) {
				TheLog_nc_v1(Log::Info, name(),"  Opening BROADBAND IP  Zmq Connection to [%s]...Success", zmqPort);
			} else {
				TheLog_nc_v1(Log::Info, name(),"  Opening BROADBAND IP  Zmq Connection to [%s]...FAILED!!!", zmqPort);
				exit(1);
			}
			zmqConnect = -1;
			sprintf(zmqPort, "%s",GContainer::config->bbConfig->BROADBAND_DNS_FLUSH_PORT.c_str());
			TheLog_nc_v1(Log::Info, name(),"Opening BROADBAND DNS Zmq Connection to [%s]...", zmqPort);
			IPGlobal::dnsZmqContext = zmq_ctx_new ();
			IPGlobal::dnsZmqRequester = zmq_socket (IPGlobal::dnsZmqContext, ZMQ_PUSH);
			zmqConnect = zmq_bind(IPGlobal::dnsZmqRequester, zmqPort);
			if(!zmqConnect) {
				TheLog_nc_v1(Log::Info, name(),"  Opening BROADBAND DNS Zmq Connection to [%s]...Success", zmqPort);
			} else {
				TheLog_nc_v1(Log::Info, name(),"  Opening BROADBAND DNS Zmq Connection to [%s]...FAILED!!!", zmqPort);
				exit(1);
			}
		} else {
			TheLog_nc_v1(Log::Warn, name(),"  WARNING!!! BROADBAND Zmq Push is Off%s","");
		}
	}

//	if(GContainer::config->RADIUS_PROBE) { /* ** Create RADIUS ZMQ ** */
//		if(GContainer::config->raConfig->RADIUS_FLUSH_FLAG) {
//			sprintf(zmqPort, "%s", GContainer::config->raConfig->RADIUS_FLUSH_PORT.c_str());
//			TheLog_nc_v1(Log::Info, name(),"  Opening RADIUS Connection to [%s]...", zmqPort);
//			IPGlobal::radiusZmqContext = zmq_ctx_new ();
//			IPGlobal::radiusZmqRequester = zmq_socket (IPGlobal::radiusZmqContext, ZMQ_PUSH);
//			zmqConnect = zmq_bind(IPGlobal::radiusZmqRequester, zmqPort);
//			if(!zmqConnect) {
//				TheLog_nc_v1(Log::Info, name(),"  Opening RADIUS Connection to [%s]...Success", zmqPort);
//			} else {
//				TheLog_nc_v1(Log::Info, name(),"  Opening RADIUS Connection to [%s]...FAILED!!!", zmqPort);
//				exit(1);
//			}
//		} else {
//			TheLog_nc_v1(Log::Warn, name(),"  WARNING!!! RADIUS Zmq Push is Off%s","");
//		}
//	}
}

VOID SpectaProbe::initialize_pkt_repo()
{
	if(IPGlobal::NO_OF_INTERFACES > 0)
		initialize_pkt_repo_i_0();
	if(IPGlobal::NO_OF_INTERFACES > 1)
		initialize_pkt_repo_i_1();
	if(IPGlobal::NO_OF_INTERFACES > 2)
		initialize_pkt_repo_i_2();
	if(IPGlobal::NO_OF_INTERFACES > 3)
		initialize_pkt_repo_i_3();
}

VOID SpectaProbe::initialize_pkt_repo_i_0()
{

	int intfId = 0;
	int maxLen = IPGlobal::PPS_PER_INTERFACE[intfId] / IPGlobal::ROUTER_PER_INTERFACE[intfId];

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);

	for(long i=0; i<maxLen; i++){
		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 0){
			PKTStore::pktRepository_i_0_r_0_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_0_t_9[i] = new RawPkt();
		}

		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 1){
			PKTStore::pktRepository_i_0_r_1_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_0_r_1_t_9[i] = new RawPkt();
		}

//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 2){
//			PKTStore::pktRepository_i_0_r_2_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_2_t_9[i] = new RawPkt();
//		}
//
//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 3){
//			PKTStore::pktRepository_i_0_r_3_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_0_r_3_t_9[i] = new RawPkt();
//		}
	}

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
}

VOID SpectaProbe::initialize_pkt_repo_i_1()
{

	int intfId = 1;
	int maxLen = IPGlobal::PPS_PER_INTERFACE[intfId] / IPGlobal::ROUTER_PER_INTERFACE[intfId];

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);

	for(long i=0; i<maxLen; i++){
		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 0){
			PKTStore::pktRepository_i_1_r_0_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_0_t_9[i] = new RawPkt();
		}

		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 1){
			PKTStore::pktRepository_i_1_r_1_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_1_r_1_t_9[i] = new RawPkt();
		}

//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 2){
//			PKTStore::pktRepository_i_1_r_2_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_2_t_9[i] = new RawPkt();
//		}
//
//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 3){
//			PKTStore::pktRepository_i_1_r_3_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_1_r_3_t_9[i] = new RawPkt();
//		}
	}

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
}

VOID SpectaProbe::initialize_pkt_repo_i_2()
{

	int intfId = 2;
	int maxLen = IPGlobal::PPS_PER_INTERFACE[intfId] / IPGlobal::ROUTER_PER_INTERFACE[intfId];

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);

	for(long i=0; i<maxLen; i++){
		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 0){
			PKTStore::pktRepository_i_2_r_0_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_0_t_9[i] = new RawPkt();
		}

		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 1){
			PKTStore::pktRepository_i_2_r_1_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_2_r_1_t_9[i] = new RawPkt();
		}

//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 2){
//			PKTStore::pktRepository_i_2_r_2_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_2_t_9[i] = new RawPkt();
//		}
//
//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 3){
//			PKTStore::pktRepository_i_2_r_3_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_2_r_3_t_9[i] = new RawPkt();
//		}
	}

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
}

VOID SpectaProbe::initialize_pkt_repo_i_3()
{

	int intfId = 0;
	int maxLen = IPGlobal::PPS_PER_INTERFACE[intfId] / IPGlobal::ROUTER_PER_INTERFACE[intfId];

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);

	for(long i=0; i<maxLen; i++){
		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 0){
			PKTStore::pktRepository_i_3_r_0_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_0_t_9[i] = new RawPkt();
		}

		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 1){
			PKTStore::pktRepository_i_3_r_1_t_0[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_1[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_2[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_3[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_4[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_5[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_6[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_7[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_8[i] = new RawPkt();
			PKTStore::pktRepository_i_3_r_1_t_9[i] = new RawPkt();
		}

//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 2){
//			PKTStore::pktRepository_i_3_r_2_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_2_t_9[i] = new RawPkt();
//		}
//
//		if(IPGlobal::ROUTER_PER_INTERFACE[intfId] > 3){
//			PKTStore::pktRepository_i_3_r_3_t_0[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_1[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_2[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_3[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_4[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_5[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_6[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_7[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_8[i] = new RawPkt();
//			PKTStore::pktRepository_i_3_r_3_t_9[i] = new RawPkt();
//		}
	}

	printf("PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed\n", intfId, maxLen, IPGlobal::ROUTER_PER_INTERFACE[intfId]);
	TheLog_nc_v3(Log::Info, name(),"  PKTStore Repository for Interface [%d] Initializing [%'d] per Router x 10 x %d Router RawPkt...Completed", intfId, maxLen,IPGlobal::ROUTER_PER_INTERFACE[intfId]);
}

