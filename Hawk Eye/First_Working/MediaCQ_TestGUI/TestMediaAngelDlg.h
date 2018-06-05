// TestMediaAngelDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "Gdiplus.h"
#include "afxcmn.h"
#include "Resource.h"
#define UM_CLOSE_CQ_HANDLE WM_APP +1
using namespace Gdiplus;

#pragma comment(lib,"gdiplus.lib")

#define CHECK_SCENE		1
#define CHECK_ERROR		2

#include "../MediaCQ/MediaCQ.h"
/*
///////////////////////////////////////////////////////////////////////////
//
//QC 처리 옵션, dwProcessFlag에 대한 정의
//
// 사용예 = (CQ_CATELOG|CQ_SAVE_IMG|CQ_QC_ALL) = Hex(0x8000FFFF) = Dec(2147549183)
// Catalog와 QC를 동시진행, QC는 모든 알고리즘을 적용하고, 모든 검출 프레임은 이미지 파일로 저장.
//
#ifndef _CQ_PROCESS_FLAG_
#define _CQ_PROCESS_FLAG_
#define CQ_CATELOG           0x80000000 // Dec(2147483648), Catalog 프로세서 활성화
#define CQ_SAVE_IMG          0x00010000 // Dec(2147483648) 검출 프레임을 이미지 파일(jpeg)로 저장
#define CQ_QC                0x00008000 // Dec(36863), QC 프로세서 활성화
#define CQ_QC_ALL            0x0000FFFF // Dec(65535), 전체 알고리즘 활성화
#define CQ_QC_EDGE_BLOC      0x00000001 // QC 1번, 사물의 가장자리로 블럭화가 발생하는 에러 검출.
#define CQ_QC_FS_STAR        0x00000002 // QC 2번, 전체 화면에 거처 번쩍이는 화면이 삽입된 에러 검출.
#define CQ_QC_FS_BLACK       0x00000004 // QC 3번, 전체 화면에 거처 검정색 프레임이 삽입된 에러 검출.
#define CQ_QC_AU_MUTE        0x00000008 // QC 4번, 오디오 묵음 검사.
#endif//_CQ_PROCESS_FLAG_
//
///////////////////////////////////////////////////////////////////////////


 
typedef BOOL (CALLBACK * LPFN_PROGRESS)( HANDLE hCQHandle , //CQ 프로세서 핸들
										DWORD dwCurPos   , //progress 현재
										DWORD dwTotal    , //progress 전체
										BOOL  bFinish    );//종료플래그
typedef BOOL (CALLBACK * LPFN_CQINFO  )( HANDLE  nCQHandle    , //CQ 프로세서 핸들
										HBITMAP hBitmap      , //출력 이미지 
										LPCTSTR lpThumbPath  , //저장된 이미지 전체 경로
										INT64   nMuteStart   , //오디오 묵음검사에 대한 시작시간
										INT64	 nMuteEnd     , //오디오 묵음검사에 대한 종료시간
										INT64   nFrameNumber , //결과에 대한 현재 프레임 수.
										DWORD   dwProcessFlag);//처리 옵션, 프로세스 종류


typedef HANDLE (WINAPI *LPFN_CQSET   )  (
	IN LPCTSTR        lpDstFileName           , //파일 이름
	IN DWORD          dwDstFileType           , //파일출력방식
	IN DWORD          dwCheckMute             );//묵음 처리시간(초)


typedef HANDLE (WINAPI *LPFN_CQOPEN   ) (IN LPCTSTR        lpSrcPath             , //입력 미디어 파일 전체 경로
										 IN LPCTSTR        lpDstDir              , //썸네일 출력 디렉터리
										 IN LPCTSTR        lpOutFileName		 , //출력파일 형식 이름
										 IN DWORD          dwProcessFlag         , //처리 옵션
										 IN DWORD          dwCatelogSensitive    , //카타로그 감도 조정계수(1~9)
										 IN DWORD          dwCheckAudioMute      , //오디오 묵음 검사 시간(초)
										 IN LPFN_CQINFO    lpFnCQInfo            , //처리 결과 정보 CALLBACK 함수
										 IN LPFN_PROGRESS  lpFnProgress          );//Progress 정보 CALLBACK 함수
typedef HRESULT (WINAPI *LPFN_CQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQRESUME) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQPAUSE ) (HANDLE hCQHandle);
*/
class CTestMediaControl;
class CMediaFileOut;
// CTestMediaAngelDlg 대화 상자
class CTestMediaAngelDlg : public CDialog
{
// 생성입니다.
public:
	HINSTANCE m_hDll;
	static BOOL GetEncCLSID(WCHAR *mime, CLSID *pClsid);
	
	CTestMediaAngelDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TESTMEDIAANGEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


public:
	static BOOL CALLBACK OnRcvInfo( HANDLE     nCQHandle    , //CQ 프로세서 핸들
									HBITMAP    hBitmap      , //출력 이미지 
									LPCTSTR    lpThumbPath  , //저장된 이미지 전체 경로
									LPAVRESULT lpAVResult   ,
									LPVOID     lpUserData   );//처리 옵션, 프로세스 종류
/*
	static BOOL CALLBACK OnRcvInfo( HANDLE  nCQHandle    , //CQ 프로세서 핸들
									HBITMAP hBitmap      , //출력 이미지 
									LPCTSTR lpThumbPath  , //저장된 이미지 전체 경로
									INT64   nMuteStart,
									INT64   nMuteEnd,
									INT64   nFrameNumber , //결과에 대한 현재 프레임 수.
									DOUBLE  dVilumeLevel ,
									DWORD   dwProcessFlag,
									LPVOID  lpUserData   );//처리 옵션, 프로세스 종류
*/
	static BOOL CALLBACK OnRcvProgress( HANDLE hCQHandle  ,//CQ 프로세서 핸들
										DWORD dwCurPos    ,//progress 현재
										DWORD dwTotal     ,//progress 전체
										BOOL  bFinish     ,//종료플래그
										LPVOID  lpUserData);

	static BOOL CALLBACK OnMediaInfo( LPMEDIAINFORMATION lpMediaInfo);


// 구현입니다.
protected:
	HICON m_hIcon;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInButton();
	afx_msg void OnBnClickedOutButton();
	CEdit m_strOutPath;
	afx_msg void OnBnClickedOk();
	CEdit m_strInputPath;
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnBnClickedPauseButton();
	afx_msg void OnBnClickedResumeButton();
	afx_msg void OnDestroy();
	CProgressCtrl m_nCurProgress;
	afx_msg void OnBnClickedStopButton();
	CButton m_StartButton;
	afx_msg LRESULT OnCloseCQHandle(WPARAM wparam, LPARAM lpsram);//UM_CLOSE_CQ_HANDLE
//
protected:
	LPFN_CQOPEN    m_lpfnArchiveOpen   ;
	LPFN_CQCLOSE   m_lpfnArchiveClose  ;
	LPFN_CQPAUSE   m_lpfnArchivePause  ;
	LPFN_CQRESUME  m_lpfnArchiveResume ;
	LPFN_CQSET	   m_lpfnArchiveSet    ;


	BOOL InitDLL( void );
public:
	void ResetFlag(HANDLE nCQHandle);
	CButton m_cbSceneCheck;
	CButton m_cbErrorCheck;
	CEdit m_nScene_Val;
	HANDLE* m_HandleProc;		//현재 동작중인 핸들배열
	CListCtrl m_nWorkingList;	//컨트롤 리스트
	int m_nTotalProc;			//현재 동작중인 핸들 전체 갯수
	HANDLE m_nMyHandle;			//파일을 시작하기위한 핸들
	int m_nSelectProc;			//사용자가 선택한 미디어
	afx_msg void OnNMClickWorkingList(NMHDR *pNMHDR, LRESULT *pResult);
	int* m_nProcProgress;		//현재 동작중인 미디어에 대한 진행도 배열
	CProgressCtrl m_nTotalProgress; //전체 프로그레스바 컨트롤 변수
	afx_msg void OnBnClickedTotalstopButton();
	afx_msg void OnBnClickedTotalpauseButton();
	afx_msg void OnBnClickedTotalresumeButton();
	CButton m_nCheckImageOut;
	CButton m_cbMute;
	CEdit m_CheckMute;
	CEdit m_FilePreName;
	int m_nTotalCount;


	static CTestMediaControl* m_pMControl;
	static CMediaFileOut*     m_pfOut;

	afx_msg void OnClose();

	CEdit m_EditTotalCount;
	//afx_msg void OnBnClickedInButton2();
	afx_msg void OnBnClickedButtonInputProfile();
	CEdit m_editCheckProfilePath;
};
