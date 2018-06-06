//DetectBlock.h
//Detection Block for x times Macro block size.
//2010.02.22
//by kiok ahn
//kiokahn@mediachorus.com

#ifndef _DETECT_BLOCK_H_INCLUDE_
#define _DETECT_BLOCK_H_INCLUDE_

#include <list>
#include <math.h>
using namespace std;

#define _MACRO_BLOCK_SIZE    8
#define _MAX_GRAY         0xFF
#define _LESS_ALLOWABLE      3//모자람에 대한 허용 오차, 3 pixel


#define _IS_MAX_L(pX) (*pX!=_MAX_GRAY && *(pX-1)!=_MAX_GRAY && *(pX+1)!=_MAX_GRAY)
#define _IS_MAX_R(pX) (*pX!=_MAX_GRAY && *(pX+1)!=_MAX_GRAY)

#define _ABS_POS_SUB_L(pX) abs( (int)(*(pX+1)) - (int)(*(pX-1)) )
#define _ABS_POS_SUB_R(pX) abs( (int)(*(pX-1)) - (int)(*(pX+1)) )

#define _ABS_POS_SUB_U(pX,nWidth) abs( (int)(*(pX+nWidth)) - (int)(*(pX-nWidth)) )
#define _ABS_POS_SUB_D(pX,nWidth) abs( (int)(*(pX-nWidth)) - (int)(*(pX+nWidth)) )

#define _CHECK_BOUNDARY(nMin,nMax,nValue) if(nMax<nValue || nValue<nMin )break;

enum ePOSITION_TYPE{
	T_UNKNOW = 0,
	LEFT_TOP = 1,
	LINE_TOP    ,
	RIGHT_TOP   ,
	LINE_RIGHT  ,
	RIGHT_BOTTOM,
	LINE_BOTTOM ,
	LEFT_BOTTOM ,
	LINE_LEFT
};

typedef struct tagPositionInfo
{
	INT              nX   ;
	INT              nY   ;
	ePOSITION_TYPE   eType;//1:left_top, 2:line_top, 3:right_top, 4:line_right, 5:right_bottom, 6:line_bottom, 7:left_bottom, 8:line_left
	BYTE*            pData;
}POSITIONINFO, *LPPOSITIONINFO;

class CPositionInfo : public tagPositionInfo
{
public:
	CPositionInfo(                           ) { nX=0;nY=0;eType=T_UNKNOW;pData=NULL; };
	CPositionInfo( const POSITIONINFO & info ) { (*this)=info;                 };
	CPositionInfo( const CPositionInfo& info ) { (*this)=(POSITIONINFO)(info); };
	CPositionInfo( INT _X, INT _Y, ePOSITION_TYPE _Type, BYTE* _Data ){ nX=_X;nY=_Y;eType=_Type;pData=_Data; };
	~CPositionInfo(){};

//operator
public:
	void operator=( const POSITIONINFO& info )
	{
		memcpy( (void*)this, (void*)&info, sizeof(POSITIONINFO) );
	};

	void operator=( const CPositionInfo& info )
	{
		(*this)=(POSITIONINFO)(info);
	};

	BOOL operator==(POSITIONINFO info) const throw()
	{
		return ( nX==info.nX && nY==info.nY )? TRUE : FALSE;
	};

	BOOL operator!=(POSITIONINFO info) const throw()
	{
		return !( *this==info );
	};


public:
	BYTE* GetUpper ( const INT& nWidth, const INT& nBytes = 1 ){ return ( pData + nWidth*nBytes); };
	BYTE* GetDown  ( const INT& nWidth, const INT& nBytes = 1 ){ return ( pData + nWidth*nBytes); };
	BYTE* GetBuffer( void                                     ){ return   pData; };

	INT   GetX     ( void ) {return nX;};
	INT   GetY     ( void ) {return nY;};

	void  SetType  ( const ePOSITION_TYPE& _Type ){ eType=_Type; };
};

typedef list<CPositionInfo> LIST_POSITIONINFO, *LPLIST_POSITIONINFO;
typedef LIST_POSITIONINFO::iterator LIST_POSITIONINFOItor;


