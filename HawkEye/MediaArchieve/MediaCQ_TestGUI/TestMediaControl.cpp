#include "StdAfx.h"
#include "TestMediaControl.h"
 

//#ifdef _DEBUG
//#include "mem_trace.h"
//#define new DBG_NEW
//#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestMediaControl::CTestMediaControl( const CWnd* pParent )
{
	m_pMainDlg =(CTestMediaAngelDlg*)pParent;
	m_bProFlag=TRUE;
	m_bFinishFlag=FALSE;
}

CTestMediaControl::~CTestMediaControl(void)
{	
}
void CTestMediaControl::ReSetMain(HANDLE nCQHandle)
{
	CTestMediaAngelDlg* pMainDlg=(CTestMediaAngelDlg*)AfxGetApp()->m_pMainWnd;
	//if(m_pMainDlg == pMainDlg)
	{
		m_pMainDlg->ResetFlag(nCQHandle);
	}
}
void CTestMediaControl::ProcFinish(HANDLE nCQHandle)
{

	CTestMediaAngelDlg* pMainDlg=(CTestMediaAngelDlg*)AfxGetApp()->m_pMainWnd;
	//if(m_pMainDlg == pMainDlg)
	{
		CString MSG;
		MSG.LoadString(IDS_FINISH);
		for(int i=0;i<m_pMainDlg->m_nTotalProc;i++)
		{
			if(nCQHandle==m_pMainDlg->m_HandleProc[i])
			{
				CString complete;
				complete.Format(_T("complete"));
				m_pMainDlg->m_nWorkingList.SetItemText(i,2,(LPCTSTR)complete);
				m_pMainDlg->m_nProcProgress[i]=100;
				m_pMainDlg->m_HandleProc[i] = NULL;
			}
		}
		//m_pMainDlg->ShowWindow(SW_MINIMIZE);
		//m_pMainDlg->ShowWindow(SW_RESTORE);
		ReSetMain(nCQHandle);
		SetTotalProgress();

		/*
		Sleep(1000);		
		m_pMainDlg->OnBnClickedStartButton();
		CString temp;
		m_pMainDlg->m_nTotalCount++;
		temp.Format(_T("%d¹ø"),m_pMainDlg->m_nTotalCount);
		m_pMainDlg->m_EditTotalCount.SetWindowText(temp);
		*/

	}
}

void CTestMediaControl::SetProgressPos(const int& nCurProgress,HANDLE nCQHandle)
{
	m_csProgress.Lock();
	//if(!m_bFinishFlag)
	{
		CTestMediaAngelDlg* pMainDlg=m_pMainDlg;//(CTestMediaAngelDlg*)AfxGetApp()->m_pMainWnd;
		//if(m_pMainDlg == pMainDlg)
		{
			if(m_bProFlag)
			{
				pMainDlg->m_nCurProgress.SetRange(0,100);
				m_bProFlag=FALSE;
			}
			for(int i=0;i<pMainDlg->m_nTotalProc;i++)
			{	
				CString nCurProc;
				nCurProc.Format(_T("%d %%"), nCurProgress);
				if(nCQHandle==pMainDlg->m_HandleProc[i])
				{
					if(pMainDlg->m_nProcProgress[i]!=100)
					{
						pMainDlg->m_nProcProgress[i] = nCurProgress;
						pMainDlg->m_nWorkingList.SetItemText(i,2,(LPCTSTR)(nCurProc));
						if(pMainDlg->m_nSelectProc == i)
						{
							pMainDlg->m_nCurProgress.SetPos( nCurProgress );
						}
					}
				}
			}
			SetTotalProgress();
		}
	}
	m_csProgress.Unlock();
}

void CTestMediaControl::SetTotalProgress()
{
	int ntotalcur=0;
	CTestMediaAngelDlg* pMainDlg=(CTestMediaAngelDlg*)AfxGetApp()->m_pMainWnd;
	if(m_pMainDlg == pMainDlg)
	{
		for(int i=0;i<pMainDlg->m_nTotalProc;i++)
		{
			ntotalcur+=pMainDlg->m_nProcProgress[i];
		}

		if( pMainDlg->m_nTotalProc!=0)
			ntotalcur= ntotalcur/pMainDlg->m_nTotalProc;
		else ntotalcur=0;
		
		pMainDlg->m_nTotalProgress.SetPos(ntotalcur);
		
	}
}
