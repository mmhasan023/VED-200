//DetectTimeIntervalBase.h
//2011.03.03
//by Kiok Ahn
//비디오의 구간에러를 검출 하기위한 기본 클레스
//시작,끝 등에 대한 기본 변수들의 집합.
//CheckStream은 실제 알고리즘이 구현 되는 함수이므로 이 클래스를 상속 받아 꼭 구현 해야 함.

class CDetectTimeIntervalBase
{
public:
	CDetectTimeIntervalBase( const DWORD&      dwDetecedFlag, 
		                     const LPCVIDEOAPI lpVideoApi   );
	~CDetectTimeIntervalBase();

public:
	virtual HRESULT CheckStream		( LPAVDATA lpAVData							  )=0;
	virtual HRESULT SetCallback		( LPFN_AVRESULT lpCallback, LPVOID lpUserData );
	virtual HRESULT FinishedStream	( void );

	BOOL IsDetectState( void ){return m_bDetectFalg;};

protected:
	virtual HRESULT SendErrorFrame  ( LPAVDATA lpAVData, const int& nTargetFrame  );

protected:
	LPFN_AVRESULT   m_lpCallback   	  ;
	LPVOID          m_lpUserData   	  ;
	AVRESULT        m_AVResult     	  ;
	DWORD           m_dwDetecedFlag   ;
	LPCVIDEOAPI     m_lpVideoApi      ;
	BOOL            m_bInitFlag       ;

protected:
	UINT            m_nStartFrame     ;
	UINT            m_nEndFrame       ;
	DOUBLE          m_dStartTime      ;
	DOUBLE          m_dEndTime        ;

	time_t          m_tSystemStartTime;
	time_t          m_tSystemEndTime  ;

	TIMECODE			m_tcStart	;
	TIMECODE			m_tcEnd	;

	BOOL            m_bDetectFalg     ;
};
