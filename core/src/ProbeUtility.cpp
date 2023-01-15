/*
 * ProbeUtility.cpp
 *
 *  Created on: 30-Jan-2016
 *      Author: debashis
 */

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <pcap.h>
#include <unistd.h>

#include "ProbeUtility.h"

ProbeUtility::ProbeUtility() {
}

ProbeUtility::~ProbeUtility() {
}

ULONG ProbeUtility::HextoDigits(TCHAR *hexadecimal)
{
	long decimalNumber=0;
	char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int i, j, power=0, digit;

	for(i=strlen(hexadecimal)-1; i >= 0; i--)
	{
		for(j=0; j<16; j++)
		{
			if(hexadecimal[i] == hexDigits[j])
			{
				decimalNumber += j*pow(16, power);
			}
		}
		 power++;
	}
	return decimalNumber;
}

ULONG ProbeUtility::getLength(const BYTE packet, size_t offset)
{
	TCHAR hexadecimal[10];
	hexadecimal[0] = 0;

	sprintf(hexadecimal, "%02x%02x%02x", packet[offset], packet[offset+1], packet[offset+2]);

	ULONG decimalNumber=0;
	char hexDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int i, j, power=0, digit;

	for(i=strlen(hexadecimal)-1; i >= 0; i--)
	{
		for(j=0; j<16; j++)
		{
			if(hexadecimal[i] == hexDigits[j])
			{
				decimalNumber += j*pow(16, power);
			}
		}
		 power++;
	}
	return decimalNumber;
}

uint32_t
ProbeUtility::getCurrentSec() {
	timeval curTime;
	gettimeofday(&curTime, NULL);

	TCHAR currentTime[84] = "";
	sprintf(currentTime, "%d", curTime.tv_sec);
	uint32_t ret = atoi(currentTime);
	currentTime[0] = 0;
	return ret;
}

uint32_t
ProbeUtility::getCurrentSecond() {
	int currentMin;
	time_t now;
	struct tm *now_tm;

	now = time(NULL);
	now_tm = localtime(&now);
	currentMin = now_tm->tm_sec;

	return currentMin;
}

uint32_t
ProbeUtility::getCurrentMinute() {
	int currentMin;
	time_t now;
	struct tm *now_tm;

	now = time(NULL);
	now_tm = localtime(&now);
	currentMin = now_tm->tm_min;

	return currentMin;
}

ULONG
ProbeUtility::getCurrentMilliSec() {
	timeval curTime;
	TCHAR currentTime[31];
	currentTime[0] = 0;

	gettimeofday(&curTime, NULL);

	snprintf (currentTime, 31, "%lu%03lu", curTime.tv_sec, curTime.tv_usec / 1000);
	ULONG ret = atol(currentTime);
	currentTime[0] = 0;
	return ret;
}

TCHAR
*ProbeUtility::getCurrentTimeStamp() {
	timeval curTime;
	gettimeofday(&curTime, NULL);

	TCHAR buffer [80];
	TCHAR currentTime[84];
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
	sprintf(currentTime, "%s.%06d", buffer, curTime.tv_usec);
	return currentTime;
}

TCHAR
*ProbeUtility::getSystemTimeStamp(TCHAR *currentTime) {
	timeval curTime;
	gettimeofday(&curTime, NULL);

	TCHAR buffer [80];
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

	sprintf(currentTime, "%s", buffer);
	buffer[0] = 0;
	return currentTime;
}

TCHAR
*ProbeUtility::getSystemTimeHM(TCHAR *currentTime) {
	timeval curTime;
	gettimeofday(&curTime, NULL);

	TCHAR buffer [80];
	strftime(buffer, 80, "%Y-%m-%d-%H-%M", localtime(&curTime.tv_sec));

	sprintf(currentTime, "%s", buffer);
	buffer[0] = 0;
	return currentTime;
}


ULONG ProbeUtility::getEpochTimeMicroSecond() {
	timeval curTime;
	gettimeofday(&curTime, NULL);
	return curTime.tv_sec*1000000 + curTime.tv_usec;
}

VOID
ProbeUtility::Append(UCHAR *original, const UCHAR *add)
{
   while(*original)
      original++;

   while((*original++ = *add++))
   *original = 0;
}

VOID
ProbeUtility::printBytes(const UCHAR *identifier, bool printflag, const UCHAR *packet, uint32_t size)
{
	if(printflag){
		printf("  %s packet of size [%d] bytes", identifier, size);
		for(uint32_t i=0;i<size;i++){
			if((i%16 == 0)) printf("\n	%04x ", i);
			printf("%02x ", packet[i]);
		}
		printf("\n\n");
	}
}

