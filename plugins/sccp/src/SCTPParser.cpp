/*
 * SCTPParser.cpp
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#include "SCTPParser.h"

SCTPParser::SCTPParser() {
	sctpMsgObj = new SCTP();
	mtp3 = new MTP3Parser();
	this->_name = "SCTPParser";
	this->setLogLevel(Log::theLog().level());

}

SCTPParser::~SCTPParser() {
	delete (sctpMsgObj);
	delete (mtp3);
}

void SCTPParser::parsePacket(const BYTE packet, MPacket *msgObj)
{
	int sh_len = sizeof(struct sctphdr);

	struct sctphdr *sh = (struct sctphdr *)(packet);
	if (PCons::P_SCTP && PCons::DEBUG) printf("SCTP HDR %d,%d,%08x,%08x\n",ntohs(sh->source_port), ntohs(sh->dest_port),ntohl(sh->verification_tag), ntohl(sh->checksum));

	int chunkNo = 0;
	int chunkIdx = 0;
	int sctp_chunk_offset=sh_len;
	int sctp_packet_length = msgObj->ipTLen - msgObj->ipHLen;

	if(PCons::P_SCTP && PCons::DEBUG) printf("Begin point of SCTP data chunk read	: %u\n", sctp_chunk_offset);
	if(PCons::P_SCTP && PCons::DEBUG) printf("SCTP Packet Length			: %u\n", sctp_packet_length);

	while(sctp_chunk_offset < sctp_packet_length){
		struct sctp_chunkhdr *sch = (struct sctp_chunkhdr *)(packet + sctp_chunk_offset);
		int chunk_type = sch->chunk_type;
		int chunk_length = ntohs(sch->chunk_length);

		if(chunk_length == 0) break;

		if(PCons::P_SCTP && PCons::DEBUG) printf(" Chunk Number		: %d [%d]", chunkNo, IPGlobal::t_FrameCount);

		if(PCons::P_SCTP && PCons::DEBUG) printf("  Chunk Flag	        : %u\n", sch->chunk_flags);
		if(PCons::P_SCTP && PCons::DEBUG) printf("  Chunk length		: %d\n", chunk_length);

		int chunk_data_length = 0;

		if(chunk_type == SCTP_DATA){
			chunk_data_length = chunk_length - 16;
			sctpMsgObj->reset();
			decode_sctp_chunk_data(packet, sctp_chunk_offset, chunk_data_length, msgObj, sctpMsgObj, chunkNo);
			sctpMap[msgObj->packetNo][chunkIdx].copy(sctpMsgObj);
			chunkIdx++;
			if(PCons::P_SCTP && PCons::DEBUG) printf("  SCTP Chunk processing completed\n");
		}else{
			if(PCons::P_SCTP && PCons::WARNING) printf("** [SCTP] Attention!!! Not processing chunk of type [%d]\n", chunk_type);
		}

		sctp_chunk_offset += chunk_length;
//		printf("** [SCTP] ChunkNo [%d] IMSI::%s\n",	chunkNo, msgObj->SCTPData[chunkNo].iups_IMSI);

		chunkNo++;

	}
}

int SCTPParser::decode_sctp_chunk_data(const BYTE packet, int offset, int data_length, MPacket *msgObj, SCTP *sctpMsgObj, int chunkNo)
{
	//If the chunk length does not equate to a multiple of 4 bytes then the protocol implicitly pads the chunk with trailing zeros
	offset += sizeof(struct sctp_chunkhdr);  //Adjust SCTP data chunk header offset
	int data_header_length = sizeof(struct sctp_datahdr);
	if(PCons::P_SCTP && PCons::DEBUG) printf("  Reading SCTP chunk data header of length %d bytes\n", data_header_length);
	struct sctp_datahdr *cdataptr = (struct sctp_datahdr*)(packet+offset);
	if(PCons::P_SCTP && PCons::TRACE) printf("     TSN		: %u\n", ntohl(cdataptr->tsn));
	if(PCons::P_SCTP && PCons::DEBUG) printf("     Stream Identifier	: 0x%04x\n", ntohs(cdataptr->stream_id));
	if(PCons::P_SCTP && PCons::TRACE) printf("     Sequence Number	: %u\n", ntohs(cdataptr->sequence_no));

	sctpMsgObj->sctp_tsn = ntohl(cdataptr->tsn);
	sctpMsgObj->sctp_sequence_no = ntohs(cdataptr->sequence_no);
	sctpMsgObj->sctp_protocol = ntohl(cdataptr->protocol_identifier);

	if(ntohl(cdataptr->protocol_identifier) == IPPROTO_M3UA) {
		if(PCons::P_SCTP && PCons::TRACE) printf("     Protocol		: %u [M3UA]\n", sctpMsgObj->sctp_protocol);
		//Send only M3UA packet, (length - header)
		offset += sizeof(struct sctp_datahdr);
		mtp3->processPacket(packet + offset, msgObj, sctpMsgObj, chunkNo, data_length);
	}else if(ntohl(cdataptr->protocol_identifier) == IPPROTO_S1AP) {
		if(PCons::P_SCTP && PCons::TRACE) printf("     Protocol		: %u [S1AP]\n",sctpMsgObj->sctp_protocol);
		//Send only M3UA packet, (length - header)
		offset += sizeof(struct sctp_datahdr);
		if(PCons::P_SCTP && PCons::WARNING) printf("** [SCTP] Attention!!! Not processing IP Protocol data of type [%u]\n", sctpMsgObj->sctp_protocol);
	}else{
		if(PCons::P_SCTP && PCons::WARNING) printf("** [SCTP] Attention!!! Not processing IP Protocol data of type [%u]\n", sctpMsgObj->sctp_protocol);
	}
	return 0;
}

