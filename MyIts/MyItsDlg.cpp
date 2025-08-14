
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
	m_nIdxItsFile = -1;
	m_nIdxSapp3File = -1;
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
	ON_BN_CLICKED(IDC_BUTTON4, &CMyItsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyItsDlg::OnBnClickedButton5)
	ON_MESSAGE(WM_EDIT_CLICK, wmClickEdit)
	ON_WM_LBUTTONDOWN()
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
	InitEdit();
	InitReelmap();

	DispIts();
	DispSapp3();

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

void CMyItsDlg::InitEdit()
{
	myEditIts.SubclassDlgItem(IDC_EDIT4, this);
	myEditIts.SetHwnd(this->GetSafeHwnd(), IDC_EDIT4);
	myEditIts.SetFontName(_T("Arial"));
	myEditIts.SetFontSize(12);
	myEditIts.SetFontBold(FALSE);
	myEditIts.SetTextColor(RGB_BLACK);
	myEditIts.SetBkColor(RGB_WHITE);
	myEditIts.SetText(_T(""));
	myEditIts.SetFont((CFont*)&myEditIts.m_font, TRUE);

	myEditSapp3.SubclassDlgItem(IDC_EDIT5, this);
	myEditSapp3.SetHwnd(this->GetSafeHwnd(), IDC_EDIT5);
	myEditSapp3.SetFontName(_T("Arial"));
	myEditSapp3.SetFontSize(12);
	myEditSapp3.SetFontBold(FALSE);
	myEditSapp3.SetTextColor(RGB_BLACK);
	myEditSapp3.SetBkColor(RGB_WHITE);
	myEditSapp3.SetText(_T(""));
	myEditSapp3.SetFont((CFont*)&myEditSapp3.m_font, TRUE);
}

void CMyItsDlg::InitReelmap()
{
	CString sPathInfo = _T("C:\\R2RSet\\Info0.bin");
	CString sPathRmap = _T("C:\\R2RSet\\Reelmap0.bin");
	CString sPathYield = _T("C:\\R2RSet\\Yield0.bin");
	CString sPathMark = _T("C:\\R2RSet\\Mark0.bin");
	m_pReelmap = new CSimpleReelmap(RMapUp, sPathInfo, sPathRmap, sPathYield, sPathMark, this);

	stRmapInfo stInfo;
	stInfo.m_sMcName = _T("BAO14");
	stInfo.m_sUserName = _T("BAO14");
	stInfo.m_sModel = _T("L231115S31");
	stInfo.m_sLot = _T("200125279");
	stInfo.m_sLayer = _T("TOP-3-050");
	stInfo.m_sLayerUp = _T("TOP-3-050");
	stInfo.m_sLayerDn = _T("BOTTOM-4-050");
	stInfo.m_sItsCode = _T("200125279");
	stInfo.m_sProcessCode = _T("VS90");
	stInfo.m_nActionCode = 3;
	stInfo.m_nMaxRow = 20;
	stInfo.m_nMaxCol = 30;
	stInfo.m_nMaxStrip = 4;
	stInfo.m_nMaxDefCode = 30;
	m_pReelmap->Init(stInfo);
}

void CMyItsDlg::Disp(int nIdx)
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	if (nIdx == 0)
	{
		DispReelmap();
		DispReelmapResult();
	}
	else if (nIdx == 1)
	{
		DispIts();
	}
	else if (nIdx == 2)
	{
		DispSapp3();
	}
}

void CMyItsDlg::DispReelmap()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	if (m_bConverse)
		sDisp = m_pReelmap->GetTextConverse();
	else
		sDisp = m_pReelmap->GetTextArPcr();

	GetDlgItem(IDC_EDIT1)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT1)->SetWindowText(sDisp);

}

void CMyItsDlg::DispReelmapResult()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	sDisp = m_pReelmap->GetTextResult();

	GetDlgItem(IDC_EDIT2)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT2)->SetWindowText(sDisp);
}