char *getDateTimeWithMilliSec(TCHAR *buffer) {
	timeval curTime;
	gettimeofday(&curTime, NULL);
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
	return buffer;
}

uint16_t
ProbeUtility::parseTcpTimeStamp(struct tcphdr *tcp, ULONG *tsval, ULONG *tsecr)
{
	UCHAR *tcpHeader;
	uint32_t op, opLen, len;

	if (!tsval || !tsecr)
		return 0;

	tcpHeader = ((UCHAR *)tcp) + sizeof(*tcp);
	len = 4 * tcp->doff - sizeof(*tcp);

	while (len > 0 && *tcpHeader != TCPOPT_EOL)
	{
		op = *tcpHeader++;

		if (op == TCPOPT_EOL)
			break;

		if (op == TCPOPT_NOP)
		{
			len--;
			continue;
		}

		opLen = *tcpHeader++;

		if (opLen < 2)
			break;

		if (opLen > len)
			break; /* not enough space */

		if (op == TCPOPT_TIMESTAMP && opLen == 10)
		{
			/* legitimate timestamp option */
			if (tsval)
			{
				memcpy((char *)tsval, tcpHeader, 4);
				*tsval = (uint32_t)ntohl(*tsval);
			}

			tcpHeader += 4;

			if (tsecr)
			{
				memcpy((char *)tsecr, tcpHeader, 4);
				*tsecr = (uint32_t)ntohl(*tsecr);
			}
			return 1;
		}

		len -= opLen;
		tcpHeader += opLen - 2;
	}
	*tsval = 0;
	*tsecr = 0;
	return 0;
}

VOID
ProbeUtility::getIPHex(UCHAR *address, UCHAR *hexaddress)
{
	UCHAR *p, a[25];
	uint32_t i = 0;

	p = NULL;
	a[0] = 0;
	p = (UCHAR *)strtok((char *)address, ".");

	while(p!= NULL)
	{
		sprintf((char *)a, "%02x", atoi((const char *)p));
	    strcat((char *)hexaddress, (const char *)a);
	    a[0] = 0;

	    if(i < 3)
	      strcat((char *)hexaddress, ".");
	    p = (UCHAR *)strtok(NULL, ".");
	    i++;
	}
}

VOID
ProbeUtility::fillIP(UCHAR *address, UCHAR *fillInAddress)
{
	UCHAR *p, a[25];
	uint32_t i = 0;

	p = NULL;
	a[0] = 0;
	p = (UCHAR *)strtok((char *)address, ".");

	while(p!= NULL)
	{
		sprintf((char *)a, "%03d", atoi((const char *)p));
	    strcat((char *)fillInAddress, (const char *)a);
	    a[0] = 0;

	    if(i < 3)
	      strcat((char *)fillInAddress, ".");
	    p = (UCHAR *)strtok(NULL, ".");
	    i++;
	}
}

VOID
ProbeUtility::flushHTTPData(const UCHAR *sIP, const UCHAR * dIP, uint16_t sP, uint16_t dP, UCHAR *tokenBuf)
{
	TCHAR zmqBuffer[10240];
	zmqBuffer[0] = 0;

	sprintf(zmqBuffer, "%d,%d,%s,%s,%d,%s,%d,%s", 10, PACKET_IPPROTO_TCP, "HTTP", sIP, sP, dIP, dP, tokenBuf);
	zmqBuffer[strlen(zmqBuffer)+1] = '\0';

	IPGlobal::httpLogHandler << zmqBuffer << endl;
	zmqBuffer[0] = 0;
}


VOID
ProbeUtility::ExtractIP4Address(const BYTE packet, UCHAR *ipBuffer, uint32_t loc)
{
	unsigned int address;

	address = (packet[loc] << 24) | (packet[loc+1] << 16) | (packet[loc+2] << 8) | (packet[loc+3]);
	sprintf((char *)ipBuffer,"%d.%d.%d.%d",(address & 0xFF000000) >> 24,(address & 0x00FF0000) >> 16,(address & 0x0000FF00) >> 8, address & 0x000000FF);
}

