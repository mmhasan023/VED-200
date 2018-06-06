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


//typedef BOOL ( CALLBACK * LPFN_PROGRESS  )( HANDLE	hCQHandle    , 		//CQ 프로세서 핸들
//											  DWORD		dwCurPos     , 		//progress 현재
//											  DWORD		dwTotal      , 		//progress 전체
//											  BOOL		bFinish      , 		//종료플래그
//											  LPVOID	lpUserData     		//CQOpen에서 입력받은 lpUserData
//										  );
typedef BOOL ( CALLBACK * LPFN_PROGRESS  )( HANDLE		hCQHandle    , 		//CQ 프로세서 핸들
										    DWORD       dwCurFrame   ,      //Current Ferame, //kmg, support creating file
											DWORD		dwCurPos     , 		//progress 현재
											DWORD		dwTotal      , 		//progress 전체
											BOOL		bFinish      , 		//종료플래그
											LPVOID		lpUserData     		//CQOpen에서 입력받은 lpUserData
										  );

typedef BOOL ( CALLBACK * LPFN_CQINFO    )( HANDLE		nCQHandle    ,		//CQ 프로세서 핸들
											HBITMAP     hBitmap      ,		//출력 이미지 
											LPCTSTR     lpThumbPath  ,		//저장된 이미지 전체 경로
											LPAVRESULT  lpAVResult   ,
											LPVOID      lpUserData   		//CQOpen에서 입력받은 lpUserData
										  );

typedef BOOL ( CALLBACK * LPFN_MEDIAINFO )( LPMEDIAINFORMATION lpMediaInfo,
										    LPVOID             lpUserData   //CQOpen에서 입력받은 lpUserData
										   );

//{{kiokahn, check split file
typedef BOOL ( CALLBACK * LPFN_SPLITINFO )( DWORD              dwSplitCount   ,//분할 되는 프로세스의 수, 자시의 수는 빠짐, 2분할이라면 1이 리턴
										    LPLIST_CHECKTIME   lplistCheckTime,//분할 프로세스의 분할 시간 정보
										    LPVOID             lpUserData   //CQOpen에서 입력받은 lpUserData
										   );
//}}kiokahn, check split file

typedef HANDLE ( WINAPI *LPFN_CQSET      )( IN LPCTSTR        lpDstFileName        ,		//파일 이름
										    IN DWORD          dwDstFileType        ,		//파일출력방식
										    IN DWORD          dwCheckMute					//묵음 처리시간(초)
										  );

typedef HANDLE (WINAPI *LPFN_CQOPEN     )( IN LPCTSTR            lpSrcPath             ,//입력 미디어 파일 전체 경로
										   IN LPCTSTR            lpCheckProfilePath	   ,//프로파일 경로 2009.11.11 ajy
										   IN LPCTSTR            lpDstDir              ,//썸네일 출력 디렉터리
										   IN LPCTSTR            lpOutFileName		   ,//출력파일 형식 이름
										   IN DWORD              dwDelayProcessing     ,//지연 처리 설정, 검사 속도, 네트웍 대역폭, ms
										   IN LONGLONG	         rtCheckStartTime      ,//kmg, support creating file
										   IN LONGLONG	         rtCheckEndTime        ,//{{kiokahn, check split file, 분할 검사 종료 시간, 
										   IN DWORD		         dwCheckStartFrame     ,//kmg, support creating file, rtCheckStartTime에 해당되는 Frame
										   IN LPPROCESSSPLITINFO lpSplitInfo           ,//{{kiokahn, check split file, NULL인 경우 분할 검사 여부 판단 없음.
										   IN LPFN_CQINFO        lpFnCQInfo            ,//처리 결과 정보 CALLBACK 함수
										   IN LPFN_PROGRESS      lpFnProgress          ,//Progress 정보 CALLBACK 함수
										   IN LPFN_MEDIAINFO     lpFnMediaInfo         ,
										   IN LPFN_SPLITINFO     lpFnSplitInfo         ,//{{kiokahn, check split file, lpSplitInfo에 대한 정보 전달, 무조건 한번 콜을 해야 함.
										   LPVOID                lpUserData				//LPFN_CQINFO callback함수로 그대로 출력
										  );
