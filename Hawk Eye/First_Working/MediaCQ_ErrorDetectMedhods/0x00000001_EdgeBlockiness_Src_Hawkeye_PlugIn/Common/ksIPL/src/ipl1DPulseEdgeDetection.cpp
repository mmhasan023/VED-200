//#include "stdafx.h"
#include "ipl1DPulseEdgeDetection.h"

#ifdef _DEBUG
#include "mem_trace.h"
#define new DBG_NEW
#endif



//nWindowSize   : process window size
//nTotalCount   : signal total count, ���Ŀ��� ��ü ��ȣ�� ���� ����, ���� ť�� ������ ����. ���� ť�� ũ���� �Է�.
//tInitVarience : Initialize Variance
C1DPulseEdgeDetection::C1DPulseEdgeDetection(const int& nWindowSize, const int& nTotalCount, const /*T&*/int& tInitVariance)
:C1DImpulseEdgeDetection(nWindowSize, nTotalCount, tInitVariance)
{
	m_nPrevShotBoundary = 0;
}

C1DPulseEdgeDetection::~C1DPulseEdgeDetection(void)
{

}

int C1DPulseEdgeDetection::SetValue(int val, int currentFrameNum, int& nTargetFrame)
{
	//�Ÿ� ���̸� �����Ѵ�.
	m_pValue[currentFrameNum] = val;
	m_nCurrentNum=currentFrameNum;
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
	m_nSubSum -= m_pValue[currentFrameNum - m_nWindowSize];
	//���α��� ���� ���Ѵ�
	m_nSubSum += val;

	//�л��� ���Ѵ�
	CalcVarience(m_nTargetFrame);

	// �� ��� ����
	if(m_nTargetFrame == 0)
		return IPL1D_NONE;//IPL1D_DETECT;

	int nShotBoundary= DetectBoundary(m_nTargetFrame - 1);

	//����� ��� IPL1D_NONE ��ȯ
	if( nShotBoundary > 0 )
		return IPL1D_DETECT;//IPL1D_NONE;

	return IPL1D_CONTINUE;
}

UINT C1DPulseEdgeDetection::DetectBoundary(int nFrame)
{
	UINT nThreshold = 0;
	UINT nBoundary = 0;

	//Ÿ��������-1�� �Ӱ谪
	nThreshold = m_pConv[nFrame] + THRESOLD_VARIENCE_WEIGHT * m_pVariance[nFrame];

	// �ް��� ��� ����
	if(m_pValue[nFrame] > nThreshold)
	{
		//		if(m_pConv[nFrame - 1] <= m_pConv[nFrame] &&
		//		m_pConv[nFrame + 1] <= m_pConv[nFrame])
		{
			m_nStartGradientShot = 0;
			nBoundary = nFrame;
		}
	}
	else
	{
		if(m_nStartGradientShot > 0)
		{
			if(m_pConv[nFrame] < m_nGradientMean && 
				m_pVariance[nFrame] < m_nThresoldVarience &&
				m_pConv[nFrame - 1] > m_pConv[nFrame + 1])
			{
				//				nFrame = (m_nStartGradientShot + nFrame) / 2;
				m_nStartGradientShot = 0;
				m_nGradientMean = 0;
				nBoundary = nFrame;
			}
		}
		else
		{
			if(m_nGradientMean > 0)
			{
				if(m_pConv[nFrame] < m_nGradientMean)
					m_nGradientMean = 0;
			}
			else if(m_pVariance[nFrame] > m_nThresoldVarience && 
				m_pConv[nFrame - 1] < m_pConv[nFrame + 1])
			{
				m_nStartGradientShot = nFrame;
				m_nGradientMean = m_pConv[nFrame];
			}
		}
	}

	if(nBoundary == 0)
		return 0;

	if(nBoundary - m_nPrevShotBoundary < THRESOLD_SHOT_INTERVAL)
	{
		m_nPrevShotBoundary = nBoundary;
		return 0;
	}

	m_nPrevShotBoundary = nBoundary;
	return nBoundary;
}
