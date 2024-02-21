#pragma once
#include "GameObject.h"
#include "Ball.h"
#include <atlimage.h>


#define MISSLE_WIDTH 15
#define MISSLE_HEIGHT 40
class CMissle :public CGameObject
{
public:
	CMissle(int x, int y, int nMontion);
	CMissle(int x, int y, int nMontion, int c);
	~CMissle(void);

	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int shearAngle, BOOL bPause);

	static BOOL LoadImage();

	void SetImageRotationAngle(double angle,CImage m_StaticImage);//调整图片旋转角度

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_HEIGHT, m_ptPos.y + BALL_HEIGHT));
	}
	int getChargeDirection()
	{
		return m_chargeDirection;
	}
	void setChargeDirection(int d) 
	{
		m_chargeDirection = d;
	}
	void setDirectY(int x)
	{
		directY = x;
	}
private:
	static const int BALL_HEIGHT = 8;
	static CImageList m_Images;
	static CImageList m_Images2;
	int    m_nMotion;
	int    m_chargeDirection;
	int    m_freshFreaq;//导弹刷新频率（控制追踪时间和强度）
	double angle;//旋转角度
	int directY;
};
