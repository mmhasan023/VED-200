//EdgeBlockExport.h    
#ifndef _DETECTION_EDGE_BLOC_H_INCLUDE_
#define _DETECTION_EDGE_BLOC_H_INCLUDE_

#include "TTypeDefine.h"

HANDLE  WINAPI MCQA_EdgeBlockOpen          ( void );
HRESULT WINAPI MCQA_EdgeBlockClose         ( HANDLE hHandle );
HRESULT WINAPI MCQA_EdgeBlockSetCallback   ( HANDLE hHandle, LPFN_AVRESULT lpCallback, LPVOID lpUserData );
HRESULT WINAPI MCQA_EdgeBlock              ( HANDLE hHandle,LPAVDATA lpAVData );
HRESULT WINAPI MCQA_EdgeBlockFinishedStream( HANDLE hHandle );
HRESULT WINAPI MCQA_EdgeBlockSetOption     ( HANDLE hHandle, LPSTR_MAP lpmapOption );
#endif//_DETECTION_EDGE_BLOC_H_INCLUDE_