typedef HRESULT ( WINAPI *LPFN_CQCLOSE    )( HANDLE hCQHandle );
typedef HRESULT ( WINAPI *LPFN_CQRESUME   )( HANDLE hCQHandle );
typedef HRESULT ( WINAPI *LPFN_CQPAUSE    )( HANDLE hCQHandle );
typedef HRESULT ( WINAPI *LPFN_CQSETFINISHEVENT )( 
	IN HANDLE hCQHandle   ,
	IN HANDLE hFinishEvent//종료 이벤트 입력
);

//{{kiokahn, check split file
//분할 프로세스 수를 입력 받아야 함.
//분할 검사와 생성 중 파일검사에 대한 구분자 가 필요 할수도...
HANDLE WINAPI CQOpen	( IN LPCTSTR            lpSrcPath         ,//입력 미디어 파일 전체 경로
				    	  IN LPCTSTR            lpCheckProfilePath,//프로파일 경로 2009.11.11 ajy
						  IN LPCTSTR            lpDstDir          ,//썸네일 출력 디렉터리
						  IN LPCTSTR            lpOutFileName     ,//출력파일 형식 이름
						  IN DWORD              dwDelayProcessing ,//지연 처리 설정, 검사 속도, 네트웍 대역폭,ms
						  IN LONGLONG	        rtCheckStartTime  ,//kmg, support creating file
						  IN LONGLONG	        rtCheckEndTime    ,//{{kiokahn, check split file, 분할 검사 종료 시간, 
						  IN DWORD		        dwCheckStartFrame ,//kmg, support creating file, rtCheckStartTime에 해당되는 Frame
						  IN LPPROCESSSPLITINFO lpSplitInfo       ,//{{kiokahn, check split file, NULL인 경우 분할 검사 여부 판단 없음.
						  LPFN_CQINFO           lpFnCQInfo        ,//처리결과 CALLBACK함수
						  LPFN_PROGRESS         lpFnProgress      ,//Progress정보 CALLBACK함수
						  LPFN_MEDIAINFO        lpFnMediaInfo     ,//미디어 정보 전달 CALLBACK
						  LPFN_SPLITINFO        lpFnSplitInfo     ,//{{kiokahn, check split file, lpSplitInfo에 대한 정보 전달, 무조건 한번 콜을 해야 함.
						  LPVOID                lpUserData
						);
HRESULT WINAPI CQClose ( HANDLE hCQHandle );
HRESULT WINAPI CQPause ( HANDLE hCQHandle );
HRESULT WINAPI CQResume( HANDLE hCQHandle );
HRESULT WINAPI CQResume( HANDLE hCQHandle );
HRESULT WINAPI CQSetFinishEvent(            //사용하지 않아도 됨. LPFN_PROGRESS를 통해 종료 이벤트를 받을 수 있음.
	IN HANDLE hCQHandle   ,
	IN HANDLE hFinishEvent//종료 이벤트 입력
);

/**RED Start copy*/
typedef BOOL ( CALLBACK * LPFN_REDPROGRESS )(  HANDLE	 hCQHandle    , 	//CQ 프로세서 핸들
											   DWORD	 dwCurPos     , 	//progress 현재
											   BOOL		 bFinish      , 	//종료플래그
											   LPCTSTR	 lpstrTime	  ,		//타임코드
											   LPVOID	 lpUserData     	//CQOpen에서 입력받은 lpUserData
											);

typedef BOOL ( CALLBACK * LPFN_REDCQINFO   )(  HANDLE     hCQHandle    , 	//CQ 프로세서 핸들
											   HBITMAP    hBitmap      , 	//출력 이미지 
											   LPCTSTR    lpThumbPath  , 	//저장된 이미지 전체 경로
											   LPAVRESULT lpAVResult   ,
											   LPVOID     lpUserData			//CQOpen에서 입력받은 lpUserData
											);

typedef BOOL ( CALLBACK * LPFN_REDMEDIAINFO )( LPMEDIAINFORMATION  lpMediaInfo            );

typedef HANDLE ( WINAPI *LPFN_REDCQSET     )( IN LPCTSTR          lpDstFileName           , 	//파일 이름
											  IN DWORD            dwDstFileType           ,		//파일출력방식
											  IN DWORD            dwCheckMute					//묵음 처리시간(초)
											);

