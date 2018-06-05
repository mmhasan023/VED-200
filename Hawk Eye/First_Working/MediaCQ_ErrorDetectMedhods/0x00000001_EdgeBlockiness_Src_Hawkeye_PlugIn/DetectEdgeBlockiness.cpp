//DetecFreezeFrame.cpp
#include "stdafx.h"
#include "MAUtil.h"
#include "iplFrameEx.h"
#include "iplAPI.h"

#include "DetectEdgeBlockiness.h"


#include <algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _LOGDATA
#include "log.h"
#endif


#define PHASE_SIZE 60
int g_nWeight[] = { 
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7,//14__________
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7,//14__________
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7,//14__________
	10,// 0 
	 7,// 1
	 3,// 2
	 2,// 3 
	 1,// 4
	 1,// 5
	 0,// 6
	 0,// 7____
	 0,// 8
	 0,// 9
	 1,//10
	 1,//11
	 2,//12
	 3,//13
	 7 //14__________
};


CDetectionEdgeBlockiness::CDetectionEdgeBlockiness(void)
{
	memset( &m_AVResult, 0, sizeof(AVRESULT) );
	memset( &m_VideoApi, 0, sizeof(CVIDEOAPI) );

	m_lpCallback             = NULL;
	m_lpUserData             = NULL;
	m_hCommonDLL             = NULL;
	m_dwDetecedFlag          = CQ_QC_EDGE_BLOC;
	m_bInitialize            = TRUE;

	m_nWindowSize            = 0;
	m_nWidth                 = 0;
	m_nHeight                = 0;
	m_nSize                  = 0;
	m_dwTotalFrames          = 0;

	m_tAlramSystemStartTime	 = 0;
	m_tAlramSystemEndTime	 = 0;

	m_dwNoneDetectEndFrame   = 0;
	m_dwNoneDetectStartFrame = 0;
	m_ucNoneDetectStartRatio = 0;
	m_ucNoneDetectEndRatio   = 0;
	m_pGrayPhase             = NULL;
	m_pHistogramPhase        = NULL;
	m_ppErrorDector          = NULL;

	LoadCommonDLL();
}

CDetectionEdgeBlockiness::~CDetectionEdgeBlockiness(void)
{
	if(m_hCommonDLL)
		FreeLibrary(m_hCommonDLL); 

	if( m_pGrayPhase )
		delete[] m_pGrayPhase;

	if( m_pHistogramPhase )
		delete[] m_pHistogramPhase;

	if( m_ppErrorDector )
	{
		for( int i=0 ; i<4 ; i++ )
		{
			delete m_ppErrorDector[i];
		}

		delete m_ppErrorDector;
	}
}

