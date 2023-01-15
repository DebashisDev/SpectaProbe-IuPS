/*
 * diameterParse.cpp
 *
 *  Created on: 05-Oct-2016
 *      Author: deb
 */

#include "GXParser.h"
#include <stdio.h>
#include <unistd.h>
using namespace std;

GXParser::GXParser() {
	packet = NULL;
	msgType = 0;
	accumulatedDiameterLen = calculate_Len = 0;
	ipLen = 0;
	gxSM = new GXSessionManager();
	this->_name = "GxParser";
	this->setLogLevel(Log::theLog().level());

	initResultCode();
	initRatType();
	initEventTrigger();
	initAppType();
}

GXParser::~GXParser() {
	delete (gxSM);
}

resultCodeMap 	GXParser::attributeResultCode = resultCodeMap();
ratTypeMap 		GXParser::ratType = ratTypeMap();
eventTriggerMap GXParser::eventTrigger = eventTriggerMap();
appTypeMap 		GXParser::appType = appTypeMap();

void GXParser::parsePacket(const BYTE packet, MPacket *msgObj)
{
	bool process = true;
	uint32_t version = 0;
	uint32_t len = 0;
	size_t offset = 0;
	uint32_t no_of_diameter = 0;

	this->packet = packet + msgObj->tcpHLen;
	calculate_Len = (msgObj->ipTLen - (msgObj->ipHLen + msgObj->tcpHLen));

	ipLen = calculate_Len;

//	printf("\nPacket # %lu\n", IPGlobal::t_FrameCount);

	if(msgObj->protoSourcePort == GX_PORT)
	{
		this->msgType = ANSWER;
	}
	else
	{
		this->msgType = REQUEST;
	}

	version = VAL_BYTE(this->packet);

	if(version != 1)
		return;

	accumulatedDiameterLen = 0;

	while(calculate_Len > 0) {
		no_of_diameter++;

		len = parseDiameterParameter(this->packet, msgObj, offset);
//		printf("\nDiameter# %d| Calculated Len :: %d| Offset :: %d Return Len :: %d\n", no_of_diameter, calculate_Len, offset, len);

		if(len == 0)
			break;

		calculate_Len -= len;
		offset += len;
	}
}

int GXParser::parseDiameterParameter(const BYTE packet, MPacket *msgObj, size_t bodyOffset)
{
	uint32_t avp_len = 0;
	TCHAR lchar[10];
	lchar[0] = 0;
	bool found = false;

	msgObj->messageType = this->msgType;
	int version = VAL_BYTE(packet + bodyOffset);
	bodyOffset += 1;

	uint32_t diameterLen = ProbeUtility::getLength(packet, bodyOffset);

	accumulatedDiameterLen += diameterLen;

//	printf("IP Length = %d| diameterLen = %d| accumulated = %d\n", ipLen, diameterLen, accumulatedDiameterLen);

	if(accumulatedDiameterLen > ipLen)
		return 0;

	bodyOffset += 3; 	// Length

	bodyOffset += 1; 	// Flag

	sprintf(lchar, "%02x%02x%02x", packet[bodyOffset], packet[bodyOffset+1], packet[bodyOffset+2]);
	msgObj->commandCode = ProbeUtility::HextoDigits(lchar);
	bodyOffset += 3;	// Command Code

	// Parsing Credit-Control (272)
	if(msgObj->commandCode != 272)
	{
		// Parsing Re-Auth (258)
		if(msgObj->commandCode != 258)
			return 0;
	}

	appTypeMap appName = getAppType();
	msgObj->appId = VAL_ULONG(packet + bodyOffset);
	msgObj->appName = appName[msgObj->appId];

	bodyOffset += 4;	// Application Id

//	Long2Hex(VAL_ULONG(packet + bodyOffset), msgObj->diameterData->hop_by_hop);
	bodyOffset += 4;	// Hop-by-Hop

//	Long2Hex(VAL_ULONG(packet + bodyOffset), msgObj->diameterData->end_to_end);
	bodyOffset += 4;	//End-to-End

	int gxRemainingLen = diameterLen - 20; //bodyOffset;

	//( Head Size (Code(4) + Flag(1) + Length(3) + Vendor Id(4)))

	while(gxRemainingLen >= 12)
	{
		avp_len = parseAVPType(packet, bodyOffset, msgObj); //Attribute-Value Pairs (AVP)

		if(avp_len == 0)
			return 0;

		gxRemainingLen -= avp_len;
		bodyOffset += avp_len;

	}
	/* Send the Diameter Session in Session Manager Queue */

	if(msgObj->sessionId.length() != 0) {
		if(msgObj->eventTrigger.length() > 0)
			msgObj->eventTrigger = msgObj->eventTrigger.substr(0, msgObj->eventTrigger.size() - 1);	// Remove extra # from the string, as there are multiple Event-triggers those are separated by #
		else
			msgObj->eventTrigger.assign("NA");

//		TPacket *pushObj = new TPacket();
//		pushObj->set(*msgObj);
//		msgObj->reset();
//
//		gxIpc->submitData(pushObj, pushObj->threadId);

		gxSM->updateGxSession(msgObj, 1);
		//TODO
	}
	return diameterLen;
}

