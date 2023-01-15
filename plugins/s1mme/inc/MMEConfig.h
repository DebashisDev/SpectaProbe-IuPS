/*
 * MMEConfig.h
 *
 *  Created on: Aug 1, 2016
 *      Author: Deb
 */

#ifndef PLUGINS_S1MME_MMECONFIG_H_
#define PLUGINS_S1MME_MMECONFIG_H_

#include <fstream>
#include <iostream>

using namespace std;

class MMEConfig {
	public:
		MMEConfig();
		virtual ~MMEConfig();
		void loadConfig(ifstream &fp);

		bool MME_SM_QUEUE = false;
		int MME_INTERFACE_TYPE;
		string MME_ETH_INTERFACE_NAME;

};

#endif /* PLUGINS_S1MME_MMECONFIG_H_ */
