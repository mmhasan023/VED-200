////////////////////////////////////////////////////////////////////
// Copyright (C) 2010, SafeNet, Inc. All rights reserved.
//
// HASP(R) is a registered trademark of SafeNet, Inc. 
//
//
// $Id: haspmain.cpp,v 1.10 2010-06-08 05:31:20 pwang Exp $
////////////////////////////////////////////////////////////////////
#if defined(WIN32) && defined(_USRDLL)

#include "hasp_api_cpp_.h"


////////////////////////////////////////////////////////////////////
// DLL entry point
////////////////////////////////////////////////////////////////////

BOOL APIENTRY DllMain(HANDLE /* hModule */, 
                      DWORD  /* dwReason */, 
                      LPVOID /* lpReserved */)
{
    return TRUE;
}

#endif // WIN32 && _USRDLL
