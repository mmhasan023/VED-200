//DetecBlackFrame.cpp
#include "stdafx.h"
#include "DetecBlackFrame.h"
#include "MAUtil.h"
#include "iplFrameEx.h"
#include "math.h"
#define BLACK_TIME				60000000

#define BLOCK_SIZE 8
#ifdef _OPENMP
#include "omp.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


       
#ifdef _LOGDATA
	#include "apputil.h"
	#include <time.h>
	#include "tchar.h"
	#include <mmsystem.h>
	#pragma comment(lib,"winmm.lib")

	CString g_szLogPath;
	#define _LOGPATH _T("\\CQ_API\\BlackFrame")

	void init_log(void)
	{
		//g_szLogPath = CAppUtil::GetMainPath();
		g_szLogPath = CAppUtil::GetUserDataPath();

		//		g_szLogPath.Delete(g_szLogPath.GetLength()-1,1);
		//		while(g_szLogPath.Right(1)!=_T("\\") && g_szLogPath.GetLength() )
		//			g_szLogPath.Delete(g_szLogPath.GetLength()-1,1);

		g_szLogPath += _LOGPATH;
		CAppUtil::CreateFullDir(g_szLogPath);

		g_szLogPath += _T("\\");

		CTime time = CTime::GetCurrentTime();
		CString szFile;
		szFile.Format(_T("%d_%d_%d_%d_%d_%d.txt"), time.GetYear(), time.GetMonth(), time.GetDay(),
			time.GetHour(), time.GetMinute(), time.GetSecond());
		g_szLogPath += szFile;
	}

	void LOGMSG(TCHAR *szMsg, ... )
	{
		FILE *fFile = NULL;
		if( (fFile = _tfopen(g_szLogPath, _T("a+") )) == NULL )
			return;

		va_list marker;
		TCHAR szTmp[2048];
		memset(szTmp,0,2048*sizeof(TCHAR));

		va_start( marker ,szMsg );  
		_vstprintf(szTmp,szMsg, marker);
		va_end( marker );             

		char szMessage[2048];
		memset(szMessage,0,2048*sizeof(char));
	#ifdef _UNICODE
		int AnsiStrSize = WideCharToMultiByte(CP_ACP, 0, szTmp, -1, NULL, 0, NULL, NULL); 
		WideCharToMultiByte(CP_ACP, 0, szTmp, -1, szMessage, AnsiStrSize, 0, 0);
	#else
		strcpy_s(szMessage, szTmp);
	#endif
		fseek(fFile,0,SEEK_END);
		fwrite(szMessage,strlen(szMessage),1,fFile);
		fwrite("\r\n",strlen("\r\n"),1,fFile);

		fclose(fFile);
	}
#endif


UINT  CalNh (LPBYTE lpLine1,  LPBYTE lpLine2,	LPBYTE lpLine3,	LPBYTE lpLine4,	LPBYTE lpLine5,	LPBYTE lpLine6,	LPBYTE lpLine7,	LPBYTE lpLine8,	int nBlockSize,	  int nGamma1 = 10)
{
	UINT  nNh = abs( *(lpLine1)  - *(lpLine1-1) ) +
		        abs( *(lpLine2)  - *(lpLine2-1) ) +
				abs( *(lpLine3)  - *(lpLine3-1) ) +
				abs( *(lpLine4)  - *(lpLine4-1) ) +
				abs( *(lpLine5)  - *(lpLine5-1) ) +
				abs( *(lpLine6)  - *(lpLine6-1) ) +
				abs( *(lpLine7)  - *(lpLine7-1) ) +
				abs( *(lpLine8)  - *(lpLine8-1) ) ;

	return nNh*nGamma1;
}


float CalDh (LPBYTE lpLine1,  LPBYTE lpLine2,	LPBYTE lpLine3,	LPBYTE lpLine4,	LPBYTE lpLine5,	LPBYTE lpLine6,	LPBYTE lpLine7,	LPBYTE lpLine8,	int nBlockSize, float nGamma2 = 1.5)

{
	float nDh= nGamma2* (
	abs( *(lpLine1-3)  - *(lpLine1-4) )+abs( *(lpLine1-2)  - *(lpLine1-3) )+abs( *(lpLine1-1)  - *(lpLine1-2) )+abs( *(lpLine1+1)  - *(lpLine1) )+abs( *(lpLine1+2)  - *(lpLine1+1) )+abs( *(lpLine1+3)  - *(lpLine1+2) )+
	abs( *(lpLine2-3)  - *(lpLine2-4) )+abs( *(lpLine2-2)  - *(lpLine2-3) )+abs( *(lpLine2-1)  - *(lpLine2-2) )+abs( *(lpLine2+1)  - *(lpLine2) )+abs( *(lpLine2+2)  - *(lpLine2+1) )+abs( *(lpLine2+3)  - *(lpLine2+2) )+		
	abs( *(lpLine3-3)  - *(lpLine3-4) )+abs( *(lpLine3-2)  - *(lpLine3-3) )+abs( *(lpLine3-1)  - *(lpLine3-2) )+abs( *(lpLine3+1)  - *(lpLine3) )+abs( *(lpLine3+2)  - *(lpLine3+1) )+abs( *(lpLine3+3)  - *(lpLine3+2) )+
	abs( *(lpLine4-3)  - *(lpLine4-4) )+abs( *(lpLine4-2)  - *(lpLine4-3) )+abs( *(lpLine4-1)  - *(lpLine4-2) )+abs( *(lpLine4+1)  - *(lpLine4) )+abs( *(lpLine4+2)  - *(lpLine4+1) )+abs( *(lpLine4+3)  - *(lpLine4+2) )+
	abs( *(lpLine5-3)  - *(lpLine5-4) )+abs( *(lpLine5-2)  - *(lpLine5-3) )+abs( *(lpLine5-1)  - *(lpLine5-2) )+abs( *(lpLine5+1)  - *(lpLine5) )+abs( *(lpLine5+2)  - *(lpLine5+1) )+abs( *(lpLine5+3)  - *(lpLine5+2) )+
	abs( *(lpLine6-3)  - *(lpLine6-4) )+abs( *(lpLine6-2)  - *(lpLine6-3) )+abs( *(lpLine6-1)  - *(lpLine6-2) )+abs( *(lpLine6+1)  - *(lpLine6) )+abs( *(lpLine6+2)  - *(lpLine6+1) )+abs( *(lpLine6+3)  - *(lpLine6+2) )+
	abs( *(lpLine7-3)  - *(lpLine7-4) )+abs( *(lpLine7-2)  - *(lpLine7-3) )+abs( *(lpLine7-1)  - *(lpLine7-2) )+abs( *(lpLine7+1)  - *(lpLine7) )+abs( *(lpLine7+2)  - *(lpLine7+1) )+abs( *(lpLine7+3)  - *(lpLine7+2) )+
	abs( *(lpLine8-3)  - *(lpLine8-4) )+abs( *(lpLine8-2)  - *(lpLine8-3) )+abs( *(lpLine8-1)  - *(lpLine8-2) )+abs( *(lpLine8+1)  - *(lpLine8) )+abs( *(lpLine8+2)  - *(lpLine8+1) )+abs( *(lpLine8+3)  - *(lpLine8+2) )
	)+(
	abs( *(lpLine1)	   - *(lpLine1-1) )+
	abs( *(lpLine2)    - *(lpLine2-1) )+
	abs( *(lpLine3)    - *(lpLine3-1) )+
	abs( *(lpLine4)    - *(lpLine4-1) )+
	abs( *(lpLine5)    - *(lpLine5-1) )+
	abs( *(lpLine6)    - *(lpLine6-1) )+
	abs( *(lpLine7)    - *(lpLine7-1) )+ 
	abs( *(lpLine8)    - *(lpLine8-1) )		) ;

	return nDh;
		


}

UINT  CalNv (LPBYTE lpLine1up,LPBYTE IpLine1,   int nBlockSize, int nGamma1 = 10)
{
	UINT  nNv = abs( *(IpLine1++)  - *(lpLine1up++) ) +
		        abs( *(IpLine1++)  - *(lpLine1up++) ) +
				abs( *(IpLine1++)  - *(lpLine1up++) ) +
				abs( *(IpLine1++)  - *(lpLine1up++) ) +
				abs( *(IpLine1++)  - *(lpLine1up++) ) +
				abs( *(IpLine1++)  - *(lpLine1up++) ) +
				abs( *(IpLine1++)  - *(lpLine1up++) ) +
				abs( *(IpLine1++)  - *(lpLine1up++) ) ;

	return nNv*nGamma1;
}


float CalDv (LPBYTE lpLine4up,LPBYTE  lpLine3up,LPBYTE lpLine2up,LPBYTE  lpLine1up,LPBYTE  lpLine1,LPBYTE  lpLine2,LPBYTE  lpLine3,LPBYTE  lpLine4, int nBlockSize, float nGamma2 = 1.5)

