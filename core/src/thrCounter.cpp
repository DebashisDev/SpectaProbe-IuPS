/*
 * thrCounter.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: root
 */

#include <string.h>

#include "thrCounter.h"
#include "Log.h"
#include "BWData.h"

thrData thr_min_0[60];
thrData thr_min_1[60];
thrData thr_min_2[60];
thrData thr_min_3[60];

thrCounter::thrCounter() {
	this->_name = "ThreadCounter";
	this->setLogLevel(Log::theLog().level());

}

thrCounter::~thrCounter()
{}

void thrCounter::updateThrCounter(TPacket *msgObj)
{

	int min = msgObj->frameData->frameMinute;

	switch(msgObj->threadId)
	{
		case 0:
				thr_min_0[min].counter ++;
				break;

		case 1:
				thr_min_1[min].counter ++;
				break;

		case 2:
				thr_min_2[min].counter ++;
				break;

		case 3:
				thr_min_3[min].counter ++;
				break;
	}
}

void thrCounter::writeThrCounter(int min)
{
	TheLog_v4(Log::Info, "    ThreadCount", " Packet Processed Thread#0 [%lu] Thread#1 [%lu] Thread#2 [%lu] for minute [%d] ...",
			thr_min_0[min].counter, thr_min_1[min].counter, thr_min_2[min].counter, min);

	thr_min_0[min].counter = 0;
	thr_min_1[min].counter = 0;
	thr_min_2[min].counter = 0;
}
