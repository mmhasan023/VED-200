#include "Stdafx.h"
#include "DetectBlock.h"


int ipl_BlockDetect( IN LPBYTE pCopyedSrc, int nWidth, int nHeight, OUT LPLIST_BLOCK lpListBlock, IN BYTE byteBarrier, IN INT nMaxBlockSize )
{
	if( pCopyedSrc==NULL ) return 0;

	LPBYTE lpSrc           = pCopyedSrc;
	LPBYTE lpBoundartStart = pCopyedSrc;
	LPBYTE lpBoundartEnd   = pCopyedSrc + (nWidth*nHeight);

	int    nX              = _MACRO_BLOCK_SIZE;
	int    nY              = _MACRO_BLOCK_SIZE;
	int    nWidthEnd       = nWidth  - _MACRO_BLOCK_SIZE;
	int    nHeightEnd      = nHeight - _MACRO_BLOCK_SIZE;
	int    nIncreaseSize   = (_MACRO_BLOCK_SIZE)*2      ;
	int    nCount          = 0;

	for( ; nY<nHeightEnd ; nY++ )
	{
		lpSrc = pCopyedSrc + (nY*nWidth+_MACRO_BLOCK_SIZE);
		for( nX = _MACRO_BLOCK_SIZE ; nX<nWidthEnd ; nX++, lpSrc++ )
		{
			if( _IS_MAX_L(lpSrc)                    && //완전 흰바탕에서 시작하는 블럭은 찾지 못함, 속도를 고려한 결과.
				_ABS_POS_SUB_L(lpSrc) > byteBarrier )
//			while( _IS_MAX_L(lpSrc)                   && //완전 흰바탕에서 시작하는 블럭은 찾지 못함, 속도를 고려한 결과.
//				   _ABS_POS_SUB_L(lpSrc) > byteBarrier )
			{
				int nStartX = nX;
				int nRight  = 0;
				CBlockElement block( nWidth );
				*lpSrc = _MAX_GRAY;
				block.AddLeftLine( nX, nY, LEFT_TOP, lpSrc );
//				lpSrc+=_MACRO_BLOCK_SIZE-1;
//				nX   +=_MACRO_BLOCK_SIZE-1;
				lpSrc++;
				nX   ++;

//				if(*lpSrc==_MAX_GRAY) break;

				nCount = 0;
				while( nCount++<nMaxBlockSize && nX<nWidthEnd )
				{
					if( _ABS_POS_SUB_R(lpSrc) > byteBarrier &&
						((nX-nStartX)%_MACRO_BLOCK_SIZE) ==0 ) //_MACRO_BLOCK_SIZE의 배수 검사
					{
						*lpSrc = _MAX_GRAY;
						block.AddRightLine( nX, nY, RIGHT_TOP, lpSrc );
						break;
					}
					lpSrc++;nX++;
				}

				//Search Right Line
				if( block.GetSizeRight() )
				{
					LPLIST_POSITIONINFO lpListPos = block.GetListRight();
					LIST_POSITIONINFOItor itor = lpListPos->begin();
					LPBYTE lpDown = (*itor).GetDown( nWidth );
					int    nTmpY  = nY+1;
					nRight        = nX;

					while( _ABS_POS_SUB_R(lpDown) > byteBarrier && 
						   nTmpY < nHeightEnd )
					{
						*lpDown = _MAX_GRAY;

						lpListPos->push_back( CPositionInfo( nX, nTmpY, LINE_RIGHT, lpDown) );
						itor++ ;
						nTmpY++;
						lpDown = (*itor).GetDown( nWidth );
						_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpDown );
					}
				}

				//Search Left Line
				if( block.GetSizeRight() >_MACRO_BLOCK_SIZE )
				{
					LPLIST_POSITIONINFO lpListPos = block.GetListLeft();
					LIST_POSITIONINFOItor itor = lpListPos->begin();
					LPBYTE lpDown = (*itor).GetDown( nWidth );
					int    nTmpX  = (*itor).GetX();
					int    nTmpY  = nY+1;

					while( _ABS_POS_SUB_L(lpDown) > byteBarrier && 
						   nTmpY < nHeightEnd )
					{
						*lpDown = _MAX_GRAY;

						lpListPos->push_back( CPositionInfo( nTmpX, nTmpY, LINE_RIGHT, lpDown) );
						itor++;
						nTmpY++;
						lpDown = (*itor).GetDown( nWidth );
						_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpDown );
					}
				}

				//Search Upper Line
				if( block.GetSizeLeft() >_MACRO_BLOCK_SIZE )
				{
					int    nTmpX   = 0;
					int    nTmpY   = 0;
					LPBYTE lpRight = NULL;

					LPLIST_POSITIONINFO   lpListPosUp   = block.GetListUp();
					LPLIST_POSITIONINFO   lpListLeftPos = block.GetListLeft();

					LIST_POSITIONINFOItor itorLeft      = lpListLeftPos->begin();
					LIST_POSITIONINFOItor itorLeftEnd   = lpListLeftPos->end  (); 
					for( int nItorCount=0 ; nItorCount<_MACRO_BLOCK_SIZE-1 ; nItorCount++ ) itorLeftEnd--;//Uppper line과 down line의 차이를 두기 위해

					while( itorLeft != itorLeftEnd )//lpListLeftPos->end() )
					{
						if( _ABS_POS_SUB_U( ((*itorLeft).GetBuffer()+1), nWidth ) > byteBarrier )
						{
							lpRight = (*itorLeft).GetBuffer()+1;
							nTmpX   = (*itorLeft).GetX();
							nTmpY   = (*itorLeft).GetY();

							while( _ABS_POS_SUB_U(lpRight, nWidth) > byteBarrier && 
								   nTmpX                           < nWidthEnd   &&
								   nTmpX                           < nRight       )
							{
								*lpRight = _MAX_GRAY;

								lpListPosUp->push_back( CPositionInfo( nTmpX, nTmpY, LINE_TOP, lpRight) );
								nTmpX  ++;
								lpRight++;
								_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpRight );
							}

							if( lpListPosUp->size() < _MACRO_BLOCK_SIZE )
								while( lpListPosUp->size() ) lpListPosUp->pop_front();
							else break;

						}

						itorLeft++;
					}
				}

				if( block.GetSizeUp() >_MACRO_BLOCK_SIZE )
				{
					//Search Down Line
					int    nTmpX   = 0;
					int    nTmpY   = 0;
					LPBYTE lpRight = NULL;

					LPLIST_POSITIONINFO   lpListPosDown = block.GetListDown();
					LPLIST_POSITIONINFO   lpListLeftPos = block.GetListLeft();

					LIST_POSITIONINFOItor itorLeft      = lpListLeftPos->end  (); itorLeft--;
					LIST_POSITIONINFOItor itorLeftBegin = lpListLeftPos->begin(); 
					for( int nItorCount=0 ; nItorCount<_MACRO_BLOCK_SIZE-1 ; nItorCount++ ) itorLeftBegin++;//Uppper line과 down line의 차이를 두기 위해


					while( itorLeft != itorLeftBegin )//lpListLeftPos->begin() )
					{
						if( _ABS_POS_SUB_D( ((*itorLeft).GetBuffer()+1), nWidth ) > byteBarrier )
						{
							lpRight = (*itorLeft).GetBuffer()+1;
							nTmpX   = (*itorLeft).GetX();
							nTmpY   = (*itorLeft).GetY();

							while( _ABS_POS_SUB_D(lpRight, nWidth) > byteBarrier && 
								   nTmpX                           < nWidthEnd   &&
								   nTmpX                           < nRight       )
							{
								*lpRight = _MAX_GRAY;

								lpListPosDown->push_back( CPositionInfo( nTmpX, nTmpY, LINE_BOTTOM, lpRight) );
								nTmpX  ++;
								lpRight++;
								_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpRight );
							}

							if( lpListPosDown->size() < _MACRO_BLOCK_SIZE )
								while( lpListPosDown->size() ) lpListPosDown->pop_front();
							else break;

						}
						itorLeft--;
					}
				}

				if( block.IsBlock() )
				{
					lpListBlock->push_back( block );
				}
			}
		}
	}

	return 0;
}

