/*
 * GTPXdrWriter.h
 *
 *  Created on: Jan 9, 2017
 *      Author: Deb
 */

#ifndef PLUGINS_GN_SRC_GTPXDRWRITER_H_
#define PLUGINS_GN_SRC_GTPXDRWRITER_H_

#include <sys/time.h>
#include <unistd.h>
#include "Log.h"
#include "BaseConfig.h"
#include "IPGlobal.h"
#include "GTPGlobal.h"


#define XDR_RECORDS_BATCH_SIZE	5000

class GTPXdrWriter : public BaseConfig  {

	private:
		timeval curTime;
		long beginEpochSec = 0;
		int beginSec = 0;

		string 	csvGtpcDataGlb;
		string 	csvGtpuDataGlb;
		string 	csvDnsDataGlb;

		VOID 	flushGTPcV1Data(int index, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	flushGTPuData(int index, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID	flushDnsData(int index, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);

		VOID 	openCsvXdrFile(string &prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	closeCsvXdrFile();
		VOID 	openTdrFile(string &prefix, int currentMin, int currentHour, int currentDay, int currentMonth, int currentYear);
		VOID 	closeTdrFile();

	public:
		GTPXdrWriter();
		virtual ~GTPXdrWriter();
		VOID 	run();
};

#endif /* PLUGINS_GN_SRC_GTPXDRWRITER_H_ */
