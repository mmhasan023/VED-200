#ifndef _LOG_INCLUDE_H_
#define _LOG_INCLUDE_H_




#ifndef MAX_PATH2
	#define MAX_PATH2 520
#endif


//#ifdef _LOGDATA
#if ( defined(_LOGDATA) || defined(PIPE_LOG) )

extern void LOGOUT (TCHAR *szMsg, ...);
extern void LOGSEND(TCHAR *szMsg, ...);
extern void LOGRSV (TCHAR *szMsg, ...);
extern void SET_SUBFOLDER( IN LPCTSTR lpFolderName );//저장 될 하위 폴더 이름 지정, CApp::InitInstance등에서 한번만 수행 한다.

extern BOOL CreateFullDir(LPCTSTR lpSrcPath, BOOL bIsFilePath);
extern BOOL GetUserDataPath(LPTSTR lpPath, int nSize);

#endif


#endif//_LOG_INCLUDE_H_