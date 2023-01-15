/*
 * PUDP.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: Debashis
 */


#include <netinet/udp.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <algorithm>

#include "UDPParser.h"

#define RAW_UDP false
#define RAW_DNS false
bool P_UDP_PACKETS = false;

#define randomQueue	rand() % 2 + 0

using namespace std;
using namespace GContainer;

UDPParser::UDPParser()
{
	utility 		= new ProbeUtility();
	dnsData 		= new DnsData();

	this->_name = "UDP";
	this->setLogLevel(Log::theLog().level());
}

UDPParser::~UDPParser()
{
	delete (utility);
	delete (dnsData);
}

VOID UDPParser::lockDnsMap()
{
	    pthread_mutex_lock(&mapDnsLock::lockCount);
	    while (mapDnsLock::count == 0)
	        pthread_cond_wait(&mapDnsLock::nonzero, &mapDnsLock::lockCount);
	    mapDnsLock::count = mapDnsLock::count - 1;
	    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID UDPParser::unLockDnsMap()
{
    pthread_mutex_lock(&mapDnsLock::lockCount);
    if (mapDnsLock::count == 0)
        pthread_cond_signal(&mapDnsLock::nonzero);
    mapDnsLock::count = mapDnsLock::count + 1;
    pthread_mutex_unlock(&mapDnsLock::lockCount);
}

VOID UDPParser::parsePacket(const BYTE packet, MPacket *msgObj)
{ 
	std::string URL, appProtocol;
	uint16_t ret = 0;
	ULONG sessionKey = 0;

	struct udphdr *udpHeader = (struct udphdr *)(packet);

 	msgObj->protoTLen = ntohs((unsigned short int)udpHeader->len);
	msgObj->protoSourcePort = ntohs((unsigned short int)udpHeader->source);
	msgObj->protoDestPort = ntohs((unsigned short int)udpHeader->dest);

	msgObj->protoPayload = msgObj->ipTLen - (msgObj->ipHLen + UDP_HDR_LEN);

    if((msgObj->protoSourcePort == DNS_PORT) || (msgObj->protoDestPort == DNS_PORT))
    {
    	lockDnsMap();
   		parsePacketDNS(packet + UDP_HDR_LEN, msgObj); // Total Length of UDP message (8)
    	unLockDnsMap();
    }

    /*   Check the Application Protocol */
	if(msgObj->protoSourcePort == STUN_PORT)
	{
//		decodeStunMsg(packet + UDP_HDR_LEN, msgObj);
	}


//	else if((msgObj->protoSourcePort > 550  && msgObj->protoDestPort > 550))
//    {
//    	msgObj->protoAppProto.assign("UNASSIGNED");
//	}
//    else if((msgObj->udpSourcePort > 550  && msgObj->udpDestPort <= 550))
//    {
//    	msgObj->udpAppProto = tcpPort::TCPPort[msgObj->udpDestPort];
//	}
//    else if((msgObj->udpSourcePort <= 550  && msgObj->udpDestPort > 550))
//    {
//		msgObj->udpAppProto = tcpPort::TCPPort[msgObj->udpSourcePort];
//    }
//    else
//    {
//    	msgObj->udpAppProto.assign("UNASSIGNED");
//	}

    return;
}

VOID UDPParser::parsePacketDNS(const BYTE packet, MPacket *msgObj)
{
    uint32_t pos = 0, id_pos = 0, retPos = 0;
	uint8_t authoritative, truncatedFlag;

	if ( msgObj->frSize - msgObj->protoTLen < 12)
	{ return; }

    msgObj->dnsTLen 			= msgObj->protoTLen - UDP_HDR_LEN;
    msgObj->dnsTransactionId 	= (packet[pos] << 8) + packet[pos+1];		// Transaction ID
    msgObj->dnsQRFlag 			= packet[pos+2] >> 7;					    // Query Response -> Question=0 and Answer=1

    if(msgObj->dnsQRFlag < QUERY || msgObj->dnsQRFlag > RESPONSE)
    	return;

    authoritative = (packet[pos+2] & 0x04) >> 2;
    truncatedFlag = (packet[pos+2] & 0x02) >> 1;			// Truncated Message Flag
    msgObj->dnsResponseCode = packet[pos + 3] & 0x0f;		// rcode will be there in case of Response (Answer = 1)

    //0 - No Error, 1- Format Error
	if (msgObj->dnsResponseCode > 5)
	{
		qdcount = ancount = nscount = arcount = 0;
		return;
	}

    // Counts for each of the record types.
    qdcount = (packet[pos+4] << 8) + packet[pos+5];			// Query Count
    ancount = (packet[pos+6] << 8) + packet[pos+7];			// Answer Count
    nscount = (packet[pos+8] << 8) + packet[pos+9];			// Authority count
    arcount = (packet[pos+10] << 8) + packet[pos+11];		// Additional Information Count

    if(msgObj->dnsQRFlag == RESPONSE || msgObj->dnsQRFlag == QUERY)
    {
                if(nscount > 0) {
                    msgObj->dnsTLen 			= 0;
                    msgObj->dnsTransactionId 	= 0;		// Transaction ID
                    msgObj->dnsQRFlag 			= 0;		// Query Response -> Question=0 and Answer=1
                	return;
                }

                if(arcount > 0) {
                    msgObj->dnsTLen 			= 0;
                    msgObj->dnsTransactionId 	= 0;		// Transaction ID
                    msgObj->dnsQRFlag 			= 0;		// Query Response -> Question=0 and Answer=1
                	return;
                }
    }

  //  printf("qdcount::%d| ancount::%d| nscount::%d| arcount::%d\n", qdcount, ancount, nscount, arcount);

    switch(msgObj->dnsQRFlag)
    {
    	case QUERY:
					if(qdcount == 1)
					{ parsePacketDNSQueries(pos + DNS_HDR_LEN, id_pos, msgObj, (const unsigned char *)packet, &retPos); }

					break;

    	case RESPONSE:
					if(qdcount == 1 && ancount >= 1)
						if(parsePacketDNSQueries((pos + DNS_HDR_LEN), id_pos, msgObj, (const unsigned char *)packet, &retPos))
						{ parsePacketDNSAnswers(retPos, msgObj, packet); }

					break;

    	default:				// Default
    		 	 	 msgObj->dnsTLen 			= 0;
    		 	 	 msgObj->dnsTransactionId 	= 0;		// Transaction ID
    		 	 	 msgObj->dnsQRFlag 			= 0;		// Query Response -> Question=0 and Answer=1
    		 	 	 break;
    }
}

BOOL UDPParser::parsePacketDNSQueries(uint32_t pos, uint32_t id_pos, MPacket *msgObj, const UCHAR *packet, uint32_t *retPos)
{
    uint16_t i = 0, type = 0, cls = 0;
    uint32_t len = 0;
    std::string url;

    url = read_rr_name(packet, &pos, id_pos, msgObj->dnsTLen);
    std::replace(url.begin(), url.end(), ',', '.');

    if (url.compare("NULL") == 0)
    {
    	return false;
    }

//    int urlLen = url.length();
//    int stPos = 0;
//    if(urlLen > DNS_LEN - 1){
//    	stPos = urlLen - DNS_LEN - 1;
//    	url.substr(stPos, DNS_LEN - 1);
//    }
//    strcpy(msgObj->dnsName, url.c_str());

    strncpy((char *)msgObj->dnsName, (const char *)url.c_str(), 49);

    *retPos = pos + 4;
    return true;
}

VOID UDPParser::parsePacketDNSAnswers(uint32_t pos, MPacket *msgObj, const BYTE packet)
{
	uint16_t dataLen, ttl;

	UCHAR IP4Addr[25], IP6Addr[50];
	std::string url = "";
	std::string ipAddress = "";
	std::string addressList = "";
	std::string userIP_resolveIP_key = "";
	
	dataLen = ttl = 0;
	IP4Addr[0] = IP6Addr[0] = 0;
//	int maxLen = 409;
	try
	{
		for(uint16_t ansCounter = 0; ansCounter < ancount; ansCounter++)
		{
			pos = pos + 2;												// Reference Question Name (2 Bytes)

			for (uint16_t i=0; i<4; i++)								// TTL 4 Bytes
				ttl = (ttl << 8) + packet[pos+4+i];

			dataLen = (packet[pos+8] << 8) + packet[pos+9];				// Data Length 2 Bytes

			if(dataLen == IP4_LEN)
			{
				uint32_t longResolvedIp = 0;

				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[pos + 10]);
				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[pos + 11]);
				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[pos + 12]);
				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[pos + 13]);

				userIP_resolveIP_key = getDNSKey(msgObj->ipDestAddr, longResolvedIp);


				if(strlen(msgObj->dnsName) > 0) {
//					printf("DNS:: %s\n", msgObj->dnsName);
					dnsData->updateDns(userIP_resolveIP_key, msgObj->ipDestAddr, longResolvedIp, msgObj->dnsName, msgObj->frTimeEpochSec);
				}

				addressList = "";
				addressList.assign(std::to_string(longResolvedIp));

//				if(addressList.length() <= 1)
//				{
//					addressList.append(std::to_string(longResolvedIp));
//				}

//				if(addressList.length() < maxLen) {
//					addressList.append(std::to_string(longResolvedIp));
//					addressList.append("#");
//				}
//				else
//				{
//					printf("********* Len Excceeeeeeeeeeeeeed\n");
//				}

				// Increment the pos to next Answer location
				// Name(2 Bytes) + Type(2 Bytes) + Class(2 Bytes) + TTL (4 Bytes) + Data Length( 2 Bytes) + Address( 4 Bytes) = 16 Bytes
				pos = pos + 14; // 2 Bytes already increased

				IP4Addr[0] = 0;
			}
			else if(dataLen == IP6_LEN)
			{
				utility->ExtractIP6Address((const unsigned char *)packet, IP6Addr, pos + 10);

				ipAddress.assign((char *)IP6Addr);

				addressList = "";
				addressList.assign(ipAddress);

//				if(addressList.length() <= 1)
//				{
//					addressList.append(ipAddress);
//				}

//				if(addressList.length() < ((IP_ADDR_LEN + 1) * (DNS_MAX_IPS-1))){
//					addressList.append(ipAddress);
//					addressList.append("#");
//				}
				IP6Addr[0] = 0;
			}
			else
			{
                if(pos == 0)
                	addressList.assign("Bad Address");
                else
                {
                	pos = pos + 10; // Name 2 Bytes, Type 2 Bytes, Class 2 Bytes, TTL, 4 Bytes
                	url = read_rr_name((const unsigned char *)packet, &pos, 0, msgObj->dnsTLen);
                }
			}
		}

		if(addressList.length() == 0)
			addressList.assign("Bad Address");

		IP4Addr[0] = IP6Addr[0] = 0;
		ipAddress.clear();

