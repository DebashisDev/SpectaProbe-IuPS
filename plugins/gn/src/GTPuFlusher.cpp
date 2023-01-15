/*
 * GTPuFlusher.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: Deb
 */

#include "GTPuFlusher.h"

GTPuFlusher::GTPuFlusher(int id) {
	_thisLogLevel = 0;
	this->_name = "GTPuFlusher";
	this->setLogLevel(Log::theLog().level());
	this->InstanceId = id;
	tcpFlusherUtility = new TCPFlusherUtility();
}

GTPuFlusher::~GTPuFlusher() {
	delete(tcpFlusherUtility);
}

VOID GTPuFlusher::run()
{
	struct tm *now_tm;
	int currentMin, currentHour, currentDay, currentMonth, currentYear;
	int lastProcessedIndex = -1;
	int curIndex = -1;
	int prevMin = 0;
	repoInitStatus = true;

	lastProcessedIndex = 0;
	currentMin = currentHour = currentDay = currentMonth = currentYear = 0;


	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	currentMin = prevMin = now_tm->tm_min;

//	curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX);
//	if(curIndex < 0) curIndex = IPGlobal::FLUSHER_TIMEINDEX + curIndex;
	curIndex = READ_TIME_INDEX(curTime.tv_sec);

	lastProcessedIndex = curIndex;

	while(IPGlobal::GN_GTPU_FLUSHER_RUNNING_STATUS)
	{
		sleep(1);
		gettimeofday(&curTime, NULL);

//		curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX);
//		if(curIndex < 0) curIndex = IPGlobal::FLUSHER_TIMEINDEX + curIndex;
		curIndex = READ_TIME_INDEX(curTime.tv_sec);


		while(lastProcessedIndex != curIndex){

//			usleep(100000);		// 100ms;	//Just to eliminate racing condition at 00 sec
			sleep(1);
			gettimeofday(&curTime, NULL);
			now_tm = localtime(&curTime.tv_sec);

			IPGlobal::lastFlusherEpochTimeSec = curTime.tv_sec;

			currentMin 		= now_tm->tm_min;
			currentHour 	= now_tm->tm_hour;
			currentDay 		= IPGlobal::currentDay = now_tm->tm_mday;
			currentMonth 	= 1 + now_tm->tm_mon;
			currentYear 	= 1900 + now_tm->tm_year;

			processStartEpochSec = curTime.tv_sec;
			if(GContainer::config->GN_PROBE) {
				/* Flush GTPu Data */
				strcpy(csvXdr, "");
				processGTPuData(lastProcessedIndex);

				/* Flush DNS Data */
				strcpy(csvXdr, "");
				processDNSData(lastProcessedIndex);
			}
			lastProcessedIndex = NEXT_TIME_INDEX(lastProcessedIndex);

//			lastProcessedIndex++;
//			if(lastProcessedIndex >= IPGlobal::FLUSHER_TIMEINDEX)
//				lastProcessedIndex = 0;
		}

//		TheLog_v1(Log::Info, "  GTPuFlusher", " Flusher will be invoked In [%d]", 60 - currentSec);
	}
	printf("GTPuFlusher Shutdown Completed\n");
}

VOID GTPuFlusher::processGTPuData(int index)
{
	switch(InstanceId)
	{
		case 0:
			processGTPuData_f_0(index);
			break;
		case 1:
			processGTPuData_f_1(index);
			break;
		case 2:
			processGTPuData_f_2(index);
			break;
		case 3:
			processGTPuData_f_3(index);
			break;


	}
}

//VOID GTPuFlusher::flushGTPuData_sm_t(std::vector<ipSession> &flushMap, int &ipFlushMap_sm_cnt)
VOID GTPuFlusher::flushGTPuData_sm_t(std::map<int, ipSession> &flushMap, int &ipFlushMap_sm_cnt)
{
	int cnt = ipFlushMap_sm_cnt;
	for(int i=0; i<cnt; i++)
	{
		buildCSVDataGTPu(&flushMap[i]);
		strcpy(objXdrStore.xdr, csvXdr);
		flushGtpuCsvRecords();
		flushMap[i].packTimeMap.clear();
		flushMap.erase(i);
		ipFlushMap_sm_cnt--;
	}
	flushMap.clear();
//	flushMap = std::vector<ipSession>();
//	flushMap.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	ipFlushMap_sm_cnt = 0;
}

