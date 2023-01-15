/*
 * GTPcFlusher.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: Deb
 */

#include "GTPcFlusher.h"

GTPcFlusher::GTPcFlusher() {
	_thisLogLevel = 0;
	this->_name = "GTPcFlusher";
	this->setLogLevel(Log::theLog().level());
}

GTPcFlusher::~GTPcFlusher() {
}

VOID GTPcFlusher::run()
{
	struct tm *now_tm;
	int currentMin, currentHour, currentDay, currentMonth, currentYear;
	int lastProcessedIndex = -1;
	int curIndex = -1;
	int prevMin = 0;

	lastProcessedIndex = 0;
	currentMin = currentHour = currentDay = currentMonth = currentYear = 0;

	repoInitStatus = true;

	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	//currentMin = prevMin = now_tm->tm_min;

//	curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX);
//	if(curIndex < 0) curIndex = IPGlobal::FLUSHER_TIMEINDEX + curIndex;

	curIndex = READ_TIME_INDEX(curTime.tv_sec);

	lastProcessedIndex = curIndex;

	while(IPGlobal::GN_GTPC_FLUSHER_RUNNING_STATUS)
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
				/* Flush GTPc Data */
				strcpy(csvXdr, "");
				openGTPcCsvXdrFile(GContainer::config->gtpConfig->GN_GTPC_FILE_PREFIX, currentMin, currentHour, currentDay, currentMonth, currentYear);
//				openGTPcTdrFile(GContainer::config->gtpConfig->GN_GTPC_FILE_PREFIX, currentMin, currentHour, currentDay, currentMonth, currentYear);
				flushGTPcV1Data(lastProcessedIndex);
				closeGTPcCsvXdrFile();
//				closeGTPcTdrFile();

				if(currentMin != prevMin){
					//Flush Active session count
					buildGTPcSessionCountCSV((curTime.tv_sec * 1000) + (curTime.tv_usec / 1000));
					flushGtpcCsvRecords(false,1,1);
					buildBwCSV((curTime.tv_sec * 1000) + (curTime.tv_usec / 1000));
					flushGtpcCsvRecords(false,1,1);
					prevMin = currentMin;
				}

			}

//			else if(GContainer::config->GN_PROBE && IPGlobal::gtpVersion == 2) {
//				flushGTPV2Data(lastProcessedSecRange, currentMin, currentHour, currentDay, currentMonth, currentYear);
//			}
//			lastProcessedIndex = FLUSHER_NEXT_TIME_INDEX(lastProcessedIndex);
//			lastProcessedIndex++;
//			if(lastProcessedIndex >= IPGlobal::FLUSHER_TIMEINDEX)
//				lastProcessedIndex = 0;
			lastProcessedIndex = NEXT_TIME_INDEX(lastProcessedIndex);
		}

//		TheLog_v1(Log::Info, "  GTPcFlusher", " Flusher will be invoked In [%d]", 60 - currentSec);
	}
	printf("GTPcFlusher Shutdown Completed\n");
}

VOID GTPcFlusher::flushGTPcV1Data_sm_t(
		int &gtpcV1FlushMap_sm_cnt,
		std::vector<GTPSession> &gtpcV1FlushMap_sm,
		int &index, int &totalFlushCount, int &recordCount)
{
	int recCount = 0;

	recCount = gtpcV1FlushMap_sm_cnt;
	if(recCount > 0)
	{
		for(int i=0; i<recCount; i++)
		{
			buildCSVDataGTPcV1(&gtpcV1FlushMap_sm[i]);
			flushGtpcCsvRecords(GContainer::config->gtpConfig->GN_GTPC_WRITE_XDR, recordCount, totalFlushCount);

//			buildTDRDataGTPcV1(gtpcV1FlushRepository_sm[arrId][bitId]);
//			flushTdrRecords(index,recordCount,totalFlushCount);

//			gtpcV1FlushMap_sm.erase(i);
			gtpcV1FlushMap_sm_cnt--;
		}
		gtpcV1FlushMap_sm.clear();
		gtpcV1FlushMap_sm = std::vector<GTPSession>();
		gtpcV1FlushMap_sm.reserve(GContainer::config->gtpConfig->GTPC_FLUSH_MAP_REPO_SIZE);
	}
	gtpcV1FlushMap_sm_cnt = 0;
}