//		if(addressList.length() >= maxLen){
//			addressList.substr(0, 409);
//		}

		msgObj->dnsIpAddress[0] = 0;
//		strncpy(msgObj->dnsIpAddress, addressList.c_str(), addressList.length());
		if(addressList.length() < IP_ADDR_LEN)
			strcpy(msgObj->dnsIpAddress, addressList.c_str());

//		printf("DNS::URL::%s| IP::%s| Len::%d\n", url.c_str(), msgObj->dnsIpAddress, addressList.length());

	}
	catch(const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '" << e.what() << "'\n";
	}
}

string UDPParser::read_rr_name(const uint8_t * packet, uint32_t * packet_p, uint32_t id_pos, uint32_t len)
{
    uint32_t i, next, pos=*packet_p;
    uint32_t end_pos = 0;
    uint32_t name_len=0;
    uint32_t steps = 0;
    //char *name;

    // Scan through the name, one character at a time. We need to look at
    // each character to look for values we can't print in order to allocate
    // extra space for escaping them.  'next' is the next position to look
    // for a compression jump or name end.
    // It's possible that there are endless loops in the name. Our protection
    // against this is to make sure we don't read more bytes in this process
    // than twice the length of the data.  Names that take that many steps to
    // read in should be impossible.
    next = pos;
    while (pos < len && !(next == pos && packet[pos] == 0) && steps < len*2) {
        uint8_t c = packet[pos];
        steps++;
        if (next == pos) {
            // Handle message compression.
            // If the length byte starts with the bits 11, then the rest of
            // this byte and the next form the offset from the dns proto start
            // to the start of the remainder of the name.
            if ((c & 0xc0) == 0xc0) {
                if (pos + 1 >= len){
                	return "NULL";
                }
                if (end_pos == 0) end_pos = pos + 1;
                pos = id_pos + ((c & 0x3f) << 8) + packet[pos+1];
                next = pos;
            } else {
                name_len++;
                pos++;
                next = next + c + 1;
            }
        } else {
            if (c >= '!' && c <= 'z' && c != '\\') name_len++;
            else name_len += 4;
            pos++;
        }
    }
    if (end_pos == 0) end_pos = pos;

    // Due to the nature of DNS name compression, it's possible to get a
    // name that is infinitely long. Return an error in that case.
    // We use the len of the packet as the limit, because it shouldn't
    // be possible for the name to be that long.
    if (steps >= 2*len || pos >= len)
    	return "NULL";

    name_len++;

    if(name_len > len *2)
    	return "NULL";

//    name = (char *)malloc(sizeof(char) * name_len);
    string name;
    pos = *packet_p;

    //Now actually assemble the name.
    //We've already made sure that we don't exceed the packet length, so
    // we don't need to make those checks anymore.
    // Non-printable and whitespace characters are replaced with a question
    // mark. They shouldn't be allowed under any circumstances anyway.
    // Other non-allowed characters are kept as is, as they appear sometimes
    // regardless.
    // This shouldn't interfere with IDNA (international
    // domain names), as those are ascii encoded.
    next = pos;
    i = 0;
    while (next != pos || packet[pos] != 0) {
        if (pos == next) {
            if ((packet[pos] & 0xc0) == 0xc0) {
                pos = id_pos + ((packet[pos] & 0x3f) << 8) + packet[pos+1];
                next = pos;
            } else {
                // Add a period except for the first time.
                if (i != 0) name.append(1,'.');i++;
                next = pos + packet[pos] + 1;
                pos++;
            }
        } else {
            uint8_t c = packet[pos];
            if (c >= '!' && c <= '~' && c != '\\') {
                name.append(1, (char) c);
                i++; pos++;
            } else {
            	return "NULL";
//                name.append(1,'\\')
//                	.append(1,'x');
//                uint8_t c1 = c/16 + 0x30;
//                uint8_t c2 = c%16 + 0x30;
//                if (c1 > 0x39) c1 += 0x27;
//                if (c2 > 0x39) c2 += 0x27;
//                name.append(1,c1)
//                	.append(1,c2);
//                i+=4;
//                pos++;
            }
        }
    }
    *packet_p = end_pos + 1;
    //printf("Name : %s\n", name.c_str());
    return name;
}

