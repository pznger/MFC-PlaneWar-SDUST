#include "stdafx.h"
#include "Boss.h"
#include "resource.h"

CImageList CBOSS::m_Images;
CBOSS::CBOSS(void)
{
	//随机确定X位置
	m_ptPos.x = (GAME_WIDTH / 2) - (BOSS_WIDTH / 2) - rand() % 200;

	//随机确定图像索引
	m_nImgIndex = 0;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -BOSS_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nMotion = -1;
		m_ptPos.y = GAME_HEIGHT + BOSS_HEIGHT;
	}

	m_freshFreaq = 0;
	//随机确定速度
	m_V = 3;
	m_xV = rand() % 6 + 5;

	m_chargeDirection = 1;
	m_nWait = 0;
}
CBOSS::CBOSS(int c)
{
	//随机确定X位置
	m_ptPos.x = (GAME_WIDTH / 2) - (BOSS_WIDTH / 2) - rand() % 200;

	//随机确定图像索引
	m_nImgIndex = 0;

	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -BOSS_HEIGHT;
	if (m_nImgIndex % 2 != 0)//如果是图像索引是偶数
	{
		m_nMotion = -1;
		m_ptPos.y = GAME_HEIGHT + BOSS_HEIGHT;
	}

	m_freshFreaq = 0;
	//随机确定速度
	m_V = 3;
	m_xV = rand() % 6 + 5;

	m_nWait = 0;

	m_chargeDirection = c;
}

CBOSS::~CBOSS(void)
{
}
BOOL CBOSS::LoadImage()
{
	//加载游戏对象的图标对象
	CBitmap enemy1;
	if (!enemy1.LoadBitmap(IDB_BOSS))
		return FALSE;
	//创建CImageList对象
	if (!m_Images.Create(BOSS_WIDTH, BOSS_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;//cx,cy 图片的宽度
	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	m_Images.Add(&enemy1, RGB(0, 0, 0));
}
BOOL CBOSS::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 30)
		m_nWait = 0;

	if (!bPause)
	{
		m_freshFreaq++;
		if (m_freshFreaq < 100)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		}
		else
		{
			if (m_ptPos.x > GAME_WIDTH - BOSS_WIDTH + 50)
			{
				m_chargeDirection = -1;
			}
			else if(m_ptPos.x < - 50)
			{
				m_chargeDirection = 1;
			}
			m_ptPos.x = m_ptPos.x + m_nMotion * m_xV * m_chargeDirection;
		}
		
	}


	if (m_ptPos.y > GAME_HEIGHT + BOSS_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 4, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBOSS::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}