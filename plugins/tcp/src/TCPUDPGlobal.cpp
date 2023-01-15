/*
 * TCPUDPGlobal.cpp
 *
 *  Created on: 15-Jul-2016
 *      Author: deb
 */

#include "TCPUDPGlobal.h"

using namespace std;

/* STUN SESSION MAP */
namespace STUNMAP {
	std::map<uint32_t, stunData> stunMap;
}

namespace DnsDataMap {
	std::map<uint32_t, std::string> dailyDnsDump;
}

namespace DNSGlobal {
	std::map<string, dnsUrl> dnsDatabaseMap_0;
	std::map<string, dnsUrl> dnsDatabaseMap_1;
	std::map<string, dnsUrl> dnsDatabaseMap_2;
	std::map<string, dnsUrl> dnsDatabaseMap_3;
	std::map<string, dnsUrl> dnsDatabaseMap_4;
	std::map<string, dnsUrl> dnsDatabaseMap_5;
	std::map<string, dnsUrl> dnsDatabaseMap_6;
	std::map<string, dnsUrl> dnsDatabaseMap_7;
	std::map<string, dnsUrl> dnsDatabaseMap_8;
	std::map<string, dnsUrl> dnsDatabaseMap_9;

	std::map<uint32_t, string> dnsLookUpMap_0;
	std::map<uint32_t, string> dnsLookUpMap_1;
	std::map<uint32_t, string> dnsLookUpMap_2;
	std::map<uint32_t, string> dnsLookUpMap_3;
	std::map<uint32_t, string> dnsLookUpMap_4;
	std::map<uint32_t, string> dnsLookUpMap_5;
	std::map<uint32_t, string> dnsLookUpMap_6;
	std::map<uint32_t, string> dnsLookUpMap_7;
	std::map<uint32_t, string> dnsLookUpMap_8;
	std::map<uint32_t, string> dnsLookUpMap_9;
}

namespace IPFlushRepository {
	/* Flusher 0 SM 0 */
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_0;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_1;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_2;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_3;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_4;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_5;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_6;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_7;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_8;
	std::map<int, ipSession> ipFlushMap_f_0_sm_0_t_9;

	int ipFlushMap_f_0_sm_0_t_0_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_1_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_2_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_3_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_4_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_5_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_6_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_7_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_8_cnt = 0;
	int ipFlushMap_f_0_sm_0_t_9_cnt = 0;

	/* Flusher 0 SM 1 */
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_0;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_1;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_2;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_3;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_4;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_5;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_6;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_7;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_8;
	std::map<int, ipSession> ipFlushMap_f_0_sm_1_t_9;

	int ipFlushMap_f_0_sm_1_t_0_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_1_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_2_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_3_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_4_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_5_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_6_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_7_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_8_cnt = 0;
	int ipFlushMap_f_0_sm_1_t_9_cnt = 0;

	/* Flusher 0 SM 2 */
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_0;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_1;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_2;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_3;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_4;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_5;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_6;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_7;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_8;
	std::map<int, ipSession> ipFlushMap_f_0_sm_2_t_9;

	int ipFlushMap_f_0_sm_2_t_0_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_1_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_2_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_3_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_4_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_5_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_6_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_7_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_8_cnt = 0;
	int ipFlushMap_f_0_sm_2_t_9_cnt = 0;

	/* Flusher 0 SM 3 */
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_0;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_1;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_2;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_3;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_4;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_5;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_6;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_7;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_8;
	std::map<int, ipSession> ipFlushMap_f_0_sm_3_t_9;

	int ipFlushMap_f_0_sm_3_t_0_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_1_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_2_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_3_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_4_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_5_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_6_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_7_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_8_cnt = 0;
	int ipFlushMap_f_0_sm_3_t_9_cnt = 0;

	/* Flusher 0 SM 4 */
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_0;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_1;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_2;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_3;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_4;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_5;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_6;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_7;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_8;
	std::map<int, ipSession> ipFlushMap_f_0_sm_4_t_9;

	int ipFlushMap_f_0_sm_4_t_0_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_1_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_2_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_3_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_4_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_5_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_6_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_7_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_8_cnt = 0;
	int ipFlushMap_f_0_sm_4_t_9_cnt = 0;

	/* Flusher 1 SM 0 */
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_0;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_1;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_2;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_3;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_4;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_5;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_6;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_7;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_8;
	std::map<int, ipSession> ipFlushMap_f_1_sm_0_t_9;

	int ipFlushMap_f_1_sm_0_t_0_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_1_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_2_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_3_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_4_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_5_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_6_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_7_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_8_cnt = 0;
	int ipFlushMap_f_1_sm_0_t_9_cnt = 0;

