// TestMediaAngel.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.



// CTestMediaAngelApp:
// �� Ŭ������ ������ ���ؼ��� TestMediaAngel.cpp�� �����Ͻʽÿ�.
//


class CTestMediaAngelApp : public CWinApp
{
public:
	CTestMediaAngelApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestMediaAngelApp theApp;