VOID UDPParser::decodeStunMsg(const BYTE packet, MPacket *msgObj)
{
	int offset = 0;
//	UCHAR addr[16];

	struct stun_packet_header *h = (struct stun_packet_header*)packet;

	uint16_t msgType = ntohs((unsigned short int)h->msgType);
	uint16_t msgLen  = ntohs((unsigned short int)h->msgLen);

	if(msgType != INDICATION)
		return;

	offset += STUN_PKT_HEADER;

	while(offset < msgLen)
	{
		uint16_t  attribute = (uint16_t) VAL_USHORT(packet+offset);
		offset += 2;
		uint16_t  attributeLen = (uint16_t) VAL_USHORT(packet+offset);
		offset += 2;

		if(attribute == REMOTE_ADDRESS && attributeLen == 8)
		{
				TCHAR upFamily = VAL_BYTE(packet);
				offset += 2;
				uint16_t  port = (uint16_t) VAL_USHORT(packet+offset);
				offset += 2;

				uint32_t longResolvedIp = 0;

				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[offset]);
				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[offset + 1]);
				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[offset + 2]);
				longResolvedIp=(longResolvedIp << 8) + (0xff & packet[offset + 3]);

//				utility->ExtractIP4Address(packet, addr, offset);
//				key.assign(std::string((const char *)addr));

				//Populate StunMAP with key = addr-port and store appIp which is msgObj->SIP

				STUNMAP::stunMap[longResolvedIp].appIp = longResolvedIp;
				STUNMAP::stunMap[longResolvedIp].createEpochSec = msgObj->frTimeEpochSec;

				break;
		}
		else
			offset += attributeLen;
	}
}

ULONG UDPParser::convIP2Long(char *ipAddress)
{
	char lAddress[16];
    unsigned long int num=0,val;
    char *tok,*ptr;

    strcpy(lAddress, ipAddress);

    tok=strtok(lAddress,".");
    while( tok != NULL)
    {
        val=strtoul(tok,&ptr,0);
        num=(num << 8) + val;
        tok=strtok(NULL,".");
    }
    return(num);
}


