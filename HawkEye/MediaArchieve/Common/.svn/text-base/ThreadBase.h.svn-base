//threadbase.h
//by kiok ahn
//쓰레드를 사용하는 두가지 방법
//
// 1. ThreadProcess() 상속 함수를 구현 한다.
//      start()함수 호출 이후 setEvent()함수 호출 필요. 이벤트 응용 방법 이해가 필요.
//      unsigned int CALLBACK ThreadFunc(LPVOID lpvoid) 함수 참고.
//
// 2. typedef unsigned int (CALLBACK* LPTHREADFUNC)(LPVOID);형식의 함수를 구현 하여 start함수의 인자로 입력한다.
//   unsigned int CALLBACK MyThreadFunc(LPVOID lpvoid){ /*work*/ return 0;}
//   CThreadBase th;
//   th.start( (LPVOID)this, MyThreadFunc );
#ifndef _THREAD_BASE_H_INCLUDE_
#define _THREAD_BASE_H_INCLUDE_

typedef unsigned int (CALLBACK* LPTHREADFUNC)(LPVOID);

class CThreadBase
{
public:
	CThreadBase();
	virtual ~CThreadBase();

public:
	BOOL Start     ( LPVOID lpvoid = NULL, LPTHREADFUNC pfunc = NULL );
	void Stop      ( void );
	BOOL End       ( void );
	BOOL Pause     ( void );
	BOOL Resume    ( void );
	BOOL IsRun     ( void ){return m_bLoop;};
	void SetEvent  ( void );
	void ResetEvent( void );

	//thread loop의 sleep time에 따라 변경
	void SetEndThreadWaitTime( const UINT& nEndThreadWaitTime );

public:
	BOOL     GetLoop   ( void ) const;
	HANDLE   GetThread ( void ) const;
	HANDLE   GetEvent  ( void ) const;

public:
	virtual void ThreadProcess      ( LPVOID lpvoid ){};
	virtual void ThreadPreProcessor ( void );
	virtual void ThreadPostProcessor( void );//상속 받은 클래스는 이 Base 함수를 실행
	virtual BOOL ThreadCheck        ( void );
	virtual void SetFinish          ( void ){m_bFinished=TRUE;};

protected:
	LPTHREADFUNC m_funcThread;
	HANDLE       m_hThread   ;
	HANDLE       m_hEvent    ;
	BOOL         m_bLoop     ;
	UINT         m_nEndThreadWaitTime;
	BOOL         m_bFinished ;


protected:
	static unsigned int CThreadBase::ThreadProc( LPVOID lpvoid );
};

#endif //_THREAD_BASE_H_INCLUDE_
