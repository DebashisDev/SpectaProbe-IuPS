/*
 * PacketSSL.cpp
 *
 *  Created on: 24-Sep-2016
 *      Author: deb
 */

#include "PacketSSL.h"
#include "IPGlobal.h"

PacketSSL::PacketSSL() {
}

PacketSSL::~PacketSSL() {
}

void PacketSSL::decodeSSL(const BYTE packet, MPacket *msgObj)
{
	char result[50];
	uint32_t offset = 0, handshakeType = 0, len = 0;
	TCHAR lchar[10];
//	string result;
	int serialNoLen = 0, issuerLen = 0, not_before_len = 0, not_after_len = 0, RDNSequence = 0, dirStringLen = 0;

	lchar[0] = 0;

	offset += msgObj->tcpHLen;

	offset += 1; // Content Type

	int version = VAL_USHORT(packet + offset);

	if(version != TLSv1_2	 || version != TLSv1)
		return;

	offset += 2; // Version
	offset += 2; // Length

	handshakeType = VAL_BYTE(packet + offset);

	if(handshakeType == SSL_SERVER_HELLO)
	{
		offset += 1; // handshake Type

		sprintf(lchar, "%02x%02x%02x", packet[offset], packet[offset+1], packet[offset+2]);

		len = ProbeUtility::HextoDigits(lchar);
//		printf("Length:: %d\n", len);
		offset += 3; // Length

		offset += len;
		printf("#%lu, OffSet %d| len:: %d\n", IPGlobal::t_FrameCount, offset, len);

		int certificate = VAL_BYTE(packet + offset);

		if(certificate == SSL_CERTIFICATE)
		{
			offset += 1; // handshake Type

			lchar[0] = 0;
			sprintf(lchar, "%02x%02x%02x", packet[offset], packet[offset+1], packet[offset+2]);
			len = ProbeUtility::HextoDigits(lchar);
			offset += 3;

			lchar[0] = 0;
			sprintf(lchar, "%02x%02x%02x", packet[offset], packet[offset+1], packet[offset+2]);
			len = ProbeUtility::HextoDigits(lchar);
			offset += 3;
//		  		  			  printf("Certificates Len = %d\n", len);

			lchar[0] = 0;
			sprintf(lchar, "%02x%02x%02x", packet[offset], packet[offset+1], packet[offset+2]);
			len = ProbeUtility::HextoDigits(lchar);
			offset += 3;
//		  	printf("Certificate Len = %d\n", len);

			offset += 10; // Spare 0x30, 0x82, 0x06, 0xa7, 0x30, 0x82, 0x04, 0x8f, 0xa0, 0x03

			offset += 2; // SignedCertificate Tag and Length
			offset += 1; // SignedCertificate Version;

			offset += 1;	// Serial Number Tag
			serialNoLen = VAL_BYTE(packet + offset);
//		  	printf("serialNoLen Len = %d\n", serialNoLen);

			offset += 1;	// Serial Number Length

			offset += serialNoLen;

			offset += 2; // 0x30, 0x0d

			offset += 1;	// Signature Tag
			int signatureLen = VAL_BYTE(packet + offset);
//		  	printf("signatureLen Len = %d\n", signatureLen);
			offset += 1;	// Signature Length
			offset += signatureLen;

			offset += 4; // Spare 0x05, 0x00, 0x30, 0x81

			issuerLen = VAL_BYTE(packet + offset);
//		  		  			  printf("issuerLen Len = %d\n", issuerLen);
			offset += 1;	// issuer Length
			offset += issuerLen;

			offset += 2; // Spare 0x30, 0x1e

			offset += 1;	// Not Before Tag
			not_before_len = VAL_BYTE(packet + offset);
//		  		  			  printf("not_before_len Len = %d\n", not_before_len);
			offset += 1;	// Not Before Length
			offset += not_before_len;

			offset += 1;	// Not After Tag
			not_after_len = VAL_BYTE(packet + offset);
//		  		  			  printf("not_after_len Len = %d\n", not_after_len);
			offset += 1;	// Not After Length

			offset += not_after_len;

			RDNSequence = VAL_BYTE(packet + offset);

			while(RDNSequence != RDNSequenceTag)
			{
				offset += 1;
				RDNSequence = VAL_BYTE(packet + offset);
			}

			while(RDNSequence == RDNSequenceTag)
			{
				offset += 1;
				int id_len = VAL_BYTE(packet + offset);
//								  printf(" id_len Len = %d\n", id_len);
				offset += 1;	// Id Length

				offset += id_len;

				offset += 1; // Directory String Tag
				dirStringLen = VAL_BYTE(packet + offset);
//				printf(" dirStringLen Len = %d\n", dirStringLen);
				offset += 1;	// Directory String Length

				result[0] = 0;
				for(int i = 0; i < dirStringLen; i++)
				{
//					if ((isprint(packet[offset + i])) != 0 && ((packet[offset + i] >= 42 && packet[offset + i] <= 57)
//							                             || (packet[offset + i] >= 64 && packet[offset + i] <= 90)
//														 || (packet[offset + i] >= 97 && packet[offset + i] <= 122)))

					if ((isprint(packet[offset + i])) != 0 && ((packet[offset + i] == 42 || packet[offset + i] == 45 || packet[offset + i] == 46)
							                             || (packet[offset + i] == 64)
														 || (packet[offset + i] >= 97 && packet[offset + i] <= 122)))

						if(i >= 50) break;
						result[i] = packet[offset + i];
				}
				offset += dirStringLen;

				// Check for next RDNSequence
				offset += 4;
				RDNSequence = VAL_BYTE(packet + offset);
			}

			if(strstr(result, ".") == 0)
			//std::size_t pos = result.find('.');
			//if(pos != std::string::npos)
			{
				string userIP_resolveIP_key = getDNSKey(msgObj->ipDestAddr, msgObj->ipSourceAddr);
//				printf("\nPacket :: %lu Key:: %s -- IP:: %s -- URL:: %s\n", IPGlobal::t_FrameCount, userIP_resolveIP_key.c_str(), msgObj->ipData->s_addr.c_str(), result.c_str());
				updateDns(userIP_resolveIP_key, msgObj->ipDestAddr, msgObj->ipSourceAddr, result, msgObj->frTimeEpochNanoSec);
			}
		}
	}
}

