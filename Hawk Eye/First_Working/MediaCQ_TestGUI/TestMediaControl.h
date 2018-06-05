#include "TestMediaAngelDlg.h"
#include "afxmt.h"
#pragma once

class CTestMediaControl
{
public:
	CTestMediaControl( const CWnd* pParent = NULL);
	~CTestMediaControl(void);

public:
	BOOL                m_bProFlag;
	CTestMediaAngelDlg* m_pMainDlg;
	BOOL				m_bFinishFlag;

	CCriticalSection    m_csProgress;

public:
	void ReSetMain       (HANDLE nCQHandle);
	void ProcFinish      (HANDLE nCQHandle);
	void SetProgressPos  ( const int& nCurProgress, HANDLE nCQHandle);
	void SetTotalProgress();
};