//VOID
//ProbeUtility::ExtractIP4AddressR(const BYTE packet, UCHAR *ipBuffer, uint32_t loc)
//{
//	unsigned int address;
//
//	address = (packet[loc+3] << 24) | (packet[loc+2] << 16) | (packet[loc+1] << 8) | (packet[loc]);
//	sprintf((char *)ipBuffer,"%d.%d.%d.%d",(address & 0xFF000000) >> 24,(address & 0x00FF0000) >> 16,(address & 0x0000FF00) >> 8, address & 0x000000FF);
//}

VOID
ProbeUtility::ExtractIP6Address(const UCHAR *packet, UCHAR *ipBuffer, uint32_t loc)
{
	sprintf((char *)ipBuffer,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", packet[loc], packet[loc+1], \
			packet[loc+2], packet[loc+3], packet[loc+4], packet[loc+5], packet[loc+6], packet[loc+7], packet[loc+8], packet[loc+9], \
			packet[loc+10], packet[loc+11], packet[loc+12], packet[loc+13], packet[loc+14], packet[loc+15], packet[loc+16]);
}

void ProbeUtility::pinThread(pthread_t th,int core_num)
{
	   cpu_set_t cpuset;

           /* Set affinity mask to include CPUs 0 to 7 */

           CPU_ZERO(&cpuset);
           CPU_SET(core_num,&cpuset);

           int s = pthread_setaffinity_np(th, sizeof(cpu_set_t), &cpuset);
           if (s != 0)
               handle_error_en(s, "pthread_setaffinity_np");

           /* Check the actual affinity mask assigned to the thread */

           s = pthread_getaffinity_np(th, sizeof(cpu_set_t), &cpuset);
           if (s != 0)
               handle_error_en(s, "pthread_getaffinity_np");

           printf("Set returned by pthread_getaffinity_np() contained:\n");
           if (CPU_ISSET(core_num, &cpuset))
               printf("    CPU %d\n", core_num);

}


string ProbeUtility::convertToTimeStamp(ULONG currentTime) {
        TCHAR retBuffer[84];
        TCHAR buffer [80];
	
	buffer[0] = retBuffer[0] = 0;

        time_t t = (currentTime / 1000000);
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&t));

        sprintf(retBuffer, "%s.%06d", buffer, currentTime % 1000000);
	//printf("%ld | %s\n", currentTime, retBuffer);
	string str(retBuffer);
        return str;
}


//string ProbeUtility::getDNSKey(uint32_t destAddrLong, uint32_t sourceAddrLong)
//{
//	char dnsKey[25];
//	sprintf(dnsKey,"%010u-%010u",destAddrLong,sourceAddrLong);
//	return std::string(dnsKey);
//}

uint16_t ProbeUtility::getHourToProcess(uint16_t lastProcessedHour)
{
	uint16_t toProcessHour = lastProcessedHour + 1;
	if(toProcessHour > 23)
		toProcessHour = 0;
	return toProcessHour;
}

int16_t ProbeUtility::getPreviousHour(uint16_t currentHour)
{
	int16_t previousHour = currentHour - 1;
	if(previousHour < 0)
		previousHour = 23;
	return previousHour;
}

uint16_t ProbeUtility::getMinToProcess(uint16_t lastProcessedMin)
{
	uint16_t toProcessMin = lastProcessedMin + 1;
	if(toProcessMin > 59)
		toProcessMin = 0;
	return toProcessMin;
}

int16_t ProbeUtility::getPreviousMin(uint16_t currentMin)
{
	int16_t previousMin = currentMin - 1;
	if(previousMin < 0)
		previousMin = 59;
	return previousMin;
}

uint16_t ProbeUtility::getSecRangeToProcess(uint16_t lastProcessedSec)
{
	uint16_t toProcessMin = lastProcessedSec + 1;
	if(toProcessMin > 59)
		toProcessMin = 0;

	toProcessMin = toProcessMin/10;

	return toProcessMin;
}


uint16_t ProbeUtility::getProcessIndex(uint16_t prevIndex)
{
	prevIndex++;
	if(prevIndex > 5 )
		prevIndex = 0;

	return prevIndex;
}

uint16_t ProbeUtility::getPrevIndex(uint16_t currIndex)
{
	currIndex--;
	if(currIndex < 0 )
		currIndex = 5;

	return currIndex;
}

uint16_t ProbeUtility::getCurrentSecRange(uint16_t current)
{
	uint16_t currSecRange = 0;

	currSecRange = current/10;

	return currSecRange;
}

uint16_t ProbeUtility::getNextSecRange(uint16_t currentRange)
{
	currentRange++;
	if(currentRange > 5 )
		currentRange = 0;

	return currentRange;
}

