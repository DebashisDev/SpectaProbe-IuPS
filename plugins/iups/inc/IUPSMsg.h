/*
 * IUPSMsg.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_IUPS_INC_IUPSMSG_H_
#define PLUGINS_IUPS_INC_IUPSMSG_H_

using namespace std;

typedef struct _iupsMsg
{
	unsigned int 	packetLengthRANAP;
	int 	packetLengthNAS;

	//Two types of transaction sessions maintained
	// RANAP session or GMM session, they are mutually exclusive
	// and is determined by the value stored in sessiontype
	int 	sessiontype;
	bool 	rsessionstart;
	bool 	rsessionend;
	bool 	gmmsessionstart;
	bool 	gmmsessionintmd;
	bool 	gmmsessionend;


	//Global parameters
    string 	flow_dir_desc;
    string 	imsi;
    string 	tmsi;
    string 	imei;
    string 	msisdn;

    unsigned int ranap_bytes;

    string	session_ranap_id;		//ranap session key of the session originating procedure
	int 	procedure_code;
    string 	procedure_desc;

    int 	session_mmsm_id;		//mmsm_id of the session originating procedure
    int 	mmsm_id;
    string 	mmsm_desc;

    //Session specific parameters
    //will be set either by a RANAP session or MMSM session
    int 	RABCauseId;
    string 	RABCauseDesc;

    string 	RABId;
    string 	TEId;
    string 	PDPType;

    int 	RATId;
    string 	RATDesc;

    int 	RAUpdateId;
    string 	RAUpdateDesc;

    int 	EndCauseId;
    string 	EndCauseDesc;

    int 	AttachDetachId;
    //int AttachDetachDir;
    string 	AttachDetachDir;
    string 	AttachDetachDesc;

    int 	PDPStaticAddressRequested;
    string 	PDPAddressRequested;
    string 	PDPAddressAllocated;

    string 	PLMNIdHex;
    string 	PLMNIdDec;
    string 	SACIdHex;
    string 	SACIdDec;
    string 	LACIdHex;
    string 	LACIdDec;
    string 	RACIdHex;
    string 	RACIdDec;

    string 	RNCId;

    string 	RAIOldHex;
    string 	RAIOldDec;
    string 	RAINewHex;
    string 	RAINewDec;

    string 	APN;

    //unsigned int ByteSizeUL;
    //unsigned int ByteSizeDL;


    _iupsMsg()
	{
    	reset();
	}

//    ~_iupsMsg(){}

	void reset()
	{

		packetLengthRANAP = 0;
		packetLengthNAS = 0;

		sessiontype = 0;
		rsessionstart = false;			//Important indicators to flush out Ranap sessions
		rsessionend = false;
		gmmsessionstart = false;		//Important indicators to flush out GMM sessions
		gmmsessionintmd = false;
		gmmsessionend = false;


		flow_dir_desc.assign("");
	    imsi.assign("");
	    tmsi.assign("");
		imei.assign("");
		msisdn.assign("");

		ranap_bytes = 0;

		session_ranap_id.assign("");
		procedure_code = -1;
		procedure_desc.assign("");

		session_mmsm_id = -1;
		mmsm_id = -1;
		mmsm_desc.assign("");

		RABCauseId = -1;
		RABCauseDesc.assign("");

		RABId.assign("");
		TEId.assign("");

		RAUpdateId = -1;
		RAUpdateDesc.assign("");

		EndCauseId = -1;
		EndCauseDesc.assign("");

		AttachDetachId = -1;
		AttachDetachDesc.assign("");

		PDPStaticAddressRequested = -1;
		PDPAddressRequested.assign("");
		PDPAddressAllocated.assign("");

		PLMNIdHex.assign("");
		PLMNIdDec.assign("");
		SACIdHex.assign("");
		SACIdDec.assign("");
		LACIdHex.assign("");
		LACIdDec.assign("");
		RACIdHex.assign("");
		RACIdDec.assign("");

		RNCId.assign("");

		RAIOldHex.assign("");
		RAIOldDec.assign("");
		RAINewHex.assign("");
		RAINewDec.assign("");

		APN.assign("");
	}

	void set(const _iupsMsg *obj)
	{
		this->packetLengthRANAP = obj->packetLengthRANAP;
		this->packetLengthNAS = obj->packetLengthNAS;

		//Two types of transaction sessions maintained
		// RANAP session or GMM session, they are mutually exclusive
		// and is determined by the value stored in sessiontype
		this->sessiontype = obj->sessiontype;
		this->rsessionstart = obj->rsessionstart;
		this->rsessionend = obj->rsessionend;
		this->gmmsessionstart = obj->gmmsessionstart;
		this->gmmsessionintmd = obj->gmmsessionintmd;
		this->gmmsessionend = obj->gmmsessionend;


		//Global parameters
	    this->flow_dir_desc.assign(obj->flow_dir_desc);
	    this->imsi.assign(obj->imsi);
	    this->tmsi.assign(obj->tmsi);
	    this->imei.assign(obj->imei);
	    this->msisdn.assign(obj->msisdn);

	    this->ranap_bytes = obj->ranap_bytes;

	    this->session_ranap_id.assign(obj->session_ranap_id);
		this->procedure_code = obj->procedure_code;
	    this->procedure_desc.assign(obj->procedure_desc);

	    this->session_mmsm_id = obj->session_mmsm_id;
	    this->mmsm_id = obj->mmsm_id;
	    this->mmsm_desc.assign(obj->mmsm_desc);

	    //Session specific parameters
	    //will be set either by a RANAP session or MMSM session
	    this->RABCauseId = obj->RABCauseId;
	    this->RABCauseDesc.assign(obj->RABCauseDesc);

	    this->RABId.assign(obj->RABId);
	    this->TEId.assign(obj->TEId);
	    this->PDPType.assign(obj->PDPType);

	    this->RATId = obj->RATId;
	    this->RATDesc.assign(obj->RATDesc);

	    this->RAUpdateId = obj->RAUpdateId;
	    this->RAUpdateDesc.assign(obj->RAUpdateDesc);

	    this->EndCauseId = obj->EndCauseId;
	    this->EndCauseDesc.assign(obj->EndCauseDesc);

	    this->AttachDetachId = obj->AttachDetachId;
	    this->AttachDetachDir.assign(obj->AttachDetachDir);
	    this->AttachDetachDesc.assign(obj->AttachDetachDesc);

	    this->PDPStaticAddressRequested = obj->PDPStaticAddressRequested;
	    this->PDPAddressRequested.assign(obj->PDPAddressRequested);
	    this->PDPAddressAllocated.assign(obj->PDPAddressAllocated);

	    this->PLMNIdHex.assign(obj->PLMNIdHex);
	    this->PLMNIdDec.assign(obj->PLMNIdDec);
	    this->SACIdHex.assign(obj->SACIdHex);
	    this->SACIdDec.assign(obj->SACIdDec);
	    this->LACIdHex.assign(obj->LACIdHex);
	    this->LACIdDec.assign(obj->LACIdDec);
	    this->RACIdHex.assign(obj->RACIdHex);
	    this->RACIdDec.assign(obj->RACIdDec);

	    this->RNCId.assign(obj->RNCId);

	    this->RAIOldHex.assign(obj->RAIOldHex);
	    this->RAIOldDec.assign(obj->RAIOldDec);
	    this->RAINewHex.assign(obj->RAINewHex);
	    this->RAINewDec.assign(obj->RAINewDec);

	    this->APN.assign(obj->APN);

	}

}iupsMsg;




#endif /* PLUGINS_IUPS_INC_IUPSMSG_H_ */
