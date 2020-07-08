#pragma once
#include <math.h>
namespace toy {
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
	//点积
	inline float dot(const float3& a, const float3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	//叉积
	inline float3 cross(const float3& a, const float3& b) {
		return make_float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x)
	}
	//向量长度
	inline float length(const float3& a, const float3& b) {
		return sqrtf(dot(a, b));
	}
	//单位向量
	inline float3 normalize(const float3& a) {
		float length_scale = 1.f / sqrtf(dot(a, a));
		return 
	}
	inline float3 make_float3(float x, float y, float z) { float3 r; r.x = x; r.y = y; r.z = z; return r; }

	inline float3 make_float3(float x) { float3 r; r.x = x; r.x = x; r.y = x; r.z = x; return r; }

	//减法
	inline float3 operator-(const float3& a, const float3& b) {
		return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	//乘法
}