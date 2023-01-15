/*
 * TraceListener.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: Deb
 */

#include "TraceListener.h"
#include "sys/time.h"

TraceListener::TraceListener() {
}

TraceListener::~TraceListener() {
}

VOID TraceListener::run()
{
	int currentSec = 0;
	int lastProcessedIndex = -1;
	int curIndex = -1;

	printf("TraceListener instance started.\n");

	struct tm *now_tm;
	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);

	curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX);
	if(curIndex < 0) curIndex = IPGlobal::FLUSHER_TIMEINDEX + curIndex;
	lastProcessedIndex = curIndex;

	while(true)
	{
		sleep(1);
		gettimeofday(&curTime, NULL);
		now_tm = localtime(&curTime.tv_sec);

		curIndex = (((curTime.tv_sec % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX);
		if(curIndex < 0) curIndex = IPGlobal::FLUSHER_TIMEINDEX + curIndex;

		if(lastProcessedIndex != curIndex)
		{
			sleep(1);
			process(lastProcessedIndex);
			lastProcessedIndex++;
			if(lastProcessedIndex > 9) lastProcessedIndex = 0;
		}
	}
}


//VOID TraceListener::processMessage(MPacket *msgObj)
//{
//	char *buffer;
//	buffer = (char *)malloc(300);
//
//	buffer[0] = 0;
//
//	string TraceData = "";
//
//	sprintf(buffer, "-- TRACE -------------------------------------\n");
//	TraceData.assign(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	GTPu/GTPc		: %d\n", msgObj->ipAppProtocol);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	TCP/UDP			: %d\n", msgObj->ipProtocol);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	Source_IP_Addr		: %lu\n", msgObj->ipSourceAddr);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	Destination_IP_Addr	: %lu\n", msgObj->ipDestAddr);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	OPC			: %d\n", msgObj->protoSourcePort);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	DPC			: %d\n", msgObj->protoDestPort);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	MSISDN			: %s\n", msgObj->MSISDN);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	IMSI			: %s\n", msgObj->IMSI);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	IMEI			: %s\n", msgObj->IMEI);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	RAT_Id			: %d\n", msgObj->gtpcRAT);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	Tunnel_Id_D_Dn		: %lu\n", msgObj->gtpcPktTunnelId);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	Tunnel_Id_C_Dn		: %lu\n", msgObj->gtpcTunnel_Id_Control);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//
//	sprintf(buffer, "	Charging GW		: %s\n", msgObj->gtpcChargingGWAddr);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	PDP_Addr_Allocated	: %s\n", msgObj->gtpUserIpAddress);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	End_Cause		: %d\n", msgObj->gtpcCauseCode);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	PLMN_Id			: %d-%d\n", msgObj->gtpcMCC, msgObj->gtpcMNC);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	LAC_Id			: %d\n", msgObj->gtpcLAC);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	RAC_Id			: %d\n", msgObj->gtpcRAC);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "	Cell_Id			: %d\n", msgObj->gtpcCellId);
//	TraceData.append(buffer);
//	buffer[0] = '\0';
//
//	sprintf(buffer, "-------------------------------------------------\n");
//	TraceData.append(buffer);
//
////	buffer[0] = '\0';
//	delete[] buffer;
//
//
//	fp << TraceData << endl;
//}


VOID TraceListener::process(int idx){

	process_i_0_r_0(idx);
	process_i_0_r_1(idx);
	process_i_0_r_2(idx);
	process_i_0_r_3(idx);

	process_i_1_r_0(idx);
	process_i_1_r_1(idx);
	process_i_1_r_2(idx);
	process_i_1_r_3(idx);

	process_i_2_r_0(idx);
	process_i_2_r_1(idx);
	process_i_2_r_2(idx);
	process_i_2_r_3(idx);

	process_i_3_r_0(idx);
	process_i_3_r_1(idx);
	process_i_3_r_2(idx);
	process_i_3_r_3(idx);
}

VOID TraceListener::processMessage(int &tr_msg_cnt, std::string (&tr_msg)[TRACE_QUEUE_LIMIT])
{
	int recCnt = tr_msg_cnt;
	if(recCnt > 0)
	{
		fp.open("/data/SpectaProbe/trace/trace.txt", ios :: out | ios :: app);
		if(fp.fail())
		{
			printf("  Error in Opening Configuration File : %s\n", "/data/SpectaProbe/trace/trace.txt");
			exit(1);
		}

		for(int i=0; i<recCnt; i++)
		{
			fp << tr_msg[i] << endl;
			tr_msg_cnt--;
			tr_msg[i] = "";
		}
		tr_msg_cnt = 0;
		fp.close();
	}
}

VOID TraceListener::process_i_0_r_0(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_0_cnt, TraceStore::tr_msg_i_0_r_0_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_1_cnt, TraceStore::tr_msg_i_0_r_0_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_2_cnt, TraceStore::tr_msg_i_0_r_0_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_3_cnt, TraceStore::tr_msg_i_0_r_0_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_4_cnt, TraceStore::tr_msg_i_0_r_0_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_5_cnt, TraceStore::tr_msg_i_0_r_0_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_6_cnt, TraceStore::tr_msg_i_0_r_0_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_7_cnt, TraceStore::tr_msg_i_0_r_0_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_8_cnt, TraceStore::tr_msg_i_0_r_0_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_0_r_0_t_9_cnt, TraceStore::tr_msg_i_0_r_0_t_9);
			break;
	}
}

