//CommonDataApi.h
#ifndef _COMMON_DATA_API_H_INCLUDE_
#define _COMMON_DATA_API_H_INCLUDE_

#include "TTypeDefine.h"

#ifdef _DEBUG
	#ifdef UNICODE
		#define _COMMON_VIDEO_DLL_NAME  _T("MediaCQ_CommonDataVideoUD.dll")
		#define _COMMON_AUDIO_DLL_NAME  _T("MediaCQ_CommonDataAudioUD.dll")
	#else
		#define _COMMON_VIDEO_DLL_NAME  _T("MediaCQ_CommonDataVideoD.dll")
		#define _COMMON_AUDIO_DLL_NAME  _T("MediaCQ_CommonDataAudioD.dll")
	#endif
#else
	#ifdef UNICODE
		#define _COMMON_VIDEO_DLL_NAME  _T("MediaCQ_CommonDataVideoU.dll")
		#define _COMMON_AUDIO_DLL_NAME  _T("MediaCQ_CommonDataAudioU.dll")
	#else
		#define _COMMON_VIDEO_DLL_NAME  _T("MediaCQ_CommonDataVideo.dll")
		#define _COMMON_AUDIO_DLL_NAME  _T("MediaCQ_CommonDataAudio.dll")
	#endif
#endif

#define NAME_COMMON_VIDEO_CREATE           "CQ_CommonDVideoCreate"
#define NAME_COMMON_VIDEO_CREATEEX         "CQ_CommonDVideoCreateEx"
#define NAME_COMMON_VIDEO_CLOSE            "CQ_CommonDVideoClose"
#define NAME_COMMON_VIDEO_INPUTDATA        "CQ_CommonDVideoInputData"
#define NAME_COMMON_VIDEO_SETCALLBACK      "CQ_CommonDVideoSetResultCallback"
#define NAME_COMMON_VIDEO_GETFRAME         "CQ_CommonDVideoGetFrame"
#define NAME_COMMON_VIDEO_FINISHED_STREAM  "CQ_CommonDVideoSetFinishedStream"
#define NAME_COMMON_VIDEO_P_FRAME_WIN_SIZE "CQ_CommonDVideoGetProcessFrameWindowSize"
#define NAME_COMMON_VIDEO_IS_SHOT_FRAME    "CQ_CommonDVideoIsShotFrame"
#define NAME_COMMON_VIDEO_IS_SCENE_FRAME   "CQ_CommonDVideoIsSceneFrame"
#define NAME_COMMON_VIDEO_SET_SSSENSITIVE  "CQ_CommonDVideoSetSSSensitive"


/*
HCDVIDEO   WINAPI CQ_CommonDVideoCreate   (void             );
HRESULT    WINAPI CQ_CommonDVideoClose    (HCDVIDEO hDVideo );
HRESULT    WINAPI CQ_CommonDVideoInputData(HCDVIDEO hCVideo, LPAVDATA lpAVData);
CIplFrame* WINAPI CQ_CommonDVideoGetFrame (HCDVIDEO hCVideo, const UINT& nFrameNo);
void       WINAPI CQ_CommonDVideoSetResultCallback(HCDVIDEO hCVideo, LPFN_AVRESULT lpFnAVResult, LPVOID lpUserData);
*/

class CIplFrameEx;
typedef HCDVIDEO     (WINAPI* LPFN_COMMON_VIDEO_CREATE           )( void             );
typedef HCDVIDEO     (WINAPI* LPFN_COMMON_VIDEO_CREATEEX         )( void             );
typedef HRESULT      (WINAPI* LPFN_COMMON_VIDEO_CLOSE            )( HCDVIDEO hDVideo );
typedef HRESULT      (WINAPI* LPFN_COMMON_VIDEO_INPUTDATA        )( HCDVIDEO hCVideo, LPAVDATA lpAVData, const DWORD& dwProcessingFlag, const DWORD& dwCommonProcessing);
typedef CIplFrameEx* (WINAPI* LPFN_COMMON_VIDEO_GETFRAME         )( HCDVIDEO hCVideo, const UINT& nFrameNo);
typedef void         (WINAPI* LPFN_COMMON_VIDEO_SETCALLBACK      )( HCDVIDEO hCVideo, LPFN_AVRESULT lpFnAVResult, LPVOID lpUserData);
typedef HRESULT      (WINAPI* LPFN_COMMON_VIDEO_FINISHED_STREAM  )( HCDVIDEO hDVideo );
typedef INT          (WINAPI* LPFN_COMMON_VIDEO_P_FRAME_WIN_SIZE )( HCDVIDEO hDVideo );
typedef BOOL         (WINAPI* LPFN_COMMON_VIDEO_IS_SHOT_FRAME    )( HCDVIDEO hCVideo, const UINT& nFrameNumber );
typedef BOOL         (WINAPI* LPFN_COMMON_VIDEO_IS_SCENE_FRAME   )( HCDVIDEO hCVideo, const UINT& nFrameNumber );
typedef HRESULT      (WINAPI* LPFN_COMMON_VIDEO_SET_SSSENNSITIVE )( HCDVIDEO hCVideo, const UINT& nSensitive   );


