/*
 * thrCounter.h
 *
 *  Created on: Jun 22, 2016
 *      Author: root
 */

#ifndef SRC_THRCOUNTER_H_
#define SRC_THRCOUNTER_H_

#include <stdlib.h>    //malloc
#include <string.h>    //strlen

#include "BaseConfig.h"
#include "IPGlobal.h"
#include "ProbeUtility.h"

typedef struct _thrData
{
	ULONG counter;
	_thrData()
	{
		counter = 0;
	}
}thrData;

class thrCounter : public BaseConfig {

	private:
	public:
		thrCounter();
		~thrCounter();
		VOID updateThrCounter(TPacket *msgObj);
		VOID writeThrCounter(int min);
};

#endif /* SRC_THRCOUNTER_H_ */
