/*
 * IUPSConfig.h
 *
 *  Created on: 26-Jul-2016
 *      Author: deb
 */

#ifndef PLUGINS_IUPS_SRC_IUPSCONFIG_H_
#define PLUGINS_IUPS_SRC_IUPSCONFIG_H_

#include "BaseConfig.h"
#include <fstream>
#include <iostream>

using namespace std;

class IUPSConfig : public BaseConfig{
	private:
		void openZmq();

	public:
		IUPSConfig();
		virtual ~IUPSConfig();
		void loadConfig(ifstream &fp);

		bool IUPS_FLUSH_FLAG;
		string IUPS_FLUSH_PORT;
		string IUPS_FILE_PREFIX;
		bool IUPS_WRITE_XDR;
		bool IUPS_WRITE_TDR;
		int IUPS_ZMQ_FLUSER_TPS;
};

#endif /* PLUGINS_IUPS_SRC_IUPSCONFIG_H_ */
