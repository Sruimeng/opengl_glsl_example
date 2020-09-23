//�켣����ƴ���

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
		//���ַ��� 
		inline bool wheelEvent(int wheelY);
		inline void setCamera(Camera* camera) { m_camera = camera; }
	private:
		bool m_panLocked = false;
		bool m_zoomLocked = false;
		bool m_rotLocked = false;
		float        m_moveSpeed = 1.0f;
		float        m_rollSpeed = 0.5f;
		float        m_zoomSpeed = 1.05f;
		Camera* m_camera; //���
		//������ز���
		float m_minDistance = 0.3f;
		float m_maxDistance = 1000.f;
		float m_targetDistance = 0.f;
		//�����ز���
		int m_prevPosX=0;
		int m_prevPosY=0;
		//uvn����
		float3 m_u = make_float3(0.0f);
		float3 m_v = make_float3(0.0f);
		float3 m_n = make_float3(0.0f);
	};
}