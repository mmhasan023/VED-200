//MAUtil.h
//Media Archiving API Utility
//2009.06.03
//by kiok ahn
#ifndef _MEDIA_ARCHIVING_API_UTILITY_H_INCLUDE_
#define _MEDIA_ARCHIVING_API_UTILITY_H_INCLUDE_

#include "stdafx.h"
#include "CommonDataApi.h"

#ifdef _LOGDATA
#define LOG_PATH2 _T("C:\\log.txt")
extern void DEBUG_MSG(TCHAR *szMsg, ... );
#endif

#ifndef MAX_PATH2
#define MAX_PATH2 520 //MAX_PATH*2
#endif

class CMAUtil
{
public:
	CMAUtil(){};
	~CMAUtil(){};
public:	
	static BOOL GetCommonAudioAPI(HINSTANCE* phInatance, LPCAUDIOAPI lpCAudioApi);
	static BOOL GetCommonVideoAPI(HINSTANCE* phInatance, LPCVIDEOAPI lpCVideoApi);

protected:
	static int GetMainPath( LPTSTR lpPath, int nSize );
};

#endif