{
	  float nDv= nGamma2* 
	  ( 
	  abs( *(lpLine4up ) - *(lpLine3up) )	  +  abs( *(lpLine4up+1 ) - *(lpLine3up+1) ) +  abs( *(lpLine4up+2 ) - *(lpLine3up+2) ) +  abs( *(lpLine4up+3 ) - *(lpLine3up+3) ) +
	  abs( *(lpLine4up+4 ) - *(lpLine3up+4) ) +  abs( *(lpLine4up+5 ) - *(lpLine3up+5) ) +  abs( *(lpLine4up+6 ) - *(lpLine3up+6) ) +  abs( *(lpLine4up+7 ) - *(lpLine3up+7) ) +
	  
	  abs( *(lpLine3up ) - *(lpLine2up) )	  +  abs( *(lpLine3up+1 ) - *(lpLine2up+1) ) +  abs( *(lpLine3up+2 ) - *(lpLine2up+2) ) +  abs( *(lpLine3up+3)  - *(lpLine2up+3) ) +
	  abs( *(lpLine3up+4 ) - *(lpLine2up+4) ) +  abs( *(lpLine3up+5 ) - *(lpLine2up+5) ) +  abs( *(lpLine3up+6 ) - *(lpLine2up+6) ) +  abs( *(lpLine3up+7)  - *(lpLine2up+7) ) +
	  
	  abs( *(lpLine2up ) - *(lpLine1up) )	  +  abs( *(lpLine2up+1 ) - *(lpLine1up+1) ) +  abs( *(lpLine2up+2 ) - *(lpLine1up+2) ) +  abs( *(lpLine2up+3 ) - *(lpLine1up+3) ) +
	  abs( *(lpLine2up+4 ) - *(lpLine1up+4) ) +  abs( *(lpLine2up+5 ) - *(lpLine1up+5) ) +  abs( *(lpLine2up+6 ) - *(lpLine1up+6) ) +  abs( *(lpLine2up+7 ) - *(lpLine1up+7) ) +
	
	  abs( *(lpLine2   ) - *(lpLine1  ) )	  +  abs( *(lpLine2+1   ) - *(lpLine1+1  ) ) +  abs( *(lpLine2+2   ) - *(lpLine1+2  ) ) +  abs( *(lpLine2+3   ) - *(lpLine1+3  ) ) +
	  abs( *(lpLine2+4   ) - *(lpLine1+4  ) ) +  abs( *(lpLine2+5   ) - *(lpLine1+5  ) ) +  abs( *(lpLine2+6   ) - *(lpLine1+6  ) ) +  abs( *(lpLine2+7   ) - *(lpLine1+7  ) ) +
	  
	  abs( *(lpLine3   ) - *(lpLine2  ) )	  +  abs( *(lpLine3+1   ) - *(lpLine2+1  ) ) +  abs( *(lpLine3+2   ) - *(lpLine2+2  ) ) +  abs( *(lpLine3+3   ) - *(lpLine2+3  ) ) +  
	  abs( *(lpLine3+4   ) - *(lpLine2+4  ) ) +  abs( *(lpLine3+5   ) - *(lpLine2+5  ) ) +  abs( *(lpLine3+6   ) - *(lpLine2+6  ) ) +  abs( *(lpLine3+7   ) - *(lpLine2+7  ) ) +  

	  abs( *(lpLine4   ) - *(lpLine3  ) )	  +  abs( *(lpLine4+1   ) - *(lpLine3+1  ) ) +  abs( *(lpLine4+2   ) - *(lpLine3+2  ) ) +  abs( *(lpLine4+3   ) - *(lpLine3+3  ) ) +  
	  abs( *(lpLine4+4   ) - *(lpLine3+4  ) ) +  abs( *(lpLine4+5   ) - *(lpLine3+5  ) ) +  abs( *(lpLine4+6   ) - *(lpLine3+6  ) ) +  abs( *(lpLine4+7   ) - *(lpLine3+7  ) )   
	  
	  )
	+
	(
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) ) +
	abs( *(lpLine1++)  - *(lpLine1up++) )   
	);
	
	return nDv;

}


UINT CalZ(LPBYTE IpLineOne, LPBYTE IpLineTwo)
{
	UINT z =0;
	UINT Result = abs( (int)(*IpLineOne) - (int)(*IpLineTwo) );

	if (Result==0)
		z =1;
	else
		z =0;

	return z;



}


float CalZh(LPBYTE lpLine1,LPBYTE lpLine2,LPBYTE lpLine3,LPBYTE lpLine4,LPBYTE lpLine5,LPBYTE lpLine6,LPBYTE lpLine7,LPBYTE lpLine8, int nBlockSize)

{
		float fZh = 0;

		fZh = (10.f/56.f) * ( 
		
		CalZ( (lpLine1-3), (lpLine1-4) ) + CalZ( (lpLine1-2), (lpLine1-3) ) + CalZ( (lpLine1-1), (lpLine1-2) ) + CalZ( (lpLine1+1), (lpLine1) ) + CalZ( (lpLine1+2), (lpLine1+1) ) + CalZ( (lpLine1+3), (lpLine1+2) ) +
		CalZ( (lpLine2-3), (lpLine2-4) ) + CalZ( (lpLine2-2), (lpLine2-3) ) + CalZ( (lpLine2-1), (lpLine2-2) ) + CalZ( (lpLine2+1), (lpLine2) ) + CalZ( (lpLine2+2), (lpLine2+1) ) + CalZ( (lpLine2+3), (lpLine2+2) ) +
		CalZ( (lpLine3-3), (lpLine3-4) ) + CalZ( (lpLine3-2), (lpLine3-3) ) + CalZ( (lpLine3-1), (lpLine3-2) ) + CalZ( (lpLine3+1), (lpLine3) ) + CalZ( (lpLine3+2), (lpLine3+1) ) + CalZ( (lpLine3+3), (lpLine3+2) ) +
		CalZ( (lpLine4-3), (lpLine4-4) ) + CalZ( (lpLine4-2), (lpLine4-3) ) + CalZ( (lpLine4-1), (lpLine4-2) ) + CalZ( (lpLine4+1), (lpLine4) ) + CalZ( (lpLine4+2), (lpLine4+1) ) + CalZ( (lpLine4+3), (lpLine4+2) ) +
		CalZ( (lpLine5-3), (lpLine5-4) ) + CalZ( (lpLine5-2), (lpLine5-3) ) + CalZ( (lpLine5-1), (lpLine5-2) ) + CalZ( (lpLine5+1), (lpLine5) ) + CalZ( (lpLine5+2), (lpLine5+1) ) + CalZ( (lpLine5+3), (lpLine5+2) ) +
		CalZ( (lpLine6-3), (lpLine6-4) ) + CalZ( (lpLine6-2), (lpLine6-3) ) + CalZ( (lpLine6-1), (lpLine6-2) ) + CalZ( (lpLine6+1), (lpLine6) ) + CalZ( (lpLine6+2), (lpLine6+1) ) + CalZ( (lpLine6+3), (lpLine6+2) ) +
		CalZ( (lpLine7-3), (lpLine7-4) ) + CalZ( (lpLine7-2), (lpLine7-3) ) + CalZ( (lpLine7-1), (lpLine7-2) ) + CalZ( (lpLine7+1), (lpLine7) ) + CalZ( (lpLine7+2), (lpLine7+1) ) + CalZ( (lpLine7+3), (lpLine7+2) ) +
		CalZ( (lpLine8-3), (lpLine8-4) ) + CalZ( (lpLine8-2), (lpLine8-3) ) + CalZ( (lpLine8-1), (lpLine8-2) ) + CalZ( (lpLine8+1), (lpLine8) ) + CalZ( (lpLine8+2), (lpLine8+1) ) + CalZ( (lpLine8+3), (lpLine8+2) ) 
		) 
		+
		(10.f/56.f) * (
		CalZ( (lpLine1), (lpLine1-1) )+
		CalZ( (lpLine2), (lpLine2-1) )+
		CalZ( (lpLine3), (lpLine3-1) )+
		CalZ( (lpLine4), (lpLine4-1) )+
		CalZ( (lpLine5), (lpLine5-1) )+
		CalZ( (lpLine6), (lpLine6-1) )+
		CalZ( (lpLine7), (lpLine7-1) )+
		CalZ( (lpLine8), (lpLine8-1) )

		);

		return fZh;


}