	/* Flusher 1 SM 1 */
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_0;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_1;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_2;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_3;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_4;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_5;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_6;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_7;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_8;
	std::map<int, ipSession> ipFlushMap_f_1_sm_1_t_9;

	int ipFlushMap_f_1_sm_1_t_0_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_1_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_2_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_3_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_4_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_5_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_6_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_7_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_8_cnt = 0;
	int ipFlushMap_f_1_sm_1_t_9_cnt = 0;

	/* Flusher 1 SM 2 */
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_0;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_1;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_2;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_3;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_4;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_5;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_6;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_7;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_8;
	std::map<int, ipSession> ipFlushMap_f_1_sm_2_t_9;

	int ipFlushMap_f_1_sm_2_t_0_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_1_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_2_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_3_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_4_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_5_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_6_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_7_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_8_cnt = 0;
	int ipFlushMap_f_1_sm_2_t_9_cnt = 0;

	/* Flusher 1 SM 3 */
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_0;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_1;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_2;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_3;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_4;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_5;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_6;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_7;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_8;
	std::map<int, ipSession> ipFlushMap_f_1_sm_3_t_9;

	int ipFlushMap_f_1_sm_3_t_0_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_1_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_2_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_3_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_4_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_5_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_6_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_7_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_8_cnt = 0;
	int ipFlushMap_f_1_sm_3_t_9_cnt = 0;

	/* Flusher 1 SM 4 */
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_0;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_1;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_2;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_3;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_4;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_5;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_6;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_7;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_8;
	std::map<int, ipSession> ipFlushMap_f_1_sm_4_t_9;

	int ipFlushMap_f_1_sm_4_t_0_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_1_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_2_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_3_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_4_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_5_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_6_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_7_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_8_cnt = 0;
	int ipFlushMap_f_1_sm_4_t_9_cnt = 0;

	/* Flusher 2 SM 0 */
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_0;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_1;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_2;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_3;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_4;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_5;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_6;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_7;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_8;
	std::map<int, ipSession> ipFlushMap_f_2_sm_0_t_9;

	int ipFlushMap_f_2_sm_0_t_0_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_1_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_2_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_3_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_4_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_5_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_6_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_7_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_8_cnt = 0;
	int ipFlushMap_f_2_sm_0_t_9_cnt = 0;

	/* Flusher 2 SM 1 */
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_0;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_1;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_2;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_3;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_4;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_5;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_6;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_7;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_8;
	std::map<int, ipSession> ipFlushMap_f_2_sm_1_t_9;

	int ipFlushMap_f_2_sm_1_t_0_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_1_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_2_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_3_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_4_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_5_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_6_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_7_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_8_cnt = 0;
	int ipFlushMap_f_2_sm_1_t_9_cnt = 0;

	/* Flusher 2 SM 2 */
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_0;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_1;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_2;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_3;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_4;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_5;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_6;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_7;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_8;
	std::map<int, ipSession> ipFlushMap_f_2_sm_2_t_9;

	int ipFlushMap_f_2_sm_2_t_0_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_1_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_2_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_3_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_4_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_5_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_6_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_7_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_8_cnt = 0;
	int ipFlushMap_f_2_sm_2_t_9_cnt = 0;

	/* Flusher 2 SM 3 */
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_0;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_1;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_2;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_3;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_4;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_5;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_6;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_7;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_8;
	std::map<int, ipSession> ipFlushMap_f_2_sm_3_t_9;

	int ipFlushMap_f_2_sm_3_t_0_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_1_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_2_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_3_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_4_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_5_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_6_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_7_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_8_cnt = 0;
	int ipFlushMap_f_2_sm_3_t_9_cnt = 0;

	/* Flusher 2 SM 4 */
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_0;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_1;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_2;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_3;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_4;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_5;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_6;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_7;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_8;
	std::map<int, ipSession> ipFlushMap_f_2_sm_4_t_9;

	int ipFlushMap_f_2_sm_4_t_0_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_1_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_2_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_3_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_4_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_5_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_6_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_7_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_8_cnt = 0;
	int ipFlushMap_f_2_sm_4_t_9_cnt = 0;

	/* Flusher 3 SM 0 */
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_0;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_1;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_2;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_3;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_4;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_5;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_6;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_7;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_8;
	std::map<int, ipSession> ipFlushMap_f_3_sm_0_t_9;

	int ipFlushMap_f_3_sm_0_t_0_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_1_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_2_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_3_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_4_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_5_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_6_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_7_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_8_cnt = 0;
	int ipFlushMap_f_3_sm_0_t_9_cnt = 0;

	/* Flusher 3 SM 1 */
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_0;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_1;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_2;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_3;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_4;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_5;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_6;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_7;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_8;
	std::map<int, ipSession> ipFlushMap_f_3_sm_1_t_9;

