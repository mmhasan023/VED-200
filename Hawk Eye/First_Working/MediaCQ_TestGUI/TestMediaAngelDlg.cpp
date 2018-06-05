// TestMediaAngelDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TestMediaAngel.h"
#include "TestMediaAngelDlg.h"
#include "resource.h"
#include "../Common/apputil.h"

#include "MediaFileOut.h"
#include "TestMediaControl.h"
//#include <vld.h>
//#pragma comment(lib,"vld")

#include "TTypeDefine.h"

#define NOT_CHECKED			0
#define CHECKED				1

#define	NOT_DEFINE_MODE		0

static CString g_szMutePath;

//#include "ExtractManager.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
DWORD g_start = 0;
DWORD g_end   = 0;

/*

int WINAPI Myfunc(DWORD, UINT);

typedef UINT(CALLBACK* LPFNDLLFUNC1)(DWORD,UINT);

LPFNDLLFUNC1 lpfnDLLFunc1;
DWORD dwParam1;
UINT uParam2, uReturnVal;
*/



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
GdiplusStartupInput g_gdiplusStartupInput;
ULONG_PTR			g_gdiplusToken;
GdiplusStartupOutput g_gdiplusStartupOutput;
CTestMediaControl* CTestMediaAngelDlg::m_pMControl=NULL;
CMediaFileOut*     CTestMediaAngelDlg::m_pfOut    =NULL;
static HWND g_hWND = NULL;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestMediaAngelDlg 대화 상자




CTestMediaAngelDlg::CTestMediaAngelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMediaAngelDlg::IDD, pParent)
	, m_nTotalProc(0)
	, m_nProcProgress(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMControl = NULL;
}

void CTestMediaAngelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTPUT_MEDIA, m_strOutPath);
	DDX_Control(pDX, IDC_INPUT_MEDIA, m_strInputPath);
	DDX_Control(pDX, IDC_CUR_PROGRESS, m_nCurProgress);
	DDX_Control(pDX, IDC_START_BUTTON, m_StartButton);
	DDX_Control(pDX, IDC_SCENE_CHECK, m_cbSceneCheck);
	DDX_Control(pDX, IDC_ERROR_CHECK, m_cbErrorCheck);
	DDX_Control(pDX, IDC_SCENE_VAL_EDIT, m_nScene_Val);
	DDX_Control(pDX, IDC_WORKING_LIST, m_nWorkingList);
	DDX_Control(pDX, IDC_TOTAL_PROGRESS, m_nTotalProgress);
	DDX_Control(pDX, IDC_CHECK1, m_nCheckImageOut);
	DDX_Control(pDX, IDC_CHECK_MUTE, m_cbMute);
	DDX_Control(pDX, IDC_EDIT_MUTETIME, m_CheckMute);
	DDX_Control(pDX, IDC_EDIT_OUTFILE, m_FilePreName);

	DDX_Control(pDX, IDC_EDIT1, m_EditTotalCount);
	DDX_Control(pDX, IDC_INPUT_CHECK_PROFILE, m_editCheckProfilePath);
}

//20081205 by kiok ahn -> VC++ 6.0 start
BEGIN_MESSAGE_MAP(CTestMediaAngelDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//{{AFX_MSG_MAP(CTestMediaAngelDlg)
	ON_BN_CLICKED(IDC_IN_BUTTON, OnBnClickedInButton)
	ON_BN_CLICKED(IDC_OUT_BUTTON, OnBnClickedOutButton)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_START_BUTTON, OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_PAUSE_BUTTON, OnBnClickedPauseButton)
	ON_BN_CLICKED(IDC_RESUME_BUTTON, OnBnClickedResumeButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, OnBnClickedStopButton)
	ON_BN_CLICKED(IDC_TOTALSTOP_BUTTON, OnBnClickedTotalstopButton)
	ON_BN_CLICKED(IDC_TOTALPAUSE_BUTTON, OnBnClickedTotalpauseButton)
	ON_BN_CLICKED(IDC_TOTALRESUME_BUTTON, OnBnClickedTotalresumeButton)
	ON_NOTIFY(NM_CLICK, IDC_WORKING_LIST, OnNMClickWorkingList)
	ON_MESSAGE(UM_CLOSE_CQ_HANDLE, OnCloseCQHandle)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
