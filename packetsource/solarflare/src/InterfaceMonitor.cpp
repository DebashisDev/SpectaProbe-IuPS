/*
 * InterfaceMonitor.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: Deb
 */

#include "InterfaceMonitor.h"

InterfaceMonitor::InterfaceMonitor(int intfid, interfaceThread *t) {
	this->InterfaceId = intfid;
	this->thread = t;
	this->_name = "InterfaceMonitor";
	this->setLogLevel(Log::theLog().level());
}

InterfaceMonitor::~InterfaceMonitor() {
}

void InterfaceMonitor::run()
{
	uint64_t now_bytes, prev_bytes;
	struct timeval start, end;
	struct tm *now_tm;
	uint64_t prev_pkts, now_pkts;
	int ms, pkt_rate, mbps;
	long ppsMax = 0;

	prev_pkts = thread->n_rx_pkts;
	prev_bytes = thread->n_rx_bytes;
	gettimeofday(&start, NULL);

	now_tm = localtime(&start.tv_sec);
	int today = 0, lastday = 0;
	int nowMin = 0, prevMin = 0;

	today = lastday = now_tm->tm_mday;
	nowMin = prevMin = now_tm->tm_min;

	for(int i=0; i<60; i++)
		ppsArray[i] = 0;

	while(IPGlobal::PKT_LISTENER_INTF_MON_RUNNING_STATUS[InterfaceId]) {
		sleep(1);
		gettimeofday(&end, NULL);

		now_tm = localtime(&end.tv_sec);
		today = now_tm->tm_mday;
		nowMin = now_tm->tm_min;

		now_pkts = thread->n_rx_pkts;
		now_bytes = thread->n_rx_bytes;

		if(now_pkts < prev_pkts)
			now_pkts = prev_pkts;
		if(now_bytes < prev_bytes)
			now_bytes = prev_bytes;

		ms = (end.tv_sec - start.tv_sec) * 1000;
		ms += (end.tv_usec - start.tv_usec) / 1000;
		pkt_rate = (int) ((int64_t) (now_pkts - prev_pkts) * 1000 / ms);
		mbps = (int) ((now_bytes - prev_bytes) * 8 / 1000 / ms);

		ppsArray[now_tm->tm_sec] = pkt_rate;
		if(nowMin != prevMin)
		{
			ppsMax = 0;
			prevMin = nowMin;
			for(int i=0; i<60; i++)
			{
				if(ppsArray[i] > ppsMax)
					ppsMax = ppsArray[i];
				ppsArray[i] = 0;
			}
			TheLog_nc_v3(Log::Info, name(),"  Peak PPS for Interface [%d] for minute [%02d] :: %d", InterfaceId, nowMin, ppsMax);
		}

		switch(InterfaceId)
		{
			case 0:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_0 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_0 = now_pkts;
				IPGlobal::PKT_RATE_INTF_0 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_0 = mbps;
				break;
			case 1:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_1 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_1 = now_pkts;
				IPGlobal::PKT_RATE_INTF_1 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_1 = mbps;
				break;
			case 2:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_2 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_2 = now_pkts;
				IPGlobal::PKT_RATE_INTF_2 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_2 = mbps;
				break;
			case 3:
				if(lastday != today){
					IPGlobal::PKTS_TOTAL_INTF_3 = 0;
					lastday = today;
				}
				IPGlobal::PKTS_TOTAL_INTF_3 = now_pkts;
				IPGlobal::PKT_RATE_INTF_3 = pkt_rate;
				IPGlobal::BW_MBPS_INTF_3 = mbps;
				break;
		}
		prev_pkts = now_pkts;
		prev_bytes = now_bytes;
		start = end;
	}
	printf("InterfaceMonitor [%d] shutdown complete.\n",InterfaceId);
}
