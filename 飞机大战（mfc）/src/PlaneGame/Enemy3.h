#pragma once
#include "gameobject.h"
#include "Enemy.h"
#include "EnemyTroop.h"

#define ENEMY_HEIGHT 90//�л��ĸ߶�

#define ENEMY_WIDTH 120//�л��Ŀ��

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
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
	static CImageList m_Images;
private:
	int m_xV;//ˮƽ�����ٶ�
	int m_freshFreaq;//ˢ��֡Ƶ��
};
