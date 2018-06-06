//#if defined(WIN32)
//#include "stdafx.h"
//#endif

#include "ipl1DImpulseEdgeDetectionRT.h"
#include <memory.h>
#include <math.h>

#ifdef _MANAGED
#pragma managed(push, off)
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

C1DImpulseEdgeDetectionRT::C1DImpulseEdgeDetectionRT()
{
	m_nSubSum      = 0;
	m_nTargetFrame = 0;
	m_nCurPointer  = 0;
	m_nUsingNum    = 0;

	m_pValue    = NULL;
	m_pConv     = NULL;
	m_pVariance = NULL;

	m_nWindowSize     = 0;
	m_nWindowHalfSize = 0;

	m_nBoundary     = 0;
	m_dfirstValue   = 0;;
	m_dsecondeValue = 0;

}

C1DImpulseEdgeDetectionRT::C1DImpulseEdgeDetectionRT(const int& nWindowSize)
{
	m_nBoundary     = 0;
	m_dfirstValue   = 0;
	m_dsecondeValue = 0;

	m_pValue    = new unsigned int [nWindowSize+1];
	m_pConv     = new unsigned int [nWindowSize+1];
	m_pVariance = new unsigned int [nWindowSize+1];


	m_nWindowSize     = nWindowSize;
	m_nWindowHalfSize = nWindowSize >> 1;  

	Reset(nWindowSize);

}

C1DImpulseEdgeDetectionRT::~C1DImpulseEdgeDetectionRT()
{
	delete[] m_pValue;
	delete[] m_pConv;
	delete[] m_pVariance;
}

void C1DImpulseEdgeDetectionRT::SetWindowSize(int nWindowSize)
{
	if(m_pValue   ){ delete[] m_pValue   ;m_pValue   = NULL;};
	if(m_pConv    ){ delete[] m_pConv    ;m_pConv    = NULL;};
	if(m_pVariance){ delete[] m_pVariance;m_pVariance= NULL;};

	m_pValue    = new unsigned int [nWindowSize+1];
	m_pConv     = new unsigned int [nWindowSize+1];
	m_pVariance = new unsigned int [nWindowSize+1];


	m_nWindowSize     = nWindowSize;
	m_nWindowHalfSize = nWindowSize >> 1;  

	Reset(nWindowSize);
}


void C1DImpulseEdgeDetectionRT::Reset(const int& nWindowSize){

	m_nSubSum      = 0;
	m_nTargetFrame = 0;
	m_nCurPointer  = 0;
	m_nUsingNum    = 0;
	m_nCurNum      = 0;

	memset(m_pValue    , 0, sizeof(unsigned int) * (nWindowSize+1));
	memset(m_pConv     , 0, sizeof(unsigned int) * (nWindowSize+1));
	memset(m_pVariance , 0, sizeof(unsigned int) * (nWindowSize+1));

}
/*
void C1DImpulseEdgeDetectionRT::GetShiftingValue(unsigned int nSize, 
												 unsigned int nHori_orVerti,
												 unsigned int* nShiftVal)
{

	if(nHori_orVerti == _SIZE_VERTICAL_)
	{
		if    (nSize >= _SIZE_HORI_1920_) { *nShiftVal = 5;	}
		else if(nSize >= _SIZE_HORI_720_) { *nShiftVal = 3;	}
		else if(nSize >= _SIZE_HORI_640_) { *nShiftVal = 3;	}
		else if(nSize >= _SIZE_HORI_320_) { *nShiftVal = 2;	}

	}
	else
	{
		if    (nSize >= _SIZE_VERT_1080_) {	*nShiftVal = 4;	}
		else if(nSize >= _SIZE_VERT_480_) { *nShiftVal = 3;	}
		else if(nSize >= _SIZE_VERT_240_) { *nShiftVal = 2;	}
	}

}
*/

