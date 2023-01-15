/*
 * GTPFlusherZmq.cpp
 *
 *  Created on: 13-Feb-2017
 *      Author: Deb
 */

#include <zmq.h>
#include "GTPFlusherZmq.h"

GTPFlusherZmq::GTPFlusherZmq() {
	_thisLogLevel = 0;
	this->_name = "GTPFlusherZmq";
	this->setLogLevel(Log::theLog().level());
}

GTPFlusherZmq::~GTPFlusherZmq() {
}

VOID GTPFlusherZmq::run()
{
	struct tm *now_tm;
	int currentMin, currentHour, currentDay, currentMonth, currentYear;
	int lastProcessedIndex = -1;
	int curIndex = -1;

	TPS_PER_100MS = GContainer::config->gtpConfig->GN_GTPU_ZMQ_FLUSER_TPS / 10;

	openZmq();

	lastProcessedIndex = 0;
	currentMin = currentHour = currentDay = currentMonth = currentYear = 0;

	gettimeofday(&curTime, NULL);
//	curIndex = lastProcessedIndex = FLUSHER_READ_TIME_INDEX(curTime.tv_sec);

//	curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX);
//	if(curIndex < 0) curIndex = IPGlobal::ZMQ_FLUSHER_TIMEINDEX + curIndex;
	curIndex = READ_TIME_INDEX(curTime.tv_sec);

	lastProcessedIndex = curIndex;

//	TheLog_nc_v3(Log::Info, name()," Starting Loop curIndex::%d| lastProcessedIndex::%d Status [%d]", curIndex, lastProcessedIndex,IPGlobal::FLUSHER_ZMQ_RUNNING_STATUS);

	while(IPGlobal::GN_FLUSHER_ZMQ_RUNNING_STATUS)
	{
		sleep(1);

		gettimeofday(&curTime, NULL);
//		curIndex = FLUSHER_READ_TIME_INDEX(curTime.tv_sec);

//		curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX);
//		if(curIndex < 0) curIndex = IPGlobal::ZMQ_FLUSHER_TIMEINDEX + curIndex;
		curIndex = READ_TIME_INDEX(curTime.tv_sec);


//		TheLog_nc_v2(Log::Info, name()," curIndex::%d| lastProcessedIndex::%d", curIndex, lastProcessedIndex);

		while(lastProcessedIndex != curIndex){
//			TheLog_nc_v2(Log::Info,name(),"  LastProcessedIndex [%d] != currentIndex [%d] so Flushing..", lastProcessedIndex, curIndex);
//			usleep(100000);		// 100ms;	//Just to eliminate racing condition at 00 sec
			sleep(1);

			GTPZmqFlushStore::zmq_flush_t_index = lastProcessedIndex;
			process(lastProcessedIndex);
//			lastProcessedIndex = FLUSHER_NEXT_TIME_INDEX(lastProcessedIndex);
//			lastProcessedIndex++;
//			if(lastProcessedIndex >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX)
//				lastProcessedIndex = 0;
			lastProcessedIndex = NEXT_TIME_INDEX(lastProcessedIndex);

		}
	}
	printf("GTPFlusher Shutdown Completed\n");
}

VOID GTPFlusherZmq::sendGTPcZmqData(std::vector<xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt)
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
		buffer = (char*)zmq_flush_map[i].xdr;
		zmq_send (IPGlobal::gtpcZmqRequester, buffer, strlen(buffer), 0);

		zmq_flush_map_cnt--;
	}
	zmq_flush_map.clear();
	zmq_flush_map = std::vector<xdrStore>();
	zmq_flush_map.reserve(GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE);
	zmq_flush_map_cnt = 0;
}

//VOID GTPFlusherZmq::sendGTPuZmqData(std::vector<xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt)
VOID GTPFlusherZmq::sendGTPuZmqData(std::map<int, xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt)
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
		buffer = (char*)zmq_flush_map[i].xdr;
		zmq_send (IPGlobal::gtpuZmqRequester, buffer, strlen(buffer), 0);

		zmq_flush_map_cnt--;
	}
	zmq_flush_map.clear();
