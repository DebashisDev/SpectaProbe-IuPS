/*
 * ETHMsg.h
 *
 *  Created on: 18-Jul-2016
 *      Author: deb
 */

#ifndef CORE_INC_ETHMSG_H_
#define CORE_INC_ETHMSG_H_

using namespace std;

typedef struct _ethIIData
{
	uint16_t	protocolId;
	uint32_t	packetSize;
	string		sourceMacAddr;
	string		destMacAddr;
	uint16_t	vLanId;

	_ethIIData()
	{ reset(); }

	void reset()
	{
		protocolId = 0;
		packetSize = 0;
		sourceMacAddr = "";
		destMacAddr = "";
		vLanId = 0;
	}

	void set(const _ethIIData *obj)
	{
		this->protocolId = obj->protocolId;
		this->packetSize = obj->packetSize;
		this->sourceMacAddr.assign(obj->sourceMacAddr);
		this->destMacAddr.assign(obj->destMacAddr);
		this->vLanId = obj->vLanId;
	}
}ethernetVar;




#endif /* CORE_INC_ETHMSG_H_ */
