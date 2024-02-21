#pragma once
#include "gameobject.h"
#include "Enemy.h"


#define ENEMY_HEIGHT 90//敌机的高度

#define ENEMY_WIDTH 120//敌机的宽度

class CEnemy2 :public CEnemy
{
public:
	CEnemy2(void);
	CEnemy2(int c);
	~CEnemy2(void);


	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
private:
	int m_xV;//水平方向速度
	int m_freshFreaq;//刷新帧频率
public:	
	int enhancedEnemyBlood = 80;//血量（相对于玩家100点血量）
	int m_chargeDirection;//最后冲锋方向
	static CImageList m_Images;
};