string GXParser::getAVPValue(int len, size_t bodyOffset, const BYTE packet)
{
	std::string val;
	val.clear();

	// 8 = 4 Bytes (Code) + 1 Byte (Flag) + 3 Bytes AVP Length
	for(int count = 0; count < len; count++) {
		val.append(1, packet[bodyOffset + count]);
	}
	return val;
}

uint32_t GXParser::parseAVPType(const BYTE packet, size_t bodyOffset, MPacket *msgObj)
{
	ULONG avpCode = VAL_ULONG(packet + bodyOffset);
	UCHAR addr[16];
	addr[0] = 0;

	if(avpCode == 0)
		return 0;

	bodyOffset += 4;	// AVP_Code

//	uint32_t flag = VAL_BYTE(packet + bodyOffset);
	bodyOffset += 1;	// AVP_Flag

	uint32_t AVPLen = ProbeUtility::getLength(packet, bodyOffset);
	bodyOffset += 3;	// AVP_Length

	switch(avpCode)
	{
		case SESSION_ID:
				msgObj->sessionId = getAVPValue(AVPLen - AVP_HEADER, bodyOffset, packet);
				TheLog_v1(Log::Trace, name(),"AVP:: SESSION_ID : %s", msgObj->sessionId.c_str());

				break;

		case AUTH_APP_ID:
//			{
//				ULONG appId = VAL_ULONG(packet + bodyOffset);
//				TheLog_v1(Log::Trace, name(),"AVP:: AUTH_APP_ID : %ld\n", appId);
//			}
			break;

		case ORIGINAL_HOST:
				msgObj->originHost = getAVPValue(AVPLen - AVP_HEADER, bodyOffset, packet);
				TheLog_v1(Log::Trace, name(),"AVP:: ORIGINAL_HOST : %s\n", msgObj->originHost.c_str());

				break;

		case ORIGIN_REALM:
				msgObj->originRealm = getAVPValue(AVPLen - AVP_HEADER, bodyOffset, packet);
				TheLog_v1(Log::Trace, name(),"AVP:: ORIGIN_REALM : %s\n", msgObj->originRealm.c_str());

				break;

		case DESTINATION_HOST:
				msgObj->destinationHost = getAVPValue(AVPLen - AVP_HEADER, bodyOffset, packet);
				TheLog_v1(Log::Trace, name(),"AVP:: ORIGIN_REALM : %s\n", msgObj->originRealm.c_str());
				break;

		case DESTINATION_REALM:
				msgObj->destinationRealm = 	getAVPValue(AVPLen - AVP_HEADER, bodyOffset, packet);
				TheLog_v1(Log::Trace, name(),"AVP:: DESTINATION_REALM : %s\n", msgObj->destinationRealm.c_str());

				break;

		case CC_REQUEST_TYPE: /* 1 - Initial Request 2 - Update Request 3 - Termination Request */
				msgObj->ccRequestType = VAL_ULONG(packet + bodyOffset);

				if(msgObj->ccRequestType > 3)
					return 0;

				msgObj->ccReqTypeDesc = GXAVPMap::requestType[msgObj->ccRequestType];
				TheLog_v2(Log::Trace, name(),"AVP:: CC_REQUEST_TYPE : %ld| %s\n", msgObj->ccRequestType, GXAVPMap::requestType[msgObj->ccRequestType]);

				break;

		case TERMINATION_CAUSE: /* 1 - Logout, 6 - Authentication Expired*/
					msgObj->tCause = VAL_ULONG(packet + bodyOffset);

					if(msgObj->tCause > 8 || msgObj->tCause == 0)
						return 0;

					msgObj->tCauseDesc = GXAVPMap::terminationCause[msgObj->tCause];
					TheLog_v2(Log::Trace, name(),"AVP:: TERMINATION_CAUSE : %ld| %s\n", msgObj->tCause, GXAVPMap::terminationCause[msgObj->tCause]);

					break;

		case BEARER_OPERATION: /* */
					bodyOffset += 4;	// AVP Vendor Id
					msgObj->bearerOperation = VAL_ULONG(packet + bodyOffset);

					msgObj->bearerOperationDesc = GXAVPMap::bearerOperation[msgObj->bearerOperation];
					TheLog_v2(Log::Trace, name(),"AVP:: BEARER_OPERATION : %ld: %s\n", msgObj->bearerOperation, msgObj->bearerOperationDesc.c_str());

					break;

		case CALLED_STATION_ID:
					msgObj->calledStationId = getAVPValue(AVPLen - AVP_HEADER, bodyOffset, packet);
					TheLog_v1(Log::Trace, name(),"AVP:: CALLED_STATION_ID : %s\n", msgObj->calledStationId.c_str());

					break;

		case ACCESS_NW_CHARGING_ADDR:
					bodyOffset += 6;	// AVP Vendor Id (4 Bytes) + IP Family (2 Bytes)
					ProbeUtility::ExtractIP4Address(packet, addr, bodyOffset);
					msgObj->accessNetworkChargingAddress.assign(std::string((char *)addr));
					TheLog_v1(Log::Trace, name(),"AVP:: ACCESS_NW_CHARGING_ADDR : %s\n", msgObj->accessNetworkChargingAddress.c_str());

					break;

		case FRAMED_IP_ADDRESS:
					ProbeUtility::ExtractIP4Address(packet, addr, bodyOffset);
					msgObj->framedIPAddress.assign(std::string((char *)addr));
					TheLog_v1(Log::Trace, name(),"AVP:: FRAMED_IP_ADDRESS : %s\n", msgObj->framedIPAddress.c_str());

					break;

		case GPP_SGSN_ADDRESS:
					bodyOffset += 4;	// AVP Vendor Id
					ProbeUtility::ExtractIP4Address(packet, addr, bodyOffset);
					msgObj->GPPS_GSN_Address.assign(std::string((char *)addr));
					TheLog_v1(Log::Trace, name(),"AVP:: GPP_SGSN_ADDRESS : %s\n", msgObj->GPPS_GSN_Address.c_str());

					break;

		case RAT_TYPE:
				{
					ratTypeMap ratTypeDesc = getRatTypeMap();
					bodyOffset += 4;	// AVP Vendor Id
					msgObj->ratType = VAL_ULONG(packet + bodyOffset);
					msgObj->ratTypeDesc = ratTypeDesc[msgObj->ratType];
					TheLog_v2(Log::Trace, name(),"AVP:: RAT_TYPE : %d[%s]\n", msgObj->ratType, msgObj->ratTypeDesc.c_str());
				}
				break;

		case USER_EQUIPMENT_INFO:
				{
					u_char sbuf[256];
					std::string result;
					result.clear();

					ULONG code = VAL_ULONG(packet + bodyOffset);
					bodyOffset += 5;	// Code (4 Bytes) + AVP_Flag (1 Bytes)

					int len = ProbeUtility::getLength(packet, bodyOffset);
					bodyOffset += 3;	// Length

					ULONG type = VAL_ULONG(packet + bodyOffset);
					bodyOffset += 4;

					if(type == USER_EQUIPMENT_IMEI)	// Equipment Info Type (0 - IMEI)
					{
						ULONG code = VAL_ULONG(packet + bodyOffset);
						bodyOffset += 5;	// Code (4 Bytes) + AVP_Flag (1 Bytes)

						len = 0;
						len = ProbeUtility::getLength(packet, bodyOffset);
						bodyOffset += 3;	// AVP_Length

						int imeiLen = len - AVP_HEADER;

						if(imeiLen == 16) {
							result = getAVPValue(imeiLen, bodyOffset, packet);
						}
						else if(imeiLen == 8) {
							Long2Hex(VAL_ULONG(packet + bodyOffset), sbuf);
							result.assign(std::string((const char *)sbuf));
							bodyOffset += 4;
							Long2Hex(VAL_ULONG(packet + bodyOffset), sbuf);
							result.append(std::string((const char *)sbuf));
						}

						msgObj->imei = result;
						TheLog_v1(Log::Trace, name(),"IMEI :: %s\n", result.c_str());
					}
				}
				break;

		case RESULT_CODE:
				{
					resultCodeMap resultCodeDesc = getResultCodeMap();
					msgObj->resultCode = VAL_ULONG(packet + bodyOffset);

					msgObj->resultCodeDesc = resultCodeDesc[msgObj->resultCode];
					TheLog_v2(Log::Trace, name(),"AVP:: RESULT_CODE : %d Disc : %s\n", msgObj->resultCode, msgObj->resultCodeDesc.c_str());
				}

				break;

		case EVENT_TRIGGER:
				{
					eventTriggerMap eventDesc = getEventTrigger();
					bodyOffset += 4;	// AVP Vendor Id
					int event = VAL_ULONG(packet + bodyOffset);
					msgObj->eventTrigger.append(eventDesc[event]);
					msgObj->eventTrigger.append("#");
					TheLog_v1(Log::Trace, name(),"AVP:: EVENT_TRIGGER : %s\n", msgObj->eventTrigger.c_str());
				}
				break;

		case SUBSCRIPTION_ID:
				{
					dataPart:

					ULONG code = VAL_ULONG(packet + bodyOffset);
					bodyOffset += 4;

					bodyOffset += 1;	// AVP_Flag

					int len = ProbeUtility::getLength(packet, bodyOffset);

					if(len > 44)
						return 0;

					bodyOffset += 3;	// AVP_Length

					switch(code)
					{
						case SUBSCRIPTION_ID_TYPE:
									{	/* 1 - IMSI and 0 - MSISDN */
										ULONG resultNo = VAL_ULONG(packet + bodyOffset);
										TheLog_v1(Log::Trace, name(),"AVP:: SUBSCRIPTION_ID_TYPE : %ld ", resultNo);

										if (resultNo > 1)
											return 0;

										msgObj->subscriptionType = resultNo;

										bodyOffset += len - AVP_HEADER;

										int padding =  roundUp(len, 4) - len;
										bodyOffset += padding;
										goto dataPart;
									}
									break;

						case SUBSCRIPTION_ID_DATA:
									{
										switch(msgObj->subscriptionType)
										{
											case 0:
													msgObj->msisdn = getAVPValue(len - 8, bodyOffset, packet);
													TheLog_v1(Log::Trace, name()," AVP:: MSISDN : %s\n", msgObj->msisdn.c_str());
													break;

											case 1:
													msgObj->imsi = getAVPValue(len - 8, bodyOffset, packet);
													TheLog_v1(Log::Trace, name()," AVP:: IMSI   : %s\n", msgObj->imsi.c_str());
													break;

											default:
													break;
										}
										bodyOffset += len - AVP_HEADER;
										int padding =  roundUp(len, 4) - len;
										bodyOffset += padding;
									}
									break;

						default:
									return 0;
									break;
					}
				}
				break;

		default:
				break;

	}

	bodyOffset += AVPLen - AVP_HEADER; // AVPLen - AVP Header Len ( 8 = 4 Bytes (Code) + 1 Byte (Flag) + 3 Bytes AVP Length)

	// AVP Length is multiple of 4.
	int padding =  roundUp(AVPLen, 4) - AVPLen;
	bodyOffset += padding;

	return (AVPLen + padding);
}

