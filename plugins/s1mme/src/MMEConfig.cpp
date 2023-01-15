/*
 * MMEConfig.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: Deb
 */

#include "MMEConfig.h"

MMEConfig::MMEConfig() {
	// TODO Auto-generated constructor stub

}

MMEConfig::~MMEConfig() {
	// TODO Auto-generated destructor stub
}

void MMEConfig::loadConfig(ifstream &fp){

	printf("  Loading S1-MME configurations...\n");

	string Key, Value;

	while(!fp.eof())
	{
		fp >> Key;
		if(Key.compare("MME_SM_QUEUE") == 0)
		{
			fp >> Value;
			if(Value.compare("true") == 0)
				MME_SM_QUEUE = true;
			else
				MME_SM_QUEUE = false;
			printf("	MME_SM_QUEUE			:: %d\n", MME_SM_QUEUE);
		}
		else if(Key.compare("MME_INTERFACE_TYPE") == 0)
		{
			fp >> Value;
			MME_INTERFACE_TYPE =  atoi(Value.c_str());
			printf("	MME_INTERFACE_TYPE		:: %d\n", MME_INTERFACE_TYPE);
		}
		else if(Key.compare("MME_ETH_INTERFACE_NAME") == 0)
		{
			fp >> Value;
			MME_ETH_INTERFACE_NAME =  Value;
			printf("	MME_ETH_INTERFACE_NAME		:: %s\n", MME_ETH_INTERFACE_NAME.c_str());
		}
//		else if(Key.compare("MME_TDR_DIR") == 0)
//		{
//			fp >> Value;
//			MME_TDR_DIR =  Value;
//			printf("	MME_TDR_DIR			:: %s\n", MME_TDR_DIR.c_str());
//		}
	}
}

