
// MyItsDlg.h : ��� ����
//

#pragma once
#include "SimpleReelmap.h"
#include "MyEdit.h"

#define PATH_ITS_INFO			_T("C:\\R2RSet\\ItsInfo.ini")
typedef struct tagItsInfo
{
	int nCase;
	CString sItsCode, sProcCode;
	CString sLayer[2]; // 0 : Up , 1 : Dn
	CString sLayerInner[2]; // 0 : Up , 1 : Dn
	CString sLayerOuter[2]; // 0 : Up , 1 : Dn

	tagItsInfo()
	{
		nCase = 0;
		sItsCode = _T(""); sProcCode = _T("");		
		sLayer[0] = _T(""); sLayer[1] = _T("");
		sLayerInner[0] = _T(""); sLayerInner[1] = _T("");
		sLayerOuter[0] = _T(""); sLayerOuter[1] = _T("");
	}
}stItsInfo;

// CMyItsDlg ��ȭ ����
class CMyItsDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap;
	BOOL m_bConverse;

	CMyEdit myEditIts, myEditSapp3;
	void InitEdit();

	int m_nIdxItsFile, m_nIdxSapp3File;

	void InitReelmap();
	void Disp(int nIdx);
	void DispReelmap();
	void DispReelmapResult();
	void DispIts();
	void DispItsResult();
	void DispSapp3();
	void DispSapp3Result();

	stItsInfo m_stItsInfo;
	BOOL LoadItsInfo();
	void OnEventItsOrgCase(int nCase);
	BOOL ConvertItsData(int nCase);

	void RefreshRadioBtn();
	BOOL MakeIts(int nSerial);
	
	// �����Դϴ�.
public:
	CMyItsDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CMyItsDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYITS_DIALOG };
#endif

public:
	void RedrawItsList();
	int GetItsOrgCase();

protected:
	afx_msg LRESULT wmClickEdit(WPARAM wParam, LPARAM lParam);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
