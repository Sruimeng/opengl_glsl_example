//�켣����ƴ���

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
		//�����ز���
		int m_prevPosX;
	};

	trackBall::trackBall()
	{
	}

	trackBall::~trackBall()
	{
	}
}