float CalZv(LPBYTE lpLine4up,LPBYTE lpLine3up,LPBYTE lpLine2up,LPBYTE lpLine1up,LPBYTE lpLine1,LPBYTE lpLine2,LPBYTE lpLine3,LPBYTE lpLine4, int nBlockSize)
{
	  float fZv = 0;

	  fZv= (10.f/56.f) *  (
	  CalZ( (lpLine4up ),(lpLine3up) )    + CalZ( (lpLine4up+1 ),(lpLine3up+1) )+ CalZ( (lpLine4up+2 ),(lpLine3up+2) )+ CalZ( (lpLine4up+3 ),(lpLine3up+3) )+
	  CalZ( (lpLine4up+4),(lpLine3up+4) ) + CalZ( (lpLine4up+5 ),(lpLine3up+5) )+ CalZ( (lpLine4up+6 ),(lpLine3up+6) )+ CalZ( (lpLine4up+7 ),(lpLine3up+7) )+

		  

	  CalZ( (lpLine3up),(lpLine2up) )    + CalZ( (lpLine3up +1),(lpLine2up+1) )+ CalZ( (lpLine3up +2),(lpLine2up+2) )+ CalZ( (lpLine3up+3 ),(lpLine2up+3) )+	
	  CalZ( (lpLine3up +4),(lpLine2up+4) )+ CalZ( (lpLine3up+5 ),(lpLine2up+5) )+ CalZ( (lpLine3up +6),(lpLine2up+6) )+ CalZ( (lpLine3up+7 ),(lpLine2up+7) )+
	  


	  CalZ( (lpLine2up ),(lpLine1up) )    + CalZ( (lpLine2up+1 ),(lpLine1up+1) )+ CalZ( (lpLine2up+2 ),(lpLine1up+2) )+ CalZ( (lpLine2up+3 ),(lpLine1up+3) )+
	  CalZ( (lpLine2up+4 ),(lpLine1up+4) )+ CalZ( (lpLine2up +5),(lpLine1up+5) )+ CalZ( (lpLine2up+6 ),(lpLine1up+6) )+ CalZ( (lpLine2up+7 ),(lpLine1up+7) )+



	  CalZ( (lpLine2   ),(lpLine1  ) )    + CalZ( (lpLine2 +1  ),(lpLine1+1  ) )+ CalZ( (lpLine2  +2 ),(lpLine1 +2 ) )+ CalZ( (lpLine2  +3 ),(lpLine1 +3 ) )+
      CalZ( (lpLine2 +4  ),(lpLine1 +4 ) )+ CalZ( (lpLine2  +5 ),(lpLine1 +5 ) )+ CalZ( (lpLine2  +6 ),(lpLine1 +6 ) )+ CalZ( (lpLine2   +7),(lpLine1 +7 ) )+
	  

	  CalZ( (lpLine3   ),(lpLine2  ) )    + CalZ( (lpLine3  +1 ),(lpLine2 +1 ) )+ CalZ( (lpLine3  +2 ),(lpLine2 +2 ) )+ CalZ( (lpLine3 +3  ),(lpLine2 +3 ) )+
      CalZ( (lpLine3 +4  ),(lpLine2 +4 ) )+ CalZ( (lpLine3   +5),(lpLine2  +5) )+ CalZ( (lpLine3  +6 ),(lpLine2  +6) )+ CalZ( (lpLine3  +7 ),(lpLine2  +7) )+
	

	  
	  CalZ( (lpLine4   ),(lpLine3  ) )    + CalZ( (lpLine4  +1 ),(lpLine3 +1 ) )+ CalZ( (lpLine4  +2 ),(lpLine3 +2 ) )+ CalZ( (lpLine4  +3 ),(lpLine3  +3) )+
	  CalZ( (lpLine4 +4  ),(lpLine3 +4 ) )+ CalZ( (lpLine4  +5 ),(lpLine3 +5 ) )+ CalZ( (lpLine4  +6 ),(lpLine3 +6 ) )+ CalZ( (lpLine4  +7 ),(lpLine3  +7) )
		

	  )	
	  +
		(10.f/56.f) * (
	  CalZ( (lpLine1  ),(lpLine1up )) +
	  CalZ( (lpLine1+1  ),(lpLine1up+1 )) +
	  CalZ( (lpLine1 +2 ),(lpLine1up+2 )) +
	  CalZ( (lpLine1 +3 ),(lpLine1up+3 )) +
	  CalZ( (lpLine1 +4 ),(lpLine1up+4 )) +
	  CalZ( (lpLine1 +5 ),(lpLine1up+5 )) +
	  CalZ( (lpLine1 +6 ),(lpLine1up+6 )) +
	  CalZ( (lpLine1 +7 ),(lpLine1up+7 ))
	  );
	  
	
 	return fZv;	



}

/*
float CalTJnd(LPBYTE lpLine4up,LPBYTE lpLine3up,LPBYTE lpLine2up,LPBYTE lpLine1up,LPBYTE lpLine1,LPBYTE lpLine2,LPBYTE lpLine3,LPBYTE lpLine4,LPBYTE lpLine5,LPBYTE lpLine6,LPBYTE lpLine7,LPBYTE lpLine8,int nBlockSize, float lambda = .05)
{
		
	
float 	avg =(
		  (*(lpLine1-4)) + (*(lpLine1-3)) + (*(lpLine1-2)) + (*(lpLine1-1)) + (*(lpLine1  )) + (*(lpLine1+1)) + (*(lpLine1+2)) + (*(lpLine1+3)) +
		  (*(lpLine2-4)) + (*(lpLine2-3)) + (*(lpLine2-2)) + (*(lpLine2-1)) + (*(lpLine2  )) + (*(lpLine2+1)) + (*(lpLine2+2)) + (*(lpLine2+3)) +
		  (*(lpLine3-4)) + (*(lpLine3-3)) + (*(lpLine3-2)) + (*(lpLine3-1)) + (*(lpLine3  )) + (*(lpLine3+1)) + (*(lpLine3+2)) + (*(lpLine3+3)) +
		  (*(lpLine4-4)) + (*(lpLine4-3)) + (*(lpLine4-2)) + (*(lpLine4-1)) + (*(lpLine4  )) + (*(lpLine4+1)) + (*(lpLine4+2)) + (*(lpLine4+3)) +
		  (*(lpLine5-4)) + (*(lpLine5-3)) + (*(lpLine5-2)) + (*(lpLine5-1)) + (*(lpLine5  )) + (*(lpLine5+1)) + (*(lpLine5+2)) + (*(lpLine5+3)) +
		  (*(lpLine6-4)) + (*(lpLine6-3)) + (*(lpLine6-2)) + (*(lpLine6-1)) + (*(lpLine6  )) + (*(lpLine6+1)) + (*(lpLine6+2)) + (*(lpLine6+3)) +
		  (*(lpLine7-4)) + (*(lpLine7-3)) + (*(lpLine7-2)) + (*(lpLine7-1)) + (*(lpLine7  )) + (*(lpLine7+1)) + (*(lpLine7+2)) + (*(lpLine7+3)) + 
		  (*(lpLine8-4)) + (*(lpLine8-3)) + (*(lpLine8-2)) + (*(lpLine8-1)) + (*(lpLine8  )) + (*(lpLine8+1)) + (*(lpLine8+2)) + (*(lpLine8+3)) +
		  (*(lpLine1++)) + (*(lpLine1++)) + (*(lpLine1++)) + (*(lpLine1++)) + (*(lpLine1++)) + (*(lpLine1++)) + (*(lpLine1++)) + (*(lpLine1++)) +
		  (*(lpLine2++)) + (*(lpLine2++)) + (*(lpLine2++)) + (*(lpLine2++)) + (*(lpLine2++)) + (*(lpLine2++)) + (*(lpLine2++)) + (*(lpLine2++)) +
		  (*(lpLine3++)) + (*(lpLine3++)) + (*(lpLine3++)) + (*(lpLine3++)) + (*(lpLine3++)) + (*(lpLine3++)) + (*(lpLine3++)) + (*(lpLine3++)) +
		  (*(lpLine4++)) + (*(lpLine4++)) + (*(lpLine4++)) + (*(lpLine4++)) + (*(lpLine4++)) + (*(lpLine4++)) + (*(lpLine4++)) + (*(lpLine4++)) +
		  (*(lpLine5++)) + (*(lpLine5++)) + (*(lpLine5++)) + (*(lpLine5++)) + (*(lpLine5++)) + (*(lpLine5++)) + (*(lpLine5++)) + (*(lpLine5++)) +
		  (*(lpLine6++)) + (*(lpLine6++)) + (*(lpLine6++)) + (*(lpLine6++)) + (*(lpLine6++)) + (*(lpLine6++)) + (*(lpLine6++)) + (*(lpLine6++)) +	
		  (*(lpLine7++)) + (*(lpLine7++)) + (*(lpLine7++)) + (*(lpLine7++)) + (*(lpLine7++)) + (*(lpLine7++)) + (*(lpLine7++)) + (*(lpLine7++)) +
		  (*(lpLine8++)) + (*(lpLine8++)) + (*(lpLine8++)) + (*(lpLine8++)) + (*(lpLine8++)) + (*(lpLine8++)) + (*(lpLine8++)) + (*(lpLine8++)) +
		  (*(lpLine1up++)) +(*(lpLine1up++)) +(*(lpLine1up++)) +(*(lpLine1up++)) +(*(lpLine1up++)) +(*(lpLine1up++)) +(*(lpLine1up++)) +(*(lpLine1up++)) +
		  (*(lpLine2up++)) +(*(lpLine2up++)) +(*(lpLine2up++)) +(*(lpLine2up++)) +(*(lpLine2up++)) +(*(lpLine2up++)) +(*(lpLine2up++)) +(*(lpLine2up++)) +
		  (*(lpLine3up++)) +(*(lpLine3up++)) +(*(lpLine3up++)) +(*(lpLine3up++)) +(*(lpLine3up++)) +(*(lpLine3up++)) +(*(lpLine3up++)) +(*(lpLine3up++)) +
		  (*(lpLine4up++)) +(*(lpLine4up++)) +(*(lpLine4up++)) +(*(lpLine4up++)) +(*(lpLine4up++)) +(*(lpLine4up++)) +(*(lpLine4up++)) +(*(lpLine4up++)) 
		  )/160 ; 

	float Tjnd = lambda * avg;

	return Tjnd ; 

 
} 

*/

float CallBG(LPBYTE LineMiddle, LPBYTE Line1Up, LPBYTE Line2Up, LPBYTE Line1Down , LPBYTE Line2Down)
{
	UINT fBG =	 ((*(LineMiddle))*0)   + ((*(LineMiddle-1))*2)  + ((*(LineMiddle-2))*1)  + ((*(LineMiddle++))*2)     + ((*(LineMiddle++))*1)   +
				 ((*(Line1Up))*2)      + ((*(Line1Up-1))*2)     + ((*(Line1Up-2))*1)     + ((*(Line1Up++))*2)        + ((*(Line1Up++))*1)      +
				 ((*(Line2Up))*1)      + ((*(Line2Up-1))*1)     + ((*(Line2Up-2))*1)     + ((*(Line2Up++))*1)        + ((*(Line2Up++))*1)      +
				 ((*(Line1Down))*2)    + ((*(Line1Down-1))*2)   + ((*(Line1Down-2))*1)   + ((*(Line1Down++))*2)      + ((*(Line1Down++))*1)    +
				 ((*(Line2Down))*1)    + ((*(Line2Down-1))*1)   + ((*(Line2Down-2))*1)   + ((*(Line2Down++))*1)      + ((*(Line2Down++))*1)    ;
																
	return fBG/32.f;
}

