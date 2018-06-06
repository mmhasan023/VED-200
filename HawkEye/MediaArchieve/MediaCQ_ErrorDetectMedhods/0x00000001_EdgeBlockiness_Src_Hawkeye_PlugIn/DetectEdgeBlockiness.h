//DetecEdgeBlockiness.h
//Detection Edge Blockiness
//By kiok ahn
//2012.02.06

#ifndef _CEDGE_BLOCKINESS_H_INCLUDE_
#define _CEDGE_BLOCKINESS_H_INCLUDE_

#include "stdafx.h"
#include "TTypeDefine.h"
#include "CommonDataApi.h"

class C1DImpulseEdgeDetectionRT;

class CDetectionEdgeBlockiness
{
public:
	CDetectionEdgeBlockiness(void);
	~CDetectionEdgeBlockiness(void);

public:
	HRESULT CheckStream   ( LPAVDATA lpAVData );
	void    SetCallback   ( LPFN_AVRESULT lpCallback, LPVOID lpUserData );
	HRESULT FinishedStream( void );
	HRESULT SetOption     ( LPSTR_MAP lpmapOption );

protected:
	void    LoadCommonDLL ( void );
	HRESULT SendErrorFrame( LPAVDATA lpAVData, const int& nTargetFrame );

	HRESULT ImpulseNoiseEnhance(LPAVDATA lpAVData);

private:
	AVRESULT        m_AVResult        ;
	CVIDEOAPI       m_VideoApi        ;

	LPFN_AVRESULT   m_lpCallback      ;
	LPVOID          m_lpUserData      ;

	HINSTANCE       m_hCommonDLL      ;
	DWORD           m_dwDetecedFlag   ;
	BOOL            m_bInitialize     ;

protected:
	int             m_nWindowSize     ;
	INT             m_nWidth          ;
	INT             m_nHeight         ;
	INT             m_nSize           ;
	DWORD           m_dwTotalFrames   ;
	BYTE*           m_pGrayPhase      ;
	long*           m_pHistogramPhase ;

	C1DImpulseEdgeDetectionRT** m_ppErrorDector;

protected:
	time_t		    m_tAlramSystemStartTime ;
	time_t        	m_tAlramSystemEndTime   ;

	DWORD           m_dwNoneDetectEndFrame  ;
	DWORD           m_dwNoneDetectStartFrame;
	BYTE            m_ucNoneDetectStartRatio;
	BYTE            m_ucNoneDetectEndRatio  ;
};

#endif//_CEDGE_BLOCKINESS_H_INCLUDE_