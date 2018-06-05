// cpuid.cpp 
// processor: x86, x64
// Use the __cpuid intrinsic to get information about a CPU

#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
#include <intrin.h>
//#include <tchar.h>
#include "cpuID.h"

const TCHAR* szFeatures[] =
{
	_T("x87 FPU On Chip"),
	_T("Virtual-8086 Mode Enhancement"),
	_T("Debugging Extensions"),
	_T("Page Size Extensions"),
	_T("Time Stamp Counter"),
	_T("RDMSR and WRMSR Support"),
	_T("Physical Address Extensions"),
	_T("Machine Check Exception"),
	_T("CMPXCHG8B Instruction"),
	_T("APIC On Chip"),
	_T("Unknown1"),
	_T("SYSENTER and SYSEXIT"),
	_T("Memory Type Range Registers"),
	_T("PTE Global Bit"),
	_T("Machine Check Architecture"),
	_T("Conditional Move/Compare Instruction"),
	_T("Page Attribute Table"),
	_T("Page Size Extension"),
	_T("Processor Serial Number"),
	_T("CFLUSH Extension"),
	_T("Unknown2"),
	_T("Debug Store"),
	_T("Thermal Monitor and Clock Ctrl"),
	_T("MMX Technology"),
	_T("FXSAVE/FXRSTOR"),
	_T("SSE Extensions"),
	_T("SSE2 Extensions"),
	_T("Self Snoop"),
	_T("Hyper-threading Technology"),
	_T("Thermal Monitor"),
	_T("Unknown4"),
	_T("Pend. Brk. EN.")
};

int SpaceFilter( char* pSrc, int nSize );

BOOL GetCPU_ID( int* pCpuInfo, int& nSize )
{
	int CPUInfo         [   4] = {-1};
	__cpuid(CPUInfo, 0);
	unsigned nIds = CPUInfo[0];
	if( nIds < 1 )
		return FALSE;

	__cpuid(CPUInfo, 1);
	if( nSize < 4 )
		return FALSE;

	nSize = 4;
	memcpy( pCpuInfo, CPUInfo, sizeof(int)*4 );

	return TRUE;
}

HRESULT GetCPU_ID( char* pCPUID, int nSize)
{
	HRESULT hr                 = E_FAIL;
	char CPUString     [0x20]  = { 0};
	char CPUBrandString[0x40]  = { 0};
	int CPUInfo         [   4] = {-1};
	int nSteppingID            = 0;
	int nModel                 = 0;
	int nFamily                = 0;
	int nProcessorType         = 0;
	int nExtendedmodel         = 0;
	int nExtendedfamily        = 0;
	int nBrandIndex            = 0;
	int nCLFLUSHcachelinesize  = 0;
	int nAPICPhysicalID        = 0;
	int nFeatureInfo           = 0;
	int nCacheLineSize         = 0;
	int nL2Associativity       = 0;
	int nCacheSizeK            = 0;
	int nRet                   = 0;
	unsigned    nIds, nExIds, i;
	bool    bSSE3NewInstructions    = false;
	bool    bMONITOR_MWAIT          = false;
	bool    bCPLQualifiedDebugStore = false;
	bool    bThermalMonitor2        = false;


	// __cpuid with an InfoType argument of 0 returns the number of
	// valid Ids in CPUInfo[0] and the CPU identification string in
	// the other three array elements. The CPU identification string is
	// not in linear order. The code below arranges the information 
	// in a human readable form.
	__cpuid(CPUInfo, 0);
	nIds = CPUInfo[0];
	memset(CPUString, 0, sizeof(CPUString));
	*((int*)(CPUString  )) = CPUInfo[1];
	*((int*)(CPUString+4)) = CPUInfo[3];
	*((int*)(CPUString+8)) = CPUInfo[2];

	// Get the information associated with each valid Id
	for (i=0; i<=nIds; ++i)
	{
		__cpuid(CPUInfo, i);

		// Interpret CPU feature information.
		if  (i == 1)
		{
			nSteppingID             =  (CPUInfo[0]      ) & 0xf;
			nModel                  =  (CPUInfo[0] >>  4) & 0xf;
			nFamily                 =  (CPUInfo[0] >>  8) & 0xf;
			nProcessorType          =  (CPUInfo[0] >> 12) & 0x3;
			nExtendedmodel          =  (CPUInfo[0] >> 16) & 0xf;
			nExtendedfamily         =  (CPUInfo[0] >> 20) & 0xff;
			nBrandIndex             =  (CPUInfo[1]      ) & 0xff;
			nCLFLUSHcachelinesize   = ((CPUInfo[1] >>  8) & 0xff) * 8;
			nAPICPhysicalID         =  (CPUInfo[1] >> 24) & 0xff;
			bSSE3NewInstructions    =  (CPUInfo[2] & 0x1  ) || false;
			bMONITOR_MWAIT          =  (CPUInfo[2] & 0x8  ) || false;
			bCPLQualifiedDebugStore =  (CPUInfo[2] & 0x10 ) || false;
			bThermalMonitor2        =  (CPUInfo[2] & 0x100) || false;
			nFeatureInfo            =   CPUInfo[3];
		}
	}

	// Calling __cpuid with 0x80000000 as the InfoType argument
	// gets the number of valid extended IDs.
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	memset( CPUBrandString, 0, sizeof(CPUBrandString));

	// Get the information associated with each extended ID.
	for (i=0x80000000; i<=nExIds; ++i)
	{
		__cpuid(CPUInfo, i);

		// Interpret CPU brand string and cache information.
		if      (i == 0x80000002)
			memcpy(CPUBrandString     , CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000006)
		{
			nCacheLineSize   = (CPUInfo[2]      ) & 0xff  ;
			nL2Associativity = (CPUInfo[2] >> 12) & 0xf   ;
			nCacheSizeK      = (CPUInfo[2] >> 16) & 0xffff;
		}
	}

	if  (nExIds >= 0x80000004)
	{
		hr = S_OK;

		int nRstSize = SpaceFilter( CPUBrandString, (int)strlen(CPUBrandString) );

		int nCpySize = min( (nSize-1), nRstSize );
		memcpy( pCPUID, CPUBrandString, sizeof(char)*nCpySize );

		*(pCPUID + nCpySize + 1 ) = 0;
		//printf_s("\nCPU Brand String: %s\n", CPUBrandString);
	}

	return  hr;
}