VOID TraceListener::process_i_0_r_1(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_0_cnt, TraceStore::tr_msg_i_0_r_1_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_1_cnt, TraceStore::tr_msg_i_0_r_1_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_2_cnt, TraceStore::tr_msg_i_0_r_1_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_3_cnt, TraceStore::tr_msg_i_0_r_1_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_4_cnt, TraceStore::tr_msg_i_0_r_1_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_5_cnt, TraceStore::tr_msg_i_0_r_1_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_6_cnt, TraceStore::tr_msg_i_0_r_1_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_7_cnt, TraceStore::tr_msg_i_0_r_1_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_8_cnt, TraceStore::tr_msg_i_0_r_1_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_0_r_1_t_9_cnt, TraceStore::tr_msg_i_0_r_1_t_9);
			break;
	}
}

VOID TraceListener::process_i_0_r_2(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_0_cnt, TraceStore::tr_msg_i_0_r_2_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_1_cnt, TraceStore::tr_msg_i_0_r_2_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_2_cnt, TraceStore::tr_msg_i_0_r_2_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_3_cnt, TraceStore::tr_msg_i_0_r_2_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_4_cnt, TraceStore::tr_msg_i_0_r_2_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_5_cnt, TraceStore::tr_msg_i_0_r_2_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_6_cnt, TraceStore::tr_msg_i_0_r_2_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_7_cnt, TraceStore::tr_msg_i_0_r_2_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_8_cnt, TraceStore::tr_msg_i_0_r_2_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_0_r_2_t_9_cnt, TraceStore::tr_msg_i_0_r_2_t_9);
			break;
	}
}

VOID TraceListener::process_i_0_r_3(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_0_cnt, TraceStore::tr_msg_i_0_r_3_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_1_cnt, TraceStore::tr_msg_i_0_r_3_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_2_cnt, TraceStore::tr_msg_i_0_r_3_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_3_cnt, TraceStore::tr_msg_i_0_r_3_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_4_cnt, TraceStore::tr_msg_i_0_r_3_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_5_cnt, TraceStore::tr_msg_i_0_r_3_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_6_cnt, TraceStore::tr_msg_i_0_r_3_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_7_cnt, TraceStore::tr_msg_i_0_r_3_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_8_cnt, TraceStore::tr_msg_i_0_r_3_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_0_r_3_t_9_cnt, TraceStore::tr_msg_i_0_r_3_t_9);
			break;
	}
}


VOID TraceListener::process_i_1_r_0(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_0_cnt, TraceStore::tr_msg_i_1_r_0_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_1_cnt, TraceStore::tr_msg_i_1_r_0_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_2_cnt, TraceStore::tr_msg_i_1_r_0_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_3_cnt, TraceStore::tr_msg_i_1_r_0_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_4_cnt, TraceStore::tr_msg_i_1_r_0_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_5_cnt, TraceStore::tr_msg_i_1_r_0_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_6_cnt, TraceStore::tr_msg_i_1_r_0_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_7_cnt, TraceStore::tr_msg_i_1_r_0_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_8_cnt, TraceStore::tr_msg_i_1_r_0_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_1_r_0_t_9_cnt, TraceStore::tr_msg_i_1_r_0_t_9);
			break;
	}
}

