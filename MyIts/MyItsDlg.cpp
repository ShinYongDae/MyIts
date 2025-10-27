
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
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDC_RADIO1, &CMyItsDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMyItsDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMyItsDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMyItsDlg::OnBnClickedRadio4)
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
	LoadItsInfo();

	InitEdit();
	InitReelmap();

	DispIts();
	DispSapp3();

	RefreshRadioBtn();
	//this->SetFocus();
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
	myEditIts.SetReadOnly(TRUE);

	myEditSapp3.SubclassDlgItem(IDC_EDIT5, this);
	myEditSapp3.SetHwnd(this->GetSafeHwnd(), IDC_EDIT5);
	myEditSapp3.SetFontName(_T("Arial"));
	myEditSapp3.SetFontSize(12);
	myEditSapp3.SetFontBold(FALSE);
	myEditSapp3.SetTextColor(RGB_BLACK);
	myEditSapp3.SetBkColor(RGB_WHITE);
	myEditSapp3.SetText(_T(""));
	myEditSapp3.SetFont((CFont*)&myEditSapp3.m_font, TRUE);
	myEditSapp3.SetReadOnly(TRUE);
}

void CMyItsDlg::InitReelmap()
{
	CString sPathInfo = _T("C:\\R2RSet\\Info0.bin");
	CString sPathRmap = _T("C:\\R2RSet\\Reelmap0.bin");
	CString sPathYield = _T("C:\\R2RSet\\Yield0.bin");
	CString sPathMark = _T("C:\\R2RSet\\Mark0.bin");
	m_pReelmap = new CSimpleReelmap(RMapUp, sPathInfo, sPathRmap, sPathYield, sPathMark, this);
	m_pReelmap->SetItsOrgCase(GetItsOrgCase());

	stRmapInfo stInfo;
	//stInfo.m_sMcName = _T("BAO14");
	//stInfo.m_sUserName = _T("������");
	//stInfo.m_sModel = _T("L231115S31");
	//stInfo.m_sLot = _T("200125279");
	//stInfo.m_sLayer = _T("TOP-3-050");
	//stInfo.m_sLayerUp = _T("TOP-3-050");
	//stInfo.m_sLayerDn = _T("BOTTOM-4-050");
	//stInfo.m_sItsCode = _T("200125279");
	//stInfo.m_sProcessCode = _T("VS90");

	stInfo.m_sMcName = _T("BAO14");
	stInfo.m_sUserName = _T("����");
	stInfo.m_sModel = _T("B1313F2ST1");
	stInfo.m_sLot = _T("200180747");
	stInfo.m_sLayer = _T("TOP-0-050");
	stInfo.m_sLayerUp = _T("TOP-0-050");
	stInfo.m_sLayerDn = _T("BOTTOM-0-050");
	stInfo.m_sItsCode = _T("200180747");
	stInfo.m_sProcessCode = _T("AO9L");

	stInfo.m_nActionCode = 3;
	stInfo.m_nMaxRow = 20;
	stInfo.m_nMaxCol = 30;
	stInfo.m_nMaxStrip = 4;
	stInfo.m_nMaxDefCode = 30;
	m_pReelmap->Init(stInfo);
}

void CMyItsDlg::RefreshRadioBtn()
{
	int nCase = GetItsOrgCase();
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(nCase == 0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(nCase == 1);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(nCase == 2);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(nCase == 3);
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
	GetDlgItem(IDC_EDIT3)->GetWindowText(str); // Serial
	nSerial = _tstoi(str);
	MakeIts(nSerial);
}

BOOL CMyItsDlg::MakeIts(int nSerial)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nSerial > 0)
	{
		if (m_pReelmap)
		{
			if (m_pReelmap->MakeIts(nSerial))
				Disp(1); // ITS
			else
			{
				AfxMessageBox(_T("Failed Make Its File!!!"));
				return FALSE;;
			}
		}
	}
	else
	{
		AfxMessageBox(_T("Serial is smaller than 1."));
		return FALSE;
	}

	return TRUE;
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

	int nLineIndex_Its = pControl->LineFromChar(-1); // ���� ĳ���� �ִ� ���ι�ȣ�� ��ȯ
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
		if (nLine == nLineIndex_Its)
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
			pControl->RedrawWindow();
			break;
		}
		nCharSt += nPos + 1;
		nLine++;
	}

	return (LRESULT)0L;
}

void CMyItsDlg::RedrawItsList()
{
	CEdit* pControl = (CEdit*)GetDlgItem(IDC_EDIT4);
	pControl->SetSel(0, 0);
	CString sData = m_pReelmap->GetTextListItsFile();

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
		if (nLine == m_nIdxItsFile)
		{
			pControl->SetSel(nCharSt, nCharEd);
			pControl->RedrawWindow();
			break;
		}
		nCharSt += nPos + 1;
		nLine++;
	}
}

void CMyItsDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_nIdxItsFile > -1)
	{
		RedrawItsList();
	}
}


void CMyItsDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	//if (m_nIdxItsFile > -1)
	//{
	//	RedrawItsList();
	//}

	//if (pOldWnd->GetSafeHwnd())
	//	pOldWnd->SetFocus();
}

BOOL CMyItsDlg::LoadItsInfo()
{
	TCHAR szData[MAX_PATH];
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("DataOrigin"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.nCase = _ttoi(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("ItsCode"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sItsCode = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("ProcessUnitCode"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sProcCode = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("LayerUp"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sLayer[0] = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("LayerDn"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sLayer[1] = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("InnerLayerUp"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sLayerInner[0] = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("InnerLayerDn"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sLayerInner[1] = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("OuterLayerUp"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sLayerOuter[0] = CString(szData);
	if (0 < ::GetPrivateProfileString(_T("Info"), _T("OuterLayerDn"), NULL, szData, sizeof(szData), PATH_ITS_INFO))
		m_stItsInfo.sLayerOuter[1] = CString(szData);

	return TRUE;
}

int CMyItsDlg::GetItsOrgCase()
{
	LoadItsInfo();
	return m_stItsInfo.nCase;
}

void CMyItsDlg::OnEventItsOrgCase(int nCase)
{
	if (ConvertItsData(nCase))
	{
		CString sVal;
		sVal.Format(_T("%d"), nCase);
		::WritePrivateProfileString(_T("Info"), _T("DataOrigin"), sVal, PATH_ITS_INFO);

		CString sDate;
		sDate.Format(_T("%s: "), COleDateTime::GetCurrentTime().Format(_T("%Y/%m/%d %H:%M:%S")));
		::WritePrivateProfileString(_T("History"), sDate, sVal, PATH_ITS_INFO);
	}
}

BOOL CMyItsDlg::ConvertItsData(int nCase)
{
	if (IDNO == AfxMessageBox(_T("ITS Data�� ������ �����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION))
	{
		RefreshRadioBtn();
		return FALSE;
	}
	m_pReelmap->SetItsOrgCase(nCase);

	int nSerial = 0;
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str); // Serial
	nSerial = _tstoi(str);

	if(!MakeIts(nSerial))
	{
		RefreshRadioBtn();
		return FALSE;
	}

	return TRUE;
}

void CMyItsDlg::OnBnClickedRadio1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnEventItsOrgCase(0);
}


void CMyItsDlg::OnBnClickedRadio2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnEventItsOrgCase(1);
}


void CMyItsDlg::OnBnClickedRadio3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnEventItsOrgCase(2);
}


void CMyItsDlg::OnBnClickedRadio4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnEventItsOrgCase(3);
}