typedef struct _tagCVideoAPI
{
	LPFN_COMMON_VIDEO_CREATE            lpfnCreate        ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_VIDEO_CREATEEX          lpfnCreateEx      ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_VIDEO_CLOSE             lpfnClose         ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_VIDEO_INPUTDATA         lpfnInputData     ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_VIDEO_SETCALLBACK       lpfnSetCallback   ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_VIDEO_GETFRAME          lpGetFrame        ;//한프레임의 정보를 알아온다.
	LPFN_COMMON_VIDEO_FINISHED_STREAM   lpFinishedStream  ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_VIDEO_P_FRAME_WIN_SIZE  lpGetProcessWindow;//프로세싱에 사용되는 프레의의 윈도우 크기를 알아온다.
	LPFN_COMMON_VIDEO_IS_SHOT_FRAME     lpIsShotFrame     ;//입력 프레임이 샷의 경계면인지 조사한다.
	LPFN_COMMON_VIDEO_IS_SCENE_FRAME    IsSceneFrame      ;//입력 프레임이 장면의 경계면인지 조사한다.
	LPFN_COMMON_VIDEO_SET_SSSENNSITIVE  lpfnSetSSSensitive;//장면 추출의 민감도를 설정한다.
}CVIDEOAPI, *LPCVIDEOAPI;

/*
HCDAUDIO WINAPI CQ_CommonDAudioCreate   (void);
HRESULT  WINAPI CQ_CommonDAudioClose    (HCDAUDIO hDAudio);
HRESULT  WINAPI CQ_CommonDAudioInputData(HCDAUDIO hDAudio, LPAVDATA lpAVData);
void     WINAPI CQ_CommonDAudioSetResultCallback(HCDAUDIO hDAudio, LPFN_AVRESULT lpFnAVResult, LPVOID lpUserData);
*/
#define NAME_COMMON_AUDIO_CREATE          "CQ_CommonDAudioCreate"
#define NAME_COMMON_AUDIO_CLOSE           "CQ_CommonDAudioClose"
#define NAME_COMMON_AUDIO_INPUTDATA       "CQ_CommonDAudioInputData"
#define NAME_COMMON_AUDIO_SETCALLBACK     "CQ_CommonDAudioSetResultCallback"
#define NAME_COMMON_AUDIO_FINISHED_STREAM "CQ_CommonDAudioSetFinishedStream"

// added by Tem (2011.08.11)
#define NAME_COMMON_AUDIO_GETIMAGEDATA	  "CQ_CommonDAudioGetImageData"


typedef HCDAUDIO (WINAPI* LPFN_COMMON_AUDIO_CREATE         )(void);
typedef HRESULT  (WINAPI* LPFN_COMMON_AUDIO_CLOSE          )(HCDAUDIO hDAudio);
typedef HRESULT  (WINAPI* LPFN_COMMON_AUDIO_INPUTDATA      )(HCDAUDIO hDAudio, LPAVDATA lpAVData);
typedef void     (WINAPI* LPFN_COMMON_AUDIO_SETCALLBACK    )(HCDAUDIO hDAudio, LPFN_AVRESULT lpFnAVResult, LPVOID lpUserData);
typedef HRESULT  (WINAPI* LPFN_COMMON_AUDIO_FINISHED_STREAM)(HCDVIDEO hDVideo );

// added by Tem (2011.08.11)
typedef HRESULT  (WINAPI* LPFN_COMMON_AUDIO_GETIMAGEDATA   )(	   HCDAUDIO			hDAudio			,
															 const REFERENCE_TIME&	startTime		, 
															 const REFERENCE_TIME&	endTime			,
															 const UINT				nChannelIndex	,
															 const UINT				nWidth			,
															 const UINT				nHeight			,
															 OUT   LPBYTE			lpImageData		) ; 

typedef struct _tagCAudioAPI
{
	LPFN_COMMON_AUDIO_CREATE          lpfnCreate      ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_AUDIO_CLOSE           lpfnClose       ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_AUDIO_INPUTDATA       lpfnInputData   ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_AUDIO_SETCALLBACK     lpfnSetCallback ;//Algorithm 레벨의 DLL에서 사용 금지
	LPFN_COMMON_AUDIO_FINISHED_STREAM lpFinishedStream;//Algorithm 레벨의 DLL에서 사용 금지

	// added by Tem (2011.08.11)
	LPFN_COMMON_AUDIO_GETIMAGEDATA	  lpGetImageData  ;//Algorithm 레벨의 DLL에서 사용 금지
}CAUDIOAPI, *LPCAUDIOAPI;

#endif//_COMMON_DATA_API_H_INCLUDE_