VOID GTPuFlusher::processGTPuData_f_0(int index)
{

	switch(index)
	{
		case 0:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_0, IPFlushRepository::ipFlushMap_f_0_sm_0_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_0, IPFlushRepository::ipFlushMap_f_0_sm_1_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_0, IPFlushRepository::ipFlushMap_f_0_sm_2_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_0, IPFlushRepository::ipFlushMap_f_0_sm_3_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_0, IPFlushRepository::ipFlushMap_f_0_sm_4_t_0_cnt);

			break;

		case 1:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_1, IPFlushRepository::ipFlushMap_f_0_sm_0_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_1, IPFlushRepository::ipFlushMap_f_0_sm_1_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_1, IPFlushRepository::ipFlushMap_f_0_sm_2_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_1, IPFlushRepository::ipFlushMap_f_0_sm_3_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_1, IPFlushRepository::ipFlushMap_f_0_sm_4_t_1_cnt);

			break;

		case 2:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_2, IPFlushRepository::ipFlushMap_f_0_sm_0_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_2, IPFlushRepository::ipFlushMap_f_0_sm_1_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_2, IPFlushRepository::ipFlushMap_f_0_sm_2_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_2, IPFlushRepository::ipFlushMap_f_0_sm_3_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_2, IPFlushRepository::ipFlushMap_f_0_sm_4_t_2_cnt);

			break;

		case 3:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_3, IPFlushRepository::ipFlushMap_f_0_sm_0_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_3, IPFlushRepository::ipFlushMap_f_0_sm_1_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_3, IPFlushRepository::ipFlushMap_f_0_sm_2_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_3, IPFlushRepository::ipFlushMap_f_0_sm_3_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_3, IPFlushRepository::ipFlushMap_f_0_sm_4_t_3_cnt);

			break;

		case 4:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_4, IPFlushRepository::ipFlushMap_f_0_sm_0_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_4, IPFlushRepository::ipFlushMap_f_0_sm_1_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_4, IPFlushRepository::ipFlushMap_f_0_sm_2_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_4, IPFlushRepository::ipFlushMap_f_0_sm_3_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_4, IPFlushRepository::ipFlushMap_f_0_sm_4_t_4_cnt);

			break;

		case 5:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_5, IPFlushRepository::ipFlushMap_f_0_sm_0_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_5, IPFlushRepository::ipFlushMap_f_0_sm_1_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_5, IPFlushRepository::ipFlushMap_f_0_sm_2_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_5, IPFlushRepository::ipFlushMap_f_0_sm_3_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_5, IPFlushRepository::ipFlushMap_f_0_sm_4_t_5_cnt);

			break;

		case 6:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_6, IPFlushRepository::ipFlushMap_f_0_sm_0_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_6, IPFlushRepository::ipFlushMap_f_0_sm_1_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_6, IPFlushRepository::ipFlushMap_f_0_sm_2_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_6, IPFlushRepository::ipFlushMap_f_0_sm_3_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_6, IPFlushRepository::ipFlushMap_f_0_sm_4_t_6_cnt);

			break;

		case 7:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_7, IPFlushRepository::ipFlushMap_f_0_sm_0_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_7, IPFlushRepository::ipFlushMap_f_0_sm_1_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_7, IPFlushRepository::ipFlushMap_f_0_sm_2_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_7, IPFlushRepository::ipFlushMap_f_0_sm_3_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_7, IPFlushRepository::ipFlushMap_f_0_sm_4_t_7_cnt);

			break;

		case 8:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_8, IPFlushRepository::ipFlushMap_f_0_sm_0_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_8, IPFlushRepository::ipFlushMap_f_0_sm_1_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_8, IPFlushRepository::ipFlushMap_f_0_sm_2_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_8, IPFlushRepository::ipFlushMap_f_0_sm_3_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_8, IPFlushRepository::ipFlushMap_f_0_sm_4_t_8_cnt);

			break;

		case 9:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_0_t_9, IPFlushRepository::ipFlushMap_f_0_sm_0_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_1_t_9, IPFlushRepository::ipFlushMap_f_0_sm_1_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_2_t_9, IPFlushRepository::ipFlushMap_f_0_sm_2_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_3_t_9, IPFlushRepository::ipFlushMap_f_0_sm_3_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_0_sm_4_t_9, IPFlushRepository::ipFlushMap_f_0_sm_4_t_9_cnt);

			break;
	}
}

VOID GTPuFlusher::processGTPuData_f_1(int index)
{

	switch(index)
	{
		case 0:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_0, IPFlushRepository::ipFlushMap_f_1_sm_0_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_0, IPFlushRepository::ipFlushMap_f_1_sm_1_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_0, IPFlushRepository::ipFlushMap_f_1_sm_2_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_0, IPFlushRepository::ipFlushMap_f_1_sm_3_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_0, IPFlushRepository::ipFlushMap_f_1_sm_4_t_0_cnt);

			break;

		case 1:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_1, IPFlushRepository::ipFlushMap_f_1_sm_0_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_1, IPFlushRepository::ipFlushMap_f_1_sm_1_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_1, IPFlushRepository::ipFlushMap_f_1_sm_2_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_1, IPFlushRepository::ipFlushMap_f_1_sm_3_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_1, IPFlushRepository::ipFlushMap_f_1_sm_4_t_1_cnt);

			break;

		case 2:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_2, IPFlushRepository::ipFlushMap_f_1_sm_0_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_2, IPFlushRepository::ipFlushMap_f_1_sm_1_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_2, IPFlushRepository::ipFlushMap_f_1_sm_2_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_2, IPFlushRepository::ipFlushMap_f_1_sm_3_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_2, IPFlushRepository::ipFlushMap_f_1_sm_4_t_2_cnt);

			break;

		case 3:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_3, IPFlushRepository::ipFlushMap_f_1_sm_0_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_3, IPFlushRepository::ipFlushMap_f_1_sm_1_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_3, IPFlushRepository::ipFlushMap_f_1_sm_2_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_3, IPFlushRepository::ipFlushMap_f_1_sm_3_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_3, IPFlushRepository::ipFlushMap_f_1_sm_4_t_3_cnt);

			break;

		case 4:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_4, IPFlushRepository::ipFlushMap_f_1_sm_0_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_4, IPFlushRepository::ipFlushMap_f_1_sm_1_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_4, IPFlushRepository::ipFlushMap_f_1_sm_2_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_4, IPFlushRepository::ipFlushMap_f_1_sm_3_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_4, IPFlushRepository::ipFlushMap_f_1_sm_4_t_4_cnt);

			break;

		case 5:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_5, IPFlushRepository::ipFlushMap_f_1_sm_0_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_5, IPFlushRepository::ipFlushMap_f_1_sm_1_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_5, IPFlushRepository::ipFlushMap_f_1_sm_2_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_5, IPFlushRepository::ipFlushMap_f_1_sm_3_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_5, IPFlushRepository::ipFlushMap_f_1_sm_4_t_5_cnt);

			break;

		case 6:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_6, IPFlushRepository::ipFlushMap_f_1_sm_0_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_6, IPFlushRepository::ipFlushMap_f_1_sm_1_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_6, IPFlushRepository::ipFlushMap_f_1_sm_2_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_6, IPFlushRepository::ipFlushMap_f_1_sm_3_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_6, IPFlushRepository::ipFlushMap_f_1_sm_4_t_6_cnt);

			break;

		case 7:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_7, IPFlushRepository::ipFlushMap_f_1_sm_0_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_7, IPFlushRepository::ipFlushMap_f_1_sm_1_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_7, IPFlushRepository::ipFlushMap_f_1_sm_2_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_7, IPFlushRepository::ipFlushMap_f_1_sm_3_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_7, IPFlushRepository::ipFlushMap_f_1_sm_4_t_7_cnt);

			break;

		case 8:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_8, IPFlushRepository::ipFlushMap_f_1_sm_0_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_8, IPFlushRepository::ipFlushMap_f_1_sm_1_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_8, IPFlushRepository::ipFlushMap_f_1_sm_2_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_8, IPFlushRepository::ipFlushMap_f_1_sm_3_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_8, IPFlushRepository::ipFlushMap_f_1_sm_4_t_8_cnt);

			break;

		case 9:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_0_t_9, IPFlushRepository::ipFlushMap_f_1_sm_0_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_1_t_9, IPFlushRepository::ipFlushMap_f_1_sm_1_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_2_t_9, IPFlushRepository::ipFlushMap_f_1_sm_2_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_3_t_9, IPFlushRepository::ipFlushMap_f_1_sm_3_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_1_sm_4_t_9, IPFlushRepository::ipFlushMap_f_1_sm_4_t_9_cnt);

			break;
	}
}

