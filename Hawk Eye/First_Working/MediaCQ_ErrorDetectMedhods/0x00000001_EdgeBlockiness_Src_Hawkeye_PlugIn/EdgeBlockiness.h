// EdgeBlock.h : EdgeBlock DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CEdgeBlockApp
// �� Ŭ������ ������ ������ EdgeBlock.cpp�� �����Ͻʽÿ�.
//

class CEdgeBlockApp : public CWinApp
{
public:
	CEdgeBlockApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
