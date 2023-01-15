/*
 * PacketRouter.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: Debashis
 */

#include "PacketRouter.h"

PacketRouter::PacketRouter(int intfid, int rid, int totrouters, int coreid) {

	this->_name = "PacketRouter";
	this->setLogLevel(Log::theLog().level());
	bwData  = new BWData(intfid, rid);
	ethParser = new EthernetParser(intfid, rid);
	gtpMsgBroker = new GTPMessageBroker(intfid, rid);
	sccpMsgBroker = new SCCPMessageBroker(intfid, rid);

	msgObj = new MPacket();
	rawPkt = new RawPkt();
	this->interfaceId = intfid;
	this->routerId = rid;
	this->routerTotal = totrouters;
	this->coreId = coreid;
}

PacketRouter::~PacketRouter() {
	delete (bwData);
	delete(ethParser);
	delete(gtpMsgBroker);
	delete(sccpMsgBroker);
	delete(msgObj);
	delete(rawPkt);
}

char * PacketRouter::ByteToString(const void* pv, int len)
{
	char localBuffer[len+1];
	const unsigned char* p = (const unsigned char*) pv;
	int i;
	for( i = 0; i < len; ++i ) {
		sprintf(localBuffer, "%08x", i);
	}

	return localBuffer;
}

bool PacketRouter::isRepositoryInitialized(){
	return repoInitStatus;
}

void PacketRouter::run()
{
	int lastProcessedIndex = -1;
	int curIndex = -1;
	struct tm *now_tm;
	int curDay = 0, prevDay = 0;

	printf("Packet Router [%d::%d] Instance Started, pinned to core :: %d\n",interfaceId, routerId, coreId);

	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	curDay = prevDay = now_tm->tm_mday;
	curMin = prevMin = now_tm->tm_min;

	lastProcessedIndex = curIndex = PKT_READ_TIME_INDEX(curTime.tv_sec);

	long sleepTime = 50000;
	long minCheckCnt = 10000 / (sleepTime / 1000);		//Check min change after every 10 sec
	long cnt = 0;

	repoInitStatus = true;

	while(IPGlobal::PKT_ROUTER_RUNNING_STATUS[interfaceId][routerId])
	{
		usleep(sleepTime);
		cnt++;

		gettimeofday(&curTime, NULL);
		curIndex = PKT_READ_TIME_INDEX(curTime.tv_sec);

		while(lastProcessedIndex != curIndex)
		{
			usleep(50000);		// 100ms
			processQueue(lastProcessedIndex);
			lastProcessedIndex = PKT_READ_NEXT_TIME_INDEX(lastProcessedIndex);
		}


		if(cnt >= minCheckCnt)
		{
			cnt = 0;
			now_tm = localtime(&curTime.tv_sec);
			curMin = now_tm->tm_min;
			curDay = now_tm->tm_mday;

			if(prevMin != curMin)		//Min changed
			{
				if(prevMin != curMin){
					bwData->setBWData(curMin);
					prevMin = curMin;
				}
			}

			if(prevDay != curDay)		//Day changed
			{
				prevDay = curDay;
				dayChanged = true;
			}

		}
	}
	printf("Packet Router [%d::%d] Shutdown Complete\n",interfaceId, routerId);
}

