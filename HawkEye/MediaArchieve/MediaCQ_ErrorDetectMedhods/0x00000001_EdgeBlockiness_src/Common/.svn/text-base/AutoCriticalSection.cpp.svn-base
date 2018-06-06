#include "stdafx.h"
#include "AutoCriticalSection.h"

CAutoCriticalSection::CAutoCriticalSection( LPCRITICAL_SECTION  lpCS )
{
	m_lpCS = lpCS;
	EnterCriticalSection( m_lpCS );
}

CAutoCriticalSection::~CAutoCriticalSection()
{
	LeaveCriticalSection( m_lpCS );
	m_lpCS = NULL;
}
