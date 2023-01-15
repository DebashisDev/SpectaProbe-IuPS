/*
 * GTPFlusher.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: Deb
 */


#include "GTPXdrFlusher.h"

GTPXdrFlusher::GTPXdrFlusher() {
	_thisLogLevel = 0;
	this->_name = "GTPXdrFlusher";
	this->setLogLevel(Log::theLog().level());
}

GTPXdrFlusher::~GTPXdrFlusher() {
}

BOOL GTPXdrFlusher::isRepositoryInitialized() {
	return repoInitStatus;
}

VOID GTPXdrFlusher::run()
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

	while(IPGlobal::GN_XDR_RUNNING_STATUS)
	{
		sleep(1);
		gettimeofday(&curTime, NULL);

//		curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX);
//		if(curIndex < 0) curIndex = IPGlobal::FLUSHER_TIMEINDEX + curIndex;
		curIndex = READ_TIME_INDEX(curTime.tv_sec);

		while(lastProcessedIndex != curIndex){

			usleep(100000);		// 100ms;	//Just to eliminate racing condition at 00 sec

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
				openGTPuCsvXdrFile(GContainer::config->gtpConfig->GN_GTPU_FILE_PREFIX, currentMin, currentHour, currentDay, currentMonth, currentYear);
				processGTPu(lastProcessedIndex);
				closeGTPuCsvXdrFile();

				/* Flush DNS Data */
				strcpy(csvXdr, "");
				openDnsCsvXdrFile(GContainer::config->gtpConfig->GN_DNS_FILE_PREFIX, currentMin, currentHour, currentDay, currentMonth, currentYear);
				processDns(lastProcessedIndex);
				closeDnsCsvXdrFile();
			}
			lastProcessedIndex = NEXT_TIME_INDEX(lastProcessedIndex);

//			lastProcessedIndex++;
//			if(lastProcessedIndex >= IPGlobal::FLUSHER_TIMEINDEX)
//				lastProcessedIndex = 0;
		}

//		TheLog_v1(Log::Info, "  GTPFlusher", " Flusher will be invoked In [%d]", 60 - currentSec);
	}
	printf("GTPFlusher Shutdown Completed\n");
}

