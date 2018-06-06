// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef WINVER 
#define WINVER  0x0400
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
//#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define CALL_CDECL
#include "./../../include/iplApi.h"

#include "./../cximage/ximage.h"

#if defined(_DEBUG)
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "../png/Debug/png.lib")
#pragma comment(lib, "../jpeg/Debug/jpeg.lib")
#pragma comment(lib, "../zlib/Debug/zlib.lib")
#pragma comment(lib, "../tiff/Debug/tiff.lib")
#pragma comment(lib, "../jbig/Debug/jbig.lib")
#pragma comment(lib, "../jasper/Debug/jasper.lib")
#pragma comment(lib, "../mng/Debug/mng.lib")
#pragma comment(lib, "../cximage/Debug/cximage.lib")
#else
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "./../png/Release/png.lib")
#pragma comment(lib, "./../jpeg/Release/jpeg.lib")
#pragma comment(lib, "./../zlib/Release/zlib.lib")
#pragma comment(lib, "./../tiff/Release/tiff.lib")
#pragma comment(lib, "./../jbig/Release/jbig.lib")
#pragma comment(lib, "./../jasper/Release/jasper.lib")
#pragma comment(lib, "./../mng/Release/mng.lib")
#pragma comment(lib, "./../cximage/Release/cximage.lib")
#endif


HCORNERDETECT _IPL_API _IPL_CALL _iplCornerDetectOpen   ( int nWidth, int nHeight, int nBarrier );
int           _IPL_API _IPL_CALL _iplCornerDetect       ( HCORNERDETECT  hCorner, const BYTE* pBuffer, VECTOR_POINT& vectorPOINT );
int           _IPL_API _IPL_CALL _iplCornerDetectBlock  ( HCORNERDETECT  hCorner, const BYTE* pBuffer, VECTOR_POINT& vectorPOINT );
BOOL          _IPL_API _IPL_CALL _iplCornerDetectClose  ( HCORNERDETECT& hCorner );

int _IPL_API _IPL_CALL _ipl_corner_detect               (IN const BYTE* pBuffer, int nWidth, int nHeight, VECTOR_POINT& vectorLPPOINT, int nBarrier=30);