//	ON_BN_CLICKED(IDC_IN_BUTTON2, &CTestMediaAngelDlg::OnBnClickedInButton2)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_PROFILE, &CTestMediaAngelDlg::OnBnClickedButtonInputProfile)
END_MESSAGE_MAP()
/*
BEGIN_MESSAGE_MAP(CTestMediaAngelDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_IN_BUTTON, &CTestMediaAngelDlg::OnBnClickedInButton)
	ON_BN_CLICKED(IDC_OUT_BUTTON, &CTestMediaAngelDlg::OnBnClickedOutButton)
	ON_BN_CLICKED(IDOK, &CTestMediaAngelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_START_BUTTON, &CTestMediaAngelDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_PAUSE_BUTTON, &CTestMediaAngelDlg::OnBnClickedPauseButton)
	ON_BN_CLICKED(IDC_RESUME_BUTTON, &CTestMediaAngelDlg::OnBnClickedResumeButton)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CTestMediaAngelDlg::OnBnClickedStopButton)
	ON_NOTIFY(NM_CLICK, IDC_WORKING_LIST, &CTestMediaAngelDlg::OnNMClickWorkingList)
	ON_BN_CLICKED(IDC_TOTALSTOP_BUTTON, &CTestMediaAngelDlg::OnBnClickedTotalstopButton)
	ON_BN_CLICKED(IDC_TOTALPAUSE_BUTTON, &CTestMediaAngelDlg::OnBnClickedTotalpauseButton)
	ON_BN_CLICKED(IDC_TOTALRESUME_BUTTON, &CTestMediaAngelDlg::OnBnClickedTotalresumeButton)
END_MESSAGE_MAP()
*/
//20081205 by kiok ahn -> VC++ 6.0
LRESULT CTestMediaAngelDlg::OnCloseCQHandle(WPARAM wparam, LPARAM lpsram)
{
	g_end = timeGetTime();
	CString szMsg;
	szMsg.Format(_T("time = %f second"), (double)(g_end-g_start)/1000.0 );
#ifdef DEBUG
	AfxMessageBox(szMsg);
#endif
	if(m_lpfnArchiveClose)
		m_lpfnArchiveClose((HANDLE)wparam);

	CTestMediaAngelDlg *pDlg = (CTestMediaAngelDlg*)wparam;

	return S_OK;
}

