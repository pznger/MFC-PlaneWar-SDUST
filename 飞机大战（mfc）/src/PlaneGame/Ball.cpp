#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"

CImageList CBall::m_Images;
CImageList CBall::m_Images2;

CBall::CBall(int x,int y,int nMontion):CGameObject(x,y),m_nMotion(nMontion),m_chargeDirection(0)
{

}
CBall::CBall(int x, int y, int nMontion,int c) : CGameObject(x, y), m_nMotion(nMontion),m_chargeDirection(c),m_type(0)
{

}
CBall::CBall(int x, int y, int nMontion, int c,int d) : CGameObject(x, y), m_nMotion(nMontion), m_chargeDirection(c),m_type(d)
{

}
CBall::~CBall(void)
{
}
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
		m_ptPos.x = m_ptPos.x + m_nMotion * 8 * m_chargeDirection;
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;
	if (this->getType() == 0)
	{
		m_Images.Draw(pDC,1,m_ptPos,ILD_TRANSPARENT);
	}
	else if (this->getType() == 1)
	{
		m_Images.Draw(pDC, 4, m_ptPos, ILD_TRANSPARENT);
	}
	else if (this->getType() == 2)
	{
		m_Images.Draw(pDC, 2, m_ptPos, ILD_TRANSPARENT);
	}
	

	return TRUE;
}

BOOL CBall::LoadImage()
{

	//加载游戏对象的图标对象
	CBitmap ball;
	if (!ball.LoadBitmap(IDB_MISSLE_DOWN))
		return FALSE;
	//创建CImageList对象
	if (!m_Images.Create(15, 40, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;//cx,cy 图片的宽度
	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	m_Images.Add(&ball, RGB(0, 0, 0));

	
}