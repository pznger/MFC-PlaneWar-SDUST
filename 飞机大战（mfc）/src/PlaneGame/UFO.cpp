#include "StdAfx.h"
#include "Enemy3.h"
#include "resource.h"
#include "Enemy.h"
#include "UFO.h"
#include <math.h>
CImageList CUFO::m_Images;
#define PI 3.1415926535
#define UFO_FIRE_NUM 10


CUFO::CUFO(void)
{
	//随机确定X位置
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMY_HEIGHT) + 1;

	//随机确定图像索引
	m_nImgIndex = 0;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -ENEMY_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nMotion = -1;
		m_ptPos.y = GAME_HEIGHT + ENEMY_HEIGHT;
	}

	m_freshFreaq = 0;
	
	//随机确定速度
	m_V = 3;
	m_xV = rand() % 6 + 5;

	m_nWait = 0;

}


CUFO::~CUFO(void)
{
}
BOOL CUFO::LoadImage()
{
	//return CGameObject::LoadImage(m_Images, IDB_BALL, RGB(0, 0, 0), 8, 8, 1);
	//加载游戏对象的图标对象
	CBitmap enemy1;
	if (!enemy1.LoadBitmap(IDB_ENHANCED_ENEMY))
		return FALSE;
	//创建CImageList对象
	if (!m_Images.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;//cx,cy 图片的宽度
	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	m_Images.Add(&enemy1, RGB(0, 0, 0));
}
BOOL CUFO::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 30)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + ENEMY_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;
	if (m_ptPos.x > GAME_WIDTH + ENEMY_HEIGHT)
		return FALSE;
	if (m_ptPos.x < 0)
		return FALSE;

	m_Images.Draw(pDC, 2, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CUFO::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}