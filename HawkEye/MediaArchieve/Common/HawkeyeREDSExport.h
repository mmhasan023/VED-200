//2008.11.7
//by kiok ahn
//�̵�� ���� ��� API ����
//Catalog And Q.C. ���࿡ ������ API
///////////////////////////////////////////////////////////////////////////
// Cataloger And QC
///////////////////////////////////////////////////////////////////////////

#include "REDTTypeDefine.h"
#include "mmsystem.h"

#ifndef _MEDIA_ANGEL_H_INCLUDE_
#define _MEDIA_ANGEL_H_INCLUDE_


typedef BOOL (CALLBACK * LPFN_REDPROGRESS )(  HANDLE	hCQHandle    , //CQ ���μ��� �ڵ�
											  DWORD		dwCurPos     , //progress ����
											  BOOL		bFinish      , //�����÷���
											  TIMECODE	tc			 , //Ÿ���ڵ�
											  LPVOID	lpUserData   );//CQOpen���� �Է¹��� lpUserData

typedef BOOL (CALLBACK * LPFN_REDCQINFO   )(  HANDLE     hCQHandle    , //CQ ���μ��� �ڵ�
											  HBITMAP    hBitmap      , //��� �̹��� 
											  LPCTSTR    lpThumbPath  , //����� �̹��� ��ü ���
											  LPAVRESULT lpAVResult   ,
											  LPVOID     lpUserData   );//CQOpen���� �Է¹��� lpUserData

typedef BOOL (CALLBACK * LPFN_REDMEDIAINFO)( LPMEDIAINFORMATION lpMediaInfo);

typedef HANDLE (WINAPI *LPFN_REDCQSET   )  (
										 IN LPCTSTR        lpDstFileName           , //���� �̸�
										 IN DWORD          dwDstFileType           , //������¹��
										 IN DWORD          dwCheckMute             );//���� ó���ð�(��)
										 

typedef HANDLE (WINAPI *LPFN_REDCQOPEN   ) (
										 IN LPCTSTR        		lpCaptureDeviceNameVideo    , //�Է� �̵�� ���� ��ü ���
										 IN LPCTSTR        		lpCaptureDeviceNameAudio    ,
										 IN LPCTSTR        		lpCheckProfilePath			, //�Է� �̵�� ���� ��ü ���
										 IN HWND           		hWnd						, //Preview Window�� Handle
										 IN LPCTSTR        		lpDstDir					, //����� ��� ���͸�
										 IN LPCTSTR        		lpOutFileName				, //������� ���� �̸�
										 IN UINT		   		nTimeCodeSetting			, //Ÿ���ڵ� ���ð� 0:SDI 1:RS422 2:None
										 IN RECT				rectCheckSize				,
										 IN LPFN_REDCQINFO		lpFnCQInfo            		, //ó�� ��� ���� CALLBACK �Լ�
										 IN LPFN_REDPROGRESS	lpFnProgress          		, //Progress ���� CALLBACK �Լ�
										 LPVOID					lpUserData            		);//LPFN_CQINFO callback�Լ��� �״�� ���

typedef HRESULT (WINAPI *LPFN_REDCQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_REDCQRESUME) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_REDCQPAUSE ) (HANDLE hCQHandle);



//RED���� �߰�
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


HANDLE WINAPI REDCQOpen(IN LPCTSTR				lpCaptureDeviceNameVideo	, //�Է� �̵�� ���� ��ü ���
					 	IN LPCTSTR				lpCaptureDeviceNameAudio	,
					 	IN LPCTSTR				lpCheckProfilePath		, //�Է� �̵�� ���� ��ü ���
						IN HWND					hWnd						, //Preview Window�� Handle
					 	IN LPCTSTR				lpDstDir					, //����� ��� ���͸�
					 	IN LPCTSTR				lpOutFileName			, //������� ���� �̸�
						IN UINT					nTimeCodeSetting			, //Ÿ���ڵ� ���ð� 0:SDI 1:RS422 2:None
					 	IN LPFN_REDCQINFO		lpFnCQInfo				, //ó����� CALLBACK�Լ�
					 	IN LPFN_REDPROGRESS		lpFnProgress				, //Progress���� CALLBACK�Լ�
					 	LPVOID					lpUserData
					 	);
