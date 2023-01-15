/*
 * BWData.cpp
 *
 *  Created on: 27-May-2016
 *      Author: Deb
 */

#include "BWData.h"

BWData::BWData(int intfid, int rid)
{
	this->_name = "BWData";
	this->setLogLevel(Log::theLog().level());
	this->interfaceId = intfid;
	this->routerId = rid;
}

BWData::~BWData()
{
}

VOID BWData::updateBWData(int curMin, MPacket *msgObj){


	bwval = msgObj->frSize * 8;
	isUpDir = msgObj->dirUserNetwork;
	curSec = msgObj->frTimeEpochSec % 100;

	//Write in curMin index based on Odd or Even min
	//if curMin = 3, write in _1 if curMin = 4 write in _0
	//Reading will happen opposite
	int t_index = curMin % 2;
	processBw(t_index);
}

VOID BWData::setBWData(int curMin)
{
	int t_index = curMin % 2;
	if(t_index == 0) t_index = 1;
	else if(t_index == 1) t_index = 0;

	switch(interfaceId)
	{
		case 0:
			setBWData_i_0(t_index);
			break;

		case 1:
			setBWData_i_1(t_index);
			break;

		case 2:
			setBWData_i_2(t_index);
			break;

		case 3:
			setBWData_i_3(t_index);
			break;
	}
}

VOID BWData::setBWData_i_0(int t_index)
{
	bwData bw;

	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_0_r_0_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_0_r_0_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_0_r_0.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_0_r_0.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_0_r_0.dnVolume = bw.dnVolume;

			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_0_r_1_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_0_r_1_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_0_r_1.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_0_r_1.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_0_r_1.dnVolume = bw.dnVolume;

			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_0_r_2_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_0_r_2_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_0_r_2.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_0_r_2.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_0_r_2.dnVolume = bw.dnVolume;

			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_0_r_3_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_0_r_3_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_0_r_3.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_0_r_3.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_0_r_3.dnVolume = bw.dnVolume;

			break;
	}
}

VOID BWData::setBWData_i_1(int t_index)
{
	bwData bw;

	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_1_r_0_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_1_r_0_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_1_r_0.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_1_r_0.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_1_r_0.dnVolume = bw.dnVolume;

			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_1_r_1_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_1_r_1_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_1_r_1.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_1_r_1.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_1_r_1.dnVolume = bw.dnVolume;

			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_1_r_2_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_1_r_2_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_1_r_2.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_1_r_2.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_1_r_2.dnVolume = bw.dnVolume;

			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_1_r_3_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_1_r_3_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_1_r_3.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_1_r_3.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_1_r_3.dnVolume = bw.dnVolume;

			break;
	}
}

VOID BWData::setBWData_i_2(int t_index)
{
	bwData bw;

	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_2_r_0_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_2_r_0_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_2_r_0.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_2_r_0.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_2_r_0.dnVolume = bw.dnVolume;

			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_2_r_1_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_2_r_1_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_2_r_1.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_2_r_1.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_2_r_1.dnVolume = bw.dnVolume;

			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_2_r_2_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_2_r_2_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_2_r_2.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_2_r_2.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_2_r_2.dnVolume = bw.dnVolume;

			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_2_r_3_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_2_r_3_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_2_r_3.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_2_r_3.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_2_r_3.dnVolume = bw.dnVolume;

			break;
	}
}

VOID BWData::setBWData_i_3(int t_index)
{
	bwData bw;

	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_3_r_0_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_3_r_0_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_3_r_0.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_3_r_0.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_3_r_0.dnVolume = bw.dnVolume;

			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_3_r_1_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_3_r_1_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_3_r_1.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_3_r_1.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_3_r_1.dnVolume = bw.dnVolume;

			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_3_r_2_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_3_r_2_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_3_r_2.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_3_r_2.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_3_r_2.dnVolume = bw.dnVolume;

			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						bw = calculateBwData(t_index, bw_i_3_r_3_0);
						break;

					case 1:
						bw = calculateBwData(t_index, bw_i_3_r_3_1);
						break;
				}
			}
			IPGlobal::BW_MBPS_i_3_r_3.Volume = bw.Volume;
			IPGlobal::BW_MBPS_i_3_r_3.upVolume = bw.upVolume;
			IPGlobal::BW_MBPS_i_3_r_3.dnVolume = bw.dnVolume;

			break;
	}
}