float CallMG1(LPBYTE LineMiddle, LPBYTE Line1Up, LPBYTE Line2Up, LPBYTE Line1Down , LPBYTE Line2Down)
{
	float fMG1 =abs(	 ((*(LineMiddle))*0)	  + ((*(LineMiddle-1))*0)    + ((*(LineMiddle-2))*0)    + ((*(LineMiddle++))*0)     + ((*(LineMiddle++))*0)   +
						 ((*(Line1Up))*8)		  + ((*(Line1Up-1))*3)       + ((*(Line1Up-2))*1)       + ((*(Line1Up++))*3)        + ((*(Line1Up++))*1)      +
						 ((*(Line2Up))*0)         + ((*(Line2Up-1))*0)       + ((*(Line2Up-2))*0)       + ((*(Line2Up++))*0)        + ((*(Line2Up++))*0)      +
						 ((*(Line1Down))*(-8))    + ((*(Line1Down-1))*(-3))  + ((*(Line1Down-2))*(-1))  + ((*(Line1Down++))*(-3))   + ((*(Line1Down++))*(-1))    +
						 ((*(Line2Down))*0)       + ((*(Line2Down-1))*0)     + ((*(Line2Down-2))*0)     + ((*(Line2Down++))*0)      + ((*(Line2Down++))*0) )/(float)16   ;
																
	return fMG1;
}

float CallMG2(LPBYTE LineMiddle, LPBYTE Line1Up, LPBYTE Line2Up, LPBYTE Line1Down , LPBYTE Line2Down)
{
	float fMG2 =abs(	 ((*(LineMiddle))*0)	  + ((*(LineMiddle-1))*3)    + ((*(LineMiddle-2))*1)    + ((*(LineMiddle++))*(-3))  + ((*(LineMiddle++))*(-1))   +
						 ((*(Line1Up))*3)		  + ((*(Line1Up-1))*8)       + ((*(Line1Up-2))*0)       + ((*(Line1Up++))*0)        + ((*(Line1Up++))*0)      +
						 ((*(Line2Up))*1)         + ((*(Line2Up-1))*0)       + ((*(Line2Up-2))*0)       + ((*(Line2Up++))*0)        + ((*(Line2Up++))*0)      +
						 ((*(Line1Down))*(-3))    + ((*(Line1Down-1))*(0))   + ((*(Line1Down-2))*(0))   + ((*(Line1Down++))*(-8))   + ((*(Line1Down++))*(0))    +
						 ((*(Line2Down))*(-1))    + ((*(Line2Down-1))*0)     + ((*(Line2Down-2))*0)     + ((*(Line2Down++))*0)      + ((*(Line2Down++))*0) )/(float)16   ;

	return fMG2;
}

float CallMG3(LPBYTE LineMiddle, LPBYTE Line1Up, LPBYTE Line2Up, LPBYTE Line1Down , LPBYTE Line2Down)
{
	float fMG3 =abs(	 ((*(LineMiddle))*0)	  + ((*(LineMiddle-1))*(-3)) + ((*(LineMiddle-2))*(-1)) + ((*(LineMiddle++))*3)     + ((*(LineMiddle++))*1)     +
						 ((*(Line1Up))*3)		  + ((*(Line1Up-1))*0)       + ((*(Line1Up-2))*0)       + ((*(Line1Up++))*8)        + ((*(Line1Up++))*0)        +
						 ((*(Line2Up))*1)         + ((*(Line2Up-1))*0)       + ((*(Line2Up-2))*0)       + ((*(Line2Up++))*0)        + ((*(Line2Up++))*0)        +
						 ((*(Line1Down))*(-3))    + ((*(Line1Down-1))*(-8))  + ((*(Line1Down-2))*(0))   + ((*(Line1Down++))*(0))    + ((*(Line1Down++))*(0))    +
						 ((*(Line2Down))*(-1))    + ((*(Line2Down-1))*0)     + ((*(Line2Down-2))*0)     + ((*(Line2Down++))*0)      + ((*(Line2Down++))*0) )/(float)16   ;
																
	return fMG3;
}

float CallMG4(LPBYTE LineMiddle, LPBYTE Line1Up, LPBYTE Line2Up, LPBYTE Line1Down , LPBYTE Line2Down)
{
	float fMG4 =abs(	 ((*(LineMiddle))*0)	  + ((*(LineMiddle-1))*8)    + ((*(LineMiddle-2))*(0))    + ((*(LineMiddle++))*(-8))     + ((*(LineMiddle++))*0)     +
						 ((*(Line1Up))*0)		  + ((*(Line1Up-1))*3)       + ((*(Line1Up-2))*(0))       + ((*(Line1Up++))*(-3))        + ((*(Line1Up++))*0)        +
						 ((*(Line2Up))*0)         + ((*(Line2Up-1))*1)       + ((*(Line2Up-2))*(0))       + ((*(Line2Up++))*(-1))        + ((*(Line2Up++))*0)        +
						 ((*(Line1Down))*(0))     + ((*(Line1Down-1))*(3))   + ((*(Line1Down-2))*(0))     + ((*(Line1Down++))*(-3))      + ((*(Line1Down++))*(0))    +
						 ((*(Line2Down))*0)       + ((*(Line2Down-1))*1)     + ((*(Line2Down-2))*0)       + ((*(Line2Down++))*(-1))      + ((*(Line2Down++))*0) )/(float)16   ;
																
	return fMG4;
}




float CalJnd(LPBYTE LineMiddle, LPBYTE Line1Up, LPBYTE Line2Up, LPBYTE Line1Down , LPBYTE Line2Down)
{
	 
float f2BG1		= 0;	
float fBG1		= 0;
float fMG1		= 0;
float fAlphaBG1	= 0;
float fBitaBG1  = 0;
float f1BGMG1	= 0;	
float JND		= 0;	

   fBG1      = CallBG(LineMiddle,Line1Up, Line2Up,Line1Down, Line2Down);
		
   fMG1      = max( max(CallMG1(LineMiddle,Line1Up, Line2Up,Line1Down, Line2Down), CallMG2(LineMiddle,Line1Up, Line2Up,Line1Down, Line2Down)), 
                    max(CallMG3(LineMiddle,Line1Up, Line2Up,Line1Down, Line2Down), CallMG4(LineMiddle,Line1Up, Line2Up,Line1Down, Line2Down))	);
						
   fAlphaBG1 = (fBG1*0.0001) + 0.115 ;
   fBitaBG1  = 0.5 - (fBG1*0.01) ;
   f1BGMG1	   = fMG1*fAlphaBG1 + fBitaBG1;

if(fBG1<=127)
{
	f2BG1 = 17.f * (1-sqrt(fBG1/127.f))+3.f ;

}
else
{
	f2BG1 = (3.f/128.f) * (fBG1 - 127.f) +3.f;

}


   JND = max(f1BGMG1, f2BG1);


return JND;		
						
}						

int  Img_show(const LPBYTE pSrc, int nSrcWidth, int nSrcHeight, int nBytes)
	{
	
		if(!pSrc) return FALSE;
		
		BYTE *iDst;

		iDst = pSrc;
			
		return TRUE;
	
	}


BOOL ipl_RGBToGray(OUT LPBYTE pGrayBuffer, IN const LPBYTE pSrc, int nSrcWidth, int nSrcHeight, int nBytes)
	{
		if(nBytes<3) return -1;

		LPBYTE	IpDst= pGrayBuffer;
		LPBYTE	IpSrc= pSrc;
		register int nByteGap = nBytes-3;

		if(nByteGap<0) nByteGap=0;

		int nSize = nSrcHeight*nSrcWidth;
		LPBYTE IpDstEnd = IpDst + nSize;

		BYTE rgbBlue, rgbGreen, rgbRed;

		while(IpDst<IpDstEnd)
		{
			rgbRed =	*(IpSrc++);
			rgbGreen=	*(IpSrc++);
			rgbBlue=	*(IpSrc++);


			*IpDst++=(BYTE)(0.2125f*(float)rgbRed + .7154f*(float)rgbGreen + 0.0721f*(float)rgbBlue);
			//*IpDst++=(*(IpSrc++) + *(IpSrc++) + *(IpSrc++))/3 ;
			IpSrc+=nByteGap;


		}

		return 1;

	}

int ipl_FilterSobelMagnitudeGray(OUT LPBYTE pDstSobel, IN const LPBYTE pSrc, IN int nSrcWidth, IN int nSrcHeight)
	{
		register int nHeight = nSrcHeight;
		register int nWidth = nSrcWidth;
		register int x,y;

		LPBYTE IpDst	= pDstSobel+nWidth;

		LPBYTE IpSrc	= pSrc;
		LPBYTE IpSrcUp	= NULL;
		LPBYTE IpSrcDn	= NULL;

		register BYTE	WN, NN, NE;
		register BYTE	WW, CC, EE;
		register BYTE	SW, SS, ES;

		register int	fGyValue;
		register int	fGxValue;
		int				fsmValue;

		IpSrcUp		= pSrc;
		IpSrc		= pSrc + nWidth;
		IpSrcDn		= IpSrc + nWidth;

		for(y=1; y<nHeight-1;y++)
		{
			IpSrcUp++;
			IpSrc++;
			IpSrcDn++;
			IpDst++;

			for(x=1; x<nWidth-1; x++)
			{
				WN	=	*(IpSrcUp-1);	 NN	=	*(IpSrcUp);		NE	=	*(IpSrcUp+1);
				WW	=	*(IpSrc-1);		 CC	=	*(IpSrc);		EE	=	*(IpSrc+1);
				SW	=	*(IpSrcDn-1);	 SS=	*(IpSrcDn);		ES	=	*(IpSrcDn+1);
			
			
				fGyValue	=	WN+NN+NN+NE-SW-SS-SS-ES;
				fGxValue	=	WN+WW+WW+SW-NE-EE-EE-ES;

				fsmValue = abs(fGyValue) + abs(fGxValue);
//				fsmValue = abs(fsmValue);
//				fsmValue = abs(fGxValue);


				if (fsmValue>255)	fsmValue=255;
				*IpDst++	=	(BYTE)(fsmValue);
				
				IpSrcUp++;
				IpSrc++;
				IpSrcDn++;
			
			}
		
			IpSrcUp++;
			IpSrc++;
			IpSrcDn++;
			IpDst++;
		
		}

		return 0;

	}

