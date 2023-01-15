/*
 * GTPGlobal.h
 *
 *  Created on: 10-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_INC_GTPGLOBAL_H_
#define PLUGINS_GN_INC_GTPGLOBAL_H_

#include "IPGlobal.h"
using namespace std;

#define GTPv1		1
#define GTPv2		2

#define GTP_GLB_SESSION_TEID_ARRAY_SIZE		1000	//Poosible values 10, 100, 1000, 10000, 100000....

#define GTP_MPKT_PPS_INTF_0		200000
#define GTP_MPKT_PPS_INTF_1		5000
#define GTP_MPKT_PPS_INTF_2		200000
#define GTP_MPKT_PPS_INTF_3		5000

#define GTPC_CLEAN_BATCH_LIMIT	100000
#define GTPC_GLB_CLEAN_BATCH_LIMIT	50000

//Determined by number of expected packets / sec per interface per router to be distributed to each sm / sec
//200K PPS per interface
//100K PPS per router
//Worst case all packets goes to one router and single SM
//Set 200K per Sec, with 10 sec buffer set to 2M
#define GTP_MPKT_POOL_ARRAY_ELEMENTS		100		//Poosible values 10, 100, 1000, 10000, 100000....
#define GTP_MPKT_POOL_ARRAY_SIZE			10000

#define GTPC_SESSION_POOL_ARRAY_ELEMENTS  	100		//Poosible values 10, 100, 1000, 10000, 100000....
#define GTPC_SESSION_POOL_ARRAY_SIZE 	 	5000

//This number will be determined by total number of active users
#define GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS 100		//Poosible values 10, 100, 1000, 10000, 100000....
#define GTP_GLB_SESSION_POOL_ARRAY_SIZE		10000

#define GTPC_V1_FLUSH_POOL_ARRAY_ELEMENTS	100		//Poosible values 10, 100, 1000, 10000, 100000....
#define GTPC_V1_FLUSH_POOL_ARRAY_SIZE		5000

#define GTPC_V1_MAX_FLUSH_COUNT		10000

//#define GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE			50000

/* definitions of fields in information table */
#define GTP_EXT_CAUSE 		1
#define GTP_EXT_IMSI 		2
#define GTP_EXT_RAI			3
#define GTP_EXT_TLLI		4
#define GTP_EXT_TMSI		5
#define GTP_EXT_SPARE1		6
#define GTP_EXT_SPARE2		7
#define GTP_EXT_REORDER		8
#define GTP_EXT_AUTH_T		9
#define GTP_EXT_SPARE		10
#define GTP_EXT_MAP			11
#define GTP_EXT_PTMSI		12
#define GTP_EXT_MS_V		13
#define GTP_EXT_RECOV		14
#define GTP_EXT_SELECT		15
#define GTP_EXT_TEID 		16
#define GTP_EXT_TEID_CP 	17
#define GTP_EXT_TEID_II 	18
#define GTP_EXT_TEARD_IND	19
#define GTP_EXT_NSAPI 		20
#define GTP_EXT_RANAP		21
#define GTP_EXT_RABCONT		22
#define GTP_EXT_RAD_SMS		23
#define GTP_EXT_RP	 		24
#define GTP_EXT_PKT_F 		25
#define GTP_EXT_CHARG_CHRC	26
#define GTP_EXT_TRACE_REF	27
#define GTP_EXT_TRACE_TYPE	28
#define GTP_EXT_MS_NOT_RECH	29
#define GTP_EXT_CHARG_ID	127
#define GTP_EXT_USER_ADDR 	128
#define GTP_EXT_MM_CONTEXT	129
#define GTP_EXT_PDP_CONTEXT	130
#define GTP_EXT_APN			131
#define GTP_EXT_PROTO_CONF  132
#define GTP_EXT_GSN_ADDR 	133
#define GTP_EXT_MSISDN 		134
#define GTP_EXT_QOS			135
#define GTP_EXT_AUTH		136
#define GTP_EXT_TFT			137
#define GTP_EXT_TARGET_ID 	138 /* 3G */
#define GTP_EXT_UTRN		139
#define GTP_EXT_RAB			140
#define GTP_EXT_HEADER_T_L	141
#define GTP_EXT_TRIG_ID		142
#define GTP_EXT_OMC			143
#define GTP_EXT_SSGN_NO		147
#define GTP_EXT_COMMON_FLAG	148 /* Added by Debashis */
#define GTP_EXT_APN_RES		149 /* Added by Debashis */
#define GTP_EXT_RAT			151	/* Added by Debashis */
#define GTP_EXT_ULI			152	/* Added by Debashis */
#define GTP_EXT_TZ			153	/* Added by Debashis */
#define GTP_EXT_IMEI		154	/* Added by Debashis */
#define GTP_EXT_CHARGING	251
#define GTP_EXT_PRIV_EXT 	255


/*
 * cause message
 */
#define REQ_IMSI			"Request IMSI"
#define REQ_IMEI			"Request IMEI"
#define REQ_IMSI_IMEI		"Request IMSI and IMEI"
#define NO_ID_NEEDED		"No identity needed"
#define MS_REFUSE			"MS refuses"
#define	MS_NOT_RES			"MS is not GPRS responding"
#define REACTIVE_REQ		"Reactivation Requested"
#define PDP_ADDR_INACTV		"PDP address inactivity timer expires"
#define REQ_ACCEPTED		"Request accepted"
#define NEW_PDP_NP			"New PDP type due to network preference"
#define NEW_PDP_SAB			"New PDP type due to single address bearer only"
#define CDR_DECOD_ERR		"CDR decoding error"
#define NON_EXIST			"Non-existent"
#define INVALID_MSG_FORMAT	"Invalid message format"
#define	IMSI_UNKNOWN		"IMSI not known"
#define CONTXT_NOT_FOUND	"Context not found"
#define UNKNWN_PDP_ADDR		"Unknown PDP address or PDP type"
#define PDP_ACTIVE_WT_TFT	"PDP context without TFT already activated"
#define REQ_FULFILLED		"Request already fulfilled"
#define REQ_NOT_FULFILLED	"Request not fulfilled"

#define GTP_EXT_C1 0xC1
#define GTP_EXT_C2 0xC2

// ipv6 address len
//#define recordingFlag 40

#define COMPLETE	true
#define ONGOING		false
#define IPV4		4
#define	IPV6		6

const static int unknown_ie[11] = { 0, 6, 7, 10, 129, 130, 136, 138, 252, 253, 254 };

const static string RAT_TYPES[4] = {"NA", "UTRAN", "GERAN", "LTE" };

enum TIED_TYPE { CTL_UP = 0, CTL_DW =1, DATA_UP = 2, DATA_DW = 3, CTL = 4, DATA = 5};

const static string FLUSH_TYPE[41] =
{
		"UNKNOWN", 			//0
		"UNKNOWN", 			//1
		"UNKNOWN",			//2
		"UNKNOWN",			//3
		"UNKNOWN",			//4
		"UNKNOWN", 			//5
		"UNKNOWN", 			//6
		"UNKNOWN", 			//7
		"UNKNOWN", 			//8
		"UNKNOWN", 			//9
		"FLUSH_TYPE_CR_REQ_NO_TEID", 	//10
		"FLUSH_TYPE_CR_REQ_RESREQ", 	//11
		"FLUSH_TYPE_CR_REQ_DUP", 		//12
		"FLUSH_TYPE_CR_RES_NO_TEID",	//13
		"FLUSH_TYPE_CR_RES_REQRES",		//14
		"FLUSH_TYPE_CR_RES_DUP", 		//15
		"FLUSH_TYPE_CR_RES_NO_REQ", 	//16
		"UNKNOWN", 			//17
		"UNKNOWN", 			//18
		"UNKNOWN", 			//19
		"FLUSH_TYPE_UP_REQ_NO_TEID", 	//20
		"FLUSH_TYPE_UP_REQ_RESREQ", 	//21
		"FLUSH_TYPE_UP_REQ_DUP",		//22
		"FLUSH_TYPE_UP_RES_NO_TEID",	//23
		"FLUSH_TYPE_UP_RES_REQRES",		//24
		"FLUSH_TYPE_UP_RES_DUP", 		//25
		"FLUSH_TYPE_UP_RES_NO_REQ", 	//26
		"UNKNOWN", 			//27
		"UNKNOWN", 			//28
		"UNKNOWN", 			//29
		"FLUSH_TYPE_DL_REQ_NO_TEID", 	//30
		"FLUSH_TYPE_DL_REQ_RESREQ", 	//31
		"FLUSH_TYPE_DL_REQ_DUP",		//32
		"FLUSH_TYPE_DL_RES_NO_TEID",	//33
		"FLUSH_TYPE_DL_RES_REQRES",		//34
		"FLUSH_TYPE_DL_RES_DUP", 		//35
		"FLUSH_TYPE_DL_RES_NO_REQ", 	//36
		"UNKNOWN", 			//37
		"UNKNOWN", 			//38
		"UNKNOWN", 			//39
		"FLUSH_TYPE_CLEANUP" //40
};

const static string MSG_DESC[22] =
{
		"NA",	//0
		"NA",	//1
		"NA",	//2
		"NA",	//3
		"NA",	//4
		"NA",	//5
		"NA",	//6
		"NA",	//7
		"NA",	//8
		"NA",	//9
		"NA",	//10
		"NA",	//11
		"NA",	//12
		"NA",	//13
		"NA",	//14
		"NA",	//15
		"Create PDP Request",	//16
		"Create PDP Response",	//17
		"Update PDP Request",	//18
		"Update PDP Response",	//19
		"Delete PDP Request",	//20
		"Delete PDP Response"	//21
};

enum PROCEDURE_TYPE {
						PDPCREATE = 10,
						PDPUPDATE = 11,
						PDPDELETE = 12,
						CREATE1 = 0,
						UPDATE1 = 1,
						DELETE1 = 2,
						CREATE_SESSION = 3,
						UPDATE_SESSION = 4,
						DELETE_SESSION = 5,
						CREATE_BEARER = 6,
						UPDATE_BEARER = 7,
						MODIFY_BEARER = 8,
						DELETE_BEARER = 9
};

const static string MSG_DIRECTION[2] = {"SGSN<--GGSN", "SGSN-->GGSN"};
const static string MSG_DIRECTION_V2[2] = {"MME<--SGW", "SGW-->MME"};

