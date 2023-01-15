/*
 * Common.h
 *
 *  Created on: Nov 14, 2015
 *      Author: debashis
 */

#ifndef INC_SPECTATYPEDEF_H_
#define INC_SPECTATYPEDEF_H_

#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
typedef char				 	TCHAR;
typedef char *				 	PCHAR;
typedef const char * 		 	CCHAR;
typedef long			     	LONG;
typedef long *			     	PLONG;
typedef	unsigned long * 	 	UPLONG;
typedef	unsigned short	     	USHORT;
typedef	unsigned long	     	ULONG;
typedef bool			     	BOOL;
typedef void			     	VOID;

typedef float					FLOAT;

typedef unsigned char	     	UCHAR;

typedef unsigned char *      	BYTE;

typedef short int				int16_t;
typedef int						int32_t;
typedef long int				int64_t;
typedef long long int			int128_t;
typedef unsigned short int		uint16_t;
typedef unsigned int			uint32_t;
typedef unsigned long int		uint64_t;
typedef unsigned long long int	uint128_t;

static const char* HexLkp2 =
	"000102030405060708090A0B0C0D0E0F"
	"101112131415161718191A1B1C1D1E1F"
	"202122232425262728292A2B2C2D2E2F"
	"303132333435363738393A3B3C3D3E3F"
	"404142434445464748494A4B4C4D4E4F"
	"505152535455565758595A5B5C5D5E5F"
	"606162636465666768696A6B6C6D6E6F"
	"707172737475767778797A7B7C7D7E7F"
	"808182838485868788898A8B8C8D8E8F"
	"909192939495969798999A9B9C9D9E9F"
	"A0A1A2A3A4A5A6A7A8A9AAABACADAEAF"
	"B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
	"C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF"
	"D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
	"E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF"
	"F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";

#ifndef VAL_BYTE
#define VAL_BYTE(p)     (*(p))
#endif

#ifndef VAL_USHORT
#define VAL_USHORT(p)   (ntohs(*((unsigned short *)(p) )))
#endif

#ifndef VAL_ULONG
#define	VAL_ULONG(p)	(ntohl(*((unsigned long *)(p) )))
#endif

static const char* B2H[] = {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};

inline UCHAR *Byte2Hex(UCHAR a1, UCHAR *pBuf)
{
	uint16_t * pptbl = (uint16_t*) HexLkp2;
	uint16_t * ppout = (uint16_t*) pBuf;
    *ppout = pptbl[a1];
    pBuf[2] = 0;
    return pBuf + 2;
}

inline UCHAR *Long2Hex(ULONG a1, UCHAR *pBuf)
{
	uint16_t * pptbl = (uint16_t*) HexLkp2;
	uint16_t * ppout = (uint16_t*) pBuf;

    *ppout++=pptbl[(a1&0xff000000)>>24];
    *ppout++=pptbl[(a1&0x00ff0000)>>16];
    *ppout++=pptbl[(a1&0x0000ff00)>>8 ];
    *ppout++=pptbl[a1&0x000000ff];
    pBuf[8]=0;
    return pBuf+8;
}

inline TCHAR  *Long2IPHex(ULONG a1, TCHAR *pBuf)
 {
		uint16_t * pptbl = (uint16_t*) HexLkp2;
		uint16_t * ppout = (uint16_t*) pBuf;

     *ppout=pptbl[(a1&0xff000000)>>24]; ppout = (uint16_t*) (pBuf+3);
     *ppout=pptbl[(a1&0x00ff0000)>>16]; ppout = (uint16_t*) (pBuf+6);
     *ppout=pptbl[(a1&0x0000ff00)>>8];  ppout = (uint16_t*) (pBuf+9);
     *ppout=pptbl[(a1&0x000000ff)];
		pBuf[2]=pBuf[5]=pBuf[8]='.';
     pBuf[11]=0;

     return pBuf+11;
 }

inline UCHAR  Hex2Byte(UCHAR n1, UCHAR n2)
{
	n1=toupper(n1);
	n2=toupper(n2);

	UCHAR b1=(char *) isdigit(n1)?(n1-'0'):(n1-'A'+10);
	UCHAR b2=(char *) isdigit(n2)?(n2-'0'):(n2-'A'+10);

	return (b1<<4)|b2;
}

inline UCHAR * ExtractIP(UCHAR *pszString, UCHAR *pBuf)
{
	const UCHAR * pptr = pszString;
	UCHAR b[4];
	b[0]=Hex2Byte(pptr[0],pptr[1]);
	b[1]=Hex2Byte(pptr[3],pptr[4]);
	b[2]=Hex2Byte(pptr[6],pptr[7]);
	b[3]=Hex2Byte(pptr[9],pptr[10]);

	sprintf((char *)pBuf, "%u.%u.%u.%u", b[0],b[1],b[2],b[3]);
	return pBuf;
}

#endif /* INC_SPECTATYPEDEF_H_ */
