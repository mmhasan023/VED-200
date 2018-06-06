//2008.11.7
//by kiok ahn
//�̵�� ���� ��� API ����
//Catalog And Q.C. ���࿡ ������ API
///////////////////////////////////////////////////////////////////////////
// Cataloger And QC
///////////////////////////////////////////////////////////////////////////

#include "TTypeDefine.h"

#ifndef _MEDIA_ANGEL_H_INCLUDE_
#define _MEDIA_ANGEL_H_INCLUDE_


typedef BOOL (CALLBACK * LPFN_PROGRESS )( HANDLE  hCQHandle    , //CQ ���μ��� �ڵ�
										  DWORD   dwCurPos     , //progress ����
										  DWORD   dwTotal      , //progress ��ü
										  BOOL    bFinish      , //�����÷���
										  LPVOID  lpUserData   );//CQOpen���� �Է¹��� lpUserData
/*
typedef BOOL (CALLBACK * LPFN_CQINFO   )( HANDLE  nCQHandle    , //CQ ���μ��� �ڵ�
									      HBITMAP hBitmap      , //��� �̹��� 
									      LPCTSTR lpThumbPath  , //����� �̹��� ��ü ���
										  INT64   nMuteStart   , //����� �����˻翡 ���� ���۽ð�
										  INT64	  nMuteEnd     , //����� �����˻翡 ���� ����ð�
									      INT64   nFrameNumber , //����� ���� ���� ������ ��.
										  DOUBLE  dVilumeLevel , //Audio volume level
									      DWORD   dwProcessFlag, //ó�� �ɼ�, ���μ��� ����
										  LPVOID  lpUserData   );//CQOpen���� �Է¹��� lpUserData
*/

typedef BOOL (CALLBACK * LPFN_CQINFO   )( HANDLE     nCQHandle    , //CQ ���μ��� �ڵ�
									      HBITMAP    hBitmap      , //��� �̹��� 
									      LPCTSTR    lpThumbPath  , //����� �̹��� ��ü ���
										  LPAVRESULT lpAVResult   ,
										  LPVOID     lpUserData   );//CQOpen���� �Է¹��� lpUserData

typedef BOOL (CALLBACK * LPFN_MEDIAINFO)( LPMEDIAINFORMATION lpMediaInfo);

typedef HANDLE (WINAPI *LPFN_CQSET   )  (
										 IN LPCTSTR        lpDstFileName           , //���� �̸�
										 IN DWORD          dwDstFileType           , //������¹��
										 IN DWORD          dwCheckMute             );//���� ó���ð�(��)
										 

typedef HANDLE (WINAPI *LPFN_CQOPEN   ) (IN LPCTSTR        lpSrcPath             , //�Է� �̵�� ���� ��ü ���
										 IN LPCTSTR        lpCheckProfilePath    ,//�Է� �̵�� ���� ��ü ���
										 IN LPCTSTR        lpDstDir              , //����� ��� ���͸�
										 IN LPCTSTR        lpOutFileName		 , //������� ���� �̸�
										 IN DWORD          dwProcessFlag         , //ó�� �ɼ�
										 IN DWORD          dwCatelogSensitive    , //īŸ�α� ���� �������(1~9)
										 IN DWORD          dwCheckAudioMute      , //����� ���� �˻� �ð�(��)
										 IN LPFN_CQINFO    lpFnCQInfo            , //ó�� ��� ���� CALLBACK �Լ�
										 IN LPFN_PROGRESS  lpFnProgress          , //Progress ���� CALLBACK �Լ�
										 IN LPFN_MEDIAINFO lpFnMediaInfo         ,
										 LPVOID            lpUserData            );//LPFN_CQINFO callback�Լ��� �״�� ���
typedef HRESULT (WINAPI *LPFN_CQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQRESUME) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQPAUSE ) (HANDLE hCQHandle);

/*
HANDLE WINAPI CQOpen(IN LPCTSTR        lpSrcPath             , //�Է� �̵�� ���� ��ü ���
					 IN LPCTSTR        lpDstDir              , //����� ��� ���͸�
															   //  CQ_SAVE_IMG �ɼ��� ������ NULL �� ��� ������tmp ������ ���� �� ���� 
					 IN DWORD          dwProcessFlag         , //ó�� �ɼ�
					 IN DWORD          dwCatelogSensitive    , //īŸ�α� ���� �������(1~9)
					 IN LPFN_CQINFO    lpFnCQInfo            , //ó�� ��� ���� CALLBACK �Լ�
					 IN LPFN_PROGRESS  lpFnProgress          , //Progress ���� CALLBACK �Լ�
					 LPVOID            lpUserData            );//LPFN_CQINFO,LPFN_PROGRESS callback�Լ��� �״�� ���
*/
HANDLE WINAPI CQOpen(IN LPCTSTR      lpSrcPath         ,//�Է� �̵�� ���� ��ü ���
					 IN LPCTSTR      lpCheckProfilePath,//�Է� �̵�� ���� ��ü ���
					 IN LPCTSTR      lpDstDir          ,//����� ��� ���͸�
					 IN LPCTSTR      lpOutFileName     ,//������� ���� �̸�
					 IN DWORD        dwFlag            ,//ó�� �ɼ�
					 IN DWORD        dwSceneVal        ,//���ΰ���
					 IN DWORD        dwCheckAudioMute  ,//���� ó�� �ð�
					 LPFN_CQINFO     lpFnCQInfo        ,//ó����� CALLBACK�Լ�
					 LPFN_PROGRESS   lpFnProgress      ,//Progress���� CALLBACK�Լ�
					 LPFN_MEDIAINFO  lpFnMediaInfo     ,//�̵�� ���� ���� CALLBACK
					 LPVOID          lpUserData
					 );

HRESULT WINAPI CQClose (HANDLE hCQHandle);
HRESULT WINAPI CQPause (HANDLE hCQHandle);
HRESULT WINAPI CQResume(HANDLE hCQHandle);


#endif//_MEDIA_ANGEL_H_INCLUDE_