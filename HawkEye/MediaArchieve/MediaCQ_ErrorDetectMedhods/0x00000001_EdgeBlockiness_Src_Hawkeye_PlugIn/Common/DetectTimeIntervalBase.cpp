#include "stdafx.h"
#include "TTypeDefine.h"
#include "MAUtil.h"
#include "iplapi.h"
#include "iplFrameEx.h"

#include "DetectTimeIntervalBase.h"

#ifdef _LOGDATA
#include "log.h"
#endif


CDetectTimeIntervalBase::CDetectTimeIntervalBase( const DWORD&      dwDetecedFlag,
												  const LPCVIDEOAPI lpVideoApi   )
{
	m_dwDetecedFlag         = dwDetecedFlag;
	m_lpCallback   			= NULL ;
	m_lpUserData   			= NULL ;
	memset( &m_AVResult, 0, sizeof(AVRESULT) );

	m_nStartFrame           = 0    ;
	m_nEndFrame             = 0    ;
	m_dStartTime            = 0    ;
	m_dEndTime              = 0    ;
	m_tSystemStartTime      = 0    ;
	m_tSystemEndTime        = 0    ;
	m_bDetectFalg           = FALSE;
	m_bInitFlag             = TRUE ;

	m_lpVideoApi            = lpVideoApi;
}

CDetectTimeIntervalBase::~CDetectTimeIntervalBase()
{
}

HRESULT CDetectTimeIntervalBase::SetCallback( LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	m_lpCallback = lpCallback;
	m_lpUserData = lpUserData;
	return S_OK;
}

HRESULT CDetectTimeIntervalBase::FinishedStream	( void )
{
	return S_OK;
}

HRESULT CDetectTimeIntervalBase::SendErrorFrame( LPAVDATA lpAVData, const int& nTargetFrame  )
{
	m_AVResult.nFrameStart		= m_nStartFrame   		;
	m_AVResult.nFrameEnd		= m_nEndFrame   		;
	m_AVResult.lpData			= lpAVData->lpData      ;
	m_AVResult.dwDataSize		= lpAVData->dwDataSize	;
	m_AVResult.dwDetectFlag		= m_dwDetecedFlag		;
	m_AVResult.nFrameNumber		= m_nStartFrame  	    ;
	m_AVResult.tSystemTimeStart = m_tSystemStartTime    ;
	m_AVResult.tSystemTimeEnd   = m_tSystemEndTime      ;
	m_AVResult.eResultCondition = eCONDITION_DETECTION	;

	m_AVResult.rtStartTime  = (REFERENCE_TIME)( m_dStartTime * UINT_REFERENCE_TIME );
	m_AVResult.rtEndTime    = (REFERENCE_TIME)( m_dEndTime   * UINT_REFERENCE_TIME );

	if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);

	return S_OK;
}