const static string GTPC_CAUSE_CODE[256] = {
		"Request IMSI",	//0
		"Request IMEI",	//1
		"Request IMSI and IMEI",	//2
		"No identity needed",	//3
		"MS refuses",	//4
		"MS is not GPRS responding",	//5
		"Reactivation Requested",	//6
		"PDP address inactivity timer expires",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//10
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//20
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//30
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//40
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//50
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//60
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"Non-existent",	//4
		"Invalid Message Format",	//5
		"Version not supported by next peer",	//6
		"Invalid length",	//7
		"Service not supported",	//8
		" Mandatory IE incorrect",	//9
		"UNDEFINED",	//70
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//80
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//90
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//100
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//110
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//120
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"Request accepted",	//8
		"New PDP type due to network preference",	//9
		"New PDP type due to single address bearer only",	//130
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//140
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//150
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//160
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//170
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"CDR decoding error",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//180
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//190
		"UNDEFINED",	//1
		"Non-existent",	//2
		"Invalid message format",	//3
		"IMSI not known",	//4
		"MS is GPRS Detached",	//5
		"MS is not GPRS Responding",	//6
		"MS Refused",	//7
		"Version not supported",	//8
		"No resources available",	//9
		"Service not supported",	//200
		"Mandatory IE Incorrect",	//1
		"Mandatory IE Missing",	//2
		"Optional IE incorrect",	//3
		"System Failure",	//4
		"Roaming Restriction",	//5
		"P-TMSI Signature mismatch",	//6
		"GPRS connection suspended",	//7
		"Authentication failed",	//8
		"User authentication failed",	//9
		"Context not found",	//210
		"PDP addresses are occupied",	//1
		"No memory is available",	//2
		"Relocation failure",	//3
		"Unknown mandatory extension header",	//4
		"Semantic error in the TFT operation",	//5
		"Syntactic error in the TFT operation",	//6
		"Semantic errors in packet filter(s)",	//7
		"Syntactic errors in packet filter(s)",	//8
		"Missing or unknown APN",	//9
		"Unknown PDP address or PDP type",	//220
		"PDP context without TFT already activated",	//1
		"APN access denied – no subscription",	//2
		"APN Restriction type incompatibility with currently active PDP Contexts",	//3
		"MS MBMS Capabilities Insufficient",	//4
		"Invalid Correlation-ID",	//5
		"MBMS Bearer Context Superseded",	//6
		"Bearer Control Mode violation",	//7
		"Collision with network initiated request",	//8
		"APN Congestion",	//9
		"Bearer handling not supported",	//230
		"Target access restricted for the subscriber",	//1
		"UE is temporarily not reachable due to power saving",	//2
		"Relocation failure due to NAS message redirection",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//240
		//		241 – 251 (GTP’) Reserved for GPRS charging protocol use (see GTP’ in 3GPP TS 32.295)
		"UNDEFINED",	//1
		"UNDEFINED",	//2
		"UNDEFINED",	//3
		"UNDEFINED",	//4
		"UNDEFINED",	//5
		"UNDEFINED",	//6
		"UNDEFINED",	//7
		"UNDEFINED",	//8
		"UNDEFINED",	//9
		"UNDEFINED",	//250
		"UNDEFINED",	//1
		"Request related to possibly duplicated packets already fulfilled",	//2
		"Request already fulfilled",	//3
		"Sequence numbers of released/cancelled packets IE incorrect",	//4
		"Request not fulfilled"	//5


//		64 (GTPv2) Non-existent
//		65 (GTPv2) Invalid Message Format.
//		66 (GTPv2) Version not supported by next peer.t
//		67 (GTPv2) Invalid length.
//		68 (GTPv2) Service not supported
//		69 (GTPv2) Mandatory IE incorrect
//		70 (GTPv2) Mandatory IE missing
//		71 (GTPv2) Shall not be used.
//		72 (GTPv2) System failure
//		73 (GTPv2) No resources available
//		74 (GTPv2) Semantic error in the TFT operation
//		75 (GTPv2) Syntactic error in the TFT operation
//		76 (GTPv2) Semantic errors in packet filter(s)
//		77 (GTPv2) Syntactic errors in packet filter(s)
//		78 (GTPv2) Missing or unknown APN
//		79 (GTPv2) Shall not be used.
//		80 (GTPv2) GRE key not found.
//		81 (GTPv2) Relocation failure.
//		82 (GTPv2) Denied in RAT.
//		83 (GTPv2) Preferred PDN type not supported.
//		84 (GTPv2) All dynamic addresses are occupied.
//		85 (GTPv2) UE context without TFT already activated.
//		86 (GTPv2) Protocol type not supported.
//		87 (GTPv2) UE not responding.
//		88 (GTPv2) UE refuses.
//		89 (GTPv2) Service denied.
//		90 (GTPv2) Unable to page UE
//		91 (GTPv2) No memory available
//		92 (GTPv2) User authentication failed
//		93 (GTPv2) APN access denied – no subscription
//		94 (GTPv2) Request rejected (reason not specified)
//		95 (GTPv2) P-TMSI Signature mismatch
//		96 (GTPv2) IMSI/IMEI not known
//		97 (GTPv2) Semantic error in the TAD operation
//		98 (GTPv2) Syntactic error in the TAD operation
//		99 (GTPv2) Shall not be used
//		100 (GTPv2) Remote peer not responding
//		101 (GTPv2) Collision with network initiated request
//		102 (GTPv2) Unable to page UE due to Suspension
//		103 (GTPv2) Conditional IE missing
//		104 (GTPv2) APN Restriction type Incompatible with currently active PDN connection
//		105 (GTPv2) Invalid overall length of the triggered response message and a piggybacked initial message
//		106 (GTPv2) Data forwarding not supported
//		107 (GTPv2) Invalid reply from remote peer
//		108 (GTPv2) Fallback to GTPv1
//		109 (GTPv2) Invalid peer
//		110 (GTPv2) Temporarily rejected due to handover/TAU/RAU procedure in progress
//		111 (GTPv2) Modifications not limited to S1-U bearers
//		112 (GTPv2) Request rejected for a PMIPv6 reason
//		113 (GTPv2) APN Congestion
//		114 (GTPv2) Bearer handling not supported
//		115 (GTPv2) UE already re-attached
//		116 (GTPv2) Multiple PDN connections for a given APN not allowed
//		117 (GTPv2) Target access restricted for the subscriber
//		118 (GTPv2) Shall not be used
//		119 (GTPv2) MME/SGSN refuses due to VPLMN Policy
//		120 (GTPv2) GTP-C Entity Congestiony
//		121 (GTPv2) Late Overlapping Request
//		122 (GTPv2) Timed out Request
//		123 (GTPv2) UE is temporarily not reachable due to power saving
//		124 (GTPv2) Relocation failure due to NAS message redirection
//		125-239 (GTPv2) Spare
//		221 (GTPv1) PDP context without TFT already activated
//		222 (GTPv1) APN access denied – no subscription
//		223 (GTPv1) APN Restriction type incompatibility with currently active PDP Contexts
//		224 (GTPv1) MS MBMS Capabilities Insufficient
//		225 (GTPv1) Invalid Correlation-ID
//		226 (GTPv1) MBMS Bearer Context Superseded
//		227 (GTPv1) Bearer Control Mode violation
//		228 (GTPv1) Collision with network initiated request
//		229 (GTPv1) APN Congestion
//		230 (GTPv1) Bearer handling not supported
//		231 (GTPv1) Target access restricted for the subscriber
//		232 (GTPv1) UE is temporarily not reachable due to power saving
//		233 (GTPv1) Relocation failure due to NAS message redirection
//		234 – 240 (GTPv1) For future use
//		241 – 251 (GTP’) Reserved for GPRS charging protocol use (see GTP’ in 3GPP TS 32.295)
//		252 (GTP’) Request related to possibly duplicated packets already fulfilled
//		253 (GTP’) Request already fulfilled
//		254 (GTP’) Sequence numbers of released/cancelled packets IE incorrect
//		255 (GTP’) Request not fulfilled
};
enum GTPheaderType_e
{
	version0 = 0,
	version1 = 1,
	version2 = 2,
	gnunknown = 10
};

#define table_offset	0xFFF

/* change it for offset count */

#define octval		3

#define C_U				0x000
#define C_D				(1 << (octval*4 -2))
#define D_U				(2 << (octval*4 -2))
#define D_D				(3 << (octval*4 -2))
#define OFF_SET			(C_D -1)

// array index calculation based on tunnel id. MSB 2 bit for tied type
#define INDEX_CU(val)	(val & OFF_SET) | C_U
#define INDEX_CD(val)	(val & OFF_SET) | C_D
#define INDEX_DU(val)	(val & OFF_SET) | D_U
#define INDEX_DD(val)	(val & OFF_SET) | D_D

#define INDEX_TEID(val)	(val % GTP_GLB_SESSION_TEID_ARRAY_SIZE)

class ssgnkey {
  public:
    uint32_t  val1;
    uint32_t  val2;

    ssgnkey(uint32_t k1, uint32_t k2)
     : val1(k1), val2(k2) {}

    bool operator<(const ssgnkey &right) const
    {
		if ((right.val1 == val1 ) ||(right.val1 == 0 ) ||(0 == this->val1 ))
		{
			if ((right.val2 == 0 ) ||(0 == this->val2 ))
			{
				return false;
			}
			else
				return right.val2 < val2;
        }
        else
        {
           return right.val1 < val1;
        }
    }
};

struct ssgnkey_less : public std::binary_function<ssgnkey, ssgnkey, bool>
{
    bool
    operator()(const ssgnkey &mkey1, const ssgnkey &mkey2 ) const
    {
        return mkey1.operator<(mkey2); // mkey1 < mkey2;
    }
};

typedef struct _GTPGlbCounters
{
	int active_sessions_cnt;
	int total_sessions_cnt;

	int active_sessions_cnt_utran;
	int active_sessions_cnt_geran;
	int active_sessions_cnt_na;

	_GTPGlbCounters()
	{
		reset();
	}

	void reset()
	{
		active_sessions_cnt = 0;
		total_sessions_cnt = 0;

		active_sessions_cnt_utran = 0;
		active_sessions_cnt_geran = 0;
		active_sessions_cnt_na = 0;
	}

}GTPGlbCounters;

//typedef struct _gtpData
//{
//	string msisdn;
//	string imsi;
//	uint16_t rat;
//	string ratDesc;
//
//	_gtpData()
//	{
//		msisdn = "NULL";
//		imsi = "NULL";
//		rat = 0;
//		ratDesc = "NULL";
//	}
//}gtpData;

