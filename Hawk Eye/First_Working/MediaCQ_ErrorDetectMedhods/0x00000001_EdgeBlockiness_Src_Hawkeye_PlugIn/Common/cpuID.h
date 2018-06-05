// cpuID.h
// processor: x86, x64
// Use the __cpuid intrinsic to get information about a CPU
// by kiokahn, 20101029
#ifndef _CPU_INCORAMATION_H_INCLUDE_
#define _CPU_INCORAMATION_H_INCLUDE_

extern HRESULT GetCPU_ID( char* pCPUID, int nSize);
extern BOOL    GetCPU_ID( int* pCpuInfo, int& nSize );

#endif