HRESULT CDetectionEdgeBlockiness::SetOption( LPSTR_MAP lpmapOption )
{
	STR_MAP::iterator itor;
	CString szValue;

	itor = lpmapOption->find(_T("None detect start ratio"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_ucNoneDetectStartRatio = (BYTE)_ttoi( (LPCTSTR)szValue );
	}

	itor = lpmapOption->find(_T("None detect end ratio"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_ucNoneDetectEndRatio = (BYTE)_ttoi( (LPCTSTR)szValue );
	}
/*
	itor = lpmapOption->find(_T("Pulse signal detect ratio"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_ucPulseSignalRatio = (BYTE)_ttoi( (LPCTSTR)szValue );
	}

	itor = lpmapOption->find(_T("Using twin block filter"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();

//		if( szValue == _T("False") )
		if( szValue.CompareNoCase( _T("False") ) == 0 )
			m_bUseingAdaboost = FALSE;
//		if( szValue == _T("True") )
//			m_bUseingAdaboost = TRUE;
	}
*/

	return S_OK;
}












HRESULT CDetectionEdgeBlockiness::CheckStream(LPAVDATA lpAVData)
{
//	ImpulseNoiseEnhance(LPAVDATA lpAVData);

	if( m_hCommonDLL    == NULL            ) return E_FAIL;
	if( lpAVData        == NULL            ) return E_FAIL;
	if( lpAVData->eType != _AL_MEDIA_Video ) return E_FAIL;

	LPVIDEODATA lpVideo = &(lpAVData->video);

	if( m_bInitialize )
	{
		m_nWindowSize   = (m_VideoApi.lpGetProcessWindow)(lpVideo->hCVideo);
		m_nWidth        = lpVideo->dwWidth ;
		m_nHeight       = lpVideo->dwHeight;
		m_dwTotalFrames = lpVideo->dwTotalFrames;
		m_nSize         = m_nWidth * m_nHeight;
		m_pGrayPhase    = new BYTE[m_nSize];

		m_dwNoneDetectStartFrame = (DWORD)( (float)m_dwTotalFrames * (float)m_ucNoneDetectStartRatio/100.f );
		m_dwNoneDetectEndFrame   = (DWORD)( (float)m_dwTotalFrames - (float)m_dwTotalFrames * (float)m_ucNoneDetectEndRatio  /100.f );

		m_ppErrorDector  = new C1DImpulseEdgeDetectionRT*[4];
		for( int i=0 ; i<4 ; i++ )
		{
			m_ppErrorDector[i] = new C1DImpulseEdgeDetectionRT(7);
		}

		m_pHistogramPhase = new long[256];

#ifdef _OPENMP
		iplSetOptimalThreasds( m_nHeight );
#endif
		m_bInitialize = FALSE;
	}


	UINT nCurFrameNum = lpVideo->dwCurrentFrame;

	if( m_dwTotalFrames )//For RED, Hawkeye RED's m_dwTotalFrames=0,
	{
		if( nCurFrameNum < m_dwNoneDetectStartFrame ) 
			return S_OK;
		if( nCurFrameNum > m_dwNoneDetectEndFrame   )
			return S_OK;
	}


	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nCurFrameNum   );
	if( pFrame == NULL ) return S_FALSE;

	LPBYTE lpGray = pFrame->GetGrayBuffer();
	if( lpGray == NULL ) return S_FALSE;

	iplSobel60Hypotenuse( lpGray, m_pGrayPhase, m_nWidth, m_nHeight, 10 );

	////////////////////////////////////////////////////////////////////////////
	//Compute Phase Histogram
	memset( m_pHistogramPhase, 0, sizeof(long)*256 );
    BYTE *pSrcBuffer          = m_pGrayPhase;
    BYTE *pEndBuffer          = pSrcBuffer + m_nSize;
    long *pDstHistogramBuffer = m_pHistogramPhase;

	while( pSrcBuffer < pEndBuffer )
		pDstHistogramBuffer[*pSrcBuffer++]++;
	//Compute Phase Histogram
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//Cut Histogram
	int nApplyStart =  0;
	int nApplyEnd   = 60;
	pDstHistogramBuffer = m_pHistogramPhase;
	memset( pDstHistogramBuffer, 0, sizeof(long) * nApplyStart );
	memset( pDstHistogramBuffer + nApplyEnd, 0, sizeof(long) * (256-nApplyEnd) );
	//Cut Histogram
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//Apply Weight
	int*  pWeight      = g_nWeight;
	long* pSrcHisto    = m_pHistogramPhase;
	long* pDstHisto    = m_pHistogramPhase;
	long* pSrcHistoEnd = pSrcHisto + PHASE_SIZE;

	while( pSrcHisto<pSrcHistoEnd )
	{
		*pDstHisto++ = *pSrcHisto++ * *pWeight++;
	}
	//Apply Weight
	////////////////////////////////////////////////////////////////////////////


	int nDetected = 0;
	for( int i=0 ; i<4 ; i++ )
	{
		int nResult = m_ppErrorDector[i]->SetValue( m_pHistogramPhase[i*15], 400, 60 );

		switch( nResult )
		{
		case IPL1D_NONE        :		
		case IPL1D_DETECT      :
		case IPL1D_SMALL       :
		case IPL1D_CONTINUE    :
		case IPL1D_DETECT_LOW  : break;
		case IPL1D_DETECT_HIGH :
			nDetected |= 1<<i;
			break;
		default: break;
		}
	}
#ifdef _LOGDATA
	LOGOUT( _T("%d	0x%08X	%d	%d	%d	%d"), nCurFrameNum, nDetected,
		m_pHistogramPhase[0],m_pHistogramPhase[15],m_pHistogramPhase[30],m_pHistogramPhase[45]  );
#endif

	if( nDetected )
	{
		SendErrorFrame( lpAVData, nCurFrameNum-4 );
	}

#ifdef _LOGDATA
	if( 310<=nCurFrameNum && nCurFrameNum<=320 )
	{
		TCHAR szPath[MAX_PATH]={0};
		CxImage xImageorg;
		_stprintf( szPath, _T("C:\\TestCheckResult\\org%08d.jpg"), nCurFrameNum);
		xImageorg.CreateFromArray( pFrame->GetPixelData(), m_nWidth , m_nHeight, sizeof(BYTE)*24, m_nWidth*3 , false );
		xImageorg.Save( szPath, CXIMAGE_FORMAT_JPG);
	}
#endif
	return S_OK;
}

HRESULT CDetectionEdgeBlockiness::ImpulseNoiseEnhance(LPAVDATA lpAVData)
{
	if( m_hCommonDLL    == NULL            ) return E_FAIL;
	if( lpAVData        == NULL            ) return E_FAIL;
	if( lpAVData->eType != _AL_MEDIA_Video ) return E_FAIL;

	LPVIDEODATA lpVideo = &(lpAVData->video);

	if( m_bInitialize )
	{
		m_nWindowSize  = (m_VideoApi.lpGetProcessWindow)(lpVideo->hCVideo);
		m_nWidth       = lpVideo->dwWidth ;
		m_nHeight      = lpVideo->dwHeight;
		m_dwTotalFrames= lpVideo->dwTotalFrames;
		m_nSize        = m_nWidth * m_nHeight;

		m_dwNoneDetectStartFrame = (DWORD)( (float)m_dwTotalFrames * (float)m_ucNoneDetectStartRatio/100.f );
		m_dwNoneDetectEndFrame   = (DWORD)( (float)m_dwTotalFrames - (float)m_dwTotalFrames * (float)m_ucNoneDetectEndRatio  /100.f );

#ifdef _OPENMP
		iplSetOptimalThreasds( m_nHeight );
#endif
		m_bInitialize = FALSE;
	}


	UINT nCurFrameNum = lpVideo->dwCurrentFrame;

	if( m_dwTotalFrames )//For RED, Hawkeye RED's m_dwTotalFrames=0,
	{
		if( nCurFrameNum < m_dwNoneDetectStartFrame ) 
			return S_OK;
		if( nCurFrameNum > m_dwNoneDetectEndFrame   )
			return S_OK;
	}

	if( nCurFrameNum < 3 )
		return S_OK;

	CIplFrameEx* pFrameB = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nCurFrameNum-2 );
	if( pFrameB==NULL ) return S_FALSE;
	CIplFrameEx* pFrameC = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nCurFrameNum-1 );
	if( pFrameC==NULL ) return S_FALSE;
	CIplFrameEx* pFrameA = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nCurFrameNum   );
	if( pFrameA==NULL ) return S_FALSE;


	if( nCurFrameNum < 153 ) return S_OK;
	if( nCurFrameNum > 319 ) return S_OK;
	

	BYTE* pDst = new BYTE[m_nSize*3];

