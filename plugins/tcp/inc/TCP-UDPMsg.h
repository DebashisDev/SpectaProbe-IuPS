/*
 * TCP-UDPMsg.h
 *
 *  Created on: 15-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_TCP_INC_TCP_UDPMSG_H_
#define PLUGINS_TCP_INC_TCP_UDPMSG_H_

using namespace std;
/*
** Definition of DNS Resolution structure
*/

//typedef struct _dnsUrl{
//	ULONG 		pckLastTimeEpcohMicroSec;
//	char 		URL[50];
//	uint32_t 	address;
//
//	_dnsUrl()
//	{
//		pckLastTimeEpcohMicroSec = 0;
//		URL[0] = 0;
//		address = 0;
//	}
//}dnsUrl;

typedef struct _tcpData
{
	uint16_t 		packetType;
	uint32_t 		tcpTLen;
	uint32_t 		tcpHLen;
	uint32_t 		s_port;
	uint32_t 		d_port;
	uint32_t		payload;
	uint32_t 		seqNo;
	ULONG			packetNo;
	ULONG			tsval;
	ULONG			tsecr;
	uint16_t 		cType;
	std::string 	protoDesc; /* TCP, UDP, TLS, SSL */
	std::string 	appProto;
	std::string 	contentType;
	uint32_t		teid;
	uint32_t 		gtpuDirection;

	_tcpData()
	{ reset(); }

	void reset()
	{
		packetType = 0;
		tcpTLen = 0;
		tcpHLen = 0;
		s_port =0;
		d_port = 0;
		payload = 0;
		seqNo = 0;
		packetNo = 0;
		tsval = 0;
		tsecr = 0;
		cType = 0;
		protoDesc = "";
		appProto = "";
		contentType = "";
		teid = 0;
		gtpuDirection = 0;
	}

	void set(const _tcpData *obj)
	{
		this->packetType = obj->packetType;
		this->tcpTLen = obj->tcpTLen;
		this->tcpHLen = obj->tcpHLen;
		this->s_port = obj->s_port;
		this->d_port = obj->d_port;
		this->payload = obj->payload;
		this->seqNo = obj->seqNo;
		this->packetNo = obj->packetNo;
		this->tsval = obj->tsval;
		this->tsecr = obj->tsecr;
		this->cType = obj->cType;
		this->protoDesc.assign(obj->protoDesc);
		this->appProto.assign(obj->appProto);
		this->contentType.assign(obj->contentType);
		this->teid = obj->teid;
		this->gtpuDirection = obj->gtpuDirection;
	}
}tcpVar;

typedef struct _udpData
{
	uint32_t sP;
	uint32_t dP;
	uint32_t udpLen;
	uint32_t dnsLen;
	uint32_t ansLevel;
	uint32_t queLevel;
	uint32_t payload;
	ULONG	 packetNo;
	std::string 	protoDesc; /* TCP, UDP, TLS, SSL */
	string 	 appProto;
	uint32_t	teid;
	uint32_t	gtpuDirection;

	_udpData()
	{ reset(); }

	void reset()
	{
		sP = 0;
		dP = 0;
		udpLen = 0;
		dnsLen =0;
		ansLevel = 0;
		queLevel = 0;
		payload = 0;
		packetNo = 0;
		protoDesc = "";
		appProto = "";
		teid = 0;
		gtpuDirection = 0;
	}

	void set(const _udpData *obj)
	{
		this->sP = obj->sP;
		this->dP = obj->dP;
		this->udpLen = obj->udpLen;
		this->dnsLen = obj->dnsLen;
		this->ansLevel = obj->ansLevel;
		this->queLevel = obj->queLevel;
		this->payload = obj->payload;
		this->packetNo = obj->packetNo;
		this->protoDesc.assign(obj->protoDesc);
		this->appProto.assign(obj->appProto);
		this->teid = obj->teid;
		this->gtpuDirection = obj->gtpuDirection;
	}
}udpVar;

typedef struct _dnsData
{
	uint16_t cls;
	uint16_t type;
	string 	name;
	string 	address;

	_dnsData()
	{ reset(); }

	void reset()
	{
		cls = 0;
		type = 0;
		name = "";
		address = "";
	}

	void set(const _dnsData *obj)
	{
		reset();
		this->cls = obj->cls;
		this->type = obj->type;
		this->name.assign(obj->name);
		this->address.assign(obj->address);
	}

}dnsVar;

typedef struct _httpData
{
	string 		http;
	string 		httpRsp;

	_httpData()
	{ reset(); }

	void reset()
	{
		http = "";
		httpRsp = "";
	}

	void set (const _httpData *obj)
	{
		this->http.assign(obj->http);
		this->httpRsp.assign(obj->httpRsp);
	}
}httpVar;

#endif /* PLUGINS_TCP_INC_TCP_UDPMSG_H_ */