BOOL CTestMediaAngelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_hWND = this->m_hWnd;
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitDLL();
	CString temp;
	temp.Format(_T("%d"),1);
	m_nScene_Val.SetWindowText(temp);
	temp.Format(_T("%d"),10);
	m_CheckMute.SetWindowText(temp);
	if(GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, & g_gdiplusStartupOutput))
	{
		exit(0);
	}
	m_HandleProc = new HANDLE[100];
	m_nProcProgress = new int[100];
	for(int i=0;i<100;i++)
	{
		m_HandleProc   [i]=NULL;
		m_nProcProgress[i]=0;
	}
	ListView_SetExtendedListViewStyle(::GetDlgItem(m_hWnd,IDC_WORKING_LIST),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_nWorkingList.InsertColumn(0,_T("Media File"),LVCFMT_LEFT,300,-1);
	m_nWorkingList.InsertColumn(1,_T("Out Folder"),LVCFMT_LEFT,300,-1);
	m_nWorkingList.InsertColumn(2,_T("Progress" ),LVCFMT_LEFT,122,-1);
	m_nTotalProc=0;
	
	m_nTotalProgress.SetRange(0,100);
	if( m_pMControl==NULL ) 
		m_pMControl = new CTestMediaControl( this );
	if(m_pfOut==NULL) m_pfOut = new CMediaFileOut();
	m_nSelectProc = 0;
	m_nTotalCount=1;
	

	CString szPath = _T("c:\\TestCheckResult");
	if( ::GetFileAttributes(szPath) == INVALID_FILE_ATTRIBUTES )
		CreateDirectory(szPath,NULL);
	m_strOutPath.SetWindowText(szPath);

	UpdateData(FALSE);

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestMediaAngelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestMediaAngelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestMediaAngelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL ResumeFlag = FALSE;
BOOL StopFlag   = FALSE;
BOOL StartFlag  =  TRUE;


void CTestMediaAngelDlg::OnBnClickedInButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString m_strFileName;
	CString strFilter;
	strFilter.Format(IDS_FILE_FILTER);

	CFileDialog dlg(TRUE, NULL, NULL,
	(OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
	(LPCTSTR)strFilter, NULL);

	if(dlg.DoModal()==IDOK)
	{
		m_strInputPath.SetWindowText(dlg.GetPathName());
	}
}



void CTestMediaAngelDlg::OnBnClickedOutButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ITEMIDLIST      *pidlBrowse;
	char			Pathname[MAX_PATH]; 
	BROWSEINFO		BrInfo;
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot  = NULL         ; 

	memset( &BrInfo, 0, sizeof(BrInfo) );

	BrInfo.pszDisplayName =(LPTSTR)Pathname;
	CString                      nOutFolder;
	nOutFolder.LoadString(IDS_OUT_FOLDER)  ;
	BrInfo.lpszTitle =           nOutFolder;
	BrInfo.ulFlags =   BIF_DONTGOBELOWDOMAIN;
	// 다이얼로그 띄우기
	pidlBrowse = SHBrowseForFolder(&BrInfo);

	if( pidlBrowse != NULL)
	{
		// 패스를 얻어옴
		BOOL bSuccess = ::SHGetPathFromIDList(pidlBrowse, (LPTSTR)Pathname); 

		if ( bSuccess )
		{  
			m_strOutPath.SetWindowText((LPTSTR)Pathname);
			UpdateData(FALSE);
		}
		else
		{
			CString nErrFolderName;
			nErrFolderName.LoadString(IDS_ERROR_FOLDERNAME);
			MessageBox(nErrFolderName, _T("lol"), MB_OKCANCEL|MB_ICONASTERISK ); 
		}
	}
}
void CTestMediaAngelDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!StartFlag)
	{

		for(int i=0;i<m_nTotalProc;i++)
		{
			if(m_nProcProgress[i]!=100)
			{
				HANDLE StopHandle = m_HandleProc[i];
				(m_lpfnArchivePause)(StopHandle);
			}
		}

		CString MsgReset;
		MsgReset.LoadString(IDS_MSG_RESET);
		int buttonReturn = AfxMessageBox(MsgReset,MB_OK);
		if(buttonReturn==IDOK)
		{
			CString Stop;
			Stop.Format(_T("Stop"));
			for(int i=0;i<m_nTotalProc;i++)
			{
				if(m_nProcProgress[i]!=100)
				{
					m_nWorkingList.SetItemText(i,2,(LPCTSTR)Stop);
					HANDLE StopHandle = m_HandleProc[i];
					m_nProcProgress[i]=100;
					(m_lpfnArchiveClose)(StopHandle);
				}
			}
			ResumeFlag = FALSE;
			StopFlag   = FALSE;
			StartFlag  =  TRUE;
			m_nCurProgress.SetPos(0);
			m_nTotalProgress.SetPos(0);

		}
	}	
	
	
	
	//OnBnClickedTotalstopButton();
	OnOK();
}

void CTestMediaAngelDlg::OnBnClickedStartButton()
{
	UpdateData();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_OUTPUT_MEDIA)->GetWindowText(g_szMutePath);
	
	CString InPath,OutPath,OutFileName  ;
	m_strInputPath.GetWindowText(InPath);
	m_strOutPath.GetWindowText(OutPath) ;


	LPCTSTR lpCheckProfilePath = NULL;
	TCHAR szCheckProfilePath[MAX_PATH*2]={0};
	m_editCheckProfilePath.GetWindowText(szCheckProfilePath,MAX_PATH*2); //CAppUtil::GetMainPath();
