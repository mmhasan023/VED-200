// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

// �Ʒ� ������ �÷����� �켱�ϴ� �÷����� ������� �ϴ� ��� ���� ���Ǹ� �����Ͻʽÿ�.
// �ٸ� �÷����� ���Ǵ� �ش� ���� �ֽ� ������ MSDN�� �����Ͻʽÿ�.
#ifndef WINVER				// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define WINVER 0x0501		// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINNT		// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.                   
#define _WIN32_WINNT 0x0501	// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINDOWS 0x0410 // Windows Me �̻� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_IE			// IE 6.0 �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_IE 0x0600	// �ٸ� ������ IE�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE Ŭ�����Դϴ�.
#include <afxodlgs.h>       // MFC OLE ��ȭ ���� Ŭ�����Դϴ�.
#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC �����ͺ��̽� Ŭ�����Դϴ�.
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO �����ͺ��̽� Ŭ�����Դϴ�.
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma warning(disable:4995)
#pragma warning(disable:4996)

#ifdef _LOGDATA

#include "../../common/cximage/include/ximage.h"

#ifdef WIN64
	#pragma comment(lib, "../../common/cximage/libU_x64/cximage.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/jasper.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/jbig.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/Jpeg.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/libdcr.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/mng.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/png.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/Tiff.lib")
	#pragma comment(lib, "../../common/cximage/libU_x64/zlib.lib")
#else
	#pragma comment(lib, "../../common/cximage/libU/cximage.lib")
	#pragma comment(lib, "../../common/cximage/libU/jasper.lib")
	#pragma comment(lib, "../../common/cximage/libU/jbig.lib")
	#pragma comment(lib, "../../common/cximage/libU/Jpeg.lib")
	#pragma comment(lib, "../../common/cximage/libU/libdcr.lib")
	#pragma comment(lib, "../../common/cximage/libU/mng.lib")
	#pragma comment(lib, "../../common/cximage/libU/png.lib")
	#pragma comment(lib, "../../common/cximage/libU/Tiff.lib")
	#pragma comment(lib, "../../common/cximage/libU/zlib.lib")
#endif
#endif

#ifdef _LOGDATA
#define _SHORT_TERM_PROCESS_LOG
#endif