int ipl_FilterKirschGray1(OUT LPBYTE pDstSobel, IN const LPBYTE pSrc, IN int nSrcWidth, IN int nSrcHeight)
	{
		register int nHeight = nSrcHeight;
		register int nWidth = nSrcWidth;
		register int x,y;

		LPBYTE IpDst	= pDstSobel+nWidth;

		LPBYTE IpSrc	= pSrc;
		LPBYTE IpSrcUp	= NULL;
		LPBYTE IpSrcDn	= NULL;

		register BYTE	WN, NN, NE;
		register BYTE	WW, CC, EE;
		register BYTE	SW, SS, ES;

		register int	fNValue;
		register int	fWValue;
		register int	fSValue;
		register int	fEValue;
		register int	fNWValue;
		register int	fSWValue;
		register int	fSEValue;
		register int	fNEValue;
		int				fmaxValue;

		IpSrcUp		= pSrc;
		IpSrc		= pSrc + nWidth;
		IpSrcDn		= IpSrc + nWidth;

		for(y=1; y<nHeight-1;y++)
		{
			IpSrcUp++;
			IpSrc++;
			IpSrcDn++;
			IpDst++;

			for(x=1; x<nWidth-1; x++)
			{
				WN	=	*(IpSrcUp-1);	 NN	=	*(IpSrcUp);		NE	=	*(IpSrcUp+1);
				WW	=	*(IpSrc-1);		 CC	=	*(IpSrc);		EE	=	*(IpSrc+1);
				SW	=	*(IpSrcDn-1);	 SS =	*(IpSrcDn);		ES	=	*(IpSrcDn+1);
			
			
				fNValue		=	NE+NE+NE+NE+NE+EE+EE+EE+EE+EE+ES+ES+ES+ES+ES-WN-WN-WN-WW-WW-WW-SW-SW-SW-NN-NN-NN-SS-SS-SS;
				fWValue		=	NE+NE+NE+NE+NE+EE+EE+EE+EE+EE+-ES-ES-ES-WN-WN-WN-WW-WW-WW-SW-SW-SW+NN+NN+NN+NN+NN-SS-SS-SS;
				fNWValue	=	-NE-NE-NE-EE-EE-EE-ES-ES-ES+WN+WN+WN+WN+WN+WW+WW+WW+WW+WW+SW+SW+SW+SW+SW-NN-NN-NN-SS-SS-SS;
				fNEValue	=	-NE-NE-NE+EE+EE+EE+EE+EE+ES+ES+ES+ES+ES-WN-WN-WN-WW-WW-WW-SW-SW-SW-NN-NN-NN+SS+SS+SS+SS+SS;
//				fSValue		=	NE+NE+NE+NE+NE-EE-EE-EE-ES-ES-ES+WN+WN+WN+WN+WN-WW-WW-WW-SW-SW-SW+NN+NN+NN+NN+NN-SS-SS-SS;
//				fEValue		=	-NE-NE-NE-EE-EE-EE-ES-ES-ES+WN+WN+WN+WN+WN+WW+WW+WW+WW+WW-SW-SW-SW+NN+NN+NN+NN+NN-SS-SS-SS;
//				fSWValue	=	-NE-NE-NE-EE-EE-EE-ES-ES-ES-WN-WN-WN+WW+WW+WW+WW+WW+SW+SW+SW+SW+SW-NN-NN-NN+SS+SS+SS+SS+SS;
//				fSEValue	=	-NE-NE-NE-EE-EE-EE+ES+ES+ES+ES+ES-WN-WN-WN-WW-WW-WW+SW+SW+SW+SW+SW-NN-NN-NN+SS+SS+SS+SS+SS;
				

//				fmaxValue   =	max(max(max(max(max(max(max(fNEValue,fSEValue),fSWValue), fNWValue ), fEValue), fSValue), fWValue), fEValue);
				fmaxValue   =	max(max(max (fNValue, fWValue), fNWValue), fNEValue);
//				fmaxValue   =	max(max(max (fSValue, fEValue), fSWValue), fSEValue);
				fmaxValue = abs(fmaxValue);

				if (fmaxValue>255)	fmaxValue=255;
				*IpDst++	=	(BYTE)(fmaxValue);
				
				IpSrcUp++;
				IpSrc++;
				IpSrcDn++;
			
			}
		
			IpSrcUp++;
			IpSrc++;
			IpSrcDn++;
			IpDst++;
		
		}

		return 0;

	}

int ipl_FilterKirschGray2(OUT LPBYTE pDstSobel, IN const LPBYTE pSrc, IN int nSrcWidth, IN int nSrcHeight)
	{
		register int nHeight = nSrcHeight;
		register int nWidth = nSrcWidth;
		register int x,y;

		LPBYTE IpDst	= pDstSobel+nWidth;

		LPBYTE IpSrc	= pSrc;
		LPBYTE IpSrcUp	= NULL;
		LPBYTE IpSrcDn	= NULL;

		register BYTE	WN, NN, NE;
		register BYTE	WW, CC, EE;
		register BYTE	SW, SS, ES;

		register int	fNValue;
		register int	fWValue;
		register int	fSValue;
		register int	fEValue;
		register int	fNWValue;
		register int	fSWValue;
		register int	fSEValue;
		register int	fNEValue;
		int				fmaxValue;

		IpSrcUp		= pSrc;
		IpSrc		= pSrc + nWidth;
		IpSrcDn		= IpSrc + nWidth;

		for(y=1; y<nHeight-1;y++)
		{
			IpSrcUp++;
			IpSrc++;
			IpSrcDn++;
			IpDst++;

			for(x=1; x<nWidth-1; x++)
			{
				WN	=	*(IpSrcUp-1);	 NN	=	*(IpSrcUp);		NE	=	*(IpSrcUp+1);
				WW	=	*(IpSrc-1);		 CC	=	*(IpSrc);		EE	=	*(IpSrc+1);
				SW	=	*(IpSrcDn-1);	 SS =	*(IpSrcDn);		ES	=	*(IpSrcDn+1);
			
			
//				fNValue		=	NE+NE+NE+NE+NE+EE+EE+EE+EE+EE+ES+ES+ES+ES+ES-WN-WN-WN-WW-WW-WW-SW-SW-SW-NN-NN-NN-SS-SS-SS;
//				fWValue		=	NE+NE+NE+NE+NE+EE+EE+EE+EE+EE+-ES-ES-ES-WN-WN-WN-WW-WW-WW-SW-SW-SW+NN+NN+NN+NN+NN-SS-SS-SS;
//				fNWValue	=	-NE-NE-NE-EE-EE-EE-ES-ES-ES+WN+WN+WN+WN+WN+WW+WW+WW+WW+WW+SW+SW+SW+SW+SW-NN-NN-NN-SS-SS-SS;
//				fNEValue	=	-NE-NE-NE+EE+EE+EE+EE+EE+ES+ES+ES+ES+ES-WN-WN-WN-WW-WW-WW-SW-SW-SW-NN-NN-NN+SS+SS+SS+SS+SS;
				fSValue		=	NE+NE+NE+NE+NE-EE-EE-EE-ES-ES-ES+WN+WN+WN+WN+WN-WW-WW-WW-SW-SW-SW+NN+NN+NN+NN+NN-SS-SS-SS;
				fEValue		=	-NE-NE-NE-EE-EE-EE-ES-ES-ES+WN+WN+WN+WN+WN+WW+WW+WW+WW+WW-SW-SW-SW+NN+NN+NN+NN+NN-SS-SS-SS;
				fSWValue	=	-NE-NE-NE-EE-EE-EE-ES-ES-ES-WN-WN-WN+WW+WW+WW+WW+WW+SW+SW+SW+SW+SW-NN-NN-NN+SS+SS+SS+SS+SS;
				fSEValue	=	-NE-NE-NE-EE-EE-EE+ES+ES+ES+ES+ES-WN-WN-WN-WW-WW-WW+SW+SW+SW+SW+SW-NN-NN-NN+SS+SS+SS+SS+SS;
				

//				fmaxValue   =	max(max(max(max(max(max(max(fNEValue,fSEValue),fSWValue), fNWValue ), fEValue), fSValue), fWValue), fEValue);
//				fmaxValue   =	max(max(max (fNValue, fWValue), fNWValue), fNEValue);
				fmaxValue   =	max(max(max (fSValue, fEValue), fSWValue), fSEValue);
				fmaxValue = abs(fmaxValue);

				if (fmaxValue>255)	fmaxValue=255;
				*IpDst++	=	(BYTE)(fmaxValue);
				
				IpSrcUp++;
				IpSrc++;
				IpSrcDn++;
			
			}
		
			IpSrcUp++;
			IpSrc++;
			IpSrcDn++;
			IpDst++;
		
		}

		return 0;

	}


