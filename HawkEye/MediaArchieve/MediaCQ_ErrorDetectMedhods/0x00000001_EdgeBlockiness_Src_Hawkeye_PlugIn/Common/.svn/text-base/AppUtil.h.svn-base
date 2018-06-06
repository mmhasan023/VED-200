//////////////////////////////////////////////////////////////////////////////////////
//
//  Mediachorus Inc.
//
//////////////////////////////////////////////////////////////////////////////////////
//AppUtil.h
//Author : Kiok ahn
//E-mail : kiokahn@mediachorus.com
//////////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_UTILITY_H_INCLUDE_
#define _APPLICATION_UTILITY_H_INCLUDE_

#define CALCU_EFF_WIDTH(effwidth, width, bpp) \
	{ \
	effwidth = (DWORD)ceil(width * bpp / 8.0); \
	if (effwidth % 4 != 0) \
	effwidth = (effwidth / 4 + 1) * 4; \
	}

#ifdef _LOGDATA
//extern void DEBUG_MSG(TCHAR *szMsg, ... );
#endif


class CAppUtil
{
public:
	CAppUtil(){};
	~CAppUtil(){};

public:	
	static CString WINAPI GetMainPath       (void);
	static CString WINAPI GetProcessPath    (void);
	static void    WINAPI ForegroundWindow  (HWND hWnd);
	static BOOL    WINAPI FileDrop          (HWND hTarget, char *szFiles, int size);
	static BOOL    WINAPI KillProcess       (const CString& szProcess );
	static BOOL    WINAPI KillProcess		 (TCHAR *szProcess);		
	static BOOL    WINAPI Execute           (HWND hWnd, CString pathname, 
		                              CString argument=CString(""), BOOL bMustTruncate=FALSE);
	static CString WINAPI GetProcess        (const CString& szFullPath );
	static CString WINAPI GetCurDir         (const CString& szFullPath );
	static void    WINAPI SetActiveWindow   (HWND hWnd);
	static CString WINAPI GetWindowClassName(HWND hwnd);
	static void    WINAPI DisplayGetLastErrorMessage(void);

	static CString WINAPI GetDirectory		(const CString szFullPath);
	static CString WINAPI GetFtpDirectory	(const CString szFullPath);
	static CString WINAPI GetExtention      (LPCTSTR szPath);
	static CString WINAPI GetFileName       (LPCTSTR szFullPath);
	static CString WINAPI GetUserDataPath   (void);
	static BOOL	   WINAPI _GetUserDataPath(LPTSTR lpPath, int nSize);
	static BOOL    WINAPI CreateFullDir     (const CString &strPath, BOOL bFilePath=FALSE);
	static BOOL    WINAPI DeleteFilesInDirectory(LPCTSTR pathname);
	static BOOL    WINAPI CopyFilesinDirectory  (CString szSource , CString szDes);

	static BOOL    WINAPI WriteDIB          (LPTSTR szFile, HANDLE hDIB);
	static HANDLE  WINAPI DDBToDIB          (CBitmap& bitmap, DWORD dwCompression, CPalette* pPal);
	static BOOL    WINAPI WriteBitmap       (LPTSTR szFullPath, CBitmap* pBitmap, DWORD dwCompression=BI_RGB);
	static HBITMAP WINAPI GetHBITMAP        (LPBYTE lpData, LPBITMAPINFOHEADER lpBih);

	static DWORD   WINAPI GetFileSize       (LPCTSTR sPathName);

	static int     WINAPI axtoi             (const TCHAR* hexStg) ;

	int FastFileCopy(LPCTSTR src, LPCTSTR dest, const bool overwrite);
	static void WINAPI InverseBitmap(HBITMAP hDIB);

protected:
	static inline void    WINAPI SetTopMost (HWND hWnd);
	static inline BOOL    WINAPI KillProcess(IN DWORD dwProcessId);
	static inline int     WINAPI copyFileUsingMapping(HANDLE srcHandle, HANDLE destHandle);
	static inline int     WINAPI increaseFileSize(const HANDLE file, const __int64 size);
};

#endif