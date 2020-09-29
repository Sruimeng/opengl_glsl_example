#pragma once

#include <iostream>
#include "vector.h"
namespace toy {
	class Euler
	{
	public:
		Euler();
		inline Euler(float3 Euler) { this->Euler = Euler };
	private:
		float3 Euler;
		std::string order;
	};

	Euler::Euler()
	{
	}
}