int ipl_FilterBoxcarGray(OUT LPBYTE pDstSobel, IN const LPBYTE pSrc, IN int nSrcWidth, IN int nSrcHeight)
	{
		register int nHeight = nSrcHeight;
		register int nWidth = nSrcWidth;
		register int x,y;

		LPBYTE IpDst	= pDstSobel+nWidth;

		LPBYTE IpSrc1	= pSrc;
		LPBYTE IpSrc2	= NULL;
		LPBYTE IpSrc3	= NULL;
		LPBYTE IpSrc4	= NULL;

		register BYTE	L1, L2, L3, L4;
		register BYTE	R1, R2, R3, R4;
		int				fsmValue;

		IpSrc1		= pSrc;
		IpSrc2		= IpSrc1 + nWidth;
		IpSrc3		= IpSrc2 + nWidth;
		IpSrc4		= IpSrc3 + nWidth;

		for(y=1; y<nHeight-1;y++)
		{
			IpSrc1++;	
			IpSrc2++;	
			IpSrc3++;	
			IpSrc4++;	
			
			IpDst++;

			for(x=1; x<nWidth-1; x++)
			{
				R1	=	*(IpSrc1) ;		 R2	=	*(IpSrc2) ;		R3 = *(IpSrc3) ;	R4 = *(IpSrc4) ; 

				L1	=	*(IpSrc1-1) ;	 L2	=	*(IpSrc2-1) ;	L3 = *(IpSrc3-1) ;	L4 = *(IpSrc4-1) ;
					
				

				fsmValue = ((L1+L2+L3+L4) - (R1+R2+R3+R4));

				if (fsmValue>255)	fsmValue=255;

				else fsmValue =  abs(fsmValue);
				
				
				*IpDst++	=	(BYTE)(fsmValue);
				
				IpSrc1++;	
				IpSrc2++;	
				IpSrc3++;	
				IpSrc4++;
			
			}
		
			IpSrc1++;	
			IpSrc2++;	
			IpSrc3++;	
			IpSrc4++;	
			
			IpDst++;
		
		}



		return 0;

	}

BOOL  ipl_CpyyGrayToRGB(OUT LPBYTE pDstRGB, IN const LPBYTE pSrcGray, int nSrcWidth, int nSrcHeight, int nBytes)
	{
		if(nBytes<3) return -1;

		LPBYTE	IpDst= pDstRGB;
		LPBYTE	IpSrc= pSrcGray;
		
		register int nByteGap = nBytes-3;

		if(nByteGap<0) nByteGap=0;

		int nSize = nSrcHeight*nSrcWidth;
		LPBYTE IpSrcEnd = IpSrc + nSize;

		while(IpSrc<IpSrcEnd)
		{
			*IpDst++= *IpSrc;
			*IpDst++= *IpSrc;
			*IpDst++= *IpSrc;

			IpSrc++;
			
			IpDst+=nByteGap;
		}
			
		return 1;

	}

float ipl_BoxcarToBlock(OUT LPBYTE pDst ,IN const LPBYTE pSrc, int nWidth, int nHeight, int nBytes)
	{
	DWORD dwBlockSum	= 0				;
	DWORD dwBlockSum1	= 0				;
	UINT  nBlockCount	= 0				;
	
	INT	  SumBuck		= 0				;
	float AvgBuck		= 0				;
	float DiffBuck		= 0				;
	float scale			= 1				;
	float BlockMeasure	= 0				;
	INT   MaxBuck		= 0				;
	
	
	INT	  Buck1			= 0				;
	INT	  Buck2			= 0				;
	INT	  Buck3			= 0				;
	INT	  Buck4			= 0				;
	INT	  Buck5			= 0				;
	INT	  Buck6			= 0				;
	INT	  Buck7			= 0				;
	INT	  Buck8			= 0				;

	INT   nWidthStart   = BLOCK_SIZE    ;
	INT   nHeightStart  = BLOCK_SIZE    ;
	INT   nWidthEnd     = nWidth  - BLOCK_SIZE ;
	INT   nHeightEnd    = nHeight - BLOCK_SIZE ;

		
	LPBYTE pBuf         = pSrc;
	
	LPBYTE lpLine1 		= pBuf			+ nWidth*nHeightStart + BLOCK_SIZE;
	LPBYTE lpLine2 		= lpLine1  		+ nWidth		;
	LPBYTE lpLine3 		= lpLine2  		+ nWidth		;
	LPBYTE lpLine4 		= lpLine3  		+ nWidth		;
	LPBYTE lpLine5 		= lpLine4  		+ nWidth		;
	LPBYTE lpLine6 		= lpLine5  		+ nWidth		;
	LPBYTE lpLine7 		= lpLine6  		+ nWidth		;
	LPBYTE lpLine8 		= lpLine7  		+ nWidth		;
	
	UINT   nBlock = BLOCK_SIZE*2;

	
	
	for( int i=nHeightStart, j ; i<nHeightEnd ; i+=BLOCK_SIZE )
	{
		for( j=nWidthStart ; j<nWidthEnd ; j+=BLOCK_SIZE )
		{
			
			{	
				Buck1	=	Buck1 + (*(lpLine1));
				Buck2	=	Buck2 + (*(lpLine2));
				Buck3	=	Buck3 + (*(lpLine3));
				Buck4	=	Buck4 + (*(lpLine4));
				Buck5	=	Buck5 + (*(lpLine5));
				Buck6	=	Buck6 + (*(lpLine6));
				Buck7	=	Buck7 + (*(lpLine7));
				Buck8	=	Buck8 + (*(lpLine8));
			
			}


			lpLine1     += nBlock;
			lpLine2     += nBlock;
			lpLine3     += nBlock;
			lpLine4		+= nBlock;
			lpLine5		+= nBlock;
			lpLine6		+= nBlock;
			lpLine7		+= nBlock;
			lpLine8		+= nBlock;
			

		
		}
	}
			
		SumBuck = Buck1 + Buck2 + Buck3	+ Buck4 + Buck5 + Buck6 + Buck7 + Buck8 ;
		AvgBuck = (float)SumBuck/8;

		MaxBuck = max(Buck1, max(Buck2, max(Buck3, max(Buck4, max(Buck5, max(Buck6, max(Buck7,Buck8))))))); 
		DiffBuck= MaxBuck- AvgBuck;

		BlockMeasure = DiffBuck * scale;
						
	
	return BlockMeasure;
	
	
	}



