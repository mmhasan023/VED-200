//iplFrame.h
//20090528 by Kiok ahn
//One Frame Information
#ifndef _IPL_CIPLFRAME_H_INCLUDE_
#define _IPL_CIPLFRAME_H_INCLUDE_

#include "iplDefine.h"

class CHistoRGB12bitBin;

class CIplFrame
{
public:
	CIplFrame(void);
	CIplFrame(const CIplFrame& frame);
	CIplFrame(LPBITMAPINFOHEADER lpBih, LPBYTE lpData, INT nDataSize);
	CIplFrame(LPBITMAPINFOHEADER lpBih, LPBYTE lpData, INT nDataSize, CHistoRGB12bitBin* pHistogram);
	CIplFrame(INT nWidth, INT nHeight , LPBYTE lpData, INT nDataSize);
	CIplFrame(INT nWidth, INT nHeight , INT nBytes=3);
	virtual ~CIplFrame(void);

public:

	void operator=(const CIplFrame& op);

	BOOL			   IsValide      ( void ){return m_lpData != NULL;};
	LPBITMAPINFOHEADER GetBih        ( void ){return &m_Bih;};
	LPBYTE			   GetPixelData  ( void ){return m_lpData;};
	INT                GetDataSize   ( void ){return m_nDataSize;};
	DOUBLE             GetSampleTime ( void ){return m_dbSampleTime;};
	UINT               GetFrameNo    ( void ){return m_nFrameNo;};
	CHistoRGB12bitBin* GetHistogram  ( void );

	void SetFrameNo     ( const UINT&   nFrameNo ){ m_nFrameNo=nFrameNo;};
	void SetSampleTime  ( const DOUBLE& dbSampleTime ){ m_dbSampleTime=dbSampleTime;};
	
	BOOL CalcHistogram ( void );//히스토그램 계산.

	virtual void SetData( 
		LPBITMAPINFOHEADER lpBih        , 
		LPBYTE             lpData       , 
		INT                nDataSize    , 
		CHistoRGB12bitBin* pHistogram   ,
		double             dblSampleTime,
		int                nFrameNo     );


protected:
	LPBYTE	volatile		m_lpData       ;
	UINT	volatile		m_nDataSize    ;
	BITMAPINFOHEADER		m_Bih          ;
	CHistoRGB12bitBin*      m_pHistogram   ;
	DOUBLE                  m_dbSampleTime ; 
	UINT                    m_nFrameNo     ;
};

#endif//_IPL_CIPLFRAME_H_INCLUDE_