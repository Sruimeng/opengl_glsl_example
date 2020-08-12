//轨迹球控制代码

#pragma once
namespace toy {
	
	class trackBall
	{
	public:
		trackBall();
		~trackBall();

	private:
		bool m_pan = false;
		bool m_zoomLocked = false;
		//鼠标相关参数
		int m_prevPosX;
	};

	trackBall::trackBall()
	{
	}

	trackBall::~trackBall()
	{
	}
}