float ipl_GrayToBlock(OUT LPBYTE pDst ,IN const LPBYTE pSrc, int nWidth, int nHeight, int nBytes)
	{
	DWORD dwBlockSum	= 0				;
	DWORD dwBlockSum1	= 0				;
	UINT  nBlockCount	= 0				;
	UINT  nBlockCount1	= 0				;

	INT   nWidthStart   = BLOCK_SIZE    ;
	INT   nHeightStart  = BLOCK_SIZE    ;
	INT   nWidthEnd     = nWidth  - BLOCK_SIZE ;
	INT   nHeightEnd    = nHeight - BLOCK_SIZE ;

	UINT  nNh           = 0;
	UINT  nNv           = 0;
	float fDh			= 0;
	float fBh			= 0;
	float fDv			= 0;
	float fBv			= 0;
	float fBblk			= 0;
	float fZh			= 0;
	float fZv			= 0;
	float fZblk			= 0;
	float fQblk			= 0;
	float fNewQblk		= 0;
	float fQimage		= 0;
	
	LPBYTE pBuf         = pSrc;
		
	LPBYTE lpLine4up	= pBuf			+ nWidth*(nHeightStart-4) + BLOCK_SIZE;
	LPBYTE lpLine3up	= pBuf			+ nWidth*(nHeightStart-3) + BLOCK_SIZE;
	LPBYTE lpLine2up	= pBuf			+ nWidth*(nHeightStart-2) + BLOCK_SIZE;
	LPBYTE lpLine1up 	= pBuf			+ nWidth*(nHeightStart-1) + BLOCK_SIZE;
	LPBYTE lpLine1 		= pBuf			+ nWidth*nHeightStart + BLOCK_SIZE;
	LPBYTE lpLine2 		= lpLine1  		+ nWidth		;
	LPBYTE lpLine3 		= lpLine2  		+ nWidth		;
	LPBYTE lpLine4 		= lpLine3  		+ nWidth		;
	LPBYTE lpLine5 		= lpLine4  		+ nWidth		;
	LPBYTE lpLine6 		= lpLine5  		+ nWidth		;
	LPBYTE lpLine7 		= lpLine6  		+ nWidth		;
	LPBYTE lpLine8 		= lpLine7  		+ nWidth		;
	LPBYTE lpLine9 		= lpLine8  		+ nWidth		;
	LPBYTE lpLine10 	= lpLine9  		+ nWidth		;

	UINT   nDoubleBlock = BLOCK_SIZE*2;

	for( int i=nHeightStart, j ; i<nHeightEnd ; i+=BLOCK_SIZE )
	{
		for( j=nWidthStart ; j<nWidthEnd ; j+=BLOCK_SIZE )
		{
			nNh = CalNh(lpLine1, lpLine2, lpLine3, lpLine4, lpLine5, lpLine6, lpLine7, lpLine8, BLOCK_SIZE);

			fDh = CalDh(lpLine1, lpLine2, lpLine3, lpLine4, lpLine5, lpLine6, lpLine7, lpLine8, BLOCK_SIZE);
						
			if (fDh!=0)
				{fBh= nNh/fDh;}
			else
				{fBh=0;}
			
			nNv = CalNv(lpLine1up, lpLine1, BLOCK_SIZE);

			fDv = CalDv(lpLine4up, lpLine3up, lpLine2up, lpLine1up, lpLine1, lpLine2, lpLine3, lpLine4, BLOCK_SIZE);
						
			if (fDv!=0)
				{fBv= nNv/fDv;}
			else
				{fBv=0;}
			
			fBblk= (fBh+fBv)/2 ;

			fZh = CalZh(lpLine1, lpLine2, lpLine3, lpLine4, lpLine5, lpLine6, lpLine7, lpLine8, BLOCK_SIZE);
			

			fZv = CalZv(lpLine4up, lpLine3up, lpLine2up, lpLine1up, lpLine1, lpLine2, lpLine3, lpLine4, BLOCK_SIZE);
			
			
			fZblk= (fZh+fZv)/2 ;
			

//			float 			fJnd = CalTJnd(lpLine4up, lpLine3up, lpLine2up, lpLine1up, lpLine1, lpLine2, lpLine3, lpLine4,lpLine5, lpLine6, lpLine7, lpLine8, BLOCK_SIZE );

		
			
			
			float			fJnd1  = CalJnd(lpLine1, lpLine1up,  lpLine2up, lpLine2, lpLine3 );
			float			fJnd2  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			float			fJnd3  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			float			fJnd4  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			float			fJnd5  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			float			fJnd6  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			float			fJnd7  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			float			fJnd8  = CalJnd(++lpLine1, ++lpLine1up,  ++lpLine2up, ++lpLine2, ++lpLine3 );
			
			float			fJnd9   = CalJnd(lpLine2, lpLine1,  lpLine1up, lpLine3, lpLine4 );
			float			fJnd10  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );			
			float			fJnd11  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );
			float			fJnd12  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );			
			float			fJnd13  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );
			float			fJnd14  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );
			float			fJnd15  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );
			float			fJnd16  = CalJnd(++lpLine2,++lpLine1,++lpLine1up,++lpLine3,++lpLine4 );

			float			fJnd17  = CalJnd(lpLine3, lpLine2,  lpLine1, lpLine4, lpLine5 );
			float			fJnd18  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );
			float			fJnd19  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );
			float			fJnd20  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );
			float			fJnd21  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );
			float			fJnd22  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );
			float			fJnd23  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );
			float			fJnd24  = CalJnd(++lpLine3,++lpLine2,++lpLine1,++lpLine4,++lpLine5 );

			float			fJnd25  = CalJnd(lpLine4,lpLine3,lpLine2,lpLine5,lpLine6 );
			float			fJnd26  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );
			float			fJnd27  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );
			float			fJnd28  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );
			float			fJnd29  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );
			float			fJnd30  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );
			float			fJnd31  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );
			float			fJnd32  = CalJnd(++lpLine4,++lpLine3,++lpLine2,++lpLine5,++lpLine6 );

			float			fJnd33  = CalJnd(lpLine5,lpLine4,lpLine3,lpLine6,lpLine7 );
			float			fJnd34  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );
			float			fJnd35  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );
			float			fJnd36  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );
			float			fJnd37  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );
			float			fJnd38  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );
			float			fJnd39  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );
			float			fJnd40  = CalJnd(++lpLine5,++lpLine4,++lpLine3,++lpLine6,++lpLine7 );

			float			fJnd41  = CalJnd(lpLine6,lpLine5,lpLine4,lpLine7,lpLine8 );
			float			fJnd42  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );
			float			fJnd43  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );
			float			fJnd44  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );
			float			fJnd45  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );
			float			fJnd46  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );
			float			fJnd47  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );
			float			fJnd48  = CalJnd(++lpLine6,++lpLine5,++lpLine4,++lpLine7,++lpLine8 );

			float			fJnd49  = CalJnd(lpLine7,lpLine6,lpLine5,lpLine8,lpLine9 );
			float			fJnd50  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );
			float			fJnd51  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );
			float			fJnd52  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );
			float			fJnd53  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );
			float			fJnd54  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );
			float			fJnd55  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );
			float			fJnd56  = CalJnd(++lpLine7,++lpLine6,++lpLine5,++lpLine8,++lpLine9 );

			float			fJnd57  = CalJnd(lpLine8,lpLine7,lpLine6,lpLine9,lpLine10 );
			float			fJnd58  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );
			float			fJnd59  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );
			float			fJnd60  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );
			float			fJnd61  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );
			float			fJnd62  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );
			float			fJnd63  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );
			float			fJnd64  = CalJnd(++lpLine8,++lpLine7,++lpLine6,++lpLine9,++lpLine10 );


			float			fAvgJnd = (fJnd1 + fJnd2  +  fJnd3  + fJnd4  + fJnd5  + fJnd6  + fJnd7  + fJnd8  + fJnd9  + fJnd10 +  fJnd11 + fJnd12 + fJnd13 + fJnd14 + fJnd15 + fJnd16 + 
									   fJnd17 + fJnd18 + fJnd19 + fJnd20 + fJnd21 + fJnd22 + fJnd23 + fJnd24 + fJnd25 + fJnd26 + fJnd27 + fJnd28 + fJnd29 + fJnd30 +  fJnd31 + fJnd32 +	 
									   fJnd33 + fJnd34 + fJnd35 + fJnd36 + fJnd37 + fJnd38 + fJnd39 + fJnd40 + fJnd41 + fJnd42 + fJnd43 + fJnd44 + fJnd45 + fJnd46 + fJnd47 + fJnd48 + 
									   fJnd49 + fJnd50 + fJnd51 + fJnd52 + fJnd53 + fJnd54 + fJnd55 + fJnd56 + fJnd57 + fJnd58 + fJnd59 + fJnd60 + fJnd61 + fJnd62 + fJnd63 + fJnd64)/64.f;

			float  fTJnd = 0.1* fAvgJnd;   



			if(fBblk > fZblk)
				{
					if (fBblk > fTJnd)
					{	fQblk =fBblk;
					
					}
					
					else
						fQblk=0;
				}
//			else
//				{	
//					if (fZblk > fTJnd)
//						fQblk = fZblk;
//					else
//						fQblk=0;
//				}

			
			fNewQblk= fQblk + fNewQblk;
			
			nBlockCount++;
			
			
			lpLine4up    += nDoubleBlock;
			lpLine3up    += nDoubleBlock;
            lpLine2up    += nDoubleBlock;
			lpLine1up    += nDoubleBlock;
			lpLine1      += nDoubleBlock;
			lpLine2      += nDoubleBlock;
			lpLine3      += nDoubleBlock;
			lpLine4      += nDoubleBlock;
			lpLine5      += nDoubleBlock;
			lpLine6      += nDoubleBlock;
			lpLine7      += nDoubleBlock;
			lpLine8      += nDoubleBlock;
			lpLine9      += nDoubleBlock;
			lpLine10     += nDoubleBlock;
	

		
		}
	}
			
			fQimage = fNewQblk/(float)nBlockCount;
			
						
	
	return fQimage;
	
	
	}


	
CDetectionBlackFrame::CDetectionBlackFrame(void)
:m_rgbBlack(0,0,0)//,m_BeforeRGB(255,255,255)
{
	m_nCurFrame        =0   ;
	m_nStartFrame      =0   ;
	m_nEndFrame        =0   ;
	m_lpCallback       =NULL;
	m_lpUserData       =NULL;
	m_hCVideo          =NULL;
	memset( &m_AVResult, 0, sizeof(AVRESULT) );
	m_dwDetecedFlag    = CQ_QC_FS_BLACK;
	m_hCommonDLL       = NULL;
	memset( &m_VideoApi, 0, sizeof(CVIDEOAPI) );

	LoadCommonDLL();

	m_bInitFlag        = TRUE;
//	m_nStopProcessFrame= 0   ;

	m_byteNoiseLevel   = 0   ;
	m_nNoneDetectStart = 3   ;//%
	m_nNoneDetectEnd   = 5   ;//%

	m_dStartTime       = 0.0 ;
//	m_dEndTime         = 0.0 ;
	m_bDetectFalg      = FALSE;
	m_bAlram           = FALSE;
	m_nAlramTime       = 0	 ;
	m_tSystemStart     = 0	 ;
	m_tSystemEnd       = 0	 ;

	m_pGrayBuffer      = NULL;
	m_nSizeOfGray      = 0   ;

	m_pSobelBuffer	   = NULL;
	m_nSizeOfSobel	   = 0	 ;
	
	m_pTempBuffer	   = NULL;
	m_nSizeOfTemp	   = 0	 ;	
	
	m_DetectBlockVal   = 0   ;



}



CDetectionBlackFrame::~CDetectionBlackFrame(void)
{
	if(m_hCommonDLL)
		FreeLibrary(m_hCommonDLL); 
	
	if( m_pGrayBuffer )
		delete[] m_pGrayBuffer;

	if(	m_pSobelBuffer)
		delete[] m_pSobelBuffer;
	
	if(	m_pTempBuffer)
		delete[] m_pTempBuffer;

}

