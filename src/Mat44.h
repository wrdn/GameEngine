#pragma once

#include "ctypes.h"
#include "util.h"
#include <iostream>
#include "float4.h"
#include "float3.h"

enum Mat44Index
{
	m11 = 0,
	m12 = 1,
	m13 = 2,
	m14 = 3,

	m21 = 4,
	m22 = 5,
	m23 = 6,
	m24 = 7,

	m31 = 8,
	m32 = 9,
	m33 = 10,
	m34 = 11,

	m41 = 12,
	m42 = 13,
	m43 = 14,
	m44 = 15,
};

// using unaligned loads so we can use unaligned float4s
#define Mat44_Vector_Load_Fn _mm_loadu_ps
#define Mat44_Vector_Store_Fn _mm_storeu_ps

// Note: Calculations are performed in SSE registers. Data is assumed to be aligned to a 16 byte boundary.
// NOTE: Mat44 will be 16 byte aligned on the stack, but by default, float4 is not. Mat44 assumes float4 is aligned
// and it is the task of the programmer to ensure this. As an alternative, replace the code with an unaligned (slower) load
// to avoid the problem entirely (at the cost of a slight performance hit)
// See #define MAT44_UNALIGNED_VECTOR_LOADS
class Mat44
{
private:
	static const c8 MATRIX_ELEMENT_COUNT = 16;
	//__declspec(align(16)) f32 mat[Mat44::MATRIX_ELEMENT_COUNT];
	ALIGN(f32 mat[MATRIX_ELEMENT_COUNT], 16);

	void Cramers_Inverse(const Mat44 *out, f32 &det) const;
	void Cramers_Inverse_SSE(const Mat44 *out, f32 &det) const;

	/*
	[ 0  1  2  3]
	[ 4  5  6  7]
	[ 8  9 10 11]
	[12 13 14 15]

	[m11 m12 m13 m14]
	[m21 m22 m23 m24]
	[m31 m32 m33 m34]
	[m41 m42 m43 m44]
	*/
public:
	Mat44(void);
	explicit Mat44(const f32* _mat); // use existing FP array to initialise the matrix
	explicit Mat44(
		const f32 m11, const f32 m12, const f32 m13, const f32 m14,
		const f32 m21, const f32 m22, const f32 m23, const f32 m24,
		const f32 m31, const f32 m32, const f32 m33, const f32 m34,
		const f32 m41, const f32 m42, const f32 m43, const f32 m44);
	~Mat44(void);

	static const Mat44 IDENTITY;

	const f32* GetMatrix() const;

	void SetMatrix(const f32* _mat) const;

	void SetMatrix(const f32 m11, const f32 m12, const f32 m13, const f32 m14,
	const f32 m21, const f32 m22, const f32 m23, const f32 m24,
	const f32 m31, const f32 m32, const f32 m33, const f32 m34,
	const f32 m41, const f32 m42, const f32 m43, const f32 m44);

	void Identity() const; // sets this matrix back to the identity matrix (Mat44::IDENTITY)

	Mat44 Add(const Mat44 &m) const; // standard matrix addition
	Mat44 Add(const f32 v) const; // adds v to each matrix element
	Mat44 Sub(const Mat44 &m) const; // standard matrix subtraction
	Mat44 Sub(const f32 v) const; // subtracts v from each matrix element

	Mat44 Mult(const f32 scale) const; // matrix scaling
	Mat44 Mult_ComponentWise(const Mat44 &m) const; // component-wise multiplication
	Mat44 Mult(const Mat44 &m) const; // standard matrix multiplication
	float4 Mult(const float4 &m) const; // matrix-vector multiplication

	// Used to multiply a batch of vectors by the same matrix
	void BatchMult(const float4 * const in, float4 *out, u32 len) const;

	// Does inverse according to Cramers Rule
	// See ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
	Mat44 Inverse() const;
	f32 Determinant() const;

	Mat44 Transpose() const;

	void write(std::ostream &out);

	static Mat44 BuildTranslationMatrix(const f32 x, const f32 y, const f32 z);
	static Mat44 BuildRotationMatrix(const f32 angle_in_degrees, const f32 x, const f32 y, const f32 z);
	static Mat44 BuildRotationMatrix(const f32 angle_in_degrees, const float3 &axis);
	static Mat44 BuildScaleMatrix(const f32 xscale, const f32 yscale, const f32 zscale);

	// modifies only the elements for the scale matrix (assumes rest is identity)
	static void BuildScaleMatrix(const f32 xscale, const f32 yscale, const f32 zscale, Mat44 &out);

	const float3 GetTranslationFromMatrix() const;

	inline const Mat44& operator+=(const Mat44 &rhs) { *this = Add(rhs); return *this; }
	inline const Mat44& operator-=(const Mat44 &rhs) { *this = Sub(rhs); return *this; }
	inline const Mat44& operator*=(const Mat44 &rhs) { *this = Mult(rhs); return *this; } // matrix-matrix mult
	inline const Mat44& operator*=(const f32 &rhs) { *this = Mult(rhs); return *this; } // scale
};

inline Mat44 operator+(const Mat44 &a, const Mat44 &b) { return Mat44(a)+=b; }
inline Mat44 operator-(const Mat44 &a, const Mat44 &b) { return Mat44(a)-=b; }
inline Mat44 operator*(const Mat44 &a, const Mat44 &b) { return Mat44(a)*=b; }
inline Mat44 operator*(const Mat44 &a, const f32 &b) { return Mat44(a)*=b; }
inline float4 operator*(const Mat44 &a, const float4 &b) { return a.Mult(b); }

inline Mat44 operator*(const f32 &a, const Mat44 &b) { return Mat44(b)*=a; }
inline float4 operator*(const float4 &a, const Mat44 &b) { return b.Mult(a); }

std::ostream& operator<<(std::ostream &out, Mat44 &m);
