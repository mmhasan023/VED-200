//CQInfoResult.h
#ifndef _CQ_INFO_RESULT_H_INCLUDE_
#define _CQ_INFO_RESULT_H_INCLUDE_

#include "TTypeDefine.h"

class CCQInfoResult : public CQINFORESULT
{
public:
	CCQInfoResult();
	CCQInfoResult( const CCQInfoResult& op);
	CCQInfoResult( const CQINFORESULT & op);
	CCQInfoResult( HBITMAP hBitmap, LPCTSTR lpThumbPath, LPCAVRESULT lpAVResult);
	~CCQInfoResult();

public:
	void operator =(const CCQInfoResult& op);
	void operator =(const CQINFORESULT & op);

protected:
	inline void init ( void );
	inline void set  ( const HBITMAP hInBitmap, LPCTSTR lpThumbPath, LPCAVRESULT lpAVResult );
};


typedef list<CCQInfoResult> LIST_CQINFORESULT, *LPLIST_CQINFORESULT;
typedef LIST_CQINFORESULT::iterator LIST_CQINFORESULTItor;


#endif//_CQ_INFO_RESULT_H_INCLUDE_