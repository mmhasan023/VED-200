#ifndef _LOCK_BY_SYSTEM_H_INCLUDE_
#define _LOCK_BY_SYSTEM_H_INCLUDE_

extern BOOL GetLockInitInfo( TCHAR* pInfo, int nSize );
extern BOOL CheckLockInfo  ( TCHAR* pInfo, int nSize );
extern int  GetPhysicalDriveNumber (void);

#endif //_LOCK_BY_SYSTEM_H_INCLUDE_