//#if defined(WIN32)
//	#include "stdafx.h"
//#endif

#include "ipl1DImpulseEdgeDetection.h"
#include <memory.h>
#include <math.h>
#include "omp_thread.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#ifdef _LOG_DATA
extern void ipl_LOG_MSG(TCHAR *szMsg, ... );
#endif

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#ifdef malloc
#undef malloc
#endif
#define malloc(s) (_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef calloc
#undef calloc
#endif
#define calloc(c, s) (_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef realloc
#undef realloc
#endif
#define realloc(p, s) (_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef _expand
#undef _expand
#endif
#define _expand(p, s) (_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__  ))
#ifdef free
#undef free
#endif
#define free(p) (_free_dbg(p, _NORMAL_BLOCK))
#ifdef _msize
#undef _msize
#endif
#define _msize(p) (_msize_dbg(p, _NORMAL_BLOCK))

#endif
*/

C1DImpulseEdgeDetection::C1DImpulseEdgeDetection(const int& nWindowSize, 
												 const int& nTotalCount, 
												 const /*T&*/int& tInitVariance,
												 eDETEC_DIRECTION eDirection)
{
	m_nWindowSize        = 0;
	m_nSubSum            = 0;
	m_nStartGradientShot = 0;
	m_nThresoldVarience  = 0;	
	m_nGradientMean      = 0;
//	m_nPrevShotBoundary  = 0;
	m_nCurrentNum        = 0;
	m_nTargetFrame       = 0;
	m_nTotalCount        = nTotalCount+50;//frame���� ��Ȯ�� ���� ���ϴ� ��쿡 ����� �ӽ� ����.

	m_nWindowSize       = nWindowSize;
	m_nThresoldVarience = (UINT)(tInitVariance*THRESOLD_VARIENCE);

	m_eDirection        = eDirection;

	m_pConv     = new UINT[m_nTotalCount];
	m_pValue    = new UINT[m_nTotalCount];
	m_pVariance = new UINT[m_nTotalCount];

	memset(m_pConv      , 0, sizeof(UINT) * m_nTotalCount);
	memset(m_pValue     , 0, sizeof(UINT) * m_nTotalCount);
	memset(m_pVariance  , 0, sizeof(UINT) * m_nTotalCount);
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("m_pValue=0x%08x, m_pConv=0x%08x, m_pVariance=0x%08x"),m_pValue,m_pConv,m_pVariance);
#endif
}

C1DImpulseEdgeDetection::~C1DImpulseEdgeDetection(void)
{
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("m_pValue=0x%08x, m_pConv=0x%08x, m_pVariance=0x%08x"),m_pValue,m_pConv,m_pVariance);
#endif

	delete[] m_pVariance;
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("delete m_pVariance"));
#endif

	delete[] m_pConv;
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("delete m_pConv"));
#endif

	delete[] m_pValue;
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("delete m_pValue"));
#endif

}


int C1DImpulseEdgeDetection::SetValue(  int  val            , 
									    int  currentFrameNum, 
										int& nTargetFrame   , 
										int& nFailFrame     , 
										int  nUpperRate/* =400 */, 
										int nLowestRate/* =25 */)
{
	UINT* pValue = m_pValue;

	//�Է¹��� ���� �����Ѵ�
//	m_pValue[currentFrameNum] = val;
	pValue[currentFrameNum] = val;
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("SetValue = %d / %d"),currentFrameNum,m_nTotalCount);
#endif

	m_nCurrentNum=currentFrameNum;

	//Ÿ���������� ���Ѵ�
	m_nTargetFrame = currentFrameNum - m_nWindowSize / 2;
	nTargetFrame=m_nTargetFrame;

	//�Է¹��� ������ ������ ������
	if (  currentFrameNum < m_nWindowSize )
	{
		m_nSubSum += val;	
		//��հ��� ���ϰ� �����Ѵ�.
		m_pConv[currentFrameNum] = m_nSubSum / (currentFrameNum + 1);

		return IPL1D_SMALL;
	}

	//����ڰ� ������ �������� ������ ù��° ���ߴ� ���� �����
