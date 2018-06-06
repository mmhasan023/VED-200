#include "stdafx.h"


//#ifdef _LOGDATA
#if ( defined(_LOGDATA) || defined(PIPE_LOG) )

#include "tchar.h"
#include "log.h"
#include <shlobj.h>
#include <stdio.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
static DWORD g_t0 = 0;
static TCHAR g_szFolder[MAX_PATH]={0};
static int g_nSema = 1;

BOOL _CreateFullDir(LPCTSTR lpSrcPath, BOOL bIsFilePath)
{
	TCHAR szPath[MAX_PATH2]={0};
	_tcscpy( szPath, lpSrcPath);

	int     nSize     = (int)_tcslen(szPath);
	TCHAR*  lpItor    = szPath         ;
	TCHAR*  lpItorEnd = szPath+nSize   ;

	if(bIsFilePath)
	{
		while( *lpItorEnd != '\\' && lpItorEnd!=lpItor )
			*lpItorEnd-- = NULL;
	}
	lpItorEnd = szPath+nSize   ;

	TCHAR szResult[MAX_PATH2]={0};
	TCHAR szTmp   [MAX_PATH2]={0};

	while( (lpItor<lpItorEnd) && *lpItor!='\0' )
	{
		memset( szTmp, 0, sizeof(TCHAR)*MAX_PATH2 );
		TCHAR* pTmpItor = szTmp;
		while( *lpItor!='\\' && *lpItor!='\0')
		{
			*pTmpItor++ = *lpItor++;
		}

		if(*lpItor!='\0')
			_tcscat( szTmp, _T("\\") );

		_tcscat( szResult, szTmp );
		if( ::GetFileAttributes(szResult)==INVALID_FILE_ATTRIBUTES )
		{
			if (CreateDirectory(szResult, NULL) == FALSE)
			{
				return FALSE;
			}
		}

		while( *lpItor=='\\' && *lpItor!='\0')
		{
			lpItor++;
		}
	}

	return TRUE;
}

BOOL _GetUserDataPath(LPTSTR lpPath, int nSize)
{
	TCHAR	szPath[MAX_PATH2]={0};

	if (::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE) == FALSE )
			return FALSE;

	if (_tcslen(szPath) == 0)
	{
		if ( ::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE) == FALSE )
			return FALSE;
	}
	_tcscat( szPath, _T("\\Hawkeye\\") );

	if(::GetFileAttributes(szPath)==INVALID_FILE_ATTRIBUTES)
		::CreateDirectory(szPath,NULL);


	_tcscpy( lpPath, szPath);

	return TRUE;
}

void SET_SUBFOLDER( IN LPCTSTR lpFolderName )
{
	memset ( g_szFolder, 0, sizeof(TCHAR)*MAX_PATH );
	_tcscpy( g_szFolder, lpFolderName );
}

BOOL DEBUG_MAKE_NAME(IN LPCTSTR szName, OUT LPTSTR lpFullPath, int nSize)
{
	TCHAR szPath[MAX_PATH2]={0};
	_GetUserDataPath( szPath, MAX_PATH2 );

	_tcscat( szPath, g_szFolder );

	int nLength = (int)_tcslen( szPath ) -1;
	if( szPath[nLength] != '\\' )
		_tcscat( szPath, _T("\\") );

	_CreateFullDir(szPath,FALSE);

	SYSTEMTIME st;
	GetSystemTime(&st);
	TCHAR szFileName[MAX_PATH]={0};
//	_stprintf( szFileName, _T("%04d_%02d_%02d_%s.txt"), st.wYear, st.wMonth, st.wDay, g_szFolder );		//체크서버로그를 한파일에 다 남기는 경우.,
	_stprintf( szFileName, _T("%04d_%02d_%02d_%s.txt"), st.wYear, st.wMonth, st.wDay, szName );

	_tcscat( szPath, szFileName );
	_tcscpy( lpFullPath, szPath);

//	memset(szPath, 0, sizeof(szPath));
//	_GetUserDataPath( szPath, MAX_PATH2 );
//	_tcscat( szPath, _T("CheckProfile") );
//	_CreateFullDir(szPath,FALSE);

	return TRUE;
}

