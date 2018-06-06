#include "stdafx.h"
#include "cpuID.h"
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")

#include <winioctl.h>

#include "macaddresslist.h"
#include "LockBySystem.h"

BOOL GetMACaddress( LPVECTOR_MACADDRESS lpvMacAddress )
{
	IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information 
	// for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(      // Call GetAdapterInfo
		AdapterInfo,                 // [out] buffer to receive data
		&dwBufLen);                  // [in] size of receive data buffer
	if( dwStatus != ERROR_SUCCESS ) return FALSE;  // Verify return value is 
	// valid, no buffer overflow

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to

	// current adapter info
	do {
		lpvMacAddress->push_back( CMacAddress( pAdapterInfo->Address ) );
		//PrintMACaddress(pAdapterInfo->Address); // Print MAC address
		pAdapterInfo = pAdapterInfo->Next;    // Progress through 
		// linked list
	}
	while(pAdapterInfo);                    // Terminate if last adapter

	return TRUE;
}


// Fetches the MAC address and prints it
BOOL GetMACaddressSingle( BYTE* pMacAddress, int nSize )//nSize=MAX_ADAPTER_ADDRESS_LENGTH
{
	IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information 
	// for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(      // Call GetAdapterInfo
		AdapterInfo,                 // [out] buffer to receive data
		&dwBufLen);                  // [in] size of receive data buffer
	if( dwStatus != ERROR_SUCCESS ) return FALSE;  // Verify return value is 
	// valid, no buffer overflow

	if( nSize < MAX_ADAPTER_ADDRESS_LENGTH ) return FALSE;

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to
	memcpy( pMacAddress, pAdapterInfo->Address, sizeof(BYTE)*MAX_ADAPTER_ADDRESS_LENGTH );

	// current adapter info
//	do {
//		PrintMACaddress(pAdapterInfo->Address); // Print MAC address
//		pAdapterInfo = pAdapterInfo->Next;    // Progress through 
//		// linked list
//	}
//	while(pAdapterInfo);                    // Terminate if last adapter
	return TRUE;
}

void MixNumber( int& nNum )
{
	int nTmp = ( nNum & 0xE0000000 )>>29;

	nNum = (nNum<<3) | nTmp;
}

void MixInfoString( int nFirst, int nSecond, int* pCpuInfo, TCHAR* pString, int nSize )
{
	MixNumber(nFirst );
	MixNumber(nSecond);
	MixNumber(nSecond);
	MixNumber(pCpuInfo[0]);
	MixNumber(pCpuInfo[1]);
	MixNumber(pCpuInfo[1]);
	MixNumber(pCpuInfo[2]);
	MixNumber(pCpuInfo[2]);
	MixNumber(pCpuInfo[3]);

	pCpuInfo[1] = pCpuInfo[1] & 0x3FFFFFF0 ;//상위 두비트 제거, 수시로 변화하는 요소

	_stprintf( pString, _T("%08X%08X%08X%08X%08X%08X"), 
		nFirst, pCpuInfo[0], pCpuInfo[1], nSecond, pCpuInfo[2], pCpuInfo[3] );
}

BOOL GetLockInitInfo( TCHAR* pInfo, int nSize )
{
	TCHAR szMsg[MAX_PATH]={0};

	int nCpuInfo[4]={0};
	int nCpuSize = 4;
	if( GetCPU_ID( nCpuInfo, nCpuSize ) == FALSE )
	{
		return FALSE;
	}

	BYTE byteMacAddress[MAX_ADAPTER_ADDRESS_LENGTH]={0};
	if( GetMACaddressSingle(byteMacAddress, MAX_ADAPTER_ADDRESS_LENGTH) == FALSE )
	{
		return FALSE;
	}

	int nFirst  = 0;
	int nSecond = 0;
	memcpy( (void*)&nFirst , (void*)byteMacAddress, sizeof(int) );
	memcpy( (void*)&nSecond, (void*)(byteMacAddress+4), sizeof(int) );

	MixInfoString( nFirst, nSecond, nCpuInfo, szMsg, MAX_PATH );

	int nRstLen = int(_tcslen(szMsg));
	int nCount  = nRstLen%8;

	while( nCount )
	{
		szMsg[nRstLen++]= 'K';
	}

	nRstLen = int(_tcslen(szMsg));
	if( nSize < nRstLen )
		return FALSE;

	_tcscpy( pInfo, szMsg );
	return TRUE;
}