//	zmq_flush_map = std::vector<xdrStore>();
//	zmq_flush_map.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	zmq_flush_map_cnt = 0;
}

//VOID GTPFlusherZmq::sendGTPuDnsZmqData(std::vector<xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt)
VOID GTPFlusherZmq::sendGTPuDnsZmqData(std::map<int, xdrStore> &zmq_flush_map, int &zmq_flush_map_cnt)
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
		buffer = (char*)zmq_flush_map[i].xdr;
		zmq_send (IPGlobal::dnsZmqRequester, buffer, strlen(buffer), 0);

		zmq_flush_map_cnt--;
	}
	zmq_flush_map.clear();
//	zmq_flush_map = std::vector<xdrStore>();
//	zmq_flush_map.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	zmq_flush_map_cnt = 0;
}

VOID GTPFlusherZmq::process(int index)
{
	switch(index)
	{
		case 0:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_0, GTPZmqFlushStore::zmq_flush_map_gtpc_t_0_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_0, IPFlushRepository::ip_zmq_flush_f_0_t_0_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_0, IPFlushRepository::ip_zmq_flush_f_1_t_0_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_0, IPFlushRepository::dns_zmq_flush_f_0_t_0_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_0, IPFlushRepository::dns_zmq_flush_f_1_t_0_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_0, IPFlushRepository::ip_zmq_flush_f_0_t_0_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_0, IPFlushRepository::ip_zmq_flush_f_1_t_0_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_0, IPFlushRepository::ip_zmq_flush_f_2_t_0_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_0, IPFlushRepository::ip_zmq_flush_f_3_t_0_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_0, IPFlushRepository::dns_zmq_flush_f_0_t_0_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_0, IPFlushRepository::dns_zmq_flush_f_1_t_0_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_0, IPFlushRepository::dns_zmq_flush_f_2_t_0_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_0, IPFlushRepository::dns_zmq_flush_f_3_t_0_cnt);
					break;
			}
			break;

		case 1:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_1, GTPZmqFlushStore::zmq_flush_map_gtpc_t_1_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_1, IPFlushRepository::ip_zmq_flush_f_0_t_1_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_1, IPFlushRepository::ip_zmq_flush_f_1_t_1_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_1, IPFlushRepository::dns_zmq_flush_f_0_t_1_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_1, IPFlushRepository::dns_zmq_flush_f_1_t_1_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_1, IPFlushRepository::ip_zmq_flush_f_0_t_1_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_1, IPFlushRepository::ip_zmq_flush_f_1_t_1_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_1, IPFlushRepository::ip_zmq_flush_f_2_t_1_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_1, IPFlushRepository::ip_zmq_flush_f_3_t_1_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_1, IPFlushRepository::dns_zmq_flush_f_0_t_1_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_1, IPFlushRepository::dns_zmq_flush_f_1_t_1_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_1, IPFlushRepository::dns_zmq_flush_f_2_t_1_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_1, IPFlushRepository::dns_zmq_flush_f_3_t_1_cnt);
					break;
			}
			break;

		case 2:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_2, GTPZmqFlushStore::zmq_flush_map_gtpc_t_2_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_2, IPFlushRepository::ip_zmq_flush_f_0_t_2_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_2, IPFlushRepository::ip_zmq_flush_f_1_t_2_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_2, IPFlushRepository::dns_zmq_flush_f_0_t_2_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_2, IPFlushRepository::dns_zmq_flush_f_1_t_2_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_2, IPFlushRepository::ip_zmq_flush_f_0_t_2_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_2, IPFlushRepository::ip_zmq_flush_f_1_t_2_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_2, IPFlushRepository::ip_zmq_flush_f_2_t_2_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_2, IPFlushRepository::ip_zmq_flush_f_3_t_2_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_2, IPFlushRepository::dns_zmq_flush_f_0_t_2_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_2, IPFlushRepository::dns_zmq_flush_f_1_t_2_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_2, IPFlushRepository::dns_zmq_flush_f_2_t_2_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_2, IPFlushRepository::dns_zmq_flush_f_3_t_2_cnt);
					break;
			}
			break;

		case 3:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_3, GTPZmqFlushStore::zmq_flush_map_gtpc_t_3_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_3, IPFlushRepository::ip_zmq_flush_f_0_t_3_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_3, IPFlushRepository::ip_zmq_flush_f_1_t_3_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_3, IPFlushRepository::dns_zmq_flush_f_0_t_3_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_3, IPFlushRepository::dns_zmq_flush_f_1_t_3_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_3, IPFlushRepository::ip_zmq_flush_f_0_t_3_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_3, IPFlushRepository::ip_zmq_flush_f_1_t_3_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_3, IPFlushRepository::ip_zmq_flush_f_2_t_3_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_3, IPFlushRepository::ip_zmq_flush_f_3_t_3_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_3, IPFlushRepository::dns_zmq_flush_f_0_t_3_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_3, IPFlushRepository::dns_zmq_flush_f_1_t_3_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_3, IPFlushRepository::dns_zmq_flush_f_2_t_3_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_3, IPFlushRepository::dns_zmq_flush_f_3_t_3_cnt);
					break;
			}
			break;

		case 4:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_4, GTPZmqFlushStore::zmq_flush_map_gtpc_t_4_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_4, IPFlushRepository::ip_zmq_flush_f_0_t_4_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_4, IPFlushRepository::ip_zmq_flush_f_1_t_4_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_4, IPFlushRepository::dns_zmq_flush_f_0_t_4_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_4, IPFlushRepository::dns_zmq_flush_f_1_t_4_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_4, IPFlushRepository::ip_zmq_flush_f_0_t_4_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_4, IPFlushRepository::ip_zmq_flush_f_1_t_4_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_4, IPFlushRepository::ip_zmq_flush_f_2_t_4_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_4, IPFlushRepository::ip_zmq_flush_f_3_t_4_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_4, IPFlushRepository::dns_zmq_flush_f_0_t_4_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_4, IPFlushRepository::dns_zmq_flush_f_1_t_4_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_4, IPFlushRepository::dns_zmq_flush_f_2_t_4_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_4, IPFlushRepository::dns_zmq_flush_f_3_t_4_cnt);
					break;
			}
			break;

		case 5:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_5, GTPZmqFlushStore::zmq_flush_map_gtpc_t_5_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_5, IPFlushRepository::ip_zmq_flush_f_0_t_5_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_5, IPFlushRepository::ip_zmq_flush_f_1_t_5_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_5, IPFlushRepository::dns_zmq_flush_f_0_t_5_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_5, IPFlushRepository::dns_zmq_flush_f_1_t_5_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_5, IPFlushRepository::ip_zmq_flush_f_0_t_5_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_5, IPFlushRepository::ip_zmq_flush_f_1_t_5_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_5, IPFlushRepository::ip_zmq_flush_f_2_t_5_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_5, IPFlushRepository::ip_zmq_flush_f_3_t_5_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_5, IPFlushRepository::dns_zmq_flush_f_0_t_5_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_5, IPFlushRepository::dns_zmq_flush_f_1_t_5_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_5, IPFlushRepository::dns_zmq_flush_f_2_t_5_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_5, IPFlushRepository::dns_zmq_flush_f_3_t_5_cnt);
					break;
			}
			break;

		case 6:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_6, GTPZmqFlushStore::zmq_flush_map_gtpc_t_6_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_6, IPFlushRepository::ip_zmq_flush_f_0_t_6_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_6, IPFlushRepository::ip_zmq_flush_f_1_t_6_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_6, IPFlushRepository::dns_zmq_flush_f_0_t_6_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_6, IPFlushRepository::dns_zmq_flush_f_1_t_6_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_6, IPFlushRepository::ip_zmq_flush_f_0_t_6_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_6, IPFlushRepository::ip_zmq_flush_f_1_t_6_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_6, IPFlushRepository::ip_zmq_flush_f_2_t_6_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_6, IPFlushRepository::ip_zmq_flush_f_3_t_6_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_6, IPFlushRepository::dns_zmq_flush_f_0_t_6_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_6, IPFlushRepository::dns_zmq_flush_f_1_t_6_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_6, IPFlushRepository::dns_zmq_flush_f_2_t_6_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_6, IPFlushRepository::dns_zmq_flush_f_3_t_6_cnt);
					break;
			}
			break;

		case 7:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_7, GTPZmqFlushStore::zmq_flush_map_gtpc_t_7_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_7, IPFlushRepository::ip_zmq_flush_f_0_t_7_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_7, IPFlushRepository::ip_zmq_flush_f_1_t_7_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_7, IPFlushRepository::dns_zmq_flush_f_0_t_7_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_7, IPFlushRepository::dns_zmq_flush_f_1_t_7_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_7, IPFlushRepository::ip_zmq_flush_f_0_t_7_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_7, IPFlushRepository::ip_zmq_flush_f_1_t_7_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_7, IPFlushRepository::ip_zmq_flush_f_2_t_7_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_7, IPFlushRepository::ip_zmq_flush_f_3_t_7_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_7, IPFlushRepository::dns_zmq_flush_f_0_t_7_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_7, IPFlushRepository::dns_zmq_flush_f_1_t_7_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_7, IPFlushRepository::dns_zmq_flush_f_2_t_7_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_7, IPFlushRepository::dns_zmq_flush_f_3_t_7_cnt);
					break;
			}
			break;

		case 8:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_8, GTPZmqFlushStore::zmq_flush_map_gtpc_t_8_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_8, IPFlushRepository::ip_zmq_flush_f_0_t_8_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_8, IPFlushRepository::ip_zmq_flush_f_1_t_8_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_8, IPFlushRepository::dns_zmq_flush_f_0_t_8_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_8, IPFlushRepository::dns_zmq_flush_f_1_t_8_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_8, IPFlushRepository::ip_zmq_flush_f_0_t_8_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_8, IPFlushRepository::ip_zmq_flush_f_1_t_8_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_8, IPFlushRepository::ip_zmq_flush_f_2_t_8_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_8, IPFlushRepository::ip_zmq_flush_f_3_t_8_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_8, IPFlushRepository::dns_zmq_flush_f_0_t_8_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_8, IPFlushRepository::dns_zmq_flush_f_1_t_8_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_8, IPFlushRepository::dns_zmq_flush_f_2_t_8_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_8, IPFlushRepository::dns_zmq_flush_f_3_t_8_cnt);
					break;
			}
			break;

		case 9:
			sendGTPcZmqData(GTPZmqFlushStore::zmq_flush_map_gtpc_t_9, GTPZmqFlushStore::zmq_flush_map_gtpc_t_9_cnt);
			switch(IPGlobal::GN_GTPU_FLUSHER_NO) {
				case 2:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_9, IPFlushRepository::ip_zmq_flush_f_0_t_9_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_9, IPFlushRepository::ip_zmq_flush_f_1_t_9_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_9, IPFlushRepository::dns_zmq_flush_f_0_t_9_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_9, IPFlushRepository::dns_zmq_flush_f_1_t_9_cnt);
					break;

				case 4:
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_0_t_9, IPFlushRepository::ip_zmq_flush_f_0_t_9_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_1_t_9, IPFlushRepository::ip_zmq_flush_f_1_t_9_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_2_t_9, IPFlushRepository::ip_zmq_flush_f_2_t_9_cnt);
					sendGTPuZmqData(IPFlushRepository::ip_zmq_flush_f_3_t_9, IPFlushRepository::ip_zmq_flush_f_3_t_9_cnt);

					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_0_t_9, IPFlushRepository::dns_zmq_flush_f_0_t_9_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_1_t_9, IPFlushRepository::dns_zmq_flush_f_1_t_9_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_2_t_9, IPFlushRepository::dns_zmq_flush_f_2_t_9_cnt);
					sendGTPuDnsZmqData(IPFlushRepository::dns_zmq_flush_f_3_t_9, IPFlushRepository::dns_zmq_flush_f_3_t_9_cnt);
					break;
			}
			break;
	}
}