typedef struct _GTPSession{

//	uint8_t		frInterfaceIdReq;
//	uint8_t		frInterfaceIdRes;

	uint64_t 	StartTimeEpochSec;
	uint64_t 	EndTimeEpochSec;
	uint128_t 	StartTimeEpochNanoSec;
	uint128_t 	EndTimeEpochNanoSec;

	int			flushInstanceId;
	uint8_t		flushType;
	uint64_t 	FlushTimeEpochMicroSec;

	/* Ethernet Data */
	char		sgsnMACAddr[MAC_ADDR_LEN];
	char		ggsnMACAddr[MAC_ADDR_LEN];
	uint16_t	VLanId;

	uint16_t 	sgsnPort;
	uint16_t 	ggsnPort;
	uint32_t 	sgsnIPAddr;
	uint32_t 	ggsnIPAddr;

	uint8_t		GTPReqMsgId;
	uint8_t		GTPRspMsgId;
	int	 		EndCauseId;
	uint16_t 	ByteSizeUL;
	uint16_t 	ByteSizeDL;

	char 		SessionId[SESSION_ID_LEN];
	char 		IMSI[IMSI_LEN];
	char 		IMEI[IMEI_LEN];
	char 		MSISDN[MSISDN_LEN];
	char 		userIPAddress[IP_ADDR_LEN];

	char 		chargingGWAddr[IP_ADDR_LEN];
	char 		APN[APN_LEN];
	char		sgsnCtlIPAddr[IP_ADDR_LEN];
	char		sgsnDataIPAddr[IP_ADDR_LEN];
	char		ggsnCtlIPAddr[IP_ADDR_LEN];
	char		ggsnDataIPAddr[IP_ADDR_LEN];

	bool		dirSgsnGgsn;

	uint16_t 	MCC;
	uint16_t 	MNC;
	uint16_t 	LAC;
	uint16_t 	RAC;
	uint16_t 	CI;

	uint16_t 	RAT;
	uint16_t 	RATOld;

	uint16_t 	req_mbrupl;
	uint16_t 	req_mbrdnl;
	uint16_t 	res_mbrupl;
	uint16_t 	res_mbrdnl;
	uint16_t 	req_ext_mbrdnl;
	uint16_t 	res_ext_mbrdnl;
	uint16_t 	req_sequence_no;
	uint16_t 	res_sequence_no;

	uint32_t 	nsapi_val;
	uint32_t 	charging_Id;

	uint32_t 	pkt_tunnel_id_up;
	uint32_t 	pkt_tunnel_id_dn;
	uint32_t	tunnel_id_control_dn;
	uint32_t	tunnel_id_data_dn;
	uint32_t	tunnel_id_control_up;
	uint32_t	tunnel_id_data_up;

	bool		active_session;
	bool		expiredFlag;
	uint64_t	expiredTimeEpochSec;
	uint64_t	lastActivityTime;
	uint64_t	lastActivityTimeGtpc;
	uint64_t	lastActivityTimeGtpu;
	int			create_step;
	char 		IMSI_OLD[IMSI_LEN];
	int			SgsnId;
//	uint32_t	old_tunnel_id_control_dn;
//	uint32_t	old_tunnel_id_data_dn;
//	uint32_t	old_tunnel_id_control_up;
//	uint32_t	old_tunnel_id_data_up;
//	uint32_t 	old_sgsnIPAddr;
//	uint32_t 	old_ggsnIPAddr;
//	char		old_sgsnMACAddr[MAC_ADDR_LEN];
//	char		old_ggsnMACAddr[MAC_ADDR_LEN];
//	uint32_t 	old_sequence_no;
//	uint128_t 	old_StartTimeEpochNanoSec;

	_GTPSession()
	{
		reset();
	}

	void reset()
	{
//		frInterfaceIdReq = 0;
//		frInterfaceIdRes = 0;

		StartTimeEpochSec = 0;
		EndTimeEpochSec = 0;
		StartTimeEpochNanoSec = 0;
		EndTimeEpochNanoSec = 0;

		flushInstanceId = 0;
		flushType = 0;
		FlushTimeEpochMicroSec = 0;

		/* Ethernet Data */
		strcpy(sgsnMACAddr, "NA");
		strcpy(ggsnMACAddr, "NA");
		VLanId = 0;

		sgsnPort = 0;
		ggsnPort = 0;
		sgsnIPAddr = 0;
		ggsnIPAddr = 0;

		GTPReqMsgId = 0;
		GTPRspMsgId = 0;
	    EndCauseId = -1;
		ByteSizeUL = 0;
		ByteSizeDL = 0;

		strcpy(SessionId, "NA");
		strcpy(IMSI, "NA");
		strcpy(IMEI, "NA");
		strcpy(MSISDN, "NA");
		strcpy(userIPAddress, "NA");

		strcpy(chargingGWAddr, "NA");
		strcpy(APN, "NA");
		strcpy(sgsnCtlIPAddr, "NA");
		strcpy(sgsnDataIPAddr, "NA");
		strcpy(ggsnCtlIPAddr, "NA");
		strcpy(ggsnDataIPAddr, "NA");

		dirSgsnGgsn = false;

		MCC = 0;
		MNC = 0;
		LAC = 0;
		RAC = 0;
		CI = 0;

		RAT = 0;
		RATOld = 0;

		req_mbrupl = 0;
		req_mbrdnl = 0;
		res_mbrupl = 0;
		res_mbrdnl = 0;
		req_ext_mbrdnl = 0;
		res_ext_mbrdnl = 0;
		req_sequence_no = 0;
		res_sequence_no = 0;
		nsapi_val = 0;
		charging_Id = 0;

		pkt_tunnel_id_up = 0;
		pkt_tunnel_id_dn = 0;
		tunnel_id_control_dn = 0;
		tunnel_id_data_dn = 0;
		tunnel_id_control_up = 0;
		tunnel_id_data_up = 0;
		active_session = false;
//		deleteTimeEpochSec = 0;
		expiredFlag = false;
		expiredTimeEpochSec = 0;
		lastActivityTime = 0;
		lastActivityTimeGtpc = 0;
		lastActivityTimeGtpu = 0;
		create_step = 0;
		strcpy(IMSI_OLD, "NA");
		SgsnId = 0;
//		old_tunnel_id_control_dn = 0;
//		old_tunnel_id_data_dn = 0;
//		old_tunnel_id_control_up = 0;
//		old_tunnel_id_data_up = 0;
//		old_sgsnIPAddr = 0;
//		old_ggsnIPAddr = 0;
//		strcpy(old_sgsnMACAddr, "NA");
//		strcpy(old_ggsnMACAddr, "NA");
//		old_sequence_no = 0;
//		old_StartTimeEpochNanoSec = 0;
	}

	_GTPSession(const _GTPSession& obj)
	{
//		frInterfaceIdReq = obj.frInterfaceIdReq;
//		frInterfaceIdRes = obj.frInterfaceIdRes;

		StartTimeEpochSec = obj.StartTimeEpochSec;
		EndTimeEpochSec = obj.EndTimeEpochSec;
		StartTimeEpochNanoSec = obj.StartTimeEpochNanoSec;
		EndTimeEpochNanoSec = obj.EndTimeEpochNanoSec;

		flushInstanceId = obj.flushInstanceId;
		flushType = obj.flushType;
		FlushTimeEpochMicroSec = obj.FlushTimeEpochMicroSec;

		/* Ethernet Data */
		strcpy(sgsnMACAddr, obj.sgsnMACAddr);
		strcpy(ggsnMACAddr, obj.ggsnMACAddr);
		VLanId = obj.VLanId;

		sgsnPort = obj.sgsnPort;
		ggsnPort = obj.ggsnPort;
		sgsnIPAddr = obj.sgsnIPAddr;
		ggsnIPAddr = obj.ggsnIPAddr;

		GTPReqMsgId = obj.GTPReqMsgId;
		GTPRspMsgId = obj.GTPRspMsgId;
		EndCauseId = obj.EndCauseId;
		ByteSizeUL = obj.ByteSizeUL;
		ByteSizeDL = obj.ByteSizeDL;

		strcpy(SessionId, obj.SessionId);
		strcpy(IMSI, obj.IMSI);
		strcpy(IMEI, obj.IMEI);
		strcpy(MSISDN, obj.MSISDN);
		strcpy(userIPAddress, obj.userIPAddress);

		strcpy(chargingGWAddr, obj.chargingGWAddr);
		strcpy(APN, obj.APN);
		strcpy(sgsnCtlIPAddr, obj.sgsnCtlIPAddr);
		strcpy(sgsnDataIPAddr, obj.sgsnDataIPAddr);
		strcpy(ggsnCtlIPAddr, obj.ggsnCtlIPAddr);
		strcpy(ggsnDataIPAddr, obj.ggsnDataIPAddr);

		dirSgsnGgsn = obj.dirSgsnGgsn;

		MCC = obj.MCC;
		MNC = obj.MNC;
		LAC = obj.LAC;
		RAC = obj.RAC;
		CI = obj.CI;

		RAT = obj.RAT;
		RATOld = obj.RATOld;

		req_mbrupl = obj.req_mbrupl;
		req_mbrdnl = obj.req_mbrdnl;
		res_mbrupl = obj.res_mbrupl;
		res_mbrdnl = obj.res_mbrdnl;
		req_ext_mbrdnl = obj.req_ext_mbrdnl;
		res_ext_mbrdnl = obj.res_ext_mbrdnl;
		req_sequence_no = obj.req_sequence_no;
		res_sequence_no = obj.res_sequence_no;
//		sequenceFlag = obj.sequenceFlag;
		nsapi_val = obj.nsapi_val;
		charging_Id = obj.charging_Id;

		pkt_tunnel_id_up = obj.pkt_tunnel_id_up;
		pkt_tunnel_id_dn = obj.pkt_tunnel_id_dn;
		tunnel_id_control_dn = obj.tunnel_id_control_dn;
		tunnel_id_data_dn = obj.tunnel_id_data_dn;
		tunnel_id_control_up = obj.tunnel_id_control_up;
		tunnel_id_data_up = obj.tunnel_id_data_up;

		active_session = obj.active_session;
//		deleteTimeEpochSec = obj.deleteTimeEpochSec;
		expiredFlag = obj.expiredFlag;
		expiredTimeEpochSec = obj.expiredTimeEpochSec;
		lastActivityTime = obj.lastActivityTime;
		lastActivityTimeGtpc = obj.lastActivityTimeGtpc;
		lastActivityTimeGtpu = obj.lastActivityTimeGtpu;
		create_step = obj.create_step;
		strcpy(IMSI_OLD, obj.IMSI_OLD);
		SgsnId = obj.SgsnId;
//		old_tunnel_id_control_dn = obj.old_tunnel_id_control_dn;
//		old_tunnel_id_data_dn = obj.old_tunnel_id_data_dn;
//		old_tunnel_id_control_up = obj.old_tunnel_id_control_up;
//		old_tunnel_id_data_up = obj.old_tunnel_id_data_up;
//		old_sgsnIPAddr = obj.old_sgsnIPAddr;
//		old_ggsnIPAddr = obj.old_ggsnIPAddr;
//		strcpy(old_sgsnMACAddr, obj.old_sgsnMACAddr);
//		strcpy(old_ggsnMACAddr, obj.old_ggsnMACAddr);
//		old_sequence_no = obj.old_sequence_no;
//		old_StartTimeEpochNanoSec = obj.old_StartTimeEpochNanoSec;
	}

	void copy(const _GTPSession* obj)
	{
//		frInterfaceIdReq = obj->frInterfaceIdReq;
//		frInterfaceIdRes = obj->frInterfaceIdRes;

		StartTimeEpochSec = obj->StartTimeEpochSec;
		EndTimeEpochSec = obj->EndTimeEpochSec;
		StartTimeEpochNanoSec = obj->StartTimeEpochNanoSec;
		EndTimeEpochNanoSec = obj->EndTimeEpochNanoSec;

		flushInstanceId = obj->flushInstanceId;
		flushType = obj->flushType;
		FlushTimeEpochMicroSec = obj->FlushTimeEpochMicroSec;

		/* Ethernet Data */
		strcpy(sgsnMACAddr, obj->sgsnMACAddr);
		strcpy(ggsnMACAddr, obj->ggsnMACAddr);
		VLanId = obj->VLanId;

		sgsnPort = obj->sgsnPort;
		ggsnPort = obj->ggsnPort;
		sgsnIPAddr = obj->sgsnIPAddr;
		ggsnIPAddr = obj->ggsnIPAddr;

		GTPReqMsgId = obj->GTPReqMsgId;
		GTPRspMsgId = obj->GTPRspMsgId;
		EndCauseId = obj->EndCauseId;
		ByteSizeUL = obj->ByteSizeUL;
		ByteSizeDL = obj->ByteSizeDL;

		strcpy(SessionId, obj->SessionId);
		strcpy(IMSI, obj->IMSI);
		strcpy(IMEI, obj->IMEI);
		strcpy(MSISDN, obj->MSISDN);
		strcpy(userIPAddress, obj->userIPAddress);

		strcpy(chargingGWAddr, obj->chargingGWAddr);
		strcpy(APN, obj->APN);
		strcpy(sgsnCtlIPAddr, obj->sgsnCtlIPAddr);
		strcpy(sgsnDataIPAddr, obj->sgsnDataIPAddr);
		strcpy(ggsnCtlIPAddr, obj->ggsnCtlIPAddr);
		strcpy(ggsnDataIPAddr, obj->ggsnDataIPAddr);

		dirSgsnGgsn = obj->dirSgsnGgsn;

		MCC = obj->MCC;
		MNC = obj->MNC;
		LAC = obj->LAC;
		RAC = obj->RAC;
		CI = obj->CI;

		RAT = obj->RAT;
		RATOld = obj->RATOld;

		req_mbrupl = obj->req_mbrupl;
		req_mbrdnl = obj->req_mbrdnl;
		res_mbrupl = obj->res_mbrupl;
		res_mbrdnl = obj->res_mbrdnl;
		req_ext_mbrdnl = obj->req_ext_mbrdnl;
		res_ext_mbrdnl = obj->res_ext_mbrdnl;
		req_sequence_no = obj->req_sequence_no;
		res_sequence_no = obj->res_sequence_no;

//		sequenceFlag = obj->sequenceFlag;
		nsapi_val = obj->nsapi_val;
		charging_Id = obj->charging_Id;

		pkt_tunnel_id_up = obj->pkt_tunnel_id_up;
		pkt_tunnel_id_dn = obj->pkt_tunnel_id_dn;
		tunnel_id_control_dn = obj->tunnel_id_control_dn;
		tunnel_id_data_dn = obj->tunnel_id_data_dn;
		tunnel_id_control_up = obj->tunnel_id_control_up;
		tunnel_id_data_up = obj->tunnel_id_data_up;

		active_session = obj->active_session;
//		deleteTimeEpochSec = obj->deleteTimeEpochSec;
		expiredFlag = obj->expiredFlag;
		expiredTimeEpochSec = obj->expiredTimeEpochSec;
		lastActivityTime = obj->lastActivityTime;
		lastActivityTimeGtpc = obj->lastActivityTimeGtpc;
		lastActivityTimeGtpu = obj->lastActivityTimeGtpu;
		create_step = obj->create_step;
		strcpy(IMSI_OLD, obj->IMSI_OLD);
		SgsnId = obj->SgsnId;
//		old_tunnel_id_control_dn = obj->old_tunnel_id_control_dn;
//		old_tunnel_id_data_dn = obj->old_tunnel_id_data_dn;
//		old_tunnel_id_control_up = obj->old_tunnel_id_control_up;
//		old_tunnel_id_data_up = obj->old_tunnel_id_data_up;
//		old_sgsnIPAddr = obj->old_sgsnIPAddr;
//		old_ggsnIPAddr = obj->old_ggsnIPAddr;
//		strcpy(old_sgsnMACAddr, obj->old_sgsnMACAddr);
//		strcpy(old_ggsnMACAddr, obj->old_ggsnMACAddr);
//		old_sequence_no = obj->old_sequence_no;
//		old_StartTimeEpochNanoSec = obj->old_StartTimeEpochNanoSec;

	}

	void operator=(const _GTPSession& obj)
	{
//		frInterfaceIdReq = obj.frInterfaceIdReq;
//		frInterfaceIdRes = obj.frInterfaceIdRes;

		StartTimeEpochSec = obj.StartTimeEpochSec;
		EndTimeEpochSec = obj.EndTimeEpochSec;
		StartTimeEpochNanoSec = obj.StartTimeEpochNanoSec;
		EndTimeEpochNanoSec = obj.EndTimeEpochNanoSec;

		flushInstanceId = obj.flushInstanceId;
		flushType = obj.flushType;
		FlushTimeEpochMicroSec = obj.FlushTimeEpochMicroSec;

		/* Ethernet Data */
		strcpy(sgsnMACAddr, obj.sgsnMACAddr);
		strcpy(ggsnMACAddr, obj.ggsnMACAddr);
		VLanId = obj.VLanId;

		sgsnPort = obj.sgsnPort;
		ggsnPort = obj.ggsnPort;
		sgsnIPAddr = obj.sgsnIPAddr;
		ggsnIPAddr = obj.ggsnIPAddr;

		GTPReqMsgId = obj.GTPReqMsgId;
		GTPRspMsgId = obj.GTPRspMsgId;
		EndCauseId = obj.EndCauseId;
		ByteSizeUL = obj.ByteSizeUL;
		ByteSizeDL = obj.ByteSizeDL;

		strcpy(SessionId, obj.SessionId);
		strcpy(IMSI, obj.IMSI);
		strcpy(IMEI, obj.IMEI);
		strcpy(MSISDN, obj.MSISDN);
		strcpy(userIPAddress, obj.userIPAddress);

		strcpy(chargingGWAddr, obj.chargingGWAddr);
		strcpy(APN, obj.APN);
		strcpy(sgsnCtlIPAddr, obj.sgsnCtlIPAddr);
		strcpy(sgsnDataIPAddr, obj.sgsnDataIPAddr);
		strcpy(ggsnCtlIPAddr, obj.ggsnCtlIPAddr);
		strcpy(ggsnDataIPAddr, obj.ggsnDataIPAddr);

		dirSgsnGgsn = obj.dirSgsnGgsn;

		MCC = obj.MCC;
		MNC = obj.MNC;
		LAC = obj.LAC;
		RAC = obj.RAC;
		CI = obj.CI;

		RAT = obj.RAT;
		RATOld = obj.RATOld;

		req_mbrupl = obj.req_mbrupl;
		req_mbrdnl = obj.req_mbrdnl;
		res_mbrupl = obj.res_mbrupl;
		res_mbrdnl = obj.res_mbrdnl;
		req_ext_mbrdnl = obj.req_ext_mbrdnl;
		res_ext_mbrdnl = obj.res_ext_mbrdnl;
		req_sequence_no = obj.req_sequence_no;
		res_sequence_no = obj.res_sequence_no;

//		sequenceFlag = obj.sequenceFlag;
		nsapi_val = obj.nsapi_val;
		charging_Id = obj.charging_Id;

		pkt_tunnel_id_up = obj.pkt_tunnel_id_up;
		pkt_tunnel_id_dn = obj.pkt_tunnel_id_dn;
		tunnel_id_control_dn = obj.tunnel_id_control_dn;
		tunnel_id_data_dn = obj.tunnel_id_data_dn;
		tunnel_id_control_up = obj.tunnel_id_control_up;
		tunnel_id_data_up = obj.tunnel_id_data_up;

		active_session = obj.active_session;
//		deleteTimeEpochSec = obj.deleteTimeEpochSec;
		expiredFlag = obj.expiredFlag;
		expiredTimeEpochSec = obj.expiredTimeEpochSec;
		lastActivityTime = obj.lastActivityTime;
		lastActivityTimeGtpc = obj.lastActivityTimeGtpc;
		lastActivityTimeGtpu = obj.lastActivityTimeGtpu;
		create_step = obj.create_step;
		strcpy(IMSI_OLD, obj.IMSI_OLD);
		SgsnId = obj.SgsnId;
//		old_tunnel_id_control_dn = obj.old_tunnel_id_control_dn;
//		old_tunnel_id_data_dn = obj.old_tunnel_id_data_dn;
//		old_tunnel_id_control_up = obj.old_tunnel_id_control_up;
//		old_tunnel_id_data_up = obj.old_tunnel_id_data_up;
//		old_sgsnIPAddr = obj.old_sgsnIPAddr;
//		old_ggsnIPAddr = obj.old_ggsnIPAddr;
//		strcpy(old_sgsnMACAddr, obj.old_sgsnMACAddr);
//		strcpy(old_ggsnMACAddr, obj.old_ggsnMACAddr);
//		old_sequence_no = obj.old_sequence_no;
//		old_StartTimeEpochNanoSec = obj.old_StartTimeEpochNanoSec;
	}

}GTPSession;


