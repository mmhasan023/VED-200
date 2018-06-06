#include "stdafx.h"
#include <shlobj.h>
#include "atlbase.h"

#include "math.h"
#include "AppUtil.h"
#include "Tlhelp32.h"

#ifdef _LOGDATA
//#include <LogWnd.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define HBYTES(w, b)    ((((w) * (b) + 31) & ~31) / 8)
/*
#ifdef _LOGDATA
#include <time.h>
#include "tchar.h"
#define LOG_PATH2 _T("log.txt")
void DEBUG_MSG(TCHAR *szMsg, ... )
{
	time_t osBinaryTime;  // C run-time time (defined in <time.h>)
	time( &osBinaryTime ) ;
	CTime _time( osBinaryTime );

	CString szPath;
	szPath.Format(_T("c:\\TestCheckResult\\%d_%d_%d"), _time.GetYear(), _time.GetMonth(), _time.GetDay() );
	if( ::GetFileAttributes(szPath) == INVALID_FILE_ATTRIBUTES )
		CAppUtil::CreateFullDir(szPath);

	szPath += _T("\\");
	szPath += LOG_PATH2;

	FILE *fFile = NULL;
	va_list marker;
	TCHAR szTmp[2048];
	memset(szTmp,0,2048*sizeof(TCHAR));

	va_start( marker ,szMsg );  
	_vstprintf(szTmp,szMsg, marker);
	va_end( marker );             

	if( (fFile = _tfopen(szPath, _T("a+") )) == NULL )
		return;

	fseek(fFile,0,SEEK_END);
	fwrite(szTmp,_tcsclen(szTmp)*sizeof(TCHAR),1,fFile);
	fwrite("\n",1,1,fFile);

	fclose(fFile);
}
#endif
*/

CString CAppUtil::GetMainPath(void)
{
	CString szPath;
	TCHAR *currentDirectory = new TCHAR[MAX_PATH];
	int size = sizeof(TCHAR)*MAX_PATH;
	ZeroMemory(currentDirectory, size);
	GetModuleFileName(AfxGetInstanceHandle(), currentDirectory, size);
	szPath = currentDirectory;
	delete []currentDirectory;

	while(szPath.Right(1)!=_T("\\") && szPath.GetLength() )
		szPath.Delete(szPath.GetLength()-1,1);

	return szPath;
}


CString CAppUtil::GetProcessPath(void)
{
	CString szPath;
	TCHAR *currentDirectory = new TCHAR[MAX_PATH];
	int size = sizeof(TCHAR)*MAX_PATH;
	ZeroMemory(currentDirectory, size);
	GetModuleFileName(AfxGetInstanceHandle(), currentDirectory, size);
	szPath = currentDirectory;
	delete []currentDirectory;

	return szPath;
}

void CAppUtil::ForegroundWindow(HWND hWnd)
{
	HWND hPrevWnd = ::GetForegroundWindow();
	if (hPrevWnd == NULL)
	{
		TRACE(_T("Fail to ForegroundWindow()"));
		return;
	}

	// hPrevWnd로 프로세스 ID를 얻음..
	DWORD dwAttach = ::GetWindowThreadProcessId(hPrevWnd, NULL); 

	// hWnd로 프로세스 ID를 얻음..
	DWORD dwAttachTo = ::GetWindowThreadProcessId(hWnd, NULL); 

	::AttachThreadInput(dwAttach, dwAttachTo, TRUE);

	::SetForegroundWindow(hWnd);

	SetTopMost(hWnd);
}