int C1DImpulseEdgeDetectionRT::SetValue(int nVal,
										int nUpperRate/* =400 */, 
										int nLowestRate/* =25 */)
{

	UINT fnTempVal;
	int  fnTemp; 
	/* Using Num. of Array */
	if(m_nUsingNum != m_nWindowSize){ m_nUsingNum++; }

	m_nCurPointer++;
	m_nCurPointer = m_nCurPointer % (m_nWindowSize+1);

	if(m_nCurPointer == 0) {m_nCurPointer++;}

	//�Է¹��� ���� �����Ѵ�
	fnTempVal = m_pValue[m_nCurPointer];
	m_pValue[m_nCurPointer] = nVal;

	if (  m_nUsingNum < m_nWindowSize )
	{
		m_nSubSum += nVal;	
		//��հ��� ���ϰ� �����Ѵ�.
		m_pConv[m_nCurPointer] = m_nSubSum / (m_nUsingNum+1);

		return IPL1D_SMALL;
	}else{
		m_nCurNum++;
		if(m_nCurNum == (m_nWindowSize+1)){m_nCurNum=1;}
	}

	//Ÿ���������� ���Ѵ�

	fnTemp = m_nCurNum + m_nWindowHalfSize;
	m_nTargetFrame = fnTemp % (m_nWindowSize+1);
	if(fnTemp > m_nWindowSize) {m_nTargetFrame++;}

	//���α��� ���� ���Ѵ�
	m_nSubSum -= fnTempVal;
	m_nSubSum += nVal;	

	//�л��� ���Ѵ�
	CalcVarience(m_nTargetFrame);

	UINT nShotBoundary=DetectBoundary(nUpperRate, nLowestRate);

	//����� ��� IPL1D_DETECT ��ȯ
	if     (nShotBoundary == IPL1D_DETECT_LOW ) {return IPL1D_DETECT_LOW ;}
	else if(nShotBoundary == IPL1D_DETECT_HIGH) {return IPL1D_DETECT_HIGH;}

	return IPL1D_CONTINUE;
}

BOOL	C1DImpulseEdgeDetectionRT::CalcVarience(int nFrame)
{
	// ���������� �� ���
	UINT nDeviationSum = 0;
	UINT nAvg = m_nSubSum / m_nWindowSize;
	INT  fnCnt;

//#pragma omp parallel for
	for(fnCnt = 1; fnCnt <= m_nWindowSize; fnCnt ++)
	{
		nDeviationSum += (m_pValue[fnCnt] - nAvg) * (m_pValue[fnCnt] - nAvg);
	}

	m_pConv[nFrame] = nAvg;
	m_pVariance[nFrame] = (unsigned int)sqrt((float)nDeviationSum);

	//return m_pVariance[nFrame];
	return TRUE;
}

void C1DImpulseEdgeDetectionRT::GetCurrentValue(UINT* pnBoundary, double*  pdfirstValue, double* pdsecondeValue)
{
	*pnBoundary     = m_nBoundary;
	*pdfirstValue   = m_dfirstValue;
	*pdsecondeValue = m_dsecondeValue; 
}

