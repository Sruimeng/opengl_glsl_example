#pragma once
#include "vector.h"
namespace toy {
	class Quaternion
	{
	public:
		Quaternion() {
			q = make_float4(1.0);
		};

		Quaternion(float x, float y, float z, float w) {
			q.x = x;
			q.y = y;
			q.z = z;
			q.w = w;
		}

	private:
		float4 quat;
	};

	Quaternion::Quaternion()
	{
	}
}