class CBlockElement
{//MAX RIO영역을 _MACRO_BLOCK_SIZE 안쪽으로만 잡는다.

public:
	CBlockElement( const INT& nWidth ){ m_nWidth = nWidth;};
	CBlockElement( const CBlockElement& block ){ (*this)=block; };
	~CBlockElement(){};

//operator
public:
	void operator=( const CBlockElement& block )
	{
		m_listLeft  = block.m_listLeft ;
		m_listRight = block.m_listRight;
		m_listUp    = block.m_listUp   ;
		m_listDown  = block.m_listDown ;
		m_nWidth    = block.m_nWidth   ;
	};
protected:
	BOOL  CheckConner( void ){
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
	};

public:
	size_t  GetSize     ( void ) { 
		return m_listLeft.size() + m_listRight.size() + m_listUp.size() + m_listDown.size(); 
	};
	size_t  GetSizeLeft ( void ) { return m_listLeft .size(); };
	size_t  GetSizeRight( void ) { return m_listRight.size(); };
	size_t  GetSizeUp   ( void ) { return m_listUp   .size(); };
	size_t  GetSizeDown ( void ) { return m_listDown .size(); };
	float   GetDistance ( const INT& x1, const INT& x2, const INT& y1, const INT& y2 ) {
		float fDistance = sqrt( (float)(x2-x1)*(x2-x1) + (float)(y2-y1)*(y2-y1) );
		return fDistance;
	}

	BOOL  IsBlock     ( void ) {
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
	};


	LPLIST_POSITIONINFO GetListLeft ( void ) { return &m_listLeft ; };
	LPLIST_POSITIONINFO GetListRight( void ) { return &m_listRight; };
	LPLIST_POSITIONINFO GetListUp   ( void ) { return &m_listUp   ; };
	LPLIST_POSITIONINFO GetListDown ( void ) { return &m_listDown ; };


	void  AddLeftLine ( INT nX, INT nY, ePOSITION_TYPE eType, BYTE* pData ) { 
		m_listLeft .push_back( CPositionInfo(nX, nY, eType, pData) ); 
	};
	void  AddRightLine( INT nX, INT nY, ePOSITION_TYPE eType, BYTE* pData ) { 
		m_listRight.push_back( CPositionInfo(nX, nY, eType, pData) ); 
	};

protected:
	LIST_POSITIONINFO m_listLeft ;
	LIST_POSITIONINFO m_listRight;
	LIST_POSITIONINFO m_listUp   ;
	LIST_POSITIONINFO m_listDown ;

	INT               m_nWidth   ;
};

typedef list<CBlockElement>  LIST_BLOCK, *LPLIST_BLOCK;
typedef LIST_BLOCK::iterator LIST_BLOCKItor;

//pCopyedSrc는 내부에서 값이 변경 된다.
//For Gray Image
int ipl_BlockDetect( IN LPBYTE pCopyedSrc, int nWidth, int nHeight, OUT LPLIST_BLOCK lpListBlock, IN BYTE byteBarrier=30, IN INT nMaxBlockSize=32 );
//int _IPL_API _IPL_CALL ipl_BlockDetect( IN LPBYTE pCopyedSrc, int nWidth, int nHeight, IN BYTE byteBarrier=30, IN INT nMaxBlockSize=64 );

//#define _DETECT_CLASS
#ifdef _DETECT_CLASS

class CDetectBlock
{
public:
	CDetectBlock( const BYTE& byteBarrier = 30, const INT& nMaxBlockSize = 32);
	~CDetectBlock();

public:
	HRESULT CheckStream   ( LPAVDATA lpAVData);
	void    SetCallback   ( LPFN_AVRESULT lpCallback, LPVOID lpUserData );
	HRESULT FinishedStream( void );
	HRESULT SetOption     ( LPSTR_MAP lpmapOption );

protected:
	void    LoadCommonDLL ( void );
	HRESULT SendErrorFrame( LPAVDATA lpAVData, const int& nTargetFrame );

private:
	LPFN_AVRESULT m_lpCallback       ;
	LPVOID        m_lpUserData       ;
	AVRESULT      m_AVResult         ;
	DWORD         m_dwDetecedFlag    ;

protected:
	BYTE            m_byteBarrier  ;
	INT             m_nMaxBlockSize;
};
#endif

#endif//_DETECT_BLOCK_H_INCLUDE_
