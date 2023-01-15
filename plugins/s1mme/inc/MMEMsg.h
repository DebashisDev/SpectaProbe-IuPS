/*
 * MMEMsg.h
 *
 *  Created on: 02-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_S1MME_INC_MMEMSG_H_
#define PLUGINS_S1MME_INC_MMEMSG_H_

using namespace std;

typedef struct _mmeMsg
{
	int 	packetLength;
	int 	packetLengthNAS;

	//Two types of transaction sessions maintained
	// MME session or GMM session, they are mutually exclusive
	// and is determined by the value stored in sessiontype
	int 	sessiontype;
	bool 	sessionstart;
	bool 	sessionend;
	bool 	gmmsessionstart;
	bool 	gmmsessionend;


	//Global parameters
    string 	flow_dir_desc;
    string 	imsi;
    string 	tmsi;
    string 	imei;
    string 	msisdn;

    //unsigned int bytes;

	int 	procedure_code;
    string 	procedure_desc;

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


    _mmeMsg()
	{
    	reset();
	}

//    ~_mmeMsg(){}

	void reset()
	{

		packetLength = 0;
		packetLengthNAS = 0;

		sessiontype = 0;
		sessionstart = false;			//Important indicators to flush out MME sessions
		sessionend = false;
		gmmsessionstart = false;		//Important indicators to flush out GMM sessions
		gmmsessionend = false;


		flow_dir_desc.assign("");
	    imsi.assign("");
	    tmsi.assign("");
		imei.assign("");
		msisdn.assign("");

		//ranap_bytes = 0;

		procedure_code = -1;
		procedure_desc.assign("");

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

	void set(const _mmeMsg *obj)
	{
		this->packetLength = obj->packetLength;
		this->packetLengthNAS = obj->packetLengthNAS;

		//Two types of transaction sessions maintained
		// RANAP session or GMM session, they are mutually exclusive
		// and is determined by the value stored in sessiontype
		this->sessiontype = obj->sessiontype;
		this->sessionstart = obj->sessionstart;
		this->sessionend = obj->sessionend;
		this->gmmsessionstart = obj->gmmsessionstart;
		this->gmmsessionend = obj->gmmsessionend;


		//Global parameters
	    this->flow_dir_desc.assign(obj->flow_dir_desc);
	    this->imsi.assign(obj->imsi);
	    this->tmsi.assign(obj->tmsi);
	    this->imei.assign(obj->imei);
	    this->msisdn.assign(obj->msisdn);

	    //this->ranap_bytes = obj->ranap_bytes;

		this->procedure_code = obj->procedure_code;
	    this->procedure_desc.assign(obj->procedure_desc);

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

}mmeMsg;



#endif /* PLUGINS_S1MME_INC_MMEMSG_H_ */