VOID PacketRouter::decodePacket()
{
	bool process = true;

	if(rawPkt->pkt != NULL)	{
		msgObj->reset();
	    msgObj->frInterfaceId = this->interfaceId;
	    msgObj->frRouterId = this->routerId;
	    msgObj->frTimeEpochSec = rawPkt->tv_sec;
	    msgObj->frTimeEpochNanoSec = (rawPkt->tv_sec * 1000000000) + rawPkt->tv_nsec;
	    msgObj->frSize = rawPkt->len;
	    msgObj->packetNo = rawPkt->pkt_no;

//		DEB --> Testing pcap writing
//		printf("pcap file writing begins...\n");
//
//		ProbeUtility::HEXDUMP(rawPkt->pkt,rawPkt->len);
//
////		struct pcapFileHeader {
////		    uint32_t magic_number;   /* magic number */
////		    uint16_t version_major;  /* major version number */
////		    uint16_t version_minor;  /* minor version number */
////		    int32_t  thiszone;       /* GMT to local correction */
////		    uint32_t sigfigs;        /* accuracy of timestamps */
////		    uint32_t snaplen;        /* max length of captured packets, in octets */
////		    uint32_t network;        /* data link type */
////		};
//		//		fileHeader.magic_number = 0xa1b2c3d4;
//		//		fileHeader.version_major = 2;
//		//		fileHeader.version_minor = 4;
//		//		fileHeader.thiszone = 0;
//		//		fileHeader.sigfigs = 0;
//		//		fileHeader.snaplen = 65535; //(2^16)
//		//		fileHeader.network = 1;     //Ethernet
//
//		FILE *ptr_myfile;
//		ptr_myfile=fopen("file.pcap", "wb");
//		if (!ptr_myfile)
//		{
//		    printf("Unable to open file!");
//		    exit(0);
//		}
//
//
////		ofstream fileout;
////		fileout.open("file.pcap", ios::binary);
//
//		struct pcap_file_header  fileHeader;
//		fileHeader.magic = 0xa1b2c3d4;
//		fileHeader.version_major = 2;
//		fileHeader.version_minor = 4;
//		fileHeader.thiszone = 0;
//		fileHeader.sigfigs = 0;
//		fileHeader.snaplen = 65535; //(2^16)
//		fileHeader.linktype  = 1;     //Ethernet
//
//		fwrite(&fileHeader, sizeof(fileHeader), 1, ptr_myfile);
////		fileout.write(reinterpret_cast<const char*>(&fileHeader), sizeof fileHeader);
//
////		struct pcap_pkthdr pkhdr;
////		pkhdr.len = (uint32_t)rawPkt->len;
////		pkhdr.caplen = (uint32_t)rawPkt->len;
////		gettimeofday(&pkhdr.ts, NULL);
//
//		struct pcapPkthdr {
//			uint32_t tv_sec;
//			uint32_t tv_usec;
//			uint32_t caplen;
//			uint32_t len;
//		 };
//		pcapPkthdr pkhdr;
//		pkhdr.len = pkhdr.caplen = (uint32_t)rawPkt->len;
//		gettimeofday(&curTime, NULL);
//		pkhdr.tv_sec = rawPkt->tv_sec;
//		//pkhdr.tv_sec = rawPkt->tv_sec;
////		pkhdr.ts = &curTime;//rawPkt->tv_sec; // Some unix timestamp
//
//		fwrite(&pkhdr, sizeof(pkhdr), 1, ptr_myfile);
////		fileout.write(reinterpret_cast<const char*>(&pkhdr), sizeof pkhdr);
//
//		fwrite(rawPkt->pkt, rawPkt->len, 1, ptr_myfile);
////		fileout.write(reinterpret_cast<const char*>(&rawPkt->pkt), rawPkt->len);
//
//
//	//	fileout <<  fileHeader.magic_number <<
//	//	            fileHeader.version_major <<
//	//	            fileHeader.version_minor <<
//	//	            fileHeader.thiszone <<
//	//	            fileHeader.sigfigs <<
//	//	            fileHeader.snaplen <<
//	//	            fileHeader.network;
//
//		fclose(ptr_myfile);
////		fileout.close();
//
//		printf("pcap file written for length %d...\n",rawPkt->len);
//
//
//		ifstream::pos_type size;
//		char * memblock;
//
//		ifstream file ("file.pcap", ios::in|ios::binary|ios::ate);
//		  if (file.is_open())
//		  {
//		    size = file.tellg();
//		    memblock = new char [size];
//		    file.seekg (0, ios::beg);
//		    file.read (memblock, size);
//		    file.close();
//
//		    ProbeUtility::HEXDUMP(memblock,size);
//		  }
//
//			printf("/home/engine/pcaps/BSNL_GN_PJ_1.pcap 2000 bytes\n");
//
//		  ifstream file1 ("/home/engine/pcaps/BSNL_GN_PJ_1.pcap", ios::in|ios::binary|ios::ate);
//		  		  if (file1.is_open())
//		  		  {
//		  		    size = 2000;//file.tellg();
//		  		    memblock = new char [size];
//		  		    file1.seekg (0, ios::beg);
//		  		    file1.read (memblock, size);
//		  		    file1.close();
//
//		  		    ProbeUtility::HEXDUMP(memblock,size);
//		  		  }
//
//		exit(0);


	    ethParser->parsePacket(rawPkt->pkt, msgObj);

	    bwData->updateBWData(curMin, msgObj);

	    if(msgObj->ipSourceAddr < IPGlobal::IPV4_MULTIPLIER_OCTET_1 ||
	    		msgObj->ipDestAddr < IPGlobal::IPV4_MULTIPLIER_OCTET_1 ||
				msgObj->ipVer != 4) {
	    	process = false;
	    }

	    countPacket(process);

	    int len = 0, i = 0;

	    if(process) {
			switch(msgObj->ipAppProtocol) {
					case PACKET_IPPROTO_GTPC:
					case PACKET_IPPROTO_GTPU:
							if(GContainer::config->GN_PROBE)
							{
								gtpMsgBroker->assignMessage(msgObj);
							}
							break;

					case PACKET_IPPROTO_SCTP:
							if(GContainer::config->IUPS_PROBE)
							{
								sccpMsgBroker->assignMessage(&(ethParser->sctp->sctpMap[msgObj->packetNo]), msgObj);

								len = ethParser->sctp->sctpMap[msgObj->packetNo].size();
								for(i = 0; i < len; i++)
									ethParser->sctp->sctpMap[msgObj->packetNo].erase(i);

								ethParser->sctp->sctpMap[msgObj->packetNo].clear();
								ethParser->sctp->sctpMap.erase(msgObj->packetNo);
							}
							break;

					default:
							break;
			} /* End of Switch */
	    }	/* End of If */
	}	/* End of If */
}


VOID PacketRouter::processQueue(int t_index)
{
	switch(interfaceId)
	{
		case 0:
			processQueue_i_0(t_index);
			break;

		case 1:
			processQueue_i_1(t_index);
			break;

		case 2:
			processQueue_i_2(t_index);
			break;

		case 3:
			processQueue_i_3(t_index);
			break;
	}
}

VOID PacketRouter::processQueue_i_0(int t_index)
{
	switch(routerId)
	{
		case 0:
			processQueue_i_0_r_0(t_index);
			break;

		case 1:
			if(routerTotal > 1){
				processQueue_i_0_r_1(t_index);
			}
			break;

//		case 2:
//			if(routerTotal > 2){
//				processQueue_i_0_r_2(t_index);
//			}
//			break;
//
//		case 3:
//			if(routerTotal > 3){
//				processQueue_i_0_r_3(t_index);
//			}
//			break;
	}
}

VOID PacketRouter::processQueue_i_1(int t_index)
{
	switch(routerId)
	{
		case 0:
			processQueue_i_1_r_0(t_index);
			break;

		case 1:
			if(routerTotal > 1){
				processQueue_i_1_r_1(t_index);
			}
			break;

//		case 2:
//			if(routerTotal > 2){
//				processQueue_i_1_r_2(t_index);
//			}
//			break;
//
//		case 3:
//			if(routerTotal > 3){
//				processQueue_i_1_r_3(t_index);
//			}
//			break;
	}
}

VOID PacketRouter::processQueue_i_2(int t_index)
{
	switch(routerId)
	{
		case 0:
			processQueue_i_2_r_0(t_index);
			break;

		case 1:
			if(routerTotal > 1){
				processQueue_i_2_r_1(t_index);
			}
			break;

//		case 2:
//			if(routerTotal > 2){
//				processQueue_i_2_r_2(t_index);
//			}
//			break;
//
//		case 3:
//			if(routerTotal > 3){
//				processQueue_i_2_r_3(t_index);
//			}
//			break;
	}
}

VOID PacketRouter::processQueue_i_3(int t_index)
{
	switch(routerId)
	{
		case 0:
			processQueue_i_3_r_0(t_index);
			break;

		case 1:
			if(routerTotal > 1){
				processQueue_i_3_r_1(t_index);
			}
			break;

//		case 2:
//			if(routerTotal > 2){
//				processQueue_i_3_r_2(t_index);
//			}
//			break;
//
//		case 3:
//			if(routerTotal > 3){
//				processQueue_i_3_r_3(t_index);
//			}
//			break;
	}
}


