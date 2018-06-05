//BlackFrameExport.h    
#ifndef _DETECTION_BLACK_FRAME_EXPORT_H_INCLUDE_
#define _DETECTION_BLACK_FRAME_EXPORT_H_INCLUDE_

#include "TTypeDefine.h"

HANDLE  WINAPI MCQA_BlackFrameOpen( void );
HRESULT WINAPI MCQA_BlackFrameClose( HANDLE hHandle );
HRESULT WINAPI MCQA_BlackFrameSetCallback( HANDLE hHandle, LPFN_AVRESULT lpCallback, LPVOID lpUserData );
HRESULT WINAPI MCQA_BlackFrame( HANDLE hHandle,LPAVDATA lpAVData );
HRESULT WINAPI MCQA_EdgeBlockSetOption( HANDLE hHandle, LPSTR_MAP lpmapOption );

#endif//_DETECTION_BLACK_FRAME_EXPORT_H_INCLUDE_