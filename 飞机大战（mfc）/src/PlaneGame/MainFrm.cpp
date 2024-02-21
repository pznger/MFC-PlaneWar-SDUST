// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"
#include <Windows.h>
#include <mmsystem.h>
#include "MainFrm.h"
#pragma comment(lib,"winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 去掉菜单栏
	SetMenu(NULL);
	
	//设置标题栏图标
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//SetIcon(m_hIcon, TRUE); 
	//SetIcon(m_hIcon, FALSE); 
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	
	cs.x = (::GetSystemMetrics(SM_CXSCREEN)-GAME_WIDTH) / 2;
	cs.y = (::GetSystemMetrics(SM_CYSCREEN)-GAME_HEIGHT) / 2;
	cs.cx = GAME_WIDTH;
	cs.cy = GAME_HEIGHT+::GetSystemMetrics(SM_CYMENU)+::GetSystemMetrics(SM_CYCAPTION);

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序