HRESULT CDetectionBlackFrame::SetOption( LPSTR_MAP lpmapOption )
{
	STR_MAP::iterator itor;
	CString szValue;

	itor = lpmapOption->find(_T("Noise level"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_byteNoiseLevel = (BYTE)_ttoi( (LPCTSTR)szValue );

		// ">>"연산을 쓰기 위한 비트 수 계산.
		//-연산은 0-
		m_byteNoiseLevel = (BYTE)( log10( (double)m_byteNoiseLevel ) / log10(2.0)  );
	}
	itor = lpmapOption->find(_T("None detect start ratio"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_nNoneDetectStart = (UINT)_ttoi( (LPCTSTR)szValue );
	}

	itor = lpmapOption->find(_T("None detect end ratio"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_nNoneDetectEnd  = (UINT)_ttoi( (LPCTSTR)szValue );
	}
	itor = lpmapOption->find(_T("Alram time"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_nAlramTime  = (UINT)_ttoi( (LPCTSTR)szValue );
		m_nAlramTime *= UINT_REFERENCE_TIME;
	}

	itor = lpmapOption->find(_T("Addition Value"));
	if (itor != lpmapOption->end())
	{
		szValue = (*itor).second.data();
		m_AdditionValue = (BYTE)_ttoi( (LPCTSTR)szValue );
	}	
	
	return S_OK;
}

HRESULT CDetectionBlackFrame::CheckStream(LPAVDATA lpAVData)
{
	if( m_hCommonDLL == NULL ) return E_FAIL;
	if( lpAVData     == NULL ) return E_FAIL;
	if( lpAVData->eType != _AL_MEDIA_Video ) return E_FAIL;

	if( m_bInitFlag )
	{
		m_nNoneDetectStart = (UINT)(((float)m_nNoneDetectStart/100.f) * lpAVData->video.dwTotalFrames);
		m_nNoneDetectEnd   = lpAVData->video.dwTotalFrames - (UINT)( ((float)m_nNoneDetectEnd/100.f) * lpAVData->video.dwTotalFrames );

//		if( lpAVData->video.dwTotalFrames/lpAVData->video.dbFrameRate > 6200 )//1시간보다 길다면 마지막 10% 프로세싱 중지.
//			m_nStopProcessFrame = lpAVData->video.dwTotalFrames - (UINT)(lpAVData->video.dwTotalFrames*0.08);

		m_nSizeOfGray  = lpAVData->dwDataSize / lpAVData->video.dwBytes;
		m_pGrayBuffer  = new BYTE[m_nSizeOfGray];

		m_nSizeOfSobel = lpAVData->dwDataSize / lpAVData->video.dwBytes;
		m_pSobelBuffer = new BYTE[m_nSizeOfSobel];


		m_nSizeOfTemp  = lpAVData->dwDataSize / lpAVData->video.dwBytes;
		m_pTempBuffer  = new BYTE[m_nSizeOfTemp];

		m_bInitFlag = FALSE;
	}


//	if(lpAVData->video.dwCurrentFrame==0) return S_OK;

	//Histogram을 구하면서 간단한 비트 작업을 같이 하게 함으로서 연산 량을 줄인다.
	//비트연산(point pixel 간 xor(^)결과를 CIplFrame의 맴버러 등록 하고 여기서는 그 결과에 대한 분석만으로 콜백함수로 결과 전달.)

	//아래는 사용방법에 대한 샘플로서의 가치를 갖는다.
	if( lpAVData->video.dwBytes != sizeof(tagRGB) ) return E_FAIL;

	m_nCurFrame = lpAVData->video.dwCurrentFrame;
	m_hCVideo   = lpAVData->video.hCVideo;

	//if( m_nStopProcessFrame && m_nStopProcessFrame<m_nCurFrame) return S_OK;

	if(lpAVData->video.dwTotalFrames !=0)
	{
		if( m_nNoneDetectStart>m_nCurFrame ) return S_OK;
		if( m_nNoneDetectEnd  <m_nCurFrame ) return S_OK;
	}

	
//	CIplFrameEx* pCurFrame = m_VideoApi.lpGetFrame( lpAVData->video.hCVideo, m_nCurFrame );
	LPBYTE lpSrc   = lpAVData->lpData;

//	ipl_Flip( lpSrc, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes );
	
//	Addition(lpSrc,lpAVData->video.dwWidth,lpAVData->video.dwHeight,m_AdditionValue, lpAVData->video.dwBytes );

	
//	ipl_RGBToGray( m_pGrayBuffer, lpSrc, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes);
	
//	ipl_FilterBoxcarGray(m_pSobelBuffer, m_pGrayBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight);


//	ipl_FilterSobelMagnitudeGray(m_pSobelBuffer, m_pGrayBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight);
	
//	ipl_FilterKirschGray1(m_pSobelBuffer, m_pGrayBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight);
//	ipl_FilterKirschGray2(m_pTempBuffer, m_pGrayBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight);

//	ipl_CpyyGrayToRGB( lpSrc, m_pSobelBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes);


//	m_DetectBlockVal = ipl_GrayToBlock(m_pTempBuffer , m_pGrayBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes);
	
	
//	m_DetectBlockVal = ipl_BoxcarToBlock(m_pTempBuffer , m_pSobelBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes);


//	ipl_CpyyGrayToRGB( lpSrc, m_pSobelBuffer, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes);

	Img_show(lpSrc, lpAVData->video.dwWidth, lpAVData->video.dwHeight, lpAVData->video.dwBytes);
	
		#ifdef _LOGDATA
		LOGMSG(_T("%08d	m_DetectBlockVal = %f"), lpAVData->video.dwCurrentFrame, m_DetectBlockVal );
		#endif


//	if(m_DetectBlockVal>=3)
//	{
						
		SendErrorFrame( lpAVData, m_nCurFrame );
//	}

	return S_OK;

}
HRESULT CDetectionBlackFrame::SendAlramFrame(LPAVDATA lpAVData, const int& nTargetFrame)
{
	//이전 프레임을 얻어 오는 방법.
	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpAVData->video.hCVideo, nTargetFrame );
#ifdef _LOGDATA
//	LOGMSG(_T("CDetectionBlackFrame::SendErrorFrame() frame=%08d	m_lpCallback=%08x, pFrame=%08x"), lpAVData->video.dwCurrentFrame-1, m_lpCallback, pFrame);
#endif
	if(pFrame==NULL) return S_FALSE;

	m_nEndFrame             = m_nCurFrame - 1         ;
	m_AVResult.nFrameStart  = m_nStartFrame           ;
	m_AVResult.nFrameEnd    = m_nEndFrame             ;
	m_AVResult.lpData       = pFrame->GetPixelData () ;
	m_AVResult.dwDataSize   = pFrame->GetDataSize  () ;
	m_AVResult.dwDetectFlag = m_dwDetecedFlag         ;
	m_AVResult.nFrameNumber = pFrame->GetFrameNo   () ;

	m_AVResult.rtStartTime = m_nStartFrame;
	m_AVResult.rtEndTime   = m_nEndFrame;
	m_AVResult.eResultCondition = eCONDITION_ALARM;
	m_AVResult.tSystemTimeStart = m_tSystemStart;
	time(&m_AVResult.tSystemTimeEnd);
	
	m_AVResult.rtStartTime = (REFERENCE_TIME)( m_dStartTime*UINT_REFERENCE_TIME );
	m_AVResult.rtEndTime   =  (REFERENCE_TIME)(pFrame->GetSampleTime()*UINT_REFERENCE_TIME);

	if((m_AVResult.rtEndTime - m_AVResult.rtStartTime) > m_nAlramTime && m_bAlram)
	{
		if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);
		m_bAlram = FALSE;
	}
	
	return S_OK;

}

HRESULT CDetectionBlackFrame::SendErrorFrame(LPAVDATA lpAVData, const int& nTargetFrame)
{
	//이전 프레임을 얻어 오는 방법.
	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpAVData->video.hCVideo, nTargetFrame );
#ifdef _LOGDATA
//	LOGMSG(_T("CDetectionBlackFrame::SendErrorFrame() frame=%08d	m_lpCallback=%08x, pFrame=%08x"), lpAVData->video.dwCurrentFrame-1, m_lpCallback, pFrame);
#endif
	if(pFrame==NULL) return S_FALSE;

	m_nEndFrame             = m_nCurFrame             ;
	m_AVResult.nFrameStart  = m_nCurFrame             ;
	m_AVResult.nFrameEnd    = m_nEndFrame             ;
	m_AVResult.lpData       = lpAVData->lpData        ;//pFrame->GetPixelData () ;
	m_AVResult.dwDataSize   = lpAVData->dwDataSize    ;//pFrame->GetDataSize  () ;
	m_AVResult.dwDetectFlag = m_dwDetecedFlag         ;
	m_AVResult.nFrameNumber = lpAVData->video.dwCurrentFrame; //pFrame->GetFrameNo   () ;
	m_AVResult.eResultCondition = eCONDITION_DETECTION;
	m_AVResult.tSystemTimeStart = m_tSystemStart;
	time(&m_AVResult.tSystemTimeEnd);
	m_AVResult.rtStartTime = (REFERENCE_TIME)( lpAVData->video.dbSampleTime  * UINT_REFERENCE_TIME );
	m_AVResult.rtEndTime   = (REFERENCE_TIME)( lpAVData->video.dbSampleTime  * UINT_REFERENCE_TIME );

	if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);

//	m_nStartFrame  = 0   ;
//	m_nEndFrame    = 0   ;
//	m_dStartTime   = 0.0 ;
//	m_bDetectFalg  = FALSE;
	return S_OK;

}

void CDetectionBlackFrame::SetCallback( LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	m_lpCallback = lpCallback;
	m_lpUserData = lpUserData;
}

void CDetectionBlackFrame::LoadCommonDLL(void)
{
	CMAUtil::GetCommonVideoAPI( &m_hCommonDLL, &m_VideoApi);
}

HRESULT CDetectionBlackFrame::FinishedStream( void )
{
	if( m_nStartFrame ) 
	{
		//이전 프레임을 얻어 오는 방법.
		CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( m_hCVideo, m_nCurFrame );
#ifdef _LOGDATA
//	LOGMSG(_T("%08d	pFrame=%08x"), lpAVData->video.dwCurrentFrame, pFrame);
#endif
		if(pFrame==NULL) return S_FALSE;

		m_nEndFrame             = m_nCurFrame             ;
		m_AVResult.nFrameStart  = m_nStartFrame           ;
		m_AVResult.nFrameEnd    = m_nEndFrame             ;
		m_AVResult.lpData       = pFrame->GetPixelData () ;
		m_AVResult.dwDataSize   = pFrame->GetDataSize  () ;
		m_AVResult.dwDetectFlag = m_dwDetecedFlag         ;
		m_AVResult.nFrameNumber = pFrame->GetFrameNo   () ;

		//임시로 사용
		m_AVResult.rtStartTime  = (REFERENCE_TIME)( m_dStartTime*UINT_REFERENCE_TIME );
		m_AVResult.rtEndTime    = (REFERENCE_TIME)( pFrame->GetSampleTime()  * UINT_REFERENCE_TIME );
		m_AVResult.eResultCondition = eCONDITION_DETECTION;

		if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);

		m_nStartFrame = 0;
		m_nEndFrame   = 0;
	}

	return S_OK;
}
