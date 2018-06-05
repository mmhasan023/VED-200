#include "stdafx.h"
#include "iplAPI.h"
#include "CQInfoResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCQInfoResult::CCQInfoResult()
{
	init();
}

CCQInfoResult::CCQInfoResult(const CCQInfoResult& op)
{
	*this = op;
}

CCQInfoResult::CCQInfoResult(const CQINFORESULT & op)
{
	*this = op;
}

CCQInfoResult::CCQInfoResult( HBITMAP hBitmap, LPCTSTR lpThumbPath, LPCAVRESULT lpAVResult)
{
	set( hBitmap, lpThumbPath, lpAVResult );
}

CCQInfoResult::~CCQInfoResult()
{
}

void CCQInfoResult::operator =(const CCQInfoResult& op)
{
	set( op.hBitmap, op.szThumbPath, (LPCAVRESULT)&op.AVResult );
}

void CCQInfoResult::operator =(const CQINFORESULT & op)
{
	set( op.hBitmap, op.szThumbPath, (LPCAVRESULT)&op.AVResult );
}

void CCQInfoResult::init( void )
{
	hBitmap  = NULL;
	iplmemzero( szThumbPath, sizeof(TCHAR)*MAX_PATH*2 );
	iplmemzero( &AVResult  , sizeof(AVRESULT)         );
}

void CCQInfoResult::set( const HBITMAP hInBitmap, LPCTSTR lpThumbPath, LPCAVRESULT lpAVResult  )
{
	hBitmap  = hInBitmap;
	iplmemcpy( szThumbPath, lpThumbPath, sizeof(TCHAR)*MAX_PATH*2 );
	iplmemcpy( &AVResult  , lpAVResult , sizeof(AVRESULT)         );
}