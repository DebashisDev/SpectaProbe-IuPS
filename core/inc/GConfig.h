/*
 * GConfig.h
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#ifndef CORE_SRC_GCONFIG_H_
#define CORE_SRC_GCONFIG_H_

#include <string.h>

#include "BroadBandConfig.h"
#include "GTPConfig.h"
#include "GConstant.h"
#include "SCCPConfig.h"
#include "IUPSConfig.h"

class GConfig {
private:
		ifstream fp;
		void initialize(char *fileName);
		void openConfigFile(char *fileName);
		void closeConfigFile();
		void loadPuglinConfigs(char *fileName);

public:
	GConfig(char *fileName);
	~GConfig();

	BroadBandConfig *bbConfig;
	GTPConfig 		*gtpConfig;
	IUPSConfig		*iupsConfig;
	SCCPConfig		*sccpConfig;

	int 	LOG_LEVEL;
	string 	XDR_DIR;
	string 	LOG_DIR;
	string 	DATA_DIR;
	string 	TRACE_DIR;

	bool	BROADBAND_PROBE;
	bool	GX_PROBE;
	bool	RADIUS_PROBE;
	bool	IUPS_PROBE;
	bool	GN_PROBE;
	bool	S1MME_PROBE;

};

#endif /* CORE_SRC_GCONFIG_H_ */
