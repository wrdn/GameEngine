#pragma once

#include "float4.h"
typedef float4 color;

const color BLACK(0,0,0,1.0f);
const color WHITE(1.0f);
const color GREY(0.5f, 0.5f, 0.5f, 1.0f);
const color RED(1.0f,0,0,1.0f);
const color GREEN(0,1.0f,0,1.0f);
const color BLUE(0,0,1.0f,1.0f);
const color YELLOW(1.0f,1.0f,0,1.0f);
const color PINK(1.0f, 0.75f, 0.79f, 1.0f);

inline color int_to_color(const u32 i)
{
	return color(
		(f32)((i>>24) & 255), //r
		(f32)((i>>16) & 255), //g
		(f32)((i>>8) & 255),  //b
		(f32)((i & 255)));    //a
};

inline u32 color_to_int(const f32 r, const f32 g, const f32 b, const f32 a)
{
	return ( (u32)r<<24 | (u32)g<<16 | (u32)b << 8 | (u32)a );
};
inline u32 color_to_int(const color &c)
{
	return color_to_int(c.r(), c.g(), c.b(), c.a());
};

// convert color with values in range 0 to 255, to color with values in range 0 to 1
inline color normalize_color(const color &c)
{
	const f32 Multiplier = 1.0f / 255.0f;
	return c * Multiplier;
};