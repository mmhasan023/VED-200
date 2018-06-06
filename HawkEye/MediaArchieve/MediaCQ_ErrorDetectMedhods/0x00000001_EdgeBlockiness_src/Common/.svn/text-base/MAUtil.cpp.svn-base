#include "stdafx.h"
#include "MAUtil.h"
//#include "AppUtil.h"
#include "tchar.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#pragma comment(lib, "User32.lib")

#ifdef _LOGDATA	
	extern void LOGMSG(TCHAR *szMsg, ... );
#endif


int CMAUtil::GetMainPath( LPTSTR lpPath, int nSize )
{
	int nTmpSize = MAX_PATH2;

	TCHAR *ptcCurrentDirectory = new TCHAR[nTmpSize];
	ZeroMemory( ptcCurrentDirectory, sizeof(TCHAR)*nTmpSize );
	GetModuleFileName( NULL, ptcCurrentDirectory, nTmpSize);


	int nStrLength = (int)(_tcslen( ptcCurrentDirectory ));

	TCHAR *pIter = ptcCurrentDirectory + nStrLength - 1;
	while( *pIter != '\\' )
		*pIter-- = 0;

//	while(szPath.Right(1)!=_T("\\") && szPath.GetLength() )
//		szPath.Delete(szPath.GetLength()-1,1);

	nStrLength = (int)_tcslen( ptcCurrentDirectory );
	int nCpySize = min( nStrLength, nSize );

	_tcsncpy( lpPath, ptcCurrentDirectory, nCpySize );

	delete[] ptcCurrentDirectory;
	return nCpySize;
}

BOOL CMAUtil::GetCommonAudioAPI(HINSTANCE* phInatance, LPCAUDIOAPI lpCAudioApi)
{
	TCHAR szPath[MAX_PATH2]={0};
	int nSize = GetMainPath( szPath, MAX_PATH2 );

	if( szPath[nSize-1] != '\\' ) _tcscat( szPath, _T("\\") );
	_tcscat( szPath, _COMMON_AUDIO_DLL_NAME );

//	CString szPath = CAppUtil::GetMainPath();
//	if(szPath.Right(1)!=_T("\\")) szPath += _T("\\");
//	szPath += _COMMON_AUDIO_DLL_NAME;
//#ifdef _LOGDATA				
//	LOGMSG(_T("%s"),  szPath);
//#endif

	*phInatance = LoadLibrary(szPath);
	if( *phInatance == NULL )
		return FALSE;

	lpCAudioApi->lpfnCreate       = (LPFN_COMMON_AUDIO_CREATE         )GetProcAddress( *phInatance, NAME_COMMON_AUDIO_CREATE          );
	lpCAudioApi->lpfnClose        = (LPFN_COMMON_AUDIO_CLOSE          )GetProcAddress( *phInatance, NAME_COMMON_AUDIO_CLOSE           );
	lpCAudioApi->lpfnInputData    = (LPFN_COMMON_AUDIO_INPUTDATA      )GetProcAddress( *phInatance, NAME_COMMON_AUDIO_INPUTDATA       );
	lpCAudioApi->lpfnSetCallback  = (LPFN_COMMON_AUDIO_SETCALLBACK    )GetProcAddress( *phInatance, NAME_COMMON_AUDIO_SETCALLBACK     );
	lpCAudioApi->lpFinishedStream = (LPFN_COMMON_AUDIO_FINISHED_STREAM)GetProcAddress( *phInatance, NAME_COMMON_AUDIO_FINISHED_STREAM );

	// added by Tem (2011.08.11)
	lpCAudioApi->lpGetImageData	  = (LPFN_COMMON_AUDIO_GETIMAGEDATA	  )GetProcAddress( *phInatance, NAME_COMMON_AUDIO_GETIMAGEDATA	  );

	if(  lpCAudioApi->lpfnSetCallback  == NULL ) goto return_false;
	if(  lpCAudioApi->lpfnInputData    == NULL ) goto return_false;
	if(  lpCAudioApi->lpfnClose        == NULL ) goto return_false;
	if(  lpCAudioApi->lpfnCreate       == NULL ) goto return_false;
	if(  lpCAudioApi->lpFinishedStream == NULL ) goto return_false;

	// added by Tem (2011.08.11)
	if(  lpCAudioApi->lpGetImageData   == NULL ) goto return_false;

	return TRUE;

return_false:
	if(*phInatance)
	{
		FreeLibrary(*phInatance);
		*phInatance = NULL;

	}
	return FALSE;
}

