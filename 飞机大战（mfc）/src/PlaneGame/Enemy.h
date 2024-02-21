#pragma once
#include "gameobject.h"

class CEnemy :public CGameObject
{
public:
	CEnemy(void);
	CEnemy(int x,int y);
	~CEnemy(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
	}

	CRect GetRect(int x,int y)
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + x, m_ptPos.y + y));
	}

	CRect GetRect(int x)
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 120, m_ptPos.y + 90));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
public:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int    m_nWait;//发射延时
	int imgCnt;//敌机种类
};
