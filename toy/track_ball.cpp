#include "track_ball.h"
#include "camera.h"

namespace toy {
	namespace {

	}

	void trackBall::zoom(int dir) {
		float zoom = (dir > 0) ? (1 - m_zoomSpeed) : (1 + m_zoomSpeed);
		//保存目前distance的变量
		m_targetDistance *= zoom;
		//重新设置eye的位置
		const float3& lookat = m_camera->getLookat();
		const float3& eye = m_camera->getEye();
		m_camera->setEye(lookat + (eye - lookat) * zoom);
	}

	bool trackBall::wheelEvent(int wheelY) {
		zoom(wheelY);
		return true;
	}
}