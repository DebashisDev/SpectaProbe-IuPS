/*
 * GTPFlusher.h
 *
 *  Created on: Dec 21, 2016
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPFLUSHER_H_
#define PLUGINS_GN_SRC_GTPFLUSHER_H_

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

class GTPXdrFlusher :BaseConfig {
	private:

			timeval curTime;

			fstream	GTPuXdrHandler;
			fstream	DnsXdrHandler;

			string 	csvGTPuDataGlb;
			int 	csvGTPuBatchCount = 0;

			string 	csvDNSDataGlb;
			int 	csvDNSBatchCount = 0;

			long processStartEpochSec = 0;

			BOOL repoInitStatus = false;

			char csvXdr[XDR_MAX_LEN];
			char tdrXdr[TDR_MAX_LEN];

			VOID	processGTPu(int index);
			VOID	processDns(int index);

			//VOID 	writeGTPuCsvData(std::vector<xdrStore> &ip_flush_map, int &ip_xdr_flush_map_cnt);
			VOID 	writeGTPuCsvData(std::map<int, xdrStore> &ip_flush_map, int &ip_xdr_flush_map_cnt);

//			VOID 	writeDnsCsvData(std::vector<xdrStore> &dns_flush_map, int &dns_xdr_flush_map_cnt);
			VOID 	writeDnsCsvData(std::map<int, xdrStore> &dns_flush_map, int &dns_xdr_flush_map_cnt);

			VOID 	openGTPuCsvXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
			VOID 	closeGTPuCsvXdrFile();
			VOID 	openDnsCsvXdrFile(string prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
			VOID 	closeDnsCsvXdrFile();



	public:
			GTPXdrFlusher();
			virtual ~GTPXdrFlusher();
			BOOL 	isRepositoryInitialized();
			VOID 	run();

};

#endif /* PLUGINS_GN_SRC_GTPFLUSHER_H_ */
