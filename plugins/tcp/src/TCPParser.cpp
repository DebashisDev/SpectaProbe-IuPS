/*
 * TCPProbe.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: debashis
 */


#include "TCPParser.h"

#include <pthread.h>
#include <string.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <ctype.h>
#include <algorithm>
#include <string>

#include "Log.h"

using namespace std;

// --------------------------------------------------------------------
TCPParser::TCPParser()
{
	tsval = tsecr = 0;
	psh = rst = syn = fin = window = ack = urg = ackNo = check = urgPtr = 0;
	tcpHeader = 0;

//	this->_name = string("TCP");
//	this->setLogLevel(Log::theLog().level());
}

// --------------------------------------------------------------------
TCPParser::~TCPParser()
{

}

// --------------------------------------------------------------------
VOID
TCPParser::parsePacket(const BYTE packet, MPacket *msgObj)
{ 
	uint16_t cType = 0;

	tcpHeader = (struct tcphdr *)(packet);

	msgObj->tcpHLen = ((tcpHeader->doff) << 2);
	msgObj->protoSourcePort = ntohs((unsigned short int)tcpHeader->source);
	msgObj->protoDestPort = ntohs((unsigned short int)tcpHeader->dest);
	msgObj->tcpSeqNo = htonl((unsigned long int)tcpHeader->seq);

//	ackNo = htonl((unsigned long int)tcpHeader->ack_seq);
//	window = ntohs((unsigned short int)tcpHeader->window);
//	check = ntohs((unsigned short int)tcpHeader->check);
//	urgPtr = ntohs((unsigned short int)tcpHeader->urg_ptr);

	urg = tcpHeader->urg;
	ack = tcpHeader->ack;
	psh = tcpHeader->psh;
	rst = tcpHeader->rst;
	syn = tcpHeader->syn;
	fin = tcpHeader->fin;

	msgObj->protoPayload = msgObj->ipTLen - (msgObj->ipHLen + msgObj->tcpHLen);

	// Check TCP Packet Type (i.e. TLSv1/TLSv1.2 or Normal)
	if(msgObj->protoPayload > 0)
	{
		  msgObj->tcpSSLVer = VAL_BYTE(packet + msgObj->tcpHLen);
		  uint16_t  version = (uint16_t) VAL_USHORT(packet + msgObj->tcpHLen + 1);

//		  switch(version)
//		  {
//		  	  case SSL_V_1:
//		  		  	  msgObj->protoProtoDesc.assign("TLSv1");
//		  		  	  break;
//
//		  	  case SSL_V_1_2:
//	  		  	  	  msgObj->protoProtoDesc.assign("TLSv1.2");
//	  		  	  	  break;
//
//		  	  default:
//		  		  	  msgObj->protoProtoDesc.assign("TCP");
//		  		  	  break;
//		  }

		  switch(msgObj->tcpSSLVer)
		  {
		  	  case SSL_ID_CHG_CIPHER_SPEC:
		  	  case SSL_ID_ALERT:
		  	  case SSL_ID_APP_DATA:
		  		  	  break;

		  	  case SSL_ID_HANDSHAKE:
//		  		  	  PacketSSL::decodeSSL(packet, msgObj); // TBD
		  		  	  break;

		  	  default:
		  		  	  break;
		  }
	}
//	else
//	{
//		msgObj->tcpCType = 0;
//	}
		
	/* ---------------- Session Management --------------------- */
	
//	if((msgObj->protoSourcePort > 550  && msgObj->protoDestPort > 550))
//	{
//		msgObj->protoAppProto.assign("UNASSIGNED");
//    }
//	else if((msgObj->protoSourcePort > 550  && msgObj->protoDestPort <= 550))
//	{
//		msgObj->protoAppProto = tcpPort::TCPPort[msgObj->protoDestPort];
//	}
//	else if((msgObj->protoSourcePort <= 550  && msgObj->protoDestPort > 550))
//	{
//		msgObj->protoAppProto = tcpPort::TCPPort[msgObj->protoSourcePort];
//	}
//	else
//	{
//		msgObj->protoAppProto.assign("UNASSIGNED");
//	}


	/* ** Connection Request ** */
	if((syn == OK) && (ack == NOK) && (psh == NOK) && (fin == NOK))
	{
		msgObj->tcpFlags = SYN_RCV;
	}
	/* ** Connection Request with Response ** */
	else if((syn == OK) && (ack == OK) && (psh == NOK) && (fin == NOK))
	{
		msgObj->tcpFlags = SYN_ACK_RCV;
	}
	/* ** Connection Complete ** */
   	else if((syn == NOK) && (ack == OK) && (rst == NOK) && (fin == NOK) && (msgObj->protoPayload == 0))
	{
   		msgObj->tcpFlags = ACK_RCV;
	}
	/* ** Data Request** */
	else if((rst == NOK) && (fin == NOK) && (msgObj->protoPayload > 0))
	{
//		if(msgObj->protoSourcePort == 80 || msgObj->protoDestPort == 80)
//			checkContentType(packet + msgObj->protoHLen, msgObj);

		ProbeUtility::parseTcpTimeStamp(tcpHeader, &tsval, &tsecr);				// Fetch TSVAL and TSECR
		msgObj->tcpTsVal = tsval;
		msgObj->tcpTsEcr = tsecr;

		msgObj->tcpFlags = DATA_RCV;
	}
	/* ** Disconnect Request ** */
	else if(fin == OK || rst == OK)
	{
		msgObj->tcpFlags = FIN_RCV;
	}else{
		//This should never happen, but in case
		msgObj->tcpFlags = TCP_UNKNOWN_PACKET_TYPE;
	}

	/* ---------------- End of Session Management --------------------- */

	tcpHeader = NULL;

}

void TCPParser::checkContentType(const BYTE packet, MPacket *msgObj)
{
	int i, posIndex;
	const u_char *ch;
	std::string buffer, httpRspHdr;
	int length = 4;
	bool doFlag = false;

	string::iterator it;

	buffer.clear();
	httpRspHdr.clear();

	posIndex = 0;

	ch = packet;

	// Check for first 4 character as HTTP
	for(i = 0; i < length; i++) {
		httpRspHdr.append(1, *ch);
		ch++;
	}

	std::size_t pos = httpRspHdr.find("HTTP");

	if(pos != std::string::npos) {
		doFlag = true;
	}
	else {
		return;
	}

	int len = msgObj->protoPayload - length;

	if(doFlag) {
		for(i = 0; i < len; i++) {
			if(*ch != CR) {
				buffer.append(1, *ch);
				posIndex ++;
				ch++;

			}	// If
			else {
				std::size_t pos = buffer.find("Content-Type:");

				if(pos != std::string::npos) {
					vector<string> sep = split(buffer, ':'); //Content-Type: application/x-javascript; charset=utf-8-

					if(sep.size() > 1) {
						for (int n = 0; n != sep[1].length(); n++) {
							if(sep[1][n] == ';' || n == 50 || sep[1][n] == ',') {
								return;
							}

							if ((sep[1][n] >= 'a' && sep[1][n] <= 'z') || (sep[1][n] == '/')) {
//								msgObj->tcpCType[n].append(1, sep[1][n]);
								msgObj->tcpCType[n] = sep[1][n];
							}
						}
					}
					else {
						return;
					}
				}

				ch += 2;
				buffer.clear();
			} // Else
		}	// For Loop
	}	// End of If Condition
}

vector<string> TCPParser::split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string token;

	while(getline(ss, token, delimiter)) {
	    internal.push_back(token);
	}

	return internal;
}
