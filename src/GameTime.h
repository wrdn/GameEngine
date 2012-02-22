#pragma once
#include <ctime>
#include "ctypes.h"
#include <stdio.h>
#include <GL/freeglut.h>

/*
// GXBase timing code
#ifdef __linux__
#include <sys/time.h>
static unsigned int sys_get_msec()
{
        static struct timeval tv0;
        struct timeval tv;

        gettimeofday(&tv, 0);
        if(tv0.tv_sec == 0) {
                tv0 = tv;
        }
        return (tv.tv_sec - tv0.tv_sec) * 1000 + (tv.tv_usec - tv0.tv_usec) / 1000;
}
#elif _WIN32
#include <Windows.h>
static u32 sys_get_msec()
{
	return timeGetTime();
};
#endif

double GetTime() { return (double)sys_get_msec() / 1000.0; };
double GetDeltaTime()
{
	const double TimeInterval = 1.0 / 60.0;
	double timeNow = (double)sys_get_msec() / 1000.0;
	static double timeOld = timeNow - TimeInterval;
	double delta = timeNow - timeOld;
	timeOld = timeNow;
	return delta;
};
*/

const int FPS_TARGET = 60;
const int SKIP_TICKS = 1000 / FPS_TARGET;


class GameTime
{
private:
	int old_time;
	double dt;
	int sleep_time;
	DWORD nextTick;

public:
	GameTime() : old_time(0), dt(0), sleep_time(0),
		nextTick(GetTickCount()) {};
	~GameTime() {};

	double Update()
	{
		nextTick += SKIP_TICKS;
		sleep_time = nextTick - GetTickCount();
		if(sleep_time >= 0) { Sleep(sleep_time); }
		return 1.0 / FPS_TARGET;
	};

	double GetDeltaTime() { return 1.0 / FPS_TARGET; };
};

/*
class GameTime
{
private:
	f32 currentTime, oldTime, deltaTime;

	clock_t lastTime, newTime;


	int glut_oldtime;

public:
	GameTime() : currentTime(0), oldTime(0), deltaTime(0) {};

	f32 GetCurrentTime() const { return currentTime; }
	f32 GetOldTime() const { return oldTime; }
	f32 GetDeltaTime() const { return deltaTime; }

	void Init()
	{
		currentTime = (f32)GetTime();
		oldTime = currentTime;
		deltaTime=0;

		glut_oldtime = 0;
	};

	f32 Update() // updates time and returns dt
	{
		int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		int deltaTimev = timeSinceStart - glut_oldtime;
		glut_oldtime = timeSinceStart;
		deltaTime = deltaTimev * 0.001f;
		return deltaTime;


		
		static const f32 TargetTime = 1.0f/30.0f; // target=30fps

		currentTime = (f32)GetTime();
		deltaTime = currentTime - oldTime;

		if(deltaTime > TargetTime)
		{
			//deltaTime = TargetTime;
		}

		oldTime = currentTime;
		//return deltaTime;



		lastTime = newTime;
		newTime = std::clock();
		//return (m_NewTime-m_LastTime)/(f32)CLOCKS_PER_SEC;
		deltaTime = (newTime-lastTime)/(f32)CLOCKS_PER_SEC;
		return deltaTime;
	};
};
*/