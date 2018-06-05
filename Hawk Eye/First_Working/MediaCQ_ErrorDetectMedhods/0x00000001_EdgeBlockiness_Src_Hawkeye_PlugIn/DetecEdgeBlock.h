//DetecEdgeBlock.h
//Detection Edge Block
//By kiok ahn
//2009.06.10

#ifndef _CEDGE_BLOCK_H_INCLUDE_
#define _CEDGE_BLOCK_H_INCLUDE_

#include "stdafx.h"
#include "TTypeDefine.h"
#include "CommonDataApi.h"

#define _FREEZE_FRAME_NOISE_LEVEL 2

class C1DImpulseEdgeDetection;
class CDetectionEdgeBlock
{
public:
	CDetectionEdgeBlock(void);
	~CDetectionEdgeBlock(void);

public:
	HRESULT CheckStream   ( LPAVDATA lpAVData );
	void    SetCallback   ( LPFN_AVRESULT lpCallback, LPVOID lpUserData );
	HRESULT FinishedStream( void );

protected:
	HINSTANCE m_hCommonDLL ;
	CVIDEOAPI       m_VideoApi  ;

protected:
	void    LoadCommonDLL ( void );
	HRESULT SendErrorFrame( LPAVDATA lpAVData, const int& nTargetFrame );
private:
	LPFN_AVRESULT m_lpCallback       ;
	LPVOID        m_lpUserData       ;
	AVRESULT      m_AVResult         ;
	DWORD         m_dwDetecedFlag    ;
	DWORD         m_dwTargetGap      ;


	C1DImpulseEdgeDetection* m_pErrorDector;
};

#endif//_CEDGE_BLOCK_H_INCLUDE_