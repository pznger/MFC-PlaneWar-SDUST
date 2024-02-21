// PlaneGameView.h : CPlaneGameView 类的接口
//


#pragma once
#include <atlimage.h>
#include "bloodAdd.h"
#include "Level.h"
#include <sstream>
#define FULL_BLOOD 100//战机满血
#define BACKGROUND_SPEED_ROUND1 0.2//第一关背景移动速度
#define BACKGROUND_SPEED_ROUND2 1//第二关背景移动速度
#define BACKGROUND_SPEED_ROUND3 2//第三关背景移动速度
#define UFO_BALL_NUM 20//UFO一次发射子弹数
#define ENHANCED1_FREQ 20//加强敌机1出现频率
#define ENHANCED2_FREQ 30//加强敌机2出现频率
#define ENHANCED3_FREQ 50//加强敌机3出现频率
#define BLOOD_ADD_FREQ 20//血包出现频率
#define UFO_FREQ 50//UFO出现频率
#define FULL_SCORE 100//关卡满分
#define NORMAL_ENEMY_BALL_HARM 5//普通导弹伤害
#define MISSLE_HARM 10//追踪导弹伤害
#define UFO_BALL_HARM 3//UFO子弹伤害
#define PLANE_COLLIDE_HARM 10//飞机碰撞伤害
#define PI 3.1415926535
#define LEVEL_NUM 3
const wchar_t bg1[15] = L"plane\\bg00.png";
const wchar_t bg2[15] = L"plane\\bg02.png";
const wchar_t bg3[15] = L"plane\\bg03.png";
// 声明鼠标移动事件处理函数
afx_msg void OnMouseMove(UINT nFlags, CPoint point);

class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType{enEnemy,enBomb,enBall,enExplosion,enEnhanced,enEnhanced2,enBlood,enMissle,enEnhanced3,enUFO,enUFOBall,enBOSS};

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;
	int bgX = 0;//背景图片X坐标
	int bgY = 0;//背景图片Y坐标
	//CImage imgNumber[10];
	int m_score;//玩家分数
	int playerBlood;//玩家血量
	static int k ;//第几个关卡
	//wchar_t* bg0[100][50] ; 
	wchar_t* bg;// 将bg声明为const wchar_t类型的指针变量
	CPoint m_planePosition;//飞机位置
	int enemyCnt1 = 0;//控制第一种强化敌机出现频率
	int enemyCnt2 = 0;//控制第二种强化敌机出现频率
	int enemyCnt3 = 0;//控制第三种强化敌机出现频率
	int enemyCnt4 = 0;//控制UFO出现频率
	int enemyCnt5 = 0;//控制BOSS出现频率
	bool isExist=TRUE;//玩家是否还存在
	//CObList bloodList;//血包
	//CBlood* blood;
	BOOL bloodExist;//标记屏幕中是否存在血包
	//int lifeCount;//血包产生控制参数
	//CRect rect;//窗口屏幕矩形
	bool isDebugMode = false;
	Level* gameLevel;
	UINT_PTR m_nTimerID;      // 计时器ID
	bool m_IsWin;           // 是否通关
	ULONGLONG m_dwStartTime;     // 通关开始时间
	ULONGLONG m_dwTotalTime;     // 通关所花费的总时间
	int m_highScore;//最高分
	bool m_isScoreWindowCreated;
	bool isBOSSDie;
	bool isBOSSExist;

// 操作 
public:
	//绘制血条函数
	void drawBloodBar(int x, int y, int width, int height, int lineWidth, COLORREF boardColor, COLORREF emptyColor, COLORREF fillColor, float percent);
	//鼠标移动函数
	void OnMouseMove(UINT nFlags, CPoint point);
	//设定位置函数
	void SetPosition(int x, int y);

	void GetHighestScore();

	void ReadHighestScore();


// 重写
public: 
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);


	void AI();//按键检测

	void enemyCreate();//产生敌机

	void backgroundMove();//背景移动

	void enemyShoot();//敌机发射子弹

	void checkCollide();//碰撞检测

	void keyEvent();//按键检测

	void debug();//切换调试模式

	void playerShoot();//玩家反射子弹

	void planeCollideCheck();//战机与敌机碰撞检测

	void bulletCollideCheck();//子弹碰撞检测

	void propCollideCheck();//道具碰撞检测

	void Remove();

	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;

	CObList    m_ObjList[12];



// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};


#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

