#########################################################################
#																		#
# SCRIPT NAME	: Makefile												#
# DESCRIPTION	: To build the SpectaProbe along with user librarys		#
# DATE 			: 19-02-2016										    #
# AUTHOR		: Debashis.											    #
#																		#
# Copyright (c) 2016, Pinnacle Digital (P) Ltd. New-Delhi.				# 
#########################################################################

# Include all the header directories.
include ${PROBE_ROOT}/probe.mk

PROBE_DIRS = 	\
	${CORE_SRC} \
	${LOG_SRC} 	\
	${SF_SRC} 	\
	${ETH_SRC} 	\
	${PCAP_SRC} \
	${TCP_SRC} 	\
	${BB_SRC} 	\
	${GN_SRC}	\
	${SCCP_SRC} \
	${IUPS_SRC}

#########################################################################
# SCP Platform and Platform Library File Name														#
#########################################################################
PROBE_TARGET	= ${PROBE_BIN}/spectaProbe

#System Library
PCAPLIB 	= pcap
THRLIB 		= pthread
ZMQLIB 		= zmq
SOLARLIB	= ${PROBE_ROOT}/lib/libciul.so
PROTOBUF	= /usr/local/lib/libprotobuf.so

ASNLIB		= ${OSS_LIB}/libosscpp.so ${OSS_LIB}/libcpptoed.so

LIBS 		= $(ASNLIB) -lm -ldl -l$(PCAPLIB) -l$(THRLIB) -l$(ZMQLIB)
#LIBS 		= -lm -ldl -l$(PCAPLIB) -l$(THRLIB) -l$(ZMQLIB)

#########################################################################
# For SpectaProbe
#########################################################################
probe:
	for i in ${PROBE_DIRS}; \
	do \
		(cd $$i; \
		echo "*******" $$i; \
		${MAKE} all \
		); \
	done

	${GCC} -o ${PROBE_TARGET} $(ASNLIB) ${SOLARLIB}	\
						${TCP_SRC}/*.o 		\
						${CORE_SRC}/*.o 	\
						${LOG_SRC}/*.o 		\
						${SF_SRC}/*.o		\
						${ETH_SRC}/*.o 		\
						${PCAP_SRC}/*.o 	\
						${BB_SRC}/*.o 		\
						${GN_SRC}/*.o		\
						${SCCP_SRC}/*.o 	\
						${IUPS_SRC}/*.o 	\
						${LIBS}

#########################################################################

clean:
	for i in ${PROBE_DIRS}; \
	do \
		(cd $$i; \
		echo $$i; \
		${MAKE} clean \
		); \
	done

	${RM} ${PROBE_TARGET}
