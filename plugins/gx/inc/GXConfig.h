/*
 * GXConfig.h
 *
 *  Created on: Oct 13, 2016
 *      Author: Debashis
 */

#ifndef PLUGINS_GX_SRC_GXCONFIG_H_
#define PLUGINS_GX_SRC_GXCONFIG_H_

#include <fstream>
#include <iostream>
#include <zmq.h>

using namespace std;

class GxConfig {
public:
	GxConfig();
	virtual ~GxConfig();

	void loadGXConfig(ifstream& fp);
	void createGxZMQ();

	int 	GX_INTERFACE_TYPE;
	string 	GX_INTERFACE_NAME;
	int 	GX_SF_VIRTUAL_INTERFACES;

	bool 	GX_FLUSH_FLAG;
	string 	GX_FLUSH_PORT;

	bool 	GX_WRITE_XDR;
	string 	GX_FILE_PREFIX;

	int 	GX_IDLE_SESSION_TIMEOUT_IN_SEC;
	int 	GX_ACTIVE_SESSION_TIMEOUT_IN_SEC;
	int 	GX_SESSION_PACKET_LIMIT;
};

#endif /* PLUGINS_GX_SRC_GXGYCONFIG_H_ */