HRESULT WINAPI REDCQStart 	(HANDLE hCQHandle);
HRESULT WINAPI REDCQClose 	(HANDLE hCQHandle);
HRESULT WINAPI REDCQPause 	(HANDLE hCQHandle);
HRESULT WINAPI REDCQResume	(HANDLE hCQHandle);

//RED ���� �߰��Լ�
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
//�̵���� �ε��� �ܺο��� �����ϱ� ���� API
typedef HANDLE (WINAPI *LPFN_LOWCQOPEN   ) (
					   IN PBITMAPINFOHEADER  lpVideoInfo       ,//�Է� ���� Secquency ����
					   IN PPCMWAVEFORMAT     lpAudioInfo       ,//�Է� ����� Secquency ����
					   IN REFERENCE_TIME     rtDuration        ,//�̵�� ��ü ����
					   IN REFERENCE_TIME     rtTimeperFrame    ,//�����Ӵ� �Ҵ�� �ð�
					   IN UINT               nTotalFrames      ,//��ü ���� ������ ��, �ش� ������ 0
					   IN LPCTSTR            lpCheckProfilePath,//�˼� �������� ��ü ��� ��) "c:\\1.xml"
					   IN LPCTSTR            lpDstDir          ,//����� ��� ���͸�
					   IN LPCTSTR            lpOutFileName     ,//������������̸�
					   LPFN_REDCQINFO        lpFnCQInfo        ,
					   LPFN_REDPROGRESS      lpFnProgress      ,
					   LPVOID                lpUserData        );
typedef HRESULT (WINAPI *LPFN_LOWCQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_LOWSETVIDEOSTREAMDATA) ( HANDLE hCQHandle, DOUBLE dbSampleTime, const LPBYTE lpData, const int& nDataSize );
typedef HRESULT (WINAPI *LPFN_LOWSETAUDIOSTREAMDATA) ( HANDLE hCQHandle, REFERENCE_TIME rtStartTime, REFERENCE_TIME rtEndTime, const LPBYTE lpData, const DWORD& dwSize );



HANDLE WINAPI LOWCQOpen( 
					   IN PBITMAPINFOHEADER  lpVideoInfo       ,//�Է� ���� Secquency ����
					   IN PPCMWAVEFORMAT     lpAudioInfo       ,//�Է� ����� Secquency ����
					   IN REFERENCE_TIME     rtDuration        ,//�̵�� ��ü ����
					   IN REFERENCE_TIME     rtTimeperFrame    ,//�����Ӵ� �Ҵ�� �ð�
					   IN UINT               nTotalFrames      ,//��ü ���� ������ ��, �ش� ������ 0
					   IN LPCTSTR            lpCheckProfilePath,//�˼� �������� ��ü ��� ��) "c:\\1.xml"
					   IN LPCTSTR            lpDstDir          ,//����� ��� ���͸�
					   IN LPCTSTR            lpOutFileName     ,//������������̸�
					   LPFN_REDCQINFO        lpFnCQInfo        ,
					   LPFN_REDPROGRESS      lpFnProgress      ,
					   LPVOID                lpUserData        );
HRESULT WINAPI LOWCQClose           ( HANDLE hCQHandle );
HRESULT WINAPI LOWSetVideoStreamData( HANDLE hCQHandle, DOUBLE dbSampleTime, const LPBYTE lpData, const int& nDataSize );
HRESULT WINAPI LOWSetAudioStreamData( HANDLE hCQHandle, REFERENCE_TIME rtStartTime, REFERENCE_TIME rtEndTime, const LPBYTE lpData, const DWORD& dwSize );
//�̵���� �ε��� �ܺο��� �����ϱ� ���� API
/////////////////////////////////////////////////////////////////////////////////////////////////

#endif//_MEDIA_ANGEL_H_INCLUDE_