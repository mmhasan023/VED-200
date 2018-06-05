#include "stdafx.h"
#include "TTypeDefine.h"
#include "iplAPI.h"
#include "DetectEdgeBlockiness.h"
#include "EdgeBlockinessExport.h"

#ifdef _LOGDATA
#include "log.h"
#endif

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif

HANDLE WINAPI MCQA_EdgeBlockOpen( void )
{
#ifdef _LOGDATA
	SET_SUBFOLDER( _T("CQ_API\\EdgeBlockiness") );
#endif

	CDetectionEdgeBlockiness* pEdgeBlock = new CDetectionEdgeBlockiness;
	return (HANDLE)pEdgeBlock;
}

HRESULT WINAPI MCQA_EdgeBlockClose( HANDLE hHandle )
{
	CDetectionEdgeBlockiness* ppEdgeBlock = (CDetectionEdgeBlockiness*)hHandle;
	delete ppEdgeBlock;
	ppEdgeBlock=NULL;
#ifdef _DEBUG
	mem_trace_dump();
#endif

	return S_OK;
}

HRESULT WINAPI MCQA_EdgeBlockSetCallback( HANDLE hHandle, LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	CDetectionEdgeBlockiness* pEdgeBlock = (CDetectionEdgeBlockiness*)hHandle;
	pEdgeBlock->SetCallback( lpCallback, lpUserData );
	return S_OK;
}

HRESULT WINAPI MCQA_EdgeBlock( HANDLE hHandle, LPAVDATA lpAVData )
{
	CDetectionEdgeBlockiness* pEdgeBlock = (CDetectionEdgeBlockiness*)hHandle;
	return pEdgeBlock->CheckStream(lpAVData);
}

HRESULT WINAPI MCQA_EdgeBlockFinishedStream( HANDLE hHandle )
{
	CDetectionEdgeBlockiness* pEdgeBlock = (CDetectionEdgeBlockiness*)hHandle;
	return pEdgeBlock->FinishedStream();
}

HRESULT WINAPI MCQA_EdgeBlockSetOption( HANDLE hHandle, LPSTR_MAP lpmapOption )
{
	CDetectionEdgeBlockiness* pEdgeBlock = (CDetectionEdgeBlockiness*)hHandle;
	return pEdgeBlock->SetOption(lpmapOption);
}