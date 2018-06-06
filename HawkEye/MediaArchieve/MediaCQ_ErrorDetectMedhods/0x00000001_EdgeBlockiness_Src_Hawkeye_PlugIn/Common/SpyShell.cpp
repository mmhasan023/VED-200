// SpyShell.cpp: implementation of the CSpyShell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpyShell.h"

#ifdef _LOGDATA
	#include "logwnd.h"
#endif

#include <AFXPRIV.H>
#include <process.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpyShell::CSpyShell()
{
	m_pTargetWnd = NULL;
	m_nMsg = NULL;
	m_bStopThread = TRUE;
	m_hDir = NULL;
	m_hThread = NULL;
}

CSpyShell::~CSpyShell()
{
//	Stop();
}

// pMsgTarget : 변경이 발생했을 경우 메세지를 받을 윈도우
// nMsg : 변경이 발생했을 경우 보낼 메세지 아이디
// lpszRootDir : 감시해야 할 대상 디렉토리 경로
// bFindRecursive : 하위 디렉토리까지 감시할지의 여부
void CSpyShell::SetData(CWnd *pMsgTarget, UINT nMsg, LPCTSTR lpszRootDir, UINT nFilter, BOOL bFindRecursive)
{
	m_bFindRecursive = bFindRecursive;
	m_pTargetWnd = pMsgTarget;
	m_nMsg = nMsg;
	m_strRootDir = lpszRootDir;
	m_nFilter = nFilter;
}

BOOL CSpyShell::Start()
{
	if (!m_bStopThread)
	{
		Stop();
	}

	m_bStopThread = FALSE;
	unsigned threadID;
	m_hThread = (HANDLE)_beginthreadex( NULL, 0, &ThreadFuntion, (void*) this, 0, &threadID);

	return TRUE;
}

void CSpyShell::Stop()
{
	if (m_hThread)
	{
		m_bStopThread = TRUE;	
		WaitForSingleObject( m_hThread, 1000 );

		DWORD dwExitCode;
		GetExitCodeThread(m_hThread, &dwExitCode);
		TerminateThread(m_hThread, dwExitCode);
		CloseHandle( m_hThread );
		if(m_hDir)
		{
			CloseHandle( m_hDir );	
			m_hDir = NULL;
		}
	}
}

unsigned __stdcall CSpyShell::ThreadFuntion( void* arg )
{
	CSpyShell* pShell = (CSpyShell*)arg;

	if(pShell->m_hDir)
	{
		CloseHandle(pShell->m_hDir);
		pShell->m_hDir = NULL;
	}
	pShell->m_hDir = CreateFile( pShell->m_strRootDir, // pointer to the file name
								FILE_LIST_DIRECTORY,                // access (read/write) mode
								FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE,  // share mode
								NULL,                               // security descriptor
								OPEN_EXISTING,                      // how to create
								FILE_FLAG_BACKUP_SEMANTICS,         // file attributes
								NULL                                // file with attributes to copy
								);

	FILE_NOTIFY_INFORMATION Buffer[4096];
	DWORD BytesReturned;
	while( ReadDirectoryChangesW(
								pShell->m_hDir,                                  // handle to directory
								&Buffer,                                    // read results buffer
								sizeof(Buffer),                                // length of buffer
								pShell->m_bFindRecursive,                                 // monitoring option
								pShell->m_nFilter,              // filter conditions
								&BytesReturned,              // bytes returned
								NULL,                          // overlapped buffer
								NULL// completion routine
								))
	{
		if (pShell->m_bStopThread) 
			break;

		CString strPath;
		int i=0;
		do
//		while ( Buffer[i].NextEntryOffset == NULL )
		{
			strPath = pShell->m_strRootDir;
			strPath.TrimRight(_T('\\'));

			WCHAR wszPath[MAX_PATH * 2];
			memset(wszPath, 0, MAX_PATH * 2);
			memcpy(wszPath, Buffer[i].FileName, Buffer[i].FileNameLength);

			int nSize = WideCharToMultiByte (CP_OEMCP, NULL, wszPath, -1,
				NULL, 0, NULL, NULL);
			
			TCHAR* pS = new TCHAR[nSize+1];
			memset(pS,0,sizeof(TCHAR)*(nSize+1));
#ifdef _UNICODE
			_tcscpy(pS,wszPath);
#else
			WideCharToMultiByte (CP_OEMCP, NULL, wszPath, -1,
				pS, nSize, NULL, NULL);

#endif
			strPath += _T('\\');
			strPath += pS;
			delete[] pS;

//			TCHAR szSendPath[MAX_PATH]={0};
//			_tcscpy(szSendPath,strPath);

			pShell->m_pTargetWnd->SendMessage(pShell->m_nMsg, (WPARAM)Buffer[0].Action, (LPARAM)(LPCTSTR)strPath);
			i++;
			Sleep(10);
			if (pShell->m_bStopThread) 
			{
				CloseHandle(pShell->m_hDir);
				CloseHandle(pShell->m_hThread);
				pShell->m_hThread = NULL;
				pShell->m_hDir = NULL;
				return 0;
			}
		}
		while (!Buffer[i].NextEntryOffset);

//		pShell->m_pTargetWnd->SendMessage(pShell->m_nMsg, (WPARAM)Buffer[0].Action, (LPARAM)(LPCTSTR)strPath);
	}

	CloseHandle(pShell->m_hDir);
	CloseHandle(pShell->m_hThread);
	pShell->m_hThread = NULL;
	pShell->m_hDir = NULL;

	return 0;
}