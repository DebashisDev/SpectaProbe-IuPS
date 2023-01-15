#########################################################################
#																		#
# SCRIPT NAME	: Makefile												#
# DESCRIPTION	: To build all .cpp files								#
# DATE 			: 19-02-2016										    #
# AUTHOR		: Debashis.											    #
#																		#
# Copyright (c) 2016, Pinnacle Digital (P) Ltd. New-Delhi				# 
#########################################################################

include ${PROBE_ROOT}/probe.mk
OBJS= \
	GTPcFlusher.o \
	GTPConfig.o \
	GTPCParser.o \
	GTPFlusherZmq.o \
	GTPGlobal.o \
	GTPMessage.o \
	GTPMessageBroker.o \
	GTPSessionManager.o \
	GTPuFlusher.o \
	GTPUParser.o \
	GTPV1Parser.o \
	GTPXdrFlusher.o
	
all:${OBJS}

.cpp.o:

	${GCC} ${CFLAGS} -I/usr/include ${PROBE_INCLUDE} -c $<

clean:
	${RM} ${OBJS}
