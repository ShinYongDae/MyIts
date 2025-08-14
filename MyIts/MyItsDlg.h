
// MyItsDlg.h : ��� ����
//

#pragma once
#include "SimpleReelmap.h"
#include "MyEdit.h"


// CMyItsDlg ��ȭ ����
class CMyItsDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap;
	BOOL m_bConverse;

	CMyEdit myEdit;
	void InitEdit();

	int m_nIdxItsFile;
	
	void InitReelmap();
	void Disp(int nIdx);
	void DispReelmap();
	void DispReelmapResult();
	void DispIts();
	void DispItsResult();
	void DispSapp3();
	void DispSapp3Result();

// �����Դϴ�.
public:
	CMyItsDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CMyItsDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYITS_DIALOG };
#endif

public:

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
};