//	szCheckProfilePath += _T("check_profile.xml");
	if( ::GetFileAttributes(szCheckProfilePath) != INVALID_FILE_ATTRIBUTES )
		lpCheckProfilePath = (LPCTSTR)szCheckProfilePath;

	m_FilePreName.GetWindowText(OutFileName);
	DWORD dwOptionFlag =0;
	m_nMyHandle=NULL;
	DWORD FileType = 0;
	DWORD CheckMute = 0;

	if(InPath != "" && OutPath != "")
	{
		g_start = timeGetTime();
		CString strSensitive;
		m_nScene_Val.GetWindowText(strSensitive);
		DWORD dwCatalogSensitive = (DWORD)_ttoi((LPCTSTR)strSensitive);
		CString strMute;
		m_CheckMute.GetWindowText(strMute);
		DWORD dwCheckAudioMute = 0;//(DWORD)_ttoi((LPCTSTR)strMute);
		m_nWorkingList.InsertItem(m_nTotalProc,(LPCTSTR)InPath);
		m_nWorkingList.SetItemText(m_nTotalProc,1,(LPCTSTR)OutPath);
		m_nWorkingList.SetItemText(m_nTotalProc,2,_T("0 %"));
		m_nMyHandle=(m_lpfnArchiveOpen)(    (LPCTSTR)InPath                  ,
											lpCheckProfilePath               ,
											(LPCTSTR)OutPath                 ,
											(LPCTSTR)OutFileName             ,
											dwOptionFlag                     ,
											dwCatalogSensitive               ,
											dwCheckAudioMute                 ,
											CTestMediaAngelDlg::OnRcvInfo    ,
											CTestMediaAngelDlg::OnRcvProgress,
											CTestMediaAngelDlg::OnMediaInfo  ,
											(LPVOID)this                     );
		if(m_nMyHandle==NULL)
		{
			AfxMessageBox(_T("Error Function - CQOpen()"));
		}
		StopFlag  = TRUE ;
		StartFlag = FALSE;

		m_HandleProc[m_nTotalProc]=m_nMyHandle;
		m_nTotalProc++;
	}
	else
	{
		CString nErrMsg;
		nErrMsg.LoadString(IDS_ERROR_SETPATH);
		AfxMessageBox(nErrMsg);
	}
}

void CTestMediaAngelDlg::OnBnClickedPauseButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("스탑버튼"));
	if(m_nSelectProc!=-1)
	{
		if(StopFlag)
		{
			
			StopFlag       = FALSE;
			ResumeFlag     = TRUE;
			HANDLE PauseHandle = m_HandleProc[m_nSelectProc];
			CString pause;
			pause.Format(_T("Pause"));
			CString strCurPos= m_nWorkingList.GetItemText(m_nSelectProc,2);
			m_nProcProgress[m_nSelectProc] = _ttoi(strCurPos);
			m_nWorkingList.SetItemText(m_nSelectProc,2,(LPCTSTR)pause);
			(m_lpfnArchivePause)(PauseHandle);
			
		}
		else if(StartFlag)
		{
			CString nErrMsg;
			nErrMsg.LoadString(IDS_ERROR_NOTSTART);
			AfxMessageBox(nErrMsg);
		}
		else
		{
			CString nErrMsg;
			nErrMsg.LoadString(IDS_ERROR_RESTOP);
			AfxMessageBox(nErrMsg);
		}
	}
}

void CTestMediaAngelDlg::OnBnClickedResumeButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("스탑버튼"));
	if(ResumeFlag)
	{
		StopFlag       = TRUE;
		ResumeFlag     = FALSE;
		HANDLE ResumeHandle = m_HandleProc[m_nSelectProc];
		CString CurPos;
		CurPos.Format(_T("%d %%"),m_nProcProgress[m_nSelectProc]);
		m_nWorkingList.SetItemText(m_nSelectProc,2,(LPCTSTR)CurPos);
		(m_lpfnArchiveResume)(ResumeHandle);
	}
	else if(StartFlag)
	{
		CString nErrMsg;
		nErrMsg.LoadString(IDS_ERROR_NOTSTART);
		AfxMessageBox(nErrMsg);
	}
	else if(!StartFlag && StopFlag)
	{
		CString nErrMsg;
		nErrMsg.LoadString(IDS_ERROR_RERESUME);
		AfxMessageBox(nErrMsg);
	}
}

void CTestMediaAngelDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	
	
	
	
	//m_pMControl->m_bFinishFlag=TRUE;
	delete m_pMControl;
	GdiplusShutdown(g_gdiplusToken);
	delete[] m_nProcProgress;
	delete[] m_HandleProc;
	delete[] m_pfOut;
	if(m_hDll)
	{
		FreeLibrary(m_hDll);
	}
	
	
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

BOOL CTestMediaAngelDlg::GetEncCLSID(WCHAR *mime, CLSID *pClsid)
 {
  UINT num,size,i;
  ImageCodecInfo *arCod;
  BOOL bFound=FALSE;

  GetImageEncodersSize(&num,&size);
  arCod=(ImageCodecInfo *)malloc(size);
  GetImageEncoders(num,size,arCod);

  for (i=0;i<num;i++) {
   if(wcscmp(arCod[i].MimeType,mime)==0) {
    *pClsid=arCod[i].Clsid;
    bFound=TRUE;
    break;
   }    
  }
  free(arCod);
  return bFound;
 }