//	m_nSubSum -= m_pValue[currentFrameNum - m_nWindowSize];
	m_nSubSum -= pValue[currentFrameNum - m_nWindowSize];
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("SetValue2 = %d / %d"),currentFrameNum - m_nWindowSize,m_nTotalCount);
#endif
	//���α��� ���� ���Ѵ�
	m_nSubSum += val;

	//�л��� ���Ѵ�
	CalcVarience(m_nTargetFrame);

	// �� ��� ����
	if(m_nTargetFrame == 0)
		return IPL1D_NONE;//IPL1D_DETECT;

	int nShotBoundary= DetectBoundary(m_nTargetFrame - 1, nUpperRate, nLowestRate, nFailFrame);

	//����� ��� IPL1D_DETECT ��ȯ
//	if( nShotBoundary > 0 )
//		return IPL1D_DETECT;
	switch(m_eDirection)
	{
	case _eDETEC_NONE :break;
	case _eDETEC_SMALL:
	case _eDETEC_LARGE:
		if( nShotBoundary==(int)m_eDirection )
			return IPL1D_DETECT;
		break;
	case _eDETEC_BOTH :
		if( 0 < nShotBoundary )
			return IPL1D_DETECT;
		break;
	default:
		break;
	}


	return IPL1D_CONTINUE;
}

BOOL	C1DImpulseEdgeDetection::CalcVarience(int nFrame)
{
	UINT* pValue= m_pValue;

	// ���������� �� ���
	INT nDeviationSum = 0;
	INT nAvg = m_nSubSum / m_nWindowSize;
	INT nEnd = nFrame + m_nWindowSize / 2;

	int i=0;
#pragma omp parallel for reduction(+:nDeviationSum) num_threads( g_nIplNumberOfThreasds )
	for(i = nFrame - m_nWindowSize / 2; i <= nEnd; i ++)
	{
//		nDeviationSum += (m_pValue[i] - nAvg) * (m_pValue[i] - nAvg);
		nDeviationSum += (pValue[i] - nAvg) * (pValue[i] - nAvg);
	}
#ifdef _LOGDATA
	ipl_LOG_MSG(_T("CalcVarience = %d / %d"),--i,m_nTotalCount);
#endif

	m_pConv[nFrame] = nAvg;
	m_pVariance[nFrame] = (UINT)sqrt((float)nDeviationSum);

	//return m_pVariance[nFrame];
	return TRUE;
}

