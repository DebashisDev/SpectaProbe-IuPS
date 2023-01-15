/*
 * IPV4Msg.h
 *
 *  Created on: 18-Jul-2016
 *      Author: deb
 */

#ifndef CORE_INC_IPV4MSG_H_
#define CORE_INC_IPV4MSG_H_

#include <string.h>

using namespace std;

typedef struct _ipData
{
	uint32_t 	ipV;
	uint32_t 	ipTLen;
	uint32_t 	ipHLen;
	uint32_t 	protocol;
	uint32_t 	ttl;
	bool		direction;

	ULONG		s_addr_long;
	ULONG		d_addr_long;

	string 		sourceAddr;
	string		destAddr;

	_ipData()
	{ reset(); }

	void reset()
	{
		ipV 		= 0;
		ipTLen 		= 0;
		ipHLen 		= 0;
		protocol	= 0;
		ttl 		= 0;
		direction	= false;

		s_addr_long 		= 0;
		d_addr_long 		= 0;

		sourceAddr= "";
		destAddr= "";
	}

	void set(const _ipData *obj)
	{
		this->ipV 		= obj->ipV;
		this->ipTLen 	= obj->ipTLen;
		this->ipHLen 	= obj->ipHLen;
		this->protocol 	= obj->protocol;
		this->ttl 		= obj->ttl;
		this->direction = obj->direction;

		this->s_addr_long 	= obj->s_addr_long;
		this->d_addr_long 	= obj->d_addr_long;

		this->sourceAddr.assign(obj->sourceAddr);
		this->destAddr.assign(obj->destAddr);
	}
}ipVar;

typedef struct _otrIP4Data {

    int32_t		protocol;
	string		protoDesc;

//    string 		sIP;
//	string 		dIP;

	_otrIP4Data()
	{ reset(); }

	void reset()
	{
		protocol = 0;
		protoDesc= "";

//		sIP= "";
//		dIP= "";
	}

	void set(const _otrIP4Data *obj)
	{
		this->protocol = obj->protocol;
		this->protoDesc.assign(obj->protoDesc);

//		this->sIP.assign(obj->sIP);
//		this->dIP.assign(obj->dIP);
	}
}otrIP4Var;


#endif /* CORE_INC_IPV4MSG_H_ */
