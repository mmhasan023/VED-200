//2008.11.7
//by kiok ahn
//미디어 관련 출력 API 정의
//Catalog And Q.C. 진행에 관련한 API
///////////////////////////////////////////////////////////////////////////
// Cataloger And QC
///////////////////////////////////////////////////////////////////////////

#include "TTypeDefine.h"

#ifndef _MEDIA_ANGEL_H_INCLUDE_
#define _MEDIA_ANGEL_H_INCLUDE_


typedef BOOL (CALLBACK * LPFN_PROGRESS )( HANDLE  hCQHandle    , //CQ 프로세서 핸들
										  DWORD   dwCurPos     , //progress 현재
										  DWORD   dwTotal      , //progress 전체
										  BOOL    bFinish      , //종료플래그
										  LPVOID  lpUserData   );//CQOpen에서 입력받은 lpUserData
/*
typedef BOOL (CALLBACK * LPFN_CQINFO   )( HANDLE  nCQHandle    , //CQ 프로세서 핸들
									      HBITMAP hBitmap      , //출력 이미지 
									      LPCTSTR lpThumbPath  , //저장된 이미지 전체 경로
										  INT64   nMuteStart   , //오디오 묵음검사에 대한 시작시간
										  INT64	  nMuteEnd     , //오디오 묵음검사에 대한 종료시간
									      INT64   nFrameNumber , //결과에 대한 현재 프레임 수.
										  DOUBLE  dVilumeLevel , //Audio volume level
									      DWORD   dwProcessFlag, //처리 옵션, 프로세스 종류
										  LPVOID  lpUserData   );//CQOpen에서 입력받은 lpUserData
*/

typedef BOOL (CALLBACK * LPFN_CQINFO   )( HANDLE     nCQHandle    , //CQ 프로세서 핸들
									      HBITMAP    hBitmap      , //출력 이미지 
									      LPCTSTR    lpThumbPath  , //저장된 이미지 전체 경로
										  LPAVRESULT lpAVResult   ,
										  LPVOID     lpUserData   );//CQOpen에서 입력받은 lpUserData

typedef BOOL (CALLBACK * LPFN_MEDIAINFO)( LPMEDIAINFORMATION lpMediaInfo);

typedef HANDLE (WINAPI *LPFN_CQSET   )  (
										 IN LPCTSTR        lpDstFileName           , //파일 이름
										 IN DWORD          dwDstFileType           , //파일출력방식
										 IN DWORD          dwCheckMute             );//묵음 처리시간(초)
										 

typedef HANDLE (WINAPI *LPFN_CQOPEN   ) (IN LPCTSTR        lpSrcPath             , //입력 미디어 파일 전체 경로
										 IN LPCTSTR        lpCheckProfilePath    ,//입력 미디어 파일 전체 경로
										 IN LPCTSTR        lpDstDir              , //썸네일 출력 디렉터리
										 IN LPCTSTR        lpOutFileName		 , //출력파일 형식 이름
										 IN DWORD          dwProcessFlag         , //처리 옵션
										 IN DWORD          dwCatelogSensitive    , //카타로그 감도 조정계수(1~9)
										 IN DWORD          dwCheckAudioMute      , //오디오 묵음 검사 시간(초)
										 IN LPFN_CQINFO    lpFnCQInfo            , //처리 결과 정보 CALLBACK 함수
										 IN LPFN_PROGRESS  lpFnProgress          , //Progress 정보 CALLBACK 함수
										 IN LPFN_MEDIAINFO lpFnMediaInfo         ,
										 LPVOID            lpUserData            );//LPFN_CQINFO callback함수로 그대로 출력
typedef HRESULT (WINAPI *LPFN_CQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQRESUME) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQPAUSE ) (HANDLE hCQHandle);

/*
HANDLE WINAPI CQOpen(IN LPCTSTR        lpSrcPath             , //입력 미디어 파일 전체 경로
					 IN LPCTSTR        lpDstDir              , //썸네일 출력 디렉터리
															   //  CQ_SAVE_IMG 옵션이 있으나 NULL 일 경우 임의의tmp 폴더를 생성 후 저장 
					 IN DWORD          dwProcessFlag         , //처리 옵션
					 IN DWORD          dwCatelogSensitive    , //카타로그 감도 조정계수(1~9)
					 IN LPFN_CQINFO    lpFnCQInfo            , //처리 결과 정보 CALLBACK 함수
					 IN LPFN_PROGRESS  lpFnProgress          , //Progress 정보 CALLBACK 함수
					 LPVOID            lpUserData            );//LPFN_CQINFO,LPFN_PROGRESS callback함수로 그대로 출력
*/
HANDLE WINAPI CQOpen(IN LPCTSTR      lpSrcPath         ,//입력 미디어 파일 전체 경로
					 IN LPCTSTR      lpCheckProfilePath,//입력 미디어 파일 전체 경로
					 IN LPCTSTR      lpDstDir          ,//썸네일 출력 디렉터리
					 IN LPCTSTR      lpOutFileName     ,//출력파일 형식 이름
					 IN DWORD        dwFlag            ,//처리 옵션
					 IN DWORD        dwSceneVal        ,//샷민감도
					 IN DWORD        dwCheckAudioMute  ,//묵음 처리 시간
					 LPFN_CQINFO     lpFnCQInfo        ,//처리결과 CALLBACK함수
					 LPFN_PROGRESS   lpFnProgress      ,//Progress정보 CALLBACK함수
					 LPFN_MEDIAINFO  lpFnMediaInfo     ,//미디어 정보 전달 CALLBACK
					 LPVOID          lpUserData
					 );

HRESULT WINAPI CQClose (HANDLE hCQHandle);
HRESULT WINAPI CQPause (HANDLE hCQHandle);
HRESULT WINAPI CQResume(HANDLE hCQHandle);


#endif//_MEDIA_ANGEL_H_INCLUDE_