BOOL CMAUtil::GetCommonVideoAPI(HINSTANCE* phInatance, LPCVIDEOAPI lpCVideoApi)
{
	TCHAR szPath[MAX_PATH2]={0};
	int nSize = GetMainPath( szPath, MAX_PATH2 );

	if( szPath[nSize-1] != '\\' ) _tcscat( szPath, _T("\\") );
	_tcscat( szPath, _COMMON_VIDEO_DLL_NAME );

//	CString szPath = CAppUtil::GetMainPath();
//	if(szPath.Right(1)!=_T("\\")) szPath += _T("\\");
//	szPath += _COMMON_VIDEO_DLL_NAME;

	*phInatance = LoadLibrary(szPath);
	if( *phInatance == NULL )
	{
//		TCHAR szMsg[MAX_PATH]={0};
//		_stprintf( _T("Cann't load \"%s\"."), szPath );
//		::MessageBox( NULL, szMsg, _T("Error"), MB_OK );
		return FALSE;
	}

	lpCVideoApi->lpfnCreate         = (LPFN_COMMON_VIDEO_CREATE          )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_CREATE          );
	lpCVideoApi->lpfnCreateEx       = (LPFN_COMMON_VIDEO_CREATEEX        )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_CREATEEX        );
	lpCVideoApi->lpfnClose          = (LPFN_COMMON_VIDEO_CLOSE           )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_CLOSE           );
	lpCVideoApi->lpfnInputData      = (LPFN_COMMON_VIDEO_INPUTDATA       )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_INPUTDATA       );
	lpCVideoApi->lpfnSetCallback    = (LPFN_COMMON_VIDEO_SETCALLBACK     )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_SETCALLBACK     );
	lpCVideoApi->lpGetFrame         = (LPFN_COMMON_VIDEO_GETFRAME        )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_GETFRAME        );
	lpCVideoApi->lpFinishedStream   = (LPFN_COMMON_VIDEO_FINISHED_STREAM )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_FINISHED_STREAM );
	lpCVideoApi->lpGetProcessWindow = (LPFN_COMMON_VIDEO_P_FRAME_WIN_SIZE)GetProcAddress( *phInatance, NAME_COMMON_VIDEO_P_FRAME_WIN_SIZE);
	lpCVideoApi->lpIsShotFrame      = (LPFN_COMMON_VIDEO_IS_SHOT_FRAME   )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_IS_SHOT_FRAME   );
	lpCVideoApi->IsSceneFrame       = (LPFN_COMMON_VIDEO_IS_SCENE_FRAME  )GetProcAddress( *phInatance, NAME_COMMON_VIDEO_IS_SCENE_FRAME  );
	lpCVideoApi->lpfnSetSSSensitive = (LPFN_COMMON_VIDEO_SET_SSSENNSITIVE)GetProcAddress( *phInatance, NAME_COMMON_VIDEO_SET_SSSENSITIVE );

	if (lpCVideoApi->lpfnSetCallback    == NULL) 
		goto return_false;
	if (lpCVideoApi->lpfnInputData      == NULL) 
		goto return_false;
	if (lpCVideoApi->lpfnClose          == NULL) 
		goto return_false;
	if (lpCVideoApi->lpfnCreate         == NULL) 
		goto return_false;
	if (lpCVideoApi->lpfnCreateEx       == NULL) 
		goto return_false;
	if (lpCVideoApi->lpGetFrame         == NULL)  
		goto return_false;
	if (lpCVideoApi->lpFinishedStream   == NULL)  
		goto return_false;
	if (lpCVideoApi->lpGetProcessWindow == NULL)  
		goto return_false;
	if (lpCVideoApi->lpIsShotFrame      == NULL)  
		goto return_false;
	if (lpCVideoApi->IsSceneFrame       == NULL)  
		goto return_false;
	if (lpCVideoApi->lpfnSetSSSensitive == NULL)  
		goto return_false;


	return TRUE;

return_false:
	if(*phInatance)
	{
		FreeLibrary(*phInatance);
		*phInatance = NULL;

	}
	return FALSE;
}
