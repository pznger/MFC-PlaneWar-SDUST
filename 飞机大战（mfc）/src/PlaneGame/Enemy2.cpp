#include "StdAfx.h"
#include "Enemy2.h"
#include "resource.h"

CImageList CEnemy2::m_Images;

CEnemy2::CEnemy2(void)
{
	//随机确定X位置
	m_ptPos.x = (GAME_WIDTH / 2) - (ENEMY_WIDTH / 2)-rand()%200;

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
	m_xV = rand()%6+5;

	m_chargeDirection = 1;
	m_nWait = 0;
}
CEnemy2::CEnemy2(int c)
{
	//随机确定X位置
	m_ptPos.x = (GAME_WIDTH / 2) - (ENEMY_WIDTH / 2) - rand() % 200;

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

	m_chargeDirection = c;
}

CEnemy2::~CEnemy2(void)
{
}
BOOL CEnemy2::LoadImage()
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
BOOL CEnemy2::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait > 10)
		m_nWait = 0;
	
	if (!bPause)
	{
		/*
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		int randInt = rand() % 2 + 1;
		if (m_ptPos.x>0 || m_ptPos.x<GAME_WIDTH - ENEMY_WIDTH-100)
		{
			if (randInt % 2 == 0)
			{
				m_ptPos.x = m_ptPos.x + m_nMotion * m_xV;
			}
			else
			{
				m_ptPos.x = m_ptPos.x - m_nMotion * m_xV;
			}
		}
		*/
		m_freshFreaq++;
		if (m_freshFreaq < 40)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		}
		else if (m_freshFreaq >= 40 && m_freshFreaq <= 70)
		{
			m_ptPos.x = m_ptPos.x + m_nMotion * m_xV;
			//m_ptPos.y = m_ptPos.y - m_nMotion * m_V;

		}
		else if (m_freshFreaq > 70 && m_freshFreaq <= 100)
		{
			m_ptPos.x = m_ptPos.x - m_nMotion * m_xV;
			//m_ptPos.y = m_ptPos.y + m_nMotion * m_V;

		}
		else if (m_freshFreaq > 100 && m_freshFreaq <= 120)
		{
			m_ptPos.x = m_ptPos.x + m_nMotion * m_xV;
		}
		else if (m_freshFreaq > 120 && m_freshFreaq <= 140)
		{
			m_ptPos.x = m_ptPos.x - m_nMotion * m_xV;
		}
		else if (m_freshFreaq > 140 && m_freshFreaq <= 160)
		{
			m_ptPos.x = m_ptPos.x + m_nMotion * m_xV;
		}
		else if (m_freshFreaq > 140 && m_freshFreaq <= 180)
		{
			m_ptPos.x = m_ptPos.x - m_nMotion * m_xV;
		}
		else if(m_freshFreaq >180 && m_freshFreaq <= 240 )
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		}
		else if (m_freshFreaq > 240 && m_freshFreaq <= 250)
		{
			m_ptPos.x = m_ptPos.x + m_nMotion * m_xV;
		}
		else if (m_freshFreaq > 250 && m_freshFreaq <= 260)
		{
			m_ptPos.x = m_ptPos.x - m_nMotion * m_xV;
		}
		else if (m_freshFreaq > 260 && m_freshFreaq <= 280)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		}
		else if(m_freshFreaq > 280 && m_freshFreaq <= 320)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V * 1.5;
			
			m_ptPos.x = m_ptPos.x + m_nMotion * m_xV * m_chargeDirection;	
		}
		else
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V * 5;
		}
	}


	if (m_ptPos.y > GAME_HEIGHT + ENEMY_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -ENEMY_HEIGHT)
		return FALSE;
	//if (m_ptPos.x > GAME_WIDTH + ENEMY_HEIGHT)
	//	return FALSE;
	//if (m_ptPos.x < 0)
	//	return FALSE;

	m_Images.Draw(pDC, 1, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CEnemy2::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}