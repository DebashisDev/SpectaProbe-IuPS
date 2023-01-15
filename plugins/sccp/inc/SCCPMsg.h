/*
 * SCCPMsg.h
 *
 *  Created on: 14-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCCP_INC_SCCPMSG_H_
#define PLUGINS_SCCP_INC_SCCPMSG_H_

using namespace std;

typedef struct _sccpMsg
{
	bool	flow_dir_up;
	//int		ssn;
	string 	sccp_slr;
    string 	sccp_dlr;
    string 	sccp_session_id;
    //string 	sessionid_print;
    int 	sccp_message_type;
    string 	sccp_message_desc;
    int 	sccp_release_cause;
    string 	sccp_release_desc;

    _sccpMsg()
	{ reset(); }

//    ~_sccpMsg(){}

	void reset()
	{
		flow_dir_up = true;
		//ssn = -1;
		sccp_slr.assign("000000000");
		sccp_dlr.assign("000000000");
		sccp_session_id.assign("NA");	//Important to keep "NA" as it is used to validate in later sections
		//sessionid_print.assign("00000000");
		sccp_message_type = -1;
		sccp_message_desc.clear();
		sccp_release_cause = -1;
		sccp_release_desc.clear();
	}

	void set(const _sccpMsg *obj)
	{
		this->flow_dir_up = obj->flow_dir_up;
		//this->ssn = obj->ssn;
		this->sccp_slr.assign(obj->sccp_slr);
		this->sccp_dlr.assign(obj->sccp_dlr);
		this->sccp_session_id.assign(obj->sccp_session_id);
		//this->sessionid_print.assign(obj->sessionid_print);
		this->sccp_message_type = obj->sccp_message_type;
		this->sccp_message_desc.assign(obj->sccp_message_desc);
		this->sccp_release_cause = obj->sccp_release_cause;
		this->sccp_release_desc.assign(obj->sccp_release_desc);
	}

}sccpMsg;


#endif /* PLUGINS_SCCP_INC_SCCPMSG_H_ */
