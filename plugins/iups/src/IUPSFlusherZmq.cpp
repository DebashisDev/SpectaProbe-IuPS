/*
 * IUPSFlusherZmq.cpp
 *
 *  Created on: 13-Feb-2017
 *      Author: Deb
 */

#include <zmq.h>

#include "IUPSFlusherZmq.h"

IUPSFlusherZmq::IUPSFlusherZmq() {
	_thisLogLevel = 0;
	this->_name = "IUPSFlusherZmq";
	this->setLogLevel(Log::theLog().level());
}

IUPSFlusherZmq::~IUPSFlusherZmq() {
}

VOID IUPSFlusherZmq::run()
{
	struct tm *now_tm;
	int currentMin, currentHour, currentDay, currentMonth, currentYear;
	int lastProcessedIndex = -1;
	int curIndex = -1;

	TPS_PER_100MS = GContainer::config->iupsConfig->IUPS_ZMQ_FLUSER_TPS / 10;

	openZmq();

	lastProcessedIndex = 0;
	currentMin = currentHour = currentDay = currentMonth = currentYear = 0;

	gettimeofday(&curTime, NULL);

	curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX);
	if(curIndex < 0) curIndex = IPGlobal::ZMQ_FLUSHER_TIMEINDEX + curIndex;
	lastProcessedIndex = curIndex;

	while(IPGlobal::GN_FLUSHER_ZMQ_RUNNING_STATUS)
	{
		sleep(1);

		gettimeofday(&curTime, NULL);
		curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX);
		if(curIndex < 0) curIndex = IPGlobal::ZMQ_FLUSHER_TIMEINDEX + curIndex;

		while(lastProcessedIndex != curIndex){
			usleep(100000);		// 100ms;	//Just to eliminate racing condition at 00 sec
			IUPSZmqFlushStore::zmq_flush_t_index = lastProcessedIndex;
			process(lastProcessedIndex);
			lastProcessedIndex++;
			if(lastProcessedIndex >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX)
				lastProcessedIndex = 0;
		}
	}
	printf("IUPSFlusher Shutdown Completed\n");
}

VOID IUPSFlusherZmq::sendIupsZmqData(std::string (&zmq_flush_map)[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE], int &zmq_flush_map_cnt)
{
	char* buffer;
	int cnt = zmq_flush_map_cnt;
	int thrputCnt = 0;

	for(int i=0; i<cnt; i++)
	{
		thrputCnt++;
		if(thrputCnt >= TPS_PER_100MS)
		{
			usleep(100000);
			thrputCnt = 0;
		}
		buffer = (char*)zmq_flush_map[i].c_str();
		zmq_send (IPGlobal::iupsZmqRequester, buffer, strlen(buffer), 0);

		zmq_flush_map[i] = "";
		zmq_flush_map_cnt--;
	}
	//zmq_flush_map = std::vector<std::string>();
	//zmq_flush_map.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	zmq_flush_map_cnt = 0;
}


VOID IUPSFlusherZmq::process(int index)
{

	switch(index)
	{
		case 0:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_0, IUPSZmqFlushStore::zmq_flush_map_iups_t_0_cnt);
			break;

		case 1:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_1, IUPSZmqFlushStore::zmq_flush_map_iups_t_1_cnt);
			break;

		case 2:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_2, IUPSZmqFlushStore::zmq_flush_map_iups_t_2_cnt);
			break;

		case 3:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_3, IUPSZmqFlushStore::zmq_flush_map_iups_t_3_cnt);
			break;

		case 4:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_4, IUPSZmqFlushStore::zmq_flush_map_iups_t_4_cnt);
			break;

		case 5:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_5, IUPSZmqFlushStore::zmq_flush_map_iups_t_5_cnt);
			break;

		case 6:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_6, IUPSZmqFlushStore::zmq_flush_map_iups_t_6_cnt);
			break;

		case 7:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_7, IUPSZmqFlushStore::zmq_flush_map_iups_t_7_cnt);
			break;

		case 8:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_8, IUPSZmqFlushStore::zmq_flush_map_iups_t_8_cnt);
			break;

		case 9:
			sendIupsZmqData(IUPSZmqFlushStore::zmq_flush_map_iups_t_9, IUPSZmqFlushStore::zmq_flush_map_iups_t_9_cnt);
			break;
	}
}


VOID IUPSFlusherZmq::openZmq(){

	TCHAR zmqPort[100];
	int zmqConnect = -1;

	if(GContainer::config->iupsConfig->IUPS_FLUSH_FLAG) {
		zmqConnect = -1;
		sprintf(zmqPort, "%s",GContainer::config->iupsConfig->IUPS_FLUSH_PORT.c_str());
//		TheLog_nc_v1(Log::Info, name()," Opening Iups Zmq Connection to [%s]...", zmqPort);
		printf(" Opening Iups Zmq Connection to [%s]...\n", zmqPort);

		IPGlobal::iupsZmqContext = zmq_ctx_new ();
		IPGlobal::iupsZmqRequester = zmq_socket (IPGlobal::iupsZmqContext, ZMQ_PUSH);
		zmqConnect = zmq_bind(IPGlobal::iupsZmqRequester, zmqPort);
		if(!zmqConnect) {
//			TheLog_nc_v1(Log::Info, name()," Opening IUPS Zmq Connection to [%s]...Success", zmqPort);
			printf(" Opening IUPS Zmq Connection to [%s]...Success\n", zmqPort);
		} else {
//			TheLog_nc_v1(Log::Info, name()," Opening IUPS Zmq Connection to [%s]...FAILED!!!", zmqPort);
			printf(" Opening IUPS Zmq Connection to [%s]...FAILED!!!\n", zmqPort);
			exit(1);
		}
	} else {
//		TheLog_nc_v1(Log::Warn, name(),"  WARNING!!! IUPS Zmq Push is Off%s","");
	}
}