BOOL CTestMediaAngelDlg::OnRcvInfo( HANDLE     nCQHandle    , //CQ 프로세서 핸들
									HBITMAP    hBitmap      , //출력 이미지 
									LPCTSTR    lpThumbPath  , //저장된 이미지 전체 경로
									LPAVRESULT lpAVResult   , //처리 옵션, 프로세스 종류
									LPVOID     lpUserData   )
/*
BOOL CTestMediaAngelDlg::OnRcvInfo( HANDLE   nCQHandle	   ,
									HBITMAP  hBitmap       ,//출력 이미지 
									LPCTSTR  lpThumbPath   ,//이미지 저장 경로
									INT64    nMuteStart    ,
									INT64    nMuteEnd      ,
									INT64    nFrameNumber  ,
									DOUBLE   dVilumeLevel  ,
									DWORD    dwOFlag       ,
									LPVOID   lpUserData    )
*/

{
	if( lpAVResult==NULL ) return FALSE;

	INT64    nMuteStart   = lpAVResult->rtStartTime;    
	INT64    nMuteEnd     = lpAVResult->rtEndTime  ;  
	INT64    nFrameNumber = lpAVResult->nFrameStart;   
	DOUBLE   dVilumeLevel = lpAVResult->dbAudioLevel[eAUDIO_AVERAGE]; 
	DWORD    dwOFlag      = lpAVResult->dwDetectFlag;

	
	if(dwOFlag&CQ_QC_AU_MUTE)
	{
		m_pfOut->SaveMuteFile(g_szMutePath, lpAVResult->wAudioChannel,nMuteStart,nMuteEnd,nCQHandle);
		
	}
	if(dwOFlag&CQ_QC_AU_CONST_FFREQ)
	{
		m_pfOut->SaveHighFreqFile(g_szMutePath, nMuteStart,nMuteEnd, lpAVResult->wAudioChannel,nCQHandle);
	}
	if(dwOFlag&CQ_QC_AU_TEST_TONE)
	{
		m_pfOut->SaveFreqFile(g_szMutePath, nMuteStart,nMuteEnd, lpAVResult->wAudioChannel,nCQHandle);
	}
	if(dwOFlag&CQ_QC_LATTER_BOX)
	{
		m_pfOut->SaveLatterBoxFile(g_szMutePath, nMuteStart,nMuteEnd, lpAVResult->wAudioChannel,nCQHandle);
	}
	
	if(lpThumbPath!=NULL)
	{
		Bitmap *myBit = Bitmap::FromHBITMAP(hBitmap,0);	
		
		CLSID Clsid;

		GetEncCLSID(L"image/jpeg",&Clsid);
		CString CurFrame;
		CurFrame.Format(_T("%d"),nFrameNumber);
		
		if( dwOFlag&CQ_CATELOG )
		{
			m_pfOut->SaveBmpFile(myBit,lpThumbPath,Clsid,CurFrame,nCQHandle);
		}
		if( dwOFlag&CQ_QC_FS_BLACK)
		{
			m_pfOut->SaveFrameFile(g_szMutePath, (UINT)nMuteStart,(UINT)nMuteEnd,nCQHandle);
		}
		if( dwOFlag&CQ_QC_AU_VOLUME_LEVEL)
		{
			m_pfOut->SaveFrameFile(g_szMutePath, (UINT)-1,(UINT)dVilumeLevel, nCQHandle);
		}
		if( dwOFlag&CQ_QC_ALL )
		{
			// CQ_QC프로세서가 활성화되어 에러가 검출되었다. CQ_QC+에러종류 어떤에러가? 마지막자리가 1, 2, 4에따라서
			// CQ_QC_EDGE_BLOC      0x00008001 // QC 1번, 사물의 가장자리로 블럭화가 발생하는 에러 검출.
			// CQ_QC_FS_STAR        0x00008002 // QC 2번, 전체 화면에 거처 번쩍이는 화면이 삽입된 에러 검출.
			// CQ_QC_FS_BLACK       0x00008004 // QC 3번, 전체 화면에 거처 검정색 프레임이 삽입된 에러 검출.
			m_pfOut->SaveErrBmpFile(g_szMutePath,myBit,lpThumbPath,Clsid,CurFrame,nCQHandle,dwOFlag);
		}
		/*
		ResumeFlag = FALSE;
		StopFlag   = FALSE;
		StartFlag  =  TRUE;
		*/
		delete myBit;
	}
	
	return FALSE;
}

