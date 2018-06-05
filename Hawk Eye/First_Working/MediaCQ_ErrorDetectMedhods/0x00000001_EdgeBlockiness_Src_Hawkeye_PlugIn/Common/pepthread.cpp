//pepthread.cpp

#include "stdafx.h"

#include "tchar.h"
#include <process.h>
#include "pepthread.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib") 

#ifdef _LOGDATA
	#include "log.h"
#endif

unsigned int CALLBACK ThreadFunc(LPVOID lpvoid);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPepThread::CPepThread()
{
#ifdef PIPE_LOG
	LOGOUT(_T("CPepThread::CPepThread 0x%08x"), this );
#endif

	m_funcThread = (LPTHREADFUNC)&ThreadFunc;
	m_hThread    = NULL      ;
	m_hEvent     = NULL      ;
	m_bLoop      = FALSE     ;
	m_bFinished  = TRUE      ;
	m_nEndThreadWaitTime = 1000;//Default = 1 sec
}

CPepThread::~CPepThread()
{
	end();
}

BOOL CPepThread::start(LPVOID lpvoid, LPTHREADFUNC pfunc)
{
	if(m_bLoop) return FALSE;
	
	DWORD dwThreadId;

	if(pfunc) m_funcThread = pfunc;
	if( m_hThread ) end();
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
		LOGOUT(_T("CPepThread::start(), CreateEvent() error !"));
#endif		
		return FALSE;
	}

	m_hThread = (HANDLE)_beginthreadex(NULL ,0, m_funcThread, lpvoid, 0, (unsigned *)&dwThreadId);
	if(m_hThread==NULL)
	{
		m_bLoop = FALSE;
#ifdef _LOGDATA
		LOGOUT(_T("CPepThread::start(), _beginthreadex() error !"));
#endif
		return FALSE;
	}

//	SetThreadPriority(m_hThread,THREAD_PRIORITY_TIME_CRITICAL);
	return TRUE;
}

void CPepThread::setEndThreadWaitTime( const UINT& nEndThreadWaitTime )
{
	m_nEndThreadWaitTime = nEndThreadWaitTime;
}

void CPepThread::stop( void )
{ 
	m_bLoop=FALSE;
	setEvent();
}

BOOL CPepThread::end(void)
{
	if( m_hThread==NULL && m_hEvent==NULL ) 
		return TRUE;
	
	stop();

	if( !m_bFinished && WaitForSingleObject( m_hThread, m_nEndThreadWaitTime ) == WAIT_TIMEOUT )
		TerminateThread( m_hThread, 0 );

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

BOOL CPepThread::pause(void)
{
	DWORD dwRst = SuspendThread(m_hThread);
	return TRUE;
}

BOOL CPepThread::resume(void)
{
	DWORD dwRst = ResumeThread(m_hThread);
	return TRUE;
}

void CPepThread::setEvent(void)
{
	::SetEvent(m_hEvent);
}

void CPepThread::resetEvent(void)
{
	::ResetEvent(m_hEvent);
}

BOOL CPepThread::getLoop   (void) const
{
	return m_bLoop;
}

HANDLE CPepThread::getThread (void) const
{
	return m_hThread;
}

HANDLE CPepThread::getEvent  (void) const
{
	return m_hEvent;
}

void CPepThread::ThreadProcessEnd(void)
{
	m_bFinished = TRUE;
}

BOOL CPepThread::ThreadCheck(void)
{
	return TRUE;
}

unsigned int CALLBACK ThreadFunc(LPVOID lpvoid)
{
	CPepThread* pTh = (CPepThread*)lpvoid;
	DWORD	dwResult;	

	while( pTh->getLoop() && pTh->ThreadCheck() ) 
    { 
		dwResult = WaitForSingleObject (pTh->getEvent(), INFINITE);
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
//	CloseHandle(pTh->getEvent());
	pTh->ThreadProcessEnd();

	
	_endthreadex(0);
	return 0;
}