VOID TraceListener::process_i_1_r_1(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_0_cnt, TraceStore::tr_msg_i_1_r_1_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_1_cnt, TraceStore::tr_msg_i_1_r_1_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_2_cnt, TraceStore::tr_msg_i_1_r_1_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_3_cnt, TraceStore::tr_msg_i_1_r_1_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_4_cnt, TraceStore::tr_msg_i_1_r_1_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_5_cnt, TraceStore::tr_msg_i_1_r_1_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_6_cnt, TraceStore::tr_msg_i_1_r_1_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_7_cnt, TraceStore::tr_msg_i_1_r_1_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_8_cnt, TraceStore::tr_msg_i_1_r_1_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_1_r_1_t_9_cnt, TraceStore::tr_msg_i_1_r_1_t_9);
			break;
	}
}

VOID TraceListener::process_i_1_r_2(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_0_cnt, TraceStore::tr_msg_i_1_r_2_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_1_cnt, TraceStore::tr_msg_i_1_r_2_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_2_cnt, TraceStore::tr_msg_i_1_r_2_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_3_cnt, TraceStore::tr_msg_i_1_r_2_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_4_cnt, TraceStore::tr_msg_i_1_r_2_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_5_cnt, TraceStore::tr_msg_i_1_r_2_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_6_cnt, TraceStore::tr_msg_i_1_r_2_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_7_cnt, TraceStore::tr_msg_i_1_r_2_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_8_cnt, TraceStore::tr_msg_i_1_r_2_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_1_r_2_t_9_cnt, TraceStore::tr_msg_i_1_r_2_t_9);
			break;
	}
}

VOID TraceListener::process_i_1_r_3(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_0_cnt, TraceStore::tr_msg_i_1_r_3_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_1_cnt, TraceStore::tr_msg_i_1_r_3_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_2_cnt, TraceStore::tr_msg_i_1_r_3_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_3_cnt, TraceStore::tr_msg_i_1_r_3_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_4_cnt, TraceStore::tr_msg_i_1_r_3_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_5_cnt, TraceStore::tr_msg_i_1_r_3_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_6_cnt, TraceStore::tr_msg_i_1_r_3_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_7_cnt, TraceStore::tr_msg_i_1_r_3_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_8_cnt, TraceStore::tr_msg_i_1_r_3_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_1_r_3_t_9_cnt, TraceStore::tr_msg_i_1_r_3_t_9);
			break;
	}
}


VOID TraceListener::process_i_2_r_0(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_0_cnt, TraceStore::tr_msg_i_2_r_0_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_1_cnt, TraceStore::tr_msg_i_2_r_0_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_2_cnt, TraceStore::tr_msg_i_2_r_0_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_3_cnt, TraceStore::tr_msg_i_2_r_0_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_4_cnt, TraceStore::tr_msg_i_2_r_0_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_5_cnt, TraceStore::tr_msg_i_2_r_0_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_6_cnt, TraceStore::tr_msg_i_2_r_0_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_7_cnt, TraceStore::tr_msg_i_2_r_0_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_8_cnt, TraceStore::tr_msg_i_2_r_0_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_2_r_0_t_9_cnt, TraceStore::tr_msg_i_2_r_0_t_9);
			break;
	}
}

VOID TraceListener::process_i_2_r_1(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_0_cnt, TraceStore::tr_msg_i_2_r_1_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_1_cnt, TraceStore::tr_msg_i_2_r_1_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_2_cnt, TraceStore::tr_msg_i_2_r_1_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_3_cnt, TraceStore::tr_msg_i_2_r_1_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_4_cnt, TraceStore::tr_msg_i_2_r_1_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_5_cnt, TraceStore::tr_msg_i_2_r_1_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_6_cnt, TraceStore::tr_msg_i_2_r_1_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_7_cnt, TraceStore::tr_msg_i_2_r_1_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_8_cnt, TraceStore::tr_msg_i_2_r_1_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_2_r_1_t_9_cnt, TraceStore::tr_msg_i_2_r_1_t_9);
			break;
	}
}

VOID TraceListener::process_i_2_r_2(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_0_cnt, TraceStore::tr_msg_i_2_r_2_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_1_cnt, TraceStore::tr_msg_i_2_r_2_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_2_cnt, TraceStore::tr_msg_i_2_r_2_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_3_cnt, TraceStore::tr_msg_i_2_r_2_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_4_cnt, TraceStore::tr_msg_i_2_r_2_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_5_cnt, TraceStore::tr_msg_i_2_r_2_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_6_cnt, TraceStore::tr_msg_i_2_r_2_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_7_cnt, TraceStore::tr_msg_i_2_r_2_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_8_cnt, TraceStore::tr_msg_i_2_r_2_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_2_r_2_t_9_cnt, TraceStore::tr_msg_i_2_r_2_t_9);
			break;
	}
}

