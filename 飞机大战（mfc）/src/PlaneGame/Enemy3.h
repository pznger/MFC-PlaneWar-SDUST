#pragma once
#include "gameobject.h"
#include "Enemy.h"
#include "EnemyTroop.h"

#define ENEMY_HEIGHT 90//敌机的高度

#define ENEMY_WIDTH 120//敌机的宽度

class CEnemy3 :public CEnemy
{
public:
	CEnemy3(void);
	~CEnemy3(void);

	int enhancedEnemyBlood = 10;
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
	static CImageList m_Images;
private:
	int m_xV;//水平方向速度
	int m_freshFreaq;//刷新帧频率
};
