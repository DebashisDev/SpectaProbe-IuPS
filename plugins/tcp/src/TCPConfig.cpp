/*
 * TCPConfig.cpp
 *
 *  Created on: 29-Jan-2016
 *      Author: deb
 */

#include <unistd.h>

#include "TCPConfig.h"

TCPConfig::TCPConfig() {
	tcpFlushIP[0] = 0;
	dnsFlushIP[0] = 0;
	readParameters();
	this->_name = "TCPConfig";
	this->setLogLevel(Log::theLog().level());
}

TCPConfig::~TCPConfig() {

}

void TCPConfig::readParameters(){

	printf("  Reading TCP configuration file...\n");

	char configPath[100];
	char *envConfigPath;
	char *probeRoot;
	char writeXdr[10];
	char flushFlag1[10];

	writeXdr[0] = flushFlag1[0] = 0;

	envConfigPath = getenv("PROBE_CONF");
	probeRoot = getenv("PROBE_ROOT");

	strcpy(GConstant::probeBaseDir, probeRoot);
	sprintf(configPath, "%s/%s", envConfigPath, IPGlobal::tcpConfigFile);

	/* ** TCP Open Configuration file ** */

	IPGlobal::tcpConfigHandler.open(configPath);

	if(IPGlobal::tcpConfigHandler.fail())
	{
		printf("  Error in Opening Configuration File : %s\n", configPath);
		exit(1);
	}
	printf("  Opened Configuration File : %s\n", configPath);

	string Key, Value, Value1;

	/* ** Read Configuration file ** */

	while(!IPGlobal::tcpConfigHandler.eof())
	{
		IPGlobal::tcpConfigHandler >> Key;
		if(Key.compare("TCP_FLUSH_IP") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(tcpFlushIP, Value.c_str());
		}
		else if(Key.compare("DNS_FLUSH_IP") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(dnsFlushIP, Value.c_str());
		}
		else if(Key.compare("INPUT_TYPE") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::inputType = atoi(Value.c_str());
		}
		else if(Key.compare("INPUT_SOURCE") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(IPGlobal::inputSource, Value.c_str());
		}
		else if(Key.compare("SM_QUEUE_PATH") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(IPGlobal::smQueuePath, Value.c_str());
		}
		else if(Key.compare("FF_QUEUE_PATH") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(IPGlobal::ffQueuePath, Value.c_str());
		}
		else if(Key.compare("LOG_LEVEL") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::logLevel = atoi(Value.c_str());
		}
		else if(Key.compare("WRITE_XDR") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(writeXdr, Value.c_str());

			if(!strcmp(writeXdr, "true"))
				IPGlobal::xdrFlag = 1;
		}
		else if(Key.compare("SESSION_CLEANUP_FREQ_IN_SEC") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::sessionCleanFreq = atoi(Value.c_str());
		}
		else if(Key.compare("IDLE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::idleSessionExpireTime = atoi(Value.c_str());
		}
		else if(Key.compare("ACTIVE_SESSION_TIMEOUT_IN_SEC") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::activeSessionExpireTime = atoi(Value.c_str());
		}
		else if(Key.compare("TCP_SESSION_PACKET_LIMIT") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::sliceValue = atoi(Value.c_str());
		}
		else if(Key.compare("VI_STREAMS") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			IPGlobal::viStreams = atoi(Value.c_str());
		}
		else if(Key.compare("FLUSH_FLAG") == 0)
		{
			IPGlobal::tcpConfigHandler >> Value;
			strcpy(flushFlag1, Value.c_str());

			if(!strcmp(flushFlag1, "true"))
				IPGlobal::flushFlag = 1;
		}
	}

	printf("TCP_FLUSH_IP               		:: %s\n", tcpFlushIP);
	printf("DNS_FLUSH_IP               		:: %s\n", dnsFlushIP);
	printf("INPUT_TYPE               		:: %d\n", IPGlobal::inputType);
	printf("INPUT_SOURCE               		:: %s\n", IPGlobal::inputSource);
	printf("LOG_LEVEL                  		:: %d\n", IPGlobal::logLevel);
	printf("WRITE_XDR                  		:: %d\n", IPGlobal::xdrFlag);
	printf("SESSION_CLEANUP_FREQ_IN_SEC		:: %d\n", IPGlobal::sessionCleanFreq);
	printf("IDLE_SESSION_TIMEOUT_IN_SEC     :: %d\n", IPGlobal::idleSessionExpireTime);
	printf("ACTIVE_SESSION_TIMEOUT_IN_SEC   :: %d\n", IPGlobal::activeSessionExpireTime);
	printf("TCP_SESSION_PACKET_LIMIT   		:: %d\n", IPGlobal::sliceValue);
	printf("VI_STREAMS                 		:: %d\n", IPGlobal::viStreams);
	printf("FLUSH_FLAG                 		:: %d\n", IPGlobal::flushFlag);

//	/* ** Open BW Flush file ** */
//
//	configPath[0] = 0;
//	sprintf(configPath, "%s%s.log", GConstant::AppBWFilePath, GConstant::bwLogFile);
//	IPGlobal::bwLogHandler.open((char *)configPath, ios :: out | ios :: app);
//
//	if(IPGlobal::bwLogHandler.fail())
//	{
//		printf("  Error in Opening BW Log File : %s\n", configPath);
//		exit(1);
//	}
//	else {
//		printf("  Opened BW Log File : %s\n", configPath);
//	}
	/* ** BW Flush file ** */

	/* ** Create TCP ZMQ ** */
	if(IPGlobal::flushFlag) {
		IPGlobal::tcpZmqContext = zmq_ctx_new ();
		IPGlobal::tcpZmqRequester = zmq_socket (IPGlobal::tcpZmqContext, ZMQ_PUSH);
		int tcpConnect = zmq_bind(IPGlobal::tcpZmqRequester, tcpFlushIP);
		if(!tcpConnect) {
			printf("  SpectaProbe Connected to : %s \n", tcpFlushIP);
		}
		else {
			printf("  SpectaProbe Couldn't Connected to : %s\n", tcpFlushIP);
			exit(1);
		}

		IPGlobal::dnsZmqContext = zmq_ctx_new ();
		IPGlobal::dnsZmqRequester = zmq_socket (IPGlobal::dnsZmqContext, ZMQ_PUSH);
		int dnsConnect = zmq_bind(IPGlobal::dnsZmqRequester, dnsFlushIP);

		if(!dnsConnect) {
			printf("  SpectaProbe Connected to : %s\n", dnsFlushIP);
		}
		else {
			printf("  SpectaProbe Couldn't Connected to : %s\n", dnsFlushIP);
			exit(1);
		}
	}
	else {
		printf("  SpectaProbe NOTE :: TCP & DNS ZMQ Push is Off\n");
	}

	// Read IP Range List from File and store in Vector

	std::string range;

	configPath[0] = 0;
	sprintf(configPath, "%s/%s", probeRoot, "ipRange.txt");
	ifstream ipRangeFile(configPath);

	while (ipRangeFile >> range) {
	        IPGlobal::ipRange.push_back(range);
	}

	ipRangeFile.close();

    for (unsigned n = 0; n < IPGlobal::ipRange.size(); ++n) {
       printf("  IP Range        : %s\n", IPGlobal::ipRange.at(n).c_str());
    }

	printf("  TCP configuration file read successfully.\n");
	sleep(1);
}
