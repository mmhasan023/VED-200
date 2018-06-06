//2008.11.7
//by kiok ahn
//미디어 관련 출력 API 정의
//Catalog And Q.C. 진행에 관련한 API
///////////////////////////////////////////////////////////////////////////
// Cataloger And QC
///////////////////////////////////////////////////////////////////////////

#include "REDTTypeDefine.h"
#include "mmsystem.h"

#ifndef _MEDIA_ANGEL_H_INCLUDE_
#define _MEDIA_ANGEL_H_INCLUDE_


typedef BOOL (CALLBACK * LPFN_REDPROGRESS )(  HANDLE	hCQHandle    , //CQ 프로세서 핸들
											  DWORD		dwCurPos     , //progress 현재
											  BOOL		bFinish      , //종료플래그
											  TIMECODE	tc			 , //타임코드
											  LPVOID	lpUserData   );//CQOpen에서 입력받은 lpUserData

typedef BOOL (CALLBACK * LPFN_REDCQINFO   )(  HANDLE     hCQHandle    , //CQ 프로세서 핸들
											  HBITMAP    hBitmap      , //출력 이미지 
											  LPCTSTR    lpThumbPath  , //저장된 이미지 전체 경로
											  LPAVRESULT lpAVResult   ,
											  LPVOID     lpUserData   );//CQOpen에서 입력받은 lpUserData

typedef BOOL (CALLBACK * LPFN_REDMEDIAINFO)( LPMEDIAINFORMATION lpMediaInfo);

typedef HANDLE (WINAPI *LPFN_REDCQSET   )  (
										 IN LPCTSTR        lpDstFileName           , //파일 이름
										 IN DWORD          dwDstFileType           , //파일출력방식
										 IN DWORD          dwCheckMute             );//묵음 처리시간(초)
										 

typedef HANDLE (WINAPI *LPFN_REDCQOPEN   ) (
										 IN LPCTSTR        		lpCaptureDeviceNameVideo    , //입력 미디어 파일 전체 경로
										 IN LPCTSTR        		lpCaptureDeviceNameAudio    ,
										 IN LPCTSTR        		lpCheckProfilePath			, //입력 미디어 파일 전체 경로
										 IN HWND           		hWnd						, //Preview Window의 Handle
										 IN LPCTSTR        		lpDstDir					, //썸네일 출력 디렉터리
										 IN LPCTSTR        		lpOutFileName				, //출력파일 형식 이름
										 IN UINT		   		nTimeCodeSetting			, //타임코드 셋팅값 0:SDI 1:RS422 2:None
										 IN RECT				rectCheckSize				,
										 IN LPFN_REDCQINFO		lpFnCQInfo            		, //처리 결과 정보 CALLBACK 함수
										 IN LPFN_REDPROGRESS	lpFnProgress          		, //Progress 정보 CALLBACK 함수
										 LPVOID					lpUserData            		);//LPFN_CQINFO callback함수로 그대로 출력

typedef HRESULT (WINAPI *LPFN_REDCQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_REDCQRESUME) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_REDCQPAUSE ) (HANDLE hCQHandle);



//RED개발 추가
typedef HRESULT (WINAPI *LPFN_REDCQSTART ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_REDCQGETDEVICELIST ) (LPLIST_NAMEINFO lpVideoDeviceList, LPLIST_NAMEINFO lpAudioDeviceList);
typedef HRESULT (WINAPI *LPFN_REDCQGETVIDEOFORMATLIST ) (IN LPCTSTR lpVideoName, LPLIST_NAMEINFO lpVideoDeviceList);
typedef HRESULT (WINAPI *LPFN_REDCQGETAUDIOFORMATLIST ) (IN LPCTSTR lpAudioName, LPLIST_NAMEINFO lpAudioDeviceList);
typedef HRESULT (WINAPI *LPFN_REDCQSETVIDEOFORMAT ) (IN LPCTSTR lpVideoCaptureDeviceName, IN LPCTSTR lpVideoFormatName);
typedef HRESULT (WINAPI *LPFN_REDCQSETAUDIOFORMAT ) (IN LPCTSTR lpAudioCaptureDeviceName, IN LPCTSTR lpAudioFormatName);

