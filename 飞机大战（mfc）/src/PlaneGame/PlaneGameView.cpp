// PlaneGameView.cpp : CPlaneGameView ���ʵ��
#include "stdafx.h"
#include "PlaneGame.h"
#include "gdiplus.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Bomb.h"
#include "Ball.h"
#include "missle.h"
#include "UFO.h"
#include "UFOball.h"
#include "Explosion.h"
#include "BOSS.h"
#include <atlimage.h>
#include <string>
#include <mmsystem.h>
#include "bloodAdd.h"
#include <fstream> // �ļ���д����
#include <string>  // �ַ�������
#include <ctime>   // ʱ�䴦��
#pragma comment(lib,"winmm.lib")
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#define	BLACK			0
#define	BLUE			0xAA0000
#define	GREEN			0x00AA00
#define	CYAN			0xAAAA00
#define	RED				0x0000AA
#define	MAGENTA			0xAA00AA
#define	BROWN			0x0055AA
#define	LIGHTGRAY		0xAAAAAA
#define	DARKGRAY		0x555555
#define	LIGHTBLUE		0xFF5555
#define	LIGHTGREEN		0x55FF55
#define	LIGHTCYAN		0xFFFF55
#define	LIGHTRED		0x5555FF
#define	LIGHTMAGENTA	0xFF55FF
#define	YELLOW			0x55FFFF
#define	WHITE			0xFFFFFF
#endif
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)
BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()
// CPlaneGameView ����/����
void  playSound(const char* name) {
	static int index = 1;
	char cmd[512];

	if (index == 1) {
		sprintf_s(cmd, sizeof(cmd), "play %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
		mciSendString(cmd, 0, 0, 0);
		index++;
	}
	else if (index == 2) {
		sprintf_s(cmd, sizeof(cmd), "play %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
		mciSendString(cmd, 0, 0, 0);
		index = 1;
	}
}
void CPlaneGameView::ReadHighestScore()
{
	ifstream recordFile("record.txt");
	if (!recordFile)
	{
		// �ļ���ʧ�ܣ�����Ĭ�ϵ���߷���
		return;
	}
	string line;
	while (getline(recordFile, line))
	{
		stringstream ss(line);
		string title;
		int score;
		if (ss >> title >> score && title == "��߷���")
		{
			m_highScore = score;
			break;
		}
	}
	recordFile.close();
}
CPlaneGameView::CPlaneGameView():m_pMe(NULL),m_score(0),playerBlood(100),m_IsWin(false), m_isScoreWindowCreated(false), isBOSSDie(false),isBOSSExist(false)
{
	// TODO: �ڴ˴���ӹ������
	bg = new wchar_t[15];
	wcscpy(bg, L"plane\\bg00.png");
	gameLevel = new Level(30, 40, 50, 60, 1, 5, 3, 10, 5, 5, 100,60);
	ReadHighestScore();
}
CPlaneGameView::~CPlaneGameView()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
	delete[] bg;
}
BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	playSound("plane\\3.mp3");
	return CView::PreCreateWindow(cs);
}
void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}
BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}
#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}
void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}
void CPlaneGameView::Remove()
{
	m_ObjList[enEnhanced].RemoveAll();
	m_ObjList[enEnemy].RemoveAll();
	m_ObjList[enEnhanced2].RemoveAll();
	m_ObjList[enEnhanced3].RemoveAll();
	m_ObjList[enBall].RemoveAll();
	m_ObjList[enMissle].RemoveAll();
	m_ObjList[enBOSS].RemoveAll();
	isExist = FALSE;
	delete m_pMe;
	m_pMe = NULL;
	mciSendString("stop plane/3.mp3", 0, 0, 0);//�رձ�������
}
int CPlaneGameView::k = 1;
BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);
	//�������������
	srand( (unsigned)time( NULL ) );
	//�����豸DC
	m_pDC = new CClientDC(this);
	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);
	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);
	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);
	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CEnemy2::LoadImage();
	CEnemy3::LoadImage();
	CBlood::LoadImage();
	CMissle::LoadImage();
	CEnemy4::LoadImage();
	CUFO::LoadImage();
	UFOball::LoadImage();
	CBOSS::LoadImage();
	//��������(ս��)
	m_pMe = new CMyPlane;
	//������Ϸ
	SetTimer(1,30,NULL);
	mciSendString("play plane/3.mp3 repeat", 0, 0, 0);//������������
	return TRUE;
}
void CPlaneGameView::drawBloodBar(int x, int y, int width, int height, int lineWidth, COLORREF boardColor, COLORREF emptyColor, COLORREF fillColor, float percent) 
{
	CDC* pDC= m_pMemDC;
	CPen penBloodBar;
	CBrush brushEmpty, brushFill;
	penBloodBar.CreatePen(PS_SOLID | PS_ENDCAP_ROUND, lineWidth, boardColor);
	brushEmpty.CreateSolidBrush(emptyColor);
	brushFill.CreateSolidBrush(fillColor);
	CPen* pOldPen = pDC->SelectObject(&penBloodBar);
	CBrush* pOldBrush = pDC->SelectObject(&brushEmpty);
	CRect rectEmpty(x, y, x + width, y + height);
	pDC->Rectangle(&rectEmpty);
	pDC->SelectObject(&brushFill);
	pDC->SelectObject(pOldPen);
	if (percent > 0) {
		CRect rectFill(x + 0.5 * lineWidth, y + lineWidth * 0.5, x + width * percent, y + height - 0.5 * lineWidth);
		pDC->Rectangle(&rectFill);
	}
	pDC->SelectObject(pOldBrush);
}
void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	const wchar_t overImg[15] = L"plane\\over.png";
	// ��ʼ�� GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	if ((m_score >= gameLevel->fullScore) )
	{
		if (k==1&& (isBOSSDie == true))
		{
			m_ObjList[enEnhanced].RemoveAll();
			m_ObjList[enEnemy].RemoveAll();
			m_ObjList[enEnhanced2].RemoveAll();
			m_ObjList[enEnhanced3].RemoveAll();
			m_ObjList[enBall].RemoveAll();
			m_ObjList[enMissle].RemoveAll();
			m_ObjList[enUFO].RemoveAll();
			isExist = FALSE;
			if (GetKey(0x56))
			{
				//Sleep(1000);//Ч������
				m_score = 0;
				playerBlood = 100;
				isExist = TRUE;
				isBOSSDie = false;
				isBOSSExist = false;
				//��������(ս��)
				m_pMe = new CMyPlane;
				mciSendString("play plane/3.mp3 repeat", 0, 0, 0);//�رձ�������
				gameLevel->setLevelData(30 - k * 5, 40 - k * 5, 50 - k * 5, 60 - k * 5, k, 5 + 2 * k, 3 + 2 * k, 10 + 2 * k, 5 + 2 * k, 8+2*k,100,100);
				wcscpy(bg, bg2);
				m_score = 0;
				k++;
				playerBlood = 100;
			}
		}
		else if (k==2&& (isBOSSDie == true))
		{
			m_ObjList[enEnhanced].RemoveAll();
			m_ObjList[enEnemy].RemoveAll();
			m_ObjList[enEnhanced2].RemoveAll();
			m_ObjList[enEnhanced3].RemoveAll();
			m_ObjList[enBall].RemoveAll();
			m_ObjList[enMissle].RemoveAll();
			isExist = FALSE;
			if (GetKey(0x56))
			{
				m_score = 0;
				playerBlood = 100;
				isExist = TRUE;
				isBOSSExist = false;
				isBOSSDie = false;
				//��������(ս��)
				m_pMe = new CMyPlane;
				mciSendString("play plane/3.mp3 repeat", 0, 0, 0);//�رձ�������
				gameLevel->setLevelData(30 - k * 5, 40 - k * 5, 50 - k * 5, 60 - k * 5, k, 5 + 2 * k, 3 + 2 * k, 10 + 2 * k, 5 + 2 * k, 8 + 2 * k, 100,100);
				wcscpy(bg, bg3);
				m_score = 0;
				k++;
				playerBlood = 100;
			}
		}
	}
	if (k == 3 && playerBlood <= 0)
	{
		m_IsWin = true;
	}
	Gdiplus::Bitmap skyBitmap(bg);

	// �������ͼƬ
	Gdiplus::Graphics graphics(pMemDC->m_hDC);
	graphics.DrawImage(&skyBitmap, bgX, bgY, GAME_WIDTH, GAME_HEIGHT * 2);

	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	else
	{

		Gdiplus::Bitmap over(overImg);

		// ������Ϸʧ��ͼƬ
		Gdiplus::Graphics graphics(pMemDC->m_hDC);
		if (isBOSSExist!=true && k != LEVEL_NUM)
		{
			graphics.DrawImage(&over, bgX, GAME_HEIGHT / 2 - 100, 512, 170);
		}
		if (GetKey(0x43))
		{
			m_score = 0;
			playerBlood = 100;

			isExist = TRUE;

			isBOSSDie = false;
			isBOSSExist = false;
			//��������(ս��)
			m_pMe = new CMyPlane;
			mciSendString("play plane/3.mp3 repeat", 0, 0, 0);//�رձ�������
		}
	}
	if (k != LEVEL_NUM&&m_score>=gameLevel->fullScore)
	{
		if (isBOSSDie == true)
		{
			CString levelDisplay = _T("��V����ɱ����л�......");
			pMemDC->SetBkMode(TRANSPARENT);
			pMemDC->SetTextColor(WHITE);
			pMemDC->TextOut(160, 550, levelDisplay);
			//isBOSSDie = false;
		}
		
	}
	//���� ��������ը���л����ӵ���ǿ���л���Ѫ��
	for(int i=0;i<12;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
	// ���Ʒ���
	CString strScore;
	strScore.Format(_T("%d"), m_score);
	// ��������ͼƬ
	for (int i = 0; i < strScore.GetLength(); i++)
	{
		wchar_t filePath[50];
		swprintf(filePath, L"res//sz//%c.png", strScore[i]);
		Gdiplus::Bitmap sz(filePath);

		// ����ͼƬλ��
		int x = 20 + i * 50;
		int y = 25;

		// ��������ͼƬ
		Gdiplus::Graphics graphics(pMemDC->m_hDC);
		graphics.DrawImage(&sz, x, y, 40, 60);
	}
	drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, playerBlood / 100.0);
	CString levelDisplay = _T("��ǰ�ؿ���");
	CString strLevel;
	strLevel.Format(_T("%d"), k);
	pMemDC->SetBkMode(TRANSPARENT);
	//pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RED);
	pMemDC->TextOut(GAME_WIDTH - 140, 20, levelDisplay);
	pMemDC->TextOut(GAME_WIDTH - 50, 20, strLevel);
	int lastHighScore = m_highScore;
	if (m_IsWin) 
	{
		if (m_score > lastHighScore)
		{
			std::ofstream recordFile("record.txt", std::ios::out);
			if (!recordFile)
			{
				CString str;
				str.Format(_T("�浵�ļ���"));
				AfxMessageBox(str);
				return;
			}
			m_IsWin = false;
			m_highScore = m_score;
			recordFile << "��߷��� " << m_highScore << std::endl;
			recordFile.close();
		}
		else
		{
			if (m_score == lastHighScore)
			{
				CString str;
				str.Format(_T("���ķ�����%d����ϲ����Խ�˼�¼�����ʷ��Ϸ��߷�"), m_score);
				pMemDC->SetBkMode(TRANSPARENT);
				pMemDC->SetTextColor(WHITE);
				pMemDC->TextOut(20, 550, str);
			}
			else
			{
				CString str,str1;
				str.Format(_T("���ķ�����%d�����ź���һ��û�д�����ʷ"), m_score);
				str1.Format(_T("������ʷ��Ϸ��߷�%d�ֽ���%d��"),m_highScore, m_highScore - m_score);
				//AfxMessageBox(str);
				pMemDC->SetBkMode(TRANSPARENT);
				pMemDC->SetTextColor(WHITE);
				//pMemDC->SetTextAlign(TA_CENTER);
				pMemDC->TextOut(50, 550, str);
				pMemDC->TextOut(100, 570, str1);
				m_IsWin = false;
			}
			
		}

	}

	CString tipsStr1, tipsStr2, tipsStr3, tipsStr4;
	tipsStr1.Format(_T("�ƶ���W A S D������Ҽ��϶�"));
	tipsStr2.Format(_T("�����ӵ����ո��������"));
	tipsStr3.Format(_T("���٣�H"));
	tipsStr4.Format(_T("���C"));
	// ������ѡ��һ���µ��������
	CFont font;
	font.CreatePointFont(100, _T("����")); // 12�������С��"Arial"����������
	CFont* pOldFont = pMemDC->SelectObject(&font);
	// �����ı�
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextColor(WHITE);
	pMemDC->TextOut(10, 705, tipsStr1);
	pMemDC->TextOut(10, 720, tipsStr2);
	pMemDC->TextOut(10, 735, tipsStr3);
	pMemDC->TextOut(10, 750, tipsStr4);

	// �ָ�ԭʼ����
	pMemDC->SelectObject(pOldFont);

	
	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);

	//m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, &cdc, 0, 0, SRCCOPY);
}