VOID TraceListener::process_i_2_r_3(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_0_cnt, TraceStore::tr_msg_i_2_r_3_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_1_cnt, TraceStore::tr_msg_i_2_r_3_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_2_cnt, TraceStore::tr_msg_i_2_r_3_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_3_cnt, TraceStore::tr_msg_i_2_r_3_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_4_cnt, TraceStore::tr_msg_i_2_r_3_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_5_cnt, TraceStore::tr_msg_i_2_r_3_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_6_cnt, TraceStore::tr_msg_i_2_r_3_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_7_cnt, TraceStore::tr_msg_i_2_r_3_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_8_cnt, TraceStore::tr_msg_i_2_r_3_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_2_r_3_t_9_cnt, TraceStore::tr_msg_i_2_r_3_t_9);
			break;
	}
}


VOID TraceListener::process_i_3_r_0(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_0_cnt, TraceStore::tr_msg_i_3_r_0_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_1_cnt, TraceStore::tr_msg_i_3_r_0_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_2_cnt, TraceStore::tr_msg_i_3_r_0_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_3_cnt, TraceStore::tr_msg_i_3_r_0_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_4_cnt, TraceStore::tr_msg_i_3_r_0_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_5_cnt, TraceStore::tr_msg_i_3_r_0_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_6_cnt, TraceStore::tr_msg_i_3_r_0_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_7_cnt, TraceStore::tr_msg_i_3_r_0_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_8_cnt, TraceStore::tr_msg_i_3_r_0_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_3_r_0_t_9_cnt, TraceStore::tr_msg_i_3_r_0_t_9);
			break;
	}
}

VOID TraceListener::process_i_3_r_1(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_0_cnt, TraceStore::tr_msg_i_3_r_1_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_1_cnt, TraceStore::tr_msg_i_3_r_1_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_2_cnt, TraceStore::tr_msg_i_3_r_1_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_3_cnt, TraceStore::tr_msg_i_3_r_1_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_4_cnt, TraceStore::tr_msg_i_3_r_1_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_5_cnt, TraceStore::tr_msg_i_3_r_1_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_6_cnt, TraceStore::tr_msg_i_3_r_1_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_7_cnt, TraceStore::tr_msg_i_3_r_1_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_8_cnt, TraceStore::tr_msg_i_3_r_1_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_3_r_1_t_9_cnt, TraceStore::tr_msg_i_3_r_1_t_9);
			break;
	}
}

VOID TraceListener::process_i_3_r_2(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_0_cnt, TraceStore::tr_msg_i_3_r_2_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_1_cnt, TraceStore::tr_msg_i_3_r_2_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_2_cnt, TraceStore::tr_msg_i_3_r_2_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_3_cnt, TraceStore::tr_msg_i_3_r_2_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_4_cnt, TraceStore::tr_msg_i_3_r_2_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_5_cnt, TraceStore::tr_msg_i_3_r_2_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_6_cnt, TraceStore::tr_msg_i_3_r_2_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_7_cnt, TraceStore::tr_msg_i_3_r_2_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_8_cnt, TraceStore::tr_msg_i_3_r_2_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_3_r_2_t_9_cnt, TraceStore::tr_msg_i_3_r_2_t_9);
			break;
	}
}

VOID TraceListener::process_i_3_r_3(int idx)
{

	switch(idx)
	{
		case 0:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_0_cnt, TraceStore::tr_msg_i_3_r_3_t_0);
			break;
		case 1:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_1_cnt, TraceStore::tr_msg_i_3_r_3_t_1);
			break;
		case 2:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_2_cnt, TraceStore::tr_msg_i_3_r_3_t_2);
			break;
		case 3:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_3_cnt, TraceStore::tr_msg_i_3_r_3_t_3);
			break;
		case 4:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_4_cnt, TraceStore::tr_msg_i_3_r_3_t_4);
			break;
		case 5:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_5_cnt, TraceStore::tr_msg_i_3_r_3_t_5);
			break;
		case 6:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_6_cnt, TraceStore::tr_msg_i_3_r_3_t_6);
			break;
		case 7:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_7_cnt, TraceStore::tr_msg_i_3_r_3_t_7);
			break;
		case 8:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_8_cnt, TraceStore::tr_msg_i_3_r_3_t_8);
			break;
		case 9:
			processMessage(TraceStore::tr_msg_i_3_r_3_t_9_cnt, TraceStore::tr_msg_i_3_r_3_t_9);
			break;
	}
}
