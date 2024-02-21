#include "StdAfx.h"
#include "MyPlane.h"
#include "resource.h"

CImageList CMyPlane::m_Images;

CMyPlane::~CMyPlane(void)
{
}
CMyPlane::CMyPlane(void):m_nHorMotion(0),m_nVerMotion(0)
{
	m_nWait = 0;
	m_ptPos.x = 230;
	m_ptPos.y = 600;
}

BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;

}
void CMyPlane::SetPosition(int x, int y)
{
	m_ptPos.x = x-0.5*70;
	m_ptPos.y = y-0.5*35;
}
BOOL CMyPlane::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ME,RGB(0,0,0),50,60,1);

	 // 设置敌机图片的数量，这里假设有3种图片
	//int m_nImageCount = 7;

	//for (int i = 0; i < m_nImageCount; i++)
	//{
	//	if (!CGameObject::LoadImage(m_Images, IDB_ENEMY + i, RGB(0, 0, 0), 35, 35, 2))
	//		return FALSE;
	//}

	//return TRUE;
}
BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>4)
		m_nWait=0;


	if(!bPause)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion*6;
		m_ptPos.y = m_ptPos.y - m_nVerMotion*6;
	}

	if(m_ptPos.x>=GAME_WIDTH-PLANE_WIDTH)
		m_ptPos.x =GAME_WIDTH-PLANE_WIDTH;
	if(m_ptPos.x<=0)
		m_ptPos.x=0;

	if(m_ptPos.y<=0)
		m_ptPos.y =0;

	if(m_ptPos.y>=GAME_HEIGHT-PLANE_HEIGHT)
		m_ptPos.y=GAME_HEIGHT-PLANE_HEIGHT;


	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);
	return TRUE;
}