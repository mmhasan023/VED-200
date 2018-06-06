#pragma once
#include "TestMediaAngelDlg.h"
#include "Gdiplus.h"

using namespace Gdiplus;

#pragma comment(lib,"gdiplus.lib")
// CMediaFileOut

class CMediaFileOut
{

public:
	CMediaFileOut();
	virtual ~CMediaFileOut();

protected:
public:
	CTestMediaAngelDlg *MADlg   ;
	
	BOOL SaveBmpFile(Bitmap* InBitmap, CString OutPath, CLSID Clsid,CString CurFrame,HANDLE n_CQHAndle);
	BOOL SaveErrBmpFile(LPCTSTR lpPath,Bitmap* InBitmap, CString OutPath, CLSID Clsid,CString CurFrame,HANDLE n_CQHAndle,DWORD dwErrFlag);
	void SaveMuteFile(LPCTSTR lpPath,INT64 channel, INT64 nMuteStart, INT64 nMuteEnd, HANDLE nCQHandle);
	void SaveLatterBoxFile(LPCTSTR lpPath, INT64 nMuteStart, INT64 nMuteEnd, INT64 nChannel, HANDLE nCQHandle);
	void SaveFreqFile(LPCTSTR lpPath, INT64 nMuteStart, INT64 nMuteEnd, INT64 nChannel, HANDLE nCQHandle);
	void SaveHighFreqFile(LPCTSTR lpPath, INT64 nMuteStart, INT64 nMuteEnd, INT64 nChannel, HANDLE nCQHandle);
	void SaveFrameFile(LPCTSTR lpPath, UINT nStart, UINT nEnd, HANDLE nCQHandle);

};