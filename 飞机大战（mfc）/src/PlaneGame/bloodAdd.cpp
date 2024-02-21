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
//绘制血包图标
BOOL CBlood::Draw(CDC* pDC, BOOL bPause)
{
	if (bPause == 0) {
		//血包纵坐标改变
		mPoint.y += bloodSpeed * this->directionY;
		//边界处理
		if (mPoint.y < 0) {
			mPoint.y = 0;
			this->directionY = 1;
		}
		//边界处理
		if (mPoint.y > WINDOWS_HEIGHT) {
			mPoint.y = WINDOWS_HEIGHT;
			this->directionY = -1;
		}
		//血包横坐标改变
		mPoint.x += bloodSpeed * this->directionX;
		//边界处理
		if (mPoint.x > WINDOWS_WIDTH) {
			mPoint.x = WINDOWS_WIDTH;
			this->directionX = -1;
		}
		//边界处理
		if (mPoint.x < 0) {
			mPoint.x = 0;
			this->directionX = 1;
		}
		images.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}
//加载血包图像
BOOL CBlood::LoadImage()
{
	return  CGameObject::LoadImage(images, IDB_BMP_BLOOD_ADD, RGB(0, 0, 0), BLOOD_HEIGHT, BLOOD_HEIGHT, 6);
}