int SpaceFilter( char* pSrc, int nSize )
{
//	char pTmp = new char[nSize];
	char szTmp[MAX_PATH] = {0};
//	memset( pTmp, 0, sizeof(TCHAR)*nSize );

	int    nCopyedSize = 0;
	char*  pItorDst = szTmp;
	char*  pItorSrc = pSrc;
	char*  pItorSrcEnd = pSrc+nSize;
	BOOL   bSpaceFlag = FALSE;

	while( (pItorSrc<pItorSrcEnd) && (*pItorSrc) )
	{
		if( *pItorSrc != ' ' )
		{
			*pItorDst  = *pItorSrc;
			bSpaceFlag = FALSE;
			pItorDst++; nCopyedSize++;
		}
		else if( (bSpaceFlag==FALSE) && *pItorSrc == ' ' )
		{
			*pItorDst  = *pItorSrc;
			bSpaceFlag = TRUE;
			pItorDst++; nCopyedSize++;
		}
		else if( (bSpaceFlag==TRUE) && *pItorSrc != ' ' )
		{
			*pItorDst  = *pItorSrc;
			bSpaceFlag = FALSE;
			pItorDst++; nCopyedSize++;
		}
		else if( (bSpaceFlag==TRUE) && *pItorSrc == ' ' )
		{
			;
		}
		pItorSrc++;
	}

	memset( pSrc, 0, sizeof(char)*nSize );
	memcpy( pSrc, szTmp, sizeof(char)*nCopyedSize );

//	delete[] pTmp;
//	pTmp = NULL;

	return nCopyedSize;
}

