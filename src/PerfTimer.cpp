#include "PerfTimer.h"

PerfTimer::PerfTimer(void)
{
#ifdef _WIN32
	QueryPerformanceFrequency(&frequency);
#endif
}

PerfTimer::~PerfTimer(void) { }

void PerfTimer::start()
{
#ifdef _WIN32
	QueryPerformanceCounter(&_start);
#else
	clock_gettime(CLOCK_REALTIME,&tstart);
#endif
}

void PerfTimer::end()
{
#ifdef _WIN32
	QueryPerformanceCounter(&_end);
#else
	clock_gettime(CLOCK_REALTIME,&tend);
#endif
}

double PerfTimer::time()
{
#ifdef _WIN32
	return (_end.QuadPart - _start.QuadPart)
		/ (double)frequency.QuadPart;
#else
	timespec temp;
	if((tend.tv_nsec-tstart.tv_nsec)<0)
	{
		temp.tv_nsec = 1000000000+tend.tv_nsec-tstart.tv_nsec;
	}
	else
	{
		temp.tv_nsec = tend.tv_nsec-tstart.tv_nsec;
	}
	return (double)NANOSEC_TO_SEC(temp.tv_nsec);
#endif
}