typedef HRESULT (WINAPI *LPFN_REDCQGETDEVICELISTXML ) (OUT LPTSTR lpVideoDeviceList, OUT LPTSTR lpAudioDeviceList);
typedef HRESULT (WINAPI *LPFN_REDCQGETDEVICELISTXMLLENGTH ) (OUT DWORD *dwVideoDeviceList, OUT DWORD *dwAudioDeviceList);
typedef HRESULT (WINAPI *LPFN_REDCQGETVIDEOFORMATLISTXML ) (IN LPCTSTR lpVideoName, OUT LPTSTR lpVideoFormatList)	;
typedef HRESULT (WINAPI *LPFN_REDCQGETVIDEOFORMATLISTXMLLENGTH )(IN LPCTSTR lpVideoName, OUT DWORD *dwVideoFormatListLength)	;
typedef HRESULT (WINAPI *LPFN_REDCQGETAUDIOFORMATLISTXML ) (IN LPCTSTR lpAudioName, OUT LPTSTR lpAudioFormatList)	;
typedef HRESULT (WINAPI *LPFN_REDCQGETAUDIOFORMATLISTXMLLENGTH ) (IN LPCTSTR lpAudioName, OUT DWORD *dwAudioFormatListLength)	;

typedef HRESULT (WINAPI *LPFN_REDCQGETDEVICEFORMATXML ) (OUT LPTSTR lpDeviceFormatList)	;
typedef HRESULT (WINAPI *LPFN_REDCQGETDEVICEFORMATXMLLENGTH ) (OUT DWORD *dwDeviceFormatListLength)	;


HANDLE WINAPI REDCQOpen(IN LPCTSTR				lpCaptureDeviceNameVideo	, //입력 미디어 파일 전체 경로
					 	IN LPCTSTR				lpCaptureDeviceNameAudio	,
					 	IN LPCTSTR				lpCheckProfilePath		, //입력 미디어 파일 전체 경로
						IN HWND					hWnd						, //Preview Window의 Handle
					 	IN LPCTSTR				lpDstDir					, //썸네일 출력 디렉터리
					 	IN LPCTSTR				lpOutFileName			, //출력파일 형식 이름
						IN UINT					nTimeCodeSetting			, //타임코드 셋팅값 0:SDI 1:RS422 2:None
					 	IN LPFN_REDCQINFO		lpFnCQInfo				, //처리결과 CALLBACK함수
					 	IN LPFN_REDPROGRESS		lpFnProgress				, //Progress정보 CALLBACK함수
					 	LPVOID					lpUserData
					 	);
HRESULT WINAPI REDCQStart 	(HANDLE hCQHandle);
HRESULT WINAPI REDCQClose 	(HANDLE hCQHandle);
HRESULT WINAPI REDCQPause 	(HANDLE hCQHandle);
HRESULT WINAPI REDCQResume	(HANDLE hCQHandle);

//RED 개발 추가함수
HRESULT WINAPI REDCQGetDeviceList		(OUT LPLIST_STRING lpVideoDeviceList, OUT LPLIST_STRING lpAudioDeviceList)	;
HRESULT WINAPI REDCQGetVideoFormatList	(IN LPCTSTR lpVideoCaptureDeviceName, OUT LPLIST_STRING lpVideoFormatList)	;
HRESULT WINAPI REDCQGetAudioFormatList	(IN LPCTSTR lpAudioCaptureDeviceName, OUT LPLIST_STRING lpAudioFormatList)	;
HRESULT WINAPI REDCQSetVideoFormat		(IN LPCTSTR lpVideoName, IN LPCTSTR lpVideoFormat)							;
HRESULT WINAPI REDCQSetAudioFormat		(IN LPCTSTR lpAudioName, IN LPCTSTR lpAudioFormat)							;
HRESULT WINAPI REDCQGetDeviceListXML	(OUT LPTSTR lpVideoDeviceList, OUT LPTSTR lpAudioDeviceList)				;
HRESULT WINAPI REDCQGetDeviceListXMLLength		(OUT DWORD *dwVideoDeviceList, OUT DWORD *dwAudioDeviceList)		;
HRESULT WINAPI REDCQGetVideoFormatListXML		(IN LPCTSTR lpVideoName, OUT LPTSTR lpVideoFormatList)				;
HRESULT WINAPI REDCQGetVideoFormatListXMLLength	(IN LPCTSTR lpVideoName, OUT DWORD *dwVideoFormatListLength)		;
HRESULT WINAPI REDCQGetAudioFormatListXML		(IN LPCTSTR lpAudioName, OUT LPTSTR lpAudioFormatList)				;
HRESULT WINAPI REDCQGetAudioFormatListXMLLength	(IN LPCTSTR lpAudioName, OUT DWORD *dwAudioFormatListLength)		;
HRESULT WINAPI REDCQGetDeviceFormatXMLLength	(OUT DWORD *dwDeviceFormatLength)									;
HRESULT WINAPI REDCQGetDeviceFormatXML			(OUT LPTSTR lpDeviceFormat)										;