UINT	C1DImpulseEdgeDetectionRT::DetectBoundary(int nUpperRate, int nLowestRate)
{

	UINT	nThreshold, nThresholdT;
	UINT	nBoundary = 0;
	INT 	fnNewTargetMinusOne, fnNewTargetMinusTwo, fnTemp;
	UINT    fnTargetMinusOne, fnTargetMinusTwo;

	/* Make a New Target Frame */
	fnTemp = m_nTargetFrame+m_nWindowHalfSize+1;
	INT nNewTarget = fnTemp % (m_nWindowSize+1);
	if(m_nWindowSize<fnTemp) {nNewTarget++;}

	fnTemp = nNewTarget+m_nWindowSize-1;	
	fnNewTargetMinusOne = fnTemp % (m_nWindowSize+1);
	if(m_nWindowSize<fnTemp) {fnNewTargetMinusOne++;}

	fnTemp = nNewTarget+m_nWindowSize-2;	
	fnNewTargetMinusTwo = fnTemp % (m_nWindowSize+1);
	if(m_nWindowSize<fnTemp) {fnNewTargetMinusTwo++;}

	fnTemp = m_nTargetFrame+m_nWindowSize-1;	
	fnTargetMinusOne = fnTemp % (m_nWindowSize+1);
	if(m_nWindowSize<fnTemp) {fnTargetMinusOne++;}

	fnTemp = m_nTargetFrame+m_nWindowSize-2;	
	fnTargetMinusTwo = fnTemp % (m_nWindowSize+1);
	if(m_nWindowSize<fnTemp) {fnTargetMinusTwo++;}

	nThreshold = nThresholdT = 0;

	//Ÿ��������-1�� �Ӱ谪
	nThreshold = 
		m_pConv[fnNewTargetMinusOne] + THRESOLD_VARIENCE_WEIGHT * 
		m_pVariance[fnNewTargetMinusOne];

	//Ÿ��������-2�� �Ӱ谪
	nThresholdT = 
		m_pConv[fnNewTargetMinusTwo] + THRESOLD_VARIENCE_WEIGHT * 
		m_pVariance[fnNewTargetMinusTwo];

	double calcThreshold = 0.0;


	if ( nThresholdT == 0)
		calcThreshold = nThreshold / (double)1 * 100;
	else
		calcThreshold = nThreshold / (double)nThresholdT * 100;


	nBoundary = (unsigned int)abs(calcThreshold);
	m_nBoundary= nBoundary;

	///////////////////////////////////////////////////////////
//	return IPL1D_NONE;
	///////////////////////////////////////////////////////////

	//Threshold���� �� �����Ӱ� ���ؼ� 110% �̻��̸� ���� ���������� Ȯ���Ѵ�
	//	if( nBoundary < 93 )
	if( nBoundary > 110 )
	{
		double firstValue=0.0, secondeValue=0.0;

		//%�� ���ؼ� ���� %���ϸ� ������� �����Ѵ�, ���⼭ ����%�� �⺻ 25%�̰� ����ڿ��� �Է� ������ �ִ�.
		//�� �������� �ް��� ��ȭ�� üũ�ϱ� ���ؼ� %�� ���ϴ� ���� ���� ������-1 �������� �и������ϰ� 
		// +-1�������� ���ڰ����� �Ѵ�

		//���� �и� 0�ϰ��
		if (m_pValue[fnTargetMinusOne] == 0)
		{
			firstValue = 
				( m_pValue[fnTargetMinusTwo] / (double)1 ) * 100 ;
			secondeValue = 
				( m_pValue[m_nTargetFrame] / (double)1 ) * 100 ;
		}

		//�и� 0�� �ƴҰ��
		else
		{
			firstValue   = 
				( m_pValue[fnTargetMinusTwo] / 
				(double)m_pValue[fnTargetMinusOne] ) * 100 ;
			secondeValue = 
				( m_pValue[m_nTargetFrame]   / 
				(double)m_pValue[fnTargetMinusOne] ) * 100 ;
		}
		m_dfirstValue=firstValue;
		m_dsecondeValue=secondeValue;

		//���Ѱ��� ���� ���������� �̻� �Ǵ� ������ ��츦 �Ǻ��Ѵ�
		//���Ѱ��� �Ѵ� �������� ������ ��� ������ ����
		if ( abs(firstValue) < nLowestRate && abs(secondeValue) < nLowestRate )
			return IPL1D_DETECT_HIGH;
		//���Ѱ��� �Ѵ� �������� �̻��� ��� ������ ����
		else if ( abs(firstValue) > nUpperRate &&  abs(secondeValue) > nUpperRate )
			return IPL1D_DETECT_LOW;
		else
			return IPL1D_NONE;
	}
	else
		return IPL1D_NONE;
}

/*
UINT C1DImpulseEdgeDetectionRT::GetBoundary()
{
return m_nPrevShotBoundary;
}
*/

UINT C1DImpulseEdgeDetectionRT::GetDistance(int index)
{
	if( !m_pValue )
		return FALSE;

	return m_pValue[index];
}

UINT C1DImpulseEdgeDetectionRT::GetConv(int index)
{
	if( !m_pConv )
		return FALSE;

	return m_pConv[index];
}

UINT C1DImpulseEdgeDetectionRT::GetVarience(int index)
{
	if( !m_pVariance )
		return FALSE;

	return m_pVariance[index];
}

UINT C1DImpulseEdgeDetectionRT::GetTargetValue (int nIndex)
{
	int nTarget = m_nCurPointer - m_nWindowHalfSize - 1;//(m_nWindowSize/2);
	nTarget += nIndex;

	if(nTarget<0) nTarget=m_nWindowSize+nTarget;
	if(nTarget==0) nTarget=m_nWindowSize;

	return m_pValue[nTarget];
}


#ifdef _MANAGED
#pragma managed(pop)
#endif