namespace GTPFlushMap {
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_0;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_1;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_2;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_3;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_4;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_5;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_6;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_7;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_8;
	extern std::map<ULONG, GTPSession> gtpEndSessionMap_9;

	extern 	ULONG gtpEndSessionMAPCounter_0;
	extern 	ULONG gtpEndSessionMAPCounter_1;
	extern 	ULONG gtpEndSessionMAPCounter_2;
	extern 	ULONG gtpEndSessionMAPCounter_3;
	extern 	ULONG gtpEndSessionMAPCounter_4;
	extern 	ULONG gtpEndSessionMAPCounter_5;
	extern 	ULONG gtpEndSessionMAPCounter_6;
	extern 	ULONG gtpEndSessionMAPCounter_7;
	extern 	ULONG gtpEndSessionMAPCounter_8;
	extern 	ULONG gtpEndSessionMAPCounter_9;
}

typedef struct _teid
{
	uint32_t tunnel_id_control_up;
	uint32_t tunnel_id_control_dn;
	uint32_t tunnel_id_data_up;
	uint32_t tunnel_id_data_dn;
}teid;

typedef struct _cleanUpTeidData
{
	int index;
	uint32_t tunnel_id;
}cleanUpTeidData;

typedef struct _GTPUserInfo
{
	string 		imsi;
	string 		msisdn;
	string 		imei;
	uint16_t 	rat;
	string 		ratDesc;
	uint16_t 	MCC;
	uint16_t 	MNC;
	uint16_t 	LAC;
	uint16_t 	CI;
	BOOL		activeState;
	int			teidLookUpMap;

	_GTPUserInfo()
	{ reset(); }

	void reset()
	{
		imsi = "NA";
		msisdn = "NA";
		imei = "NA";
		rat = 0;
		ratDesc = "NA";
		MCC = 0;
		MNC = 0;
		LAC = 0;
		CI = 0;
		activeState = false;
		teidLookUpMap = 0;
	}
}GTPUserInfo;


typedef std::map<std::string, teid> IMSITeidMap;
typedef std::map<uint32_t, IMSITeidMap> IMSITeidMapList;

class GTPGlobal
{
	public:
			int getGtcpFlushMapSize();
			int getGtcpV2FlushMapSize();
};

/*
 * ** GTP V2 Declaration
 */

