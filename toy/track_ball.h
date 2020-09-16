//轨迹球控制代码

#pragma once
#include "camera.h"
namespace toy {
	namespace {

	}

	class trackBall
	{
	public:
		trackBall();
		
		inline void zoom(int direction);

		inline void setCamera(Camera* camera) { m_camera = camera; }
	private:
		bool m_panLocked = false;
		bool m_zoomLocked = false;
		bool m_rotLocked = false;
		float        m_moveSpeed = 1.0f;
		float        m_rollSpeed = 0.5f;
		float        m_zoomMultiplier = 1.1f;
		Camera* m_camera; //相机

		//鼠标相关参数
		int m_prevPosX;
		int m_prevPosY;



	};
}