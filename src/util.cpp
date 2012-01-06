#include "util.h"
#include <math.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <pmmintrin.h>

void set_bit(u32 &opt, const u32 bit)
{
	opt |= bit;
};

i32 bit_set(const u32 &opt, const u32 bit)
{
	return (opt & bit);
};

void clear_bit(u32 &opt, const u32 bit)
{
	opt &= (~bit);
};

void toggle_bit(u32 &opt, const u32 bit)
{
	opt ^= bit;
};

void clamp(u32 &v, u32 lower, u32 upper)
{
	if(v < lower) { v = lower; }
	else if(v > upper) { v = upper; }
};

void clamp(i32 &v, i32 lower, i32 upper)
{
	if(v < lower) { v = lower; }
	else if(v > upper) { v = upper; }
};

bool NearZero(const f32 v)
{
		return fabs(v) < EPSILON;
};

bool NearOne(const f32 v)
{
	return v > 0.999f && v <= 1.001f;
};

// Fast inverse square root, from http://pizer.wordpress.com/2008/10/12/fast-inverse-square-root/
// Recoded to remove aliasing issues (and warnings under Linux), based on: //http://blog.reloadsystems.net/2009/11/08/avoid-dereferencing-in-carmacks-implementation-of-approximate-roots/
union flpack { long l; f32 f; };
f32 InvSqrt(f32 value)
{
   flpack fd;
   fd.f = value;
   long i = fd.l;
   fd.l = 0x5F1F1412 - (i >> 1);
   f32 y = fd.f;
   return y*(1.69000231f - 0.714158168f * value * y*y);
/*
#ifdef _WIN32
   u32 i = 0x5F1F1412 - (*(u32*)&x >> 1);
   f32 tmp = *(f32*)&i;
   return tmp * (1.69000231f - 0.714158168f * x * tmp * tmp);
#else // fix the warnings (remember Werror) on Linux, then we can use the code above again
   return (1.0f / sqrt(x));
#endif
*/
};

// Source: http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash_djb2(const uc8 *str)
{
	unsigned long hash = 5381;
	u32 c='a'; // give c a valid value so we can get into the loop

	while(c) // rewrote this slightly to get rid of Parasoft and Visual Studio Release mode warning (assignment in conditional expression)
	{
		c = *str;
		if(c==0) { break; }
		hash = ((hash << 5) + hash) + c;
		++str;
	}

	return hash;
}

f32 DEGTORAD(f32 degs)
{
	return (degs * (PI / 180.0f));
};

f32 RADTODEG(f32 rads)
{
	return (rads * (180.0f / PI));
};

f32 fract(f32 c)
{
	return (c - floor(c));
};

f32 lerp(f32 min, f32 max, f32 t)
{
	return (min + (t * (max-min)));
};

bool file_exists(const c8 *filename)
{
	struct stat f; // careful not to mix up the structure and function
	return (stat(filename,&f) == 0); // 0 if file exists
}

f32 randflt(f32 min, f32 max)
{
    f32 random = ((f32) rand()) / (f32) RAND_MAX;

    // generate (in your case) a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    f32 range = max - min;  
    return (random*range) + min;
};

f32 reciprocal_sqrt(f32 f)
{
	/*
	// SSE Version (Fast):
	f32 result; // reciprocal square root using SSE (accurate to ~11/12 mantissa bits)
	_mm_store_ss(&result, _mm_rsqrt_ss( _mm_load_ss(&f) ));
	return result;

	// More accurate scalar version:
	return 1.0f / sqrt(f);
	*/
	f32 result; // reciprocal square root using SSE (accurate to ~11/12 mantissa bits)
	_mm_store_ss(&result, _mm_rsqrt_ss( _mm_load_ss(&f) ));
	return result;
};