VOID GXParser::initResultCode()
{
	attributeResultCode.insert(std::pair<int, std::string>(1001, "DIAMETER_MULTI_ROUND_AUTH"));
	attributeResultCode.insert(std::pair<int, std::string>(2001, "DIAMETER_SUCCESS"));
	attributeResultCode.insert(std::pair<int, std::string>(2002, "DIAMETER_LIMITED_SUCCESS"));
	attributeResultCode.insert(std::pair<int, std::string>(3001, "DIAMETER_COMMAND_UNSUPPORTED"));
	attributeResultCode.insert(std::pair<int, std::string>(3002, "DIAMETER_UNABLE_TO_DELIVER"));
	attributeResultCode.insert(std::pair<int, std::string>(3003, "DIAMETER_REALM_NOT_SERVED"));
	attributeResultCode.insert(std::pair<int, std::string>(3004, "DIAMETER_TOO_BUSY"));
	attributeResultCode.insert(std::pair<int, std::string>(3005, "DIAMETER_LOOP_DETECTED"));
	attributeResultCode.insert(std::pair<int, std::string>(3006, "DIAMETER_REDIRECT_INDICATION"));
	attributeResultCode.insert(std::pair<int, std::string>(3007, "DIAMETER_APPLICATION_UNSUPPORTED"));
	attributeResultCode.insert(std::pair<int, std::string>(3008, "DIAMETER_INVALID_HDR_BITS"));
	attributeResultCode.insert(std::pair<int, std::string>(3009, "DIAMETER_INVALID_AVP_BITS"));
	attributeResultCode.insert(std::pair<int, std::string>(3010, "DIAMETER_UNKNOWN_PEER"));
	attributeResultCode.insert(std::pair<int, std::string>(4001, "DIAMETER_AUTHENTICATION_REJECTED"));
	attributeResultCode.insert(std::pair<int, std::string>(4002, "DIAMETER_OUT_OF_SPACE"));
	attributeResultCode.insert(std::pair<int, std::string>(4003, "DIAMETER_ELECTION_LOST"));
	attributeResultCode.insert(std::pair<int, std::string>(4012, "DIAMETER_CREDIT_LIMIT_REACHED"));
	attributeResultCode.insert(std::pair<int, std::string>(5001, "DIAMETER_AVP_UNSUPPORTED"));
	attributeResultCode.insert(std::pair<int, std::string>(5002, "DIAMETER_UNKNOWN_SESSION_ID"));
	attributeResultCode.insert(std::pair<int, std::string>(5003, "DIAMETER_AUTHORIZATION_REJECTED"));
	attributeResultCode.insert(std::pair<int, std::string>(5004, "DIAMETER_INVALID_AVP_VALUE"));
	attributeResultCode.insert(std::pair<int, std::string>(5005, "DIAMETER_MISSING_AVP"));
	attributeResultCode.insert(std::pair<int, std::string>(5006, "DIAMETER_RESOURCES_EXCEEDED"));
	attributeResultCode.insert(std::pair<int, std::string>(5007, "DIAMETER_CONTRADICTING_AVPS"));
	attributeResultCode.insert(std::pair<int, std::string>(5008, "DIAMETER_AVP_NOT_ALLOWED"));
	attributeResultCode.insert(std::pair<int, std::string>(5009, "DIAMETER_AVP_OCCURS_TOO_MANY_TIMES"));
	attributeResultCode.insert(std::pair<int, std::string>(5010, "DIAMETER_NO_COMMON_APPLICATION"));
	attributeResultCode.insert(std::pair<int, std::string>(5011, "DIAMETER_UNSUPPORTED_VERSION"));
	attributeResultCode.insert(std::pair<int, std::string>(5012, "DIAMETER_UNABLE_TO_COMPLY"));
	attributeResultCode.insert(std::pair<int, std::string>(5013, "DIAMETER_INVALID_BIT_IN_HEADER"));
	attributeResultCode.insert(std::pair<int, std::string>(5014, "DIAMETER_INVALID_AVP_LENGTH"));
	attributeResultCode.insert(std::pair<int, std::string>(5015, "DIAMETER_INVALID_MESSAGE_LENGTH"));
	attributeResultCode.insert(std::pair<int, std::string>(5016, "DIAMETER_INVALID_AVP_BIT_COMBO"));
	attributeResultCode.insert(std::pair<int, std::string>(5017, "DIAMETER_NO_COMMON_SECURITY"));
	attributeResultCode.insert(std::pair<int, std::string>(5030, "DIAMETER_USER_UNKNOWN"));
}