int16_t ProbeUtility::getPreviousSecRange(uint16_t currentSec)
{
	int16_t previousSec;

	previousSec = (currentSec/10) - 1;

	if(previousSec < 0)
		previousSec = 5;

	return previousSec;
}

void ProbeUtility::printPacketBytes(const BYTE packet, int size)
{
		for(int i=0;i<size;i++){
			if((i%16 == 0)) printf("\n	%04x ", i);
			printf("%02x ", packet[i]);
		}
		printf("\n\n");
}

vector<string> ProbeUtility::split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string token;

	while(getline(ss, token, delimiter)) {
	    internal.push_back(token);
	}
	return internal;
}

uint8_t ProbeUtility::matchIPs(uint32_t src, uint32_t dst, uint32_t net, uint32_t num_bits)
{
	return(matchIP(src, net, num_bits) || matchIP(dst, net, num_bits));
}


uint8_t ProbeUtility::matchIP(uint32_t ip_to_check, uint32_t net, uint32_t num_bits)
{
  uint32_t mask = 0;
  mask = ~(~mask >> num_bits);
  return(((ip_to_check & mask) == (net & mask)) ? true : false);
}

VOID ProbeUtility::HEXDUMP(const void* pv, int len)
{
	const unsigned char* p = (const unsigned char*) pv;
	int i;
	for( i = 0; i < len; ++i ) {
		const char* eos;
			switch( i & 15 ) {
				case 0:
					printf("%08x  ", i);
					eos = "";
					break;
				case 1:
					eos = " ";
					break;
				case 15:
					eos = "\n";
					break;
				default:
					eos = (i & 1) ? " " : "";
					break;
			}
			printf("%02x%s", (unsigned) p[i], eos);
	}
	printf(((len & 15) == 0) ? "\n" : "\n\n");
}

char* ProbeUtility::getByteToHex(const void* pv, int len)
{
	char datadump[10000];
	char buffer[20];

	datadump[0] = buffer[0] = 0;

	const unsigned char* p = (const unsigned char*) pv;
		int i;
		for( i = 0; i < len; ++i ) {
			const char* eos;
				switch( i & 15 ) {
					case 0:
						sprintf(buffer,"%08x  ", i);
						strcat(datadump,buffer);
						buffer[0] = 0;
						eos = "";
						break;
					case 1:
						eos = " ";
						break;
					case 15:
						eos = "\n";
						break;
					default:
						eos = (i & 1) ? " " : "";
						break;
				}
				sprintf(buffer, "%02x%s", (unsigned) p[i], eos);
				strcat(datadump,buffer);
				buffer[0] = 0;
		}
		//printf(((len & 15) == 0) ? "\n" : "\n\n");

	return datadump;
}

VOID ProbeUtility::writePcap(char *pcapFileName, const BYTE packet, uint64_t counter, int length, long tv_sec)
{
	char fName[10];

	fName[0] = 0;
	struct pcapPkthdr {
		uint32_t tv_sec;
		uint32_t tv_usec;
		uint32_t caplen;
		uint32_t len;
	 };

	FILE *ptr_myfile;
	sprintf(fName, "%lu-%s", counter, pcapFileName);
	ptr_myfile=fopen(fName, "wb");

	if (!ptr_myfile)
		printf("Unable to open file [%s] !\n", fName);


	struct pcap_file_header  fileHeader;
	fileHeader.magic = 0xa1b2c3d4;
	fileHeader.version_major = 2;
	fileHeader.version_minor = 4;
	fileHeader.thiszone = 0;
	fileHeader.sigfigs = 0;
	fileHeader.snaplen = 65535; //(2^16)
	fileHeader.linktype  = 1;     //Ethernet

	fwrite(&fileHeader, sizeof(fileHeader), 1, ptr_myfile);

	pcapPkthdr pkhdr;
//	pkhdr.len = pkhdr.caplen = (uint32_t)rawPkt->len;
	pkhdr.len = pkhdr.caplen = (uint32_t)length;
//	gettimeofday(&curTime, NULL);
	pkhdr.tv_sec = tv_sec;

	fwrite(&pkhdr, sizeof(pkhdr), 1, ptr_myfile);
	fwrite(packet, length, 1, ptr_myfile);

	fclose(ptr_myfile);

	printf("pcap file written for length %d...\n", length);


	ifstream::pos_type size;
	char * memblock;

	ifstream file (fName, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		ProbeUtility::HEXDUMP(memblock,size);
	}
}
