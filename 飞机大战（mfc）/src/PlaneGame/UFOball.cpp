#include "stdafx.h"
#include "UFOball.h"
#include "Ball.h"
#include "resource.h"
#define PI 3.1415926535
#define BALL_HEIGHT 40
#define UFO_BALL_WIDTH 15
#define UFO_BALL_HEIGHT 15
#include <math.h>
CImageList UFOball::m_Images;
UFOball::UFOball(int x, int y, int nMontion):CBall(x,y,nMontion)
{

}
UFOball::UFOball(int x, int y, int nMontion,double vx,double vy) : CBall(x, y, nMontion)
{
	m_vx = vx;
	m_vy=vy;
}
UFOball::~UFOball()
{

}
BOOL UFOball::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_vx * 2;
		m_ptPos.x = m_ptPos.x + m_vy * 2;
	}

	if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BALL_HEIGHT)
		return FALSE;
	
	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL UFOball::LoadImage()
{

	return CGameObject::LoadImage(m_Images, IDB_BALL, RGB(0, 0, 0), 8, 8, 1);

}