BOOL CTestMediaAngelDlg::OnRcvProgress( HANDLE nCQHandle	,
										DWORD dwCurPos		, //progress 현재
										DWORD dwTotal		, //progress 전체
										BOOL  finish        ,
										LPVOID  lpUserData  )

{

		double dCurPos = ((double)dwCurPos/(double)dwTotal)*100.0;
		int    nCurPos = (int)dCurPos;

		m_pMControl->SetProgressPos( nCurPos, nCQHandle );

		if(finish)
		{
			m_pMControl->ProcFinish(nCQHandle);
			::PostMessage(g_hWND, UM_CLOSE_CQ_HANDLE, (WPARAM)nCQHandle, 0);

		}

	return FALSE;
}

void CTestMediaAngelDlg::OnBnClickedStopButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if(!m_nSelectProc)
	{
		if(!StartFlag)
		{
			HANDLE StopHandle = NULL;
			StopHandle = m_HandleProc[m_nSelectProc];
			(m_lpfnArchivePause)(StopHandle);
			CString MsgReset;
			MsgReset.LoadString(IDS_MSG_RESET);
			int buttonReturn = AfxMessageBox(MsgReset,MB_YESNO);
			
			if(buttonReturn==IDYES)
			{
				
				CString Stop;
				Stop.Format(_T("Stop"));
				m_nWorkingList.SetItemText(m_nSelectProc,2,(LPCTSTR)Stop);
				m_nProcProgress[m_nSelectProc]=100;
				(m_lpfnArchiveClose)(StopHandle);
								
				ResumeFlag = FALSE;
				StopFlag   = FALSE;
				StartFlag  =  TRUE;
				m_nCurProgress.SetPos(0);
			}
			else
			{
				(m_lpfnArchiveResume)(StopHandle);
			}
		}	
	}
	
}

BOOL CTestMediaAngelDlg::InitDLL( void )
{
	CString szDllName= _T("MediaCQ.dll");

#if defined(WIN64) && defined(UNICODE) && defined(DEBUG)
	szDllName= _T("MediaCQUD.dll");
#endif
#if defined(WIN64) && defined(UNICODE) && !defined(DEBUG)
	szDllName= _T("MediaCQU.dll");
#endif
#if defined(WIN64) && !defined(UNICODE) && defined(DEBUG)
	szDllName= _T("MediaCQD.dll");
#endif
#if defined(WIN64) && !defined(UNICODE) && !defined(DEBUG)
	szDllName= _T("MediaCQ.dll");
#endif
#if !defined(WIN64) && defined(UNICODE) && defined(DEBUG)
	szDllName= _T("MediaCQUD.dll");
#endif
#if !defined(WIN64) && defined(UNICODE) && !defined(DEBUG)
	szDllName= _T("MediaCQU.dll");
#endif
#if !defined(WIN64) && !defined(UNICODE) && defined(DEBUG)
	szDllName= _T("MediaCQD.dll");
#endif
#if !defined(WIN64) && !defined(UNICODE) && !defined(DEBUG)
	szDllName= _T("MediaCQ.dll");
#endif

	CString szDllPath = CAppUtil::GetMainPath() + szDllName;

//	m_hDll= LoadLibrary(_T("MediaAngel"));
	m_hDll= LoadLibrary(szDllPath);
	if(NULL == m_hDll)
	{
		CString szMsg;
		szMsg.Format(_T("Error Loading DLL = %s"),szDllPath);
	   AfxMessageBox(szMsg);
	}

	m_lpfnArchiveClose  = (LPFN_CQCLOSE )GetProcAddress(m_hDll,"CQClose" );
	m_lpfnArchiveOpen   = (LPFN_CQOPEN  )GetProcAddress(m_hDll,"CQOpen"  );
	m_lpfnArchiveResume = (LPFN_CQRESUME)GetProcAddress(m_hDll,"CQResume");
	m_lpfnArchivePause  = (LPFN_CQPAUSE )GetProcAddress(m_hDll,"CQPause" );

	if( !m_lpfnArchiveOpen  ||
		!m_lpfnArchiveClose ||
		!m_lpfnArchiveOpen  ||
		!m_lpfnArchiveOpen   )
		return FALSE;
	return TRUE;
}