void CMyItsDlg::DispIts()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	sDisp = m_pReelmap->GetTextListItsFile();

	GetDlgItem(IDC_EDIT4)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT4)->SetWindowText(sDisp);
}

void CMyItsDlg::DispItsResult()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	sDisp = m_pReelmap->GetTextItsFile(m_nIdxItsFile);

	GetDlgItem(IDC_EDIT2)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT2)->SetWindowText(sDisp);
}

void CMyItsDlg::DispSapp3()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	sDisp = m_pReelmap->GetTextListSapp3File();

	GetDlgItem(IDC_EDIT5)->GetWindowText(sCurr);
	if (sCurr != sDisp)
		GetDlgItem(IDC_EDIT5)->SetWindowText(sDisp);
}

void CMyItsDlg::DispSapp3Result()
{
	if (!m_pReelmap) return;

	CString sCurr = _T("");
	CString sDisp = _T("");

	sDisp = m_pReelmap->GetTextSapp3File(m_nIdxSapp3File);

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
	Disp(0);
}


void CMyItsDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bConverse = TRUE;
	Disp(0); // Reelmap
}


void CMyItsDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nSerial = 0;
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	nSerial = _tstoi(str);
	if (m_pReelmap)
	{
		m_pReelmap->MakeIts(nSerial);
		Disp(1); // ITS
	}
}


void CMyItsDlg::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_pReelmap)
	{
		m_pReelmap->MakeSapp3();
		Disp(2); // LOSS
	}
}


LRESULT CMyItsDlg::wmClickEdit(WPARAM wParam, LPARAM lParam)
{
	int nId = (int)wParam;
	if(!lParam) return (LRESULT)0L;
	CEdit* pControl = (CEdit*)GetDlgItem(nId);

	//CPoint point;
	//point.y = HIWORD(lParam);
	//point.x = LOWORD(lParam);
	//CPoint ptClient = point;
	//int nCharIndex = pControl->CharFromPos(ptClient);

	int nLineIndex = pControl->LineFromChar(-1); // ���� ĳ���� �ִ� ���ι�ȣ�� ��ȯ
	CString sData;
	if (nId == IDC_EDIT4)
		sData = m_pReelmap->GetTextListItsFile();
	else if (nId == IDC_EDIT5)
		sData = m_pReelmap->GetTextListSapp3File();
	else
		return 0L;

	CString sLine;
	int nPos, nLine = 0;
	int nCharSt = 0, nCharEd = 0;
	int nSize = sData.GetLength();
	while (nSize > 0)
	{
		nPos = sData.Find('\n', 0);
		sLine = sData.Left(nPos);
		sData.Delete(0, nPos + 1);
		nSize = nSize - nPos - 1;
		nCharEd = nCharSt + nPos - 1;
		if (nLine == nLineIndex)
		{
			if (nId == IDC_EDIT4)
			{
				m_nIdxItsFile = nLine;
				DispItsResult();
			}
			else if (nId == IDC_EDIT5)
			{
				m_nIdxSapp3File = nLine;
				DispSapp3Result();
			}
			pControl->SetSel(nCharSt, nCharEd);
			break;
		}
		nCharSt += nPos + 1;
		nLine++;
	}

	return (LRESULT)0L;
}


//void CMyItsDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	CEdit* pControl = (CEdit*)GetDlgItem(IDC_EDIT4);
//	//CRect rectEdit;
//	//pControl->GetWindowRect(&rectEdit);
//	//ScreenToClient(&rectEdit);
//	//CPoint ptClient = point;
//	//ptClient.Offset(-rectEdit.left, -rectEdit.top); // x, y�� ������ ���� ���ϴ� ����
//	CPoint ptClient = point;
//	int nCharIndex = pControl->CharFromPos(ptClient);
//	int nLineIndex = pControl->LineFromChar(nCharIndex);
//
//	CDialog::OnLButtonDown(nFlags, point);
//}