VOID GTPcFlusher::flushGTPcV1Data(int index)
{
	int totalFlushCount = 0;
	int recordCount = 0;

	switch(index)
	{
		case 0:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0_cnt;

			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_0,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_0,index,totalFlushCount,recordCount);

			break;

		case 1:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_1,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_1,index,totalFlushCount,recordCount);

			break;

		case 2:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_2,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_2,index,totalFlushCount,recordCount);

			break;

		case 3:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_3,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_3,index,totalFlushCount,recordCount);

			break;

		case 4:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_4,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_4,index,totalFlushCount,recordCount);

			break;

		case 5:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_5,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_5,index,totalFlushCount,recordCount);

			break;

		case 6:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_6,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_6,index,totalFlushCount,recordCount);

			break;

		case 7:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_7,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_7,index,totalFlushCount,recordCount);

			break;

		case 8:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_8,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_8,index,totalFlushCount,recordCount);

			break;

		case 9:
			totalFlushCount = GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9_cnt + GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9_cnt;
			// TheLog_nc_v2(Log::Info, name(),"  Flushing GTPcV1 data for Index [%d] of size [%d]", index, totalFlushCount);
			if(totalFlushCount <= 0) break;

			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_0_t_9,index,totalFlushCount,recordCount);
			flushGTPcV1Data_sm_t(GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9_cnt,GTPFlushRepository::gtpcV1FlushMap_sm_1_t_9,index,totalFlushCount,recordCount);

			break;

	}
}


VOID GTPcFlusher::storeGtpcZmqRecords(int index, int &zmq_flush_map_gtpc_cnt, std::vector<xdrStore> &zmq_flush_map_gtpc){
	if(zmq_flush_map_gtpc_cnt >= GContainer::config->gtpConfig->GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE || GTPZmqFlushStore::zmq_flush_t_index == index){
			// Do nothing, we don't want to push anything into Buffer
	}
	else {
		//strcpy(zmq_flush_map_gtpc[zmq_flush_map_gtpc_cnt], csvXdr);
		strcpy(zmq_flush_map_gtpc[zmq_flush_map_gtpc_cnt].xdr, csvXdr);
		zmq_flush_map_gtpc_cnt++;
	}
}

//VOID GTPcFlusher::flushGtpcCsvRecords(int index, int writeIndex, int processCnt, int totalFlushCount)
VOID GTPcFlusher::flushGtpcCsvRecords(bool writexdr, int processCnt, int totalFlushCount)
{
	if(strlen(csvXdr) <= 0)
		return;

	if(GContainer::config->gtpConfig->GN_GTPC_FLUSH_FLAG)
	{
		gettimeofday(&curTime, NULL);
//		int index = FLUSHER_WRITE_TIME_INDEX(curTime.tv_sec);

//		int index = (((curTime.tv_sec % 100) /10)  % IPGlobal::ZMQ_FLUSHER_TIMEINDEX) + 1;
//		if(index >= IPGlobal::ZMQ_FLUSHER_TIMEINDEX) index = index - IPGlobal::ZMQ_FLUSHER_TIMEINDEX;

		int index = WRITE_TIME_INDEX(curTime.tv_sec);

		switch(index)
		{
			case 0:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_0_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_0);
				break;
			case 1:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_1_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_1);
				break;
			case 2:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_2_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_2);
				break;
			case 3:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_3_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_3);
				break;
			case 4:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_4_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_4);
				break;
			case 5:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_5_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_5);
				break;
			case 6:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_6_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_6);
				break;
			case 7:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_7_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_7);
				break;
			case 8:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_8_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_8);
				break;
			case 9:
				storeGtpcZmqRecords(index,GTPZmqFlushStore::zmq_flush_map_gtpc_t_9_cnt,GTPZmqFlushStore::zmq_flush_map_gtpc_t_9);
				break;
		}
	}

	if(writexdr)
	{
		csvGTPcBatchCount++;
		csvGTPcDataGlb = csvGTPcDataGlb + std::string(csvXdr) + "\n";

		if((csvGTPcBatchCount >= XDR_RECORDS_BATCH_SIZE) || (processCnt == totalFlushCount)){
			//Write to file
			GTPcXdrHandler << csvGTPcDataGlb;
			csvGTPcDataGlb = "";
	//		TheLog_v3(Log::Info, "  GTPcFlusher", " GTPc CSV XDR Written for Sec [%dx] :: [%d] of [%d] records", index, csvWriteBatchCount, totalFlushCount);
			csvGTPcBatchCount = 0;
		}
	}
}

