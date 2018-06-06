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
extern void SET_SUBFOLDER( IN LPCTSTR lpFolderName );//���� �� ���� ���� �̸� ����, CApp::InitInstance��� �ѹ��� ���� �Ѵ�.

extern BOOL CreateFullDir(LPCTSTR lpSrcPath, BOOL bIsFilePath);
extern BOOL GetUserDataPath(LPTSTR lpPath, int nSize);

#endif


#endif//_LOG_INCLUDE_H_