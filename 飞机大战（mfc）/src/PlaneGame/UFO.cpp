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
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - ENEMY_HEIGHT) + 1;

	//���ȷ��ͼ������
	m_nImgIndex = 0;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -ENEMY_HEIGHT;
	if (m_nImgIndex % 2 != 0)//�����ͼ��������ż��
	{
		m_nMotion = -1;
		m_ptPos.y = GAME_HEIGHT + ENEMY_HEIGHT;
	}

	m_freshFreaq = 0;
	
	//���ȷ���ٶ�
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
	//������Ϸ�����ͼ�����
	CBitmap enemy1;
	if (!enemy1.LoadBitmap(IDB_ENHANCED_ENEMY))
		return FALSE;
	//����CImageList����
	if (!m_Images.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;//cx,cy ͼƬ�Ŀ��
	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
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