	int ipFlushMap_f_3_sm_1_t_0_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_1_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_2_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_3_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_4_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_5_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_6_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_7_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_8_cnt = 0;
	int ipFlushMap_f_3_sm_1_t_9_cnt = 0;

	/* Flusher 3 SM 2 */
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_0;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_1;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_2;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_3;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_4;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_5;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_6;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_7;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_8;
	std::map<int, ipSession> ipFlushMap_f_3_sm_2_t_9;

	int ipFlushMap_f_3_sm_2_t_0_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_1_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_2_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_3_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_4_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_5_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_6_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_7_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_8_cnt = 0;
	int ipFlushMap_f_3_sm_2_t_9_cnt = 0;

	/* Flusher 3 SM 3 */
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_0;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_1;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_2;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_3;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_4;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_5;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_6;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_7;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_8;
	std::map<int, ipSession> ipFlushMap_f_3_sm_3_t_9;

	int ipFlushMap_f_3_sm_3_t_0_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_1_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_2_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_3_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_4_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_5_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_6_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_7_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_8_cnt = 0;
	int ipFlushMap_f_3_sm_3_t_9_cnt = 0;

	/* Flusher 3 SM 4 */
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_0;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_1;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_2;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_3;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_4;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_5;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_6;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_7;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_8;
	std::map<int, ipSession> ipFlushMap_f_3_sm_4_t_9;

	int ipFlushMap_f_3_sm_4_t_0_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_1_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_2_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_3_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_4_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_5_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_6_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_7_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_8_cnt = 0;
	int ipFlushMap_f_3_sm_4_t_9_cnt = 0;


	// XDR Flush Repository
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_0;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_1;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_2;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_3;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_4;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_5;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_6;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_7;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_8;
	std::map<int, xdrStore> ip_xdr_flush_f_0_t_9;

	int ip_xdr_flush_f_0_t_0_cnt = 0;
	int ip_xdr_flush_f_0_t_1_cnt = 0;
	int ip_xdr_flush_f_0_t_2_cnt = 0;
	int ip_xdr_flush_f_0_t_3_cnt = 0;
	int ip_xdr_flush_f_0_t_4_cnt = 0;
	int ip_xdr_flush_f_0_t_5_cnt = 0;
	int ip_xdr_flush_f_0_t_6_cnt = 0;
	int ip_xdr_flush_f_0_t_7_cnt = 0;
	int ip_xdr_flush_f_0_t_8_cnt = 0;
	int ip_xdr_flush_f_0_t_9_cnt = 0;

	std::map<int, xdrStore> ip_xdr_flush_f_1_t_0;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_1;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_2;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_3;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_4;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_5;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_6;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_7;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_8;
	std::map<int, xdrStore> ip_xdr_flush_f_1_t_9;

	int ip_xdr_flush_f_1_t_0_cnt = 0;
	int ip_xdr_flush_f_1_t_1_cnt = 0;
	int ip_xdr_flush_f_1_t_2_cnt = 0;
	int ip_xdr_flush_f_1_t_3_cnt = 0;
	int ip_xdr_flush_f_1_t_4_cnt = 0;
	int ip_xdr_flush_f_1_t_5_cnt = 0;
	int ip_xdr_flush_f_1_t_6_cnt = 0;
	int ip_xdr_flush_f_1_t_7_cnt = 0;
	int ip_xdr_flush_f_1_t_8_cnt = 0;
	int ip_xdr_flush_f_1_t_9_cnt = 0;

	std::map<int, xdrStore> ip_xdr_flush_f_2_t_0;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_1;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_2;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_3;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_4;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_5;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_6;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_7;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_8;
	std::map<int, xdrStore> ip_xdr_flush_f_2_t_9;

	int ip_xdr_flush_f_2_t_0_cnt = 0;
	int ip_xdr_flush_f_2_t_1_cnt = 0;
	int ip_xdr_flush_f_2_t_2_cnt = 0;
	int ip_xdr_flush_f_2_t_3_cnt = 0;
	int ip_xdr_flush_f_2_t_4_cnt = 0;
	int ip_xdr_flush_f_2_t_5_cnt = 0;
	int ip_xdr_flush_f_2_t_6_cnt = 0;
	int ip_xdr_flush_f_2_t_7_cnt = 0;
	int ip_xdr_flush_f_2_t_8_cnt = 0;
	int ip_xdr_flush_f_2_t_9_cnt = 0;

	std::map<int, xdrStore> ip_xdr_flush_f_3_t_0;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_1;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_2;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_3;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_4;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_5;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_6;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_7;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_8;
	std::map<int, xdrStore> ip_xdr_flush_f_3_t_9;

