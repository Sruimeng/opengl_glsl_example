#pragma once
#include "vector.h"

namespace toy {
	class Aabb
	{
	public:
		Aabb();

		//通过包围盒最大值和最小值
		Aabb(const float3& min, const float3& max);

		bool operator==(const Aabb& another) const;

		//包围盒的废弃也是变相初始化
		void invalidate();

		/***********************************************/
		//util
		void set(const float3& min, const float3& max);
	private:
		float3 m_min;
		float3 m_max;
	};

	inline Aabb::Aabb()
	{
		invalidate();
	}

	inline Aabb::Aabb(const float3& min, const float3& max) {
		set(min, max);
	}

	inline void Aabb::invalidate() {
		m_min = make_float3(1e37f);
		m_max = make_float3(-1e37f);
	}

	inline bool Aabb::operator==(const Aabb& another) const{
		return m_min.x == another.m_min.x &&
			m_min.y == another.m_min.y &&
			m_min.z == another.m_min.z &&
			m_max.x == another.m_max.x &&
			m_max.y == another.m_max.y &&
			m_max.z == another.m_max.z;
	}

	inline void Aabb::set(const float3& min, const float3& max) {
		m_min = min;
		m_max = max;
	}
}


