//pepthread.h
//by kiok ahn
//쓰레드를 사용하는 두가지 방법
//
// 1. ThreadProcess() 상속 함수를 구현 한다.
//      start()함수 호출 이후 setEvent()함수 호출 필요. 이벤트 응용 방법 이해가 필요.
//      unsigned int CALLBACK ThreadFunc(LPVOID lpvoid) 함수 참고.
//
// 2. typedef unsigned int (CALLBACK* LPTHREADFUNC)(LPVOID);형식의 함수를 구현 하여 start함수의 인자로 입력한다.
//   unsigned int CALLBACK MyThreadFunc(LPVOID lpvoid){ /*work*/ return 0;}
//   CPepThread th;
//   th.start( (LPVOID)this, MyThreadFunc );
#ifndef _PEP_THREAD_H_INCLUDE_
#define _PEP_THREAD_H_INCLUDE_

typedef unsigned int (CALLBACK* LPTHREADFUNC)(LPVOID);

class CPepThread
{
public:
	CPepThread();
	~CPepThread();

public:
	BOOL start   (LPVOID lpvoid, LPTHREADFUNC pfunc = NULL);
	void stop    (void);
	BOOL end     (void);
	BOOL pause   (void);
	BOOL resume  (void);
	BOOL isRun   (void){return m_bLoop;};

	void setEvent  (void);
	void resetEvent(void);

	//thread loop의 sleep time에 따라 변경
	void setEndThreadWaitTime( const UINT& nEndThreadWaitTime );

public:
	BOOL     getLoop   (void) const;
	HANDLE   getThread (void) const;
	HANDLE   getEvent  (void) const;

public:
	virtual void ThreadProcess      (LPVOID lpvoid){};
	virtual void ThreadProcessEnd   (void);
	virtual BOOL ThreadCheck        (void);//상속 받은 클래스는 이 Base 함수를 실행

protected:
	LPTHREADFUNC m_funcThread;
	HANDLE       m_hThread   ;
	HANDLE       m_hEvent    ;
	BOOL         m_bLoop     ;
	UINT         m_nEndThreadWaitTime;
	BOOL         m_bFinished ;
};

#endif //_PEP_THREAD_H_INCLUDE_