	int ip_xdr_flush_f_3_t_0_cnt = 0;
	int ip_xdr_flush_f_3_t_1_cnt = 0;
	int ip_xdr_flush_f_3_t_2_cnt = 0;
	int ip_xdr_flush_f_3_t_3_cnt = 0;
	int ip_xdr_flush_f_3_t_4_cnt = 0;
	int ip_xdr_flush_f_3_t_5_cnt = 0;
	int ip_xdr_flush_f_3_t_6_cnt = 0;
	int ip_xdr_flush_f_3_t_7_cnt = 0;
	int ip_xdr_flush_f_3_t_8_cnt = 0;
	int ip_xdr_flush_f_3_t_9_cnt = 0;

	// ZMQ Flush Repository
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_0;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_1;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_2;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_3;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_4;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_5;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_6;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_7;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_8;
	std::map<int, xdrStore> ip_zmq_flush_f_0_t_9;

	int ip_zmq_flush_f_0_t_0_cnt = 0;
	int ip_zmq_flush_f_0_t_1_cnt = 0;
	int ip_zmq_flush_f_0_t_2_cnt = 0;
	int ip_zmq_flush_f_0_t_3_cnt = 0;
	int ip_zmq_flush_f_0_t_4_cnt = 0;
	int ip_zmq_flush_f_0_t_5_cnt = 0;
	int ip_zmq_flush_f_0_t_6_cnt = 0;
	int ip_zmq_flush_f_0_t_7_cnt = 0;
	int ip_zmq_flush_f_0_t_8_cnt = 0;
	int ip_zmq_flush_f_0_t_9_cnt = 0;

	std::map<int, xdrStore> ip_zmq_flush_f_1_t_0;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_1;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_2;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_3;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_4;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_5;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_6;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_7;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_8;
	std::map<int, xdrStore> ip_zmq_flush_f_1_t_9;

	int ip_zmq_flush_f_1_t_0_cnt = 0;
	int ip_zmq_flush_f_1_t_1_cnt = 0;
	int ip_zmq_flush_f_1_t_2_cnt = 0;
	int ip_zmq_flush_f_1_t_3_cnt = 0;
	int ip_zmq_flush_f_1_t_4_cnt = 0;
	int ip_zmq_flush_f_1_t_5_cnt = 0;
	int ip_zmq_flush_f_1_t_6_cnt = 0;
	int ip_zmq_flush_f_1_t_7_cnt = 0;
	int ip_zmq_flush_f_1_t_8_cnt = 0;
	int ip_zmq_flush_f_1_t_9_cnt = 0;

	std::map<int, xdrStore> ip_zmq_flush_f_2_t_0;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_1;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_2;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_3;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_4;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_5;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_6;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_7;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_8;
	std::map<int, xdrStore> ip_zmq_flush_f_2_t_9;

	int ip_zmq_flush_f_2_t_0_cnt = 0;
	int ip_zmq_flush_f_2_t_1_cnt = 0;
	int ip_zmq_flush_f_2_t_2_cnt = 0;
	int ip_zmq_flush_f_2_t_3_cnt = 0;
	int ip_zmq_flush_f_2_t_4_cnt = 0;
	int ip_zmq_flush_f_2_t_5_cnt = 0;
	int ip_zmq_flush_f_2_t_6_cnt = 0;
	int ip_zmq_flush_f_2_t_7_cnt = 0;
	int ip_zmq_flush_f_2_t_8_cnt = 0;
	int ip_zmq_flush_f_2_t_9_cnt = 0;

	std::map<int, xdrStore> ip_zmq_flush_f_3_t_0;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_1;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_2;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_3;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_4;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_5;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_6;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_7;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_8;
	std::map<int, xdrStore> ip_zmq_flush_f_3_t_9;

	int ip_zmq_flush_f_3_t_0_cnt = 0;
	int ip_zmq_flush_f_3_t_1_cnt = 0;
	int ip_zmq_flush_f_3_t_2_cnt = 0;
	int ip_zmq_flush_f_3_t_3_cnt = 0;
	int ip_zmq_flush_f_3_t_4_cnt = 0;
	int ip_zmq_flush_f_3_t_5_cnt = 0;
	int ip_zmq_flush_f_3_t_6_cnt = 0;
	int ip_zmq_flush_f_3_t_7_cnt = 0;
	int ip_zmq_flush_f_3_t_8_cnt = 0;
	int ip_zmq_flush_f_3_t_9_cnt = 0;

	/* -- DNS - Flusher 0 SM 0 */
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_0_t_9;

	int dnsFlushMap_f_0_sm_0_t_0_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_1_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_2_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_3_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_4_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_5_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_6_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_7_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_8_cnt = 0;
	int dnsFlushMap_f_0_sm_0_t_9_cnt = 0;

