/*
 * GTPuFlusher.h
 *
 *  Created on: Mar 28, 2017
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPUFLUSHER_H_
#define PLUGINS_GN_SRC_GTPUFLUSHER_H_

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "Log.h"
#include "GTPGlobal.h"
#include "ProbeUtility.h"
#include "IPGlobal.h"
#include "TCPFlusherUtility.h"
#include "BaseConfig.h"

class GTPuFlusher : BaseConfig{

	private:

		int		InstanceId = 0;

		TCPFlusherUtility *tcpFlusherUtility;

		timeval curTime;

		long processStartEpochSec = 0;

		BOOL	repoInitStatus = false;
		char csvXdr[XDR_MAX_LEN];
		char tdrXdr[TDR_MAX_LEN];

		xdrStore objXdrStore;

		VOID 	processGTPuData(int index);
		VOID 	processGTPuData_f_0(int index);
		VOID 	processGTPuData_f_1(int index);
		VOID 	processGTPuData_f_2(int index);
		VOID 	processGTPuData_f_3(int index);


//		VOID 	flushGTPuData_sm_t(std::vector<ipSession> &flushMap, int &ipFlushMap_sm_cnt);
		VOID 	flushGTPuData_sm_t(std::map<int, ipSession> &flushMap, int &ipFlushMap_sm_cnt);

		VOID 	flushGtpuCsvRecords();
		VOID 	flushGtpuCsvRecords_f_0();
		VOID 	flushGtpuCsvRecords_f_1();
		VOID 	flushGtpuCsvRecords_f_2();
		VOID 	flushGtpuCsvRecords_f_3();

		//VOID 	storeGtpuZmqRecords(int index, int &ip_zmq_flush_map_cnt, std::vector<xdrStore> &ip_zmq_flush_map);
		VOID 	storeGtpuZmqRecords(int index, int &ip_zmq_flush_map_cnt, std::map<int, xdrStore> &ip_zmq_flush_map);

		VOID 	processDNSData(int index);
		VOID 	processDNSData_f_0(int index);
		VOID 	processDNSData_f_1(int index);
		VOID 	processDNSData_f_2(int index);
		VOID 	processDNSData_f_3(int index);

//		VOID 	flushDNSData_sm_t(std::vector<dnsSession> &flushMap, int &dnsFlushMap_sm_cnt);
		VOID 	flushDNSData_sm_t(std::map<int, dnsSession> &flushMap, int &dnsFlushMap_sm_cnt);
		VOID 	flushDNSCsvRecords();
		VOID 	flushDNSCsvRecords_f_0();
		VOID 	flushDNSCsvRecords_f_1();
		VOID 	flushDNSCsvRecords_f_2();
		VOID 	flushDNSCsvRecords_f_3();

//		VOID 	storeDNSZmqRecords(int index, int &dns_zmq_flush_map_cnt, std::vector<xdrStore> &dns_zmq_flush_map);
		VOID 	storeDNSZmqRecords(int index, int &dns_zmq_flush_map_cnt, std::map<int, xdrStore> &dns_zmq_flush_map);

		VOID 	buildCSVDataGTPu(ipSession *pIpSession);
		VOID 	buildCSVDataDns(dnsSession *pDnsSession);


	public:
			GTPuFlusher(int id);
			virtual ~GTPuFlusher();
			BOOL 	isRepositoryInitialized();
			VOID 	run();

};

#endif /* PLUGINS_GN_SRC_GTPUFLUSHER_H_ */