bwData BWData::calculateBwData(int t_index, bwData (&bw)[BW_TIME_INDEX])
{
	bwData bwdata;
	bwdata.Volume = 0;
	bwdata.upVolume = 0;
	bwdata.dnVolume = 0;

	for(int i = 0; i < BW_TIME_INDEX; i++){

		if(bw[i].Volume > bwdata.Volume)
			bwdata.Volume = bw[i].Volume;
		bw[i].Volume = 0;

		if(bw[i].upVolume > bwdata.upVolume)
			bwdata.upVolume = bw[i].upVolume;
		bw[i].upVolume = 0;

		if(bw[i].dnVolume > bwdata.dnVolume)
			bwdata.dnVolume = bw[i].dnVolume;
		bw[i].dnVolume = 0;

	}

	return bwdata;

}


VOID BWData::processBwData(bwData (&bw)[BW_TIME_INDEX])
{
	bw[curSec].Volume += bwval;
	if(isUpDir)
		bw[curSec].upVolume += bwval;
	else
		bw[curSec].dnVolume += bwval;
}

VOID BWData::processBw(int t_index)
{
	switch(interfaceId)
	{
		case 0:
			processBw_i_0(t_index);
			break;

		case 1:
			processBw_i_1(t_index);
			break;

		case 2:
			processBw_i_2(t_index);
			break;

		case 3:
			processBw_i_3(t_index);
			break;
	}
}

VOID BWData::processBw_i_0(int t_index)
{
	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_0_r_0_0);
						break;

					case 1:
						processBwData(bw_i_0_r_0_1);
						break;
				}
			}
			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_0_r_1_0);
						break;

					case 1:
						processBwData(bw_i_0_r_1_1);
						break;
				}
			}
			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_0_r_2_0);
						break;

					case 1:
						processBwData(bw_i_0_r_2_1);
						break;
				}
			}
			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_0_r_3_0);
						break;

					case 1:
						processBwData(bw_i_0_r_3_1);
						break;
				}
			}
			break;
	}
}

VOID BWData::processBw_i_1(int t_index)
{
	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_1_r_0_0);
						break;

					case 1:
						processBwData(bw_i_1_r_0_1);
						break;
				}
			}
			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_1_r_1_0);
						break;

					case 1:
						processBwData(bw_i_1_r_1_1);
						break;
				}
			}
			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_1_r_2_0);
						break;

					case 1:
						processBwData(bw_i_1_r_2_1);
						break;
				}
			}
			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_1_r_3_0);
						break;

					case 1:
						processBwData(bw_i_1_r_3_1);
						break;
				}
			}
			break;
	}
}

VOID BWData::processBw_i_2(int t_index)
{
	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_2_r_0_0);
						break;

					case 1:
						processBwData(bw_i_2_r_0_1);
						break;
				}
			}
			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_2_r_1_0);
						break;

					case 1:
						processBwData(bw_i_2_r_1_1);
						break;
				}
			}
			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_2_r_2_0);
						break;

					case 1:
						processBwData(bw_i_2_r_2_1);
						break;
				}
			}
			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_2_r_3_0);
						break;

					case 1:
						processBwData(bw_i_2_r_3_1);
						break;
				}
			}
			break;
	}
}

VOID BWData::processBw_i_3(int t_index)
{
	switch(routerId)
	{
		case 0:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_3_r_0_0);
						break;

					case 1:
						processBwData(bw_i_3_r_0_1);
						break;
				}
			}
			break;

		case 1:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_3_r_1_0);
						break;

					case 1:
						processBwData(bw_i_3_r_1_1);
						break;
				}
			}
			break;

		case 2:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_3_r_2_0);
						break;

					case 1:
						processBwData(bw_i_3_r_2_1);
						break;
				}
			}
			break;

		case 3:
			{
				switch(t_index)
				{
					case 0:
						processBwData(bw_i_3_r_3_0);
						break;

					case 1:
						processBwData(bw_i_3_r_3_1);
						break;
				}
			}
			break;
	}

}
