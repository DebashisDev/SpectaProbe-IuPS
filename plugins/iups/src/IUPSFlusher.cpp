/*
 * IUPSFlusher.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Debashis
 */

#include "IUPSFlusher.h"

IUPSFlusher::IUPSFlusher() {
	this->_name = "GTPFlusher ";
	this->setLogLevel(Log::theLog().level());
}

IUPSFlusher::~IUPSFlusher() {
}

BOOL IUPSFlusher::isRepositoryInitialized(){
}

VOID IUPSFlusher::run()
{
	struct tm *now_tm;
	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);

	ULONG curTimeEpochSec;
	int currentMin, currentHour, currentDay, currentMonth, currentYear;
	int lastProcessedIndex = -1;
	int curIndex = -1;

	lastProcessedIndex = 0;
	curTimeEpochSec = 0;
	currentMin = currentHour = currentDay = currentMonth = currentYear = 0;

	IPGlobal::lastFlusherEpochTimeSec = curTimeEpochSec = curTime.tv_sec;

	currentMin 		= now_tm->tm_min;
	currentHour 	= now_tm->tm_hour;
	currentDay 		= IPGlobal::currentDay = now_tm->tm_mday;
	currentMonth 	= 1 + now_tm->tm_mon;
	currentYear 	= 1900 + now_tm->tm_year;

//	curIndex = lastProcessedIndex = FLUSHER_READ_TIME_INDEX(curTime.tv_sec);

	curIndex = lastProcessedIndex = READ_TIME_INDEX(curTime.tv_sec);

	TheLog_nc_v2(Log::Info, name(),"  Starting Loop currentMin::%d| lastProcessedIndex::%d", currentMin, lastProcessedIndex);

	while(true)
	{
		usleep(10000);		// 100ms

		gettimeofday(&curTime, NULL);
		now_tm = localtime(&curTime.tv_sec);

		IPGlobal::lastFlusherEpochTimeSec = curTimeEpochSec = curTime.tv_sec;

		currentMin 		= now_tm->tm_min;
		currentHour 	= now_tm->tm_hour;
		currentDay 		= IPGlobal::currentDay = now_tm->tm_mday;
		currentMonth 	= 1 + now_tm->tm_mon;
		currentYear 	= 1900 + now_tm->tm_year;

//		curIndex = FLUSHER_READ_TIME_INDEX(curTime.tv_sec);

		curIndex = READ_TIME_INDEX(curTime.tv_sec);

		if(lastProcessedIndex != curIndex){
			lastProcessedIndex = curIndex;
			TheLog_nc_v2(Log::Info,name(),"  LastProcessedIndex [%d] != currentIndex [%d] so Flushing..", lastProcessedIndex, curIndex);
			usleep(10000);		// 100ms;	//Just to eliminate racing condition at 00 sec

			processStartEpochSec = IPGlobal::CURRENT_TIME_EPOCH_SEC;
			if(GContainer::config->IUPS_PROBE) {
				/* Flush GTPc Data */
				openCsvXdrFile(GContainer::config->iupsConfig->IUPS_FILE_PREFIX, currentMin, currentHour, currentDay, currentMonth, currentYear);
//				openTdrFile(GContainer::config->gtpConfig->GN_GTPC_FILE_PREFIX, currentMin, currentHour, currentDay, currentMonth, currentYear);
				flushIupsData(lastProcessedIndex, currentMin, currentHour, currentDay, currentMonth, currentYear);
				closeCsvXdrFile();
				closeTdrFile();
			}
		}
	}
}

VOID IUPSFlusher::flushIupsData_sm_t(
									std::map<uint32_t, string> &flushMap,
									int &ipFlushMap_sm_cnt,
									int &index,
									int &totalFlushCount,
									int &recordCount)
{
	int cnt = ipFlushMap_sm_cnt;
	for(int i=0; i<cnt; i++)
	{
		recordCount++;
		flushIupsCsvRecords(index, recordCount, totalFlushCount, flushMap[i]);
		ipFlushMap_sm_cnt--;
	}
	flushMap.clear();
	ipFlushMap_sm_cnt = 0;
}