typedef struct _GTPV2Session{
	BOOL		direction;
	ULONG 		StartTimeEpochNanoSec;
	ULONG 		EndTimeEpochNanoSec;
	uint32_t 	VLANId;
	uint32_t 	s_port;
	uint32_t 	d_port;
	uint32_t	GTPReqMsgId;
	uint32_t	GTPRspMsgId;

	string		GTPReqMsgDesc;
	string		GTPRspMsgDesc;

	uint32_t 	ByteSizeUL;
	uint32_t 	ByteSizeDL;

	ULONG		reqPacketNo;
	ULONG		rspPacketNo;

	string		interfaceName;
	string 		SessionId;
	string 		StartTime;
	string 		EndTime;
	string 		s_addr_mac;
	string 		d_addr_mac;
	string 		sourceAddr;
	string 		destAddr;

	uint8_t 	msgType;
	uint8_t 	m_flags;
	ULONG 		sequence_no;
	ULONG 		pkt_tunnel_id;

	ULONG 		rec_tunnel_id;
	ULONG 		trans_tunnel_id;
	uint32_t 	bearer_recv_t_id;
	uint32_t 	bearer_trans_t_id;

	string 		routing_area_info;
	string 		imsi;
	string 		apn_info;
	string 		msisdn;
	string 		imei;
	string 		serving_network;
	string 		user_location;

	string 		ipv4_address;
	string 		ipv6_address;

	string 		ipv4_add_recv;
	string 		ipv4_add_trans;
	string 		ipv6_add_recv;
	string 		ipv6_add_trans;

	string 		STN_SR;
	string 		end_user_address;
	string	 	gsn;
//	string 		gsn_ipv6;
	string		selection_mode;
	string 		ppa_addr_location;
	string 		TAD_info;
	string 		tmsi_info;
	string 		global_cnid_str;
	string 		trace_mnc_mcc;
	string 		pdn_type;
	string 		p_tmsi_sig;
	string 		trace_id;
	string 		guti_mnc_mcc;
	string 		plmn_id;
	string 		rat_type;
	string 		ldn_value;
	string 		relay_type;
	string 		relay_name;
	string 		twan_ssid;
	string 		twan_bssid;
	string 		twan_name;
	string 		twan_cai;

	uint8_t 	cause_val;
	string		cause_desc;

	uint8_t 	MME_interfaceType;
	ULONG 		MME_tunnelId;
	string		MME_ip;

	uint8_t 	PGW_interfaceType;
	ULONG 		PGW_tunnelId;
	string		PGW_ip;

	uint8_t 	SGW_interfaceType;
	ULONG 		SGW_tunnelId;
	string		SGW_ip;

	uint32_t 	counter_val;
	uint32_t 	ulink_bit_rate;
	uint32_t 	dlink_bit_rate;
	uint16_t	cn_id;
	uint16_t 	charging_id;
	uint8_t 	procedure_transt_id;
	uint32_t 	p_tmsi;
	uint8_t 	day_light_saving_time;
	uint8_t 	time_zone;
	uint16_t 	user_grp_id;
	uint8_t 	mme_code;
	uint16_t 	dl_gtpu_seq_no;
	uint16_t 	ul_gtpu_seq_no;
	uint16_t 	dl_pdcp_seq_no;
	uint16_t 	ul_pdcp_seq_no;
	uint8_t 	nsapi_val;
	uint16_t 	port_no;
	uint32_t	twan_plmni_id;

	BOOL 		bearer_recv;
	BOOL 		bearer_trans;

	_GTPV2Session()
	{ reset(); }

	void reset()
	{
		direction = false;
		StartTimeEpochNanoSec = 0;
		EndTimeEpochNanoSec = 0;
		VLANId = 0;
		s_port = 0;
		d_port = 0;
		GTPReqMsgId = 0;
		GTPRspMsgId = 0;
		GTPReqMsgDesc = "NA";
		GTPRspMsgDesc = "NA";
		ByteSizeUL = 0;
		ByteSizeDL = 0;

		reqPacketNo = 0;
		rspPacketNo = 0;

		interfaceName.assign("NA");
		SessionId.assign("NA");
		StartTime.assign("NA");
		EndTime.assign("NA");
		s_addr_mac.assign("NA");
		d_addr_mac.assign("NA");
		sourceAddr.assign("NA");
		destAddr.assign("NA");

		msgType = 0;
		m_flags = 0;
		sequence_no = 0;
		pkt_tunnel_id = 0;

		rec_tunnel_id = 0;
		trans_tunnel_id = 0;
		bearer_recv_t_id = 0;
		bearer_trans_t_id = 0;

		routing_area_info.assign("NA");
		imsi.assign("NA");
		apn_info.assign("NA");
		msisdn.assign("NA");
		imei.assign("NA");
		serving_network.assign("NA");
		user_location.assign("NA");

		ipv4_address.assign("NA");
		ipv6_address.assign("NA");

		ipv4_add_recv.assign("NA");
		ipv4_add_trans.assign("NA");
		ipv6_add_recv.assign("NA");
		ipv6_add_trans.assign("NA");

		STN_SR.assign("NA");
		end_user_address.assign("NA");
		gsn.assign("NA");
//		gsn_ipv6.assign("NA");
		selection_mode.assign("NA");
		ppa_addr_location.assign("NA");
		TAD_info.assign("NA");
		tmsi_info.assign("NA");
		global_cnid_str.assign("NA");
		trace_mnc_mcc.assign("NA");
		pdn_type.assign("NA");
		p_tmsi_sig.assign("NA");
		trace_id.assign("NA");
		guti_mnc_mcc.assign("NA");
		plmn_id.assign("NA");
		rat_type.assign("NA");
		ldn_value.assign("NA");
		relay_type.assign("NA");
		relay_name.assign("NA");
		twan_ssid.assign("NA");
		twan_bssid.assign("NA");
		twan_name.assign("NA");
		twan_cai.assign("NA");

		cause_val = 0;
		cause_desc.assign("NA");
		MME_interfaceType = 0;
		MME_tunnelId = 0;
		MME_ip = "NA";

		PGW_interfaceType = 0;
		PGW_tunnelId = 0;
		PGW_ip = "NA";

		SGW_interfaceType = 0;
		SGW_tunnelId = 0;
		SGW_ip = "NA";
		counter_val = 0;
		ulink_bit_rate = 0;
		dlink_bit_rate = 0;
		cn_id = 0;
		charging_id = 0;
		procedure_transt_id = 0;
		p_tmsi = 0;
		day_light_saving_time = 0;
		time_zone = 0;
		user_grp_id = 0;
		mme_code = 0;
		dl_gtpu_seq_no = 0;
		ul_gtpu_seq_no = 0;
		dl_pdcp_seq_no = 0;
		ul_pdcp_seq_no = 0;
		nsapi_val = 0;
		port_no = 0;
		twan_plmni_id = 0;

		bearer_recv = false;
		bearer_trans = false;
	}

	void set (const _GTPV2Session *obj)
	{
		this->direction = obj->direction;
		this->StartTimeEpochNanoSec = obj->StartTimeEpochNanoSec;
		this->EndTimeEpochNanoSec = obj->EndTimeEpochNanoSec;
		this->VLANId = obj->VLANId;
		this->s_port = obj->s_port;
		this->d_port = obj->d_port;
		this->GTPReqMsgId = obj->GTPReqMsgId;
		this->GTPRspMsgId = obj->GTPRspMsgId;

		this->ByteSizeUL = obj->ByteSizeUL;
		this->ByteSizeDL = obj->ByteSizeDL;

		this->reqPacketNo = obj->reqPacketNo;
		this->rspPacketNo = obj->rspPacketNo;

		this->interfaceName = obj->interfaceName;
		this->SessionId = obj->SessionId;
		this->StartTime = obj->StartTime;
		this->EndTime = obj->EndTime;
		this->s_addr_mac = obj->s_addr_mac;
		this->d_addr_mac = obj->d_addr_mac;
		this->sourceAddr = obj->sourceAddr;
		this->destAddr = obj->destAddr;

		this->msgType = obj->msgType;
		this->m_flags = obj->m_flags;
		this->sequence_no = obj->sequence_no;
		this->pkt_tunnel_id = obj->pkt_tunnel_id;

		this->rec_tunnel_id = obj->rec_tunnel_id;
		this->trans_tunnel_id = obj->trans_tunnel_id;
		this->bearer_recv_t_id = obj->bearer_recv_t_id;
		this->bearer_trans_t_id = obj->bearer_recv_t_id;

		this->routing_area_info = obj->routing_area_info;
		this->imsi = obj->imsi;
		this->apn_info = obj->apn_info;
		this->msisdn = obj->msisdn;
		this->imei = obj->imei;
		this->serving_network = obj->serving_network;
		this->user_location = obj->user_location;

		this->ipv4_address = obj->ipv4_address;
		this->ipv6_address = obj->ipv6_address;

		this->ipv4_add_recv = obj->ipv4_add_recv;
		this->ipv4_add_trans = obj->ipv4_add_trans;
		this->ipv6_add_recv = obj->ipv6_add_recv;
		this->ipv6_add_trans = obj->ipv6_add_trans;

		this->STN_SR = obj->STN_SR;
		this->end_user_address = obj->end_user_address;
		this->gsn = obj->gsn;
//		this->gsn_ipv6 = obj->gsn_ipv6;
		this->selection_mode = obj->selection_mode;
		this->ppa_addr_location = obj->ppa_addr_location;
		this->TAD_info = obj->TAD_info;
		this->tmsi_info = obj->tmsi_info;
		this->global_cnid_str = obj->global_cnid_str;
		this->trace_mnc_mcc = obj->trace_mnc_mcc;
		this->pdn_type = obj->pdn_type;
		this->p_tmsi_sig = obj->p_tmsi_sig;
		this->trace_id = obj->trace_id;
		this->guti_mnc_mcc = obj->guti_mnc_mcc;
		this->plmn_id = obj->plmn_id;
		this->rat_type = obj->rat_type;
		this->ldn_value = obj->ldn_value;
		this->relay_type = obj->relay_type;
		this->relay_name = obj->relay_name;
		this->twan_ssid = obj->twan_ssid;
		this->twan_bssid = obj->twan_bssid;
		this->twan_name = obj->twan_name;
		this->twan_cai = obj->twan_cai;

		this->cause_val = obj->cause_val;
		this->cause_desc = obj->cause_desc;

		this->MME_interfaceType = obj->MME_interfaceType;
		this->MME_tunnelId = obj->MME_tunnelId;
		this->MME_ip = obj->MME_ip;

		this->PGW_interfaceType = obj->PGW_interfaceType;
		this->PGW_tunnelId = obj->PGW_tunnelId;
		this->PGW_ip = obj->PGW_ip;

		this->SGW_interfaceType = obj->SGW_interfaceType;
		this->SGW_tunnelId = obj->SGW_tunnelId;
		this->SGW_ip = obj->SGW_ip;

		this->counter_val = obj->counter_val;
		this->ulink_bit_rate = obj->ulink_bit_rate;
		this->dlink_bit_rate = obj->dlink_bit_rate;
		this->cn_id = obj->cn_id;
		this->charging_id = obj->charging_id;
		this->procedure_transt_id = obj->procedure_transt_id;
		this->p_tmsi = obj->p_tmsi;
		this->day_light_saving_time = obj->day_light_saving_time;
		this->time_zone = obj->time_zone;
		this->user_grp_id = obj->user_grp_id;
		this->mme_code = obj->mme_code;
		this->dl_gtpu_seq_no = obj->dl_gtpu_seq_no;
		this->ul_gtpu_seq_no = obj->ul_gtpu_seq_no;
		this->dl_pdcp_seq_no = obj->dl_pdcp_seq_no;
		this->ul_pdcp_seq_no = obj->ul_pdcp_seq_no;
		this->nsapi_val = obj->nsapi_val;
		this->port_no = obj->port_no;
		this->twan_plmni_id = obj->twan_plmni_id;

		this->bearer_recv = obj->bearer_recv;
		this->bearer_trans = obj->bearer_trans;
	}
}GTPV2Session;

