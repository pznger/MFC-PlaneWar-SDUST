#pragma once
#include "Ball.h"
class UFOball :public CBall
{
public:
	UFOball(int x, int y, int nMontion);
	UFOball(int x, int y, int nMontion,double vx,double vy);
	~UFOball(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_HEIGHT, m_ptPos.y + BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT = 8;
	static CImageList m_Images;
	double    m_vx;
	double    m_vy;
};

