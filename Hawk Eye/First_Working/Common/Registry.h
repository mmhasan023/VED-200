#ifndef	___REGISTRY_H____
#define ___REGISTRY_H____

#include <winreg.h>

#define REG_RECT	0x0001
#define REG_POINT	0x0002

class CRegistry : public CObject
{
// Construction
public:

	CRegistry(HKEY hKeyRoot = HKEY_CURRENT_USER);
	virtual ~CRegistry();

	struct REGINFO
	{
		LONG  lMessage;
		DWORD dwType  ;
		DWORD dwSize  ;
	} m_Info;

// Operations
public:
	void DisplayGetLastErrorMessage(void);

public:
	HKEY GetHKey	 (void                          );
	BOOL VerifyKey	 (HKEY hKeyRoot, LPCTSTR pszPath);
	BOOL VerifyKey	 (LPCTSTR pszPath               );
	BOOL VerifyValue (LPCTSTR pszValue              );
	BOOL CreateKey	 (HKEY hKeyRoot, LPCTSTR pszPath);

	BOOL Open		 (HKEY hKeyRoot, LPCTSTR pszPath, REGSAM samDesired = KEY_ALL_ACCESS);
	void Close		 (void);

	BOOL DeleteValue (LPCTSTR pszValue);
	BOOL DeleteValue (LPCTSTR pszPath, LPCTSTR pszValue);
	BOOL DeleteValue (HKEY hRootKey, LPCTSTR pszPath, LPCTSTR pszValue);

	
	BOOL DeleteValueKey (HKEY hKeyRoot, LPCTSTR pszPath);
	BOOL DeleteKey		(HKEY hKeyRoot, LPCTSTR pszPath);

	BOOL Write (LPCTSTR pszKey, int				iVal        );
	BOOL Write (LPCTSTR pszKey, long			lVal        );
	BOOL Write (LPCTSTR pszKey, DWORD			dwVal       );
	BOOL Write (LPCTSTR pszKey, LPCTSTR			pszVal      );
	BOOL Write (LPCTSTR pszKey, CStringList&	scStringList);
	BOOL Write (LPCTSTR pszKey, CByteArray&		bcArray     );
	BOOL Write (LPCTSTR pszKey, CStringArray&	scArray     );
	BOOL Write (LPCTSTR pszKey, CDWordArray&	dwcArray    );
	BOOL Write (LPCTSTR pszKey, CWordArray&		wcArray     );
	BOOL Write (LPCTSTR pszKey, LPCRECT			rcRect      );
	BOOL Write (LPCTSTR pszKey, LPPOINT&		lpPoint     );

	BOOL Read (LPCTSTR pszKey, int&				iVal        );
	BOOL Read (LPCTSTR pszKey, long&			lVal        );
	BOOL Read (LPCTSTR pszKey, DWORD&			dwVal       );
	BOOL Read (LPCTSTR pszKey, CString&			sVal        );
	BOOL Read (LPCTSTR pszKey, CStringList&		scStringList);
	BOOL Read (LPCTSTR pszKey, CStringArray&	scArray     );
	BOOL Read (LPCTSTR pszKey, CDWordArray&		dwcArray    );
	BOOL Read (LPCTSTR pszKey, CWordArray&		wcArray     );
	BOOL Read (LPCTSTR pszKey, CByteArray&		bcArray     );
	BOOL Read (LPCTSTR pszKey, LPPOINT&			lpPoint     );
	BOOL Read (LPCTSTR pszKey, LPRECT&			rcRect      );

protected:	
	HKEY 	m_hKey;
	CString m_szPath;
};
#endif