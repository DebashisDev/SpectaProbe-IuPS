/*
 * GTPcFlusher.h
 *
 *  Created on: Mar 28, 2017
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPCFLUSHER_H_
#define PLUGINS_GN_SRC_GTPCFLUSHER_H_

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "Log.h"
#include "GTPGlobal.h"
#include "ProbeUtility.h"
#include "IPGlobal.h"
#include "BaseConfig.h"

class GTPcFlusher : BaseConfig{

	private:

		timeval curTime;

		fstream	GTPcXdrHandler;
		string 	csvGTPcDataGlb;
		int 	csvGTPcBatchCount = 0;

		fstream	GTPcTdrHandler;
		string  tdrGTPcDataGlb;
		int 	tdrGTPcBatchCount = 0;

		long processStartEpochSec = 0;

		BOOL repoInitStatus = false;

		char csvXdr[XDR_MAX_LEN];
		char tdrXdr[TDR_MAX_LEN];

		VOID 	flushGTPcV1Data_sm_t(
					int &gtpcV1FlushMap_sm_cnt,
					std::vector<GTPSession> &gtpcV1FlushMap_sm,
					int &index, int &totalFlushCount, int &recordCount);
		VOID 	flushGTPcV1Data(int index);
		VOID 	buildCSVDataGTPcV1(GTPSession *pGtpSession);
		VOID 	buildTDRDataGTPcV1(GTPSession *pGtpSession);
		VOID 	buildGTPcSessionCountCSV(long timems);

		VOID 	buildBwCSV(long timems);

		VOID 	storeGtpcZmqRecords(int index, int &zmq_flush_map_gtpc_cnt, std::vector<xdrStore>&zmq_flush_map_gtpc);
		VOID 	flushGtpcCsvRecords(bool writexdr, int processCnt, int totalFlushCount);
		VOID 	flushTdrRecords(int index, int processCnt, int totalFlushCount);

		VOID  	packGTPcV1Data(GTPSession *pGtpSession);

		VOID 	openGTPcCsvXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	closeGTPcCsvXdrFile();
		VOID 	openGTPcTdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	closeGTPcTdrFile();

public:
		GTPcFlusher();
		virtual ~GTPcFlusher();
		BOOL 	isRepositoryInitialized();
		VOID 	run();

};

#endif /* PLUGINS_GN_SRC_GTPCFLUSHER_H_ */
