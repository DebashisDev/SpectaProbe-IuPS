/*
 * ICMP.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: root
 */

#include "ICMP.h"
#include "Log.h"

ICMP::ICMP() {

}

ICMP::~ICMP() {

}

void ICMP::parsePacket(const BYTE packet, TPacket *msgObj, uint16_t ver)
{
	struct icmp6_hdr	*icmp6;
	struct icmphdr		*icmp4;

	TCHAR *zmqBuffer = (TCHAR *)malloc(500);
	std:string zmqData;

	// Get Current Min
	time_t now;
	struct tm *now_tm;

	now = time(NULL);
	now_tm = localtime(&now);
	int currentMin = now_tm->tm_min;


	msgObj->icmpData = new icmpVar();

	switch(ver)
	{
		case ICMP_V4:
			icmp4 = (struct icmphdr *) (packet); /* ICMP hdr */

			if(icmp4->type < MAX_ICMP_TYPE)
				strcpy(msgObj->icmpData->icmp4TypeDesc, (const char *)icmp4Type[icmp4->type]);
			else
				strcpy(msgObj->icmpData->icmp4TypeDesc, "Unassigned");

			msgObj->icmpData->icmp4Type = icmp4->type;
			msgObj->icmpData->icmp4Code = icmp4->code;

			switch(icmp4->type)
			{
				case ICMP_DEST_UNREACH:
								switch(icmp4->code)
								{
									case 0:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Net Unreachable");
											break;

									case 1:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Host Unreachable");
											break;

									case 2:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Protocol Unreachable");
											break;

									case 3:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Port Unreachable");
											break;

									case 4:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Fragmentation Needed and Don't Fragment was Set");
											break;

									case 5:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Source Route Failed");
											break;

									case 6:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Destination Network Unknown");
											break;

									case 7:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Destination Host Unknown");
											break;

									case 8:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Source Host Isolated");
											break;

									case 9:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Communication with Destination Network is Administratively Prohibited");
											break;

									case 10:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Communication with Destination Host is Administratively Prohibited");
											break;

									case 11:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Destination Network Unreachable for Type of Service");
											break;

									case 12:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Destination Host Unreachable for Type of Service");
											break;

									case 13:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Communication Administratively Prohibited");
											break;

									case 14:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Host Precedence Violation");
											break;

									case 15:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Precedence cutoff in effect");
											break;

									default:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Unknown");
											break;
								}
					break;

				case ICMP_TIME_EXCEEDED:
								switch(icmp4->code)
								{
									case 0:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Time to Live exceeded in Transit");
											break;

									case 1:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Fragment Reassembly Time Exceeded");
											break;

									default:
											strcpy(msgObj->icmpData->icmp4CodeDesc, "Unknown");
											break;
								}
					break;

				default:
						strcpy(msgObj->icmpData->icmp4CodeDesc, "Not Generated");
					break;
			}
//			TheLog_nc_v1(Log::Trace, "IP4-ICMP","    No.# : %d", IPGlobal::t_FrameCount);
//			TheLog_nc_v2(Log::Trace, "IP4-ICMP","    Type : %d| %s",icmp4->type, msgObj->icmpData->icmp4TypeDesc);
//			TheLog_nc_v2(Log::Trace, "IP4-ICMP","    Code : %d| %s", icmp4->code, msgObj->icmpData->icmp4CodeDesc);

			memset(zmqBuffer, 0, 500);
			sprintf(zmqBuffer, "%d,%d,%s,%s,%s,%s,%s,%d,%s,%d,%s,%d",
								10,
								3,
								"IP4",
								"ICMP",
								msgObj->frameData->frameTS,
								msgObj->ipData->sIP,
								msgObj->ipData->dIP,
								msgObj->icmpData->icmp4Type,
								msgObj->icmpData->icmp4TypeDesc,
								msgObj->icmpData->icmp4Code,
								msgObj->icmpData->icmp4CodeDesc,
								msgObj->frameData->frameSize);

//			TheLog_nc_v1(Log::Trace, "IPFlusher.cpp", " IP4-ICMP Flush Data [ %s ] ", zmqBuffer);

			zmqData = std::string((const char *)zmqBuffer);

			IPGlobal::flushIndex ++;
			TCPFlushMap::flushMap[currentMin][IPGlobal::flushIndex].protocol = IPv4_ICMP;
			TCPFlushMap::flushMap[currentMin][IPGlobal::flushIndex].data = zmqData;

			break;

		case ICMP_V6:
			icmp6 = (struct icmp6_hdr *) (packet); /* ICMP hdr */

			if(icmp6->icmp6_type < MAX_ICMP_TYPE)
				strcpy(msgObj->icmpData->icmp6TypeDesc, (const char *)icmp6Type[icmp6->icmp6_type]);
			else
				strcpy(msgObj->icmpData->icmp6TypeDesc, "Unassigned");

			msgObj->icmpData->icmp6Type = icmp6->icmp6_type;
			msgObj->icmpData->icmp6Code = icmp6->icmp6_code;

			switch(icmp6->icmp6_type)
			{
				case ICMP6_DST_UNREACH:
									switch(icmp6->icmp6_code)
									{
										case 0:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "No route to destination");
												break;
										case 1:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Communication with destination administratively prohibited");
												break;
										case 2:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Beyond scope of source address");
												break;
										case 3:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Address unreachable");
												break;
										case 4:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Port unreachable");
												break;
										case 5:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Source address failed ingress or egress policy");
												break;
										case 6:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Reject route to destination");
												break;
										case 7:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Error in Source Routing Header");
												break;

										default:
												strcpy(msgObj->icmpData->icmp6CodeDesc, "Unknown");
												break;

									}
									break;

				case ICMP6_TIME_EXCEEDED:
									switch(icmp6->icmp6_code)
									{
										case 0:
											strcpy(msgObj->icmpData->icmp6CodeDesc, "Hop limit exceeded in transit");
											break;

										case 1:
											strcpy(msgObj->icmpData->icmp6CodeDesc, "Fragment reassembly time exceeded");
											break;

										default:
											strcpy(msgObj->icmpData->icmp6CodeDesc, "Unknown");
											break;
									}
									break;

				default:
									strcpy(msgObj->icmpData->icmp6CodeDesc, "Not Generated");
									break;
			}

//			TheLog_nc_v1(Log::Trace, "IP6-ICMP","    No.# : %d", IPGlobal::t_FrameCount);
//			TheLog_nc_v2(Log::Trace, "IP6-ICMP","    Type : %d| %s", icmp6->icmp6_type, msgObj->icmpData->icmp6TypeDesc);
//			TheLog_nc_v2(Log::Trace, "IP6-ICMP","    Code : %d| %s", icmp6->icmp6_code, msgObj->icmpData->icmp6CodeDesc);

			memset(zmqBuffer, 0, 500);
			sprintf(zmqBuffer, "%d,%d,%s,%s,%s,%s,%s,%d,%s,%d,%s,%d",
								10,
								3,
								"IP6",
								"ICMP",
								msgObj->frameData->frameTS,
								msgObj->ip6Data->sourceIp,
								msgObj->ip6Data->destIp,
								msgObj->icmpData->icmp6Type,
								msgObj->icmpData->icmp6TypeDesc,
								msgObj->icmpData->icmp6Code,
								msgObj->icmpData->icmp6CodeDesc,
								msgObj->frameData->frameSize);

//			TheLog_nc_v1(Log::Trace, "IPFlusher.cpp", " IP6-ICMP Flush Data [ %s ] ", zmqBuffer);

			zmqData = std::string((const char *)zmqBuffer);

			IPGlobal::flushIndex ++;
			TCPFlushMap::flushMap[currentMin][IPGlobal::flushIndex].protocol = IPv6_ICMP;
			TCPFlushMap::flushMap[currentMin][IPGlobal::flushIndex].data = zmqData;

			break;

		default:
				break;
	}
	zmqData.clear();
//	memset(icmp6, 0, sizeof(struct icmp6_hdr));
//	memset(icmp4, 0, sizeof(struct icmphdr));
	free(zmqBuffer);
	delete(msgObj->icmpData);
}
