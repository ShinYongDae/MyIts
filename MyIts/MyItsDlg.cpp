
// MyItsDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MyIts.h"
#include "MyItsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyItsDlg 대화 상자



CMyItsDlg::CMyItsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYITS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pReelmap = NULL;
	m_bConverse = FALSE;
}

CMyItsDlg::~CMyItsDlg()
{
	if (m_pReelmap)
	{
		delete m_pReelmap;
		m_pReelmap = NULL;
	}
}

void CMyItsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyItsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMyItsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyItsDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyItsDlg 메시지 처리기

BOOL CMyItsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitReelmap();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyItsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyItsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyItsDlg::InitReelmap()
{
	CString sPathRmap = _T("C:\\R2RSet\\Reelmap0.bin");
	CString sPathYield = _T("C:\\R2RSet\\Yield0.bin");
	CString sPathMark = _T("C:\\R2RSet\\Mark0.bin");
	m_pReelmap = new CSimpleReelmap(sPathRmap, sPathYield, sPathMark, this);
	m_pReelmap->Init(20, 30, 3);
}

void CMyItsDlg::Disp()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");
	if(m_bConverse)
		sDisp = m_pReelmap->GetTextConverse();
	else
		sDisp = m_pReelmap->GetTextArPcr();
	GetDlgItem(IDC_EDIT1)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT1)->SetWindowText(sDisp);

	sDisp = m_pReelmap->GetTextResult();
	GetDlgItem(IDC_EDIT2)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT2)->SetWindowText(sDisp);
}

void CMyItsDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_pReelmap)
		m_pReelmap->Load();
	m_bConverse = FALSE;
	Disp();
}


void CMyItsDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bConverse = TRUE;
	Disp();
}
