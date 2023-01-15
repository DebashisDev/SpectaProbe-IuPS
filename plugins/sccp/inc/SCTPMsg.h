/*
 * SCTPMsg.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCCP_INC_SCTPMSG_H_
#define PLUGINS_SCCP_INC_SCTPMSG_H_

using namespace std;

typedef struct _sctpMsg
{
	unsigned int tsn;
	unsigned int sequence_no;
	int opc;
	int dpc;
	int protocol;

	_sctpMsg()
	{ reset(); }

//	~_sctpMsg(){}

	void reset()
	{
		tsn = 0;
		sequence_no = 0;
		opc = 0;
		dpc =0;
		protocol =0;
	}

	void set(const _sctpMsg *obj)
	{
		this->tsn = obj->tsn;
		this->sequence_no = obj->sequence_no;
		this->opc = obj->opc;
		this->dpc = obj->dpc;
		this->protocol = obj->protocol;
	}

}sctpMsg;

#endif /* PLUGINS_SCCP_INC_SCTPMSG_H_ */
