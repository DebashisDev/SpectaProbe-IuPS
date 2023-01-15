/*
 * IUPSFlusher.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Debashis
 */

#ifndef PLUGINS_IUPS_SRC_IUPSFLUSHER_H_
#define PLUGINS_IUPS_SRC_IUPSFLUSHER_H_

#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "sys/time.h"
#include <locale.h>

#include "Log.h"
#include "IUPSGlobal.h"
#include "BaseConfig.h"
#include "GTPGlobal.h"

#define MAX_TDR_XDR_SIZE	1000

class IUPSFlusher : public BaseConfig {
	private:
		timeval curTime;
		fstream	IUPSXdrHandler;
		fstream	IUPSTdrHandler;
		long processStartEpochSec = 0;
		string tdrXdr;

		int 	csvIupsBatchCount = 0;
		string 	csvIupsDataGlb;

		VOID 	openCsvXdrFile(string &prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	closeCsvXdrFile();
		VOID 	openTdrFile(string &prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	closeTdrFile();
		VOID 	flushIupsData(int index, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	flushIupsData_sm_t(std::map<uint32_t, string> &flushMap, int &ipFlushMap_sm_cnt, int &index, int &totalFlushCount, int &recordCount);
		VOID 	flushIupsCsvRecords(int index, int processCnt, int totalFlushCount, string &xdrdata);
		VOID 	storeIupsZmqRecords(int index, string xdrString, int &zmq_flush_map_iups_cnt, std::string (&zmq_flush_map_iups)[IUPS_ZMQ_FLUSH_MAP_ARRAY_SIZE]);

	public:
		IUPSFlusher();
		~IUPSFlusher();

		BOOL isRepositoryInitialized();
		VOID run();
};

#endif /* PLUGINS_IUPS_SRC_IUPSFLUSHER_H_ */
