/*
 * IPv4Layer.h
 *
 *  Created on: Oct 24, 2016
 *      Author: Debashis
 */

#ifndef PLUGINS_GN_INC_IPV4LAYER_H_
#define PLUGINS_GN_INC_IPV4LAYER_H_

#include "IpAddress.h"

/// @file

/**
 * \namespace GTPParser
 * \brief The main namespace for the GTPParser lib
 */
	/**
	 * @struct iphdr
	 * Represents an IPv4 protocol header
	 */
#pragma pack(push, 1)
	struct iphdr {
#if (BYTE_ORDER == LITTLE_ENDIAN)
		/** IP header length, has the value of 5 for IPv4 */
		uint8_t internetHeaderLength:4,
		/** IP version number, has the value of 4 for IPv4 */
				ipVersion:4;
#else
		/** IP version number, has the value of 4 for IPv4 */
		uint8_t ipVersion:4,
		/** IP header length, has the value of 5 for IPv4 */
				internetHeaderLength:4;
#endif
		/** type of service, same as Differentiated Services Code Point (DSCP)*/
		uint8_t typeOfService;
		/** Entire packet (fragment) size, including header and data, in bytes */
		uint16_t totalLength;
		/** Identification field. Primarily used for uniquely identifying the group of fragments of a single IP datagram*/
		uint16_t ipId;
		 /** Fragment offset field, measured in units of eight-byte blocks (64 bits) */
		uint16_t fragmentOffset;
		/** An eight-bit time to live field helps prevent datagrams from persisting (e.g. going in circles) on an internet.  In practice, the field has become a hop count */
		uint8_t timeToLive;
		/** Defines the protocol used in the data portion of the IP datagram. Must be one of ::IPProtocolTypes */
		uint8_t protocol;
		/** Error-checking of the header */
		uint16_t headerChecksum;
		/** IPv4 address of the sender of the packet */
		uint32_t ipSrc;
		/** IPv4 address of the receiver of the packet */
		uint32_t ipDst;
		/*The options start here. */

		//45
		//00 - service type
		//00 60 - len
		//1c 2b - identification
		//00 - flag
		//00 - offset
		//7e - ttl
		//11 - protocol
		//c5 cb - checksum
		//da f8 52 7e - source ip
		//da f8 52 27 - dest ip
		//08 68 08 68 ---
	};
#pragma pack(pop)

#define GTPParser_IP_DONT_FRAGMENT  0x40
#define GTPParser_IP_MORE_FRAGMENTS 0x20

#endif /* PLUGINS_GN_INC_IPV4LAYER_H_ */