void LOGOUT(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	while( g_nSema==0 ) Sleep(10);
	g_nSema--;

	FILE *fFile = NULL;

	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("log"), szFullPath, MAX_PATH2 );
	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;
	
	SYSTEMTIME st;
	GetLocalTime(&st);

	_ftprintf( fFile,_T("%02d:%02d:%02d:%03d - "),
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
	fseek(fFile,0,SEEK_END);

	va_list marker;
	TCHAR szTmp[2048];
	memset(szTmp,0,2048*sizeof(TCHAR));

	va_start( marker ,szMsg );  
	_vstprintf(szTmp,szMsg, marker);
	va_end( marker );             

	char szMessage[2048]={0};
#ifdef _UNICODE
	int AnsiStrSize = WideCharToMultiByte(CP_ACP, 0, szTmp, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, szTmp, -1, szMessage, AnsiStrSize, 0, 0);
#else
	strcpy(szMessage, szTmp);
#endif
	fseek(fFile,0,SEEK_END);
	fwrite(szMessage,strlen(szMessage),1,fFile);
	fwrite("\r\n",strlen("\r\n"),1,fFile);

	fclose(fFile);

	g_nSema++;
}

void LOGSEND(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	FILE *fFile = NULL;

	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("send"), szFullPath, MAX_PATH2 );
	
	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;
	
	SYSTEMTIME st;
	GetLocalTime(&st);

	_ftprintf( fFile,_T("%02d:%02d:%02d - "),
		st.wHour, st.wMinute, st.wSecond );

	fseek(fFile,0,SEEK_END);

	va_list marker;
	TCHAR szTmp[2048];
	memset(szTmp,0,2048*sizeof(TCHAR));

	va_start( marker ,szMsg );  
	_vstprintf(szTmp,szMsg, marker);
	va_end( marker );             

	char szMessage[2048]={0};
#ifdef _UNICODE
	int AnsiStrSize = WideCharToMultiByte(CP_ACP, 0, szTmp, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, szTmp, -1, szMessage, AnsiStrSize, 0, 0);
#else
	strcpy(szMessage, szTmp);
#endif
	fseek(fFile,0,SEEK_END);
	fwrite(szMessage,strlen(szMessage),1,fFile);
	fwrite("\r\n",strlen("\r\n"),1,fFile);

	fclose(fFile);

}

void LOGRSV(TCHAR *szMsg, ...)
{
	if(szMsg==NULL) return;

	FILE *fFile = NULL;

	TCHAR szFullPath[MAX_PATH2]={0};
	DEBUG_MAKE_NAME( _T("rsv"), szFullPath, MAX_PATH2 );
	
	if( (fFile = _tfopen(szFullPath, _T("a+") )) == NULL )
		return;
	
	SYSTEMTIME st;
	GetLocalTime(&st);

	_ftprintf( fFile,_T("%02d:%02d:%02d - "),
		st.wHour, st.wMinute, st.wSecond );

	fseek(fFile,0,SEEK_END);

	va_list marker;
	TCHAR szTmp[2048];
	memset(szTmp,0,2048*sizeof(TCHAR));

	va_start( marker ,szMsg );  
	_vstprintf(szTmp,szMsg, marker);
	va_end( marker );             

	char szMessage[2048]={0};
#ifdef _UNICODE
	int AnsiStrSize = WideCharToMultiByte(CP_ACP, 0, szTmp, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, szTmp, -1, szMessage, AnsiStrSize, 0, 0);
#else
	strcpy(szMessage, szTmp);
#endif
	fseek(fFile,0,SEEK_END);
	fwrite(szMessage,strlen(szMessage),1,fFile);
	fwrite("\r\n",strlen("\r\n"),1,fFile);

	fclose(fFile);
}
#endif