VOID GTPuFlusher::processGTPuData_f_2(int index)
{
	switch(index)
	{
		case 0:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_0, IPFlushRepository::ipFlushMap_f_2_sm_0_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_0, IPFlushRepository::ipFlushMap_f_2_sm_1_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_0, IPFlushRepository::ipFlushMap_f_2_sm_2_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_0, IPFlushRepository::ipFlushMap_f_2_sm_3_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_0, IPFlushRepository::ipFlushMap_f_2_sm_4_t_0_cnt);

			break;

		case 1:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_1, IPFlushRepository::ipFlushMap_f_2_sm_0_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_1, IPFlushRepository::ipFlushMap_f_2_sm_1_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_1, IPFlushRepository::ipFlushMap_f_2_sm_2_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_1, IPFlushRepository::ipFlushMap_f_2_sm_3_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_1, IPFlushRepository::ipFlushMap_f_2_sm_4_t_1_cnt);

			break;

		case 2:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_2, IPFlushRepository::ipFlushMap_f_2_sm_0_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_2, IPFlushRepository::ipFlushMap_f_2_sm_1_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_2, IPFlushRepository::ipFlushMap_f_2_sm_2_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_2, IPFlushRepository::ipFlushMap_f_2_sm_3_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_2, IPFlushRepository::ipFlushMap_f_2_sm_4_t_2_cnt);

			break;

		case 3:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_3, IPFlushRepository::ipFlushMap_f_2_sm_0_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_3, IPFlushRepository::ipFlushMap_f_2_sm_1_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_3, IPFlushRepository::ipFlushMap_f_2_sm_2_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_3, IPFlushRepository::ipFlushMap_f_2_sm_3_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_3, IPFlushRepository::ipFlushMap_f_2_sm_4_t_3_cnt);

			break;

		case 4:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_4, IPFlushRepository::ipFlushMap_f_2_sm_0_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_4, IPFlushRepository::ipFlushMap_f_2_sm_1_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_4, IPFlushRepository::ipFlushMap_f_2_sm_2_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_4, IPFlushRepository::ipFlushMap_f_2_sm_3_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_4, IPFlushRepository::ipFlushMap_f_2_sm_4_t_4_cnt);

			break;

		case 5:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_5, IPFlushRepository::ipFlushMap_f_2_sm_0_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_5, IPFlushRepository::ipFlushMap_f_2_sm_1_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_5, IPFlushRepository::ipFlushMap_f_2_sm_2_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_5, IPFlushRepository::ipFlushMap_f_2_sm_3_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_5, IPFlushRepository::ipFlushMap_f_2_sm_4_t_5_cnt);

			break;

		case 6:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_6, IPFlushRepository::ipFlushMap_f_2_sm_0_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_6, IPFlushRepository::ipFlushMap_f_2_sm_1_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_6, IPFlushRepository::ipFlushMap_f_2_sm_2_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_6, IPFlushRepository::ipFlushMap_f_2_sm_3_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_6, IPFlushRepository::ipFlushMap_f_2_sm_4_t_6_cnt);

			break;

		case 7:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_7, IPFlushRepository::ipFlushMap_f_2_sm_0_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_7, IPFlushRepository::ipFlushMap_f_2_sm_1_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_7, IPFlushRepository::ipFlushMap_f_2_sm_2_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_7, IPFlushRepository::ipFlushMap_f_2_sm_3_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_7, IPFlushRepository::ipFlushMap_f_2_sm_4_t_7_cnt);

			break;

		case 8:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_8, IPFlushRepository::ipFlushMap_f_2_sm_0_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_8, IPFlushRepository::ipFlushMap_f_2_sm_1_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_8, IPFlushRepository::ipFlushMap_f_2_sm_2_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_8, IPFlushRepository::ipFlushMap_f_2_sm_3_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_8, IPFlushRepository::ipFlushMap_f_2_sm_4_t_8_cnt);

			break;

		case 9:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_0_t_9, IPFlushRepository::ipFlushMap_f_2_sm_0_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_1_t_9, IPFlushRepository::ipFlushMap_f_2_sm_1_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_2_t_9, IPFlushRepository::ipFlushMap_f_2_sm_2_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_3_t_9, IPFlushRepository::ipFlushMap_f_2_sm_3_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_2_sm_4_t_9, IPFlushRepository::ipFlushMap_f_2_sm_4_t_9_cnt);

			break;
	}
}

