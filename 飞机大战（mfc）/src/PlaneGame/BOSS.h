#pragma once
#include "Enemy.h"

//Boss�ĸ߶�
#define BOSS_HEIGHT 250
//Boss�Ŀ��
#define BOSS_WIDTH 360
//Boss�����ٶ�
#define BOSS_SPEED 3
//Ĭ��Boss����
#define BOSS_LIFE 100

//Boss��
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
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
private:
	static CImageList m_Images;
	int m_xV;//ˮƽ�����ٶ�
	int m_freshFreaq;//ˢ��֡Ƶ��
public:
	int enhancedEnemyBlood = 100;//Ѫ������������100��Ѫ����
	int m_chargeDirection;//����淽��
};

