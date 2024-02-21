#pragma once
#include "GameObject.h"
#include "Resource.h"

//Ѫ�����ٶ�
#define BLOOD_SPEED 3
//Ѫ��ͼ����
#define BLOOD_HEIGHT 60


//Ѫ����
class CBlood :public CGameObject
{
public:
	CBlood(int WINDOWS_WIDTH, int WINDOWS_HEIGHT);
	CBlood(int WINDOWS_WIDTH, int WINDOWS_HEIGHT, int createX, int createY);
	~CBlood();
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	//���Ѫ�����ڵľ��ο�
	CRect GetRect()
	{
		return CRect(mPoint, CPoint(mPoint.x + BLOOD_HEIGHT, mPoint.y + BLOOD_HEIGHT));
	}
	void SetBallSpeed(int bloodSpeed)
	{
		this->bloodSpeed = bloodSpeed;
	}

private:
	static CImageList images;
	int bloodSpeed;//Ѫ�����ٶ�
	int directionX;//Ѫ�����з���1Ϊ���ң�-1Ϊ����
	int directionY;//Ѫ�����з���1Ϊ���£�-1Ϊ����
	int WINDOWS_WIDTH;//���ڿ��
	int WINDOWS_HEIGHT;//���ڸ߶�
};