VOID GTPcFlusher::flushTdrRecords(int index, int processCnt, int totalFlushCount)
{
	tdrGTPcBatchCount++;
	tdrGTPcDataGlb.append(tdrXdr).append("\n");

	if((tdrGTPcBatchCount >= 10000) || (processCnt == totalFlushCount)) {
		//Write to file
		GTPcTdrHandler << tdrGTPcDataGlb << endl;
		tdrGTPcDataGlb = "";
//		TheLog_v3(Log::Info, "  GTPcFlusher", " GTPc TRD XDR Written for Sec [%dx] :: [%d] of [%d] records", index, tdrWriteBatchCount, totalFlushCount);
		tdrGTPcBatchCount = 0;
	}
}


VOID GTPcFlusher::buildGTPcSessionCountCSV(long timems)
{

	//Wait if counting process is on
	while(GTPStats::gtp_glb_sessions_cnt_process)
		usleep(500000);	//500 ms

	csvXdr[0] = 0;

	sprintf(csvXdr, "%d,%d,2123,GTPc-v1,%ld,%u,%d,%d,%d,%lu",
			IPGlobal::PROBE_ID, XDR_ID_GTPC_SESSION_CNT,
			timems,
			GTPStats::gtp_glb_active_sessions_cnt,
			GTPStats::gtp_glb_sessions_total_cnt,
			GTPStats::gtp_glb_sessions_utran_cnt,
			GTPStats::gtp_glb_sessions_geran_cnt,
			(IPGlobal::BW_MBPS_INTF_0+IPGlobal::BW_MBPS_INTF_1+IPGlobal::BW_MBPS_INTF_2+IPGlobal::BW_MBPS_INTF_3));
}

