#pragma once
#include "Enemy.h"

//Boss的高度
#define BOSS_HEIGHT 250
//Boss的宽度
#define BOSS_WIDTH 360
//Boss飞行速度
#define BOSS_SPEED 3
//默认Boss生命
#define BOSS_LIFE 100

//Boss类
class CBOSS :
	public CEnemy
{
public:
	CBOSS();
	CBOSS(int c);
	~CBOSS();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	int GetMontion() const
	{
		return m_nMotion;
	}
	void setChargeDirection(int c)
	{
		m_chargeDirection = c;
	}
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static CImageList m_Images;
	int m_xV;//水平方向速度
	int m_freshFreaq;//刷新帧频率
public:
	int enhancedEnemyBlood = 100;//血量（相对于玩家100点血量）
	int m_chargeDirection;//最后冲锋方向
};