VOID GTPFlusherZmq::openZmq(){

	TCHAR zmqPort[100];
	int zmqConnect = -1;

	if(GContainer::config->gtpConfig->GN_GTPU_FLUSH_FLAG) {
		sprintf(zmqPort, "%s",GContainer::config->gtpConfig->GN_GTPU_FLUSH_PORT.c_str());
		TheLog_nc_v1(Log::Info, name()," Opening GN GTPu Zmq Connection to [%s]...", zmqPort);
		IPGlobal::gtpuZmqContext = zmq_ctx_new ();
		IPGlobal::gtpuZmqRequester = zmq_socket (IPGlobal::gtpuZmqContext, ZMQ_PUSH);
		zmqConnect = zmq_bind(IPGlobal::gtpuZmqRequester, zmqPort);
		if(!zmqConnect) {
			TheLog_nc_v1(Log::Info, name()," Opening GN GTPu Zmq Connection to [%s]...Success", zmqPort);
		} else {
			TheLog_nc_v1(Log::Info, name()," Opening GN GTPu Zmq Connection to [%s]...FAILED!!!", zmqPort);
			exit(1);
		}
		zmqConnect = -1;
		sprintf(zmqPort, "%s",GContainer::config->gtpConfig->GN_DNS_FLUSH_PORT.c_str());
		TheLog_nc_v1(Log::Info, name()," Opening GN DNS  Zmq Connection to [%s]...", zmqPort);
		IPGlobal::dnsZmqContext = zmq_ctx_new ();
		IPGlobal::dnsZmqRequester = zmq_socket (IPGlobal::dnsZmqContext, ZMQ_PUSH);
		zmqConnect = zmq_bind(IPGlobal::dnsZmqRequester, zmqPort);
		if(!zmqConnect) {
			TheLog_nc_v1(Log::Info, name()," Opening GN DNS  Zmq Connection to [%s]...Success", zmqPort);
		} else {
			TheLog_nc_v1(Log::Info, name()," Opening GN DNS  Zmq Connection to [%s]...FAILED!!!", zmqPort);
			exit(1);
		}

	}
	else
	{
		TheLog_nc_v1(Log::Warn, name(),"  WARNING!!! GN GTPu Zmq Push is Off%s","");
	}

	if(GContainer::config->gtpConfig->GN_GTPC_FLUSH_FLAG) {
		zmqConnect = -1;
		sprintf(zmqPort, "%s",GContainer::config->gtpConfig->GN_GTPC_FLUSH_PORT.c_str());
		TheLog_nc_v1(Log::Info, name()," Opening GN GTPc Zmq Connection to [%s]...", zmqPort);
		IPGlobal::gtpcZmqContext = zmq_ctx_new ();
		IPGlobal::gtpcZmqRequester = zmq_socket (IPGlobal::gtpcZmqContext, ZMQ_PUSH);
		zmqConnect = zmq_bind(IPGlobal::gtpcZmqRequester, zmqPort);
		if(!zmqConnect) {
			TheLog_nc_v1(Log::Info, name()," Opening GN GTPc Zmq Connection to [%s]...Success", zmqPort);
		} else {
			TheLog_nc_v1(Log::Info, name()," Opening GN GTPc Zmq Connection to [%s]...FAILED!!!", zmqPort);
			exit(1);
		}
	} else {
		TheLog_nc_v1(Log::Warn, name(),"  WARNING!!! GN GTPc Zmq Push is Off%s","");
	}

}