typedef HANDLE ( WINAPI *LPFN_REDCQOPEN    )( IN LPCTSTR          lpCaptureDeviceNameVideo, 		//입력 미디어 파일 전체 경로
											  IN LPCTSTR          lpCaptureDeviceNameAudio,
											  IN LPCTSTR          lpCheckProfilePath      , 		//입력 미디어 파일 전체 경로
											  IN HWND             hWnd                    , 		//Preview Window의 Handle
											  IN LPCTSTR          lpDstDir                , 		//썸네일 출력 디렉터리
											  IN LPCTSTR          lpOutFileName		      , 		//출력파일 형식 이름
											  IN UINT			  nTimeCodeSetting		  ,			//타임코드 셋팅값 0:SDI 1:RS422 2:None
											  IN RECT			  rectCheckSize			  ,
											  IN LPFN_REDCQINFO   lpFnCQInfo              , 		//처리 결과 정보 CALLBACK 함수
											  IN LPFN_REDPROGRESS lpFnProgress            , 		//Progress 정보 CALLBACK 함수
											  LPVOID              lpUserData            
											);														//LPFN_CQINFO callback함수로 그대로 출력

typedef HRESULT ( WINAPI *LPFN_REDCQCLOSE  )( HANDLE hCQHandle );
typedef HRESULT ( WINAPI *LPFN_REDCQRESUME )( HANDLE hCQHandle );
typedef HRESULT ( WINAPI *LPFN_REDCQPAUSE  )( HANDLE hCQHandle );

//RED개발 추가
typedef HRESULT ( WINAPI *LPFN_REDCQSTART             		    )( HANDLE	      hCQHandle                                                     );
typedef HRESULT ( WINAPI *LPFN_REDCQGETDEVICELIST     		    )( LPLIST_STRING lpVideoDeviceList		 , LPLIST_STRING lpAudioDeviceList		);
typedef HRESULT ( WINAPI *LPFN_REDCQGETVIDEOFORMATLIST		    )( IN LPCTSTR	 lpVideoName             , LPLIST_STRING lpVideoDeviceList		);
typedef HRESULT ( WINAPI *LPFN_REDCQGETAUDIOFORMATLIST		    )( IN LPCTSTR	 lpAudioName             , LPLIST_STRING lpAudioDeviceList		);
typedef HRESULT ( WINAPI *LPFN_REDCQSETVIDEOFORMAT    		    )( IN LPCTSTR	 lpVideoCaptureDeviceName, IN LPCTSTR	 lpVideoFormatName		);
typedef HRESULT ( WINAPI *LPFN_REDCQSETAUDIOFORMAT    		    )( IN LPCTSTR	 lpAudioCaptureDeviceName, IN LPCTSTR	 lpAudioFormatName      );
typedef HRESULT ( WINAPI *LPFN_REDCQGETDEVICELISTXML            )( OUT LPTSTR	 lpVideoDeviceList		 , OUT LPTSTR	 lpAudioDeviceList		);
typedef HRESULT ( WINAPI *LPFN_REDCQGETDEVICELISTXMLLENGTH      )( OUT DWORD*	 dwVideoDeviceList		 , OUT DWORD*	 dwAudioDeviceList		);
typedef HRESULT ( WINAPI *LPFN_REDCQGETVIDEOFORMATLISTXML       )( IN LPCTSTR	 lpVideoName      		 , OUT LPTSTR	 lpVideoFormatList		);
typedef HRESULT ( WINAPI *LPFN_REDCQGETVIDEOFORMATLISTXMLLENGTH )( IN LPCTSTR	 lpVideoName      		 , OUT DWORD*	 dwVideoFormatListLength);
typedef HRESULT ( WINAPI *LPFN_REDCQGETAUDIOFORMATLISTXML       )( IN LPCTSTR	 lpAudioName      		 , OUT LPTSTR	 lpAudioFormatList		);
typedef HRESULT ( WINAPI *LPFN_REDCQGETAUDIOFORMATLISTXMLLENGTH )( IN LPCTSTR	 lpAudioName      		 , OUT DWORD*	 dwAudioFormatListLength);
typedef HRESULT ( WINAPI *LPFN_REDCQGETDEVICEFORMATXML          )( OUT LPTSTR	 lpDeviceFormatList      										);
typedef HRESULT ( WINAPI *LPFN_REDCQGETDEVICEFORMATXMLLENGTH    )( OUT DWORD*	 dwDeviceFormatListLength										);