void CTestMediaAngelDlg::ResetFlag(HANDLE nCQHandle)
{
	ResumeFlag = FALSE;
	StopFlag   = FALSE;
	StartFlag  =  TRUE;
	//delete nCQHandle;
}

void CTestMediaAngelDlg::OnNMClickWorkingList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int listnum;
	listnum = pNMListView->iItem;
	m_nSelectProc = listnum;
	if(listnum!=-1)
	{
		m_nCurProgress.SetPos(m_nProcProgress[listnum]);
	}


	*pResult = 0;
	
}

void CTestMediaAngelDlg::OnBnClickedTotalstopButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!StartFlag)
	{
		for(int i=0;i<m_nTotalProc;i++)
		{
			HANDLE StopHandle = m_HandleProc[i];
			(m_lpfnArchivePause)(StopHandle);
		}

		CString MsgReset;
		MsgReset.LoadString(IDS_MSG_RESET);
		int buttonReturn = AfxMessageBox(MsgReset,MB_YESNO);
		if(buttonReturn==IDYES)
		{
			CString Stop;
			Stop.Format(_T("Stop"));
			for(int i=0;i<m_nTotalProc;i++)
			{
				if(m_nProcProgress[i]!=100)
				{
					m_nWorkingList.SetItemText(i,2,(LPCTSTR)Stop);
					HANDLE StopHandle = m_HandleProc[i];
					m_nProcProgress[i]=100;
					(m_lpfnArchiveClose)(StopHandle);
				}
			}
			ResumeFlag = FALSE;
			StopFlag   = FALSE;
			StartFlag  =  TRUE;
			m_nCurProgress.SetPos(0);
			m_nTotalProgress.SetPos(0);


		}
		else
		{
			for(int i=0;i<m_nTotalProc;i++)
			{
				HANDLE StopHandle = m_HandleProc[i];
				(m_lpfnArchiveResume)(StopHandle);
			}
			
		}
	}	
}

void CTestMediaAngelDlg::OnBnClickedTotalpauseButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

		
	CString pause;
	pause.Format(_T("Pause"));
	for(int i=0;i<m_nTotalProc;i++)
	{
		if(m_nProcProgress[i]!=100)
		{
			CString pause;
			pause.Format(_T("Pause"));
			CString strCurPos= m_nWorkingList.GetItemText(i,2);
			m_nProcProgress[i] = _ttoi(strCurPos);
			m_nWorkingList.SetItemText(i,2,(LPCTSTR)pause);
			HANDLE PauseHandle = m_HandleProc[i];
			(m_lpfnArchivePause)(PauseHandle);
		}

	}
}

void CTestMediaAngelDlg::OnBnClickedTotalresumeButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	for(int i=0;i<m_nTotalProc;i++)
	{
		if(m_nProcProgress[i]!=100)
		{
			CString CurPos;
			CurPos.Format(_T("%d  %%"),m_nProcProgress[i]);
			m_nWorkingList.SetItemText(i,2,(LPCTSTR)CurPos);
			HANDLE ResumeHandle = m_HandleProc[i];
			(m_lpfnArchiveResume)(ResumeHandle);
		}
	}


}

void CTestMediaAngelDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnBnClickedOk();
	CDialog::OnClose();
}

BOOL CTestMediaAngelDlg::OnMediaInfo( LPMEDIAINFORMATION lpMediaInfo)
{
	return TRUE;
}
/*
void CTestMediaAngelDlg::OnBnClickedInButton2()
{
	// TODO: Add your control notification handler code here
}
*/

void CTestMediaAngelDlg::OnBnClickedButtonInputProfile()
{
	// TODO: Add your control notification handler code here
	CString m_strFileName;
	CString strFilter;
	strFilter.Format(IDS_FILE_FILTER);

	CFileDialog dlg(TRUE, NULL, NULL,
	(OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
	(LPCTSTR)strFilter, NULL);

	if(dlg.DoModal()==IDOK)
	{
		m_editCheckProfilePath.SetWindowText(dlg.GetPathName());
	}
}
