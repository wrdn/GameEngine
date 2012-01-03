#pragma once

#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define SEC_TO_MICROSEC(x) 1000000*x
#define SEC_TO_MILLISEC(x) 1000*x
#define SEC_TO_NANOSEC(x) 1000000000*x

#define NANOSEC_TO_SEC(x) x/1000000000.0
#define MILLISEC_TO_SEC(x) x/1000.0
#define MICROSEC_TO_SEC(x) x/1000000.0

class PerfTimer
{
private:
#ifdef _WIN32
	LARGE_INTEGER _start,_end,frequency;
#else
	timespec tstart, tend;
#endif
public:
	PerfTimer(void);
	~PerfTimer(void);

	void start();
	void end();
	double time(); // Time between start and end in seconds
};