VOID GTPuFlusher::processGTPuData_f_3(int index)
{
	switch(index)
	{
		case 0:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_0, IPFlushRepository::ipFlushMap_f_3_sm_0_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_0, IPFlushRepository::ipFlushMap_f_3_sm_1_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_0, IPFlushRepository::ipFlushMap_f_3_sm_2_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_0, IPFlushRepository::ipFlushMap_f_3_sm_3_t_0_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_0, IPFlushRepository::ipFlushMap_f_3_sm_4_t_0_cnt);

			break;

		case 1:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_1, IPFlushRepository::ipFlushMap_f_3_sm_0_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_1, IPFlushRepository::ipFlushMap_f_3_sm_1_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_1, IPFlushRepository::ipFlushMap_f_3_sm_2_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_1, IPFlushRepository::ipFlushMap_f_3_sm_3_t_1_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_1, IPFlushRepository::ipFlushMap_f_3_sm_4_t_1_cnt);

			break;

		case 2:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_2, IPFlushRepository::ipFlushMap_f_3_sm_0_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_2, IPFlushRepository::ipFlushMap_f_3_sm_1_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_2, IPFlushRepository::ipFlushMap_f_3_sm_2_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_2, IPFlushRepository::ipFlushMap_f_3_sm_3_t_2_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_2, IPFlushRepository::ipFlushMap_f_3_sm_4_t_2_cnt);

			break;

		case 3:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_3, IPFlushRepository::ipFlushMap_f_3_sm_0_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_3, IPFlushRepository::ipFlushMap_f_3_sm_1_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_3, IPFlushRepository::ipFlushMap_f_3_sm_2_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_3, IPFlushRepository::ipFlushMap_f_3_sm_3_t_3_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_3, IPFlushRepository::ipFlushMap_f_3_sm_4_t_3_cnt);

			break;

		case 4:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_4, IPFlushRepository::ipFlushMap_f_3_sm_0_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_4, IPFlushRepository::ipFlushMap_f_3_sm_1_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_4, IPFlushRepository::ipFlushMap_f_3_sm_2_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_4, IPFlushRepository::ipFlushMap_f_3_sm_3_t_4_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_4, IPFlushRepository::ipFlushMap_f_3_sm_4_t_4_cnt);

			break;

		case 5:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_5, IPFlushRepository::ipFlushMap_f_3_sm_0_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_5, IPFlushRepository::ipFlushMap_f_3_sm_1_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_5, IPFlushRepository::ipFlushMap_f_3_sm_2_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_5, IPFlushRepository::ipFlushMap_f_3_sm_3_t_5_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_5, IPFlushRepository::ipFlushMap_f_3_sm_4_t_5_cnt);

			break;

		case 6:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_6, IPFlushRepository::ipFlushMap_f_3_sm_0_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_6, IPFlushRepository::ipFlushMap_f_3_sm_1_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_6, IPFlushRepository::ipFlushMap_f_3_sm_2_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_6, IPFlushRepository::ipFlushMap_f_3_sm_3_t_6_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_6, IPFlushRepository::ipFlushMap_f_3_sm_4_t_6_cnt);

			break;

		case 7:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_7, IPFlushRepository::ipFlushMap_f_3_sm_0_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_7, IPFlushRepository::ipFlushMap_f_3_sm_1_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_7, IPFlushRepository::ipFlushMap_f_3_sm_2_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_7, IPFlushRepository::ipFlushMap_f_3_sm_3_t_7_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_7, IPFlushRepository::ipFlushMap_f_3_sm_4_t_7_cnt);

			break;

		case 8:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_8, IPFlushRepository::ipFlushMap_f_3_sm_0_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_8, IPFlushRepository::ipFlushMap_f_3_sm_1_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_8, IPFlushRepository::ipFlushMap_f_3_sm_2_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_8, IPFlushRepository::ipFlushMap_f_3_sm_3_t_8_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_8, IPFlushRepository::ipFlushMap_f_3_sm_4_t_8_cnt);

			break;

		case 9:

			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_0_t_9, IPFlushRepository::ipFlushMap_f_3_sm_0_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_1_t_9, IPFlushRepository::ipFlushMap_f_3_sm_1_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_2_t_9, IPFlushRepository::ipFlushMap_f_3_sm_2_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_3_t_9, IPFlushRepository::ipFlushMap_f_3_sm_3_t_9_cnt);
			flushGTPuData_sm_t(IPFlushRepository::ipFlushMap_f_3_sm_4_t_9, IPFlushRepository::ipFlushMap_f_3_sm_4_t_9_cnt);

			break;
	}
}


VOID GTPuFlusher::flushGtpuCsvRecords()
{
	switch(InstanceId)
	{
		case 0:
			flushGtpuCsvRecords_f_0();
			break;
		case 1:
			flushGtpuCsvRecords_f_1();
			break;
		case 2:
			flushGtpuCsvRecords_f_2();
			break;
		case 3:
			flushGtpuCsvRecords_f_3();
			break;
	}
}

//VOID GTPuFlusher::storeGtpuZmqRecords(int index, int &ip_zmq_flush_map_cnt, std::vector<xdrStore> &ip_zmq_flush_map)
VOID GTPuFlusher::storeGtpuZmqRecords(int index, int &ip_zmq_flush_map_cnt, std::map<int, xdrStore> &ip_zmq_flush_map)
{

	if(ip_zmq_flush_map_cnt >= IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE || GTPZmqFlushStore::zmq_flush_t_index == index){
		// Do nothing, we don't want to push anything into Buffer
	}
	else
	{
		ip_zmq_flush_map[ip_zmq_flush_map_cnt] = objXdrStore;
		ip_zmq_flush_map_cnt++;
	}
}