	/* Flusher 0 SM 1 */
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_1_t_9;

	int dnsFlushMap_f_0_sm_1_t_0_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_1_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_2_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_3_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_4_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_5_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_6_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_7_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_8_cnt = 0;
	int dnsFlushMap_f_0_sm_1_t_9_cnt = 0;

	/* Flusher 0 SM 2 */
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_2_t_9;

	int dnsFlushMap_f_0_sm_2_t_0_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_1_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_2_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_3_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_4_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_5_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_6_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_7_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_8_cnt = 0;
	int dnsFlushMap_f_0_sm_2_t_9_cnt = 0;

	/* Flusher 0 SM 3 */
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_3_t_9;

	int dnsFlushMap_f_0_sm_3_t_0_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_1_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_2_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_3_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_4_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_5_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_6_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_7_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_8_cnt = 0;
	int dnsFlushMap_f_0_sm_3_t_9_cnt = 0;

	/* Flusher 0 SM 4 */
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_0_sm_4_t_9;

	int dnsFlushMap_f_0_sm_4_t_0_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_1_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_2_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_3_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_4_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_5_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_6_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_7_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_8_cnt = 0;
	int dnsFlushMap_f_0_sm_4_t_9_cnt = 0;

	/* -- DNS - Flusher 1 SM 0 */
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_0_t_9;

	int dnsFlushMap_f_1_sm_0_t_0_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_1_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_2_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_3_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_4_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_5_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_6_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_7_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_8_cnt = 0;
	int dnsFlushMap_f_1_sm_0_t_9_cnt = 0;

	/* Flusher 1 SM 1 */
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_1_t_9;

	int dnsFlushMap_f_1_sm_1_t_0_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_1_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_2_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_3_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_4_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_5_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_6_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_7_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_8_cnt = 0;
	int dnsFlushMap_f_1_sm_1_t_9_cnt = 0;

	/* Flusher 1 SM 2 */
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_2_t_9;

	int dnsFlushMap_f_1_sm_2_t_0_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_1_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_2_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_3_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_4_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_5_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_6_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_7_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_8_cnt = 0;
	int dnsFlushMap_f_1_sm_2_t_9_cnt = 0;

	/* Flusher 1 SM 3 */
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_3_t_9;

	int dnsFlushMap_f_1_sm_3_t_0_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_1_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_2_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_3_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_4_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_5_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_6_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_7_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_8_cnt = 0;
	int dnsFlushMap_f_1_sm_3_t_9_cnt = 0;

	/* Flusher 1 SM 4 */
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_1_sm_4_t_9;

	int dnsFlushMap_f_1_sm_4_t_0_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_1_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_2_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_3_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_4_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_5_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_6_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_7_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_8_cnt = 0;
	int dnsFlushMap_f_1_sm_4_t_9_cnt = 0;

	/* -- DNS - Flusher 2 SM 0 */
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_0_t_9;

	int dnsFlushMap_f_2_sm_0_t_0_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_1_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_2_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_3_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_4_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_5_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_6_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_7_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_8_cnt = 0;
	int dnsFlushMap_f_2_sm_0_t_9_cnt = 0;

	/* Flusher 2 SM 1 */
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_1_t_9;

	int dnsFlushMap_f_2_sm_1_t_0_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_1_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_2_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_3_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_4_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_5_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_6_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_7_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_8_cnt = 0;
	int dnsFlushMap_f_2_sm_1_t_9_cnt = 0;

	/* Flusher 2 SM 2 */
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_2_t_9;

	int dnsFlushMap_f_2_sm_2_t_0_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_1_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_2_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_3_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_4_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_5_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_6_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_7_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_8_cnt = 0;
	int dnsFlushMap_f_2_sm_2_t_9_cnt = 0;

	/* Flusher 2 SM 3 */
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_3_t_9;

	int dnsFlushMap_f_2_sm_3_t_0_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_1_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_2_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_3_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_4_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_5_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_6_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_7_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_8_cnt = 0;
	int dnsFlushMap_f_2_sm_3_t_9_cnt = 0;

	/* Flusher 2 SM 4 */
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_2_sm_4_t_9;

	int dnsFlushMap_f_2_sm_4_t_0_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_1_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_2_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_3_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_4_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_5_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_6_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_7_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_8_cnt = 0;
	int dnsFlushMap_f_2_sm_4_t_9_cnt = 0;

	/* -- DNS - Flusher 3 SM 0 */
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_0_t_9;

	int dnsFlushMap_f_3_sm_0_t_0_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_1_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_2_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_3_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_4_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_5_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_6_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_7_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_8_cnt = 0;
	int dnsFlushMap_f_3_sm_0_t_9_cnt = 0;

	/* Flusher 3 SM 1 */
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_1_t_9;