VOID PacketRouter::processQueueDecode(bool &pktRepository_busy, long &pktRepository_cnt, std::map<long, RawPkt*> &pktRepository)
{
	int recCnt = 0;
	pktRepository_busy = true;
	recCnt = pktRepository_cnt;
	if(recCnt > 0){
		for(int i = 0; i<recCnt; i++){
			rawPkt = pktRepository[i];
			decodePacket();
			pktRepository_cnt--;
		}
		pktRepository_cnt = 0;
	}
	pktRepository_busy = false;
}

VOID PacketRouter::processQueue_i_0_r_0(int t_index)
{

	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_0_busy, PKTStore::pktRepository_i_0_r_0_t_0_cnt, PKTStore::pktRepository_i_0_r_0_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_1_busy, PKTStore::pktRepository_i_0_r_0_t_1_cnt, PKTStore::pktRepository_i_0_r_0_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_2_busy, PKTStore::pktRepository_i_0_r_0_t_2_cnt, PKTStore::pktRepository_i_0_r_0_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_3_busy, PKTStore::pktRepository_i_0_r_0_t_3_cnt, PKTStore::pktRepository_i_0_r_0_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_4_busy, PKTStore::pktRepository_i_0_r_0_t_4_cnt, PKTStore::pktRepository_i_0_r_0_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_5_busy, PKTStore::pktRepository_i_0_r_0_t_5_cnt, PKTStore::pktRepository_i_0_r_0_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_6_busy, PKTStore::pktRepository_i_0_r_0_t_6_cnt, PKTStore::pktRepository_i_0_r_0_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_7_busy, PKTStore::pktRepository_i_0_r_0_t_7_cnt, PKTStore::pktRepository_i_0_r_0_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_8_busy, PKTStore::pktRepository_i_0_r_0_t_8_cnt, PKTStore::pktRepository_i_0_r_0_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_0_r_0_t_9_busy, PKTStore::pktRepository_i_0_r_0_t_9_cnt, PKTStore::pktRepository_i_0_r_0_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_0_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_0_busy, PKTStore::pktRepository_i_0_r_1_t_0_cnt, PKTStore::pktRepository_i_0_r_1_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_1_busy, PKTStore::pktRepository_i_0_r_1_t_1_cnt, PKTStore::pktRepository_i_0_r_1_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_2_busy, PKTStore::pktRepository_i_0_r_1_t_2_cnt, PKTStore::pktRepository_i_0_r_1_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_3_busy, PKTStore::pktRepository_i_0_r_1_t_3_cnt, PKTStore::pktRepository_i_0_r_1_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_4_busy, PKTStore::pktRepository_i_0_r_1_t_4_cnt, PKTStore::pktRepository_i_0_r_1_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_5_busy, PKTStore::pktRepository_i_0_r_1_t_5_cnt, PKTStore::pktRepository_i_0_r_1_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_6_busy, PKTStore::pktRepository_i_0_r_1_t_6_cnt, PKTStore::pktRepository_i_0_r_1_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_7_busy, PKTStore::pktRepository_i_0_r_1_t_7_cnt, PKTStore::pktRepository_i_0_r_1_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_8_busy, PKTStore::pktRepository_i_0_r_1_t_8_cnt, PKTStore::pktRepository_i_0_r_1_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_0_r_1_t_9_busy, PKTStore::pktRepository_i_0_r_1_t_9_cnt, PKTStore::pktRepository_i_0_r_1_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_1_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_0_busy, PKTStore::pktRepository_i_1_r_0_t_0_cnt, PKTStore::pktRepository_i_1_r_0_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_1_busy, PKTStore::pktRepository_i_1_r_0_t_1_cnt, PKTStore::pktRepository_i_1_r_0_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_2_busy, PKTStore::pktRepository_i_1_r_0_t_2_cnt, PKTStore::pktRepository_i_1_r_0_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_3_busy, PKTStore::pktRepository_i_1_r_0_t_3_cnt, PKTStore::pktRepository_i_1_r_0_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_4_busy, PKTStore::pktRepository_i_1_r_0_t_4_cnt, PKTStore::pktRepository_i_1_r_0_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_5_busy, PKTStore::pktRepository_i_1_r_0_t_5_cnt, PKTStore::pktRepository_i_1_r_0_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_6_busy, PKTStore::pktRepository_i_1_r_0_t_6_cnt, PKTStore::pktRepository_i_1_r_0_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_7_busy, PKTStore::pktRepository_i_1_r_0_t_7_cnt, PKTStore::pktRepository_i_1_r_0_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_8_busy, PKTStore::pktRepository_i_1_r_0_t_8_cnt, PKTStore::pktRepository_i_1_r_0_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_1_r_0_t_9_busy, PKTStore::pktRepository_i_1_r_0_t_9_cnt, PKTStore::pktRepository_i_1_r_0_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_1_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_0_busy, PKTStore::pktRepository_i_1_r_1_t_0_cnt, PKTStore::pktRepository_i_1_r_1_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_1_busy, PKTStore::pktRepository_i_1_r_1_t_1_cnt, PKTStore::pktRepository_i_1_r_1_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_2_busy, PKTStore::pktRepository_i_1_r_1_t_2_cnt, PKTStore::pktRepository_i_1_r_1_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_3_busy, PKTStore::pktRepository_i_1_r_1_t_3_cnt, PKTStore::pktRepository_i_1_r_1_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_4_busy, PKTStore::pktRepository_i_1_r_1_t_4_cnt, PKTStore::pktRepository_i_1_r_1_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_5_busy, PKTStore::pktRepository_i_1_r_1_t_5_cnt, PKTStore::pktRepository_i_1_r_1_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_6_busy, PKTStore::pktRepository_i_1_r_1_t_6_cnt, PKTStore::pktRepository_i_1_r_1_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_7_busy, PKTStore::pktRepository_i_1_r_1_t_7_cnt, PKTStore::pktRepository_i_1_r_1_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_8_busy, PKTStore::pktRepository_i_1_r_1_t_8_cnt, PKTStore::pktRepository_i_1_r_1_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_1_r_1_t_9_busy, PKTStore::pktRepository_i_1_r_1_t_9_cnt, PKTStore::pktRepository_i_1_r_1_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_2_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_0_busy, PKTStore::pktRepository_i_2_r_0_t_0_cnt, PKTStore::pktRepository_i_2_r_0_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_1_busy, PKTStore::pktRepository_i_2_r_0_t_1_cnt, PKTStore::pktRepository_i_2_r_0_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_2_busy, PKTStore::pktRepository_i_2_r_0_t_2_cnt, PKTStore::pktRepository_i_2_r_0_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_3_busy, PKTStore::pktRepository_i_2_r_0_t_3_cnt, PKTStore::pktRepository_i_2_r_0_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_4_busy, PKTStore::pktRepository_i_2_r_0_t_4_cnt, PKTStore::pktRepository_i_2_r_0_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_5_busy, PKTStore::pktRepository_i_2_r_0_t_5_cnt, PKTStore::pktRepository_i_2_r_0_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_6_busy, PKTStore::pktRepository_i_2_r_0_t_6_cnt, PKTStore::pktRepository_i_2_r_0_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_7_busy, PKTStore::pktRepository_i_2_r_0_t_7_cnt, PKTStore::pktRepository_i_2_r_0_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_8_busy, PKTStore::pktRepository_i_2_r_0_t_8_cnt, PKTStore::pktRepository_i_2_r_0_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_2_r_0_t_9_busy, PKTStore::pktRepository_i_2_r_0_t_9_cnt, PKTStore::pktRepository_i_2_r_0_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_2_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_0_busy, PKTStore::pktRepository_i_2_r_1_t_0_cnt, PKTStore::pktRepository_i_2_r_1_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_1_busy, PKTStore::pktRepository_i_2_r_1_t_1_cnt, PKTStore::pktRepository_i_2_r_1_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_2_busy, PKTStore::pktRepository_i_2_r_1_t_2_cnt, PKTStore::pktRepository_i_2_r_1_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_3_busy, PKTStore::pktRepository_i_2_r_1_t_3_cnt, PKTStore::pktRepository_i_2_r_1_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_4_busy, PKTStore::pktRepository_i_2_r_1_t_4_cnt, PKTStore::pktRepository_i_2_r_1_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_5_busy, PKTStore::pktRepository_i_2_r_1_t_5_cnt, PKTStore::pktRepository_i_2_r_1_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_6_busy, PKTStore::pktRepository_i_2_r_1_t_6_cnt, PKTStore::pktRepository_i_2_r_1_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_7_busy, PKTStore::pktRepository_i_2_r_1_t_7_cnt, PKTStore::pktRepository_i_2_r_1_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_8_busy, PKTStore::pktRepository_i_2_r_1_t_8_cnt, PKTStore::pktRepository_i_2_r_1_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_2_r_1_t_9_busy, PKTStore::pktRepository_i_2_r_1_t_9_cnt, PKTStore::pktRepository_i_2_r_1_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_3_r_0(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_0_busy, PKTStore::pktRepository_i_3_r_0_t_0_cnt, PKTStore::pktRepository_i_3_r_0_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_1_busy, PKTStore::pktRepository_i_3_r_0_t_1_cnt, PKTStore::pktRepository_i_3_r_0_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_2_busy, PKTStore::pktRepository_i_3_r_0_t_2_cnt, PKTStore::pktRepository_i_3_r_0_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_3_busy, PKTStore::pktRepository_i_3_r_0_t_3_cnt, PKTStore::pktRepository_i_3_r_0_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_4_busy, PKTStore::pktRepository_i_3_r_0_t_4_cnt, PKTStore::pktRepository_i_3_r_0_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_5_busy, PKTStore::pktRepository_i_3_r_0_t_5_cnt, PKTStore::pktRepository_i_3_r_0_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_6_busy, PKTStore::pktRepository_i_3_r_0_t_6_cnt, PKTStore::pktRepository_i_3_r_0_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_7_busy, PKTStore::pktRepository_i_3_r_0_t_7_cnt, PKTStore::pktRepository_i_3_r_0_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_8_busy, PKTStore::pktRepository_i_3_r_0_t_8_cnt, PKTStore::pktRepository_i_3_r_0_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_3_r_0_t_9_busy, PKTStore::pktRepository_i_3_r_0_t_9_cnt, PKTStore::pktRepository_i_3_r_0_t_9);
			break;
	}
}

