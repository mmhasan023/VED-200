#ifndef _LOG_INCLUDE_H_
#define _LOG_INCLUDE_H_

#ifndef MAX_PATH2
	#define MAX_PATH2 520
#endif

#if defined(_DEBUG)

extern void _memtrace_LOGOUT (TCHAR *szMsg, ...);
extern int  _memtrace_SET_SUBFOLDER( const TCHAR* lpSubFolderName );//���� �� ���� ���� �̸� ����, CApp::InitInstance��� �ѹ��� ���� �Ѵ�.

#endif


#endif//_LOG_INCLUDE_H_