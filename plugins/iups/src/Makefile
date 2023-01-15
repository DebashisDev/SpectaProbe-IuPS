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
	IUPSConfig.o \
	IUPSGlobal.o \
	IUPSSessionManager.o \
	NASParser.o \
	ranap.o \
	RANAPParser.o \
	IUPSFlusher.o \
	IUPSFlusherZmq.o
	
all:${OBJS}

.cpp.o:

	${GCC} ${CFLAGS} -I/usr/include ${PROBE_INCLUDE} -c $<

clean:
	${RM} IUPSConfig.o IUPSGlobal.o IUPSSessionManager.o NASParser.o RANAPParser.o IUPSFlusher.o IUPSFlusherZmq.o