VOID GTPcFlusher::buildBwCSV(long timems)
{

	csvXdr[0] = 0;

	bwData bw_i_0;
	bwData bw_i_1;
	bwData bw_i_2;
	bwData bw_i_3;

	bw_i_0.Volume = IPGlobal::BW_MBPS_i_0_r_0.Volume + IPGlobal::BW_MBPS_i_0_r_1.Volume + IPGlobal::BW_MBPS_i_0_r_3.Volume + IPGlobal::BW_MBPS_i_0_r_3.Volume;
	bw_i_0.upVolume = IPGlobal::BW_MBPS_i_0_r_0.upVolume + IPGlobal::BW_MBPS_i_0_r_1.upVolume + IPGlobal::BW_MBPS_i_0_r_3.upVolume + IPGlobal::BW_MBPS_i_0_r_3.upVolume;
	bw_i_0.dnVolume = IPGlobal::BW_MBPS_i_0_r_0.dnVolume + IPGlobal::BW_MBPS_i_0_r_1.dnVolume + IPGlobal::BW_MBPS_i_0_r_3.dnVolume + IPGlobal::BW_MBPS_i_0_r_3.dnVolume;

	bw_i_1.Volume = IPGlobal::BW_MBPS_i_1_r_0.Volume + IPGlobal::BW_MBPS_i_1_r_1.Volume + IPGlobal::BW_MBPS_i_1_r_3.Volume + IPGlobal::BW_MBPS_i_1_r_3.Volume;
	bw_i_1.upVolume = IPGlobal::BW_MBPS_i_1_r_0.upVolume + IPGlobal::BW_MBPS_i_1_r_1.upVolume + IPGlobal::BW_MBPS_i_1_r_3.upVolume + IPGlobal::BW_MBPS_i_1_r_3.upVolume;
	bw_i_1.dnVolume = IPGlobal::BW_MBPS_i_1_r_0.dnVolume + IPGlobal::BW_MBPS_i_1_r_1.dnVolume + IPGlobal::BW_MBPS_i_1_r_3.dnVolume + IPGlobal::BW_MBPS_i_1_r_3.dnVolume;

	bw_i_2.Volume = IPGlobal::BW_MBPS_i_2_r_0.Volume + IPGlobal::BW_MBPS_i_2_r_1.Volume + IPGlobal::BW_MBPS_i_2_r_3.Volume + IPGlobal::BW_MBPS_i_2_r_3.Volume;
	bw_i_2.upVolume = IPGlobal::BW_MBPS_i_2_r_0.upVolume + IPGlobal::BW_MBPS_i_2_r_1.upVolume + IPGlobal::BW_MBPS_i_2_r_3.upVolume + IPGlobal::BW_MBPS_i_2_r_3.upVolume;
	bw_i_2.dnVolume = IPGlobal::BW_MBPS_i_2_r_0.dnVolume + IPGlobal::BW_MBPS_i_2_r_1.dnVolume + IPGlobal::BW_MBPS_i_2_r_3.dnVolume + IPGlobal::BW_MBPS_i_2_r_3.dnVolume;

	bw_i_3.Volume = IPGlobal::BW_MBPS_i_3_r_0.Volume + IPGlobal::BW_MBPS_i_3_r_1.Volume + IPGlobal::BW_MBPS_i_3_r_3.Volume + IPGlobal::BW_MBPS_i_3_r_3.Volume;
	bw_i_3.upVolume = IPGlobal::BW_MBPS_i_3_r_0.upVolume + IPGlobal::BW_MBPS_i_3_r_1.upVolume + IPGlobal::BW_MBPS_i_3_r_3.upVolume + IPGlobal::BW_MBPS_i_3_r_3.upVolume;
	bw_i_3.dnVolume = IPGlobal::BW_MBPS_i_3_r_0.dnVolume + IPGlobal::BW_MBPS_i_3_r_1.dnVolume + IPGlobal::BW_MBPS_i_3_r_3.dnVolume + IPGlobal::BW_MBPS_i_3_r_3.dnVolume;

	sprintf(csvXdr, "%d,%d,"
					"%ld,"
					"%lu,%lu,%lu,"
					"%lu,%lu,%lu,"
					"%lu,%lu,%lu,"
					"%lu,%lu,%lu",
			IPGlobal::PROBE_ID, XDR_ID_IP_BW,
			timems,
			bw_i_0.Volume, bw_i_0.upVolume, bw_i_0.dnVolume,
			bw_i_1.Volume, bw_i_1.upVolume, bw_i_1.dnVolume,
			bw_i_2.Volume, bw_i_2.upVolume, bw_i_2.dnVolume,
			bw_i_3.Volume, bw_i_3.upVolume, bw_i_3.dnVolume);

//	printf("GTPcFlusher BwCSV :: %s\n",csvXdr);
}