VOID GTPuFlusher::flushGtpuCsvRecords_f_0()
{

	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_GTPU_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_0_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_0);
				break;
			case 1:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_1_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_1);
				break;
			case 2:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_2_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_2);
				break;
			case 3:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_3_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_3);
				break;
			case 4:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_4_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_4);
				break;
			case 5:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_5_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_5);
				break;
			case 6:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_6_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_6);
				break;
			case 7:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_7_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_7);
				break;
			case 8:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_8_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_8);
				break;
			case 9:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_0_t_9_cnt,IPFlushRepository::ip_zmq_flush_f_0_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_GTPU_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::ip_xdr_flush_f_0_t_0[IPFlushRepository::ip_xdr_flush_f_0_t_0_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::ip_xdr_flush_f_0_t_1[IPFlushRepository::ip_xdr_flush_f_0_t_1_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::ip_xdr_flush_f_0_t_2[IPFlushRepository::ip_xdr_flush_f_0_t_2_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::ip_xdr_flush_f_0_t_3[IPFlushRepository::ip_xdr_flush_f_0_t_3_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::ip_xdr_flush_f_0_t_4[IPFlushRepository::ip_xdr_flush_f_0_t_4_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::ip_xdr_flush_f_0_t_5[IPFlushRepository::ip_xdr_flush_f_0_t_5_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::ip_xdr_flush_f_0_t_6[IPFlushRepository::ip_xdr_flush_f_0_t_6_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::ip_xdr_flush_f_0_t_7[IPFlushRepository::ip_xdr_flush_f_0_t_7_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::ip_xdr_flush_f_0_t_8[IPFlushRepository::ip_xdr_flush_f_0_t_8_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::ip_xdr_flush_f_0_t_9[IPFlushRepository::ip_xdr_flush_f_0_t_9_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_0_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::flushGtpuCsvRecords_f_1()
{
	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_GTPU_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_0_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_0);
				break;
			case 1:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_1_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_1);
				break;
			case 2:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_2_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_2);
				break;
			case 3:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_3_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_3);
				break;
			case 4:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_4_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_4);
				break;
			case 5:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_5_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_5);
				break;
			case 6:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_6_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_6);
				break;
			case 7:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_7_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_7);
				break;
			case 8:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_8_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_8);
				break;
			case 9:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_1_t_9_cnt,IPFlushRepository::ip_zmq_flush_f_1_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_GTPU_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::ip_xdr_flush_f_1_t_0[IPFlushRepository::ip_xdr_flush_f_1_t_0_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::ip_xdr_flush_f_1_t_1[IPFlushRepository::ip_xdr_flush_f_1_t_1_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::ip_xdr_flush_f_1_t_2[IPFlushRepository::ip_xdr_flush_f_1_t_2_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::ip_xdr_flush_f_1_t_3[IPFlushRepository::ip_xdr_flush_f_1_t_3_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::ip_xdr_flush_f_1_t_4[IPFlushRepository::ip_xdr_flush_f_1_t_4_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::ip_xdr_flush_f_1_t_5[IPFlushRepository::ip_xdr_flush_f_1_t_5_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::ip_xdr_flush_f_1_t_6[IPFlushRepository::ip_xdr_flush_f_1_t_6_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::ip_xdr_flush_f_1_t_7[IPFlushRepository::ip_xdr_flush_f_1_t_7_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::ip_xdr_flush_f_1_t_8[IPFlushRepository::ip_xdr_flush_f_1_t_8_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::ip_xdr_flush_f_1_t_9[IPFlushRepository::ip_xdr_flush_f_1_t_9_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_1_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::flushGtpuCsvRecords_f_2()
{
	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_GTPU_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_0_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_0);
				break;
			case 1:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_1_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_1);
				break;
			case 2:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_2_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_2);
				break;
			case 3:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_3_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_3);
				break;
			case 4:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_4_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_4);
				break;
			case 5:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_5_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_5);
				break;
			case 6:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_6_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_6);
				break;
			case 7:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_7_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_7);
				break;
			case 8:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_8_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_8);
				break;
			case 9:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_2_t_9_cnt,IPFlushRepository::ip_zmq_flush_f_2_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_GTPU_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::ip_xdr_flush_f_2_t_0[IPFlushRepository::ip_xdr_flush_f_2_t_0_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::ip_xdr_flush_f_2_t_1[IPFlushRepository::ip_xdr_flush_f_2_t_1_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::ip_xdr_flush_f_2_t_2[IPFlushRepository::ip_xdr_flush_f_2_t_2_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::ip_xdr_flush_f_2_t_3[IPFlushRepository::ip_xdr_flush_f_2_t_3_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::ip_xdr_flush_f_2_t_4[IPFlushRepository::ip_xdr_flush_f_2_t_4_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::ip_xdr_flush_f_2_t_5[IPFlushRepository::ip_xdr_flush_f_2_t_5_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::ip_xdr_flush_f_2_t_6[IPFlushRepository::ip_xdr_flush_f_2_t_6_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::ip_xdr_flush_f_2_t_7[IPFlushRepository::ip_xdr_flush_f_2_t_7_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::ip_xdr_flush_f_2_t_8[IPFlushRepository::ip_xdr_flush_f_2_t_8_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::ip_xdr_flush_f_2_t_9[IPFlushRepository::ip_xdr_flush_f_2_t_9_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_2_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::flushGtpuCsvRecords_f_3()
{
	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_GTPU_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_0_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_0);
				break;
			case 1:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_1_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_1);
				break;
			case 2:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_2_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_2);
				break;
			case 3:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_3_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_3);
				break;
			case 4:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_4_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_4);
				break;
			case 5:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_5_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_5);
				break;
			case 6:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_6_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_6);
				break;
			case 7:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_7_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_7);
				break;
			case 8:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_8_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_8);
				break;
			case 9:
				storeGtpuZmqRecords(index, IPFlushRepository::ip_zmq_flush_f_3_t_9_cnt,IPFlushRepository::ip_zmq_flush_f_3_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_GTPU_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::ip_xdr_flush_f_3_t_0[IPFlushRepository::ip_xdr_flush_f_3_t_0_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::ip_xdr_flush_f_3_t_1[IPFlushRepository::ip_xdr_flush_f_3_t_1_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::ip_xdr_flush_f_3_t_2[IPFlushRepository::ip_xdr_flush_f_3_t_2_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::ip_xdr_flush_f_3_t_3[IPFlushRepository::ip_xdr_flush_f_3_t_3_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::ip_xdr_flush_f_3_t_4[IPFlushRepository::ip_xdr_flush_f_3_t_4_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::ip_xdr_flush_f_3_t_5[IPFlushRepository::ip_xdr_flush_f_3_t_5_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::ip_xdr_flush_f_3_t_6[IPFlushRepository::ip_xdr_flush_f_3_t_6_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::ip_xdr_flush_f_3_t_7[IPFlushRepository::ip_xdr_flush_f_3_t_7_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::ip_xdr_flush_f_3_t_8[IPFlushRepository::ip_xdr_flush_f_3_t_8_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::ip_xdr_flush_f_3_t_9[IPFlushRepository::ip_xdr_flush_f_3_t_9_cnt] = objXdrStore;
				IPFlushRepository::ip_xdr_flush_f_3_t_9_cnt++;
				break;
		}
	}
}


VOID GTPuFlusher::processDNSData(int index)
{
	switch(InstanceId)
	{
		case 0:
			processDNSData_f_0(index);
			break;
		case 1:
			processDNSData_f_1(index);
			break;
		case 2:
			processDNSData_f_2(index);
			break;
		case 3:
			processDNSData_f_3(index);
			break;

	}
}

//VOID GTPuFlusher::flushDNSData_sm_t(std::vector<dnsSession> &flushMap, int &dnsFlushMap_sm_cnt)
VOID GTPuFlusher::flushDNSData_sm_t(std::map<int, dnsSession> &flushMap, int &dnsFlushMap_sm_cnt)
{
	int cnt = dnsFlushMap_sm_cnt;
	for(int i=0; i<cnt; i++)
	{
		buildCSVDataDns(&flushMap[i]);
		strcpy(objXdrStore.xdr, csvXdr);
		flushDNSCsvRecords();
		dnsFlushMap_sm_cnt--;
	}
	flushMap.clear();
//	flushMap = std::vector<dnsSession>();
//	flushMap.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	dnsFlushMap_sm_cnt = 0;
}

VOID GTPuFlusher::processDNSData_f_0(int index)
{
	switch(index)
	{
		case 0:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_0, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_0_cnt);

			break;

		case 1:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_1, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_1_cnt);

			break;

		case 2:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_2, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_2_cnt);

			break;

		case 3:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_3, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_3_cnt);

			break;

		case 4:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_4, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_4_cnt);

			break;

		case 5:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_5, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_5_cnt);

			break;

		case 6:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_6, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_6_cnt);

			break;

		case 7:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_7, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_7_cnt);

			break;

		case 8:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_8, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_8_cnt);

			break;

		case 9:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_0_t_9, IPFlushRepository::dnsFlushMap_f_0_sm_0_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9, IPFlushRepository::dnsFlushMap_f_0_sm_1_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9, IPFlushRepository::dnsFlushMap_f_0_sm_2_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9, IPFlushRepository::dnsFlushMap_f_0_sm_3_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9, IPFlushRepository::dnsFlushMap_f_0_sm_4_t_9_cnt);

			break;
	}
}

VOID GTPuFlusher::processDNSData_f_1(int index)
{

	switch(index)
	{
		case 0:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_0, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_0_cnt);

			break;

		case 1:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_1, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_1_cnt);

			break;

		case 2:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_2, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_2_cnt);

			break;

		case 3:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_3, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_3_cnt);

			break;

		case 4:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_4, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_4_cnt);

			break;

		case 5:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_5, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_5_cnt);

			break;

		case 6:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_6, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_6_cnt);

			break;

		case 7:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_7, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_7_cnt);

			break;

		case 8:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_8, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_8_cnt);

			break;

		case 9:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_0_t_9, IPFlushRepository::dnsFlushMap_f_1_sm_0_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9, IPFlushRepository::dnsFlushMap_f_1_sm_1_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9, IPFlushRepository::dnsFlushMap_f_1_sm_2_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9, IPFlushRepository::dnsFlushMap_f_1_sm_3_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9, IPFlushRepository::dnsFlushMap_f_1_sm_4_t_9_cnt);

			break;
	}
}

