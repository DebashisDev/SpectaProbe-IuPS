/*
 * TCPConfig.h
 *
 *  Created on: 29-Jan-2016
 *      Author: deb
 */

#ifndef SRC_TCPCONFIG_H_
#define SRC_TCPCONFIG_H_

#include "BaseConfig.h"
#include "IPGlobal.h"
#include "Log.h"
#include "GConstant.h"

#include <zmq.h>

class TCPConfig : public BaseConfig {

private:
	void readParameters();

public:
	TCPConfig();
	~TCPConfig();
	TCHAR 	tcpFlushIP[100];
	TCHAR 	dnsFlushIP[100];
};

#endif /* SRC_TCPCONFIG_H_ */
