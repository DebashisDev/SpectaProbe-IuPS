/*
 * Commondefs.h
 *
 *  Created on: Jun 9, 2016
 *      Author: soumen
 */

#ifndef INCLUDE_Commondefs_H_
#define INCLUDE_Commondefs_H_

namespace GTPParser
{

#define GTP_EXT_C1 0xC1
#define GTP_EXT_C2 0xC2
// ipv6 address len
#define MAX_ADDR_STRING_LEN 40
#define COMPLETE	true
#define ONGOING		false
#define IPV4		4
#define	IPV6		6
#define MAX_APN_LENGTH 100
#define MAX_IMSI_LEN	17
#define table_offset	0xFFF

#define	GTP_U_PORT		2152
#define	GTP_C_PORT		2123
#define GTP0_C_PORT		3386
#define GTP0_U_PORT     3386

/* change it for offset count */

#define octval		3

#define C_U				0x000
#define C_D				(1 << (octval*4 -2))
#define D_U				(2 << (octval*4 -2))
#define D_D				(3 << (octval*4 -2))
#define OFF_SET			(C_D -1)

// array index calculation based on tunnel id. MSB 2 bit for tied type
#define INDEX_CU(val)	(val & OFF_SET) | C_U
#define INDEX_CD(val)	(val & OFF_SET) | C_D
#define INDEX_DU(val)	(val & OFF_SET) | D_U
#define INDEX_DD(val)	(val & OFF_SET) | D_D

enum TIED_TYPE { CTL_UP = 0, CTL_DW =1, DATA_UP = 2, DATA_DW = 3 };
enum PROCEDURE_TYPE {
	CREATE = 0,
	UPDATE = 1,
	DELETE = 2,
	CREATE_SESSION = 3,
	UPDATE_SESSION = 4,
	DELETE_SESSION = 5,
	CREATE_BEARER = 6,
	UPDATE_BEARER = 7,
	MODIFY_BEARER = 8,
	DELETE_BEARER = 9
};

enum GTPheaderType_e
{
	version0 = 0,
	version1 = 1,
	version2 = 2,
	unknown = 3
};
}

#endif /* INCLUDE_Commondefs_H_ */