VOID PacketRouter::processQueue_i_3_r_1(int t_index)
{
	switch(t_index)
	{
		case 0:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_0_busy, PKTStore::pktRepository_i_3_r_1_t_0_cnt, PKTStore::pktRepository_i_3_r_1_t_0);
			break;

		case 1:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_1_busy, PKTStore::pktRepository_i_3_r_1_t_1_cnt, PKTStore::pktRepository_i_3_r_1_t_1);
			break;

		case 2:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_2_busy, PKTStore::pktRepository_i_3_r_1_t_2_cnt, PKTStore::pktRepository_i_3_r_1_t_2);
			break;

		case 3:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_3_busy, PKTStore::pktRepository_i_3_r_1_t_3_cnt, PKTStore::pktRepository_i_3_r_1_t_3);
			break;

		case 4:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_4_busy, PKTStore::pktRepository_i_3_r_1_t_4_cnt, PKTStore::pktRepository_i_3_r_1_t_4);
			break;

		case 5:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_5_busy, PKTStore::pktRepository_i_3_r_1_t_5_cnt, PKTStore::pktRepository_i_3_r_1_t_5);
			break;

		case 6:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_6_busy, PKTStore::pktRepository_i_3_r_1_t_6_cnt, PKTStore::pktRepository_i_3_r_1_t_6);
			break;

		case 7:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_7_busy, PKTStore::pktRepository_i_3_r_1_t_7_cnt, PKTStore::pktRepository_i_3_r_1_t_7);
			break;

		case 8:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_8_busy, PKTStore::pktRepository_i_3_r_1_t_8_cnt, PKTStore::pktRepository_i_3_r_1_t_8);
			break;

		case 9:
			processQueueDecode(PKTStore::pktRepository_i_3_r_1_t_9_busy, PKTStore::pktRepository_i_3_r_1_t_9_cnt, PKTStore::pktRepository_i_3_r_1_t_9);
			break;
	}
}


