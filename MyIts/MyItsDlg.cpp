
// MyItsDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyIts.h"
#include "MyItsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyItsDlg ��ȭ ����



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


// CMyItsDlg �޽��� ó����

BOOL CMyItsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	InitReelmap();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyItsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_pReelmap)
		m_pReelmap->Load();
	m_bConverse = FALSE;
	Disp();
}


void CMyItsDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bConverse = TRUE;
	Disp();
}
