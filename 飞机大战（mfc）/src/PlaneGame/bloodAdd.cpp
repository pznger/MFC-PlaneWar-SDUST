#include "stdafx.h"
#include "bloodAdd.h"
CImageList CBlood::images;
CBlood::CBlood(int WINDOWS_WIDTH, int WINDOWS_HEIGHT)
{
	this->WINDOWS_WIDTH = WINDOWS_WIDTH;
	this->WINDOWS_HEIGHT = WINDOWS_HEIGHT;
	mPoint.x = rand() % WINDOWS_WIDTH;
	mPoint.y = 0;
	directionY = 1;
	if (rand() % 2)
		directionX = 1;
	else directionX = -1;
	this->bloodSpeed = BLOOD_SPEED;
}
CBlood::CBlood(int WINDOWS_WIDTH, int WINDOWS_HEIGHT,int createX,int createY)
{
	this->WINDOWS_WIDTH = WINDOWS_WIDTH;
	this->WINDOWS_HEIGHT = WINDOWS_HEIGHT;
	mPoint.x = createX;
	mPoint.y = createY;
	directionY = 1;
	if (rand() % 2)
		directionX = 1;
	else directionX = -1;
	this->bloodSpeed = BLOOD_SPEED;
}
CBlood::~CBlood()
{
}
//����Ѫ��ͼ��
BOOL CBlood::Draw(CDC* pDC, BOOL bPause)
{
	if (bPause == 0) {
		//Ѫ��������ı�
		mPoint.y += bloodSpeed * this->directionY;
		//�߽紦��
		if (mPoint.y < 0) {
			mPoint.y = 0;
			this->directionY = 1;
		}
		//�߽紦��
		if (mPoint.y > WINDOWS_HEIGHT) {
			mPoint.y = WINDOWS_HEIGHT;
			this->directionY = -1;
		}
		//Ѫ��������ı�
		mPoint.x += bloodSpeed * this->directionX;
		//�߽紦��
		if (mPoint.x > WINDOWS_WIDTH) {
			mPoint.x = WINDOWS_WIDTH;
			this->directionX = -1;
		}
		//�߽紦��
		if (mPoint.x < 0) {
			mPoint.x = 0;
			this->directionX = 1;
		}
		images.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}
//����Ѫ��ͼ��
BOOL CBlood::LoadImage()
{
	return  CGameObject::LoadImage(images, IDB_BMP_BLOOD_ADD, RGB(0, 0, 0), BLOOD_HEIGHT, BLOOD_HEIGHT, 6);
}
