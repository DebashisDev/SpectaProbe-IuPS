/*
 * TraceListener.h
 *
 *  Created on: Dec 6, 2016
 *      Author: Deb
 */

#ifndef CORE_SRC_TRACELISTENER_H_
#define CORE_SRC_TRACELISTENER_H_

#include <unistd.h>
#include "IPGlobal.h"

class TraceListener {
	public:
		TraceListener();
		virtual ~TraceListener();

		long beginEpochSec = 0;
		int beginSec = 0;

		VOID run();
	private:

		timeval curTime;
		fstream fp;

		VOID process(int idx);
		VOID process_i_0_r_0(int idx);
		VOID process_i_0_r_1(int idx);
		VOID process_i_0_r_2(int idx);
		VOID process_i_0_r_3(int idx);

		VOID process_i_1_r_0(int idx);
		VOID process_i_1_r_1(int idx);
		VOID process_i_1_r_2(int idx);
		VOID process_i_1_r_3(int idx);

		VOID process_i_2_r_0(int idx);
		VOID process_i_2_r_1(int idx);
		VOID process_i_2_r_2(int idx);
		VOID process_i_2_r_3(int idx);

		VOID process_i_3_r_0(int idx);
		VOID process_i_3_r_1(int idx);
		VOID process_i_3_r_2(int idx);
		VOID process_i_3_r_3(int idx);

		VOID processMessage(int &tr_msg_cnt, std::string (&tr_msg)[TRACE_QUEUE_LIMIT]);

//		VOID processMessage(MPacket *msgObj);
};

#endif /* CORE_SRC_TRACELISTENER_H_ */
