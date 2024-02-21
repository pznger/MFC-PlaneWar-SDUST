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

    // 在graphics对象上进行绘图操作
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

    // 创建一个Graphics对象以进行绘图操作
    Gdiplus::Graphics graphics(pDC->GetSafeHdc());

    // 创建一个Matrix对象
    Gdiplus::Matrix matrix;

    // 设置Matrix对象的Shear参数来实现倾斜
    float shearX = tan(shearAngle * 3.14159265f / 180); // 水平方向的倾斜程度
    float shearY = 0.0f; // 垂直方向的倾斜程度
    matrix.Shear(shearX, shearY);

    // 在graphics对象上设置变换矩阵
    graphics.SetTransform(&matrix);

    // 获取m_images的宽度和高度
    int width = 15;
    int height = 40;

    // 定义一个矩形，表示图片的位置和大小
    Gdiplus::PointF destRect(m_ptPos.x, m_ptPos.y);

    // 在graphics对象上绘制图片
    //m_Images.Draw(&graphics, 0, destRect);

    return TRUE;
}


BOOL CMissle::LoadImage()
{
	//return CGameObject::LoadImage(m_Images, IDB_MISSLE_DOWN, RGB(0, 0, 0), 8, 8, 1);
	//加载游戏对象的图标对象
	CBitmap missle;
	if (!missle.LoadBitmap(IDB_MISSLE_DOWN))
		return FALSE;
	//创建CImageList对象
	if (!m_Images.Create(MISSLE_WIDTH, MISSLE_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;//cx,cy 图片的宽度
	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	m_Images.Add(&missle, RGB(0, 0, 0));

    CBitmap missle2;
    if (!missle2.LoadBitmap(IDB_MISSLE_UP))
        return FALSE;
    //创建CImageList对象
    if (!m_Images2.Create(MISSLE_WIDTH, MISSLE_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
        return FALSE;//cx,cy 图片的宽度
    //图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
    m_Images2.Add(&missle2, RGB(0, 0, 0));
}