/*
int main(int argc, char* argv[])
{
	TCHAR CPUString     [0x20] = { 0};
	TCHAR CPUBrandString[0x40] = { 0};
	int CPUInfo         [   4] = {-1};
	int nSteppingID            = 0;
	int nModel                 = 0;
	int nFamily                = 0;
	int nProcessorType         = 0;
	int nExtendedmodel         = 0;
	int nExtendedfamily        = 0;
	int nBrandIndex            = 0;
	int nCLFLUSHcachelinesize  = 0;
	int nAPICPhysicalID        = 0;
	int nFeatureInfo           = 0;
	int nCacheLineSize         = 0;
	int nL2Associativity       = 0;
	int nCacheSizeK            = 0;
	int nRet                   = 0;
	unsigned    nIds, nExIds, i;
	bool    bSSE3NewInstructions    = false;
	bool    bMONITOR_MWAIT          = false;
	bool    bCPLQualifiedDebugStore = false;
	bool    bThermalMonitor2        = false;


	// __cpuid with an InfoType argument of 0 returns the number of
	// valid Ids in CPUInfo[0] and the CPU identification string in
	// the other three array elements. The CPU identification string is
	// not in linear order. The code below arranges the information 
	// in a human readable form.
	__cpuid(CPUInfo, 0);
	nIds = CPUInfo[0];
	memset(CPUString, 0, sizeof(CPUString));
	*((int*)(CPUString  )) = CPUInfo[1];
	*((int*)(CPUString+4)) = CPUInfo[3];
	*((int*)(CPUString+8)) = CPUInfo[2];

	// Get the information associated with each valid Id
	for (i=0; i<=nIds; ++i)
	{
		__cpuid(CPUInfo, i);
		//printf_s("\nFor InfoType %d\n", i); 
		//printf_s("CPUInfo[0] = 0x%x\n", CPUInfo[0]);
		//printf_s("CPUInfo[1] = 0x%x\n", CPUInfo[1]);
		//printf_s("CPUInfo[2] = 0x%x\n", CPUInfo[2]);
		//printf_s("CPUInfo[3] = 0x%x\n", CPUInfo[3]);

		// Interpret CPU feature information.
		if  (i == 1)
		{
			nSteppingID             =  (CPUInfo[0]      ) & 0xf;
			nModel                  =  (CPUInfo[0] >>  4) & 0xf;
			nFamily                 =  (CPUInfo[0] >>  8) & 0xf;
			nProcessorType          =  (CPUInfo[0] >> 12) & 0x3;
			nExtendedmodel          =  (CPUInfo[0] >> 16) & 0xf;
			nExtendedfamily         =  (CPUInfo[0] >> 20) & 0xff;
			nBrandIndex             =  (CPUInfo[1]      ) & 0xff;
			nCLFLUSHcachelinesize   = ((CPUInfo[1] >>  8) & 0xff) * 8;
			nAPICPhysicalID         =  (CPUInfo[1] >> 24) & 0xff;
			bSSE3NewInstructions    =  (CPUInfo[2] & 0x1  ) || false;
			bMONITOR_MWAIT          =  (CPUInfo[2] & 0x8  ) || false;
			bCPLQualifiedDebugStore =  (CPUInfo[2] & 0x10 ) || false;
			bThermalMonitor2        =  (CPUInfo[2] & 0x100) || false;
			nFeatureInfo            =   CPUInfo[3];
		}
	}

	// Calling __cpuid with 0x80000000 as the InfoType argument
	// gets the number of valid extended IDs.
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	memset(CPUBrandString, 0, sizeof(CPUBrandString));

	// Get the information associated with each extended ID.
	for (i=0x80000000; i<=nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		//printf_s("\nFor InfoType %x\n", i); 
		//printf_s("CPUInfo[0] = 0x%x\n", CPUInfo[0]);
		//printf_s("CPUInfo[1] = 0x%x\n", CPUInfo[1]);
		//printf_s("CPUInfo[2] = 0x%x\n", CPUInfo[2]);
		//printf_s("CPUInfo[3] = 0x%x\n", CPUInfo[3]);

		// Interpret CPU brand string and cache information.
		if      (i == 0x80000002)
			memcpy(CPUBrandString     , CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000006)
		{
			nCacheLineSize   = (CPUInfo[2]      ) & 0xff  ;
			nL2Associativity = (CPUInfo[2] >> 12) & 0xf   ;
			nCacheSizeK      = (CPUInfo[2] >> 16) & 0xffff;
		}
	}

	// Display all the information in user-friendly format.
	printf_s("\n\nCPU String: %s\n", CPUString);

	if  (nIds >= 1)
	{
		if  (nSteppingID)
			printf_s("Stepping ID = %d\n", nSteppingID);
		if  (nModel)
			printf_s("Model = %d\n", nModel);
		if  (nFamily)
			printf_s("Family = %d\n", nFamily);
		if  (nProcessorType)
			printf_s("Processor Type = %d\n", nProcessorType);
		if  (nExtendedmodel)
			printf_s("Extended model = %d\n", nExtendedmodel);
		if  (nExtendedfamily)
			printf_s("Extended family = %d\n", nExtendedfamily);
		if  (nBrandIndex)
			printf_s("Brand Index = %d\n", nBrandIndex);
		if  (nCLFLUSHcachelinesize)
			printf_s("CLFLUSH cache line size = %d\n",
			nCLFLUSHcachelinesize);
		if  (nAPICPhysicalID)
			printf_s("APIC Physical ID = %d\n", nAPICPhysicalID);

		if  (nFeatureInfo || bSSE3NewInstructions ||
			bMONITOR_MWAIT || bCPLQualifiedDebugStore ||
			bThermalMonitor2)
		{
			printf_s("\nThe following features are supported:\n");

			if  (bSSE3NewInstructions)
				printf_s("\tSSE3 New Instructions\n");
			if  (bMONITOR_MWAIT)
				printf_s("\tMONITOR/MWAIT\n");
			if  (bCPLQualifiedDebugStore)
				printf_s("\tCPL Qualified Debug Store\n");
			if  (bThermalMonitor2)
				printf_s("\tThermal Monitor 2\n");

			i = 0;
			nIds = 1;
			while (i < (sizeof(szFeatures)/sizeof(const char*)))
			{
				if  (nFeatureInfo & nIds)
				{
					printf_s("\t");
					printf_s(szFeatures[i]);
					printf_s("\n");
				}

				nIds <<= 1;
				++i;
			}
		}
	}
	if  (nExIds >= 0x80000004)
		printf_s("\nCPU Brand String: %s\n", CPUBrandString);


	if  (nExIds >= 0x80000006)
	{
		printf_s("Cache Line Size = %d\n" , nCacheLineSize  );
		printf_s("L2 Associativity = %d\n", nL2Associativity);
		printf_s("Cache Size = %dK\n"     , nCacheSizeK     );
	}

	return  nRet;
}
*/