	int dnsFlushMap_f_3_sm_1_t_0_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_1_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_2_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_3_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_4_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_5_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_6_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_7_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_8_cnt = 0;
	int dnsFlushMap_f_3_sm_1_t_9_cnt = 0;

	/* Flusher 3 SM 2 */
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_2_t_9;

	int dnsFlushMap_f_3_sm_2_t_0_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_1_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_2_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_3_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_4_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_5_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_6_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_7_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_8_cnt = 0;
	int dnsFlushMap_f_3_sm_2_t_9_cnt = 0;

	/* Flusher 3 SM 3 */
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_3_t_9;

	int dnsFlushMap_f_3_sm_3_t_0_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_1_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_2_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_3_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_4_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_5_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_6_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_7_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_8_cnt = 0;
	int dnsFlushMap_f_3_sm_3_t_9_cnt = 0;

	/* Flusher 3 SM 4 */
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_0;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_1;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_2;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_3;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_4;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_5;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_6;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_7;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_8;
	std::map<int, dnsSession> dnsFlushMap_f_3_sm_4_t_9;

	int dnsFlushMap_f_3_sm_4_t_0_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_1_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_2_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_3_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_4_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_5_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_6_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_7_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_8_cnt = 0;
	int dnsFlushMap_f_3_sm_4_t_9_cnt = 0;

	std::map<int, xdrStore> dns_xdr_flush_f_0_t_0;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_1;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_2;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_3;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_4;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_5;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_6;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_7;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_8;
	std::map<int, xdrStore> dns_xdr_flush_f_0_t_9;

	int dns_xdr_flush_f_0_t_0_cnt = 0;
	int dns_xdr_flush_f_0_t_1_cnt = 0;
	int dns_xdr_flush_f_0_t_2_cnt = 0;
	int dns_xdr_flush_f_0_t_3_cnt = 0;
	int dns_xdr_flush_f_0_t_4_cnt = 0;
	int dns_xdr_flush_f_0_t_5_cnt = 0;
	int dns_xdr_flush_f_0_t_6_cnt = 0;
	int dns_xdr_flush_f_0_t_7_cnt = 0;
	int dns_xdr_flush_f_0_t_8_cnt = 0;
	int dns_xdr_flush_f_0_t_9_cnt = 0;

	std::map<int, xdrStore> dns_xdr_flush_f_1_t_0;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_1;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_2;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_3;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_4;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_5;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_6;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_7;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_8;
	std::map<int, xdrStore> dns_xdr_flush_f_1_t_9;

	int dns_xdr_flush_f_1_t_0_cnt = 0;
	int dns_xdr_flush_f_1_t_1_cnt = 0;
	int dns_xdr_flush_f_1_t_2_cnt = 0;
	int dns_xdr_flush_f_1_t_3_cnt = 0;
	int dns_xdr_flush_f_1_t_4_cnt = 0;
	int dns_xdr_flush_f_1_t_5_cnt = 0;
	int dns_xdr_flush_f_1_t_6_cnt = 0;
	int dns_xdr_flush_f_1_t_7_cnt = 0;
	int dns_xdr_flush_f_1_t_8_cnt = 0;
	int dns_xdr_flush_f_1_t_9_cnt = 0;

	std::map<int, xdrStore> dns_xdr_flush_f_2_t_0;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_1;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_2;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_3;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_4;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_5;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_6;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_7;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_8;
	std::map<int, xdrStore> dns_xdr_flush_f_2_t_9;

	int dns_xdr_flush_f_2_t_0_cnt = 0;
	int dns_xdr_flush_f_2_t_1_cnt = 0;
	int dns_xdr_flush_f_2_t_2_cnt = 0;
	int dns_xdr_flush_f_2_t_3_cnt = 0;
	int dns_xdr_flush_f_2_t_4_cnt = 0;
	int dns_xdr_flush_f_2_t_5_cnt = 0;
	int dns_xdr_flush_f_2_t_6_cnt = 0;
	int dns_xdr_flush_f_2_t_7_cnt = 0;
	int dns_xdr_flush_f_2_t_8_cnt = 0;
	int dns_xdr_flush_f_2_t_9_cnt = 0;

	std::map<int, xdrStore> dns_xdr_flush_f_3_t_0;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_1;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_2;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_3;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_4;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_5;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_6;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_7;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_8;
	std::map<int, xdrStore> dns_xdr_flush_f_3_t_9;

