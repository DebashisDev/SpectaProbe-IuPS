/*
 * GTPConfig.h
 *
 *  Created on: 04-Aug-2016
 *      Author: deb
 */

#ifndef PLUGINS_GN_SRC_GTPCONFIG_H_
#define PLUGINS_GN_SRC_GTPCONFIG_H_

#include <fstream>
#include <iostream>

using namespace std;

class GTPConfig {
	private:

	public:
		GTPConfig();
		~GTPConfig();

		void 	loadGNConfig(ifstream& fp);
		void 	createGNZMQ();

		int 	GN_INTERFACE_TYPE;
		string 	GN_INTERFACE_NAME;

		bool 	GN_GTPC_FLUSH_FLAG;
		string 	GN_GTPC_FLUSH_PORT;
		bool 	GN_GTPC_WRITE_XDR;
		string 	GN_GTPC_FILE_PREFIX;

		bool 	GN_GTPU_FLUSH_FLAG;
		string 	GN_GTPU_FLUSH_PORT;
		bool 	GN_GTPU_WRITE_XDR;
		string 	GN_GTPU_FILE_PREFIX;

		bool 	GN_DNS_WRITE_XDR;
		string 	GN_DNS_FILE_PREFIX;
		bool 	GN_DNS_FLUSH_FLAG;
		string 	GN_DNS_FLUSH_PORT;
		int		GN_GTPU_ZMQ_FLUSER_TPS;
		int 	GTPC_FLUSH_MAP_REPO_SIZE;
		int 	GTPC_ZMQ_FLUSH_MAP_ARRAY_SIZE;

		int 	GN_GTPU_IDLE_SESSION_TIMEOUT_IN_SEC;
		int 	GN_GTPU_ACTIVE_SESSION_TIMEOUT_IN_SEC;
		int 	GN_GTPU_SESSION_PACKET_LIMIT;

		int		GN_GTPC_MAX_SESSIONS;
		int 	GN_GTPC_IDLE_SESSION_TIMEOUT_IN_SEC;
		int		GN_GTPC_GLOBAL_SESSION_CLEANUP_TIMEOUT_SEC;
};

#endif /* PLUGINS_GN_SRC_GTPCONFIG_H_ */
