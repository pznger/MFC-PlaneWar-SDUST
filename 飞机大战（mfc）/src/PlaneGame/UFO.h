#pragma once
#include "gameobject.h"
#include "Enemy.h"


#define ENEMY_HEIGHT 90//�л��ĸ߶�

#define ENEMY_WIDTH 120//�л��Ŀ��

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
	//�Ƿ���Կ������ӵ�
	BOOL Fired();

	//CEnemyTroop* enemys;

	int enhancedEnemyBlood = 20;
private:
	static CImageList m_Images;
	//ͼ������
	int m_nImgIndex;
	//�ٶȶ���Ϊdouble���㻭Բ
	double m_xV;//ˮƽ�����ٶ�
	int m_freshFreaq;//ˢ��֡Ƶ��
};
