#pragma once
#include "gameobject.h"
#include "Enemy.h"


#define ENEMY_HEIGHT 90//�л��ĸ߶�

#define ENEMY_WIDTH 120//�л��Ŀ��

class CEnemy4 :public CEnemy
{
public:
	CEnemy4(void);
	~CEnemy4(void);

	int enhancedEnemyBlood = 40;
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
	int imgCnt;//�л�����
	int m_freshFreaq;//ˢ��֡Ƶ��
};
