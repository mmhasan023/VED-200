#include "stdafx.h"
#include "TTypeDefine.h"
#include "DetecBlackFrame.h"
#include "BlackFrameExport.h"

#ifdef _LOGDATA	
	#include <time.h>
	extern void init_log(void);
	extern void LOGMSG(TCHAR *szMsg, ... );
#endif

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif

HANDLE WINAPI MCQA_BlackFrameOpen( void )
{
#ifdef _LOGDATA
	init_log();
	CTime time = CTime::GetCurrentTime();
	CString szMsg;
	szMsg.Format(_T("\r\nMCQA_BlackFrameOpen start................... %d. %d. %d\r\n"), time.GetHour(), time.GetMinute(), time.GetSecond() );
	LOGMSG((LPTSTR)(LPCTSTR)szMsg);
#endif

	CDetectionBlackFrame* pAMute = new CDetectionBlackFrame;
	return (HANDLE)pAMute;
}

HRESULT WINAPI MCQA_BlackFrameClose( HANDLE hHandle )
{
	if(hHandle==NULL) return E_FAIL;
#ifdef _LOGDATA
	CTime time = CTime::GetCurrentTime();
	CString szMsg;
	szMsg.Format(_T("MCQA_BlackFrameClose end................... %d. %d. %d\r\n\r\n"), time.GetHour(), time.GetMinute(), time.GetSecond() );
	LOGMSG((LPTSTR)(LPCTSTR)szMsg);
#endif


	CDetectionBlackFrame* pAMute = (CDetectionBlackFrame*)hHandle;
	delete pAMute;
	pAMute=NULL;

#ifdef _DEBUG
	mem_trace_dump();
#endif
	return S_OK;
}

HRESULT WINAPI MCQA_BlackFrameSetCallback( HANDLE hHandle, LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	if(hHandle==NULL) return E_FAIL;

	CDetectionBlackFrame* pAMute = (CDetectionBlackFrame*)hHandle;
	pAMute->SetCallback( lpCallback, lpUserData );
	return S_OK;
}

HRESULT WINAPI MCQA_BlackFrame( HANDLE hHandle, LPAVDATA lpAVData )
{
	if(hHandle==NULL) return E_FAIL;

	CDetectionBlackFrame* pAMute = (CDetectionBlackFrame*)hHandle;
	return pAMute->CheckStream(lpAVData);
}

HRESULT WINAPI MCQA_BlackFrameFinishedStream( HANDLE hHandle )
{
	CDetectionBlackFrame* pBlackFrame = (CDetectionBlackFrame*)hHandle;
	return pBlackFrame->FinishedStream();
}

HRESULT WINAPI MCQA_BlackFrameSetOption( HANDLE hHandle, LPSTR_MAP lpmapOption )
{
	CDetectionBlackFrame* pBlackFrame = (CDetectionBlackFrame*)hHandle;
	return pBlackFrame->SetOption(lpmapOption);
}