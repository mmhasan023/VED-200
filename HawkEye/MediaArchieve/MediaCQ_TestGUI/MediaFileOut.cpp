// MediaFileOut.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestMediaAngel.h"
#include "MediaFileOut.h"
#include "TestMediaAngelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMediaFileOut::CMediaFileOut()
{
	MADlg=(CTestMediaAngelDlg*)AfxGetApp()->m_pMainWnd;
}

CMediaFileOut::~CMediaFileOut()
{
	//delete[] MADlg;
}



// CMediaFileOut 메시지 처리기입니다.

BOOL CMediaFileOut::SaveBmpFile(Bitmap* InBitmap, CString OutPath, CLSID Clsid,CString CurFrame,HANDLE n_CQHAndle)
{
#ifdef _UNICODE
	Status state = InBitmap->Save(OutPath,&Clsid);
	
#else
	LPWSTR		wszFile;
	int nSize = OutPath.GetLength() + 1;
	wszFile = new WCHAR[nSize];
	memset(wszFile,0,sizeof(WCHAR)*nSize);
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)OutPath, nSize-1, wszFile, nSize); 
	Status state = InBitmap->Save(wszFile,&Clsid);
	delete[] wszFile;
#endif
	return 0;
}
#include "tchar.h"
void MSG_OUT(LPCTSTR lpFilePath, const TCHAR *szMsg, ... )
{
	FILE *fFile = NULL;
	va_list marker;
	TCHAR szTmp[2048];
	memset(szTmp,0,2048*sizeof(TCHAR));

	va_start( marker ,szMsg );  
	_vstprintf(szTmp,szMsg, marker);
	va_end( marker );             

	if( (fFile = _tfopen(lpFilePath, _T("a+") )) == NULL )
		return;

	fseek(fFile,0,SEEK_END);
	fwrite( szTmp, _tcslen(szTmp)*sizeof(TCHAR) ,1,fFile);
	fwrite( "\r\n",strlen("\r\n"),1,fFile);

	fclose(fFile);
}
BOOL CMediaFileOut::SaveErrBmpFile(LPCTSTR lpPath,Bitmap* InBitmap, CString OutPath, CLSID Clsid,CString CurFrame,HANDLE n_CQHAndle,DWORD dwErrFlag)
{

	CString szFile(lpPath);
	if(szFile.Right(1)!='\\')
		szFile += _T("\\");
	szFile += _T("ErrReport.txt");
	CString FileName = OutPath;
//	FileName.Replace((lpPath),"");
	if((dwErrFlag&CQ_QC_EDGE_BLOC)==CQ_QC_EDGE_BLOC)
	{
		MSG_OUT(szFile,_T("CQ_QC_EDGE_BLOC  :  %s"), OutPath );
	}
	else if((dwErrFlag&CQ_QC_FS_STAR)==CQ_QC_FS_STAR)
	{
		MSG_OUT(szFile,_T("CQ_QC_FS_STAR  :  %s"), OutPath );
	}
	else if((dwErrFlag&CQ_QC_FS_BLACK)==CQ_QC_FS_BLACK)
	{
		MSG_OUT(szFile,_T("CQ_QC_FS_BLACK  :  %s"), OutPath );
	}
	else if((dwErrFlag&CQ_QC_FS_FREEZE)==CQ_QC_FS_FREEZE)
	{
		MSG_OUT(szFile,_T("CQ_QC_FS_FREEZE  :  %s"), OutPath );
	}
//	else if((dwErrFlag&CQ_QC_FS_MACRO)==CQ_QC_FS_MACRO)
//	{
//		MSG_OUT(szFile,_T("CQ_QC_FS_MACRO  :  %s"), OutPath );
//	}
	else if((dwErrFlag&CQ_QC_BLACK_BAR)==CQ_QC_BLACK_BAR)
	{
		MSG_OUT(szFile,_T("CQ_QC_BLACK_BAR  :  %s"), OutPath );
	}
	else if((dwErrFlag&CQ_QC_LATTER_BOX)==CQ_QC_LATTER_BOX)
	{
		MSG_OUT(szFile,_T("CQ_QC_LATTER_BOX  :  %s"), OutPath );
	}

	

#ifdef _UNICODE
	Status state = InBitmap->Save(OutPath,&Clsid);
#else
	LPWSTR		wszFile;
	int nSize = OutPath.GetLength() + 1;
	wszFile = new WCHAR[nSize];
	memset(wszFile,0,sizeof(WCHAR)*nSize);
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)OutPath, nSize-1, wszFile, nSize); 
	Status state = InBitmap->Save(wszFile,&Clsid);
	delete[] wszFile;
#endif
	return 0;
}


void CMediaFileOut::SaveMuteFile(LPCTSTR lpPath, INT64 channel, INT64 nMuteStart, INT64 nMuteEnd, HANDLE nCQHandle)
{
	CString szFile(lpPath);
	if(szFile.Right(1)!='\\')
		szFile += _T("\\");

	szFile += _T("AudioMuteTime.txt");
	MSG_OUT(szFile,_T("%f Channel : %f second ~ %f second"), (double)channel,(double)nMuteStart/10000000.0, (double)nMuteEnd/10000000.0 );


	//레퍼런스타임의 시작, 끝시간, 핸들값 출력
}
void CMediaFileOut::SaveHighFreqFile(LPCTSTR lpPath, INT64 nMuteStart, INT64 nMuteEnd, INT64 nChannel, HANDLE nCQHandle)
{
	CString szFile(lpPath);
	if(szFile.Right(1)!='\\')
		szFile += _T("\\");

	szFile += _T("AudioHighFreqTime.txt");
	MSG_OUT(szFile,_T("%f second ~ %f second : %f Channel"), (double)nMuteStart/10000000.0, (double)nMuteEnd/10000000.0, (double)nChannel );


	//레퍼런스타임의 시작, 끝시간, 핸들값 출력
}
void CMediaFileOut::SaveFreqFile(LPCTSTR lpPath, INT64 nMuteStart, INT64 nMuteEnd, INT64 nChannel, HANDLE nCQHandle)
{
	CString szFile(lpPath);
	if(szFile.Right(1)!='\\')
		szFile += _T("\\");

	szFile += _T("AudioFreqTime.txt");
	MSG_OUT(szFile,_T("%f second ~ %f second : %f Channel"), (double)nMuteStart/10000000.0, (double)nMuteEnd/10000000.0, (double)nChannel );


	//레퍼런스타임의 시작, 끝시간, 핸들값 출력
}
void CMediaFileOut::SaveLatterBoxFile(LPCTSTR lpPath, INT64 nMuteStart, INT64 nMuteEnd, INT64 nChannel, HANDLE nCQHandle)
{
	CString szFile(lpPath);
	if(szFile.Right(1)!='\\')
		szFile += _T("\\");

	szFile += _T("LatterBoxTime.txt");
	MSG_OUT(szFile,_T("%f second ~ %f second : %f Channel"), (double)nMuteStart/10000000.0, (double)nMuteEnd/10000000.0, (double)nChannel );


	//레퍼런스타임의 시작, 끝시간, 핸들값 출력
}
void CMediaFileOut::SaveFrameFile(LPCTSTR lpPath, UINT nStart, UINT nEnd, HANDLE nCQHandle)
{
	CString szFile(lpPath);
	if(szFile.Right(1)!='\\')
		szFile += _T("\\");

	szFile += _T("OtherFrameError.txt");
	MSG_OUT(szFile,_T("%d Frame ~ %d Frame"), nStart, nEnd );


	//레퍼런스타임의 시작, 끝시간, 핸들값 출력
}