HANDLE WINAPI REDCQOpen	   ( IN LPCTSTR         lpCaptureDeviceNameVideo, 	//입력 비디오 캡쳐 보드 정보
							 IN LPCTSTR         lpCaptureDeviceNameAudio, 	//입력 오디오 캡쳐 보드 정보
							 IN LPCTSTR         lpCheckProfilePath		, 	//입력 프로파일이 저장된 주소
							 IN HWND			hWnd					, 	//Preview Window의 Handle
							 IN LPCTSTR         lpDstDir				, 	//썸네일 출력 디렉터리
							 IN LPCTSTR         lpOutFileName			, 	//출력파일 형식 이름
 							 IN UINT			nTimeCodeSetting		,	//타임코드 셋팅값 0:SDI 1:RS422 2:None
							 IN RECT			rectCheckSize			,
							 LPFN_REDCQINFO     lpFnCQInfo				, 	//처리결과 CALLBACK함수
							 LPFN_REDPROGRESS   lpFnProgress			, 	//Progress정보 CALLBACK함수
							 LPVOID             lpUserData
							);

HRESULT WINAPI REDCQStart 	( HANDLE hCQHandle );
HRESULT WINAPI REDCQClose 	( HANDLE hCQHandle );
HRESULT WINAPI REDCQPause 	( HANDLE hCQHandle );
HRESULT WINAPI REDCQResume	( HANDLE hCQHandle );

//RED 개발 추가함수
HRESULT WINAPI REDCQGetDeviceList			   ( OUT LPLIST_STRING lpVideoDeviceList       , OUT LPLIST_STRING lpAudioDeviceList	   );
HRESULT WINAPI REDCQGetVideoFormatList		   ( IN  LPCTSTR 	   lpVideoCaptureDeviceName, OUT LPLIST_STRING lpVideoFormatList	   );
HRESULT WINAPI REDCQGetAudioFormatList		   ( IN  LPCTSTR 	   lpAudioCaptureDeviceName, OUT LPLIST_STRING lpAudioFormatList	   );
HRESULT WINAPI REDCQSetVideoFormat	    	   ( IN  LPCTSTR 	   lpVideoName			   , IN  LPCTSTR	   lpVideoFormat		   );
HRESULT WINAPI REDCQSetAudioFormat	    	   ( IN  LPCTSTR 	   lpAudioName			   , IN  LPCTSTR	   lpAudioFormat		   );
HRESULT WINAPI REDCQGetDeviceListXML		   ( OUT LPTSTR  	   lpVideoDeviceList	   , OUT LPTSTR		   lpAudioDeviceList	   );
HRESULT WINAPI REDCQGetDeviceListXMLLength     ( OUT DWORD*  	   dwVideoDeviceList	   , OUT DWORD*		   dwAudioDeviceList	   );
HRESULT WINAPI REDCQGetVideoFormatListXML	   ( IN  LPCTSTR 	   lpVideoName			   , OUT LPTSTR		   lpVideoFormatList	   );
HRESULT WINAPI REDCQGetVideoFormatListXMLLength( IN  LPCTSTR 	   lpVideoName			   , OUT DWORD*		   dwVideoFormatListLength );
HRESULT WINAPI REDCQGetAudioFormatListXML	   ( IN  LPCTSTR 	   lpAudioName		 	   , OUT LPTSTR		   lpAudioFormatList	   );
HRESULT WINAPI REDCQGetAudioFormatListXMLLength( IN  LPCTSTR 	   lpAudioName			   , OUT DWORD*		   dwAudioFormatListLength );
HRESULT WINAPI REDCQGetDeviceFormatXMLLength   ( OUT DWORD*        dwDeviceFormatListLength  										   );
HRESULT WINAPI REDCQGetDeviceFormatXML         ( OUT LPTSTR        lpDeviceFormatList        										   );


#endif//_MEDIA_ANGEL_H_INCLUDE_