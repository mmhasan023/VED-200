 //DetecBlackFrame.h
//Detection Black Frame
//By kiok ahn
//2009.06.03

#ifndef _DETECTION_BLACK_FRAME_H_INCLUDE_
#define _DETECTION_BLACK_FRAME_H_INCLUDE_

#include "stdafx.h"
#include "TTypeDefine.h"
#include "CommonDataApi.h"

typedef struct tagRGB
{
	BYTE R;
	BYTE B;
	BYTE G;
} RGBCOMP, *LPRGBCOMP;

class CRGBCompoment : public tagRGB
{
public:
	CRGBCompoment(){R=0;G=0;B=0;};
	CRGBCompoment(const CRGBCompoment& op){R=op.R;G=op.G;B=op.B;};
	CRGBCompoment(const tagRGB& op){R=op.R;G=op.G;B=op.B;};
	CRGBCompoment(const BYTE& r, const BYTE& g, const BYTE& b ){R=r;G=g;B=b;};
	virtual ~CRGBCompoment(){};

	CRGBCompoment& operator^(const CRGBCompoment& op)
	{
//		BYTE* pItor = (LPBYTE)&op;
//		R = R^(*pItor++);
//		G = G^(*pItor++);
//		B = B^(*pItor);

		R = R^op.R;
		G = G^op.G;
		B = B^op.B;
		return *this;
	};
	CRGBCompoment& operator^(const RGBCOMP& op)
	{
		//		BYTE* pItor = (LPBYTE)&op;
		//		R = R^(*pItor++);
		//		G = G^(*pItor++);
		//		B = B^(*pItor);

		R = R^op.R;
		G = G^op.G;
		B = B^op.B;
		return *this;
	};

	bool operator==(const CRGBCompoment& op)
	{
		if( R == op.R && G == op.G && B == op.B ) return true;
		return false;
	};
	bool operator==(const RGBCOMP& op)
	{
		if( R == op.R && G == op.G && B == op.B ) return true;
		return false;
	};
	bool operator!=(const CRGBCompoment& op)
	{
		if( R == op.R && G == op.G && B == op.B ) return false;
		return true;
	};
	bool operator!=(const RGBCOMP& op)
	{
		if( R == op.R && G == op.G && B == op.B ) return false;
		return true;
	};

};

class CDetectionBlackFrame
{
public:
	CDetectionBlackFrame(void);
	~CDetectionBlackFrame(void);

public:
	HRESULT CheckStream   ( LPAVDATA lpAVData );
	void    SetCallback   ( LPFN_AVRESULT lpCallback, LPVOID lpUserData );
	HRESULT FinishedStream( void );
	HRESULT SetOption     ( LPSTR_MAP lpmapOption );

protected:
	HRESULT SendErrorFrame(LPAVDATA lpAVData, const int& nTargetFrame);
	HRESULT SendAlramFrame(LPAVDATA lpAVData, const int& nTargetFrame);


protected:
	UINT      m_nStartFrame;
	UINT      m_nEndFrame  ;
	DOUBLE    m_dStartTime ;
	HINSTANCE m_hCommonDLL ;
	UINT      m_nCurFrame  ;
	HCDVIDEO  m_hCVideo    ;
	time_t    m_tSystemStart;
	time_t    m_tSystemEnd ;


	CVIDEOAPI       m_VideoApi  ;
//	CRGBCompoment   m_BeforeRGB ;
	CRGBCompoment   m_rgbBlack  ;
protected:
	void LoadCommonDLL(void);

private:
	LPFN_AVRESULT m_lpCallback       ;
	LPVOID        m_lpUserData       ;
	AVRESULT      m_AVResult         ;
	DWORD         m_dwDetecedFlag    ;

protected:
	BOOL          m_bInitFlag        ;
	//UINT          m_nStopProcessFrame;

	BYTE          m_byteNoiseLevel     ;
	BYTE		  m_AdditionValue	   ;
	UINT          m_nNoneDetectStart   ; //% about duration
	UINT          m_nNoneDetectEnd     ; //% about duration
	INT64		  m_nAlramTime		   ; // 지속시간
	BOOL		  m_bAlram			   ;
	BOOL          m_bDetectFalg        ;


	BYTE*         m_pGrayBuffer        ;
	INT           m_nSizeOfGray        ;

	BYTE*		  m_pSobelBuffer	   ;
	INT			  m_nSizeOfSobel	   ;


	BYTE*		  m_pTempBuffer		   ;
	INT			  m_nSizeOfTemp        ;

	FLOAT		  m_DetectBlockVal     ;	


};

#endif//_DETECTION_BLACK_FRAME_H_INCLUDE_