BOOL CheckLockInfo  ( TCHAR* pInfo, int nSize )
{
	int nCpuInfo[4]={0};
	int nCpuSize = 4;
	if( GetCPU_ID( nCpuInfo, nCpuSize ) == FALSE )
	{
		return FALSE;
	}

	VECTOR_MACADDRESS vMacAddress;
	if( GetMACaddress( &vMacAddress ) == FALSE )
	{
		return FALSE;
	}

	VECTOR_MACADDRESSIter iter = vMacAddress.begin();

	while( iter != vMacAddress.end() )
	{
		BYTE *pMacAddress = (*iter).byteData;

		TCHAR szMsg[MAX_PATH]={0};
		int nFirst  = 0;
		int nSecond = 0;
		memcpy( (void*)&nFirst , (void*) pMacAddress   , sizeof(int) );
		memcpy( (void*)&nSecond, (void*)(pMacAddress+4), sizeof(int) );

		MixInfoString( nFirst, nSecond, nCpuInfo, szMsg, MAX_PATH );

		int nRstLen = int(_tcslen(szMsg));
		int nCount  = nRstLen%8;
		while( nCount )
		{
			szMsg[nRstLen++]= 'K';
		}

		if( _tcscmp( pInfo, szMsg ) == 0 )
			return TRUE;

		iter++;
	}

	return FALSE;
}

#define MAX_IDE_DRIVES 16   
typedef struct _MEDIA_SERAL_NUMBER_DATA    
{   
	ULONG SerialNumberLength;    
	ULONG Result;   
	ULONG Reserved[2];   
	UCHAR SerialNumberData[1];   
} MEDIA_SERIAL_NUMBER_DATA, *PMEDIA_SERIAL_NUMBER_DATA;

TCHAR *flipAndCodeBytes (TCHAR * str)   
{   
	static TCHAR flipped [1000];   
	int num = int(_tcslen(str));   
	_tcscpy (flipped, _T("") );

	for (int i = 0; i < num; i += 4)   
	{   
		for (int j = 1; j >= 0; j--)   
		{   
			int sum = 0;   
			for (int k = 0; k < 2; k++)   
			{   
				sum *= 16;   
				switch (str [i + j * 2 + k])   
				{   
				case '0': sum += 0; break;   
				case '1': sum += 1; break;   
				case '2': sum += 2; break;   
				case '3': sum += 3; break;   
				case '4': sum += 4; break;   
				case '5': sum += 5; break;   
				case '6': sum += 6; break;   
				case '7': sum += 7; break;   
				case '8': sum += 8; break;   
				case '9': sum += 9; break;   
				case 'a': sum += 10; break;   
				case 'b': sum += 11; break;   
				case 'c': sum += 12; break;   
				case 'd': sum += 13; break;   
				case 'e': sum += 14; break;   
				case 'f': sum += 15; break;   
				}   
			}   
			if (sum > 0)   
			{   
				TCHAR sub [2];   
				sub [0] = (TCHAR) sum;   
				sub [1] = 0;   
				_tcscat (flipped, sub);   
			}   
		}   
	}   
	return flipped;   
}   

int GetPhysicalDriveNumber (void)   
{   
	TCHAR serialNumber [100];   
	int done = FALSE;   
	int drive = 0;   
	for (drive = 0; drive < MAX_IDE_DRIVES; drive++)   
	{   
		HANDLE hPhysicalDriveIOCTL = 0;   

		TCHAR driveName [256];   
		_stprintf (driveName, _T("<A>\\\\.\\PhysicalDrive%d</A>"), drive);   

		hPhysicalDriveIOCTL = CreateFile (driveName, 0,   
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,   
			OPEN_EXISTING, 0, NULL);   

		if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)   
		{   
			STORAGE_PROPERTY_QUERY query;   
			DWORD cbBytesReturned = 0;   
			char buffer [10000];   
			memset ((void *) &query, 0, sizeof (query));   
			query.PropertyId = StorageDeviceProperty;   
			query.QueryType = PropertyStandardQuery;   
			memset (buffer, 0, sizeof (buffer));   
			if ( DeviceIoControl (hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,   
				&query,   
				sizeof (query),   
				&buffer,   
				sizeof (buffer),   
				&cbBytesReturned, NULL) )   
			{   
				STORAGE_DEVICE_DESCRIPTOR * descrip = (STORAGE_DEVICE_DESCRIPTOR *) &   
				buffer;   
				_tcscpy (serialNumber, flipAndCodeBytes ( (TCHAR*)&buffer[descrip->SerialNumberOffset] ) );   
			}   
			else  
			{   
				DWORD err = GetLastError ();   
			}   
			memset (buffer, 0, sizeof (buffer));   
			if ( DeviceIoControl (hPhysicalDriveIOCTL,    
				IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER,   
				NULL,   
				0,   
				&buffer,   
				sizeof (buffer),   
				&cbBytesReturned, NULL) )   
			{   
				MEDIA_SERIAL_NUMBER_DATA * mediaSerialNumber = (MEDIA_SERIAL_NUMBER_DATA *)    
					&buffer;   
				_tcscpy (serialNumber, (TCHAR*)mediaSerialNumber->SerialNumberData);    
			}   
			else  
			{   
				DWORD err = GetLastError ();   
			}   
			CloseHandle (hPhysicalDriveIOCTL);   
		}   
	}   
	return 0;   
}  
