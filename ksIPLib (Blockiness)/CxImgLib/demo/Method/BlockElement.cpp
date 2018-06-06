#include "Stdafx.h"
//#include "iplApi.h"
#include "iplBlockElement.h"


CBlockElement::CBlockElement( const INT& nWidth ){ m_nWidth = nWidth;};
CBlockElement::CBlockElement( const CBlockElement& block ){ (*this)=block; };
CBlockElement::~CBlockElement(){};
void CBlockElement::operator=( const CBlockElement& block )
{
	m_listLeft  = block.m_listLeft ;
	m_listRight = block.m_listRight;
	m_listUp    = block.m_listUp   ;
	m_listDown  = block.m_listDown ;
	m_nWidth    = block.m_nWidth   ;
}

BOOL CBlockElement::CheckConner( void )
{
	int nGap = 0;
	LIST_POSITIONINFOItor itorLeftBegin  = m_listLeft .begin();
	LIST_POSITIONINFOItor itorRightBegin = m_listRight.begin();
	LIST_POSITIONINFOItor itorUpBegin    = m_listUp   .begin();
	LIST_POSITIONINFOItor itorDownBegin  = m_listDown .begin();
	LIST_POSITIONINFOItor itorLeftEnd    = m_listLeft .end  (); itorLeftEnd --;
	LIST_POSITIONINFOItor itorRightEnd   = m_listRight.end  (); itorRightEnd--;
	LIST_POSITIONINFOItor itorUpEnd      = m_listUp   .end  (); itorUpEnd   --;
	LIST_POSITIONINFOItor itorDownEnd    = m_listDown .end  (); itorDownEnd --;

	int nTop    = (*itorUpBegin   ).GetY();
	int nBottom = (*itorDownBegin ).GetY();
	int nLeft   = (*itorLeftBegin ).GetX();
	int nRight  = (*itorRightBegin).GetX();

	////////////////////////////////////////////////////////////////////////////////////
	//Check Left Line 
	//Check Left Line Begin
	nGap = (*itorLeftBegin ).GetY() - nTop;
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorLeftBegin  = m_listLeft .begin();
			m_listLeft.push_front( CPositionInfo( (*itorLeftBegin ).GetX()     , 
				(*itorLeftBegin ).GetY() - 1 ,
				LINE_LEFT                    ,
				(*itorLeftBegin ).GetUpper(m_nWidth) ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listLeft.pop_front();
	}

	//Check Left Line End
	nGap = nBottom - (*itorLeftEnd ).GetY();
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorLeftEnd  = m_listLeft .end(); itorLeftEnd--;
			m_listLeft.push_back( CPositionInfo(  (*itorLeftEnd   ).GetX()     , 
				(*itorLeftEnd   ).GetY() + 1 ,
				LINE_LEFT                    ,
				(*itorLeftEnd   ).GetDown (m_nWidth) ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listLeft.pop_back();
	}
	//Check Left Line 
	////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////
	//Check Right Line 
	//Check Right Line Begin
	nGap = nTop - (*itorRightBegin ).GetY();
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorRightBegin = m_listLeft .begin();
			m_listLeft.push_front( CPositionInfo( (*itorRightBegin).GetX()     , 
				(*itorRightBegin).GetY() - 1 ,
				LINE_RIGHT                    ,
				(*itorRightBegin).GetUpper(m_nWidth) ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listLeft.pop_front();
	}

	//Check Right Line End
	nGap = nBottom - (*itorRightEnd).GetY();
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorRightEnd = m_listRight.end(); itorRightEnd--;
			m_listRight.push_back( CPositionInfo( (*itorRightEnd  ).GetX()     , 
				(*itorRightEnd  ).GetY() + 1 ,
				LINE_LEFT                    ,
				(*itorRightEnd  ).GetDown (m_nWidth) ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listRight.pop_back();
	}
	//Check Right Line 
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	//Check Upper Line 
	//Check Upper Line Begin
	nGap = (*itorUpBegin   ).GetX() - nLeft ;
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorUpBegin  = m_listUp.begin();
			m_listUp.push_front( CPositionInfo(   (*itorUpBegin ).GetX() - 1    , 
				(*itorUpBegin ).GetY()        ,
				LINE_TOP                      ,
				(*itorUpBegin ).GetBuffer()-1 ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listUp.pop_front();
	}

	//Check Upper Line End
	nGap = nRight - (*itorUpEnd ).GetX();
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorUpEnd  = m_listUp.end(); itorUpEnd--;
			m_listUp.push_back( CPositionInfo(    (*itorUpEnd   ).GetX() + 1    , 
				(*itorUpEnd   ).GetY()        ,
				LINE_TOP                      ,
				(*itorUpEnd   ).GetBuffer()+1 ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listUp.pop_back();
	}
	//Check Upper Line 
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	//Check Down Line 
	//Check Down Line Begin
	nGap = (*itorDownBegin   ).GetX() - nLeft ;
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorDownBegin  = m_listDown.begin();
			m_listDown.push_front( CPositionInfo( (*itorDownBegin ).GetX() - 1    , 
				(*itorDownBegin ).GetY()        ,
				LINE_BOTTOM                      ,
				(*itorDownBegin ).GetBuffer()-1 ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listDown.pop_front();
	}

	//Check Down Line End
	nGap = nRight - (*itorDownEnd ).GetX();
	if( nGap > 0 )
	{
		if( nGap > _LESS_ALLOWABLE ) return FALSE;
		while( nGap-- > 0 ) 
		{
			itorDownEnd = m_listDown.end(); itorDownEnd--;
			m_listDown.push_back( CPositionInfo( (*itorDownEnd ).GetX() + 1    , 
				(*itorDownEnd ).GetY()        ,
				LINE_BOTTOM                      ,
				(*itorDownEnd ).GetBuffer()+1 ) );
		}
	}
	else// (nGap < 0) or (nGap == 0)
	{
		while( nGap++ < 0 )
			m_listDown.pop_back();
	}
	//Check Down Line 
	////////////////////////////////////////////////////////////////////////////////////

	return TRUE;
}

size_t CBlockElement::GetSize( void ) 
{ 
	return m_listLeft.size() + m_listRight.size() + m_listUp.size() + m_listDown.size(); 
}

size_t CBlockElement::GetSizeLeft ( void ) 
{ 
	return m_listLeft .size(); 
}

size_t CBlockElement::GetSizeRight( void ) {
	return m_listRight.size(); 
}

size_t CBlockElement::GetSizeUp( void )
{ 
	return m_listUp   .size(); 
}

size_t CBlockElement::GetSizeDown ( void ) 
{ 
	return m_listDown .size(); 
}

float CBlockElement::GetDistance ( const INT& x1, const INT& x2, const INT& y1, const INT& y2 ) 
{
	float fDistance = sqrt( (float)(x2-x1)*(x2-x1) + (float)(y2-y1)*(y2-y1) );
	return fDistance;
}

BOOL CBlockElement::IsBlock( void ) 
{
	size_t nLeftSIze  = m_listLeft .size();
	size_t nRightSize = m_listRight.size();
	size_t nUpSIze    = m_listUp   .size();
	size_t nDownSize  = m_listDown .size();

	if( nLeftSIze  < _MACRO_BLOCK_SIZE ||
		nRightSize < _MACRO_BLOCK_SIZE ||
		nUpSIze    < _MACRO_BLOCK_SIZE || 
		nDownSize  < _MACRO_BLOCK_SIZE  ) return FALSE;

	return CheckConner();
	/*
	if( abs( (int)nLeftSIze-(int)nRightSize ) > _MACRO_BLOCK_SIZE*2 )
	return FALSE;

	LIST_POSITIONINFOItor itor1 = NULL;
	LIST_POSITIONINFOItor itor2 = NULL;
	int x1=0,x2=0,y1=0,y2=0;

	//포함관계를 조사하는 방법 추가 필요.
	itor1 = m_listUp  .begin();
	itor2 = m_listDown.begin();
	x1=(*itor1).GetX(); y1=(*itor1).GetY();
	x2=(*itor2).GetX(); y2=(*itor2).GetY();
	if( abs(y2-y1) < _MACRO_BLOCK_SIZE ) return FALSE;

	itor1 = m_listRight.begin();
	itor2 = m_listUp   .end  ();itor2--;
	x1=(*itor1).GetX(); y1=(*itor1).GetY();
	x2=(*itor2).GetX(); y2=(*itor2).GetY();
	if( GetDistance( x1, x2, y1, y2 ) > 2.0f ) return FALSE;

	itor1 = m_listRight.end  ();itor1--;
	itor2 = m_listDown .end  ();itor2--;
	x1=(*itor1).GetX(); y1=(*itor1).GetY();
	x2=(*itor2).GetX(); y2=(*itor2).GetY();
	if( GetDistance( x1, x2, y1, y2 ) > 2.0f ) return FALSE;

	itor1 = m_listLeft .begin();
	itor2 = m_listUp   .end  ();itor2--;
	x1=(*itor1).GetX(); y1=(*itor1).GetY();
	x2=(*itor2).GetX(); y2=(*itor2).GetY();
	if( GetDistance( x1, x2, y1, y2 ) > 2.0f ) return FALSE;

	itor1 = m_listLeft .end  ();itor1--;
	itor2 = m_listDown .end  ();itor2--;
	x1=(*itor1).GetX(); y1=(*itor1).GetY();
	x2=(*itor2).GetX(); y2=(*itor2).GetY();
	if( GetDistance( x1, x2, y1, y2 ) > 2.0f ) return FALSE;
	*/

	return TRUE;
}


LPLIST_POSITIONINFO CBlockElement::GetListLeft ( void ) 
{ 
	return &m_listLeft ; 
}

LPLIST_POSITIONINFO CBlockElement::GetListRight( void ) 
{ 
	return &m_listRight; 
}

LPLIST_POSITIONINFO CBlockElement::GetListUp( void ) 
{ 
	return &m_listUp   ; 
}

LPLIST_POSITIONINFO CBlockElement::GetListDown ( void ) 
{ 
	return &m_listDown ; 
}


void  CBlockElement::AddLeftLine ( INT nX, INT nY, ePOSITION_TYPE eType, BYTE* pData ) 
{ 
	m_listLeft .push_back( CPositionInfo(nX, nY, eType, pData) ); 
}

void  CBlockElement::AddRightLine( INT nX, INT nY, ePOSITION_TYPE eType, BYTE* pData ) 
{ 
	m_listRight.push_back( CPositionInfo(nX, nY, eType, pData) ); 
}


//pCopyedSrc에는 255를 254로 변환하여 입력 한다.
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

	LIST_POSITIONINFO  listTemp;  
	for( ; nY<nHeightEnd ; nY++ )
	{
		lpSrc = pCopyedSrc + (nY*nWidth+_MACRO_BLOCK_SIZE);
		for( nX = _MACRO_BLOCK_SIZE ; nX<nWidthEnd ; nX++, lpSrc++ )
		{
			if( _IS_MAX_L(lpSrc)                    && //완전 흰바탕에서 시작하는 블럭은 찾지 못함, 속도를 고려한 결과.
				_ABS_POS_SUB_L(lpSrc) > byteBarrier )
			{
				int nStartX = nX;
				int nRight  = 0;
				CBlockElement block( nWidth );
				*lpSrc = _MAX_GRAY;

				block.AddLeftLine( nX, nY, LEFT_TOP, lpSrc );
				lpSrc++;
				nX   ++;

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
				else
				{
					//Search Right Line - direction
					if( listTemp.size() )

					{
						LPLIST_POSITIONINFO lpListLeft  = block.GetListLeft ();
						LPLIST_POSITIONINFO lpListRight = block.GetListRight();
						*lpListRight = *lpListLeft;
						*lpListLeft  = listTemp   ;

						LIST_POSITIONINFOItor itorLeft = lpListLeft->begin();
						LPBYTE lpRight = (*itorLeft).GetBuffer();

						LPLIST_POSITIONINFO lpListPos = block.GetListRight();
						LIST_POSITIONINFOItor itor = lpListPos->begin();
						LPBYTE lpDown = (*itor).GetDown( nWidth );

						int    nTmpY  = nY+1;
						int    nTmpX  = (*itor).GetX();

						nRight        = nX;

						while( _ABS_POS_SUB_R(lpDown) > byteBarrier && 
							nTmpY < nHeightEnd )
						{
							*lpDown = _MAX_GRAY;

							lpListPos->push_back( CPositionInfo( nTmpX, nTmpY, LINE_RIGHT, lpDown) );
							itor++ ;
							nTmpY++;
							lpDown = (*itor).GetDown( nWidth );
							_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpDown );
						}
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
						lpRight = (*itorLeft).GetBuffer() + 1;

						if( _ABS_POS_SUB_U( lpRight, nWidth ) > byteBarrier )
						{
							//lpRight = (*itorLeft).GetBuffer()+1;
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

				if( block.GetSizeLeft() > _MACRO_BLOCK_SIZE &&
					block.GetSizeUp  () < _MACRO_BLOCK_SIZE  )
				{
					//Search Upper Line - direction
					int    nTmpX   = 0;
					int    nTmpY   = 0;
					LPBYTE lpLeft  = NULL;

					LPLIST_POSITIONINFO   lpListPosUp   = block.GetListUp();
					LPLIST_POSITIONINFO   lpListLeftPos = block.GetListLeft();

					LIST_POSITIONINFOItor itorLeftS     = lpListLeftPos->begin();
					LIST_POSITIONINFOItor itorLeftEnd   = lpListLeftPos->end  (); 
					for( int nItorCount=0 ; nItorCount<_MACRO_BLOCK_SIZE-1 ; nItorCount++ ) itorLeftEnd--;//Uppper line과 down line의 차이를 두기 위해

					while( itorLeftS != itorLeftEnd )//lpListLeftPos->end() )
					{
						lpLeft  = (*itorLeftS).GetBuffer() - 1;

						if( _ABS_POS_SUB_U( lpLeft , nWidth ) > byteBarrier )
						{
							//lpRight = (*itorLeft).GetBuffer()+1;
							nTmpX   = (*itorLeftS).GetX();
							nTmpY   = (*itorLeftS).GetY();

							while( _ABS_POS_SUB_U(lpLeft , nWidth) > byteBarrier && 
								   nTmpX                           < nWidthEnd   &&
								   nTmpX                           < nRight       )
							{
								if( *lpLeft == _MAX_GRAY )
								{
									LPLIST_POSITIONINFO   lpListPosLeft  = block.GetListLeft ();
									LPLIST_POSITIONINFO   lpListPosRight = block.GetListRight();

									//left line copy to right line
									listTemp          = *(lpListPosRight);
									*(lpListPosRight) = *(lpListPosLeft );

									//delete all left line
									while( lpListPosLeft->size() ) lpListPosLeft->pop_front();

									//Add New Left Line
									LIST_POSITIONINFOItor itorLeft = NULL;//lpListPosLeft->begin();
									LPBYTE lpDown = lpLeft;//(*itor).GetDown( nWidth );
									while( *lpDown == _MAX_GRAY && 
										   nTmpY   <  nHeightEnd )
									{
										lpListPosLeft->push_back( CPositionInfo( nTmpX, nTmpY, LINE_LEFT, lpDown) );
										//itor++;
										itorLeft = lpListPosLeft->end(); itorLeft--;
										nTmpY++;
										lpDown = (*itorLeft).GetDown( nWidth );
										_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpDown );
									}
									itorLeftS     = lpListLeftPos->end  (); itorLeftS--;
									itorLeftEnd   = lpListLeftPos->end  (); 


									break;
								}
								*lpLeft  = _MAX_GRAY;

								lpListPosUp->push_front( CPositionInfo( nTmpX, nTmpY, LINE_TOP, lpLeft ) );
								nTmpX  --;
								lpLeft --;
								_CHECK_BOUNDARY( lpBoundartStart, lpBoundartEnd, lpLeft );
							}

							if( lpListPosUp->size() < _MACRO_BLOCK_SIZE )
								while( lpListPosUp->size() ) lpListPosUp->pop_front();
							else break;

						}

						itorLeftS++;
					}
				}


				if( block.GetSizeLeft() > _MACRO_BLOCK_SIZE &&
					block.GetSizeUp  () > _MACRO_BLOCK_SIZE  )
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
						lpRight = (*itorLeft).GetBuffer() + 1;
						if( _ABS_POS_SUB_D( lpRight, nWidth ) > byteBarrier )
						{
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

			}//if( _IS_MAX_L(lpSrc) 
/*
			if( listTemp.size() )
			{
				CBlockElement block( nWidth );
				LPLIST_POSITIONINFO lpListLeft = block.GetListLeft();
				*lpListLeft = listTemp;

				LIST_POSITIONINFOItor itorLeft = lpListLeft->begin();
				LPBYTE lpRight = (*itorLeft).GetBuffer();

				int k=0;
			}
*/
		}//Image Scan X Direction
	}//Image Scan Y Direction

	return 0;
}
