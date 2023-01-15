/*
 * PacketSSL.h
 *
 *  Created on: 24-Sep-2016
 *      Author: deb
 */

#ifndef SRC_PACKETSSL_H_
#define SRC_PACKETSSL_H_

#include "SpectaTypedef.h"
#include "IPGlobal.h"
#include "ProbeUtility.h"
#include "DnsData.h"

#define RDNSequenceTag			0x06

#define TLSv1_2					771
#define TLSv1					769

typedef enum {
    SSL_ID_CHG_CIPHER_SPEC     = 0x14,
    SSL_ID_ALERT               = 0x15,
    SSL_ID_HANDSHAKE           = 0x16,
    SSL_ID_APP_DATA            = 0x17,
    SSL_ID_HEARTBEAT           = 0x18
} contentType;

typedef enum {
    SSL_HELLO_REQUEST          = 0x00,
    SSL_CLIENT_HELLO           = 0x01,
    SSL_SERVER_HELLO           = 0x02,
    SSL_HELLO_VERIFY_REQUEST   = 0x03,
    SSL_NEWSESSION_TICKET      = 0x04,
    SSL_CERTIFICATE            = 0x0b,
    SSL_SERVER_KEY_EXCHG       = 0x0c,
    SSL_CERT_REQUEST           = 0x0d,
    SSL_SVR_HELLO_DONE         = 0x0e,
    SSL_CERT_VERIFY            = 0x0f,
    SSL_CLIENT_KEY_EXCHG       = 0x10,
    SSL_FINISHED               = 0x14,
    SSL_CERT_URL               = 0x15,
    SSL_CERT_STATUS            = 0x16,
    SSL_SUPPLEMENTAL_DATA      = 0x17,
    SSL_ENCRYPTED_EXTS         = 0x43
} HandshakeType;

class PacketSSL : public ProbeUtility, public DnsData {

	private:

	public:
		PacketSSL();
		~PacketSSL();

	VOID decodeSSL(const BYTE packet, MPacket *msgObj);
};

#endif /* SRC_PACKETSSL_H_ */
