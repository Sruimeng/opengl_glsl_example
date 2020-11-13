#pragma once
#include <math.h>
namespace toy {
#ifndef M_PIf
#define M_PIf       3.14159265358979323846f
#endif

	struct int3
	{
		int x, y, z;
	};

	struct float4
	{
		float x, y, z ,w;
	};

	struct float3
	{
		float x, y, z;
	};

	struct float2
	{
		float x, y;
	};
	inline int3 make_int3(int x, int y, int z) { int3 r; r.x = x; r.y = y; r.z = z; return r; }
	inline int3 make_int3(int x) { int3 r; r.x = x; r.x = x; r.y = x; r.z = x; return r; }
	inline float3 make_float3(float x, float y, float z) { float3 r; r.x = x; r.y = y; r.z = z; return r; }

	inline float3 make_float3(float x) { float3 r; r.x = x; r.x = x; r.y = x; r.z = x; return r; }

	inline float4 make_float4(float x) {
		float4 r;		r.x = x;		r.y = x;		r.z = x;		r.w = x; return r;
	}

	inline float4 make_float4(float x,float y,float z,float w) {
		float4 r;		r.x = x;		r.y = y;		r.z = z;		r.w = w; return r;
	}
	//加法
	inline float3 operator+(const float3& a, const float3& b) {
		return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	//减法
	inline float3 operator-(const float3& a, const float3& b) {
		return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	//乘法
	inline float3 operator*(const float3& a, const float3& b) {
		return make_float3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	inline float3 operator*(const float3& a, const float b) {
		return make_float3(a.x * b, a.y * b, a.z * b);
	}
	inline float operator*=(const float3& a, const float b) {
		return a.x * b, a.y* b, a.z* b;
	}

	//点积
	inline float dot(const float3& a, const float3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	//叉积
	inline float3 cross(const float3& a, const float3& b) {
		return make_float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	//向量长度
	inline float length(const float3& a, const float3& b) {
		return sqrtf(dot(a, b));
	}
	inline float length(const float3& a) {
		return sqrtf(dot(a, a));
	}
	//单位向量
	inline float3 normalize(const float3& a) {
		float length_scale = 1.f / sqrtf(dot(a, a));
		return a * length_scale;
	}

	
}