UINT	C1DImpulseEdgeDetection::DetectBoundary(int nFrame, int nUpperRate, int nLowestRate, int& nFailFrame)
{
	UINT*   pValue = m_pValue;
	UINT	nThreshold = 0;
	UINT	nBoundary = 0;

	//Ÿ���������� Ÿ���������� ���Ѵ�
	int nNewTarget = m_nTargetFrame-(m_nCurrentNum - m_nTargetFrame);

	//Ÿ��������-1�� �Ӱ谪
	nThreshold = m_pConv[nNewTarget-1] + THRESOLD_VARIENCE_WEIGHT * m_pVariance[nNewTarget-1];

	//Ÿ��������-2�� �Ӱ谪
	UINT	nThresholdT = m_pConv[nNewTarget-2] + THRESOLD_VARIENCE_WEIGHT * m_pVariance[nNewTarget-2];

	double calcThreshold = 0.0;

	if ( nThresholdT == 0)
		calcThreshold = nThreshold / (double)1 * 100;
	else
		calcThreshold = nThreshold / (double)nThresholdT * 100;

	nBoundary = (UINT)abs(calcThreshold);

	//Threshold���� �� �����Ӱ� ���ؼ� 110% �̻��̸� ���� ���������� Ȯ���Ѵ�
	if( nBoundary > 110 )
	{
		double firstValue=0.0, secondeValue=0.0;

		//%�� ���ؼ� ���� %���ϸ� ������� �����Ѵ�, ���⼭ ����%�� �⺻ 25%�̰� ����ڿ��� �Է� ������ �ִ�.
		//�� �������� �ް��� ��ȭ�� üũ�ϱ� ���ؼ� %�� ���ϴ� ���� ���� ������-1 �������� �и������ϰ� 
		// +-1�������� ���ڰ����� �Ѵ�

		//���� �и� 0�ϰ��
//		if (m_pValue[m_nTargetFrame-1] == 0)
		if (pValue[m_nTargetFrame-1] == 0)
		{
//			firstValue = ( m_pValue[m_nTargetFrame-2] / (double)1 ) * 100 ;
//			secondeValue = ( m_pValue[m_nTargetFrame] / (double)1 ) * 100 ;
			firstValue   = ( pValue[m_nTargetFrame-2] / (double)1 ) * 100 ;
			secondeValue = ( pValue[m_nTargetFrame  ] / (double)1 ) * 100 ;
#ifdef _LOGDATA
			ipl_LOG_MSG(_T("DetectBoundary = %d / %d"),m_nTargetFrame-2,m_nTotalCount);
			ipl_LOG_MSG(_T("DetectBoundary = %d / %d"),m_nTargetFrame,m_nTotalCount);
#endif

		}

		//�и� 0�� �ƴҰ��
		else
		{
//			firstValue   = ( m_pValue[m_nTargetFrame-2] / (double)m_pValue[m_nTargetFrame-1] ) * 100 ;
//			secondeValue = ( m_pValue[m_nTargetFrame] / (double)m_pValue[m_nTargetFrame-1] ) * 100 ;
			firstValue   = ( pValue[m_nTargetFrame-2] / (double)(pValue[m_nTargetFrame-1]) ) * 100 ;
			secondeValue = ( pValue[m_nTargetFrame  ] / (double)(pValue[m_nTargetFrame-1]) ) * 100 ;
#ifdef _LOGDATA
			ipl_LOG_MSG(_T("DetectBoundary = %d / %d"),m_nTargetFrame-2,m_nTotalCount);
			ipl_LOG_MSG(_T("DetectBoundary = %d / %d"),m_nTargetFrame,m_nTotalCount);
#endif
		}

		nFailFrame = nNewTarget;

		//���Ѱ��� ���� ���������� �̻� �Ǵ� ������ ��츦 �Ǻ��Ѵ�
		//���Ѱ��� �Ѵ� �������� ������ ��� ������ ����
		if ( abs(firstValue) < nLowestRate && abs(secondeValue) < nLowestRate )
		{
#ifdef _LOGDATA
			ipl_LOG_MSG(_T("abs(%f) < %d &&  abs(%f) < %d"), firstValue,nLowestRate ,secondeValue,nLowestRate);
#endif		
			return 1;
		}
		//���Ѱ��� �Ѵ� �������� �̻��� ��� ������ ����
		else if ( abs(firstValue) > nUpperRate &&  abs(secondeValue) > nUpperRate )
		{
#ifdef _LOGDATA
			ipl_LOG_MSG(_T("abs(%f) > %d &&  abs(%f) > %d"), firstValue,nUpperRate ,secondeValue,nUpperRate);
#endif		
			return 2;
		}
		else
			return 0;
	}
	else
		return 0;
}

/*
UINT C1DImpulseEdgeDetection::GetBoundary()
{
	return m_nPrevShotBoundary;
}
*/

UINT C1DImpulseEdgeDetection::GetDistance(int index)
{
	if( (!m_pValue) && (index>=(int)m_nTotalCount) )
		return FALSE;

#ifdef _LOGDATA
	ipl_LOG_MSG(_T("DetectBoundary = %d / %d"),index,m_nTotalCount);
#endif
	return m_pValue[index];
}

UINT C1DImpulseEdgeDetection::GetConv(int index)
{
	if( !m_pConv )
		return FALSE;

	return m_pConv[index];
}

UINT C1DImpulseEdgeDetection::GetVarience(int index)
{
	if( !m_pVariance )
		return FALSE;

	return m_pVariance[index];
}

UINT C1DImpulseEdgeDetection::GetValue(int index)
{
	if( (!m_pValue) && (index>=(int)m_nTotalCount) )
		return FALSE;

#ifdef _LOGDATA
	ipl_LOG_MSG(_T("DetectBoundary = %d / %d"),index,m_nTotalCount);
#endif
	return m_pValue[index];
}


#ifdef _MANAGED
#pragma managed(pop)
#endif

