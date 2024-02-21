#include "StdAfx.h"
#include "missle.h"
#include "resource.h"
#include <atlimage.h>
#include <graphics.h>
#include <Windows.h>
#include <gdiplus.h>
#include <afxcmn.h>
#pragma comment(lib, "gdiplus.lib")
CImageList CMissle::m_Images;
CImageList CMissle::m_Images2;
CMissle::CMissle(int x, int y, int nMontion) :CGameObject(x, y),m_nMotion(nMontion), m_chargeDirection(0),m_freshFreaq(0),directY(1)
{

}
CMissle::CMissle(int x, int y, int nMontion, int c) : CGameObject(x, y),m_nMotion(nMontion), m_chargeDirection(c), m_freshFreaq(0), directY(1)
{

}
CMissle::~CMissle(void)
{
}
void CMissle::SetImageRotationAngle(double angle,CImage m_StaticImage)
{
	
}
BOOL CMissle::Draw(CDC* pDC, BOOL bPause)
{
    if (!bPause)
    {
        m_freshFreaq++;
        if (m_freshFreaq > 0 && m_freshFreaq <= 100)
        {
            m_ptPos.y = m_ptPos.y + m_nMotion * 6 * directY;
            m_ptPos.x = m_ptPos.x + m_nMotion * m_nMotion * m_chargeDirection;
        }
        else
        {
            directY = 1;
            m_ptPos.y = m_ptPos.y + m_nMotion * 8;
        }
    }

    if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
        return FALSE;
    if (m_ptPos.y < -BALL_HEIGHT)
        return FALSE;

    // ��graphics�����Ͻ��л�ͼ����
    if (directY == 1)
    {
        m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
    }
    else if (directY == -1)
    {
        m_Images2.Draw(pDC, 4, m_ptPos, ILD_TRANSPARENT);
    }
    return TRUE;
}

BOOL CMissle::Draw(CDC* pDC, int shearAngle, BOOL bPause)
{
    if (!bPause)
    {
        m_freshFreaq++;
        if (m_freshFreaq > 0 && m_freshFreaq <= 100)
        {
            m_ptPos.y = m_ptPos.y + m_nMotion * 6;
            m_ptPos.x = m_ptPos.x + m_nMotion * m_nMotion * m_chargeDirection;
        }
        else
        {
            m_ptPos.y = m_ptPos.y + m_nMotion * 8;
        }
    }

    if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
        return FALSE;
    if (m_ptPos.y < -BALL_HEIGHT)
        return FALSE;

    // ����һ��Graphics�����Խ��л�ͼ����
    Gdiplus::Graphics graphics(pDC->GetSafeHdc());

    // ����һ��Matrix����
    Gdiplus::Matrix matrix;

    // ����Matrix�����Shear������ʵ����б
    float shearX = tan(shearAngle * 3.14159265f / 180); // ˮƽ�������б�̶�
    float shearY = 0.0f; // ��ֱ�������б�̶�
    matrix.Shear(shearX, shearY);

    // ��graphics���������ñ任����
    graphics.SetTransform(&matrix);

    // ��ȡm_images�Ŀ�Ⱥ͸߶�
    int width = 15;
    int height = 40;

    // ����һ�����Σ���ʾͼƬ��λ�úʹ�С
    Gdiplus::PointF destRect(m_ptPos.x, m_ptPos.y);

    // ��graphics�����ϻ���ͼƬ
    //m_Images.Draw(&graphics, 0, destRect);

    return TRUE;
}


BOOL CMissle::LoadImage()
{
	//return CGameObject::LoadImage(m_Images, IDB_MISSLE_DOWN, RGB(0, 0, 0), 8, 8, 1);
	//������Ϸ�����ͼ�����
	CBitmap missle;
	if (!missle.LoadBitmap(IDB_MISSLE_DOWN))
		return FALSE;
	//����CImageList����
	if (!m_Images.Create(MISSLE_WIDTH, MISSLE_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;//cx,cy ͼƬ�Ŀ��
	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
	m_Images.Add(&missle, RGB(0, 0, 0));

    CBitmap missle2;
    if (!missle2.LoadBitmap(IDB_MISSLE_UP))
        return FALSE;
    //����CImageList����
    if (!m_Images2.Create(MISSLE_WIDTH, MISSLE_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
        return FALSE;//cx,cy ͼƬ�Ŀ��
    //ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
    m_Images2.Add(&missle2, RGB(0, 0, 0));
}