#ifdef _DETECT_CLASS
CDetectBlock::CDetectBlock( const BYTE& byteBarrier, const INT& nMaxBlockSize )
{
	m_byteBarrier   = byteBarrier  ;
	m_nMaxBlockSize = nMaxBlockSize;

	memset( &m_AVResult, 0, sizeof(AVRESULT) );
	memset( &m_VideoApi, 0, sizeof(CVIDEOAPI) );

	m_lpCallback              = NULL  ;
	m_lpUserData              = NULL  ;
	m_hCommonDLL              = NULL  ;

	m_dwDetecedFlag           = CQ_QC_EDGE_BLOC   ;
}

CDetectBlock::~CDetectBlock()
{
	if( m_hCommonDLL )
		FreeLibrary( m_hCommonDLL ); 

	if(m_pErrorDector)
		delete m_pErrorDector;

}

HRESULT CDetectBlock::SetOption( LPSTR_MAP lpmapOption )
{
	STR_MAP::iterator itor;
	CString szValue;

//	itor = lpmapOption->find(_T("None detect start ratio"));
//	if (itor != lpmapOption->end())
//	{
//		szValue = (*itor).second.data();
//		m_ucNoneDetectStartRatio = (BYTE)_ttoi( (LPCTSTR)szValue );
//	}

	return S_OK;
}

void CDetectBlock::LoadCommonDLL(void)
{
	//인터레이스 알고리즘 추가
	
	CMAUtil::GetCommonVideoAPI( &m_hCommonDLL, &m_VideoApi);
}

HRESULT CDetectBlock::FinishedStream( void )
{
	return S_OK;
}

void CDetectBlock::SetCallback( LPFN_AVRESULT lpCallback, LPVOID lpUserData )
{
	m_lpCallback = lpCallback;
	m_lpUserData = lpUserData;
}

HRESULT CDetectBlock::SendErrorFrame(LPAVDATA lpAVData, const int& nTargetFrame)
{

	//인터레이스 알고리즘 추가
	
	LPVIDEODATA  lpVideo = &(lpAVData->video);
	CIplFrameEx* pFrame = m_VideoApi.lpGetFrame( lpVideo->hCVideo, nTargetFrame );

	if(pFrame==NULL) return S_FALSE;

	m_AVResult.nFrameNumber = pFrame->GetFrameNo  ()  ;
	m_AVResult.nFrameStart  = pFrame->GetFrameNo  ()  ;
	m_AVResult.nFrameEnd    = pFrame->GetFrameNo  ()  ;
	m_AVResult.lpData       = pFrame->GetPixelData()  ;
	m_AVResult.dwDataSize   = pFrame->GetDataSize ()  ;
	m_AVResult.dwDetectFlag = m_dwDetecedFlag         ;

	double dDifference = (double)(lpAVData->video.dwCurrentFrame-m_AVResult.nFrameStart)/lpAVData->video.dbFrameRate;
	m_AVResult.rtStartTime  = (REFERENCE_TIME)( (lpAVData->video.dbSampleTime-dDifference)*UINT_REFERENCE_TIME );
	m_AVResult.rtEndTime    = m_AVResult.rtStartTime;


	if(m_lpCallback) m_lpCallback( &m_AVResult, m_lpUserData);

	return S_OK;
}
#endif