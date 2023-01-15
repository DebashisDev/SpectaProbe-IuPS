/*
 * diameterParser.h
 *
 *  Created on: 05-Oct-2016
 *      Author: debashis
 */

#ifndef PLUGINS_TCP_SRC_DIAMETERPARSE_H_
#define PLUGINS_TCP_SRC_DIAMETERPARSE_H_

#include <map>

#include "BaseConfig.h"
#include "SpectaTypedef.h"
#include "IPGlobal.h"
#include "ProbeUtility.h"
#include "GXMessage.h"
#include "GXSessionManager.h"
#include "GXGlobal.h"
#include "Log.h"

#define AVP_HEADER					8
#define USER_EQUIPMENT_IMEI			0

#define USER_NAME					1
#define GPP_SGSN_ADDRESS			6
#define	FRAMED_IP_ADDRESS			8
#define CLASS						25
#define	SESSION_TIMEOUT				27

#define CALLED_STATION_ID			30
#define PROXY_STATE					33
#define ACCOUNTING_SESSION_ID		44
#define ACCT_MULTI_SESSION_ID		50
#define EVENT_TIMESTAMP				55
#define ACCT_INTERIM_INTERVAL		85
#define HOST_IP_ADDRESS				257
#define AUTH_APP_ID					258
#define ACCT_APP_ID					259
#define VENDOR_SPECIFIC_APP_ID		260
#define REDIRECT_HOST_USAGE			261
#define REDIRECT_MAX_CACHE_TIME		262
#define SESSION_ID					263
#define ORIGINAL_HOST				264
#define SUPPORTED_VENDOR_ID			265
#define VENDOR_ID					266
#define FIRMWARE_REVISION			267
#define RESULT_CODE					268
#define PRODUCT_NAME				269

#define SESSION_BINDING				270
#define SESSION_SRV_FAILOVER		271
#define MULTI_ROUND_TIMEOUT			272
#define DISCONNECT_CAUSE			273
#define AUTH_REQUEST_TYPE			274
#define AUTH_BRACE_PERIOD			276
#define AUTH_SESSION_STATE			277
#define ORIGIN_STATE_ID				278
#define FAILED_AVP					279
#define PROXY_HOST					280
#define ERROR_MESSAGE				281
#define ROUTE_RECORD				282
#define DESTINATION_REALM			283
#define PROXY_INFO					284
#define RE_AUTH_REQUEST_TYPE		285
#define ACCOUNTING_SUB_SESSION_ID 	287
#define AUTHORIZATION_LIFETIME  	291
#define REDIRECT_HOST				292
#define DESTINATION_HOST 			293
#define ERROR_REPORTING_HOST		294
#define TERMINATION_CAUSE			295
#define ORIGIN_REALM				296
#define EXPERIMENTAL_RESULT     	297
#define EXPERIMENTAL_RESULT_CODE 	298
#define INBAND_SECURITY_ID			299
#define E2E_SEQUENCE				300
#define CC_REQUEST_NUMBER			415
#define CC_REQUEST_TYPE				416
#define SUBSCRIPTION_ID 			443
#define SUBSCRIPTION_ID_DATA		444
#define SUBSCRIPTION_ID_TYPE		450

#define	MULTI_SERVICE_CREDIT_CTRL	456
#define USER_EQUIPMENT_INFO			458
#define ACCOUNTING_RECORD_TYPE  	480
#define ACCOUNTING_REALTIME_REQ 	483
#define ACCOUNTIG_RECORD_NUMBER 	485
#define ACCESS_NW_CHARGING_ADDR 	501
#define SUPPORTED_FEATURES			628
#define	EVENT_TRIGGER				1006
#define	OFFLINE						1008
#define	ONLINE						1009
#define	QOS_INFORMATION				1016
#define	BEARER_IDENTIFIER			1020
#define	BEARER_OPERATION			1021
#define	ACCESS_NW_CHARGING_IDENTIFIER	1022
#define	BEARER_CTRL_MODE			1023
#define	IP_CAN_TYPE					1027
#define RAT_TYPE					1032
#define	USAGE_MONITORING_INFO		1067

typedef std::map<uint32_t, std::string> resultCodeMap;
typedef std::map<uint32_t, std::string> ratTypeMap;
typedef std::map<uint32_t, std::string> eventTriggerMap;
typedef std::map<ULONG, std::string> appTypeMap;


class GXParser : public BaseConfig, public ProbeUtility {

	private:
			BYTE 					packet;
			uint16_t 				msgType;
			static resultCodeMap	attributeResultCode;
			static ratTypeMap 		ratType;
			static eventTriggerMap 	eventTrigger;
			static appTypeMap 		appType;
			uint32_t calculate_Len, accumulatedDiameterLen, ipLen;
			GXSessionManager 		*gxSM;

	public:
			GXParser();
			~GXParser();

			VOID parsePacket(const BYTE packet, MPacket *msgObj);
//			virtual VOID parsePacket(const BYTE packet, MPacket *msgObj);
			int parseDiameterParameter(const BYTE packet, MPacket *msgObj, size_t offset);
			uint32_t parseAVPType(const BYTE packet, size_t offset, MPacket *msgObj);
			int roundUp(int numToRound, int multiple);
			static VOID initResultCode();
			static VOID initRatType();
			static VOID initEventTrigger();
			static VOID initAppType();
			static resultCodeMap getResultCodeMap() { return attributeResultCode; }
			static ratTypeMap getRatTypeMap() { return ratType; }
			static eventTriggerMap getEventTrigger() { return eventTrigger; }
			static appTypeMap getAppType() { return appType; }

//			virtual PacketParser* getNextParser(uint16_t protocolid);
//			virtual TPacket* getMsgObj();

			string getAVPValue(int len, size_t bodyOffset, const BYTE packet);
};

#endif /* PLUGINS_TCP_SRC_DIAMETERPARSE_H_ */