//	iplMedianTimeSpace3x3( pFrameB->GetPixelData(),
//		pFrameC->GetPixelData(),
//		pFrameA->GetPixelData(),
//		pDst,
//		m_nWidth,
//		m_nHeight,
//		3);


	static int g_ncount = 0;
	TCHAR szPath[MAX_PATH]={0};
	CxImage xImage;
	_stprintf( szPath, _T("C:\\TestCheckResult\\%08d.jpg"), g_ncount++ );
	xImage.CreateFromArray( pDst, m_nWidth , m_nHeight, sizeof(BYTE)*24, m_nWidth*3 , false );
	xImage.Save( szPath, CXIMAGE_FORMAT_JPG);

	CxImage xImageorg;
	_stprintf( szPath, _T("C:\\TestCheckResult\\org%08d.jpg"), g_ncount);
	xImageorg.CreateFromArray( pFrameC->GetPixelData(), m_nWidth , m_nHeight, sizeof(BYTE)*24, m_nWidth*3 , false );
	xImageorg.Save( szPath, CXIMAGE_FORMAT_JPG);

	delete[] pDst;

	return S_OK;
}

void CDetectionEdgeBlockiness::SetCallback( LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	m_lpCallback = lpCallback;
	m_lpUserData = lpUserData;
}

void CDetectionEdgeBlockiness::LoadCommonDLL(void)
{
	CMAUtil::GetCommonVideoAPI( &m_hCommonDLL, &m_VideoApi);
}

HRESULT CDetectionEdgeBlockiness::FinishedStream( void )
{
	return S_OK;
}

HRESULT CDetectionEdgeBlockiness::SendErrorFrame( LPAVDATA lpAVData, const int& nTargetFrame )
{
#ifdef _LOGDATA
	LOGOUT(_T("target = %08d"), nTargetFrame);
#endif

	LPVIDEODATA  lpVideo = &(lpAVData->video);
	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nTargetFrame );

	if(pFrame==NULL) return S_FALSE;

	time(&m_tAlramSystemStartTime)							;
	time(&m_tAlramSystemEndTime  )							;

	m_AVResult.nFrameNumber     = pFrame->GetFrameNo  ()  	;
	m_AVResult.nFrameStart      = pFrame->GetFrameNo  ()  	;
	m_AVResult.nFrameEnd        = pFrame->GetFrameNo  ()  	;
	m_AVResult.lpData           = pFrame->GetPixelData()  	;
	m_AVResult.dwDataSize       = pFrame->GetDataSize ()  	;
	m_AVResult.dwDetectFlag     = m_dwDetecedFlag     	    ;
	m_AVResult.eResultCondition = eCONDITION_DETECTION    	;
	m_AVResult.tSystemTimeStart = m_tAlramSystemStartTime	;
	m_AVResult.tSystemTimeEnd	= m_tAlramSystemEndTime		;

	
	double dDifference = (double)(lpAVData->video.dwCurrentFrame-m_AVResult.nFrameStart)/lpAVData->video.dbFrameRate;
	m_AVResult.rtStartTime  = (REFERENCE_TIME)( (lpAVData->video.dbSampleTime-dDifference)*UINT_REFERENCE_TIME );
	m_AVResult.rtEndTime    = m_AVResult.rtStartTime;


	if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);

	return S_OK;
}



