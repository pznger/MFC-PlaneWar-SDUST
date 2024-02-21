#pragma once
#include "GameObject.h"

class CBall :public CGameObject
{
public:
	CBall(int x,int y,int nMontion);
	CBall(int x, int y, int nMontion,int c);
	CBall(int x, int y, int nMontion, int c,int d);
	~CBall(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
	int getType()
	{
		return m_type;
	}
private:
	static const int BALL_HEIGHT=8;
	static CImageList m_Images;
	static CImageList m_Images2;
	int    m_nMotion;
	int    m_chargeDirection;
	int    m_type;//敌机子弹种类
};
