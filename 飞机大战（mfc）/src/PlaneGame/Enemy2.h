#pragma once
#include "gameobject.h"
#include "Enemy.h"


#define ENEMY_HEIGHT 90//�л��ĸ߶�

#define ENEMY_WIDTH 120//�л��Ŀ��

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
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	int m_xV;//ˮƽ�����ٶ�
	int m_freshFreaq;//ˢ��֡Ƶ��
public:	
	int enhancedEnemyBlood = 80;//Ѫ������������100��Ѫ����
	int m_chargeDirection;//����淽��
	static CImageList m_Images;
};
