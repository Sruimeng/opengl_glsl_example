#include "track_ball.h"
#include "camera.h"

namespace toy {
	namespace {

	}

	void trackBall::zoom(int dir) {
		//float zoom = (dir>0)?1/m_zoo
	}

	bool trackBall::wheelEvent(int wheelY) {
		zoom(wheelY);
		return true;
	}
}