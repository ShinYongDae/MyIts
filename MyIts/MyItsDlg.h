
// MyItsDlg.h : 헤더 파일
//

#pragma once
#include "SimpleReelmap.h"
#include "MyEdit.h"


// CMyItsDlg 대화 상자
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

// 생성입니다.
public:
	CMyItsDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CMyItsDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYITS_DIALOG };
#endif

public:

protected:
	afx_msg LRESULT wmClickEdit(WPARAM wParam, LPARAM lParam);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
