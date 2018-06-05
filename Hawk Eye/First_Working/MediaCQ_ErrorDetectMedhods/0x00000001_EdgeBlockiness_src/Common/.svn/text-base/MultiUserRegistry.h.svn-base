// MultiUserRegistry.h: interface for the CMultiUserRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIUSERREGISTRY_H__20118DFC_9075_47F4_A346_6310682FD7C0__INCLUDED_)
#define AFX_MULTIUSERREGISTRY_H__20118DFC_9075_47F4_A346_6310682FD7C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Common/Registry.h"

class CMultiUserRegistry : public CRegistry  
{
public:
	
	CMultiUserRegistry();
	virtual ~CMultiUserRegistry();


	BOOL Write(CString strRegPath, CString strKey, LPPOINT&			lpPoint     );
	BOOL Write(CString strRegPath, CString strKey, LPCRECT			rcRect      );
	BOOL Write(CString strRegPath, CString strKey, CWordArray&		wcArray     );
	BOOL Write(CString strRegPath, CString strKey, CDWordArray&		dwcArray    );
	BOOL Write(CString strRegPath, CString strKey, CStringArray&	scArray     );
	BOOL Write(CString strRegPath, CString strKey, CByteArray&		bcArray     );
	BOOL Write(CString strRegPath, CString strKey, CStringList&		scStringList);
	BOOL Write(CString strRegPath, CString strKey, LPCTSTR			pszVal      );
	BOOL Write(CString strRegPath, CString strKey, DWORD			dwVal       );
	BOOL Write(CString strRegPath, CString strKey, int				iVal        );
	BOOL Write(CString strRegPath, CString strKey, long				lVal        );
	BOOL Write(HKEY key, CString strRegPath, CString strKey, LPCTSTR pszVal);
	

	BOOL Read(CString strRegPath, CString strKey, LPRECT&			rcRect      );
	BOOL Read(CString strRegPath, CString strKey, LPPOINT&			lpPoint     );
	BOOL Read(CString strRegPath, CString strKey, CByteArray&		bcArray     );
	BOOL Read(CString strRegPath, CString strKey, CWordArray&		wcArray     );
	BOOL Read(CString strRegPath, CString strKey, CDWordArray&		dwcArray    );
	BOOL Read(CString strRegPath, CString strKey, CStringArray&		scArray     );
	BOOL Read(CString strRegPath, CString strKey, CStringList&		scStringList);
	BOOL Read(CString strRegPath, CString strKey, CString&			sVal        );
	BOOL Read(CString strRegPath, CString strKey, DWORD&			dwVal       );
	BOOL Read(CString strRegPath, CString strKey, int&				iVal        );
	BOOL Read(CString strRegPath, CString strKey, long&				lVal        );
	BOOL Read(HKEY key, CString strRegPath, CString strKey, CString &sVal);

	LONG RecursiveRegDeleteKey( HKEY hKey, LPTSTR pszSubkey );
};

#endif // !defined(AFX_MULTIUSERREGISTRY_H__20118DFC_9075_47F4_A346_6310682FD7C0__INCLUDED_)