	int dns_xdr_flush_f_3_t_0_cnt = 0;
	int dns_xdr_flush_f_3_t_1_cnt = 0;
	int dns_xdr_flush_f_3_t_2_cnt = 0;
	int dns_xdr_flush_f_3_t_3_cnt = 0;
	int dns_xdr_flush_f_3_t_4_cnt = 0;
	int dns_xdr_flush_f_3_t_5_cnt = 0;
	int dns_xdr_flush_f_3_t_6_cnt = 0;
	int dns_xdr_flush_f_3_t_7_cnt = 0;
	int dns_xdr_flush_f_3_t_8_cnt = 0;
	int dns_xdr_flush_f_3_t_9_cnt = 0;

	std::map<int, xdrStore> dns_zmq_flush_f_0_t_0;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_1;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_2;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_3;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_4;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_5;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_6;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_7;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_8;
	std::map<int, xdrStore> dns_zmq_flush_f_0_t_9;

	int dns_zmq_flush_f_0_t_0_cnt = 0;
	int dns_zmq_flush_f_0_t_1_cnt = 0;
	int dns_zmq_flush_f_0_t_2_cnt = 0;
	int dns_zmq_flush_f_0_t_3_cnt = 0;
	int dns_zmq_flush_f_0_t_4_cnt = 0;
	int dns_zmq_flush_f_0_t_5_cnt = 0;
	int dns_zmq_flush_f_0_t_6_cnt = 0;
	int dns_zmq_flush_f_0_t_7_cnt = 0;
	int dns_zmq_flush_f_0_t_8_cnt = 0;
	int dns_zmq_flush_f_0_t_9_cnt = 0;

	std::map<int, xdrStore> dns_zmq_flush_f_1_t_0;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_1;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_2;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_3;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_4;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_5;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_6;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_7;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_8;
	std::map<int, xdrStore> dns_zmq_flush_f_1_t_9;

	int dns_zmq_flush_f_1_t_0_cnt = 0;
	int dns_zmq_flush_f_1_t_1_cnt = 0;
	int dns_zmq_flush_f_1_t_2_cnt = 0;
	int dns_zmq_flush_f_1_t_3_cnt = 0;
	int dns_zmq_flush_f_1_t_4_cnt = 0;
	int dns_zmq_flush_f_1_t_5_cnt = 0;
	int dns_zmq_flush_f_1_t_6_cnt = 0;
	int dns_zmq_flush_f_1_t_7_cnt = 0;
	int dns_zmq_flush_f_1_t_8_cnt = 0;
	int dns_zmq_flush_f_1_t_9_cnt = 0;

	std::map<int, xdrStore> dns_zmq_flush_f_2_t_0;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_1;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_2;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_3;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_4;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_5;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_6;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_7;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_8;
	std::map<int, xdrStore> dns_zmq_flush_f_2_t_9;

	int dns_zmq_flush_f_2_t_0_cnt = 0;
	int dns_zmq_flush_f_2_t_1_cnt = 0;
	int dns_zmq_flush_f_2_t_2_cnt = 0;
	int dns_zmq_flush_f_2_t_3_cnt = 0;
	int dns_zmq_flush_f_2_t_4_cnt = 0;
	int dns_zmq_flush_f_2_t_5_cnt = 0;
	int dns_zmq_flush_f_2_t_6_cnt = 0;
	int dns_zmq_flush_f_2_t_7_cnt = 0;
	int dns_zmq_flush_f_2_t_8_cnt = 0;
	int dns_zmq_flush_f_2_t_9_cnt = 0;

	std::map<int, xdrStore> dns_zmq_flush_f_3_t_0;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_1;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_2;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_3;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_4;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_5;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_6;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_7;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_8;
	std::map<int, xdrStore> dns_zmq_flush_f_3_t_9;

	int dns_zmq_flush_f_3_t_0_cnt = 0;
	int dns_zmq_flush_f_3_t_1_cnt = 0;
	int dns_zmq_flush_f_3_t_2_cnt = 0;
	int dns_zmq_flush_f_3_t_3_cnt = 0;
	int dns_zmq_flush_f_3_t_4_cnt = 0;
	int dns_zmq_flush_f_3_t_5_cnt = 0;
	int dns_zmq_flush_f_3_t_6_cnt = 0;
	int dns_zmq_flush_f_3_t_7_cnt = 0;
	int dns_zmq_flush_f_3_t_8_cnt = 0;
	int dns_zmq_flush_f_3_t_9_cnt = 0;

}

namespace errorCode {

char *dnsErrorCode[] = {
		"No Error",
		"Format Error",
		"Server Failure",
		"Non-Existent Domain Name",
		"Not Implemented",
		"Query Refused",
		"Name Exists when it should not",
		"RR Set Exists when it should not",
		"RR Set that should exist does not",
		"Server Not Authoritative for zone",
		"Name not contained in zone",
		"UNASSIGNED",
		"UNASSIGNED",
		"UNASSIGNED",
		"UNASSIGNED",
		"UNASSIGNED",
		"Bad OPT Version",
		"Key not recognized",
		"Signature out of time window",
		"Bad TKEY Mode",
		"Duplicate key name",
		"Algorithm not supported",
		"Bad Truncation",
		"Bad/missing server cookie"
	};
}

