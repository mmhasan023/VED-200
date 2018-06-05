//#include "TTypeDefine.h"

#pragma once

typedef struct tag_nameinfo
{
	TCHAR m_lpszName    [MAX_PATH];	//Device or Format ³×ÀÓ
}NAMEINFO,*LPNAMEINFO;


class CNameInfo : public NAMEINFO
{
public:
	CNameInfo(			void				);
	CNameInfo(	const CNameInfo&	info	);
	CNameInfo(	const NAMEINFO&		info	);



public:
	void operator=(	const CNameInfo&	info	);
	void operator=(	const NAMEINFO&		info	);
};