/////////////////////////////////////////////////////////////////////////////////////////////////
//미디어의 로딩을 외부에서 지원하기 위한 API
typedef HANDLE (WINAPI *LPFN_LOWCQOPEN   ) (
					   IN PBITMAPINFOHEADER  lpVideoInfo       ,//입력 비디오 Secquency 형식
					   IN PPCMWAVEFORMAT     lpAudioInfo       ,//입력 오디오 Secquency 형식
					   IN REFERENCE_TIME     rtDuration        ,//미디어 전체 길이
					   IN REFERENCE_TIME     rtTimeperFrame    ,//프레임당 할당된 시간
					   IN UINT               nTotalFrames      ,//전체 비디오 프레임 수, 해당 없으면 0
					   IN LPCTSTR            lpCheckProfilePath,//검수 프로파일 전체 경로 예) "c:\\1.xml"
					   IN LPCTSTR            lpDstDir          ,//썸네일 출력 디렉터리
					   IN LPCTSTR            lpOutFileName     ,//출력파일형식이름
					   LPFN_REDCQINFO        lpFnCQInfo        ,
					   LPFN_REDPROGRESS      lpFnProgress      ,
					   LPVOID                lpUserData        );
typedef HRESULT (WINAPI *LPFN_LOWCQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_LOWSETVIDEOSTREAMDATA) ( HANDLE hCQHandle, DOUBLE dbSampleTime, const LPBYTE lpData, const int& nDataSize );
typedef HRESULT (WINAPI *LPFN_LOWSETAUDIOSTREAMDATA) ( HANDLE hCQHandle, REFERENCE_TIME rtStartTime, REFERENCE_TIME rtEndTime, const LPBYTE lpData, const DWORD& dwSize );



HANDLE WINAPI LOWCQOpen( 
					   IN PBITMAPINFOHEADER  lpVideoInfo       ,//입력 비디오 Secquency 형식
					   IN PPCMWAVEFORMAT     lpAudioInfo       ,//입력 오디오 Secquency 형식
					   IN REFERENCE_TIME     rtDuration        ,//미디어 전체 길이
					   IN REFERENCE_TIME     rtTimeperFrame    ,//프레임당 할당된 시간
					   IN UINT               nTotalFrames      ,//전체 비디오 프레임 수, 해당 없으면 0
					   IN LPCTSTR            lpCheckProfilePath,//검수 프로파일 전체 경로 예) "c:\\1.xml"
					   IN LPCTSTR            lpDstDir          ,//썸네일 출력 디렉터리
					   IN LPCTSTR            lpOutFileName     ,//출력파일형식이름
					   LPFN_REDCQINFO        lpFnCQInfo        ,
					   LPFN_REDPROGRESS      lpFnProgress      ,
					   LPVOID                lpUserData        );
HRESULT WINAPI LOWCQClose           ( HANDLE hCQHandle );
HRESULT WINAPI LOWSetVideoStreamData( HANDLE hCQHandle, DOUBLE dbSampleTime, const LPBYTE lpData, const int& nDataSize );
HRESULT WINAPI LOWSetAudioStreamData( HANDLE hCQHandle, REFERENCE_TIME rtStartTime, REFERENCE_TIME rtEndTime, const LPBYTE lpData, const DWORD& dwSize );
//미디어의 로딩을 외부에서 지원하기 위한 API
/////////////////////////////////////////////////////////////////////////////////////////////////

#endif//_MEDIA_ANGEL_H_INCLUDE_