void CAppUtil::SetTopMost(HWND hWnd)
{
	::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

static HANDLE g_hMem = NULL;
BOOL CAppUtil::FileDrop(HWND hTarget, char *szFiles, int size)
{
	//	if(!m_pTarget->m_hWnd)
	if( !(::IsWindow(hTarget)) )
		return FALSE;

	if(g_hMem)GlobalFree(g_hMem);

	HANDLE g_hMem=GlobalAlloc(GMEM_ZEROINIT,sizeof(DROPFILES)+size);
	char *p=(char *)GlobalLock(g_hMem);
	DROPFILES *DropFiles=(DROPFILES *)p;
	DropFiles->pFiles=sizeof(DROPFILES);
	DropFiles->fNC = TRUE;
	DropFiles->fWide = FALSE;
	RECT pos;
	::GetWindowRect(hTarget,&pos);
	//	m_pTarget->GetWindowRect(&pos);
	DropFiles->pt.x = ( pos.right  - pos.left ) / 2 ;
	DropFiles->pt.y = ( pos.bottom - pos.top  ) / 2 ;
	p+=sizeof(DROPFILES);

	memcpy( p, szFiles,size+2 );

	GlobalUnlock(g_hMem);

	::PostMessage(hTarget,WM_DROPFILES,(WPARAM)g_hMem,0);

	return TRUE;
}

BOOL CAppUtil::KillProcess( IN DWORD dwProcessId )
{
	// get process handle
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
	if (hProcess == NULL)
		return FALSE;

	DWORD dwError = ERROR_SUCCESS;

	// try to terminate the process
	if (!TerminateProcess(hProcess, (DWORD)-1))
		dwError = GetLastError();

	// close process handle
	CloseHandle(hProcess);

	SetLastError(dwError);
	return dwError == ERROR_SUCCESS;
};


BOOL CAppUtil::KillProcess( const CString& szProcess )
{
#ifdef _LOGDATA
//	DEBUG_MSG(_T("[CAppUtil::KillProcess()] process=%s"),szProcess);
#endif
	BOOL bResult = FALSE;
	BOOL hRes    = FALSE;
	HANDLE hSnapShot;

	//Get the snapshot of the system
	hSnapShot=CreateToolhelp32Snapshot (TH32CS_SNAPALL,NULL);

	PROCESSENTRY32 pEntry;
	pEntry.dwSize =sizeof(pEntry);

	//Get first process
	Process32First (hSnapShot,&pEntry);

	//Iterate thru all processes
	while(1)
	{
		hRes = Process32Next (hSnapShot,&pEntry);

		if( hRes == FALSE )
			break;

		if( szProcess == pEntry.szExeFile )
			bResult = (bResult || KillProcess(pEntry.th32ProcessID));
	}
	CloseHandle(hSnapShot);
	return bResult;
}


BOOL CAppUtil::KillProcess(TCHAR *szProcess)
{
	ASSERT (szProcess != NULL);

	BOOL	bRet		 = FALSE; 
	PROCESSENTRY32 pe32  = {0}; 

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  

	if (hProcessSnap != INVALID_HANDLE_VALUE)
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hProcessSnap, &pe32)) 
		{ 
			BOOL          bGotModule = FALSE; 
			MODULEENTRY32 me32       = {0};

			do 
			{
				if(::lstrcmpi(pe32.szExeFile, szProcess)==0)
				{
					DWORD  Code = 0;

					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE, pe32.th32ProcessID); 

					GetExitCodeProcess(hProcess, &Code);

					if(TerminateProcess(hProcess, Code))
					{
						WaitForSingleObject(hProcess, 1000);

						bRet = TRUE;
					} 

					CloseHandle(hProcess);
					break;
				}
			} while (Process32Next(hProcessSnap, &pe32)); 
		}    

		CloseHandle (hProcessSnap); 
		return bRet;
	}
	return FALSE; 
}