VOID PacketRouter::countPacket(bool process)
{
	switch(interfaceId){
		case 0:
			{
				switch(routerId)
				{
					case 0:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_0_r_0 = 0;
							IPGlobal::ip_discarded_packets_i_0_r_0 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_0_r_0++;
						else
							IPGlobal::ip_discarded_packets_i_0_r_0++;
						break;
					case 1:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_0_r_1 = 0;
							IPGlobal::ip_discarded_packets_i_0_r_1 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_0_r_1++;
						else
							IPGlobal::ip_discarded_packets_i_0_r_1++;
						break;
					case 2:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_0_r_2 = 0;
							IPGlobal::ip_discarded_packets_i_0_r_2 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_0_r_2++;
						else
							IPGlobal::ip_discarded_packets_i_0_r_2++;
						break;
					case 3:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_0_r_3 = 0;
							IPGlobal::ip_discarded_packets_i_0_r_3 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_0_r_3++;
						else
							IPGlobal::ip_discarded_packets_i_0_r_3++;
						break;
				}
			}
			break;

		case 1:
			{
				switch(routerId)
				{
					case 0:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_1_r_0 = 0;
							IPGlobal::ip_discarded_packets_i_1_r_0 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_1_r_0++;
						else
							IPGlobal::ip_discarded_packets_i_1_r_0++;
						break;
					case 1:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_1_r_1 = 0;
							IPGlobal::ip_discarded_packets_i_1_r_1 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_1_r_1++;
						else
							IPGlobal::ip_discarded_packets_i_1_r_1++;
						break;
					case 2:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_1_r_2 = 0;
							IPGlobal::ip_discarded_packets_i_1_r_2 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_1_r_2++;
						else
							IPGlobal::ip_discarded_packets_i_1_r_2++;
						break;
					case 3:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_1_r_3 = 0;
							IPGlobal::ip_discarded_packets_i_1_r_3 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_1_r_3++;
						else
							IPGlobal::ip_discarded_packets_i_1_r_3++;
						break;
				}
			}
			break;

		case 2:
			{
				switch(routerId)
				{
					case 0:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_2_r_0 = 0;
							IPGlobal::ip_discarded_packets_i_2_r_0 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_2_r_0++;
						else
							IPGlobal::ip_discarded_packets_i_2_r_0++;
						break;
					case 1:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_2_r_1 = 0;
							IPGlobal::ip_discarded_packets_i_2_r_1 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_2_r_1++;
						else
							IPGlobal::ip_discarded_packets_i_2_r_1++;
						break;
					case 2:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_2_r_2 = 0;
							IPGlobal::ip_discarded_packets_i_2_r_2 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_2_r_2++;
						else
							IPGlobal::ip_discarded_packets_i_2_r_2++;
						break;
					case 3:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_2_r_3 = 0;
							IPGlobal::ip_discarded_packets_i_2_r_3 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_2_r_3++;
						else
							IPGlobal::ip_discarded_packets_i_2_r_3++;
						break;
				}
			}
			break;

		case 3:
			{
				switch(routerId)
				{
					case 0:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_3_r_0 = 0;
							IPGlobal::ip_discarded_packets_i_3_r_0 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_3_r_0++;
						else
							IPGlobal::ip_discarded_packets_i_3_r_0++;
						break;
					case 1:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_3_r_1 = 0;
							IPGlobal::ip_discarded_packets_i_3_r_1 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_3_r_1++;
						else
							IPGlobal::ip_discarded_packets_i_3_r_1++;
						break;
					case 2:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_3_r_2 = 0;
							IPGlobal::ip_discarded_packets_i_3_r_2 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_3_r_2++;
						else
							IPGlobal::ip_discarded_packets_i_3_r_2++;
						break;
					case 3:
						if(dayChanged)
						{
							dayChanged = false;
							IPGlobal::ip_processed_packets_i_3_r_3 = 0;
							IPGlobal::ip_discarded_packets_i_3_r_3 = 0;
						}
						if(process)
							IPGlobal::ip_processed_packets_i_3_r_3++;
						else
							IPGlobal::ip_discarded_packets_i_3_r_3++;
						break;
				}
			}
			break;
	}
}

VOID PacketRouter::writeTrace(RawPkt *rawPkt)
{
	string hexdump = std::string(ProbeUtility::getByteToHex((const void *)rawPkt->pkt,rawPkt->len));

	long epochSecNow = getCurrentEpochSeconds();

	int index = (((epochSecNow % 100) /10)  % IPGlobal::FLUSHER_TIMEINDEX) + 1;
	if(index >= IPGlobal::FLUSHER_TIMEINDEX) index = index - IPGlobal::FLUSHER_TIMEINDEX;

	switch(interfaceId)
	{
		case 0:
			writeTrace_i_0(index, hexdump);
			break;
		case 1:
			writeTrace_i_1(index, hexdump);
			break;
		case 2:
			writeTrace_i_2(index, hexdump);
			break;
		case 3:
			writeTrace_i_3(index, hexdump);
			break;
	}

}