VOID GTPuFlusher::processDNSData_f_2(int index)
{
	switch(index)
	{
		case 0:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_0, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_0_cnt);

			break;

		case 1:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_1, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_1_cnt);

			break;

		case 2:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_2, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_2_cnt);

			break;

		case 3:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_3, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_3_cnt);

			break;

		case 4:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_4, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_4_cnt);

			break;

		case 5:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_5, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_5_cnt);

			break;

		case 6:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_6, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_6_cnt);

			break;

		case 7:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_7, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_7_cnt);

			break;

		case 8:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_8, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_8_cnt);

			break;

		case 9:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_0_t_9, IPFlushRepository::dnsFlushMap_f_2_sm_0_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9, IPFlushRepository::dnsFlushMap_f_2_sm_1_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9, IPFlushRepository::dnsFlushMap_f_2_sm_2_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9, IPFlushRepository::dnsFlushMap_f_2_sm_3_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9, IPFlushRepository::dnsFlushMap_f_2_sm_4_t_9_cnt);

			break;
	}
}

VOID GTPuFlusher::processDNSData_f_3(int index)
{
	switch(index)
	{
		case 0:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_0, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_0_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_0_cnt);

			break;

		case 1:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_1, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_1_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_1_cnt);

			break;

		case 2:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_2, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_2_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_2_cnt);

			break;

		case 3:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_3, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_3_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_3_cnt);

			break;

		case 4:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_4, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_4_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_4_cnt);

			break;

		case 5:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_5, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_5_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_5_cnt);

			break;

		case 6:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_6, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_6_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_6_cnt);

			break;

		case 7:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_7, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_7_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_7_cnt);

			break;

		case 8:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_8, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_8_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_8_cnt);

			break;

		case 9:

			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_0_t_9, IPFlushRepository::dnsFlushMap_f_3_sm_0_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9, IPFlushRepository::dnsFlushMap_f_3_sm_1_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9, IPFlushRepository::dnsFlushMap_f_3_sm_2_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9, IPFlushRepository::dnsFlushMap_f_3_sm_3_t_9_cnt);
			flushDNSData_sm_t(IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9, IPFlushRepository::dnsFlushMap_f_3_sm_4_t_9_cnt);

			break;
	}
}


