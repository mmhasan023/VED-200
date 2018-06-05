// SpyShell.h: interface for the CSpyShell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPYSHELL_H__0066CF05_0CF2_4684_BDCE_C5A7F117A4FE__INCLUDED_)
#define AFX_SPYSHELL_H__0066CF05_0CF2_4684_BDCE_C5A7F117A4FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ReadDirectoryChangesW 함수가 NT이상에서만 동작하므로 
// stdafx.h 헤더파일에 다음과 같이 선언해 준다.
// #define _WIN32_WINNT 0x400
// 
class CSpyShell  
{
protected:
	BOOL   m_bFindRecursive;
	HANDLE m_hDir;
	HANDLE m_hThread;
	BOOL  m_bStopThread;
	UINT  m_nFilter;
	CString m_strRootDir;
	static unsigned __stdcall  ThreadFuntion( void* arg );
public:
	CWnd* m_pTargetWnd;
	UINT  m_nMsg;
	void Stop();
	BOOL Start();
	void SetData(CWnd* pMsgTarget, 
				 UINT nMsg, 
				 LPCTSTR lpszRootDir, 
				 UINT nFilter,
				 BOOL bFindRecursive = TRUE);
	CSpyShell();
	virtual ~CSpyShell();

};

#endif // !defined(AFX_SPYSHELL_H__0066CF05_0CF2_4684_BDCE_C5A7F117A4FE__INCLUDED_)