VOID PacketRouter::writeTrace_i_0(int index, string hexdump)
{

	switch(routerId)
	{
		case 0:
			{
				switch(index)
				{
					case 0:
						if(TraceStore::tr_msg_i_0_r_0_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_0[TraceStore::tr_msg_i_0_r_0_t_0_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_0_cnt++;
						break;
					case 1:
						if(TraceStore::tr_msg_i_0_r_0_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_1[TraceStore::tr_msg_i_0_r_0_t_1_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_1_cnt++;
						break;
					case 2:
						if(TraceStore::tr_msg_i_0_r_0_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_2[TraceStore::tr_msg_i_0_r_0_t_2_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_2_cnt++;
						break;
					case 3:
						if(TraceStore::tr_msg_i_0_r_0_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_3[TraceStore::tr_msg_i_0_r_0_t_3_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_3_cnt++;
						break;
					case 4:
						if(TraceStore::tr_msg_i_0_r_0_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_4[TraceStore::tr_msg_i_0_r_0_t_4_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_4_cnt++;
						break;
					case 5:
						if(TraceStore::tr_msg_i_0_r_0_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_5[TraceStore::tr_msg_i_0_r_0_t_5_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_5_cnt++;
						break;
					case 6:
						if(TraceStore::tr_msg_i_0_r_0_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_6[TraceStore::tr_msg_i_0_r_0_t_6_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_6_cnt++;
						break;
					case 7:
						if(TraceStore::tr_msg_i_0_r_0_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_7[TraceStore::tr_msg_i_0_r_0_t_7_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_7_cnt++;
						break;
					case 8:
						if(TraceStore::tr_msg_i_0_r_0_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_0[TraceStore::tr_msg_i_0_r_0_t_8_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_8_cnt++;
						break;
					case 9:
						if(TraceStore::tr_msg_i_0_r_0_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_0_r_0_t_9[TraceStore::tr_msg_i_0_r_0_t_9_cnt] = hexdump;
						TraceStore::tr_msg_i_0_r_0_t_9_cnt++;
						break;
				}
				break;
			}
			break;
		case 1:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_0_r_1_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_0[TraceStore::tr_msg_i_0_r_1_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_0_r_1_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_1[TraceStore::tr_msg_i_0_r_1_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_0_r_1_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_2[TraceStore::tr_msg_i_0_r_1_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_0_r_1_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_3[TraceStore::tr_msg_i_0_r_1_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_0_r_1_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_4[TraceStore::tr_msg_i_0_r_1_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_0_r_1_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_5[TraceStore::tr_msg_i_0_r_1_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_0_r_1_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_6[TraceStore::tr_msg_i_0_r_1_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_0_r_1_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_7[TraceStore::tr_msg_i_0_r_1_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_0_r_1_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_0[TraceStore::tr_msg_i_0_r_1_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_0_r_1_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_1_t_9[TraceStore::tr_msg_i_0_r_1_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_1_t_9_cnt++;
					break;							}
				break;
			}
			break;
		case 2:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_0_r_2_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_0[TraceStore::tr_msg_i_0_r_2_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_0_r_2_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_1[TraceStore::tr_msg_i_0_r_2_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_0_r_2_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_2[TraceStore::tr_msg_i_0_r_2_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_0_r_2_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_3[TraceStore::tr_msg_i_0_r_2_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_0_r_2_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_4[TraceStore::tr_msg_i_0_r_2_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_0_r_2_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_5[TraceStore::tr_msg_i_0_r_2_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_0_r_2_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_6[TraceStore::tr_msg_i_0_r_2_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_0_r_2_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_7[TraceStore::tr_msg_i_0_r_2_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_0_r_2_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_0[TraceStore::tr_msg_i_0_r_2_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_0_r_2_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_2_t_9[TraceStore::tr_msg_i_0_r_2_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_2_t_9_cnt++;
					break;
				}
				break;
			}
			break;
		case 3:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_0_r_3_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_0[TraceStore::tr_msg_i_0_r_3_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_0_r_3_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_1[TraceStore::tr_msg_i_0_r_3_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_0_r_3_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_2[TraceStore::tr_msg_i_0_r_3_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_0_r_3_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_3[TraceStore::tr_msg_i_0_r_3_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_0_r_3_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_4[TraceStore::tr_msg_i_0_r_3_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_0_r_3_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_5[TraceStore::tr_msg_i_0_r_3_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_0_r_3_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_6[TraceStore::tr_msg_i_0_r_3_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_0_r_3_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_7[TraceStore::tr_msg_i_0_r_3_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_0_r_3_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_0[TraceStore::tr_msg_i_0_r_3_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_0_r_3_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_0_r_3_t_9[TraceStore::tr_msg_i_0_r_3_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_0_r_3_t_9_cnt++;
					break;
				}
				break;
			}
			break;
	}
}

VOID PacketRouter::writeTrace_i_1(int index, string hexdump)
{

	switch(routerId)
	{
		case 0:
			{
				switch(index)
				{
					case 0:
						if(TraceStore::tr_msg_i_1_r_0_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_0[TraceStore::tr_msg_i_1_r_0_t_0_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_0_cnt++;
						break;
					case 1:
						if(TraceStore::tr_msg_i_1_r_0_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_1[TraceStore::tr_msg_i_1_r_0_t_1_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_1_cnt++;
						break;
					case 2:
						if(TraceStore::tr_msg_i_1_r_0_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_2[TraceStore::tr_msg_i_1_r_0_t_2_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_2_cnt++;
						break;
					case 3:
						if(TraceStore::tr_msg_i_1_r_0_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_3[TraceStore::tr_msg_i_1_r_0_t_3_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_3_cnt++;
						break;
					case 4:
						if(TraceStore::tr_msg_i_1_r_0_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_4[TraceStore::tr_msg_i_1_r_0_t_4_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_4_cnt++;
						break;
					case 5:
						if(TraceStore::tr_msg_i_1_r_0_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_5[TraceStore::tr_msg_i_1_r_0_t_5_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_5_cnt++;
						break;
					case 6:
						if(TraceStore::tr_msg_i_1_r_0_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_6[TraceStore::tr_msg_i_1_r_0_t_6_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_6_cnt++;
						break;
					case 7:
						if(TraceStore::tr_msg_i_1_r_0_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_7[TraceStore::tr_msg_i_1_r_0_t_7_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_7_cnt++;
						break;
					case 8:
						if(TraceStore::tr_msg_i_1_r_0_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_0[TraceStore::tr_msg_i_1_r_0_t_8_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_8_cnt++;
						break;
					case 9:
						if(TraceStore::tr_msg_i_1_r_0_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_1_r_0_t_9[TraceStore::tr_msg_i_1_r_0_t_9_cnt] = hexdump;
						TraceStore::tr_msg_i_1_r_0_t_9_cnt++;
						break;
				}
				break;
			}
			break;
		case 1:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_1_r_1_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_0[TraceStore::tr_msg_i_1_r_1_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_1_r_1_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_1[TraceStore::tr_msg_i_1_r_1_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_1_r_1_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_2[TraceStore::tr_msg_i_1_r_1_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_1_r_1_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_3[TraceStore::tr_msg_i_1_r_1_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_1_r_1_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_4[TraceStore::tr_msg_i_1_r_1_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_1_r_1_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_5[TraceStore::tr_msg_i_1_r_1_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_1_r_1_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_6[TraceStore::tr_msg_i_1_r_1_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_1_r_1_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_7[TraceStore::tr_msg_i_1_r_1_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_1_r_1_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_0[TraceStore::tr_msg_i_1_r_1_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_1_r_1_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_1_t_9[TraceStore::tr_msg_i_1_r_1_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_1_t_9_cnt++;
					break;							}
				break;
			}
			break;
		case 2:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_1_r_2_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_0[TraceStore::tr_msg_i_1_r_2_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_1_r_2_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_1[TraceStore::tr_msg_i_1_r_2_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_1_r_2_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_2[TraceStore::tr_msg_i_1_r_2_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_1_r_2_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_3[TraceStore::tr_msg_i_1_r_2_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_1_r_2_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_4[TraceStore::tr_msg_i_1_r_2_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_1_r_2_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_5[TraceStore::tr_msg_i_1_r_2_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_1_r_2_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_6[TraceStore::tr_msg_i_1_r_2_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_1_r_2_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_7[TraceStore::tr_msg_i_1_r_2_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_1_r_2_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_0[TraceStore::tr_msg_i_1_r_2_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_1_r_2_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_2_t_9[TraceStore::tr_msg_i_1_r_2_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_2_t_9_cnt++;
					break;
				}
				break;
			}
			break;
		case 3:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_1_r_3_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_0[TraceStore::tr_msg_i_1_r_3_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_1_r_3_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_1[TraceStore::tr_msg_i_1_r_3_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_1_r_3_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_2[TraceStore::tr_msg_i_1_r_3_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_1_r_3_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_3[TraceStore::tr_msg_i_1_r_3_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_1_r_3_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_4[TraceStore::tr_msg_i_1_r_3_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_1_r_3_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_5[TraceStore::tr_msg_i_1_r_3_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_1_r_3_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_6[TraceStore::tr_msg_i_1_r_3_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_1_r_3_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_7[TraceStore::tr_msg_i_1_r_3_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_1_r_3_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_0[TraceStore::tr_msg_i_1_r_3_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_1_r_3_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_1_r_3_t_9[TraceStore::tr_msg_i_1_r_3_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_1_r_3_t_9_cnt++;
					break;
				}
				break;
			}
			break;
	}
}


VOID PacketRouter::writeTrace_i_2(int index, string hexdump)
{

	switch(routerId)
	{
		case 0:
			{
				switch(index)
				{
					case 0:
						if(TraceStore::tr_msg_i_2_r_0_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_0[TraceStore::tr_msg_i_2_r_0_t_0_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_0_cnt++;
						break;
					case 1:
						if(TraceStore::tr_msg_i_2_r_0_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_1[TraceStore::tr_msg_i_2_r_0_t_1_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_1_cnt++;
						break;
					case 2:
						if(TraceStore::tr_msg_i_2_r_0_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_2[TraceStore::tr_msg_i_2_r_0_t_2_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_2_cnt++;
						break;
					case 3:
						if(TraceStore::tr_msg_i_2_r_0_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_3[TraceStore::tr_msg_i_2_r_0_t_3_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_3_cnt++;
						break;
					case 4:
						if(TraceStore::tr_msg_i_2_r_0_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_4[TraceStore::tr_msg_i_2_r_0_t_4_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_4_cnt++;
						break;
					case 5:
						if(TraceStore::tr_msg_i_2_r_0_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_5[TraceStore::tr_msg_i_2_r_0_t_5_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_5_cnt++;
						break;
					case 6:
						if(TraceStore::tr_msg_i_2_r_0_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_6[TraceStore::tr_msg_i_2_r_0_t_6_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_6_cnt++;
						break;
					case 7:
						if(TraceStore::tr_msg_i_2_r_0_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_7[TraceStore::tr_msg_i_2_r_0_t_7_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_7_cnt++;
						break;
					case 8:
						if(TraceStore::tr_msg_i_2_r_0_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_0[TraceStore::tr_msg_i_2_r_0_t_8_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_8_cnt++;
						break;
					case 9:
						if(TraceStore::tr_msg_i_2_r_0_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_2_r_0_t_9[TraceStore::tr_msg_i_2_r_0_t_9_cnt] = hexdump;
						TraceStore::tr_msg_i_2_r_0_t_9_cnt++;
						break;
				}
				break;
			}
			break;
		case 1:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_2_r_1_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_0[TraceStore::tr_msg_i_2_r_1_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_2_r_1_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_1[TraceStore::tr_msg_i_2_r_1_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_2_r_1_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_2[TraceStore::tr_msg_i_2_r_1_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_2_r_1_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_3[TraceStore::tr_msg_i_2_r_1_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_2_r_1_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_4[TraceStore::tr_msg_i_2_r_1_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_2_r_1_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_5[TraceStore::tr_msg_i_2_r_1_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_2_r_1_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_6[TraceStore::tr_msg_i_2_r_1_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_2_r_1_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_7[TraceStore::tr_msg_i_2_r_1_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_2_r_1_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_0[TraceStore::tr_msg_i_2_r_1_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_2_r_1_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_1_t_9[TraceStore::tr_msg_i_2_r_1_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_1_t_9_cnt++;
					break;							}
				break;
			}
			break;
		case 2:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_2_r_2_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_0[TraceStore::tr_msg_i_2_r_2_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_2_r_2_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_1[TraceStore::tr_msg_i_2_r_2_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_2_r_2_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_2[TraceStore::tr_msg_i_2_r_2_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_2_r_2_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_3[TraceStore::tr_msg_i_2_r_2_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_2_r_2_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_4[TraceStore::tr_msg_i_2_r_2_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_2_r_2_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_5[TraceStore::tr_msg_i_2_r_2_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_2_r_2_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_6[TraceStore::tr_msg_i_2_r_2_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_2_r_2_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_7[TraceStore::tr_msg_i_2_r_2_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_2_r_2_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_0[TraceStore::tr_msg_i_2_r_2_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_2_r_2_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_2_t_9[TraceStore::tr_msg_i_2_r_2_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_2_t_9_cnt++;
					break;
				}
				break;
			}
			break;
		case 3:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_2_r_3_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_0[TraceStore::tr_msg_i_2_r_3_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_2_r_3_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_1[TraceStore::tr_msg_i_2_r_3_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_2_r_3_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_2[TraceStore::tr_msg_i_2_r_3_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_2_r_3_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_3[TraceStore::tr_msg_i_2_r_3_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_2_r_3_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_4[TraceStore::tr_msg_i_2_r_3_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_2_r_3_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_5[TraceStore::tr_msg_i_2_r_3_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_2_r_3_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_6[TraceStore::tr_msg_i_2_r_3_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_2_r_3_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_7[TraceStore::tr_msg_i_2_r_3_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_2_r_3_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_0[TraceStore::tr_msg_i_2_r_3_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_2_r_3_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_2_r_3_t_9[TraceStore::tr_msg_i_2_r_3_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_2_r_3_t_9_cnt++;
					break;
				}
				break;
			}
			break;
	}
}


VOID PacketRouter::writeTrace_i_3(int index, string hexdump)
{

	switch(routerId)
	{
		case 0:
			{
				switch(index)
				{
					case 0:
						if(TraceStore::tr_msg_i_3_r_0_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_0[TraceStore::tr_msg_i_3_r_0_t_0_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_0_cnt++;
						break;
					case 1:
						if(TraceStore::tr_msg_i_3_r_0_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_1[TraceStore::tr_msg_i_3_r_0_t_1_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_1_cnt++;
						break;
					case 2:
						if(TraceStore::tr_msg_i_3_r_0_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_2[TraceStore::tr_msg_i_3_r_0_t_2_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_2_cnt++;
						break;
					case 3:
						if(TraceStore::tr_msg_i_3_r_0_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_3[TraceStore::tr_msg_i_3_r_0_t_3_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_3_cnt++;
						break;
					case 4:
						if(TraceStore::tr_msg_i_3_r_0_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_4[TraceStore::tr_msg_i_3_r_0_t_4_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_4_cnt++;
						break;
					case 5:
						if(TraceStore::tr_msg_i_3_r_0_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_5[TraceStore::tr_msg_i_3_r_0_t_5_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_5_cnt++;
						break;
					case 6:
						if(TraceStore::tr_msg_i_3_r_0_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_6[TraceStore::tr_msg_i_3_r_0_t_6_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_6_cnt++;
						break;
					case 7:
						if(TraceStore::tr_msg_i_3_r_0_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_7[TraceStore::tr_msg_i_3_r_0_t_7_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_7_cnt++;
						break;
					case 8:
						if(TraceStore::tr_msg_i_3_r_0_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_0[TraceStore::tr_msg_i_3_r_0_t_8_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_8_cnt++;
						break;
					case 9:
						if(TraceStore::tr_msg_i_3_r_0_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
						TraceStore::tr_msg_i_3_r_0_t_9[TraceStore::tr_msg_i_3_r_0_t_9_cnt] = hexdump;
						TraceStore::tr_msg_i_3_r_0_t_9_cnt++;
						break;
				}
				break;
			}
			break;
		case 1:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_3_r_1_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_0[TraceStore::tr_msg_i_3_r_1_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_3_r_1_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_1[TraceStore::tr_msg_i_3_r_1_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_3_r_1_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_2[TraceStore::tr_msg_i_3_r_1_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_3_r_1_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_3[TraceStore::tr_msg_i_3_r_1_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_3_r_1_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_4[TraceStore::tr_msg_i_3_r_1_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_3_r_1_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_5[TraceStore::tr_msg_i_3_r_1_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_3_r_1_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_6[TraceStore::tr_msg_i_3_r_1_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_3_r_1_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_7[TraceStore::tr_msg_i_3_r_1_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_3_r_1_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_0[TraceStore::tr_msg_i_3_r_1_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_3_r_1_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_1_t_9[TraceStore::tr_msg_i_3_r_1_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_1_t_9_cnt++;
					break;							}
				break;
			}
			break;
		case 2:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_3_r_2_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_0[TraceStore::tr_msg_i_3_r_2_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_3_r_2_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_1[TraceStore::tr_msg_i_3_r_2_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_3_r_2_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_2[TraceStore::tr_msg_i_3_r_2_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_3_r_2_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_3[TraceStore::tr_msg_i_3_r_2_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_3_r_2_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_4[TraceStore::tr_msg_i_3_r_2_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_3_r_2_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_5[TraceStore::tr_msg_i_3_r_2_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_3_r_2_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_6[TraceStore::tr_msg_i_3_r_2_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_3_r_2_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_7[TraceStore::tr_msg_i_3_r_2_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_3_r_2_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_0[TraceStore::tr_msg_i_3_r_2_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_3_r_2_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_2_t_9[TraceStore::tr_msg_i_3_r_2_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_2_t_9_cnt++;
					break;
				}
				break;
			}
			break;
		case 3:
			{
				switch(index)
				{
				case 0:
					if(TraceStore::tr_msg_i_3_r_3_t_0_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_0[TraceStore::tr_msg_i_3_r_3_t_0_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_0_cnt++;
					break;
				case 1:
					if(TraceStore::tr_msg_i_3_r_3_t_1_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_1[TraceStore::tr_msg_i_3_r_3_t_1_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_1_cnt++;
					break;
				case 2:
					if(TraceStore::tr_msg_i_3_r_3_t_2_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_2[TraceStore::tr_msg_i_3_r_3_t_2_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_2_cnt++;
					break;
				case 3:
					if(TraceStore::tr_msg_i_3_r_3_t_3_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_3[TraceStore::tr_msg_i_3_r_3_t_3_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_3_cnt++;
					break;
				case 4:
					if(TraceStore::tr_msg_i_3_r_3_t_4_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_4[TraceStore::tr_msg_i_3_r_3_t_4_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_4_cnt++;
					break;
				case 5:
					if(TraceStore::tr_msg_i_3_r_3_t_5_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_5[TraceStore::tr_msg_i_3_r_3_t_5_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_5_cnt++;
					break;
				case 6:
					if(TraceStore::tr_msg_i_3_r_3_t_6_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_6[TraceStore::tr_msg_i_3_r_3_t_6_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_6_cnt++;
					break;
				case 7:
					if(TraceStore::tr_msg_i_3_r_3_t_7_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_7[TraceStore::tr_msg_i_3_r_3_t_7_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_7_cnt++;
					break;
				case 8:
					if(TraceStore::tr_msg_i_3_r_3_t_8_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_0[TraceStore::tr_msg_i_3_r_3_t_8_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_8_cnt++;
					break;
				case 9:
					if(TraceStore::tr_msg_i_3_r_3_t_9_cnt >= TRACE_QUEUE_LIMIT) break;
					TraceStore::tr_msg_i_3_r_3_t_9[TraceStore::tr_msg_i_3_r_3_t_9_cnt] = hexdump;
					TraceStore::tr_msg_i_3_r_3_t_9_cnt++;
					break;
				}
				break;
			}
			break;
	}
}
