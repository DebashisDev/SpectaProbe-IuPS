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
	BaseConfig.o \
	BWData.o \
	EthernetParser.o \
	GConfig.o \
	GConstant.o \
	IpAddress.o \
	IPGlobal.o \
	Main.o \
	OtherIPV4Parser.o \
	ProbeUtility.o \
	SpectaProbe.o \
	PacketRouter.o \
	TraceListener.o \
	ProbeStats.o

all:${OBJS}

.cpp.o:

	${GCC} ${CFLAGS} -I/usr/include ${PROBE_INCLUDE} -c $< 

clean:
	${RM} ${OBJS}