VOID GTPcFlusher::buildCSVDataGTPcV1(GTPSession *pGtpSession)
{

	csvXdr[0] = 0;
	char endCause[100];

	if(strlen(pGtpSession->SessionId) == 0) {
		sprintf(csvXdr, "%s", "");
		return;
	}

	if(pGtpSession->EndCauseId == -1)
	{
		strcpy(endCause, "NA");
	}else{
		strcpy(endCause, (const char *)GTPC_CAUSE_CODE[pGtpSession->EndCauseId].c_str());
	}
	sprintf(csvXdr,
			"%d,%d,2123,GTPc-v1,%s,"
			"%llu,%llu,"
			"%s,"
			"%s,%s,%u,%u,"
			"%d,%d,%d,"
			"%s,%s,%s,"
			"%d,%s,"
			"%d,%s,"
			"%u,%u,%u,%u,"
			"%s,"
			"%d,%s,"
			"%d,%s,"
			"%d,%d,%d,%d,%d,"
			"%s,"
			"%d,%d,"
			"%d,%s,%lu,"
			"%d,%d,%d,%d,%d,%d,"
			"%u,%u,"
			"%d,%s,"
			"%d,%s",
//			"%u,%u,%u,%u,"
//			"%s,%s,%u,%u,"
//			"%u,%llu",
			IPGlobal::PROBE_ID, XDR_ID_GTPC_SESSION, pGtpSession->SessionId,
			pGtpSession->StartTimeEpochNanoSec, pGtpSession->EndTimeEpochNanoSec,
			MSG_DIRECTION[pGtpSession->dirSgsnGgsn].c_str(),
			pGtpSession->sgsnMACAddr, pGtpSession->ggsnMACAddr, pGtpSession->sgsnIPAddr, pGtpSession->ggsnIPAddr,
			pGtpSession->VLanId, pGtpSession->sgsnPort, pGtpSession->ggsnPort,
			pGtpSession->IMSI,pGtpSession->IMEI, pGtpSession->MSISDN,
			pGtpSession->GTPReqMsgId, MSG_DESC[pGtpSession->GTPReqMsgId].c_str(),
			pGtpSession->RAT,RAT_TYPES[pGtpSession->RAT].c_str(),
			pGtpSession->tunnel_id_control_up, pGtpSession->tunnel_id_control_dn, pGtpSession->tunnel_id_data_up, pGtpSession->tunnel_id_data_dn,
			pGtpSession->userIPAddress,
			pGtpSession->GTPRspMsgId,MSG_DESC[pGtpSession->GTPRspMsgId].c_str(),
			pGtpSession->EndCauseId,endCause,
			pGtpSession->MCC, pGtpSession->MNC,pGtpSession->LAC,pGtpSession->RAC,pGtpSession->CI,
			pGtpSession->APN,
			pGtpSession->ByteSizeUL, pGtpSession->ByteSizeDL,
			pGtpSession->flushType, FLUSH_TYPE[pGtpSession->flushType].c_str(), pGtpSession->FlushTimeEpochMicroSec,
			pGtpSession->req_mbrupl, pGtpSession->req_mbrdnl, pGtpSession->res_mbrupl, pGtpSession->res_mbrdnl, pGtpSession->req_ext_mbrdnl, pGtpSession->res_ext_mbrdnl,
			pGtpSession->pkt_tunnel_id_up, pGtpSession->pkt_tunnel_id_dn,
			pGtpSession->RATOld,RAT_TYPES[pGtpSession->RATOld].c_str(),
			pGtpSession->create_step, pGtpSession->IMSI_OLD);//,
//			pGtpSession->old_tunnel_id_control_up, pGtpSession->old_tunnel_id_control_dn, pGtpSession->old_tunnel_id_data_up, pGtpSession->old_tunnel_id_data_dn,
//			pGtpSession->old_sgsnMACAddr, pGtpSession->old_ggsnMACAddr, pGtpSession->old_sgsnIPAddr, pGtpSession->old_ggsnIPAddr,
//			pGtpSession->old_sequence_no, pGtpSession->old_StartTimeEpochNanoSec);
}

