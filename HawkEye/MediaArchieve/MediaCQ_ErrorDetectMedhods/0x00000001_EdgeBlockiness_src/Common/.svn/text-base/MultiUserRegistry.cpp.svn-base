// MultiUserRegistry.cpp: implementation of the CMultiUserRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MultiUserRegistry.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMultiUserRegistry::CMultiUserRegistry()
{
}

CMultiUserRegistry::~CMultiUserRegistry()
{
}



BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, int &iVal)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	iVal);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey, iVal);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, long &lVal)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	lVal);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey, lVal);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, DWORD &dwVal)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	dwVal);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		dwVal);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(HKEY key, CString strRegPath, CString strKey, CString &sVal)
{
	BOOL bRead = FALSE;

	CRegistry regUser;

	if (regUser.Open(key, strRegPath,KEY_READ))
	{
		if (regUser.Read(strKey, sVal))
		{
			bRead = TRUE;			
		}
		regUser.Close();
	}

	return bRead;
}


BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, CString &sVal)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	sVal);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		sVal);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}


BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, CStringList &scStringList)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	scStringList);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		scStringList);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, CStringArray &scArray)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	scArray);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		scArray);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, CDWordArray &dwcArray)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	dwcArray);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		dwcArray);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, CWordArray &wcArray)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser = regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead = FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	wcArray);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		wcArray);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, CByteArray &bcArray)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	bcArray);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		bcArray);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, LPPOINT &lpPoint)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	lpPoint);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		lpPoint);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Read(CString strRegPath, CString strKey, LPRECT &rcRect)
{
	CRegistry regUser, regLocal;

	BOOL bOpenUser	= regUser.Open(HKEY_CURRENT_USER, strRegPath,KEY_READ);
	BOOL bRead		= FALSE;
	if (bOpenUser)
		bRead = regUser.Read(strKey,	rcRect);
	else
		bRead = FALSE;

	if (!bRead)
	{
		if (regLocal.Open(HKEY_LOCAL_MACHINE, strRegPath,KEY_READ))
			bRead = regLocal.Read(strKey,		rcRect);
	}

	regUser.Close();
	regLocal.Close();

	return bRead;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, int iVal)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	iVal);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, long lVal)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	lVal);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, DWORD dwVal)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	dwVal);

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, LPCTSTR pszVal)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	pszVal);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, CStringList &scStringList)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	scStringList);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, CByteArray &bcArray)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	bcArray);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, CStringArray &scArray)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	scArray);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, CDWordArray &dwcArray)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	dwcArray);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, CWordArray &wcArray)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	wcArray);	

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, LPCRECT rcRect)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	rcRect);

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(CString strRegPath, CString strKey, LPPOINT &lpPoint)
{
	CRegistry regUser;

	if (!regUser.Open(HKEY_CURRENT_USER, strRegPath))
	{
		if (!regUser.CreateKey(HKEY_CURRENT_USER, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	lpPoint);

	regUser.Close();

	return bWrite;
}

BOOL CMultiUserRegistry::Write(HKEY key, CString strRegPath, CString strKey, LPCTSTR pszVal)
{
	CRegistry regUser;

	if (!regUser.Open(key, strRegPath))
	{
		if (!regUser.CreateKey(key, strRegPath))
			return FALSE;
	}

	BOOL bWrite = regUser.Write(strKey,	pszVal);	

	regUser.Close();

	return bWrite;
}


LONG CMultiUserRegistry::RecursiveRegDeleteKey( HKEY hKey, LPTSTR pszSubkey )
{
    HKEY hSubkey;

    LONG result = RegOpenKeyEx( hKey, pszSubkey, 0,
                                KEY_ENUMERATE_SUB_KEYS | DELETE, &hSubkey );

    while ( ERROR_SUCCESS == result )
    {
        TCHAR szSubkey[ MAX_PATH ];
        DWORD cbSubkeySize = _tcslen(szSubkey);
        
        result = RegEnumKeyEx(  hSubkey, 0, szSubkey, &cbSubkeySize,
                                0, 0, 0, 0);

        if ( ERROR_NO_MORE_ITEMS == result )
            break;

        if ( ERROR_SUCCESS != result )
            return result;

        result = RecursiveRegDeleteKey( hSubkey, szSubkey );
    }

    RegCloseKey( hSubkey );
    result = RegDeleteKey( hKey, pszSubkey );

    return result;
}