VOID GTPuFlusher::flushDNSCsvRecords()
{
	switch(InstanceId)
	{
		case 0:
			flushDNSCsvRecords_f_0();
			break;
		case 1:
			flushDNSCsvRecords_f_1();
			break;
		case 2:
			flushDNSCsvRecords_f_2();
			break;
		case 3:
			flushDNSCsvRecords_f_3();
			break;

	}
}

//VOID GTPuFlusher::storeDNSZmqRecords(int index, int &dns_zmq_flush_map_cnt, std::vector<xdrStore> &dns_zmq_flush_map)
VOID GTPuFlusher::storeDNSZmqRecords(int index, int &dns_zmq_flush_map_cnt, std::map<int,xdrStore> &dns_zmq_flush_map)
{

	if(dns_zmq_flush_map_cnt >= IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE || GTPZmqFlushStore::zmq_flush_t_index == index){
		// Do nothing, we don't want to push anything into Buffer
	}
	else
	{
		dns_zmq_flush_map[dns_zmq_flush_map_cnt] = objXdrStore;
		dns_zmq_flush_map_cnt++;
	}
}

VOID GTPuFlusher::flushDNSCsvRecords_f_0()
{

	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_DNS_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_0_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_0);
				break;
			case 1:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_1_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_1);
				break;
			case 2:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_2_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_2);
				break;
			case 3:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_3_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_3);
				break;
			case 4:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_4_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_4);
				break;
			case 5:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_5_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_5);
				break;
			case 6:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_6_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_6);
				break;
			case 7:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_7_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_7);
				break;
			case 8:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_8_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_8);
				break;
			case 9:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_0_t_9_cnt,IPFlushRepository::dns_zmq_flush_f_0_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_DNS_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::dns_xdr_flush_f_0_t_0[IPFlushRepository::dns_xdr_flush_f_0_t_0_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::dns_xdr_flush_f_0_t_1[IPFlushRepository::dns_xdr_flush_f_0_t_1_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::dns_xdr_flush_f_0_t_2[IPFlushRepository::dns_xdr_flush_f_0_t_2_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::dns_xdr_flush_f_0_t_3[IPFlushRepository::dns_xdr_flush_f_0_t_3_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::dns_xdr_flush_f_0_t_4[IPFlushRepository::dns_xdr_flush_f_0_t_4_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::dns_xdr_flush_f_0_t_5[IPFlushRepository::dns_xdr_flush_f_0_t_5_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::dns_xdr_flush_f_0_t_6[IPFlushRepository::dns_xdr_flush_f_0_t_6_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::dns_xdr_flush_f_0_t_7[IPFlushRepository::dns_xdr_flush_f_0_t_7_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::dns_xdr_flush_f_0_t_8[IPFlushRepository::dns_xdr_flush_f_0_t_8_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::dns_xdr_flush_f_0_t_9[IPFlushRepository::dns_xdr_flush_f_0_t_9_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_0_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::flushDNSCsvRecords_f_1()
{

	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_DNS_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_0_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_0);
				break;
			case 1:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_1_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_1);
				break;
			case 2:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_2_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_2);
				break;
			case 3:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_3_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_3);
				break;
			case 4:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_4_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_4);
				break;
			case 5:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_5_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_5);
				break;
			case 6:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_6_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_6);
				break;
			case 7:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_7_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_7);
				break;
			case 8:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_8_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_8);
				break;
			case 9:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_1_t_9_cnt,IPFlushRepository::dns_zmq_flush_f_1_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_DNS_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::dns_xdr_flush_f_1_t_0[IPFlushRepository::dns_xdr_flush_f_1_t_0_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::dns_xdr_flush_f_1_t_1[IPFlushRepository::dns_xdr_flush_f_1_t_1_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::dns_xdr_flush_f_1_t_2[IPFlushRepository::dns_xdr_flush_f_1_t_2_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::dns_xdr_flush_f_1_t_3[IPFlushRepository::dns_xdr_flush_f_1_t_3_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::dns_xdr_flush_f_1_t_4[IPFlushRepository::dns_xdr_flush_f_1_t_4_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::dns_xdr_flush_f_1_t_5[IPFlushRepository::dns_xdr_flush_f_1_t_5_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::dns_xdr_flush_f_1_t_6[IPFlushRepository::dns_xdr_flush_f_1_t_6_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::dns_xdr_flush_f_1_t_7[IPFlushRepository::dns_xdr_flush_f_1_t_7_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::dns_xdr_flush_f_1_t_8[IPFlushRepository::dns_xdr_flush_f_1_t_8_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::dns_xdr_flush_f_1_t_9[IPFlushRepository::dns_xdr_flush_f_1_t_9_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_1_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::flushDNSCsvRecords_f_2()
{

	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_DNS_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_0_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_0);
				break;
			case 1:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_1_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_1);
				break;
			case 2:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_2_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_2);
				break;
			case 3:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_3_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_3);
				break;
			case 4:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_4_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_4);
				break;
			case 5:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_5_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_5);
				break;
			case 6:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_6_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_6);
				break;
			case 7:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_7_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_7);
				break;
			case 8:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_8_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_8);
				break;
			case 9:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_2_t_9_cnt,IPFlushRepository::dns_zmq_flush_f_2_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_DNS_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::dns_xdr_flush_f_2_t_0[IPFlushRepository::dns_xdr_flush_f_2_t_0_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::dns_xdr_flush_f_2_t_1[IPFlushRepository::dns_xdr_flush_f_2_t_1_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::dns_xdr_flush_f_2_t_2[IPFlushRepository::dns_xdr_flush_f_2_t_2_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::dns_xdr_flush_f_2_t_3[IPFlushRepository::dns_xdr_flush_f_2_t_3_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::dns_xdr_flush_f_2_t_4[IPFlushRepository::dns_xdr_flush_f_2_t_4_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::dns_xdr_flush_f_2_t_5[IPFlushRepository::dns_xdr_flush_f_2_t_5_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::dns_xdr_flush_f_2_t_6[IPFlushRepository::dns_xdr_flush_f_2_t_6_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::dns_xdr_flush_f_2_t_7[IPFlushRepository::dns_xdr_flush_f_2_t_7_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::dns_xdr_flush_f_2_t_8[IPFlushRepository::dns_xdr_flush_f_2_t_8_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::dns_xdr_flush_f_2_t_9[IPFlushRepository::dns_xdr_flush_f_2_t_9_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_2_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::flushDNSCsvRecords_f_3()
{
	if(strlen(csvXdr) <= 0)
		return;

	gettimeofday(&curTime, NULL);

//	int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//	if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;
	int index = WRITE_TIME_INDEX(curTime.tv_sec);

	if(GContainer::config->gtpConfig->GN_DNS_FLUSH_FLAG)
	{
		switch(index)
		{
			case 0:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_0_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_0);
				break;
			case 1:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_1_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_1);
				break;
			case 2:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_2_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_2);
				break;
			case 3:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_3_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_3);
				break;
			case 4:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_4_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_4);
				break;
			case 5:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_5_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_5);
				break;
			case 6:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_6_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_6);
				break;
			case 7:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_7_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_7);
				break;
			case 8:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_8_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_8);
				break;
			case 9:
				storeDNSZmqRecords(index, IPFlushRepository::dns_zmq_flush_f_3_t_9_cnt,IPFlushRepository::dns_zmq_flush_f_3_t_9);
				break;
		}
	}

	if(GContainer::config->gtpConfig->GN_DNS_WRITE_XDR)
	{
		switch(index)
		{
			case 0:
				IPFlushRepository::dns_xdr_flush_f_3_t_0[IPFlushRepository::dns_xdr_flush_f_3_t_0_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_0_cnt++;
				break;
			case 1:
				IPFlushRepository::dns_xdr_flush_f_3_t_1[IPFlushRepository::dns_xdr_flush_f_3_t_1_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_1_cnt++;
				break;
			case 2:
				IPFlushRepository::dns_xdr_flush_f_3_t_2[IPFlushRepository::dns_xdr_flush_f_3_t_2_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_2_cnt++;
				break;
			case 3:
				IPFlushRepository::dns_xdr_flush_f_3_t_3[IPFlushRepository::dns_xdr_flush_f_3_t_3_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_3_cnt++;
				break;
			case 4:
				IPFlushRepository::dns_xdr_flush_f_3_t_4[IPFlushRepository::dns_xdr_flush_f_3_t_4_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_4_cnt++;
				break;
			case 5:
				IPFlushRepository::dns_xdr_flush_f_3_t_5[IPFlushRepository::dns_xdr_flush_f_3_t_5_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_5_cnt++;
				break;
			case 6:
				IPFlushRepository::dns_xdr_flush_f_3_t_6[IPFlushRepository::dns_xdr_flush_f_3_t_6_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_6_cnt++;
				break;
			case 7:
				IPFlushRepository::dns_xdr_flush_f_3_t_7[IPFlushRepository::dns_xdr_flush_f_3_t_7_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_7_cnt++;
				break;
			case 8:
				IPFlushRepository::dns_xdr_flush_f_3_t_8[IPFlushRepository::dns_xdr_flush_f_3_t_8_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_8_cnt++;
				break;
			case 9:
				IPFlushRepository::dns_xdr_flush_f_3_t_9[IPFlushRepository::dns_xdr_flush_f_3_t_9_cnt] = objXdrStore;
				IPFlushRepository::dns_xdr_flush_f_3_t_9_cnt++;
				break;
		}
	}
}

VOID GTPuFlusher::buildCSVDataGTPu(ipSession *pIpSession)
{
	csvXdr[0] = 0;
	tcpFlusherUtility->buildGTPuIPCsvBuffer(pIpSession, csvXdr);
}

VOID GTPuFlusher::buildCSVDataDns(dnsSession *pDnsSession)
{
	csvXdr[0] = 0;
	tcpFlusherUtility->buildDnsCsvBuffer(pDnsSession, csvXdr);
}

BOOL GTPuFlusher::isRepositoryInitialized(){
	return repoInitStatus;
}
