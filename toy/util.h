#pragma once

namespace toy {
	//角度转弧度
	float radians(float degrees)
	{
		return degrees * M_PIf / 180.0f;
	}
	//弧度转角度
	float degrees(float radians)
	{
		return radians * M_1_PIf * 180.0f;
	}
}