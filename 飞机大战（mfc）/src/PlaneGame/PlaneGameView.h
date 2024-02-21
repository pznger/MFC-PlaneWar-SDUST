// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once
#include <atlimage.h>
#include "bloodAdd.h"
#include "Level.h"
#include <sstream>
#define FULL_BLOOD 100//ս����Ѫ
#define BACKGROUND_SPEED_ROUND1 0.2//��һ�ر����ƶ��ٶ�
#define BACKGROUND_SPEED_ROUND2 1//�ڶ��ر����ƶ��ٶ�
#define BACKGROUND_SPEED_ROUND3 2//�����ر����ƶ��ٶ�
#define UFO_BALL_NUM 20//UFOһ�η����ӵ���
#define ENHANCED1_FREQ 20//��ǿ�л�1����Ƶ��
#define ENHANCED2_FREQ 30//��ǿ�л�2����Ƶ��
#define ENHANCED3_FREQ 50//��ǿ�л�3����Ƶ��
#define BLOOD_ADD_FREQ 20//Ѫ������Ƶ��
#define UFO_FREQ 50//UFO����Ƶ��
#define FULL_SCORE 100//�ؿ�����
#define NORMAL_ENEMY_BALL_HARM 5//��ͨ�����˺�
#define MISSLE_HARM 10//׷�ٵ����˺�
#define UFO_BALL_HARM 3//UFO�ӵ��˺�
#define PLANE_COLLIDE_HARM 10//�ɻ���ײ�˺�
#define PI 3.1415926535
#define LEVEL_NUM 3
const wchar_t bg1[15] = L"plane\\bg00.png";
const wchar_t bg2[15] = L"plane\\bg02.png";
const wchar_t bg3[15] = L"plane\\bg03.png";
// ��������ƶ��¼�������
afx_msg void OnMouseMove(UINT nFlags, CPoint point);

class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType{enEnemy,enBomb,enBall,enExplosion,enEnhanced,enEnhanced2,enBlood,enMissle,enEnhanced3,enUFO,enUFOBall,enBOSS};

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;
	int bgX = 0;//����ͼƬX����
	int bgY = 0;//����ͼƬY����
	//CImage imgNumber[10];
	int m_score;//��ҷ���
	int playerBlood;//���Ѫ��
	static int k ;//�ڼ����ؿ�
	//wchar_t* bg0[100][50] ; 
	wchar_t* bg;// ��bg����Ϊconst wchar_t���͵�ָ�����
	CPoint m_planePosition;//�ɻ�λ��
	int enemyCnt1 = 0;//���Ƶ�һ��ǿ���л�����Ƶ��
	int enemyCnt2 = 0;//���Ƶڶ���ǿ���л�����Ƶ��
	int enemyCnt3 = 0;//���Ƶ�����ǿ���л�����Ƶ��
	int enemyCnt4 = 0;//����UFO����Ƶ��
	int enemyCnt5 = 0;//����BOSS����Ƶ��
	bool isExist=TRUE;//����Ƿ񻹴���
	//CObList bloodList;//Ѫ��
	//CBlood* blood;
	BOOL bloodExist;//�����Ļ���Ƿ����Ѫ��
	//int lifeCount;//Ѫ���������Ʋ���
	//CRect rect;//������Ļ����
	bool isDebugMode = false;
	Level* gameLevel;
	UINT_PTR m_nTimerID;      // ��ʱ��ID
	bool m_IsWin;           // �Ƿ�ͨ��
	ULONGLONG m_dwStartTime;     // ͨ�ؿ�ʼʱ��
	ULONGLONG m_dwTotalTime;     // ͨ�������ѵ���ʱ��
	int m_highScore;//��߷�
	bool m_isScoreWindowCreated;
	bool isBOSSDie;
	bool isBOSSExist;

// ���� 
public:
	//����Ѫ������
	void drawBloodBar(int x, int y, int width, int height, int lineWidth, COLORREF boardColor, COLORREF emptyColor, COLORREF fillColor, float percent);
	//����ƶ�����
	void OnMouseMove(UINT nFlags, CPoint point);
	//�趨λ�ú���
	void SetPosition(int x, int y);

	void GetHighestScore();

	void ReadHighestScore();


// ��д
public: 
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);


	void AI();//�������

	void enemyCreate();//�����л�

	void backgroundMove();//�����ƶ�

	void enemyShoot();//�л������ӵ�

	void checkCollide();//��ײ���

	void keyEvent();//�������

	void debug();//�л�����ģʽ

	void playerShoot();//��ҷ����ӵ�

	void planeCollideCheck();//ս����л���ײ���

	void bulletCollideCheck();//�ӵ���ײ���

	void propCollideCheck();//������ײ���

	void Remove();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;

	CObList    m_ObjList[12];



// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};


#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

