
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


// CMyItsDlg 메시지 처리기

BOOL CMyItsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	LoadItsInfo();

	InitEdit();
	InitReelmap();

	DispIts();
	DispSapp3();

	RefreshRadioBtn();
	//this->SetFocus();
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
	//stInfo.m_sUserName = _T("서봉율");
	//stInfo.m_sModel = _T("L231115S31");
	//stInfo.m_sLot = _T("200125279");
	//stInfo.m_sLayer = _T("TOP-3-050");
	//stInfo.m_sLayerUp = _T("TOP-3-050");
	//stInfo.m_sLayerDn = _T("BOTTOM-4-050");
	//stInfo.m_sItsCode = _T("200125279");
	//stInfo.m_sProcessCode = _T("VS90");

	stInfo.m_sMcName = _T("BAO14");
	stInfo.m_sUserName = _T("고도욱");
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_pReelmap)
		m_pReelmap->Load();
	m_bConverse = FALSE;
	Disp(0);
}


void CMyItsDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bConverse = TRUE;
	Disp(0); // Reelmap
}


void CMyItsDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSerial = 0;
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str); // Serial
	nSerial = _tstoi(str);
	MakeIts(nSerial);
}

BOOL CMyItsDlg::MakeIts(int nSerial)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	int nLineIndex_Its = pControl->LineFromChar(-1); // 현재 캐럿이 있는 라인번호를 반환
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_nIdxItsFile > -1)
	{
		RedrawItsList();
	}
}


void CMyItsDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
	if (IDNO == AfxMessageBox(_T("ITS Data의 원점을 변경하시겠습니까?"), MB_YESNO | MB_ICONQUESTION))
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnEventItsOrgCase(0);
}


void CMyItsDlg::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnEventItsOrgCase(1);
}


void CMyItsDlg::OnBnClickedRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnEventItsOrgCase(2);
}


void CMyItsDlg::OnBnClickedRadio4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnEventItsOrgCase(3);
}
