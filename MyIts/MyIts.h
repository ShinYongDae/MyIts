
// MyIts.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

#define WM_EDIT_CLICK				(WM_USER+0)

// CMyItsApp:
// �� Ŭ������ ������ ���ؼ��� MyIts.cpp�� �����Ͻʽÿ�.
//

class CMyItsApp : public CWinApp
{
public:
	CMyItsApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMyItsApp theApp;