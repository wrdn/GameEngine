#ifndef __UTIL_H__
#define __UTIL_H__

#include "ctypes.h"

// most files include util.h somewhere in the dependency hierarchy
// Adding Log.h include here means most files can easily log messages
// without manually adding includes
//#include "Log.h"

#ifdef _WIN32
#define ALIGN(code, alignment) __declspec(align(alignment)) code
#elif __linux__
#define ALIGN(code,alignment) code __attribute__ ((aligned(alignment)))
#endif

const f32 EPSILON = 0.000001f; // rough epsilon
const f32 PI = 3.1415926f;

void set_bit(u32 &opt, const u32 bit);
i32 bit_set(const u32 &opt, const u32 bit);
void clear_bit(u32 &opt, const u32 bit);
void toggle_bit(u32 &opt, const u32 bit);

void clamp(u32 &v, u32 lower, u32 upper);
void clamp(i32 &v, i32 lower, i32 upper);

bool NearZero(const f32 v);

f32 InvSqrt(f32 x);

// djb2 string hashing
unsigned long hash_djb2(const uc8 *str);

f32 DEGTORAD(f32 degs);
f32 RADTODEG(f32 rads);

f32 fract(f32 c);

f32 lerp(f32 min, f32 max, f32 t);

bool file_exists(const c8 *filename);

f32 randflt(f32 min, f32 max);

#endif