//VOID GTPXdrFlusher::writeGTPuCsvData(std::vector<xdrStore> &ip_flush_map, int &ip_xdr_flush_map_cnt)
VOID GTPXdrFlusher::writeGTPuCsvData(std::map<int, xdrStore> &ip_flush_map, int &ip_xdr_flush_map_cnt)
{

	int totalFlushCount = ip_xdr_flush_map_cnt;
	if(totalFlushCount > 0)
	{
		for(int i=0; i<totalFlushCount; i++)
		{
			csvGTPuBatchCount++;
			csvGTPuDataGlb = csvGTPuDataGlb + std::string(ip_flush_map[i].xdr) + "\n";

			if((csvGTPuBatchCount >= XDR_RECORDS_BATCH_SIZE) || (i == (totalFlushCount  - 1))){
				//Write to file
				GTPuXdrHandler << csvGTPuDataGlb;
				csvGTPuDataGlb = "";
				csvGTPuBatchCount = 0;
			}
			ip_xdr_flush_map_cnt--;
		}
		ip_flush_map.clear();
//		ip_flush_map = std::vector<xdrStore>();
//		ip_flush_map.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	}
	ip_xdr_flush_map_cnt = 0;
}

VOID GTPXdrFlusher::processGTPu(int index)
{
	switch(index)
	{
		case 0:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_0, IPFlushRepository::ip_xdr_flush_f_0_t_0_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_0, IPFlushRepository::ip_xdr_flush_f_1_t_0_cnt);
			}

			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_0, IPFlushRepository::ip_xdr_flush_f_2_t_0_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_0, IPFlushRepository::ip_xdr_flush_f_3_t_0_cnt);
			}
			break;

		case 1:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_1, IPFlushRepository::ip_xdr_flush_f_0_t_1_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_1, IPFlushRepository::ip_xdr_flush_f_1_t_1_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_1, IPFlushRepository::ip_xdr_flush_f_2_t_1_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_1, IPFlushRepository::ip_xdr_flush_f_3_t_1_cnt);
			}
			break;

		case 2:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_2, IPFlushRepository::ip_xdr_flush_f_0_t_2_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_2, IPFlushRepository::ip_xdr_flush_f_1_t_2_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_2, IPFlushRepository::ip_xdr_flush_f_2_t_2_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_2, IPFlushRepository::ip_xdr_flush_f_3_t_2_cnt);
			}
			break;

		case 3:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_3, IPFlushRepository::ip_xdr_flush_f_0_t_3_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_3, IPFlushRepository::ip_xdr_flush_f_1_t_3_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_3, IPFlushRepository::ip_xdr_flush_f_2_t_3_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_3, IPFlushRepository::ip_xdr_flush_f_3_t_3_cnt);
			}
			break;

		case 4:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_4, IPFlushRepository::ip_xdr_flush_f_0_t_4_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_4, IPFlushRepository::ip_xdr_flush_f_1_t_4_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_4, IPFlushRepository::ip_xdr_flush_f_2_t_4_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_4, IPFlushRepository::ip_xdr_flush_f_3_t_4_cnt);
			}
			break;

		case 5:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_5, IPFlushRepository::ip_xdr_flush_f_0_t_5_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_5, IPFlushRepository::ip_xdr_flush_f_1_t_5_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_5, IPFlushRepository::ip_xdr_flush_f_2_t_5_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_5, IPFlushRepository::ip_xdr_flush_f_3_t_5_cnt);
			}
			break;

		case 6:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_6, IPFlushRepository::ip_xdr_flush_f_0_t_6_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_6, IPFlushRepository::ip_xdr_flush_f_1_t_6_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_6, IPFlushRepository::ip_xdr_flush_f_2_t_6_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_6, IPFlushRepository::ip_xdr_flush_f_3_t_6_cnt);
			}
			break;

		case 7:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_7, IPFlushRepository::ip_xdr_flush_f_0_t_7_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_7, IPFlushRepository::ip_xdr_flush_f_1_t_7_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_7, IPFlushRepository::ip_xdr_flush_f_2_t_7_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_7, IPFlushRepository::ip_xdr_flush_f_3_t_7_cnt);
			}
			break;

		case 8:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_8, IPFlushRepository::ip_xdr_flush_f_0_t_8_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_8, IPFlushRepository::ip_xdr_flush_f_1_t_8_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_8, IPFlushRepository::ip_xdr_flush_f_2_t_8_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_8, IPFlushRepository::ip_xdr_flush_f_3_t_8_cnt);
			}
			break;

		case 9:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_0_t_9, IPFlushRepository::ip_xdr_flush_f_0_t_9_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_1_t_9, IPFlushRepository::ip_xdr_flush_f_1_t_9_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_2_t_9, IPFlushRepository::ip_xdr_flush_f_2_t_9_cnt);
				writeGTPuCsvData(IPFlushRepository::ip_xdr_flush_f_3_t_9, IPFlushRepository::ip_xdr_flush_f_3_t_9_cnt);
			}
			break;
	}
}


//VOID GTPXdrFlusher::writeDnsCsvData(std::vector<xdrStore> &dns_flush_map, int &dns_xdr_flush_map_cnt)
VOID GTPXdrFlusher::writeDnsCsvData(std::map<int, xdrStore> &dns_flush_map, int &dns_xdr_flush_map_cnt)
{

	int totalFlushCount = dns_xdr_flush_map_cnt;
	if(totalFlushCount > 0)
	{
		for(int i=0; i<totalFlushCount; i++)
		{
			csvDNSBatchCount++;
			csvDNSDataGlb = csvDNSDataGlb + std::string(dns_flush_map[i].xdr) + "\n";

			if((csvDNSBatchCount >= XDR_RECORDS_BATCH_SIZE) || (i == (totalFlushCount  - 1))){
				//Write to file
				DnsXdrHandler << csvDNSDataGlb;
				csvDNSDataGlb = "";
				csvDNSBatchCount = 0;
			}
			dns_xdr_flush_map_cnt--;
		}
		dns_flush_map.clear();
//		dns_flush_map = std::vector<xdrStore>();
//		dns_flush_map.reserve(IPGlobal::IP_SESSION_FLUSH_TIME_INDEX_REPO_SIZE);
	}
	dns_xdr_flush_map_cnt = 0;
}