typedef struct controlpacketV2
{
	bool		direction;
	ULONG 		StartTimeEpochNanoSec;
	ULONG 		EndTimeEpochNanoSec;
	uint32_t 	VLANId;
	uint32_t 	s_port;
	uint32_t 	d_port;
	uint32_t	GTPReqMsgId;
	uint32_t	GTPRspMsgId;
	string		GTPReqMsgDesc;
	string		GTPRspMsgDesc;

	uint32_t 	EndCauseId;
	uint32_t 	ByteSizeUL;
	uint32_t 	ByteSizeDL;

	ULONG		reqPacketNo;
	ULONG		rspPacketNo;

	string		interfaceName;
	string 		SessionId;
	string 		StartTime;
	string 		EndTime;
	string 		s_addr_mac;
	string 		d_addr_mac;
	string 		sourceAddr;
	string 		destAddr;

	uint8_t 	msgType;
	uint8_t 	m_flags;
	ULONG 		sequence_no;
	ULONG 		pkt_tunnel_id;

	uint32_t 	rec_tunnel_id;
	uint32_t 	trans_tunnel_id;
	uint32_t 	bearer_recv_t_id;
	uint32_t 	bearer_trans_t_id;

	string 		routing_area_info;
	string 		imsi;
	string 		apn_info;
	string 		msisdn;
	string 		imei;
	string 		serving_network;
	string 		user_location;

	string 		ipv4_address;
	string 		ipv6_address;

	string 		ipv4_add_recv;
	string 		ipv4_add_trans;
	string 		ipv6_add_recv;
	string 		ipv6_add_trans;

	string 		STN_SR;
	string 		end_user_address;
	string	 	gsn;
//	string 		gsn_ipv6;
	string		selection_mode;
	string 		ppa_addr_location;
	string 		TAD_info;
	string 		tmsi_info;
	string 		global_cnid_str;
	string 		trace_mnc_mcc;
	string 		pdn_type;
	string 		p_tmsi_sig;
	string 		trace_id;
	string 		guti_mnc_mcc;
	string 		plmn_id;
	string 		rat_type;
	string 		ldn_value;
	string 		relay_type;
	string 		relay_name;
	string 		twan_ssid;
	string 		twan_bssid;
	string 		twan_name;
	string 		twan_cai;

	uint8_t 	cause_val;
	string		cause_desc;

	uint8_t 	MME_interfaceType;
	ULONG 		MME_tunnelId;
	string		MME_ip;

	uint8_t 	PGW_interfaceType;
	ULONG 		PGW_tunnelId;
	string		PGW_ip;

	uint8_t 	SGW_interfaceType;
	ULONG 		SGW_tunnelId;
	string		SGW_ip;

	uint32_t 	counter_val;
	uint32_t 	ulink_bit_rate;
	uint32_t 	dlink_bit_rate;
	uint16_t	cn_id;
	uint16_t 	charging_id;
	uint8_t 	procedure_transt_id;
	uint32_t 	p_tmsi;
	uint8_t 	day_light_saving_time;
	uint8_t 	time_zone;
	uint16_t 	user_grp_id;
	uint8_t 	mme_code;
	uint16_t 	dl_gtpu_seq_no;
	uint16_t 	ul_gtpu_seq_no;
	uint16_t 	dl_pdcp_seq_no;
	uint16_t 	ul_pdcp_seq_no;
	uint8_t 	nsapi_val;
	uint16_t 	port_no;
	uint32_t	twan_plmni_id;

	BOOL 		bearer_recv;
	BOOL 		bearer_trans;
}*pcontrolpacketV2;


namespace GTPStore {
	extern long allocatedCnt;
	extern long deallocatedCnt;
	extern int freeGlbBitPos;
	extern int freeGlbBitPosMax;
	extern std::bitset<GTP_GLB_SESSION_POOL_ARRAY_ELEMENTS> bitFlags[GTP_GLB_SESSION_POOL_ARRAY_SIZE];
	extern std::map<int, GTPSession*> GTPGlbSession[GTP_GLB_SESSION_POOL_ARRAY_SIZE];

	extern std::map<uint32_t, int> GTPGlbMap_CTL_UP[GTP_GLB_SESSION_TEID_ARRAY_SIZE];
	extern std::map<uint32_t, int> GTPGlbMap_CTL_DW[GTP_GLB_SESSION_TEID_ARRAY_SIZE];
	extern std::map<uint32_t, int> GTPGlbMap_DATA_UP[GTP_GLB_SESSION_TEID_ARRAY_SIZE];
	extern std::map<uint32_t, int> GTPGlbMap_DATA_DW[GTP_GLB_SESSION_TEID_ARRAY_SIZE];

	extern std::map<uint32_t, GTPSession> GTPGlbMap_LKU_DATA_UP[GTP_GLB_SESSION_TEID_ARRAY_SIZE];
	extern std::map<uint32_t, GTPSession> GTPGlbMap_LKU_DATA_DW[GTP_GLB_SESSION_TEID_ARRAY_SIZE];

//	extern std::vector<GTPSession> GTPGlbMap_DL_DATA_UP;

//	extern std::map<uint32_t, GTPSession> GTPGlbMap_DL_DATA_UP[GTP_GLB_SESSION_TEID_ARRAY_SIZE];
//	extern std::map<uint32_t, GTPSession> GTPGlbMap_DL_DATA_DW[GTP_GLB_SESSION_TEID_ARRAY_SIZE];


	extern std::map<std::string, int> GTPGlb_IMSI_MAP;
}

namespace GTPSMStore {

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_0_t_9;
	extern bool gtp_msg_sm_0_i_0_r_0_t_0_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_1_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_2_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_3_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_4_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_5_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_6_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_7_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_8_busy;
	extern bool gtp_msg_sm_0_i_0_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_1_t_9;
	extern bool gtp_msg_sm_0_i_0_r_1_t_0_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_1_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_2_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_3_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_4_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_5_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_6_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_7_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_8_busy;
	extern bool gtp_msg_sm_0_i_0_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_2_t_9;
	extern bool gtp_msg_sm_0_i_0_r_2_t_0_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_1_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_2_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_3_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_4_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_5_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_6_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_7_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_8_busy;
	extern bool gtp_msg_sm_0_i_0_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_0_r_3_t_9;
	extern bool gtp_msg_sm_0_i_0_r_3_t_0_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_1_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_2_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_3_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_4_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_5_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_6_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_7_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_8_busy;
	extern bool gtp_msg_sm_0_i_0_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_0_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_0_t_9;
	extern bool gtp_msg_sm_1_i_0_r_0_t_0_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_1_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_2_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_3_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_4_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_5_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_6_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_7_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_8_busy;
	extern bool gtp_msg_sm_1_i_0_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_1_t_9;
	extern bool gtp_msg_sm_1_i_0_r_1_t_0_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_1_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_2_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_3_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_4_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_5_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_6_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_7_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_8_busy;
	extern bool gtp_msg_sm_1_i_0_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_2_t_9;
	extern bool gtp_msg_sm_1_i_0_r_2_t_0_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_1_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_2_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_3_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_4_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_5_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_6_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_7_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_8_busy;
	extern bool gtp_msg_sm_1_i_0_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_0_r_3_t_9;
	extern bool gtp_msg_sm_1_i_0_r_3_t_0_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_1_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_2_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_3_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_4_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_5_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_6_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_7_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_8_busy;
	extern bool gtp_msg_sm_1_i_0_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_0_r_3_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_0_t_9;
	extern bool gtp_msg_sm_2_i_0_r_0_t_0_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_1_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_2_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_3_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_4_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_5_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_6_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_7_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_8_busy;
	extern bool gtp_msg_sm_2_i_0_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_1_t_9;
	extern bool gtp_msg_sm_2_i_0_r_1_t_0_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_1_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_2_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_3_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_4_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_5_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_6_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_7_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_8_busy;
	extern bool gtp_msg_sm_2_i_0_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_2_t_9;
	extern bool gtp_msg_sm_2_i_0_r_2_t_0_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_1_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_2_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_3_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_4_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_5_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_6_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_7_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_8_busy;
	extern bool gtp_msg_sm_2_i_0_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_0_r_3_t_9;
	extern bool gtp_msg_sm_2_i_0_r_3_t_0_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_1_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_2_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_3_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_4_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_5_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_6_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_7_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_8_busy;
	extern bool gtp_msg_sm_2_i_0_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_0_r_3_t_9_cnt;


	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_0_t_9;
	extern bool gtp_msg_sm_3_i_0_r_0_t_0_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_1_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_2_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_3_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_4_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_5_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_6_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_7_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_8_busy;
	extern bool gtp_msg_sm_3_i_0_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_1_t_9;
	extern bool gtp_msg_sm_3_i_0_r_1_t_0_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_1_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_2_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_3_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_4_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_5_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_6_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_7_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_8_busy;
	extern bool gtp_msg_sm_3_i_0_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_2_t_9;
	extern bool gtp_msg_sm_3_i_0_r_2_t_0_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_1_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_2_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_3_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_4_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_5_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_6_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_7_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_8_busy;
	extern bool gtp_msg_sm_3_i_0_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_0_r_3_t_9;
	extern bool gtp_msg_sm_3_i_0_r_3_t_0_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_1_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_2_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_3_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_4_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_5_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_6_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_7_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_8_busy;
	extern bool gtp_msg_sm_3_i_0_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_0_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_0_t_9;
	extern bool gtp_msg_sm_4_i_0_r_0_t_0_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_1_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_2_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_3_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_4_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_5_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_6_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_7_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_8_busy;
	extern bool gtp_msg_sm_4_i_0_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_1_t_9;
	extern bool gtp_msg_sm_4_i_0_r_1_t_0_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_1_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_2_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_3_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_4_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_5_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_6_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_7_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_8_busy;
	extern bool gtp_msg_sm_4_i_0_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_2_t_9;
	extern bool gtp_msg_sm_4_i_0_r_2_t_0_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_1_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_2_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_3_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_4_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_5_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_6_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_7_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_8_busy;
	extern bool gtp_msg_sm_4_i_0_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_0_r_3_t_9;
	extern bool gtp_msg_sm_4_i_0_r_3_t_0_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_1_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_2_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_3_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_4_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_5_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_6_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_7_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_8_busy;
	extern bool gtp_msg_sm_4_i_0_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_0_r_3_t_9_cnt;