namespace tcpPort {
TCHAR *TCPPort[] = {
					"UNASSIGNED",			//0
					"TCPMUX",				//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"Remote Job Entry",		//5
					"UNASSIGNED",			//6
					"ECHO",					//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//10
					"UNASSIGNED",			//11
					"UNASSIGNED",			//12
					"UNASSIGNED",			//13
					"UNASSIGNED",			//14
					"UNASSIGNED",			//15
					"UNASSIGNED",			//16
					"UNASSIGNED",			//17
					"Message Send Protocol",	//18
					"UNASSIGNED",			//19
					"FTP-Data",				//20
					"FTP-Control",			//21
					"SSH",					//22
					"TELNET",				//23
					"UNASSIGNED",			//24
					"SMTP",					//25
					"UNASSIGNED",			//26
					"UNASSIGNED",			//27
					"UNASSIGNED",			//28
					"MSG ICP",				//29
					"UNASSIGNED",			//30
					"UNASSIGNED",			//31
					"UNASSIGNED",			//32
					"UNASSIGNED",			//33
					"UNASSIGNED",			//34
					"UNASSIGNED",			//35
					"UNASSIGNED",			//36
					"Time",					//37
					"UNASSIGNED",			//38
					"UNASSIGNED",			//39
					"UNASSIGNED",			//40
					"UNASSIGNED",			//41
					"Host Name Server",		//42
					"WhoIs",					//43
					"UNASSIGNED",			//44
					"UNASSIGNED",			//45
					"UNASSIGNED",			//46
					"UNASSIGNED",			//47
					"UNASSIGNED",			//48
					"Login Host Protocol",	//49
					"UNASSIGNED",			//50
					"UNASSIGNED",			//51
					"UNASSIGNED",			//52
					"DNS",					//53
					"UNASSIGNED",			//54
					"UNASSIGNED",			//55
					"UNASSIGNED",			//56
					"UNASSIGNED",			//57
					"UNASSIGNED",			//58
					"UNASSIGNED",			//59
					"UNASSIGNED",			//60
					"UNASSIGNED",			//61
					"UNASSIGNED",			//62
					"UNASSIGNED",			//63
					"UNASSIGNED",			//64
					"UNASSIGNED",			//65
					"UNASSIGNED",			//66
					"UNASSIGNED",			//67
					"UNASSIGNED",			//68
					"TFTP",					//69
					"Gopher Services",		//70
					"UNASSIGNED",			//71
					"UNASSIGNED",			//72
					"UNASSIGNED",			//73
					"UNASSIGNED",			//74
					"UNASSIGNED",			//75
					"UNASSIGNED",			//76
					"UNASSIGNED",			//77
					"UNASSIGNED",			//78
					"Finger",				//79
					"HTTP",					//80
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//90
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//100
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"X.400 Standard",		//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"SNA Gateway Access Server",	//8
					"POP2",					//9
					"POP3",				//110
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"SFTP",					//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"SQL Services",			//8
					"Newsgroup",				//9
					"UNASSIGNED",			//120
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//130
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"NetBIOS Name Service",	//7
					"UNASSIGNED",			//8
					"NetBIOS Datagram Service",	//9
					"UNASSIGNED",			//140
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"IMAP",					//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"NetBIOS Session Service", //150
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"SQL Server",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//160
					"SNMP",					//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//170
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"Border Gateway Protocol", //9
					"UNASSIGNED",			//180
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"GACP",					//190
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"Internet Relay Chat",	//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"DLS",					//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//200
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//210
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//220
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//230
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//240
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//250
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//260
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//270
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//280
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//290
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//300
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//310
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//320
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//330
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//340
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//350
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//360
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//370
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//380
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"LDAP",					//9
					"UNASSIGNED",			//390
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"Novell Netware over IP",//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//400
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//410
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//420
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//430
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//440
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"HTTPS"		,			//3
					"SNPP"		,			//4
					"Microsoft-DS",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//450
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"Apple QuickTime",		//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//460
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//470
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//480
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//490
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//500
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//510
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//520
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//530
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"UNASSIGNED",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED",			//540
					"UNASSIGNED",			//1
					"UNASSIGNED",			//2
					"UNASSIGNED",			//3
					"UNASSIGNED",			//4
					"UNASSIGNED",			//5
					"DHCP Client",			//6
					"UNASSIGNED",			//7
					"UNASSIGNED",			//8
					"UNASSIGNED",			//9
					"UNASSIGNED"			//550
	};
}

