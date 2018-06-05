//DetecFreezeFrame.cpp
#include "stdafx.h"
#include "DetecEdgeBlock.h"
#include "MAUtil.h"
#include "iplFrameEx.h"
#include "iplAPI.h"


CDetectionEdgeBlock::CDetectionEdgeBlock(void)
{
	m_lpCallback       =NULL;
	m_lpUserData       =NULL;
	memset( &m_AVResult, 0, sizeof(AVRESULT) );
	m_dwDetecedFlag    = CQ_QC_EDGE_BLOC;
	m_hCommonDLL       = NULL;
	memset( &m_VideoApi, 0, sizeof(CVIDEOAPI) );

	m_pErrorDector     = NULL;

	LoadCommonDLL();
}

CDetectionEdgeBlock::~CDetectionEdgeBlock(void)
{
	if(m_hCommonDLL)
		FreeLibrary(m_hCommonDLL); 

	if(m_pErrorDector)
		delete m_pErrorDector;
}

HRESULT CDetectionEdgeBlock::CheckStream(LPAVDATA lpAVData)
{
	if( m_hCommonDLL == NULL ) return E_FAIL;
	if( lpAVData     == NULL ) return E_FAIL;
	if( lpAVData->eType != _AL_MEDIA_Video ) return E_FAIL;

	LPVIDEODATA lpVideo = &(lpAVData->video);

	if( m_pErrorDector == NULL)
	{
		m_pErrorDector = new C1DImpulseEdgeDetection( (m_VideoApi.lpGetProcessWindow)(lpVideo->hCVideo),
		                                               lpVideo->dwTotalFrames                          , 
													   lpVideo->dwWidth*lpVideo->dwHeight              );

		m_dwTargetGap  = (m_VideoApi.lpGetProcessWindow)(lpVideo->hCVideo);
	}

	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpVideo->hCVideo, lpVideo->dwCurrentFrame );
	if(pFrame==NULL) return S_FALSE;

	VECTOR_POINT vectorLPPOINT;
	INT nConnerCount = ipl_corner_detect(   pFrame->GetGrayLowPassBuffer(), 
											lpVideo->dwWidth       ,
											lpVideo->dwHeight      ,
											vectorLPPOINT          );

	//CIplFrameEx* pFrameBefore = m_VideoApi.lpGetFrame( lpVideo->hCVideo, lpVideo->dwCurrentFrame-1 );
	//CHistoRGB12bitBin* pHistoBefore = pFrameBefore->GetHistogram();
	//CHistoRGB12bitBin* pHistoCur    = pFrame      ->GetHistogram();
	//INT nDiff = pHistoCur->Distance(pHistoBefore);

	int nTargetFrame = 0;
	int nOldTarget   = 0;
	int nState = m_pErrorDector->SetValue( nConnerCount, lpVideo->dwCurrentFrame, nTargetFrame, nOldTarget, 400, 35 );
#ifdef _LOGDATA
	DEBUG_MSG(_T("%08d	%08d	%08d"),lpVideo->dwCurrentFrame,nConnerCount,nState);
#endif
	switch(nState)
	{
		case IPL1D_NONE    :break;
		case IPL1D_DETECT  :
			return SendErrorFrame( lpAVData, nTargetFrame-1 );
			break;
		case IPL1D_SMALL   :break;
		case IPL1D_CONTINUE:break;
		default: break;
	}

	return S_OK;
}

void CDetectionEdgeBlock::SetCallback( LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	m_lpCallback = lpCallback;
	m_lpUserData = lpUserData;
}

void CDetectionEdgeBlock::LoadCommonDLL(void)
{
	CMAUtil::GetCommonVideoAPI( &m_hCommonDLL, &m_VideoApi);
}

HRESULT CDetectionEdgeBlock::FinishedStream( void )
{
	return S_OK;
}

HRESULT CDetectionEdgeBlock::SendErrorFrame(LPAVDATA lpAVData, const int& nTargetFrame)
{
	LPVIDEODATA  lpVideo = &(lpAVData->video);
	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nTargetFrame );

	if(pFrame==NULL) return S_FALSE;

	m_AVResult.nFrameNumber = pFrame->GetFrameNo  ()  ;
	m_AVResult.lpData       = pFrame->GetPixelData()  ;
	m_AVResult.dwDataSize   = pFrame->GetDataSize ()  ;
	m_AVResult.dwDetectFlag = m_dwDetecedFlag         ;

	if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);

	return S_OK;
}
