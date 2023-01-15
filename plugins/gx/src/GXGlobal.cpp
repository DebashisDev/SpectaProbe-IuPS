/*
 * GXGlobal.cpp
 *
 *  Created on: Oct 13, 2016
 *      Author: Debashis
 */


#include "GXGlobal.h"

namespace GXFlushMap {
		std::map<ULONG, gxSession> gxEndSessionMap_0;
		std::map<ULONG, gxSession> gxEndSessionMap_1;
		std::map<ULONG, gxSession> gxEndSessionMap_2;
		std::map<ULONG, gxSession> gxEndSessionMap_3;
		std::map<ULONG, gxSession> gxEndSessionMap_4;
		std::map<ULONG, gxSession> gxEndSessionMap_5;
		std::map<ULONG, gxSession> gxEndSessionMap_6;
		std::map<ULONG, gxSession> gxEndSessionMap_7;
		std::map<ULONG, gxSession> gxEndSessionMap_8;
		std::map<ULONG, gxSession> gxEndSessionMap_9;

		ULONG gxEndSessionMapCounter_0 = 0;
		ULONG gxEndSessionMapCounter_1 = 0;
		ULONG gxEndSessionMapCounter_2 = 0;
		ULONG gxEndSessionMapCounter_3 = 0;
		ULONG gxEndSessionMapCounter_4 = 0;
		ULONG gxEndSessionMapCounter_5 = 0;
		ULONG gxEndSessionMapCounter_6 = 0;
		ULONG gxEndSessionMapCounter_7 = 0;
		ULONG gxEndSessionMapCounter_8 = 0;
		ULONG gxEndSessionMapCounter_9 = 0;
}

namespace GXAVPMap {
TCHAR *bearerOperation[] = {
								 "Termination",		// 0
								 "Establishment",	// 1
								 "Modification"		// 2
						   };

TCHAR *requestType[] = {
								"NA",						// 0
								"Initial Request",			// 1
								"Update Request",			// 2
								"Termination Request"		// 3
					  };

TCHAR *terminationCause[] = {
								"NA",						// 0
								"Logout",					// 1
								"NA",						// 2
								"NA",						// 3
								"NA",						// 4
								"NA",						// 5
								"Authentication Expired",	// 6
								"NA",						// 7
								"Session TimeOut"			// 8
					  };
}
