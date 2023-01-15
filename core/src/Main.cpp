#include <signal.h>


#include "SpectaProbe.h"

void sig_handler(int signo)
{
	if (signo == SIGTERM)
	{
		printf("\nSignal received at Main, Probe Shutdown Initiated....\n");
		IPGlobal::PROBE_RUNNING_STATUS = false;
	}
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("USAGE:: spectaProbe <<Config File Name>>\n");
		exit(1);
	}

	/* Initialize all the Locks */
	mapTcpLock::count 	= 1;
	mapUdpLock::count 	= 1;
	mapDnsLock::count 	= 1;
	mapOtrLock::count	= 1;
	mapGtpLock::count	= 1;
	mapGxLock::count	= 1;
	mapRaLock::count	= 1;
	gSessionLock::count = 1;

	if (signal(SIGTERM, sig_handler) == SIG_ERR)
		printf("SpectaProbe Can't Received Signal...\n");

	timeval curTime;
	struct tm *now_tm;

	gettimeofday(&curTime, NULL);
	now_tm = localtime(&curTime.tv_sec);
	IPGlobal::CURRENT_TIME_EPOCH_SEC 		= curTime.tv_sec;
	IPGlobal::CURRENT_TIME_EPOCH_MICRO_SEC 	= (curTime.tv_sec * 1000000) + curTime.tv_usec;
	IPGlobal::CURRENT_TIME_SEC 				= now_tm->tm_sec;
	IPGlobal::CURRENT_TIME_MIN 				= now_tm->tm_min;
	IPGlobal::CURRENT_TIME_HOUR 			= now_tm->tm_hour;
	IPGlobal::CURRENT_TIME_DAY 				= now_tm->tm_mday;
	IPGlobal::CURRENT_TIME_MONTH 			= 1 + now_tm->tm_mon;
	IPGlobal::CURRENT_TIME_YEAR 			= 1900 + now_tm->tm_year;

	IPGlobal::PROBE_RUNNING_STATUS = true;
	SpectaProbe *spectaProbe = new SpectaProbe(argv[1]);
	spectaProbe->start();

	printf("SpectaProbe Main Exiting...Please wait...\n");
}