void CPlaneGameView::OnMouseMove(UINT nFlags, CPoint point)
{
	// ���·ɻ�λ��Ϊ���λ��
	m_planePosition = point;

	// ���ø��������ƶ��¼�������
	CView::OnMouseMove(nFlags, point);
}
void CPlaneGameView::backgroundMove()
{
	if (bgY >= 0)
	{
		bgY = -GAME_HEIGHT;
	}
	else
	{
		bgY += gameLevel->backgroundSpeed;
	}
		
}
void CPlaneGameView::enemyCreate()
{
	if (m_pMe == NULL)
	{
		return;
	}

	static int nCreator = rand() % 30 + 10;

	//���������ͨ�л�
	if (nCreator <= 0)
	{
		nCreator = rand() % 30 + 5;
		m_ObjList[enEnemy].AddTail(new CEnemy);
		//m_ObjList[enEnhanced].AddTail(new CEnemy2);
		
			enemyCnt1++;
			enemyCnt2++;
			enemyCnt3++;
			enemyCnt4++;
			enemyCnt5++;

		if (enemyCnt1 > gameLevel->enhanced1Freq)
		{
			m_ObjList[enEnhanced].AddTail(new CEnemy2);
			enemyCnt1 = 0;
		}

		if (enemyCnt2 > gameLevel->enhanced2Freq)
		{
			m_ObjList[enEnhanced2].AddTail(new CEnemy3);
			enemyCnt2 = 0;
		}

		if (enemyCnt3 > gameLevel->enhanced3Freq)
		{
			enemyCnt3 = 0;
			m_ObjList[enEnhanced3].AddTail(new CEnemy4);
		}

		if (enemyCnt4 > gameLevel->UFOFreq)
		{
			enemyCnt4 = 0;
			m_ObjList[enUFO].AddTail(new CUFO);
		}
		if (enemyCnt5 > gameLevel->BOSSFreq&&m_score>100)
		{
			enemyCnt5 = 0;
			enemyCnt4 = 0;
			enemyCnt3 = 0;
			enemyCnt2 = 0;
			enemyCnt1 = 0;

			isBOSSDie = false;
			m_ObjList[enBOSS].AddTail(new CBOSS);
			m_ObjList[enEnhanced].RemoveAll();
			m_ObjList[enEnemy].RemoveAll();
			m_ObjList[enEnhanced2].RemoveAll();
			m_ObjList[enEnhanced3].RemoveAll();
			//m_ObjList[enBall].RemoveAll();
			//m_ObjList[enMissle].RemoveAll();
			m_ObjList[enUFO].RemoveAll();
		}
	}
	nCreator--;
	if (m_pMe == NULL)
		return;
}
void CPlaneGameView::playerShoot()
{
	if (m_pMe == NULL)
	{
		return;
	}
	//����ս������
	if (GetKey(VK_SPACE) == 1 || GetKeyState(VK_LBUTTON) & 0x8000)//�����˿ո��
	{
		//cplaySound("plane\\shoot.mp3");
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10));
			m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10));
			if (k >= 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10));
			}
			if (k >= 3)
			{

			}
		}
	}
}
void CPlaneGameView::enemyShoot()
{
	if (m_pMe == NULL)
	{
		return;
	}
	//��ǿ��л�1�����ӵ�
	for (POSITION ePos = m_ObjList[enEnhanced].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy2* pEnemy = (CEnemy2*)m_ObjList[enEnhanced].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();

		BOOL by = FALSE;

		m_ObjList[enBall].AddTail(new CBall(ePt.x + 55, ePt.y + 30, pEnemy->GetMontion(), 0, 2));

	}

	//��ǿ��л�2�����ӵ�
	for (POSITION ePos = m_ObjList[enEnhanced2].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy3* pEnemy = (CEnemy3*)m_ObjList[enEnhanced2].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();
		BOOL by = FALSE;
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 55, ePt.y + 30, pEnemy->GetMontion(), 0, 1));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 65, ePt.y + 30, pEnemy->GetMontion(), -1, 1));
		m_ObjList[enBall].AddTail(new CBall(ePt.x + 45, ePt.y + 30, pEnemy->GetMontion(), 1, 1));
	}

	//��ǿ��л�3�����ӵ�
	for (POSITION ePos = m_ObjList[enEnhanced3].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy4* pEnemy = (CEnemy4*)m_ObjList[enEnhanced3].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();
		BOOL by = FALSE;
		m_ObjList[enMissle].AddTail(new CMissle(ePt.x + 55, ePt.y + 30, pEnemy->GetMontion()));
		m_ObjList[enMissle].AddTail(new CMissle(ePt.x + 55, ePt.y + 30, pEnemy->GetMontion()));
	}
	//UFO�����ӵ�
	if (m_pMe != NULL)
	{
		for (POSITION ePos = m_ObjList[enUFO].GetHeadPosition(); ePos != NULL;)
		{
			CUFO* pEnemy = (CUFO*)m_ObjList[enUFO].GetNext(ePos);
			if (!pEnemy->Fired())
				continue;
			CPoint  ePt = pEnemy->GetPoint();

			BOOL by = FALSE;

			for (int i = 0; i < UFO_BALL_NUM; i++)
			{
				double angle = 2 * PI * i / UFO_BALL_NUM;
				double r = 4 ;
				if (r == 0)continue;
				m_ObjList[enUFOBall].AddTail(new UFOball(ePt.x + 60, ePt.y + 70, pEnemy->GetMontion(), r * sin(angle), r * cos(angle)));
			}
		}
	}

	//BOSS�����ӵ�
	for (POSITION ePos = m_ObjList[enBOSS].GetHeadPosition(); ePos != NULL;)
	{
		CBOSS* pEnemy = (CBOSS*)m_ObjList[enBOSS].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();

		BOOL by = FALSE;
		if (playerBlood <= 0)
		{
			m_ObjList[enBOSS].RemoveAll();
		}
		//BOSS��������
		int randInt = rand() % 3;
		if (randInt == 0)
		{
			m_ObjList[enMissle].AddTail(new CMissle(ePt.x + 120, ePt.y + 200, pEnemy->GetMontion()));
			m_ObjList[enMissle].AddTail(new CMissle(ePt.x + 240, ePt.y + 200, pEnemy->GetMontion()));
		}
		else if (randInt == 1)
		{
			for (int i = 0; i < 30; i++)
			{
				double angle = 2 * PI * i / UFO_BALL_NUM;
				double r = 4 * angle;
				if (r == 0)
				{
					continue;
				}
				m_ObjList[enUFOBall].AddTail(new UFOball(ePt.x + 180, ePt.y + 200, pEnemy->GetMontion(), r * sin(angle), r * cos(angle)));
			}
		}
		else
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 100, ePt.y + 200, pEnemy->GetMontion(), -2, 1));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 180, ePt.y + 200, pEnemy->GetMontion(), 0, 1));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 260, ePt.y + 200, pEnemy->GetMontion(), 2, 1));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y + 250, pEnemy->GetMontion(), -1, 2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 180, ePt.y + 250, pEnemy->GetMontion(), 0, 2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 240, ePt.y + 250, pEnemy->GetMontion(), 1, 2));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 180, ePt.y + 250, pEnemy->GetMontion(), 0, 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 180, ePt.y + 250, pEnemy->GetMontion(), 0, 0));
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 180, ePt.y + 250, pEnemy->GetMontion(), 0, 0));

		}

	}
	//׷�ٵ�����ս����ײ
	if (m_pMe != NULL)
	{
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enMissle].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CMissle* pCEnemy = (CMissle*)m_ObjList[enMissle].GetNext(bPos1);
			CRect bRect = pCEnemy->GetRect();
			CRect tmpRect;

			if (m_pMe->getX() < pCEnemy->GetPoint().x)
			{
				pCEnemy->setChargeDirection(-5);
			}
			else if (m_pMe->getX() > pCEnemy->GetPoint().x && m_pMe->getX() < pCEnemy->GetPoint().x)
			{
				pCEnemy->setChargeDirection(0);
			}
			else
			{
				pCEnemy->setChargeDirection(5);
			}

			if (m_pMe->getY() <= pCEnemy->GetPoint().y - 100)
			{
				pCEnemy->setDirectY(-1);
			}
			else if (m_pMe->getY() > pCEnemy->GetPoint().y)
			{
				pCEnemy->setDirectY(1);
			}

			if (tmpRect.IntersectRect(&bRect, mRect))
			{

				//ɾ���ӵ�
				m_ObjList[enMissle].RemoveAt(bPos2);
				delete pCEnemy;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				playSound("plane\\blast.mp3");
				playerBlood -= MISSLE_HARM;
				//ɾ��ս��
				if (playerBlood <= 0)
				{
					Remove();
					break;
				}
			}
		}
	}
}
void CPlaneGameView::keyEvent()
{
	//����ĸ���������ƶ�ս��
	if (m_pMe == NULL)
	{
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		if (GetKey(0x48))
		{
			int nMeMotion = 0;
			m_pMe->SetVerMotion(0);
			m_pMe->SetHorMotion(0);

			nMeMotion = GetKey(0x57);//w
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(2);

			nMeMotion = GetKey(0x53);
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(-2);

			nMeMotion = GetKey(0x44);
			if (nMeMotion == 1)
				m_pMe->SetHorMotion(2);

			nMeMotion = GetKey(0x41);//a
			if (nMeMotion == 1)
				m_pMe->SetHorMotion(-2);
		}
		else
		{
			int nMeMotion = 0;
			m_pMe->SetVerMotion(0);
			m_pMe->SetHorMotion(0);

			nMeMotion = GetKey(0x57);
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(1);

			nMeMotion = GetKey(0x53);
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(-1);

			nMeMotion = GetKey(0x44);
			if (nMeMotion == 1)
				m_pMe->SetHorMotion(1);

			nMeMotion = GetKey(0x41);
			if (nMeMotion == 1)
				m_pMe->SetHorMotion(-1);
		}

	}
	if (GetKey(VK_RBUTTON))
		m_pMe->SetPosition(m_planePosition.x, m_planePosition.y);
}
void CPlaneGameView::planeCollideCheck()
{
	if (m_pMe == NULL)
	{
		return;
	}
	//�л���ս����ײ
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enEnemy].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy* pCEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&bRect, mRect))
		{

			//ɾ���ӵ�
			m_ObjList[enEnemy].RemoveAt(bPos2);
			delete pCEnemy;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");


			playerBlood -= gameLevel->CollideHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}

	
	//��ǿ�л�1��ս����ײ
	for (bPos1 = m_ObjList[enEnhanced].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy2* pCEnemy = (CEnemy2*)m_ObjList[enEnhanced].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (m_pMe->getX() < pCEnemy->GetPoint().x)
		{
			pCEnemy->m_chargeDirection = -1;
		}
		else if (m_pMe->getX() > pCEnemy->GetPoint().x && m_pMe->getX() < pCEnemy->GetPoint().x)
		{
			pCEnemy->m_chargeDirection = 0;
		}
		else
		{
			pCEnemy->m_chargeDirection = 2;
		}

		if (tmpRect.IntersectRect(&bRect, mRect))
		{

			//ɾ���ӵ�
			m_ObjList[enEnhanced].RemoveAt(bPos2);
			delete pCEnemy;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");


			playerBlood -= gameLevel->CollideHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}
	
	//��ǿ�л�2��ս����ײ
	for (bPos1 = m_ObjList[enEnhanced2].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy3* pCEnemy = (CEnemy3*)m_ObjList[enEnhanced2].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&bRect, mRect))
		{

			//ɾ���ӵ�
			m_ObjList[enEnhanced2].RemoveAt(bPos2);
			delete pCEnemy;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");

			playerBlood -= gameLevel->CollideHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}

	//��ǿ�л�3��ս����ײ
	for (bPos1 = m_ObjList[enEnhanced3].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy4* pCEnemy = (CEnemy4*)m_ObjList[enEnhanced3].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&bRect, mRect))
		{

			//ɾ���ӵ�
			m_ObjList[enEnhanced3].RemoveAt(bPos2);
			delete pCEnemy;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");


			playerBlood -= gameLevel->CollideHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}
	//UFO��ս����ײ
	for (bPos1 = m_ObjList[enUFO].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CUFO* pCEnemy = (CUFO*)m_ObjList[enUFO].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&bRect, mRect))
		{

			//ɾ���ӵ�
			m_ObjList[enUFO].RemoveAt(bPos2);
			delete pCEnemy;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");


			playerBlood -= gameLevel->CollideHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}
	for (bPos1 = m_ObjList[enEnemy].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS* pCEnemy = (CBOSS*)m_ObjList[enBOSS].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			playerBlood -= 80;
			pCEnemy->enhancedEnemyBlood -= 10;
			if (pCEnemy->enhancedEnemyBlood <= 0)
			{
				//ɾ���ӵ�
				m_ObjList[enBOSS].RemoveAt(bPos2);
				delete pCEnemy;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				playSound("plane\\blast.mp3");
			}
			playerBlood -= gameLevel->CollideHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}
}
void CPlaneGameView::bulletCollideCheck()
{
	if (m_pMe == NULL)
	{
		return;
	}
	//�л��ӵ�����ս��
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");

			playerBlood -= gameLevel->normalEnemyHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				Remove();
				break;
			}
		}
	}
	//ս������ը���л�
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				playSound("plane\\blast.mp3");
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;
				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				m_score++;
				break;

			}
		}
	}
	
	//ս������ը����ǿ�л�1
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnhanced].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy2* pEnemy = (CEnemy2*)m_ObjList[enEnhanced].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect(1);
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				pEnemy->enhancedEnemyBlood -= 1;

				//ɾ���л�
				if (pEnemy->enhancedEnemyBlood <= 0)
				{
					int x = pEnemy->GetPoint().x;
					int y = pEnemy->GetPoint().y;

					m_ObjList[enEnhanced].RemoveAt(ePos2);
					delete pEnemy;
					m_score += 10;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT,x,y));

					playSound("plane\\blast.mp3");
				}
				break;

			}
		}
	}
	

	//ս������ը����ǿ�л�2
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnhanced2].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy3* pEnemy = (CEnemy3*)m_ObjList[enEnhanced2].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect(1);
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				pEnemy->enhancedEnemyBlood -= 1;

				//ɾ���л�
				if (pEnemy->enhancedEnemyBlood <= 0)
				{
					int x = pEnemy->GetPoint().x;
					int y = pEnemy->GetPoint().y;

					m_ObjList[enEnhanced2].RemoveAt(ePos2);
					delete pEnemy;
					m_score += 10;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT,x,y));

					playSound("plane\\blast.mp3");

				}
				break;

			}
		}
	}
	//ս������ը����ǿ�л�3
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnhanced3].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy4* pEnemy = (CEnemy4*)m_ObjList[enEnhanced2].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect(1);
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);

				pEnemy->enhancedEnemyBlood -= 1;

				//ɾ���л�
				if (pEnemy->enhancedEnemyBlood <= 0)
				{
					int x = pEnemy->GetPoint().x;
					int y = pEnemy->GetPoint().y;

					m_ObjList[enEnhanced3].RemoveAt(ePos2);
					delete pEnemy;
					m_score += 10;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT,x,y));

					playSound("plane\\blast.mp3");

				}
				break;

			}
		}
	}
	//ս������ը��UFO
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enUFO].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CUFO* pEnemy = (CUFO*)m_ObjList[enUFO].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				pEnemy->enhancedEnemyBlood -= 1;
				//ɾ���л�
				if (pEnemy->enhancedEnemyBlood <= 0)
				{
					int x = pEnemy->GetPoint().x;
					int y = pEnemy->GetPoint().y;
					m_ObjList[enUFO].RemoveAt(ePos2);
					delete pEnemy;
					m_score += 10;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT,x,y));
					playSound("plane\\blast.mp3");
				}
				break;

			}
		}
	}
	//ս������ը��BOSS
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enBOSS].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CBOSS* pEnemy = (CBOSS*)m_ObjList[enBOSS].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect(BOSS_WIDTH,BOSS_HEIGHT);
			CRect tmpRect;

			drawBloodBar(pEnemy->GetPoint().x+180, pEnemy->GetPoint().y, 200, 10, 2, BLUE, DARKGRAY, GREEN, pEnemy->enhancedEnemyBlood / 200.0);

			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				pEnemy->enhancedEnemyBlood -= 1;
				//��ӱ�ըЧ��

				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
				);
				playSound("plane\\blast.mp3");

				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				if (pEnemy->enhancedEnemyBlood <= 0)
				{
					int x = pEnemy->GetPoint().x;
					int y = pEnemy->GetPoint().y;
					m_ObjList[enBOSS].RemoveAt(ePos2);
					delete pEnemy;
					m_score += 10;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT, x, y));
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT, x, y));
					m_ObjList[enBlood].AddTail(new CBlood(GAME_WIDTH, GAME_HEIGHT, x, y));

					playSound("plane\\blast.mp3");
					
					isBOSSDie = true;
					isBOSSExist = false;
				}
				break;

			}
		}
	}
	//UFO�ӵ�����ս��
	for (bPos1 = m_ObjList[enUFOBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		UFOball* pBall = (UFOball*)m_ObjList[enUFOBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//ɾ���ӵ�
			m_ObjList[enUFOBall].RemoveAt(bPos2);
			delete pBall;

			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);
			playSound("plane\\blast.mp3");

			playerBlood -= gameLevel->ufoBallHarm;
			//ɾ��ս��
			if (playerBlood <= 0)
			{
				// ��յл��б�
				m_ObjList[enEnhanced].RemoveAll();
				m_ObjList[enEnemy].RemoveAll();
				m_ObjList[enBOSS].RemoveAll();
				isExist = FALSE;
				delete m_pMe;
				m_pMe = NULL;
				mciSendString("stop plane/3.mp3", 0, 0, 0);//�رձ�������
				break;
			}
		}
	}

}
void CPlaneGameView::propCollideCheck()
{
	if (m_pMe == NULL)
	{
		return;
	}
	//Ѫ�����Ե�
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBlood].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBlood* pCEnemy = (CBlood*)m_ObjList[enBlood].GetNext(bPos1);
		CRect bRect = pCEnemy->GetRect();
		CRect tmpRect;

		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			m_ObjList[enBlood].RemoveAt(bPos2);
			delete pCEnemy;
			//�Ե�Ѫ���ظ�Ѫ��
			if (playerBlood >= 80)
			{
				playerBlood = 100;
			}
			else
			{
				playerBlood += 20;
			}
		}
	}
}
void CPlaneGameView::debug()
{
	if (GetKey(0x58))//����ģʽ
	{
		isDebugMode = true;
	}
	if (GetKey(0x5A))//�˳���Ѫ����ģʽ
	{
		//lastScore = m_score;
		isDebugMode = false;
	}
	if (isDebugMode)
	{
		playerBlood = 100;
	}
	if (GetKey(0x42))
	{
		m_score += 100;
	}
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	UpdateFrame(m_pMemDC);//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	backgroundMove();//����ͼƬ����
	enemyCreate();//����л�
	playerShoot();//��ҷ����ӵ�
	enemyShoot();//�л������ӵ�
	keyEvent();//��Ұ������
	planeCollideCheck();//�ɻ���л���ײ���
	bulletCollideCheck();//�ӵ���ɻ���ײ���
	propCollideCheck();//ս���������ײ���
	debug();//�������ģʽ
	//AI();

	CView::OnTimer(nIDEvent);
}