#include <iostream>
#include <stdio.h>
#include <assert.h>

#include <rapidxml.hpp>

#include "util.h"
#include "PerfTimer.h"

void *gGlobalMemoryBuffer = 0;

i32 add(const i32 a, const i32  b)
{
	return a+b;
};

#ifdef _DEBUG
//const u32 MAGIC_MEM_CLEAR = 0xEFBEADDE; // deadbeef on x86
const u32 MAGIC_MEM_CLEAR = 0xDEADBEEF;

inline void _dbg_fill_mem(void *mem, const u32 sz)
{
	printf("Debug mode\n");

	u32 *p = (u32*)mem;
	for(u32 i=0;i<sz/sizeof(u32);++i)
	{
		p[i] = MAGIC_MEM_CLEAR;
	}
};
inline void _dbg_check_mem(void* const mem, const u32 sz) // check for 0xDEADBEEF
{
	for(u32 i=0;i<sz/sizeof(u32);++i)
	{
		const u32 * const mval = &((u32*)mem)[i];
		assert(*mval == 0xDEADBEEF);
	}
	printf("_dbg_check_mem(%p, %d): Memory all OK\n", mem, sz);
};
#else
#define _dbg_fill_mem(mem,sz)
#define _dbg_check_mem(mem,sz)
#endif

int main(const int argc, const char **argv)
{



	const u32 SizeToAllocateInMB = 512; // Maximum memory application should be able to use
	const u32 AllocSize = (SizeToAllocateInMB * 1024) * 1024;

	PerfTimer pt;

	pt.start();
	gGlobalMemoryBuffer = malloc(AllocSize);
	pt.end();
	printf("Allocation time: %f\n", pt.time());

	pt.start();
	_dbg_fill_mem(gGlobalMemoryBuffer, AllocSize);
	pt.end();
	printf("Fill Memory time: %f\n", pt.time());

	pt.start();
	_dbg_check_mem(gGlobalMemoryBuffer, AllocSize);
	pt.end();
	printf("Memory check time: %f\n", pt.time());

	pt.start();
	free(gGlobalMemoryBuffer);
	pt.end();
	printf("Free time: %f\n", pt.time());

	getchar();
	return 0;
};