	//**** Interface #1 ********
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_0_t_9;
	extern bool gtp_msg_sm_0_i_1_r_0_t_0_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_1_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_2_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_3_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_4_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_5_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_6_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_7_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_8_busy;
	extern bool gtp_msg_sm_0_i_1_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_1_t_9;
	extern bool gtp_msg_sm_0_i_1_r_1_t_0_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_1_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_2_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_3_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_4_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_5_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_6_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_7_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_8_busy;
	extern bool gtp_msg_sm_0_i_1_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_2_t_9;
	extern bool gtp_msg_sm_0_i_1_r_2_t_0_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_1_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_2_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_3_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_4_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_5_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_6_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_7_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_8_busy;
	extern bool gtp_msg_sm_0_i_1_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_1_r_3_t_9;
	extern bool gtp_msg_sm_0_i_1_r_3_t_0_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_1_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_2_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_3_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_4_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_5_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_6_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_7_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_8_busy;
	extern bool gtp_msg_sm_0_i_1_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_1_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_0_t_9;
	extern bool gtp_msg_sm_1_i_1_r_0_t_0_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_1_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_2_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_3_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_4_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_5_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_6_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_7_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_8_busy;
	extern bool gtp_msg_sm_1_i_1_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_1_t_9;
	extern bool gtp_msg_sm_1_i_1_r_1_t_0_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_1_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_2_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_3_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_4_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_5_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_6_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_7_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_8_busy;
	extern bool gtp_msg_sm_1_i_1_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_2_t_9;
	extern bool gtp_msg_sm_1_i_1_r_2_t_0_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_1_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_2_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_3_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_4_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_5_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_6_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_7_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_8_busy;
	extern bool gtp_msg_sm_1_i_1_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_1_r_3_t_9;
	extern bool gtp_msg_sm_1_i_1_r_3_t_0_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_1_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_2_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_3_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_4_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_5_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_6_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_7_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_8_busy;
	extern bool gtp_msg_sm_1_i_1_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_1_r_3_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_0_t_9;
	extern bool gtp_msg_sm_2_i_1_r_0_t_0_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_1_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_2_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_3_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_4_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_5_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_6_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_7_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_8_busy;
	extern bool gtp_msg_sm_2_i_1_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_1_t_9;
	extern bool gtp_msg_sm_2_i_1_r_1_t_0_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_1_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_2_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_3_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_4_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_5_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_6_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_7_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_8_busy;
	extern bool gtp_msg_sm_2_i_1_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_2_t_9;
	extern bool gtp_msg_sm_2_i_1_r_2_t_0_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_1_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_2_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_3_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_4_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_5_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_6_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_7_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_8_busy;
	extern bool gtp_msg_sm_2_i_1_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_1_r_3_t_9;
	extern bool gtp_msg_sm_2_i_1_r_3_t_0_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_1_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_2_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_3_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_4_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_5_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_6_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_7_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_8_busy;
	extern bool gtp_msg_sm_2_i_1_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_1_r_3_t_9_cnt;


	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_0_t_9;
	extern bool gtp_msg_sm_3_i_1_r_0_t_0_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_1_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_2_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_3_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_4_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_5_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_6_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_7_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_8_busy;
	extern bool gtp_msg_sm_3_i_1_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_1_t_9;
	extern bool gtp_msg_sm_3_i_1_r_1_t_0_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_1_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_2_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_3_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_4_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_5_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_6_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_7_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_8_busy;
	extern bool gtp_msg_sm_3_i_1_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_2_t_9;
	extern bool gtp_msg_sm_3_i_1_r_2_t_0_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_1_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_2_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_3_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_4_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_5_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_6_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_7_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_8_busy;
	extern bool gtp_msg_sm_3_i_1_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_1_r_3_t_9;
	extern bool gtp_msg_sm_3_i_1_r_3_t_0_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_1_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_2_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_3_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_4_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_5_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_6_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_7_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_8_busy;
	extern bool gtp_msg_sm_3_i_1_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_1_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_0_t_9;
	extern bool gtp_msg_sm_4_i_1_r_0_t_0_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_1_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_2_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_3_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_4_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_5_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_6_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_7_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_8_busy;
	extern bool gtp_msg_sm_4_i_1_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_1_t_9;
	extern bool gtp_msg_sm_4_i_1_r_1_t_0_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_1_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_2_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_3_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_4_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_5_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_6_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_7_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_8_busy;
	extern bool gtp_msg_sm_4_i_1_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_2_t_9;
	extern bool gtp_msg_sm_4_i_1_r_2_t_0_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_1_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_2_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_3_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_4_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_5_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_6_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_7_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_8_busy;
	extern bool gtp_msg_sm_4_i_1_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_1_r_3_t_9;
	extern bool gtp_msg_sm_4_i_1_r_3_t_0_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_1_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_2_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_3_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_4_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_5_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_6_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_7_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_8_busy;
	extern bool gtp_msg_sm_4_i_1_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_1_r_3_t_9_cnt;


	//**** Interface #2 ********
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_0_t_9;
	extern bool gtp_msg_sm_0_i_2_r_0_t_0_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_1_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_2_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_3_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_4_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_5_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_6_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_7_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_8_busy;
	extern bool gtp_msg_sm_0_i_2_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_1_t_9;
	extern bool gtp_msg_sm_0_i_2_r_1_t_0_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_1_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_2_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_3_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_4_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_5_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_6_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_7_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_8_busy;
	extern bool gtp_msg_sm_0_i_2_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_2_t_9;
	extern bool gtp_msg_sm_0_i_2_r_2_t_0_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_1_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_2_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_3_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_4_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_5_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_6_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_7_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_8_busy;
	extern bool gtp_msg_sm_0_i_2_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_2_r_3_t_9;
	extern bool gtp_msg_sm_0_i_2_r_3_t_0_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_1_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_2_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_3_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_4_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_5_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_6_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_7_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_8_busy;
	extern bool gtp_msg_sm_0_i_2_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_2_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_0_t_9;
	extern bool gtp_msg_sm_1_i_2_r_0_t_0_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_1_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_2_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_3_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_4_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_5_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_6_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_7_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_8_busy;
	extern bool gtp_msg_sm_1_i_2_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_1_t_9;
	extern bool gtp_msg_sm_1_i_2_r_1_t_0_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_1_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_2_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_3_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_4_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_5_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_6_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_7_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_8_busy;
	extern bool gtp_msg_sm_1_i_2_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_2_t_9;
	extern bool gtp_msg_sm_1_i_2_r_2_t_0_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_1_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_2_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_3_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_4_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_5_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_6_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_7_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_8_busy;
	extern bool gtp_msg_sm_1_i_2_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_2_r_3_t_9;
	extern bool gtp_msg_sm_1_i_2_r_3_t_0_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_1_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_2_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_3_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_4_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_5_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_6_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_7_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_8_busy;
	extern bool gtp_msg_sm_1_i_2_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_2_r_3_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_0_t_9;
	extern bool gtp_msg_sm_2_i_2_r_0_t_0_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_1_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_2_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_3_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_4_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_5_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_6_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_7_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_8_busy;
	extern bool gtp_msg_sm_2_i_2_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_1_t_9;
	extern bool gtp_msg_sm_2_i_2_r_1_t_0_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_1_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_2_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_3_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_4_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_5_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_6_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_7_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_8_busy;
	extern bool gtp_msg_sm_2_i_2_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_2_t_9;
	extern bool gtp_msg_sm_2_i_2_r_2_t_0_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_1_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_2_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_3_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_4_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_5_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_6_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_7_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_8_busy;
	extern bool gtp_msg_sm_2_i_2_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_2_r_3_t_9;
	extern bool gtp_msg_sm_2_i_2_r_3_t_0_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_1_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_2_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_3_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_4_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_5_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_6_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_7_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_8_busy;
	extern bool gtp_msg_sm_2_i_2_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_2_r_3_t_9_cnt;


	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_0_t_9;
	extern bool gtp_msg_sm_3_i_2_r_0_t_0_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_1_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_2_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_3_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_4_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_5_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_6_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_7_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_8_busy;
	extern bool gtp_msg_sm_3_i_2_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_1_t_9;
	extern bool gtp_msg_sm_3_i_2_r_1_t_0_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_1_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_2_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_3_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_4_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_5_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_6_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_7_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_8_busy;
	extern bool gtp_msg_sm_3_i_2_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_2_t_9;
	extern bool gtp_msg_sm_3_i_2_r_2_t_0_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_1_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_2_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_3_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_4_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_5_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_6_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_7_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_8_busy;
	extern bool gtp_msg_sm_3_i_2_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_2_r_3_t_9;
	extern bool gtp_msg_sm_3_i_2_r_3_t_0_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_1_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_2_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_3_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_4_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_5_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_6_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_7_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_8_busy;
	extern bool gtp_msg_sm_3_i_2_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_2_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_0_t_9;
	extern bool gtp_msg_sm_4_i_2_r_0_t_0_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_1_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_2_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_3_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_4_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_5_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_6_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_7_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_8_busy;
	extern bool gtp_msg_sm_4_i_2_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_1_t_9;
	extern bool gtp_msg_sm_4_i_2_r_1_t_0_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_1_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_2_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_3_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_4_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_5_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_6_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_7_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_8_busy;
	extern bool gtp_msg_sm_4_i_2_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_2_t_9;
	extern bool gtp_msg_sm_4_i_2_r_2_t_0_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_1_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_2_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_3_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_4_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_5_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_6_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_7_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_8_busy;
	extern bool gtp_msg_sm_4_i_2_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_2_r_3_t_9;
	extern bool gtp_msg_sm_4_i_2_r_3_t_0_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_1_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_2_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_3_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_4_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_5_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_6_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_7_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_8_busy;
	extern bool gtp_msg_sm_4_i_2_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_2_r_3_t_9_cnt;



