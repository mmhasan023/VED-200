// TestMediaAngelDlg.h : ��� ����
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
//QC ó�� �ɼ�, dwProcessFlag�� ���� ����
//
// ��뿹 = (CQ_CATELOG|CQ_SAVE_IMG|CQ_QC_ALL) = Hex(0x8000FFFF) = Dec(2147549183)
// Catalog�� QC�� ��������, QC�� ��� �˰����� �����ϰ�, ��� ���� �������� �̹��� ���Ϸ� ����.
//
#ifndef _CQ_PROCESS_FLAG_
#define _CQ_PROCESS_FLAG_
#define CQ_CATELOG           0x80000000 // Dec(2147483648), Catalog ���μ��� Ȱ��ȭ
#define CQ_SAVE_IMG          0x00010000 // Dec(2147483648) ���� �������� �̹��� ����(jpeg)�� ����
#define CQ_QC                0x00008000 // Dec(36863), QC ���μ��� Ȱ��ȭ
#define CQ_QC_ALL            0x0000FFFF // Dec(65535), ��ü �˰��� Ȱ��ȭ
#define CQ_QC_EDGE_BLOC      0x00000001 // QC 1��, �繰�� �����ڸ��� ��ȭ�� �߻��ϴ� ���� ����.
#define CQ_QC_FS_STAR        0x00000002 // QC 2��, ��ü ȭ�鿡 ��ó ��½�̴� ȭ���� ���Ե� ���� ����.
#define CQ_QC_FS_BLACK       0x00000004 // QC 3��, ��ü ȭ�鿡 ��ó ������ �������� ���Ե� ���� ����.
#define CQ_QC_AU_MUTE        0x00000008 // QC 4��, ����� ���� �˻�.
#endif//_CQ_PROCESS_FLAG_
//
///////////////////////////////////////////////////////////////////////////


 
typedef BOOL (CALLBACK * LPFN_PROGRESS)( HANDLE hCQHandle , //CQ ���μ��� �ڵ�
										DWORD dwCurPos   , //progress ����
										DWORD dwTotal    , //progress ��ü
										BOOL  bFinish    );//�����÷���
typedef BOOL (CALLBACK * LPFN_CQINFO  )( HANDLE  nCQHandle    , //CQ ���μ��� �ڵ�
										HBITMAP hBitmap      , //��� �̹��� 
										LPCTSTR lpThumbPath  , //����� �̹��� ��ü ���
										INT64   nMuteStart   , //����� �����˻翡 ���� ���۽ð�
										INT64	 nMuteEnd     , //����� �����˻翡 ���� ����ð�
										INT64   nFrameNumber , //����� ���� ���� ������ ��.
										DWORD   dwProcessFlag);//ó�� �ɼ�, ���μ��� ����


typedef HANDLE (WINAPI *LPFN_CQSET   )  (
	IN LPCTSTR        lpDstFileName           , //���� �̸�
	IN DWORD          dwDstFileType           , //������¹��
	IN DWORD          dwCheckMute             );//���� ó���ð�(��)


typedef HANDLE (WINAPI *LPFN_CQOPEN   ) (IN LPCTSTR        lpSrcPath             , //�Է� �̵�� ���� ��ü ���
										 IN LPCTSTR        lpDstDir              , //����� ��� ���͸�
										 IN LPCTSTR        lpOutFileName		 , //������� ���� �̸�
										 IN DWORD          dwProcessFlag         , //ó�� �ɼ�
										 IN DWORD          dwCatelogSensitive    , //īŸ�α� ���� �������(1~9)
										 IN DWORD          dwCheckAudioMute      , //����� ���� �˻� �ð�(��)
										 IN LPFN_CQINFO    lpFnCQInfo            , //ó�� ��� ���� CALLBACK �Լ�
										 IN LPFN_PROGRESS  lpFnProgress          );//Progress ���� CALLBACK �Լ�
typedef HRESULT (WINAPI *LPFN_CQCLOSE ) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQRESUME) (HANDLE hCQHandle);
typedef HRESULT (WINAPI *LPFN_CQPAUSE ) (HANDLE hCQHandle);
*/
class CTestMediaControl;
class CMediaFileOut;
// CTestMediaAngelDlg ��ȭ ����
class CTestMediaAngelDlg : public CDialog
{
// �����Դϴ�.
public:
	HINSTANCE m_hDll;
	static BOOL GetEncCLSID(WCHAR *mime, CLSID *pClsid);
	
	CTestMediaAngelDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TESTMEDIAANGEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


public:
	static BOOL CALLBACK OnRcvInfo( HANDLE     nCQHandle    , //CQ ���μ��� �ڵ�
									HBITMAP    hBitmap      , //��� �̹��� 
									LPCTSTR    lpThumbPath  , //����� �̹��� ��ü ���
									LPAVRESULT lpAVResult   ,
									LPVOID     lpUserData   );//ó�� �ɼ�, ���μ��� ����
/*
	static BOOL CALLBACK OnRcvInfo( HANDLE  nCQHandle    , //CQ ���μ��� �ڵ�
									HBITMAP hBitmap      , //��� �̹��� 
									LPCTSTR lpThumbPath  , //����� �̹��� ��ü ���
									INT64   nMuteStart,
									INT64   nMuteEnd,
									INT64   nFrameNumber , //����� ���� ���� ������ ��.
									DOUBLE  dVilumeLevel ,
									DWORD   dwProcessFlag,
									LPVOID  lpUserData   );//ó�� �ɼ�, ���μ��� ����
*/
	static BOOL CALLBACK OnRcvProgress( HANDLE hCQHandle  ,//CQ ���μ��� �ڵ�
										DWORD dwCurPos    ,//progress ����
										DWORD dwTotal     ,//progress ��ü
										BOOL  bFinish     ,//�����÷���
										LPVOID  lpUserData);

	static BOOL CALLBACK OnMediaInfo( LPMEDIAINFORMATION lpMediaInfo);


// �����Դϴ�.
protected:
	HICON m_hIcon;
	// ������ �޽��� �� �Լ�
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
	HANDLE* m_HandleProc;		//���� �������� �ڵ�迭
	CListCtrl m_nWorkingList;	//��Ʈ�� ����Ʈ
	int m_nTotalProc;			//���� �������� �ڵ� ��ü ����
	HANDLE m_nMyHandle;			//������ �����ϱ����� �ڵ�
	int m_nSelectProc;			//����ڰ� ������ �̵��
	afx_msg void OnNMClickWorkingList(NMHDR *pNMHDR, LRESULT *pResult);
	int* m_nProcProgress;		//���� �������� �̵� ���� ���൵ �迭
	CProgressCtrl m_nTotalProgress; //��ü ���α׷����� ��Ʈ�� ����
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
