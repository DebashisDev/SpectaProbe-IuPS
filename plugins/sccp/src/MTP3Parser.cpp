/*
 * MTP3Parser.cpp
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */
#include "MTP3Parser.h"


MTP3Parser::MTP3Parser() {
//	cout << "Calling MTP3Parser::MTP3Parser() Constructor" << endl;
	sccp = new SCCPParser();
}

MTP3Parser::~MTP3Parser() {
	delete (sccp);
}

void MTP3Parser::processPacket(const BYTE packet, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo, int length)
{
	struct m3uahdr *ptr_m3uahdr = (struct m3uahdr *)(packet);

	int m3uahdr_len = sizeof(struct m3uahdr);
	unsigned short param_tag = ntohs(*(packet + m3uahdr_len));
	unsigned short param_length = ntohs(*(packet + m3uahdr_len + 2));
	struct ss7hdr *sptr = (struct ss7hdr*)(packet + m3uahdr_len + 2 + 2);

	if(PCons::P_MTP3 && PCons::TRACE) printf("     Protocol 		: SS7 [");
	if(PCons::P_MTP3 && PCons::TRACE) printf("OPC:%u DPC:%u SI:%u NI:%u MP:%u SLS:%u]\n", ntohl(sptr->opc),ntohl(sptr->dpc),sptr->si,sptr->ni,sptr->mp,sptr->sls);
	sctpMsgObj->sctp_opc = ntohl(sptr->opc);
	sctpMsgObj->sctp_dpc = ntohl(sptr->dpc);


	unsigned int ss7_protocol_shift = m3uahdr_len + 2 + 2 + sizeof(struct ss7hdr);
	unsigned int ss7_protocol_data_length = length - ss7_protocol_shift;

	if(sptr->si == 3)
		sccp->processPacket(packet + ss7_protocol_shift, msgObj, sctpMsgObj, chunkNo, ss7_protocol_data_length);
	else
		printf("\n\n************  Not a SCCP Packet **********************************\n\n");
}