	//**** Interface #3 ********
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_0_t_9;
	extern bool gtp_msg_sm_0_i_3_r_0_t_0_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_1_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_2_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_3_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_4_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_5_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_6_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_7_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_8_busy;
	extern bool gtp_msg_sm_0_i_3_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_1_t_9;
	extern bool gtp_msg_sm_0_i_3_r_1_t_0_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_1_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_2_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_3_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_4_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_5_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_6_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_7_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_8_busy;
	extern bool gtp_msg_sm_0_i_3_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_2_t_9;
	extern bool gtp_msg_sm_0_i_3_r_2_t_0_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_1_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_2_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_3_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_4_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_5_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_6_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_7_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_8_busy;
	extern bool gtp_msg_sm_0_i_3_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_0_i_3_r_3_t_9;
	extern bool gtp_msg_sm_0_i_3_r_3_t_0_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_1_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_2_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_3_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_4_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_5_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_6_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_7_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_8_busy;
	extern bool gtp_msg_sm_0_i_3_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_0_i_3_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_0_t_9;
	extern bool gtp_msg_sm_1_i_3_r_0_t_0_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_1_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_2_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_3_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_4_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_5_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_6_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_7_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_8_busy;
	extern bool gtp_msg_sm_1_i_3_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_1_t_9;
	extern bool gtp_msg_sm_1_i_3_r_1_t_0_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_1_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_2_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_3_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_4_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_5_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_6_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_7_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_8_busy;
	extern bool gtp_msg_sm_1_i_3_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_2_t_9;
	extern bool gtp_msg_sm_1_i_3_r_2_t_0_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_1_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_2_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_3_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_4_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_5_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_6_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_7_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_8_busy;
	extern bool gtp_msg_sm_1_i_3_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_1_i_3_r_3_t_9;
	extern bool gtp_msg_sm_1_i_3_r_3_t_0_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_1_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_2_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_3_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_4_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_5_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_6_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_7_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_8_busy;
	extern bool gtp_msg_sm_1_i_3_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_1_i_3_r_3_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_0_t_9;
	extern bool gtp_msg_sm_2_i_3_r_0_t_0_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_1_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_2_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_3_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_4_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_5_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_6_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_7_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_8_busy;
	extern bool gtp_msg_sm_2_i_3_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_1_t_9;
	extern bool gtp_msg_sm_2_i_3_r_1_t_0_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_1_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_2_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_3_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_4_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_5_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_6_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_7_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_8_busy;
	extern bool gtp_msg_sm_2_i_3_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_2_t_9;
	extern bool gtp_msg_sm_2_i_3_r_2_t_0_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_1_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_2_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_3_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_4_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_5_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_6_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_7_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_8_busy;
	extern bool gtp_msg_sm_2_i_3_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_2_i_3_r_3_t_9;
	extern bool gtp_msg_sm_2_i_3_r_3_t_0_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_1_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_2_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_3_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_4_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_5_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_6_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_7_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_8_busy;
	extern bool gtp_msg_sm_2_i_3_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_2_i_3_r_3_t_9_cnt;


	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_0_t_9;
	extern bool gtp_msg_sm_3_i_3_r_0_t_0_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_1_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_2_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_3_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_4_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_5_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_6_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_7_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_8_busy;
	extern bool gtp_msg_sm_3_i_3_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_1_t_9;
	extern bool gtp_msg_sm_3_i_3_r_1_t_0_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_1_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_2_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_3_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_4_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_5_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_6_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_7_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_8_busy;
	extern bool gtp_msg_sm_3_i_3_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_2_t_9;
	extern bool gtp_msg_sm_3_i_3_r_2_t_0_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_1_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_2_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_3_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_4_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_5_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_6_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_7_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_8_busy;
	extern bool gtp_msg_sm_3_i_3_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_3_i_3_r_3_t_9;
	extern bool gtp_msg_sm_3_i_3_r_3_t_0_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_1_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_2_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_3_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_4_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_5_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_6_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_7_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_8_busy;
	extern bool gtp_msg_sm_3_i_3_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_3_i_3_r_3_t_9_cnt;



	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_0_t_9;
	extern bool gtp_msg_sm_4_i_3_r_0_t_0_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_1_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_2_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_3_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_4_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_5_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_6_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_7_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_8_busy;
	extern bool gtp_msg_sm_4_i_3_r_0_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_0_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_1_t_9;
	extern bool gtp_msg_sm_4_i_3_r_1_t_0_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_1_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_2_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_3_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_4_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_5_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_6_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_7_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_8_busy;
	extern bool gtp_msg_sm_4_i_3_r_1_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_1_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_2_t_9;
	extern bool gtp_msg_sm_4_i_3_r_2_t_0_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_1_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_2_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_3_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_4_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_5_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_6_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_7_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_8_busy;
	extern bool gtp_msg_sm_4_i_3_r_2_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_2_t_9_cnt;

	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_0;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_1;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_2;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_3;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_4;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_5;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_6;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_7;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_8;
	extern std::map<uint32_t, MPacket> gtp_msg_sm_4_i_3_r_3_t_9;
	extern bool gtp_msg_sm_4_i_3_r_3_t_0_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_1_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_2_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_3_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_4_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_5_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_6_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_7_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_8_busy;
	extern bool gtp_msg_sm_4_i_3_r_3_t_9_busy;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_0_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_1_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_2_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_3_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_4_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_5_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_6_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_7_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_8_cnt;
	extern uint32_t gtp_msg_sm_4_i_3_r_3_t_9_cnt;
}

namespace GTPV2FlushMap {
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_0;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_1;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_2;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_3;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_4;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_5;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_6;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_7;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_8;
	extern std::map<ULONG, GTPV2Session> gtpV2EndSessionMap_9;

	extern 	ULONG gtpV2EndSessionMAPCounter_0;
	extern 	ULONG gtpV2EndSessionMAPCounter_1;
	extern 	ULONG gtpV2EndSessionMAPCounter_2;
	extern 	ULONG gtpV2EndSessionMAPCounter_3;
	extern 	ULONG gtpV2EndSessionMAPCounter_4;
	extern 	ULONG gtpV2EndSessionMAPCounter_5;
	extern 	ULONG gtpV2EndSessionMAPCounter_6;
	extern 	ULONG gtpV2EndSessionMAPCounter_7;
	extern 	ULONG gtpV2EndSessionMAPCounter_8;
	extern 	ULONG gtpV2EndSessionMAPCounter_9;
}

namespace GTPFlushRepository {

	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_0;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_1;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_2;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_3;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_4;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_5;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_6;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_7;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_8;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_0_t_9;

	extern int gtpcV1FlushMap_sm_0_t_0_cnt;
	extern int gtpcV1FlushMap_sm_0_t_1_cnt;
	extern int gtpcV1FlushMap_sm_0_t_2_cnt;
	extern int gtpcV1FlushMap_sm_0_t_3_cnt;
	extern int gtpcV1FlushMap_sm_0_t_4_cnt;
	extern int gtpcV1FlushMap_sm_0_t_5_cnt;
	extern int gtpcV1FlushMap_sm_0_t_6_cnt;
	extern int gtpcV1FlushMap_sm_0_t_7_cnt;
	extern int gtpcV1FlushMap_sm_0_t_8_cnt;
	extern int gtpcV1FlushMap_sm_0_t_9_cnt;

	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_0;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_1;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_2;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_3;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_4;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_5;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_6;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_7;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_8;
	extern std::vector<GTPSession> gtpcV1FlushMap_sm_1_t_9;

	extern int gtpcV1FlushMap_sm_1_t_0_cnt;
	extern int gtpcV1FlushMap_sm_1_t_1_cnt;
	extern int gtpcV1FlushMap_sm_1_t_2_cnt;
	extern int gtpcV1FlushMap_sm_1_t_3_cnt;
	extern int gtpcV1FlushMap_sm_1_t_4_cnt;
	extern int gtpcV1FlushMap_sm_1_t_5_cnt;
	extern int gtpcV1FlushMap_sm_1_t_6_cnt;
	extern int gtpcV1FlushMap_sm_1_t_7_cnt;
	extern int gtpcV1FlushMap_sm_1_t_8_cnt;
	extern int gtpcV1FlushMap_sm_1_t_9_cnt;

//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_0;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_1;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_2;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_3;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_4;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_5;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_6;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_7;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_8;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_2_t_9;
//
//	extern int gtpcV1FlushMap_sm_2_t_0_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_1_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_2_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_3_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_4_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_5_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_6_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_7_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_8_cnt;
//	extern int gtpcV1FlushMap_sm_2_t_9_cnt;
//
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_0;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_1;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_2;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_3;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_4;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_5;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_6;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_7;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_8;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_3_t_9;
//
//	extern int gtpcV1FlushMap_sm_3_t_0_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_1_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_2_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_3_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_4_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_5_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_6_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_7_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_8_cnt;
//	extern int gtpcV1FlushMap_sm_3_t_9_cnt;
//
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_0;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_1;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_2;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_3;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_4;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_5;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_6;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_7;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_8;
//	extern std::vector<GTPSession> gtpcV1FlushMap_sm_4_t_9;
//
//	extern int gtpcV1FlushMap_sm_4_t_0_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_1_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_2_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_3_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_4_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_5_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_6_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_7_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_8_cnt;
//	extern int gtpcV1FlushMap_sm_4_t_9_cnt;
}

namespace GTPXdrRepository {
	extern std::map<long, std::string> gtpcV1XdrMap_t_0;
	extern std::map<long, std::string> gtpcV1XdrMap_t_1;
	extern std::map<long, std::string> gtpcV1XdrMap_t_2;
	extern std::map<long, std::string> gtpcV1XdrMap_t_3;
	extern std::map<long, std::string> gtpcV1XdrMap_t_4;
	extern std::map<long, std::string> gtpcV1XdrMap_t_5;
	extern long gtpcV1XdrMap_t_0_cnt;
	extern long gtpcV1XdrMap_t_1_cnt;
	extern long gtpcV1XdrMap_t_2_cnt;
	extern long gtpcV1XdrMap_t_3_cnt;
	extern long gtpcV1XdrMap_t_4_cnt;
	extern long gtpcV1XdrMap_t_5_cnt;

//	extern std::map<long, std::string> gtpuXdrMap_t_0;
//	extern std::map<long, std::string> gtpuXdrMap_t_1;
//	extern std::map<long, std::string> gtpuXdrMap_t_2;
//	extern std::map<long, std::string> gtpuXdrMap_t_3;
//	extern std::map<long, std::string> gtpuXdrMap_t_4;
//	extern std::map<long, std::string> gtpuXdrMap_t_5;
//	extern long gtpuXdrMap_t_0_cnt;
//	extern long gtpuXdrMap_t_1_cnt;
//	extern long gtpuXdrMap_t_2_cnt;
//	extern long gtpuXdrMap_t_3_cnt;
//	extern long gtpuXdrMap_t_4_cnt;
//	extern long gtpuXdrMap_t_5_cnt;
//
//	extern std::map<long, std::string> dnsXdrMap_t_0;
//	extern std::map<long, std::string> dnsXdrMap_t_1;
//	extern std::map<long, std::string> dnsXdrMap_t_2;
//	extern std::map<long, std::string> dnsXdrMap_t_3;
//	extern std::map<long, std::string> dnsXdrMap_t_4;
//	extern std::map<long, std::string> dnsXdrMap_t_5;
//	extern long dnsXdrMap_t_0_cnt;
//	extern long dnsXdrMap_t_1_cnt;
//	extern long dnsXdrMap_t_2_cnt;
//	extern long dnsXdrMap_t_3_cnt;
//	extern long dnsXdrMap_t_4_cnt;
//	extern long dnsXdrMap_t_5_cnt;
}

namespace GTPZmqFlushStore {

	extern int zmq_flush_t_index;

	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_0;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_1;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_2;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_3;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_4;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_5;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_6;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_7;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_8;
	extern std::vector<xdrStore> zmq_flush_map_gtpc_t_9;
	extern int zmq_flush_map_gtpc_t_0_cnt;
	extern int zmq_flush_map_gtpc_t_1_cnt;
	extern int zmq_flush_map_gtpc_t_2_cnt;
	extern int zmq_flush_map_gtpc_t_3_cnt;
	extern int zmq_flush_map_gtpc_t_4_cnt;
	extern int zmq_flush_map_gtpc_t_5_cnt;
	extern int zmq_flush_map_gtpc_t_6_cnt;
	extern int zmq_flush_map_gtpc_t_7_cnt;
	extern int zmq_flush_map_gtpc_t_8_cnt;
	extern int zmq_flush_map_gtpc_t_9_cnt;

}
#endif /* PLUGINS_GN_INC_GTPGLOBAL_H_ */
