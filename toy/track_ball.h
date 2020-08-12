//�켣����ƴ���

#pragma once
#include "camera.h"
namespace toy {
	
	class trackBall
	{
	public:
		trackBall();
		~trackBall();

	private:
		bool m_panLocked = false;
		bool m_zoomLocked = false;
		bool m_rotLocked = false;
		float        m_moveSpeed = 1.0f;
		float        m_rollSpeed = 0.5f;
		Camera* m_camera; //���

		//�����ز���
		int m_prevPosX;
		int m_prevPosY;

	};
}