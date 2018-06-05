//AutoCriticalSection.h
//Auto Critical Section
//by kiok ahn.
//2011.02.07
#pragma once

class CAutoCriticalSection
{
public:
	CAutoCriticalSection( LPCRITICAL_SECTION  lpCS );
	~CAutoCriticalSection();
protected:
	LPCRITICAL_SECTION  m_lpCS;
};