VOID GXParser::initRatType()
{
	ratType.insert(std::pair<int, std::string>(0, "WLAN"));
	ratType.insert(std::pair<int, std::string>(1, "VIRTUAL"));
	ratType.insert(std::pair<int, std::string>(1000, "UTRAN"));
	ratType.insert(std::pair<int, std::string>(1001, "GERAN"));
	ratType.insert(std::pair<int, std::string>(1002, "GAN"));
	ratType.insert(std::pair<int, std::string>(1003, "HSPA_EVOLUTION"));
	ratType.insert(std::pair<int, std::string>(1004, "EUTRAN"));
	ratType.insert(std::pair<int, std::string>(2000, "CDMA2000_1X"));
	ratType.insert(std::pair<int, std::string>(2001, "HRPD"));
	ratType.insert(std::pair<int, std::string>(2002, "UMB"));
	ratType.insert(std::pair<int, std::string>(2003, "EHRPD"));
}

VOID GXParser::initEventTrigger()
{
	eventTrigger.insert(std::pair<int, std::string>(0, "SGSN_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(1, "QOS_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(2, "RAT_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(3, "TFT_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(4, "PLMN_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(5, "LOSS_OF_BEARER"));
	eventTrigger.insert(std::pair<int, std::string>(6, "RECOVERY_OF_BEARER"));
	eventTrigger.insert(std::pair<int, std::string>(7, "IP-CAN_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(11, "QOS_CHANGE_EXCEEDING_AUTHORIZATION"));
	eventTrigger.insert(std::pair<int, std::string>(12, "RAI_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(13, "USER_LOCATION_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(14, "NO_EVENT_TRIGGERS"));
	eventTrigger.insert(std::pair<int, std::string>(15, "OUT_OF_CREDIT"));
	eventTrigger.insert(std::pair<int, std::string>(16, "REALLOCATION_OF_CREDIT"));
	eventTrigger.insert(std::pair<int, std::string>(17, "REVALIDATION_TIMEOUT"));
	eventTrigger.insert(std::pair<int, std::string>(18, "UE_IP_ADDRESS_ALLOCATE"));
	eventTrigger.insert(std::pair<int, std::string>(19, "UE_IP_ADDRESS_RELEASE"));
	eventTrigger.insert(std::pair<int, std::string>(20, "DEFAULT_EPS_BEARER_QOS_CHANGE"));

	eventTrigger.insert(std::pair<int, std::string>(21, "AN_GW_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(22, "SUCCESSFUL_RESOURCE_ALLOCATION"));
	eventTrigger.insert(std::pair<int, std::string>(23, "RESOURCE_MODIFICATION_REQUEST"));
	eventTrigger.insert(std::pair<int, std::string>(24, "PGW_TRACE_CONTROL"));
	eventTrigger.insert(std::pair<int, std::string>(25, "UE_TIME_ZONE_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(26, "TAI_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(27, "ECGI_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(28, "CHARGING_CORRELATION_EXCHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(29, "APN-AMBR_MODIFICATION_FAILURE"));
	eventTrigger.insert(std::pair<int, std::string>(30, "USER_CSG_INFORMATION_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(33, "USAGE_REPORT"));
	eventTrigger.insert(std::pair<int, std::string>(34, "DEFAULT-EPS-BEARER-QOS_MODIFICATION_FAILURE"));
	eventTrigger.insert(std::pair<int, std::string>(35, "USER_CSG_HYBRID_SUBSCRIBED_INFORMATION_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(36, "USER_CSG_ HYBRID_UNSUBSCRIBED_INFORMATION_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(37, "ROUTING_RULE_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(39, "APPLICATION_START"));
	eventTrigger.insert(std::pair<int, std::string>(40, "APPLICATION_STOP"));
	eventTrigger.insert(std::pair<int, std::string>(42, "CS_TO_PS_HANDOVER"));
	eventTrigger.insert(std::pair<int, std::string>(43, "UE_LOCAL_IP_ADDRESS_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(44, "H(E)NB_LOCAL_IP_ADDRESS_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(45, "ACCESS_NETWORK_INFO_REPORT"));
	eventTrigger.insert(std::pair<int, std::string>(46, "CREDIT_MANAGEMENT_SESSION_FAILURE"));
	eventTrigger.insert(std::pair<int, std::string>(47, "DEFAULT_QOS_CHANGE"));
	eventTrigger.insert(std::pair<int, std::string>(48, "CHANGE_OF_UE_PRESENCE_IN_PRESENCE_REPORTING_AREA_REPORT"));
}

VOID GXParser::initAppType()
{
	appType.insert(std::pair<ULONG, std::string>(4, "Diameter Credit Control"));
	appType.insert(std::pair<ULONG, std::string>(16777238, "3GPP Gx"));
}

int GXParser::roundUp(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}
