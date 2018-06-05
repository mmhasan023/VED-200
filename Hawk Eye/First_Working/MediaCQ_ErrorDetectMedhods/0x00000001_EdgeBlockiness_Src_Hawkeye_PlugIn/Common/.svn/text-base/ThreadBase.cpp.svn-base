//threadbase.cpp

#include "stdafx.h"

#include "tchar.h"
#include <process.h>
#include "threadbase.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib") 

#ifdef _LOGDATA
	#include "log.h"
#endif

unsigned int CALLBACK ThreadFunc(LPVOID lpvoid);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CThreadBase::CThreadBase()
{
#ifdef PIPE_LOG
	LOGOUT(_T("CThreadBase::CThreadBase 0x%08x"), this );
#endif

	m_funcThread = (LPTHREADFUNC)&CThreadBase::ThreadProc;
	m_hThread    = NULL      ;
	m_hEvent     = NULL      ;
	m_bLoop      = FALSE     ;
	m_bFinished  = TRUE      ;
	m_nEndThreadWaitTime = 1000;//Default = 1 sec
}

CThreadBase::~CThreadBase()
{
	End();
}

BOOL CThreadBase::Start(LPVOID lpvoid, LPTHREADFUNC pfunc)
{
	if(m_bLoop) return FALSE;
	
	DWORD dwThreadId = 0;

	if( pfunc     ) m_funcThread = pfunc;
	if( m_hThread ) End();
	m_bLoop = TRUE;
	m_bFinished = FALSE;
	
	DWORD dwTime = timeGetTime();
	TCHAR szName[MAX_PATH]={0};
	_stprintf( szName, _T("_T_Name_0x%08x"), dwTime );

	m_hEvent  = CreateEvent (NULL, TRUE, FALSE, szName/*_T("")*/);
	
	if(m_hEvent==NULL)
	{	
		m_bLoop = FALSE;
#ifdef _LOGDATA
		LOGOUT(_T("CThreadBase::start(), CreateEvent() error !"));
#endif		
		return FALSE;
	}

	LPVOID lpUserData = (LPVOID)this;
	if( lpvoid ) lpUserData = lpvoid;

	m_hThread = (HANDLE)_beginthreadex(NULL ,0, m_funcThread, lpUserData, 0, (unsigned *)&dwThreadId);
	if(m_hThread==NULL)
	{
		m_bLoop = FALSE;
#ifdef _LOGDATA
		LOGOUT(_T("CThreadBase::start(), _beginthreadex() error !"));
#endif
		return FALSE;
	}

//	SetThreadPriority(m_hThread,THREAD_PRIORITY_TIME_CRITICAL);
	return TRUE;
}

void CThreadBase::Stop( void )
{ 
	m_bLoop=FALSE;
	SetEvent();
}

void CThreadBase::SetEndThreadWaitTime( const UINT& nEndThreadWaitTime )
{
	m_nEndThreadWaitTime = nEndThreadWaitTime;
}

BOOL CThreadBase::End(void)
{
	if( m_hThread==NULL && m_hEvent==NULL ) 
		return TRUE;
	
	Stop();

	if( !m_bFinished && WaitForSingleObject( m_hThread, m_nEndThreadWaitTime ) == WAIT_TIMEOUT )
		TerminateThread(m_hThread,0);

	if( m_hThread )
	{
		CloseHandle( m_hThread );
		m_hThread = NULL;
	}
	if( m_hEvent )
	{
		CloseHandle( m_hEvent  );
		m_hEvent  = NULL;
	}

	m_bFinished = TRUE;

	return TRUE;
}

BOOL CThreadBase::Pause(void)
{
	DWORD dwRst = SuspendThread( m_hThread );
	return TRUE;
}

BOOL CThreadBase::Resume(void)
{
	DWORD dwRst = ResumeThread( m_hThread );
	return TRUE;
}

void CThreadBase::SetEvent(void)
{
	::SetEvent( m_hEvent );
}

void CThreadBase::ResetEvent(void)
{
	::ResetEvent( m_hEvent );
}

BOOL CThreadBase::GetLoop   (void) const
{
	return m_bLoop;
}

HANDLE CThreadBase::GetThread (void) const
{
	return m_hThread;
}

HANDLE CThreadBase::GetEvent  (void) const
{
	return m_hEvent;
}

void CThreadBase::ThreadPreProcessor(void)
{//empty function
}

void CThreadBase::ThreadPostProcessor(void)
{
	m_bFinished = TRUE;
}

BOOL CThreadBase::ThreadCheck(void)
{
	return TRUE;
}

unsigned int CThreadBase::ThreadProc( LPVOID lpvoid )
{
	CThreadBase* pTh = (CThreadBase*)lpvoid;
	DWORD	dwResult = 0;	
	pTh->ThreadPreProcessor();

	while( pTh->GetLoop() && pTh->ThreadCheck() ) 
    { 
		dwResult = WaitForSingleObject (pTh->GetEvent(), INFINITE);
		switch (dwResult) 
		{
		case WAIT_OBJECT_0:
			pTh->ThreadProcess(lpvoid);
			break;
		case WAIT_TIMEOUT :
			break;
		default:
			break;
		}
	}

	pTh->ThreadPostProcessor();

	_endthreadex(0);
	return 0;
}

