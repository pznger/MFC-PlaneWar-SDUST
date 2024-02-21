#pragma once
#include "gameobject.h"
#include "Enemy.h"


#define ENEMY_HEIGHT 90//敌机的高度

#define ENEMY_WIDTH 120//敌机的宽度

class CUFO :public CEnemy
{
public:
	CUFO(void);
	~CUFO(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();

	//CEnemyTroop* enemys;

	int enhancedEnemyBlood = 20;
private:
	static CImageList m_Images;
	//图像索引
	int m_nImgIndex;
	//速度定义为double方便画圆
	double m_xV;//水平方向速度
	int m_freshFreaq;//刷新帧频率
};
