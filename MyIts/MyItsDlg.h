
// MyItsDlg.h : ��� ����
//

#pragma once
#include "SimpleReelmap.h"


// CMyItsDlg ��ȭ ����
class CMyItsDlg : public CDialog
{
	CSimpleReelmap* m_pReelmap;
	BOOL m_bConverse;
	
	void InitReelmap();
	void Disp();

// �����Դϴ�.
public:
	CMyItsDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CMyItsDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYITS_DIALOG };
#endif

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
};
