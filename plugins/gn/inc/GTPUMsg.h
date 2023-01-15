/*
 * GTPUMsg.h
 *
 *  Created on: 02-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_INC_GTPUMSG_H_
#define PLUGINS_GN_INC_GTPUMSG_H_

using namespace std;

typedef struct _gtpuData
{
	uint32_t 	IpPayload;

	string		sIP;
	string		dIP;
	uint32_t 	sp;
	uint32_t 	dp;
	uint32_t 	ipTLen;
	uint32_t 	ipHLen;
	uint32_t	ipVer;
	uint32_t	protocol;
	uint32_t	seqNo;
	uint32_t	direction;
	string		teid;
	uint32_t	nwtSIP;
	uint32_t	nwtDIP;

	_gtpuData()
	{
		reset();
	}

	void reset()
	{
		IpPayload = 0;

		sIP.clear();
		dIP.clear();

		sp = 0;
		dp = 0;

		ipTLen = 0;
		ipHLen = 0;
		ipVer = 0;
		protocol = 0;
		seqNo = 0;
		direction = 0;
		teid.clear();
		nwtSIP = 0;
		nwtDIP = 0;
	}
}gtpuMsg;


#endif /* PLUGINS_GN_INC_GTPUMSG_H_ */
