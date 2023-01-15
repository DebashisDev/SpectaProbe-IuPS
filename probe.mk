#########################################################################
#																		#
# SCRIPT NAME	: probe.mk												#
# DESCRIPTION	: Include script for SpectaProbe						#
# DATE 			: 19-02-2016										    #
# AUTHOR		: Debashis.											    #
#																		#
# Copyright (c) 2016, Pinnacle Digital (P) Ltd. New-Delhi				# 
#########################################################################

#GCC = g++ -g -std=c++11 -Wall -Wno-deprecated -O1 -w

GCC = g++ -g -O0 -g3 -Wall -std=c++11 -fPIC -Wno-deprecated -w


#CFLAGS = -DNDEBUG   -m64 -mtune=native -Werror -Wall -Wundef -Wpointer-arith -fomit-frame-pointer -O2 -g
CFLAGS = -D_MT_SAFE -D_REENTRANT -D_POSIX_THREAD_SAFE_FUNCTIONS -D_GNU_SOURCE -D_PTHREADS -D_POSIX_PTHREAD_SEMANTICS -D_POSIX_C_SOURCE=199506L -D__EXTENSIONS__

AR 			= ar
ARFLAGS = -r
RM 			= rm 
MAKE 		= make

PROBE_BIN		= ${PROBE_ROOT}/bin

# SpectaProbe Directory

CORE_ROOT		= ${PROBE_ROOT}/core
CORE_INC		= ${CORE_ROOT}/inc
CORE_SRC		= ${CORE_ROOT}/src

TCP_ROOT		= ${PROBE_ROOT}/plugins/tcp
TCP_INC			= ${TCP_ROOT}/inc
TCP_SRC			= ${TCP_ROOT}/src

LOG_ROOT		= ${PROBE_ROOT}/utility/log
LOG_SRC			= ${LOG_ROOT}/src
LOG_INC			= ${LOG_ROOT}/inc

ETH_ROOT		= ${PROBE_ROOT}/packetsource/ethernet
ETH_SRC			= ${ETH_ROOT}/src
ETH_INC			= ${ETH_ROOT}/inc

PCAP_ROOT		= ${PROBE_ROOT}/packetsource/pcap
PCAP_SRC		= ${PCAP_ROOT}/src
PCAP_INC		= ${PCAP_ROOT}/inc

SF_ROOT			= ${PROBE_ROOT}/packetsource/solarflare
SF_SRC			= ${SF_ROOT}/src
SF_INC			= ${SF_ROOT}/inc/solar
SFS_INC			= ${SF_ROOT}/inc/specta

SCCP_ROOT		= ${PROBE_ROOT}/plugins/sccp
SCCP_SRC		= ${SCCP_ROOT}/src
SCCP_INC		= ${SCCP_ROOT}/inc

IUPS_ROOT		= ${PROBE_ROOT}/plugins/iups
IUPS_SRC		= ${IUPS_ROOT}/src
IUPS_INC		= ${IUPS_ROOT}/inc

S1MME_ROOT		= ${PROBE_ROOT}/plugins/s1mme
S1MME_SRC		= ${S1MME_ROOT}/src
S1MME_INC		= ${S1MME_ROOT}/inc

GN_ROOT			= ${PROBE_ROOT}/plugins/gn
GN_SRC			= ${GN_ROOT}/src
GN_INC			= ${GN_ROOT}/inc

BB_ROOT			= ${PROBE_ROOT}/broadband
BB_SRC			= ${BB_ROOT}/src
BB_INC			= ${BB_ROOT}/inc

GX_ROOT			= ${PROBE_ROOT}/plugins/gx
GX_SRC			= ${GX_ROOT}/src
GX_INC			= ${GX_ROOT}/inc

RADIUS_ROOT		= ${PROBE_ROOT}/plugins/radius
RADIUS_SRC		= ${RADIUS_ROOT}/src
RADIUS_INC		= ${RADIUS_ROOT}/inc

THIRDPARTY_INC  = ${PROBE_ROOT}/thirdparty

OSSASN1_ROOT    = /home/specta/Debashis/Software/asn1cpp/linux-x86-64/6.7.0
OSS_BIN                 = $(OSSASN1_ROOT)/bin
OSS_INC                 = $(OSSASN1_ROOT)/include
OSS_LIB                 = $(OSSASN1_ROOT)/lib
OSS_DFLT                = $(OSSASN1_ROOT)
PROTOBUF_DIR		= ${PROBE_ROOT}/proto

PROBE_INCLUDE 	= \
				-I${CORE_INC} \
				-I${LOG_INC} \
				-I${ETH_INC} \
				-I${SF_INC} \
				-I${SFS_INC} \
				-I${PCAP_INC} \
				-I${TCP_INC} \
				-I${BB_INC} \
				-I${GN_INC} \
				-I${SCCP_INC} \
				-I${IUPS_INC} \
				-I${S1MME_INC} \
				-I${OSS_INC}
				
