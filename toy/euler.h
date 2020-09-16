#pragma once

#include <iostream>
#include "vector.h"
namespace toy {
	class euler
	{
	public:
		euler();
		inline euler(float3 euler) { this->euler = euler };
	private:
		float3 euler;
		std::string order;
	};

	euler::euler()
	{
	}
}
