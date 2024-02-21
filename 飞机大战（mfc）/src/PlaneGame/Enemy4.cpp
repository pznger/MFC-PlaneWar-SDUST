#include "StdAfx.h"
#include "Enemy4.h"
#include "resource.h"

CImageList CEnemy4::m_Images;

CEnemy4::CEnemy4(void)
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

CEnemy4::~CEnemy4(void)
{
}
BOOL CEnemy4::LoadImage()
{
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
BOOL CEnemy4::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 80)
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

	m_Images.Draw(pDC, 4, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy4::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}