VOID GTPcFlusher::buildTDRDataGTPcV1(GTPSession *pGtpSession)
{
//	string tdrdata = "";
//	char buffer[100];
//	tdrXdr[0] = 0;
//
//	char prefix[4] = "_p_";
//	strcpy(buffer, "-- GTPc TDR -------------------------------------\n");
//	tdrdata.assign(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sProbe_Id			: %d\n", prefix, IPGlobal::PROBE_ID);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sXDR_Id			: %d\n", prefix, XDR_ID_GTPC_SESSION);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sProtocol_Id			: 2123\n", prefix);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sProtocol_Desc		: GTPc\n", prefix);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
////	sprintf(buffer, "	%sInterface			: %d\n", prefix, pGtpSession->interfaceId);
////	tdrdata.append(buffer);
////	buffer[0] = '\0';
//	sprintf(buffer, "	%sSession_Id			: %s\n", prefix, pGtpSession->SessionId);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
////	sprintf(buffer, "	%sStart_Time			: %s\n", prefix, pGtpSession->StartTime.c_str());
////	tdrdata.append(buffer);
////	buffer[0] = '\0';
//	sprintf(buffer, "	%sStart_Time_MS		: %lu\n", prefix, pGtpSession->StartTimeEpochSec);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
////	sprintf(buffer, "	%sEnd_Time			: %s\n", prefix, pGtpSession->EndTime.c_str());
////	tdrdata.append(buffer);
////	buffer[0] = '\0';
//	sprintf(buffer, "	%sEnd_Time_MS	 		: %lu\n", prefix,  pGtpSession->EndTimeEpochSec);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sInitiation_Dir		: %s\n", prefix, MSG_DIRECTION[pGtpSession->dirSgsnGgsn].c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sSource_Mac_Addr		: %s\n", prefix, pGtpSession->sgsnMACAddr);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sDestination_Mac_Addr		: %s\n", prefix, pGtpSession->ggsnMACAddr);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sSource_IP_Addr		: %ld\n", prefix, pGtpSession->sgsnIPAddr);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sDestination_IP_Addr		: %ld\n", prefix, pGtpSession->ggsnIPAddr);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sVLAN				: %d\n", prefix, pGtpSession->VLanId);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sOPC				: %d\n", prefix, pGtpSession->sgsnPort);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sDPC				: %d\n", prefix, pGtpSession->ggsnPort);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	if(strlen(pGtpSession->MSISDN) == 0){
//		sprintf(buffer, "	%sMSISDN			: NA\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sMSISDN			: %s\n", prefix, pGtpSession->MSISDN);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	if(strlen(pGtpSession->IMSI) == 0){
//		sprintf(buffer, "	%sIMSI				: NA\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sIMSI				: %s\n", prefix, pGtpSession->IMSI);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	if(strlen(pGtpSession->IMEI) == 0){
//		sprintf(buffer, "	%sIMEI				: NA\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sIMEI				: %s\n", prefix, pGtpSession->IMEI);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	if(pGtpSession->GTPReqMsgId == -1){
//		sprintf(buffer, "	%sGTPc_Procedure_Id		:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPc_Procedure_Desc		:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sGTPc_Procedure_Id		: %d\n", prefix, pGtpSession->GTPReqMsgId);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPc_Procedure_Desc		: %s\n", prefix, MSG_DESC[pGtpSession->GTPReqMsgId].c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	sprintf(buffer, "	%sRAT_Id			: %d\n", prefix, pGtpSession->RAT);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sRAT_Desc			: %s\n", prefix, RAT_TYPES[pGtpSession->RAT].c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sTunnel_Id_C_Dn		: %zu\n", prefix, pGtpSession->tunnel_id_control_dn);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sTunnel_Id_C_Up		: %zu\n", prefix, pGtpSession->tunnel_id_control_up);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sTunnel_Id_D_Dn		: %zu\n", prefix, pGtpSession->tunnel_id_data_dn);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sTunnel_Id_D_Up		: %zu\n", prefix, pGtpSession->tunnel_id_data_up);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sCharging GW			: %s\n", prefix, pGtpSession->chargingGWAddr);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sPDP_Addr_Allocated		: %s\n", prefix, pGtpSession->userIPAddress);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	if(pGtpSession->GTPRspMsgId == -1){
//		sprintf(buffer, "	%sGTPC_End_Procedure_Id	:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPC_End_Procedure_Desc	:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}else{
//		sprintf(buffer, "	%sGTPC_End_Procedure_Id	: %d\n", prefix, pGtpSession->GTPRspMsgId);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//		sprintf(buffer, "	%sGTPC_End_Procedure_Desc	: %s\n", prefix, MSG_DESC[pGtpSession->GTPRspMsgId].c_str());
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
////	sprintf(buffer, "	%sPacket #			: %lu\n", prefix, pGtpSession->rspPacketNo);
////	tdrdata.append(buffer);
////	buffer[0] = '\0';
//
//	if(pGtpSession->EndCauseId == -1){
//		sprintf(buffer, "	%sEnd_Cause			:\n", prefix);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//	else{
//		sprintf(buffer, "	%sEnd_Cause			: %d\n", prefix, pGtpSession->EndCauseId);
//		tdrdata.append(buffer);
//		buffer[0] = '\0';
//	}
//
//	sprintf(buffer, "	%sEnd_Cause_Desc		: %s\n", prefix, GTPC_CAUSE_CODE[pGtpSession->EndCauseId].c_str());
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sPLMN_Id			: %d-%d\n", prefix, pGtpSession->MCC, pGtpSession->MNC);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sLAC_Id			: %d\n", prefix, pGtpSession->LAC);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sRAC_Id			: %d\n", prefix, pGtpSession->RAC);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sCell_Id			: %d\n", prefix, pGtpSession->CI);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	%sAPN				: %s\n", prefix, pGtpSession->APN);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sBytes_Transfer_ul		: %d\n", prefix, pGtpSession->ByteSizeUL);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sBytes_Transfer_dl		: %d\n", prefix, pGtpSession->ByteSizeDL);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sMax bit rate Uplink Req	: %d kbps\n", prefix, pGtpSession->req_mbrupl);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sMax bit rate Dnlink Req	: %d kbps\n", prefix, pGtpSession->req_mbrdnl);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sMax bit rate Uplink Rsp	: %d kbps\n", prefix, pGtpSession->res_mbrupl);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//	sprintf(buffer, "	%sMax bit rate Dnlink Rsp	: %d Kbps\n", prefix, pGtpSession->res_mbrdnl);
//	tdrdata.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "-------------------------------------------------\n");
//	tdrdata.append(buffer);
//
//	strcpy(tdrXdr,tdrdata.c_str());
}

VOID GTPcFlusher::openGTPcCsvXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
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
	GTPcXdrHandler.open((char *)filePath, ios :: out | ios :: app);

	if(GTPcXdrHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] GTPc Csv file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] GTPc Csv file Open Success. !!!", filePath);
	}

	filePath[0] = 0;
}

VOID GTPcFlusher::closeGTPcCsvXdrFile()
{
	GTPcXdrHandler.close();
}

VOID GTPcFlusher::openGTPcTdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
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
	GTPcTdrHandler.open((char *)filePath, ios :: out | ios :: app);

	if(GTPcTdrHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] GTPc XDR file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] GTPc XDR file Open Success. !!!", filePath);
	}
}

VOID GTPcFlusher::closeGTPcTdrFile()
{
	GTPcTdrHandler.close();
}

BOOL GTPcFlusher::isRepositoryInitialized(){
	return repoInitStatus;
}


