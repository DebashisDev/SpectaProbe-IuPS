/*
 * SCCPConfig.h
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_SCCP_SRC_SCCPCONFIG_H_
#define PLUGINS_SCCP_SRC_SCCPCONFIG_H_

#include <fstream>
#include <iostream>
#include <GConstant.h>
#include <string.h>

using namespace std;

class SCCPConfig {

	public:
		SCCPConfig();
		virtual ~SCCPConfig();
		void loadConfig(ifstream &fp);

		bool SCCP_WRITE_SESSION_TRACE = false;
		string SCCP_WRITE_SESSION_DIR_PREFIX = "";
		string SCCP_TRACE_SESSION_IDS = "";
		string SGSN_POINT_CODES = "";
};

#endif /* PLUGINS_SCCP_SRC_SCCPCONFIG_H_ */
