/*
 * BroadBandConfig.h
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#ifndef BROADBAND_BROADBANDCONFIG_H_
#define BROADBAND_BROADBANDCONFIG_H_

#include <fstream>
#include <iostream>
//#include <zmq.h>

using namespace std;

class BroadBandConfig {
	private:

	public:
		BroadBandConfig();
		~BroadBandConfig();
		void loadConfig(ifstream& fp);
//		void createZMQ();

		int BROADBAND_INTERFACE_TYPE;
		string BROADBAND_INTERFACE_NAME;
		int BROADBAND_SF_VIRTUAL_INTERFACES;
		bool BROADBAND_IP_FLUSH_FLAG;
		string BROADBAND_IP_FLUSH_PORT;
		bool BROADBAND_DNS_FLUSH_FLAG;
		string BROADBAND_DNS_FLUSH_PORT;
		bool BROADBAND_QUEUE;
		bool BROADBAND_WRITE_XDR;
		string BROADBAND_FILE_PREFIX;
		int BROADBAND_IDLE_SESSION_TIMEOUT_IN_SEC;
		int BROADBAND_ACTIVE_SESSION_TIMEOUT_IN_SEC;
		int BROADBAND_SESSION_PACKET_LIMIT;
};

#endif /* BROADBAND_BROADBANDCONFIG_H_ */
