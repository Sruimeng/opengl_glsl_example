#pragma once
#include "vector.h"
namespace toy {
	class Quaternion
	{
	public:
		Quaternion() {
			quat = make_float4(1.0);
		};

		Quaternion(float x, float y, float z, float w) {
			quat.x = x;
			quat.y = y;
			quat.z = z;
			quat.w = w;
		}

		//set and get
		void setX(float x) { quat.x = x };
		void setY(float y) { quat.y = y };
		void setZ(float z) { quat.z = z };
		void setW(float w) { quat.w = w };
		void set(float4 f) { quat.x = f.x, quat.y = f.y, quat.z = f.z, quat.w = f.w };
		float getX() const { return quat.x };
		float getY() const { return quat.y };
		float getZ() const { return quat.z };
		float getW() const { return quat.w };
		float4 get() const { return quat };

	private:
		float4 quat;
	};

	Quaternion::Quaternion()
	{
	}
}