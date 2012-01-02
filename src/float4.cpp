#include "float4.h"
#include "float3.h"

#include "util.h"
#include <math.h>

const float4 float4::ZERO = float4((f32)0.0f);
const float4 float4::ONE  = float4((f32)1.0f);

float3 float4::ToFloat3() const
{
	return float3(vec);
};

float4::float4()
{
	zero();
};

float4::float4(const f32 v)
{
	setall(v);
};

float4::float4(const f32 _x, f32 _y, f32 _z, f32 _w)
{
	vec[0] = _x;
	vec[1] = _y;
	vec[2] = _z;
	vec[3] = _w;
};

float4::float4(const f32 _x, f32 _y, f32 _z)
{
	vec[0] = _x;
	vec[1] = _y;
	vec[2] = _z;
	vec[3] = 0;
};

float4::float4(const f32 * v)
{
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
	vec[3] = v[3];
};

float4 float4::FromXYZ(const f32 * v)
{
	return float4(v[0], v[1], v[2]);
};

void float4::setall(const f32 v)
{
	vec[0] = vec[1] = vec[2] = vec[3] = v;
};

void float4::zero() { setall(0); };

float4 float4::add(const float4 &v) const
{
	return float4(
		vec[0] + v.vec[0],
		vec[1] + v.vec[1],
		vec[2] + v.vec[2],
		vec[3] + v.vec[3]);
};

float4 float4::sub(const float4 &v) const
{
	return float4(
		vec[0] - v.vec[0],
		vec[1] - v.vec[1],
		vec[2] - v.vec[2],
		vec[3] - v.vec[3]);
};

float4 float4::mul(const float4 &v) const
{
	return float4(
		vec[0] * v.vec[0],
		vec[1] * v.vec[1],
		vec[2] * v.vec[2],
		vec[3] * v.vec[3]);
};

float4 float4::mul(const f32 t) const
{
	return float4(
		vec[0] * t,
		vec[1] * t,
		vec[2] * t,
		vec[3] * t);
};

float4 float4::div(const float4 &v) const
{
	return float4(
		vec[0] / v.vec[0],
		vec[1] / v.vec[1],
		vec[2] / v.vec[2],
		vec[3] / v.vec[3]);
};

float4 float4::div(const f32 t) const
{
	return float4(
		vec[0] / t,
		vec[1] / t,
		vec[2] / t,
		vec[3] / t);
};

float4 float4::add(const f32 t) const
{
	return float4(
		vec[0] + t,
		vec[1] + t,
		vec[2] + t,
		vec[3] + t);
};

float4 float4::sub(const f32 t) const
{
	return float4(
		vec[0] - t,
		vec[1] - t,
		vec[2] - t,
		vec[3] - t);
};

f32 float4::dot(const float4 &v) const
{
	return (vec[0] * v.vec[0]) + (vec[1] * v.vec[1]) + (vec[2] * v.vec[2]) + (vec[3] * v.vec[3]);
};

float4 float4::cross(const float4 &v) const
{
	return float4(
		(vec[1] * v.vec[2]) - (vec[2] * v.vec[1]),
		(vec[2] * v.vec[0]) - (vec[0] * v.vec[2]),
		(vec[0] * v.vec[1]) - (vec[1] * v.vec[0]),
		0);
};

void float4::cross(const float4 &v, f32 * const output3d) const
{
	output3d[0] = (vec[1] * v.vec[2]) - (vec[2] * v.vec[1]);
	output3d[1] = (vec[2] * v.vec[0]) - (vec[0] * v.vec[2]);
	output3d[2] = (vec[0] * v.vec[1]) - (vec[1] * v.vec[0]);
};

f32 float4::magnitude() const
{
	return sqrtf( LengthSquared() );
};
f32 float4::LengthSquared() const
{
	return (vec[0]*vec[0]) + (vec[1]*vec[1]) + (vec[2]*vec[2]) + (vec[3]*vec[3]);
};

f32 float4::distance(const float4 &v) const
{
	return this->sub(v).magnitude();
};

f32 float4::DistanceSquared(const float4 &v) const
{
	return this->sub(v).LengthSquared();
};