VOID GTPXdrFlusher::processDns(int index)
{

	switch(index)
	{
		case 0:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_0, IPFlushRepository::dns_xdr_flush_f_0_t_0_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_0, IPFlushRepository::dns_xdr_flush_f_1_t_0_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_0, IPFlushRepository::dns_xdr_flush_f_2_t_0_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_0, IPFlushRepository::dns_xdr_flush_f_3_t_0_cnt);
			}
			break;

		case 1:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_1, IPFlushRepository::dns_xdr_flush_f_0_t_1_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_1, IPFlushRepository::dns_xdr_flush_f_1_t_1_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_1, IPFlushRepository::dns_xdr_flush_f_2_t_1_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_1, IPFlushRepository::dns_xdr_flush_f_3_t_1_cnt);
			}
			break;

		case 2:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_2, IPFlushRepository::dns_xdr_flush_f_0_t_2_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_2, IPFlushRepository::dns_xdr_flush_f_1_t_2_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_2, IPFlushRepository::dns_xdr_flush_f_2_t_2_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_2, IPFlushRepository::dns_xdr_flush_f_3_t_2_cnt);
			}
			break;

		case 3:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_3, IPFlushRepository::dns_xdr_flush_f_0_t_3_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_3, IPFlushRepository::dns_xdr_flush_f_1_t_3_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_3, IPFlushRepository::dns_xdr_flush_f_2_t_3_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_3, IPFlushRepository::dns_xdr_flush_f_3_t_3_cnt);
			}
			break;

		case 4:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_4, IPFlushRepository::dns_xdr_flush_f_0_t_4_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_4, IPFlushRepository::dns_xdr_flush_f_1_t_4_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_4, IPFlushRepository::dns_xdr_flush_f_2_t_4_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_4, IPFlushRepository::dns_xdr_flush_f_3_t_4_cnt);
			}
			break;

		case 5:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_5, IPFlushRepository::dns_xdr_flush_f_0_t_5_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_5, IPFlushRepository::dns_xdr_flush_f_1_t_5_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_5, IPFlushRepository::dns_xdr_flush_f_2_t_5_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_5, IPFlushRepository::dns_xdr_flush_f_3_t_5_cnt);
			}
			break;

		case 6:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_6, IPFlushRepository::dns_xdr_flush_f_0_t_6_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_6, IPFlushRepository::dns_xdr_flush_f_1_t_6_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_6, IPFlushRepository::dns_xdr_flush_f_2_t_6_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_6, IPFlushRepository::dns_xdr_flush_f_3_t_6_cnt);
			}
			break;

		case 7:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_7, IPFlushRepository::dns_xdr_flush_f_0_t_7_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_7, IPFlushRepository::dns_xdr_flush_f_1_t_7_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_7, IPFlushRepository::dns_xdr_flush_f_2_t_7_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_7, IPFlushRepository::dns_xdr_flush_f_3_t_7_cnt);
			}
			break;

		case 8:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_8, IPFlushRepository::dns_xdr_flush_f_0_t_8_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_8, IPFlushRepository::dns_xdr_flush_f_1_t_8_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_8, IPFlushRepository::dns_xdr_flush_f_2_t_8_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_8, IPFlushRepository::dns_xdr_flush_f_3_t_8_cnt);
			}
			break;

		case 9:
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 1) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_0_t_9, IPFlushRepository::dns_xdr_flush_f_0_t_9_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_1_t_9, IPFlushRepository::dns_xdr_flush_f_1_t_9_cnt);
			}
			if(IPGlobal::GN_GTPU_FLUSHER_NO > 2) {
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_2_t_9, IPFlushRepository::dns_xdr_flush_f_2_t_9_cnt);
						writeDnsCsvData(IPFlushRepository::dns_xdr_flush_f_3_t_9, IPFlushRepository::dns_xdr_flush_f_3_t_9_cnt);
			}
			break;
	}
}


VOID GTPXdrFlusher::openGTPuCsvXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
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
	GTPuXdrHandler.open((char *)filePath, ios :: out | ios :: app);

	if(GTPuXdrHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] GTPc Csv file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] GTPc Csv file Open Success. !!!", filePath);
	}

	filePath[0] = 0;
}

VOID GTPXdrFlusher::closeGTPuCsvXdrFile()
{
	GTPuXdrHandler.close();
}

VOID GTPXdrFlusher::openDnsCsvXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear)
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
	DnsXdrHandler.open((char *)filePath, ios :: out | ios :: app);

	if(DnsXdrHandler.fail()) {
//		TheLog_v1(Log::Warn, "IPFlusher.cpp", " [%s] GTPc Csv file Open failed. !!!", filePath);
	} else {
//		TheLog_v1(Log::Debug, "IPFlusher.cpp", " [%s] GTPc Csv file Open Success. !!!", filePath);
	}

	filePath[0] = 0;
}

VOID GTPXdrFlusher::closeDnsCsvXdrFile()
{
	DnsXdrHandler.close();
}