VOID IUPSFlusher::flushIupsData(int index, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
{
	int totalFlushCount = 0;
	int recordCount = 0;

	switch(index)
	{
		case 0:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_0_cnt ;

			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_0, IUPSFlushRepository::iupsFlushMap_sm_0_t_0_cnt,index,totalFlushCount,recordCount);
			break;

		case 1:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_1_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_1, IUPSFlushRepository::iupsFlushMap_sm_0_t_1_cnt,index,totalFlushCount,recordCount);
			break;

		case 2:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_2_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_2, IUPSFlushRepository::iupsFlushMap_sm_0_t_2_cnt,index,totalFlushCount,recordCount);
			break;

		case 3:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_3_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_3, IUPSFlushRepository::iupsFlushMap_sm_0_t_3_cnt,index,totalFlushCount,recordCount);
			break;

		case 4:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_4_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_4, IUPSFlushRepository::iupsFlushMap_sm_0_t_4_cnt,index,totalFlushCount,recordCount);
			break;

		case 5:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_5_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_5, IUPSFlushRepository::iupsFlushMap_sm_0_t_5_cnt,index,totalFlushCount,recordCount);
			break;

		case 6:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_6_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_6, IUPSFlushRepository::iupsFlushMap_sm_0_t_6_cnt,index,totalFlushCount,recordCount);
			break;

		case 7:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_7_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_7, IUPSFlushRepository::iupsFlushMap_sm_0_t_7_cnt,index,totalFlushCount,recordCount);
			break;

		case 8:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_8_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_8, IUPSFlushRepository::iupsFlushMap_sm_0_t_8_cnt,index,totalFlushCount,recordCount);
			break;

		case 9:
			totalFlushCount = IUPSFlushRepository::iupsFlushMap_sm_0_t_9_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushIupsData_sm_t(IUPSFlushRepository::iupsFlushMap_sm_0_t_9, IUPSFlushRepository::iupsFlushMap_sm_0_t_9_cnt,index,totalFlushCount,recordCount);
			break;

	}
}

VOID IUPSFlusher::flushIupsCsvRecords(int index, int processCnt, int totalFlushCount, string &xdrdata)
{

	if(xdrdata.length() <= 0)
		return;

	if(GContainer::config->iupsConfig->IUPS_FLUSH_FLAG)
	{
		gettimeofday(&curTime, NULL);

//		index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//		if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;

		int index = WRITE_TIME_INDEX(curTime.tv_sec);

		switch(index)
		{
			case 0:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_0_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_0);
				break;
			case 1:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_1_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_1);
				break;
			case 2:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_2_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_2);
				break;
			case 3:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_3_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_3);
				break;
			case 4:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_4_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_4);
				break;
			case 5:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_5_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_5);
				break;
			case 6:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_6_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_6);
				break;
			case 7:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_7_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_7);
				break;
			case 8:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_8_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_8);
				break;
			case 9:
				storeIupsZmqRecords(index,xdrdata,IUPSZmqFlushStore::zmq_flush_map_iups_t_9_cnt,IUPSZmqFlushStore::zmq_flush_map_iups_t_9);
				break;
		}
	}

	if(GContainer::config->iupsConfig->IUPS_WRITE_XDR)
	{
//		csvIupsBatchCount++;
//		csvIupsDataGlb = csvIupsDataGlb + std::string(xdrdata) + "\n";
//
//		if((csvIupsBatchCount >= XDR_RECORDS_BATCH_SIZE) || (processCnt == totalFlushCount)){
//			IUPSXdrHandler << csvIupsDataGlb;
//			csvIupsDataGlb = "";
//			csvIupsBatchCount = 0;
//		}

		IUPSXdrHandler << xdrdata << "\n";
	}
}



VOID IUPSFlusher::storeIupsZmqRecords(int index, string xdrString, int &zmq_flush_map_iups_cnt, std::string (&zmq_flush_map_iups)[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE]){

	if(zmq_flush_map_iups_cnt >= IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE || IUPSZmqFlushStore::zmq_flush_t_index == index){
		// Do nothing, we don't want to push anything into Buffer
	}
	else
	{
		zmq_flush_map_iups[zmq_flush_map_iups_cnt] = xdrString;
		zmq_flush_map_iups_cnt++;
	}
}


VOID IUPSFlusher::openCsvXdrFile(string &prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
{
	TCHAR filePath[300];
	filePath[0] = 0;

	sprintf(filePath, "%s%s/%s_%d-%02d-%02d-%02d-%02d.csv",
					GContainer::config->XDR_DIR.c_str(),
					prefix.c_str(),
					prefix.c_str(),
					currentYear,
					currentMonth,
					currentDay,
					currentHour,
					currentMin);
	IUPSXdrHandler.open((char *)filePath, ios :: out | ios :: app);

	if(IUPSXdrHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] GTPc Csv file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] GTPc Csv file Open Success. !!!", filePath);
	}

	filePath[0] = 0;
}

VOID IUPSFlusher::closeCsvXdrFile()
{
	IUPSXdrHandler.close();
}

VOID IUPSFlusher::openTdrFile(string &prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
{
	TCHAR filePath[300];
	filePath[0] = 0;

	// Session TDR file
	sprintf(filePath, "%s%s/%s_%d-%02d-%02d-%02d-%02d.xdr",
					GContainer::config->XDR_DIR.c_str(),
					prefix.c_str(),
					prefix.c_str(),
					currentYear,
					currentMonth,
					currentDay,
					currentHour,
					currentMin);
	IUPSTdrHandler.open((char *)filePath, ios :: out | ios :: app);

	if(IUPSTdrHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] GTPc XDR file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] GTPc XDR file Open Success. !!!", filePath);
	}

	filePath[0] = 0;
}

VOID IUPSFlusher::closeTdrFile()
{
	IUPSTdrHandler.close();
}