float4 float4::normalize() const
{
	f32 lsqr = LengthSquared();
	if(NearZero(lsqr)) { return ZERO; };
	f32 recip = InvSqrt(lsqr);
	
	return float4(vec[0]*recip, vec[1]*recip, vec[2]*recip, vec[3]*recip);
};

void float4::normalize()
{
	f32 lsqr = LengthSquared();
	if(NearZero(lsqr)) { *this = ZERO; };
	f32 recip = InvSqrt(lsqr);
	vec[0] *= recip;
	vec[1] *= recip;
	vec[2] *= recip;
	vec[3] *= recip;
};

float4 float4::negate() const
{
	return float4(
		-vec[0],
		-vec[1],
		-vec[2],
		-vec[3]);
};

float4 float4::absolute() const
{
	return float4(fabs(vec[0]), fabs(vec[1]), fabs(vec[2]), fabs(vec[3]));
};

std::ostream& operator<<(std::ostream &out, const float4 &m)
{
	f32 * vec = m.GetVec();
	std::cout << "{" << vec[0] << "," << vec[1] << "," << vec[2] << "," << vec[3] << "}";
	return out;
};

/*
static const float4 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));

float4 finit(const f32 v)
{
	return _mm_load1_ps(&v);
};

float4 finit(const f32 x, const f32 y, const f32 z, const f32 w)
{
	//return _mm_setr_ps(x,y,z,w);
	return _mm_set_ps(w,z,y,x);
};

void fpull(const float4 &f, f32 *out)
{
	_mm_store_ps(out, f);
};
void fpullu(const float4 &f, f32 *out)
{
	_mm_storeu_ps(out, f);
};
void fpull3(const float4 &f, f32 *out)
{
	ALIGN(16) f32 data[4];
	_mm_store_ps(data, f);

	out[0] = data[0];
	out[1] = data[1];
	out[2] = data[2];
};

float4 finit(const f32 x, const f32 y, const f32 z)
{
	return finit(x,y,z,0);
};

float4 finit(const f32 *v)
{
	return _mm_load_ps(v);
};

float4 finitu(const f32 *v)
{
	return _mm_loadu_ps(v);
};

float4 fzero()
{
	return _mm_setzero_ps();
};

void fzero(float4 &t)
{
	t = _mm_setzero_ps();
};

float4 fadd(const float4 &a, const float4 &b)
{
	return _mm_add_ps(a,b);
};

void fadd(const float4 &a, const float4 &b, float4 &out)
{
	out = _mm_add_ps(a,b);
};

float4 fsub(const float4 &a, const float4 &b)
{
	return _mm_sub_ps(a,b);
};

void fsub(const float4 &a, const float4 &b, float4 &out)
{
	out = _mm_sub_ps(a,b);
};

float4 fmul(const float4 &a, const float4 &b)
{
	return _mm_mul_ps(a,b);
};

void fmul(const float4 &a, const float4 &b, float4 &out)
{
	out = _mm_mul_ps(a,b);
};

float4 fdiv(const float4 &a, const float4 &b)
{
	return _mm_div_ps(a,b);
};

void fdiv(const float4 &a, const float4 &b, float4 &out)
{
	out = _mm_div_ps(a,b);
};

f32 fdot(const float4 &a, const float4 &b)
{
	// http://software.intel.com/en-us/articles/implement-a-horizontal-addsubtract-with-sse3-instructions/
	float4 mres = _mm_mul_ps(a,b);
	float4 h = _mm_hadd_ps(mres,mres);
	float4 fin = _mm_hadd_ps(h,h);
	f32 ret; _mm_store_ss(&ret,fin);
	return ret;
};

float4 fcross(const float4 &a, const float4 &b)
{
	float4 ares = _mm_mul_ps(_mm_shuffle_ps(a,a,0xD8), _mm_shuffle_ps(b,b,0xE1));
	float4 bres = _mm_mul_ps(_mm_shuffle_ps(a,a,0xE1), _mm_shuffle_ps(b,b,0xD8));
	float4 t = ares-bres;
	t = _mm_shuffle_ps(t,t,_MM_SHUFFLE(3,0,1,2)); // shuffles data back into x,y,z,w order
	return t;
};

float4 fnormalize(const float4 &a)
{
	__m128 l = _mm_mul_ps(a, a);
	l = _mm_add_ps(l, _mm_shuffle_ps(l, l, 0x4E));
	return _mm_div_ps(a, _mm_sqrt_ps(_mm_add_ps(l, _mm_shuffle_ps(l, l, 0x11))));
};

void fcross(const float4 &a, const float4 &b, float4 &out)
{
	float4 ares = _mm_mul_ps(_mm_shuffle_ps(a,a,0xD8), _mm_shuffle_ps(b,b,0xE1));
	float4 bres = _mm_mul_ps(_mm_shuffle_ps(a,a,0xE1), _mm_shuffle_ps(b,b,0xD8));
	out = ares - bres;
	out = _mm_shuffle_ps(out,out,_MM_SHUFFLE(3,0,1,2));
};

void fnormalize(const float4 &a, float4 &out)
{
	__m128 l = _mm_mul_ps(a, a);
	l = _mm_add_ps(l, _mm_shuffle_ps(l, l, 0x4E));
	out = _mm_div_ps(a, _mm_sqrt_ps(_mm_add_ps(l, _mm_shuffle_ps(l, l, 0x11))));
};

void fnormalize(float4 *a)
{
	__m128 l = _mm_mul_ps(*a, *a);
	l = _mm_add_ps(l, _mm_shuffle_ps(l, l, 0x4E));
	*a = _mm_div_ps(*a, _mm_sqrt_ps(_mm_add_ps(l, _mm_shuffle_ps(l, l, 0x11))));
};

float4 negate(const float4 &v)
{
	return _mm_xor_ps(v, SIGNMASK);
};

float4 fabsolute(const float4 &v)
{
	return _mm_andnot_ps(SIGNMASK, v);
};

float4 operator-(const float4 &v) { return negate(v); };

float4 operator+(const float4 &a, const float4 &b) { return fadd(a,b); };
float4 operator-(const float4 &a, const float4 &b) { return fsub(a,b); };
float4 operator*(const float4 &a, const float4 &b) { return fmul(a,b); };
float4 operator/(const float4 &a, const float4 &b) { return fdiv(a,b); };

float4 operator+(const float4 &a, const f32 &b) { return fadd(a,finit(b)); };
float4 operator-(const float4 &a, const f32 &b) { return fsub(a,finit(b)); };
float4 operator*(const float4 &a, const f32 &b) { return fmul(a,finit(b)); };
float4 operator/(const float4 &a, const f32 &b) { return fdiv(a,finit(b)); };

void operator+=(float4 &a, const float4 &b) { a = fadd(a,b); };
void operator-=(float4 &a, const float4 &b) { a = fsub(a,b); };
void operator*=(float4 &a, const float4 &b) { a = fmul(a,b); };
void operator/=(float4 &a, const float4 &b) { a = fdiv(a,b); };

void operator+=(float4 &a, const f32 &b) { a = fadd(a, finit(b)); };
void operator-=(float4 &a, const f32 &b) { a = fsub(a, finit(b)); };
void operator*=(float4 &a, const f32 &b) { a = fmul(a, finit(b)); };
void operator/=(float4 &a, const f32 &b) { a = fdiv(a, finit(b)); };

float4 operator^(const float4 &a, const float4 &b) { return fcross(a,b); };
float4 operator^(const float4 &a, const f32 &b) { return fcross(a,finit(b)); };
void operator^=(float4 &a, const float4 &b) { a = fcross(a,b); };
void operator^=(float4 &a, const f32 &b) { a = fcross(a,finit(b)); };

void fcross3(f32 *a, f32 *b, f32 *out)
{
	out[0] = a[1]*b[2] - a[2]*b[1];
	out[1] = a[2]*b[0] - a[0]*b[2];
	out[2] = a[0]*b[1] - a[1]*b[0];
};

void fmin3(f32 *a, f32 *b, f32 *out)
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
};
*/