BOOL CAppUtil::Execute(HWND hWnd, CString pathname, CString argument, BOOL bMustTruncate)
{
	register int i;
	if (bMustTruncate == TRUE)
	{
		i = pathname.Find(':');
		if (pathname.GetAt(i + 1) != '\\')
			pathname = pathname.Mid(i + 2, pathname.GetLength() - (i + 2));
	}

	TCHAR *currentDirectory = new TCHAR[_MAX_PATH];
	int size = sizeof(TCHAR)*_MAX_PATH;
	ZeroMemory(currentDirectory, size);

	GetCurrentDirectory(size, currentDirectory);

	i = pathname.ReverseFind('\\');
	CString newDirectory	= pathname.Left(i);
	CString filename		= pathname.Right(pathname.GetLength() - i - 1);

	SetCurrentDirectory(newDirectory);

	if (::ShellExecute(hWnd, NULL, pathname, argument, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32)
	{
		DisplayGetLastErrorMessage();

		SetCurrentDirectory(currentDirectory);

		delete[] currentDirectory;

		return FALSE;
	}

	SetCurrentDirectory(currentDirectory);

	delete[] currentDirectory;

	return TRUE;
}

CString CAppUtil::GetFtpDirectory(const CString szFullPath)
{
	ASSERT(szFullPath.GetLength() != 0);

	int index = szFullPath.ReverseFind('/');
	CString szDir = szFullPath.Left(index+1);

	return szDir;

}

CString CAppUtil::GetDirectory(const CString szFullPath)
{
	ASSERT(szFullPath.GetLength() != 0);

	int index = szFullPath.ReverseFind('\\');
	CString szDir = szFullPath.Left(index+1);

	return szDir;
}

CString CAppUtil::GetProcess(const CString& szFullPath )
{
	CString szProcess;
	TCHAR cTmp;
	int i = szFullPath.GetLength()-1;
	cTmp=szFullPath.GetAt(i);
	while(cTmp!='\\' && i )
	{
		szProcess.Insert(0,szFullPath.GetAt(i));
		i--;
		cTmp=szFullPath.GetAt(i);
	}

	return szProcess;
}

CString CAppUtil::GetCurDir(const CString& szFullPath )
{
	ASSERT(szFullPath.GetLength() != 0 );

	CString szDir;
	TCHAR cTmp;
	int i = szFullPath.GetLength()-1;
	cTmp=szFullPath.GetAt(i);

	while(cTmp!='\\' && i )
	{
		if(cTmp==':') return szFullPath;

		szDir.Insert(0,szFullPath.GetAt(i));
		i--;
		cTmp=szFullPath.GetAt(i);
	}

	return szDir;
}

CString CAppUtil::GetExtention(LPCTSTR szPath)
{
	CString szExtention;
	TCHAR cTmp;
	size_t i = _tcslen(szPath);
	TCHAR* pSrt = (TCHAR*)szPath;

	cTmp=pSrt[i];
	while( cTmp!='\\' && i && cTmp!= '.' )
	{
		szExtention.Insert(0,pSrt[i]);
		i--;
		cTmp=pSrt[i];
	}

	return szExtention;
}

void CAppUtil::SetActiveWindow(HWND hWnd)
{
	WINDOWPLACEMENT wPlacement; 
	memset(&wPlacement, 0 , sizeof(WINDOWPLACEMENT) );
	::GetWindowPlacement(hWnd,&wPlacement);
	while( wPlacement.showCmd == SW_SHOW          ||
		wPlacement.showCmd == SW_SHOWNORMAL    ||
		wPlacement.showCmd == SW_SHOWMAXIMIZED ||
		wPlacement.showCmd == SW_SHOWNA        ||
		wPlacement.showCmd == SW_SHOWDEFAULT   )
	{
		ForegroundWindow(hWnd);
		::GetWindowPlacement(hWnd,&wPlacement);
		Sleep(50);
	}
}

CString CAppUtil::GetWindowClassName(HWND hWnd)
{
	TCHAR str[MAX_PATH];
	int size = sizeof(TCHAR)*MAX_PATH;
	memset(str,0,size);

	BOOL bR = ::GetClassName(hWnd, str, size);

	CString msg(str);
	return msg;

}


CString CAppUtil::GetFileName(LPCTSTR szFullPath)
{
	CString szProcess = szFullPath;
	int nPos = szProcess.ReverseFind(_T('\\'));
	return szProcess.Right(szProcess.GetLength() - nPos - 1);
}

CString CAppUtil::GetUserDataPath(void)
{

	CString string;
	TCHAR	szPath[MAX_PATH];

	//	if (::SHGetSpecialFolderPath(0,szPath,CSIDL_COMMON_APPDATA,FALSE))
	if (::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE))
		string = szPath;

	if (_tcslen(szPath) == 0)
	{
		if (::SHGetSpecialFolderPath(0,szPath,CSIDL_LOCAL_APPDATA,FALSE))
			string = szPath;
	}

	if(::GetFileAttributes(string)==INVALID_FILE_ATTRIBUTES)
		::CreateDirectory(string,NULL);

	return string;
}
BOOL CAppUtil::_GetUserDataPath(LPTSTR lpPath, int nSize)
{
	TCHAR	szPath[MAX_PATH]={0};

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
BOOL CAppUtil::CreateFullDir(const CString &strPath, BOOL bFilePath)
{
	CFileFind	finder;
	CString		sDir, temp;
	BOOL		bWorking;

	sDir.Format(_T("%s"),strPath);
	sDir.TrimRight(_T("\\"));

	if (bFilePath == FALSE)
		sDir += _T("\\");

	int nIndex = sDir.Find(_T("\\"), 0);

	while ((nIndex = sDir.Find(_T("\\"), nIndex + 1)) >= 0)
	{
		temp	 = sDir.Left(nIndex);
		bWorking = finder.FindFile(temp);
		if (bWorking == FALSE)
		{
			if (CreateDirectory(temp, NULL) == FALSE)
			{
				DisplayGetLastErrorMessage();

				return FALSE;
			}
		}
	}

	return TRUE;
}



// DDBToDIB     - Creates a DIB from a DDB
// bitmap       - Device dependent bitmap
// dwCompression    - Type of compression - see BITMAPINFOHEADER
// pPal         - Logical palette
HANDLE CAppUtil::DDBToDIB(CBitmap& bitmap, DWORD dwCompression, CPalette* pPal)
{
	BITMAP              bm;
	BITMAPINFOHEADER    bi;
	LPBITMAPINFOHEADER  lpbi;
	DWORD               dwLen;
	HANDLE              hDIB;
	HANDLE              handle;
	HDC                 hDC;
	HPALETTE            hPal;

	ASSERT(bitmap.GetSafeHandle());
	// The function has no arg for bitfields
	if(dwCompression == BI_BITFIELDS)
		return NULL;

	// If a palette has not been supplied use defaul palette
	if((hPal = (HPALETTE) pPal->GetSafeHandle()) == NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);
	// Initialize the bitmapinfoheader
	bi.biSize           = sizeof(BITMAPINFOHEADER);
	bi.biWidth          = bm.bmWidth;
	bi.biHeight         = bm.bmHeight;
	bi.biPlanes         = 1;
	bi.biBitCount       = bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression    = dwCompression;
	bi.biSizeImage      = 0;
	bi.biXPelsPerMeter  = 0;
	bi.biYPelsPerMeter  = 0;
	bi.biClrUsed        = 0;
	bi.biClrImportant   = 0;
	// Compute the size of the  infoheader and the color table

	int nColors = (1 << bi.biBitCount);
	if(nColors > 256)   nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC  = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);
	// Allocate enough memory to hold bitmapinfoheader and color table
	if(!(hDIB = GlobalAlloc(GMEM_FIXED,dwLen)))
	{
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;
	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;
	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if(bi.biSizeImage == 0)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;
		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if(dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}
	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if(handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else
	{
		GlobalFree(hDIB);
		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(),
		0L,               // Start scan line
		(DWORD)bi.biHeight,       // # of scan lines
		(LPBYTE)lpbi          // address for bitmap bits
		+ (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi,       // address of bitmapinfo
		(DWORD)DIB_RGB_COLORS);       // Use RGB for color table

	if(!bGotBits)
	{
		GlobalFree(hDIB);
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	ReleaseDC(NULL,hDC);
	return hDIB;
};



// WriteDIB     - Writes a DIB to file
// Returns      - TRUE on success
// szFile       - Name of file to write to
// hDIB         - Handle of the DIB
BOOL CAppUtil::WriteDIB(LPTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER    hdr;
	LPBITMAPINFOHEADER  lpbi;

	if(!hDIB)
		return FALSE;

	CFile file;
	if(!file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;
	int nColors = 1 << lpbi->biBitCount;
	// Fill in the fields of the file header 
	hdr.bfType      = ((WORD) ('M' << 8) | 'B');    // is always "BM"
	hdr.bfSize      = (DWORD)GlobalSize (hDIB) + sizeof(hdr);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits   = (DWORD) (sizeof( hdr ) + lpbi->biSize + nColors * sizeof(RGBQUAD));

	// Write the file header 
	file.Write(&hdr, sizeof(hdr));
	// Write the DIB header and the bits 
	file.Write(lpbi, (UINT)GlobalSize(hDIB));
	return TRUE;
};

BOOL CAppUtil::WriteBitmap(LPTSTR szFullPath, CBitmap* pBitmap, DWORD dwCompression)
{
	HANDLE hDIB = DDBToDIB(*pBitmap, dwCompression, NULL);

	if(hDIB == NULL)
		return FALSE;

	WriteDIB(szFullPath, hDIB);
	CloseHandle(hDIB);
	return TRUE;
}


DWORD CAppUtil::GetFileSize(LPCTSTR sPathName)
{
	HANDLE	hFile;
	DWORD	dwSize;
	hFile = ::CreateFile(sPathName, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(hFile==INVALID_HANDLE_VALUE) return 0;
	dwSize = ::GetFileSize(hFile, NULL);
	CloseHandle(hFile);
	return dwSize;
}

BOOL CAppUtil::CopyFilesinDirectory(CString szSourceDir , CString szDesDir)
{
	CString		szString;
	CFileFind	fileFind;
	CString     szPath(szSourceDir);
	CString     szFind;

	if(szPath.GetAt(szPath.GetLength()-1) == '\\')
		szFind      = szPath + _T("*.*");
	else
		szFind      = szPath + _T("\\*.*");

	BOOL bContinue = fileFind.FindFile(szFind);
	while (bContinue)
	{
		bContinue = fileFind.FindNextFile();
		if (fileFind.IsDots())
			continue;

		if (fileFind.IsDirectory())
		{
			szString = fileFind.GetFilePath();
			CopyFilesinDirectory(szString,szDesDir);

		}
		else
		{
			szString = fileFind.GetFileName();
			CString szSrcFile, szDesFile;
			if(szSourceDir.GetAt(szSourceDir.GetLength()-1) == '\\')
			{
				szSrcFile = szSourceDir + _T("\\") + szString;
			}else
			{
				szSrcFile = szSourceDir + szString;
			}

			if(szDesDir.GetAt(szDesDir.GetLength()-1) == '\\')
			{
				szDesFile = szDesDir + _T("\\") + szString;
			}else
			{
				szDesFile = szDesDir + szString;
			}
			if(!CAppUtil::CreateFullDir(szDesDir))
			{
				//				LOG_ERR(0);
			}

			::CopyFile(szSrcFile,szDesFile,TRUE);
		}
	}
	return TRUE;
}
BOOL CAppUtil::DeleteFilesInDirectory(LPCTSTR pathname)
{
	CString		szString;
	CFileFind	fileFind;
	CString     szPath(pathname);
	CString     szFind;
	BOOL bRet = TRUE;

	if(szPath.GetAt(szPath.GetLength()-1) == '\\')
		szFind      = szPath + _T("*.*");
	else
		szFind      = szPath + _T("\\*.*");

	BOOL bContinue = fileFind.FindFile(szFind);
	while (bContinue)
	{
		bContinue = fileFind.FindNextFile();
		if (fileFind.IsDots())
			continue;

		if (fileFind.IsDirectory())
		{
			szString = fileFind.GetFilePath();
			DeleteFilesInDirectory(szString);
			if (RemoveDirectory(szString) == 0)
			{
				//				DisplayGetLastErrorMessage();
			}
		}
		else
		{
			szString = fileFind.GetFileName();
			bRet = DeleteFile(szPath + _T("\\") + szString);
		}
	}

	return bRet;
}



//! 파일 크기를 늘리는 함수
int CAppUtil::increaseFileSize(const HANDLE file, const __int64 size)
{
	LARGE_INTEGER li;
	li.QuadPart = size;

	if( !SetFilePointerEx(file, li, NULL, FILE_END) ||
		!SetEndOfFile(file) )
	{
		return GetLastError();
	}

	return 0;
}

//! 파일 핸들을 받아 복사하는 함수
int CAppUtil::copyFileUsingMapping(HANDLE srcHandle, HANDLE destHandle)
{
	int retCode = 0;

	HANDLE srcMap, destMap;
	unsigned char* srcView, *destView;

	srcMap = destMap = NULL;
	srcView = destView = NULL;

	LARGE_INTEGER li;
	size_t size = 131072;    // 128KB 씩 맵핑하여 사용할 것임. 이 것은 64KB의 배수이여야 함.
	LARGE_INTEGER li2;

	li.QuadPart = 0;
	SetFilePointerEx(destHandle, li, NULL, FILE_BEGIN);
	SetEndOfFile(destHandle);

	if (!GetFileSizeEx(srcHandle, &li))
	{
		ASSERT(0);
		retCode = -4;   // 소스의 파일 크기를 얻어 올 수 없음.
		goto exit_copyFileUsingMapping;
	}

	if (0 != increaseFileSize(destHandle, li.QuadPart))
	{
		ASSERT(0);
		retCode = -5;   // 파일 크기를 증가 시킬 수 없음.
		goto exit_copyFileUsingMapping;
	}

	srcMap = CreateFileMapping(srcHandle, NULL, PAGE_READONLY, 0, 0, NULL);
	destMap = CreateFileMapping(destHandle, NULL, PAGE_READWRITE, 0, 0, NULL);

	if( INVALID_HANDLE_VALUE == srcMap || NULL == srcMap ||
		INVALID_HANDLE_VALUE == destMap || NULL == destMap )
	{
		ASSERT(0);
		retCode = -6;   // FileMapping을 생성할 수 없음
		goto exit_copyFileUsingMapping;
	}

	//	size_t size = 131072;    // 128KB 씩 맵핑하여 사용할 것임. 이 것은 64KB의 배수이여야 함.
	//  LARGE_INTEGER li2;

	li2.QuadPart = 0;
	while (li.QuadPart > 0)
	{
		if (li.QuadPart < 131072) size = 0;

		srcView = (unsigned char *) MapViewOfFile(srcMap, FILE_MAP_READ, li2.HighPart, li2.LowPart, size);
		destView = (unsigned char *) MapViewOfFile(destMap, FILE_MAP_WRITE, li2.HighPart, li2.LowPart, size);

		if (NULL == srcView || NULL == destView)
		{
			ASSERT(0);
			retCode = -7;  // MapView 생성 못 함.
			goto exit_copyFileUsingMapping;
		}

		if (0 == size) size = size_t( li.QuadPart );
		memcpy(destView, srcView, (0 == size ? size_t( li.QuadPart ) : size));

		UnmapViewOfFile(srcView);  srcView = NULL;
		UnmapViewOfFile(destView);  destView = NULL;

		li.QuadPart -= size;
		li2.QuadPart += size;
	}

exit_copyFileUsingMapping:
	if (NULL != srcView) UnmapViewOfFile(srcView);
	if (NULL != destView) UnmapViewOfFile(destView);

	if (INVALID_HANDLE_VALUE != srcMap && NULL != srcMap) CloseHandle(srcMap);
	if (INVALID_HANDLE_VALUE != destMap && NULL != destMap) CloseHandle(destMap);

	return retCode;
}

//! 파일 경로을 받아 복사하는 함수. overwrite가 true이면 덮어쓰기
int CAppUtil::FastFileCopy(LPCTSTR src, LPCTSTR dest, const bool overwrite)
{
	int retCode = 0;

	HANDLE srcHandle, destHandle;

	srcHandle = CreateFile( src,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
		NULL );
	if (INVALID_HANDLE_VALUE == srcHandle)
	{
		ASSERT(0);
		retCode = -1; // Source 파일 열 수 없음.
		goto exit_pt;
	}

	destHandle = CreateFile(dest,
		GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
		NULL );
	if (!overwrite && INVALID_HANDLE_VALUE != destHandle)
	{
		ASSERT(0);
		retCode = -2;  // 파일이 이미 있어 overwrite 할 수 없음.
		goto exit_pt;
	}

	if (INVALID_HANDLE_VALUE == destHandle || NULL == destHandle)
	{
		destHandle = CreateFile(dest,
			GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
			NULL );
		if (INVALID_HANDLE_VALUE == destHandle)
		{
			ASSERT(0);
			retCode = -3;  // 복사 될 곳을 열 수 없음.
			goto exit_pt;
		}
	}

	retCode = copyFileUsingMapping(srcHandle, destHandle);

exit_pt:
	if (INVALID_HANDLE_VALUE != srcHandle && NULL != srcHandle)
		CloseHandle(srcHandle);
	if (INVALID_HANDLE_VALUE != destHandle && NULL != destHandle)
		CloseHandle(destHandle);

	return retCode;
}


void CAppUtil::DisplayGetLastErrorMessage(void)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.	

	MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

int CAppUtil::axtoi(const TCHAR* value) 
{
	const int HexMapL = 16;
	struct _tagHexMap
	{
		char chr;
		int value;
	} HexMap[16] =
	{
		{'0', 0}, {'1', 1},
		{'2', 2}, {'3', 3},
		{'4', 4}, {'5', 5},
		{'6', 6}, {'7', 7},
		{'8', 8}, {'9', 9},
		{'A', 10}, {'B', 11},
		{'C', 12}, {'D', 13},
		{'E', 14}, {'F', 15}
	};

	// char *mstr = _tcsupr(_tcsdup(value));
	const TCHAR *s = value;
	int result    = 0;
	int firsttime = 1;
	int found = 0;
	int i = 0;

	if (*s == '0' && *(s + 1) == 'X') s += 2;
	if (*s == '0' && *(s + 1) == 'x') s += 2;
	while (*s != '\0')
	{
		found = 0;
		for (i = 0; i < HexMapL; i++)
		{
			if (*s == HexMap[i].chr)
			{
				if (!firsttime) result <<= 4;
				result |= HexMap[i].value;
				found = 1;
				break;
			}
		}
		if (!found) break;
		s++;
		firsttime = 0;
	}
	// free(mstr);
	return result;
}

//20090422 Mingi HBITMAP의 배열을 반대로 바꿔줌.(상하 좌우 바뀐 이미지를 원상복귀)
void CAppUtil::InverseBitmap(HBITMAP hDIB)
{
	DIBSECTION ds;
    GetObject(hDIB, sizeof(DIBSECTION), &ds);

 

    DWORD cbHBytes = HBYTES(ds.dsBmih.biWidth, ds.dsBmih.biBitCount);
	if(ds.dsBmih.biBitCount == 24) {
		for(int y = 0; y < ds.dsBmih.biHeight; y++) {
			RGBTRIPLE* pPixel = (RGBTRIPLE*)((LPBYTE)ds.dsBm.bmBits + y * cbHBytes);
			RGBTRIPLE pTemp;
			for(int x = 0; x < ds.dsBmih.biWidth / 2; x++) {
				pTemp.rgbtBlue  = pPixel[x].rgbtBlue;
				pTemp.rgbtGreen = pPixel[x].rgbtGreen;
				pTemp.rgbtRed   = pPixel[x].rgbtRed;

				pPixel[x].rgbtBlue  = pPixel[(ds.dsBmih.biWidth - 1) - x].rgbtBlue;
				pPixel[x].rgbtGreen = pPixel[(ds.dsBmih.biWidth - 1) - x].rgbtGreen;
				pPixel[x].rgbtRed   = pPixel[(ds.dsBmih.biWidth - 1) - x].rgbtRed;

				pPixel[(ds.dsBmih.biWidth - 1) - x].rgbtBlue  = pTemp.rgbtBlue;
				pPixel[(ds.dsBmih.biWidth - 1) - x].rgbtGreen = pTemp.rgbtGreen;
				pPixel[(ds.dsBmih.biWidth - 1) - x].rgbtRed   = pTemp.rgbtRed;

				}
			}
		
		int last = ds.dsBmih.biHeight * ds.dsBmih.biWidth - 1;
    for(int p = 0; p < last / 2; p++) {
        int x = p % ds.dsBmih.biWidth;
        int y = p / ds.dsBmih.biWidth;
        RGBTRIPLE* p1 = (RGBTRIPLE*)((LPBYTE)ds.dsBm.bmBits + y * cbHBytes) + x;
        x = (last - p) % ds.dsBmih.biWidth;
        y = (last - p) / ds.dsBmih.biWidth;
        RGBTRIPLE* p2 = (RGBTRIPLE*)((LPBYTE)ds.dsBm.bmBits + y * cbHBytes) + x;
        RGBTRIPLE tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        }
		}
    else if(ds.dsBmih.biBitCount == 32) {
	}
}

HBITMAP CAppUtil::GetHBITMAP(LPBYTE lpData, LPBITMAPINFOHEADER lpBih)
{
	if( !lpData || !lpBih )
		return NULL;

	HDC        hMemDC = CreateCompatibleDC(NULL);
	LPVOID     pBit32 = NULL;;

	BITMAPINFO bitmapinfo;
	memset( &bitmapinfo, 0, sizeof(BITMAPINFO) );
	memcpy( &bitmapinfo.bmiHeader, lpBih, sizeof(BITMAPINFOHEADER) );

	HBITMAP hBmp = CreateDIBSection(hMemDC, &bitmapinfo, DIB_RGB_COLORS, &pBit32, NULL, 0);
	if (pBit32) memcpy(pBit32, lpData, lpBih->biSizeImage);

	DeleteDC(hMemDC);
	return hBmp;

}
