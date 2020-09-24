#include "track_ball.h"

namespace toy {

	void trackBall::zoom(int dir) {
		float zoom = (dir > 0) ? (1 - m_zoomSpeed) : (1 + m_zoomSpeed);
		//����Ŀǰdistance�ı���
		m_targetDistance *= zoom;
		if (m_targetDistance <= m_minDistance) {
			m_targetDistance = m_minDistance;
		}
		else if (m_targetDistance >= m_maxDistance) {
			m_targetDistance = m_maxDistance;
		}
		//��������eye��λ��
		const float3& lookat = m_camera->getLookat();
		const float3& eye = m_camera->getEye();
		m_camera->setEye(lookat + (eye - lookat) * zoom);
	}

	bool trackBall::wheelEvent(int wheelY) {
		zoom(wheelY);
		return true;
	}
}