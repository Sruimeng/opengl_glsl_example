//轨迹球控制代码
#pragma once
#include "camera.h"
namespace toy {
	class trackBall
	{
	public:
		//滑轮方法 
		bool wheelEvent(int wheelY);
		inline void setCamera(Camera* camera) { m_camera = camera; }
		inline const Camera* getCamera() const { return m_camera; }
	private:
		void zoom(int direction);
		bool m_panLocked = false;
		bool m_zoomLocked = false;
		bool m_rotLocked = false;
		float        m_moveSpeed = 1.0f;
		float        m_rollSpeed = 0.5f;
		float        m_zoomSpeed = 1.05f;
		Camera* m_camera; //相机
		//缩放相关参数
		float m_minDistance = 0.3f;
		float m_maxDistance = 1000.f;
		float m_targetDistance = 0.f;
		//鼠标相关参数
		int m_prevPosX=0;
		int m_prevPosY=0;
		//俯仰角
		//uvn矩阵
		float3 m_u = make_float3(0.0f);
		float3 m_v = make_float3(0.0f);
		float3 m_n = make_float3(0.0f);
	};
}