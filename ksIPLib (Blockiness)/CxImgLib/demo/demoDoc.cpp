// demoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "demoDoc.h"
#include "demoView.h"
#include "DlgRotate.h"
#include "DlgResample.h"
#include "DlgDecBpp.h"
#include "DlgIncBpp.h"
#include "DlgOptions.h"
#include "DlgDither.h"
#include "DlgThreshold.h"
#include "DlgColorize.h"
#include "Quantize.h"
#include "DlgOpacity.h"
#include "DlgGamma.h"
#include "DlgPalette.h"
#include "DlgCombine.h"
#include "DlgFFT.h"
#include "DlgRepair.h"
#include "DlgText.h"
#include "DlgMix.h"
#include "DlgSkew.h"
#include "DlgJpeg.h"
#include "DlgDataExt.h"
#include "DlgCustomFilter.h"
#include "DlgExpand.h"
#include "DlgFloodFill.h"
#include "DlgShadow.h"

#include "ximage.h"
#include <math.h>
#include <process.h>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define BLOCK_SIZE 7
#define BLOCK_TYPE_RIGHT		1
#define BLOCK_TYPE_BOTTOM		2

//#include "iplBlockElement.h"

#ifdef _LOGDATA
	#include "log.h"
#endif

extern DlgDataExtInfo dlgDataExtInfos;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_STRETCH_MODE, OnStretchMode)
	ON_UPDATE_COMMAND_UI(ID_STRETCH_MODE, OnUpdateStretchMode)
	ON_COMMAND(ID_TRANSFORM_ELLIPSE, OnTransformEllipse)
	ON_COMMAND(ID_WINDOW_DUPLICATE, OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_CXIMAGE_FLIP, OnCximageFlip)
	ON_COMMAND(ID_CXIMAGE_MIRROR, OnCximageMirror)
	ON_COMMAND(ID_CXIMAGE_NEGATIVE, OnCximageNegative)
	ON_COMMAND(ID_CXIMAGE_GRAYSCALE, OnCximageGrayscale)
	ON_COMMAND(ID_CXIMAGE_ROTATE, OnCximageRotate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
	ON_COMMAND(ID_VIEW_NORMALVIEWING11, OnViewNormalviewing11)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMALVIEWING11, OnUpdateViewNormalviewing11)
	ON_COMMAND(ID_CXIMAGE_SETTRANSPARENCY, OnCximageSettransparency)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SETTRANSPARENCY, OnUpdateCximageSettransparency)
	ON_COMMAND(ID_CXIMAGE_REMOVETRANSPARENCY, OnCximageRemovetransparency)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REMOVETRANSPARENCY, OnUpdateCximageRemovetransparency)
	ON_COMMAND(ID_CXIMAGE_RESAMPLE, OnCximageResample)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_FLIP, OnUpdateCximageFlip)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GRAYSCALE, OnUpdateCximageGrayscale)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_MIRROR, OnUpdateCximageMirror)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_NEGATIVE, OnUpdateCximageNegative)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_RESAMPLE, OnUpdateCximageResample)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATE, OnUpdateCximageRotate)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_ELLIPSE, OnUpdateTransformEllipse)
	ON_COMMAND(ID_CXIMAGE_DECREASEBPP, OnCximageDecreasebpp)
	ON_COMMAND(ID_CXIMAGE_INCREASEBPP, OnCximageIncreasebpp)
	ON_COMMAND(ID_CXIMAGE_OPTIONS, OnCximageOptions)
	ON_COMMAND(ID_CXIMAGE_DITHER, OnCximageDither)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DITHER, OnUpdateCximageDither)
	ON_COMMAND(ID_CXIMAGE_THRESHOLD, OnCximageThreshold)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_THRESHOLD, OnUpdateCximageThreshold)
	ON_COMMAND(ID_CXIMAGE_SPLITRGB, OnCximageSplitrgb)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITRGB, OnUpdateCximageSplitrgb)
	ON_COMMAND(ID_CXIMAGE_SPLITYUV, OnCximageSplityuv)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITYUV, OnUpdateCximageSplityuv)
	ON_COMMAND(ID_CXIMAGE_SPLITHSL, OnCximageSplithsl)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITHSL, OnUpdateCximageSplithsl)
	ON_COMMAND(ID_CXIMAGE_PSEUDOCOLORS, OnCximagePseudocolors)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_PSEUDOCOLORS, OnUpdateCximagePseudocolors)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_COLORIZE, OnUpdateCximageFiltersColorize)
	ON_COMMAND(ID_CXIMAGE_COLORIZE, OnCximageFiltersColorize)
	ON_COMMAND(ID_CXIMAGE_DARKEN, OnCximageDarken)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DARKEN, OnUpdateCximageDarken)
	ON_COMMAND(ID_CXIMAGE_LIGHTEN, OnCximageLighten)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_LIGHTEN, OnUpdateCximageLighten)
	ON_COMMAND(ID_CXIMAGE_CONTRAST, OnCximageContrast)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CONTRAST, OnUpdateCximageContrast)
	ON_COMMAND(ID_CXIMAGE_EMBOSS, OnCximageEmboss)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_EMBOSS, OnUpdateCximageEmboss)
	ON_COMMAND(ID_CXIMAGE_BLUR, OnCximageBlur)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_BLUR, OnUpdateCximageBlur)
	ON_COMMAND(ID_CXIMAGE_DILATE, OnCximageDilate)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DILATE, OnUpdateCximageDilate)

	ON_COMMAND(ID_CXIMAGE_CORNER_DETECTION, OnCximageCornerDetection)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CORNER_DETECTION, OnUpdateCximageCornerDetection)
	ON_COMMAND(ID_CXIMAGE_TEST, OnCximageTest)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_TEST, OnUpdateCximageTest)
	ON_COMMAND(ID_CXIMAGE_DETECTBLOCK, OnCximageDetectBlock)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DETECTBLOCK, OnUpdateCximageDetectBlock)
	ON_COMMAND(ID_CXIMAGE_DETECTDCTCODEBLOCK, OnCximageDetectDCTCodeBlock)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DETECTDCTCODEBLOCK, OnUpdateCximageDetectDCTCodeBlock)
	ON_COMMAND(ID_CXIMAGE_DETECTEDGEBLOCK, OnCximageDetectEdgeBlock)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DETECTEDGEBLOCK, OnUpdateCximageDetectEdgeBlock)
	ON_COMMAND(ID_CXIMAGE_DTTECTSTRIPE, OnCximageDetectStripe)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DTTECTSTRIPE, OnUpdateCximageDetectStripe)
	ON_COMMAND(ID_CXIMAGE_DTTECTSTRIPE, OnCximageDetectBlockiness)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_DTTECTSTRIPE, OnUpdateCximageDetectBlockiness)
	
	

	ON_COMMAND(ID_CXIMAGE_EDGE, OnCximageEdge)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_EDGE, OnUpdateCximageEdge)
	ON_COMMAND(ID_CXIMAGE_ERODE, OnCximageErode)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ERODE, OnUpdateCximageErode)
	ON_COMMAND(ID_CXIMAGE_SHARPEN, OnCximageSharpen)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SHARPEN, OnUpdateCximageSharpen)
	ON_COMMAND(ID_CXIMAGE_SOFTEN, OnCximageSoften)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SOFTEN, OnUpdateCximageSoften)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CROP, OnUpdateCximageCrop)
	ON_COMMAND(ID_CXIMAGE_CROP, OnCximageCrop)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REMOVEALPHACHANNEL, OnUpdateCximageRemovealphachannel)
	ON_COMMAND(ID_CXIMAGE_REMOVEALPHACHANNEL, OnCximageRemovealphachannel)
	ON_COMMAND(ID_CXIMAGE_OPACITY, OnCximageOpacity)
	ON_COMMAND(ID_CXIMAGE_INVETALPHA, OnCximageInvetalpha)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_INVETALPHA, OnUpdateCximageInvetalpha)
	ON_COMMAND(ID_CXIMAGE_ALPHAPALETTETOGGLE, OnCximageAlphapalettetoggle)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ALPHAPALETTETOGGLE, OnUpdateCximageAlphapalettetoggle)
	ON_COMMAND(ID_CXIMAGE_ALPHASTRIP, OnCximageAlphastrip)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ALPHASTRIP, OnUpdateCximageAlphastrip)
	ON_COMMAND(ID_CXIMAGE_ROTATEL, OnCximageRotatel)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATEL, OnUpdateCximageRotatel)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATER, OnUpdateCximageRotater)
	ON_COMMAND(ID_CXIMAGE_ROTATER, OnCximageRotater)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GAMMA, OnUpdateCximageGamma)
	ON_COMMAND(ID_CXIMAGE_GAMMA, OnCximageGamma)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_MEDIAN, OnUpdateCximageMedian)
	ON_COMMAND(ID_CXIMAGE_MEDIAN, OnCximageMedian)
	ON_COMMAND(ID_CXIMAGE_ADDNOISE, OnCximageAddnoise)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ADDNOISE, OnUpdateCximageAddnoise)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_MOVE, OnUpdateViewToolsMove)
	ON_COMMAND(ID_VIEW_TOOLS_MOVE, OnViewToolsMove)
	ON_COMMAND(ID_VIEW_TOOLS_SELECT, OnViewToolsSelect)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_SELECT, OnUpdateViewToolsSelect)
	ON_COMMAND(ID_VIEW_TOOLS_ZOOM, OnViewToolsZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_ZOOM, OnUpdateViewToolsZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PALETTE, OnUpdateViewPalette)
	ON_COMMAND(ID_VIEW_PALETTE, OnViewPalette)
	ON_COMMAND(ID_CXIMAGE_COMBINE, OnCximageCombine)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_COMBINE, OnUpdateCximageCombine)
	ON_COMMAND(ID_CXIMAGE_FFT, OnCximageFft)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_FFT, OnUpdateCximageFft)
	ON_COMMAND(ID_CXIMAGE_SPLITYIQ, OnCximageSplityiq)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITYIQ, OnUpdateCximageSplityiq)
	ON_COMMAND(ID_CXIMAGE_SPLITXYZ, OnCximageSplitxyz)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITXYZ, OnUpdateCximageSplitxyz)
	ON_COMMAND(ID_CXIMAGE_REPAIR, OnCximageRepair)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REPAIR, OnUpdateCximageRepair)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ALPHACHANNEL_SPLIT, OnUpdateCximageAlphachannelSplit)
	ON_COMMAND(ID_CXIMAGE_ALPHACHANNEL_SPLIT, OnCximageAlphachannelSplit)
	ON_COMMAND(ID_VIEW_TOOLS_TEXT, OnViewToolsText)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_TEXT, OnUpdateViewToolsText)
	ON_COMMAND(ID_CXIMAGE_SPLITCMYK, OnCximageSplitcmyk)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SPLITCMYK, OnUpdateCximageSplitcmyk)
	ON_COMMAND(ID_CXIMAGE_ALPHACREATE, OnCximageAlphaCreate)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_LOG, OnCximageFiltersLog)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_LOG, OnUpdateCximageFiltersLog)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_ROOT, OnCximageFiltersRoot)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_ROOT, OnUpdateCximageFiltersRoot)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_EQUALIZE, OnCximageHistogramEqualize)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_EQUALIZE, OnUpdateCximageHistogramEqualize)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_NORMALIZE, OnCximageHistogramNormalize)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_NORMALIZE, OnUpdateCximageHistogramNormalize)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCH, OnCximageHistogramStretch)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCH, OnUpdateCximageHistogramStretch)
	ON_COMMAND(ID_CXIMAGE_GAUSSIAN3X3, OnCximageGaussian3x3)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GAUSSIAN3X3, OnUpdateCximageGaussian3x3)
	ON_COMMAND(ID_CXIMAGE_GAUSSIAN5X5, OnCximageGaussian5x5)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GAUSSIAN5X5, OnUpdateCximageGaussian5x5)
	ON_COMMAND(ID_CXIMAGE_CONTOUR, OnCximageContour)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CONTOUR, OnUpdateCximageContour)
	ON_COMMAND(ID_CXIMAGE_LESSCONTRAST, OnCximageLesscontrast)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_LESSCONTRAST, OnUpdateCximageLesscontrast)
	ON_COMMAND(ID_CXIMAGE_JITTER, OnCximageJitter)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_JITTER, OnUpdateCximageJitter)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_DUPLICATE, OnUpdateWindowDuplicate)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_MIX, OnUpdateFiltersMix)
	ON_COMMAND(ID_FILTERS_MIX, OnFiltersMix)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER, OnCximageCircletransformCylinder)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER, OnUpdateCximageCircletransformCylinder)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_PINCH, OnCximageCircletransformPinch)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_PINCH, OnUpdateCximageCircletransformPinch)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_PUNCH, OnCximageCircletransformPunch)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_PUNCH, OnUpdateCximageCircletransformPunch)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_SWIRL, OnCximageCircletransformSwirl)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_SWIRL, OnUpdateCximageCircletransformSwirl)
	ON_COMMAND(ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM, OnCximageCircletransformBathroom)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM, OnUpdateCximageCircletransformBathroom)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCH1, OnCximageHistogramStretch1)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCH2, OnCximageHistogramStretch2)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCH1, OnUpdateCximageHistogramStretch1)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCH2, OnUpdateCximageHistogramStretch2)
	ON_COMMAND(ID_FILTERS_NONLINEAR_EDGE, OnFiltersNonlinearEdge)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_NONLINEAR_EDGE, OnUpdateFiltersNonlinearEdge)
	ON_COMMAND(ID_CXIMAGE_SKEW, OnCximageSkew)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SKEW, OnUpdateCximageSkew)
	ON_COMMAND(ID_VIEW_TOOLS_TRACKER, OnViewToolsTracker)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_TRACKER, OnUpdateViewToolsTracker)
	ON_COMMAND(ID_FILTERS_JPEGCOMPRESSION, OnJpegcompression)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_JPEGCOMPRESSION, OnUpdateJpegcompression)
	ON_COMMAND(ID_VIEW_SMOOTH, OnViewSmooth)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMOOTH, OnUpdateViewSmooth)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_DATAEXT, OnUpdateFiltersDataext)
	ON_COMMAND(ID_FILTERS_DATAEXT, OnFiltersDataext)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_UNSHARPMASK, OnUpdateCximageUnsharpmask)
	ON_COMMAND(ID_CXIMAGE_UNSHARPMASK, OnCximageUnsharpmask)
	ON_COMMAND(ID_CXIMAGE_TEXTBLUR, OnCximageTextblur)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_TEXTBLUR, OnUpdateCximageTextblur)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REDEYEREMOVE, OnUpdateCximageRedeyeremove)
	ON_COMMAND(ID_CXIMAGE_REDEYEREMOVE, OnCximageRedeyeremove)
	ON_COMMAND(ID_CXIMAGE_BLURSELBORDER, OnCximageBlurselborder)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_BLURSELBORDER, OnUpdateCximageBlurselborder)
	ON_COMMAND(ID_CXIMAGE_SELECTIVEBLUR, OnCximageSelectiveblur)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SELECTIVEBLUR, OnUpdateCximageSelectiveblur)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GETTRANSPARENCYMASK, OnUpdateCximageGettransparencymask)
	ON_COMMAND(ID_CXIMAGE_GETTRANSPARENCYMASK, OnCximageGettransparencymask)
	ON_COMMAND(ID_COLORS_COUNTCOLORS, OnColorsCountcolors)
	ON_UPDATE_COMMAND_UI(ID_COLORS_COUNTCOLORS, OnUpdateColorsCountcolors)
	ON_COMMAND(ID_FILTERS_LINEAR_CUSTOM, OnFiltersLinearCustom)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_LINEAR_CUSTOM, OnUpdateFiltersLinearCustom)
	ON_COMMAND(ID_CXIMAGE_CANVASSIZE, OnCximageCanvassize)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_CANVASSIZE, OnUpdateCximageCanvassize)
	ON_COMMAND(ID_VIEW_TOOLS_FLOODFILL, OnViewToolsFloodfill)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLS_FLOODFILL, OnUpdateViewToolsFloodfill)
	ON_COMMAND(ID_CXIMAGE_REMOVESELECTION, OnCximageRemoveselection)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REMOVESELECTION, OnUpdateCximageRemoveselection)
	ON_COMMAND(ID_COLORS_MORESATURATIONHSL, OnColorsMoresaturationhsl)
	ON_UPDATE_COMMAND_UI(ID_COLORS_MORESATURATIONHSL, OnUpdateColorsMoresaturationhsl)
	ON_COMMAND(ID_COLORS_MORESATURATIONYUV, OnColorsMoresaturationyuv)
	ON_UPDATE_COMMAND_UI(ID_COLORS_MORESATURATIONYUV, OnUpdateColorsMoresaturationyuv)
	ON_COMMAND(ID_COLORS_LESSSATURATION, OnColorsLesssaturation)
	ON_UPDATE_COMMAND_UI(ID_COLORS_LESSSATURATION, OnUpdateColorsLesssaturation)
	ON_COMMAND(ID_COLORS_HISTOGRAM_FULLSATURATION, OnColorsHistogramFullsaturation)
	ON_UPDATE_COMMAND_UI(ID_COLORS_HISTOGRAM_FULLSATURATION, OnUpdateColorsHistogramFullsaturation)
	ON_COMMAND(ID_COLORS_HISTOGRAM_HALFSATURATION, OnColorsHistogramHalfsaturation)
	ON_UPDATE_COMMAND_UI(ID_COLORS_HISTOGRAM_HALFSATURATION, OnUpdateColorsHistogramHalfsaturation)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCHT0, OnCximageHistogramStretcht0)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCHT0, OnUpdateCximageHistogramStretcht0)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCHT1, OnCximageHistogramStretcht1)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCHT1, OnUpdateCximageHistogramStretcht1)
	ON_COMMAND(ID_CXIMAGE_HISTOGRAM_STRETCHT2, OnCximageHistogramStretcht2)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_HISTOGRAM_STRETCHT2, OnUpdateCximageHistogramStretcht2)
	ON_COMMAND(ID_COLORS_ADAPTIVETHRESHOLD, OnColorsAdaptivethreshold)
	ON_UPDATE_COMMAND_UI(ID_COLORS_ADAPTIVETHRESHOLD, OnUpdateColorsAdaptivethreshold)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIOUSFRAME, OnUpdateViewPreviousframe)
	ON_COMMAND(ID_VIEW_PREVIOUSFRAME, OnViewPreviousframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEXTFRAME, OnUpdateViewNextframe)
	ON_COMMAND(ID_VIEW_NEXTFRAME, OnViewNextframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYANIMATION, OnUpdateViewPlayanimation)
	ON_COMMAND(ID_VIEW_PLAYANIMATION, OnViewPlayanimation)
	ON_UPDATE_COMMAND_UI(ID_FILTERS_ADDSHADOW, OnUpdateFiltersAddshadow)
	ON_COMMAND(ID_FILTERS_ADDSHADOW, OnFiltersAddshadow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
// CDemoDoc construction/destruction
CDemoDoc::CDemoDoc()
{
	image = NULL;
	m_WaitingClick = stretchMode = m_bSmoothDisplay = FALSE;
	for (int i=0;i<MAX_UNDO_LEVELS;i++) imageUndo[i]=NULL;
	m_UndoLevel=0;
	m_ZoomFactor=1;
	QueryPerformanceFrequency(&m_swFreq);
	m_etime = 0.0;
	hThread=hProgress=0;
	m_NumSel=0;
	m_tool=0;
	m_playanimation = 0;
	m_hmax=0;
#ifndef VATI_EXTENSIONS
	memset(&m_font,0,sizeof(m_font));
	m_color=0;
	m_text=_T("text");
#endif
}
//////////////////////////////////////////////////////////////////////////////
CDemoDoc::~CDemoDoc()
{
	// stop the elaborations
	if (image) image->SetEscape(1);
	// stop the progress bar
	if (hProgress){
		ResumeThread(hProgress); //wake up!
		WaitForSingleObject(hProgress,INFINITE);
		CloseHandle(hProgress);
	}
	if (hThread){
		WaitForSingleObject(hThread,INFINITE);
		CloseHandle(hThread);
	}
	// free objects
	delete image;
	for (int i=0;i<MAX_UNDO_LEVELS;i++) delete imageUndo[i];
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	image = NULL;

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////
// CDemoDoc serialization
void CDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())	{ } 
	else { }
}
//////////////////////////////////////////////////////////////////////////////
// CDemoDoc diagnostics
#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
//////////////////////////////////////////////////////////////////////////////
// CDemoDoc commands
CString CDemoDoc::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}
//////////////////////////////////////////////////////////////////////////////
CString CDemoDoc::RemoveExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(0,i);
		}
	}
	return name;
}
//////////////////////////////////////////////////////////////////////////////
int CDemoDoc::FindType(const CString& ext)
{
	return CxImage::GetTypeIdFromName(ext);
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == _T("")) return FALSE;

	int type = FindType(ext);

/*
	CxImage iinfo;
	CxIOFile file;
	file.Open(filename,"rb");
	bool bOk = iinfo.CheckFormat(&file);
	long t = iinfo.GetType();
	long w = iinfo.GetWidth();
	long h = iinfo.GetHeight();
*/

	Stopwatch(0);
	image = new CxImage(filename, type);
	Stopwatch(1);

	if (!image->IsValid()){
		CString s = image->GetLastError();
		AfxMessageBox(s);
		delete image;
		image = NULL;
		return FALSE;
	}

	UpdateStatusBar();
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);

	//multiple images (TIFF/ICO)
	if (image->GetNumFrames()>1){
		CString s;
		s.Format(_T("File with %d images. Read all?"),image->GetNumFrames());
		if (AfxMessageBox(s,MB_OKCANCEL)==IDOK){
			
			int j; // points to the document name
			for(j=_tcslen(filename)-1;j>=0;j--){
				if (filename[j]=='\\'){	j++; break;	}
			}
			// create the documents for the other images
			for(int i=1;i<image->GetNumFrames();i++){
				CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL);
				if (NewDoc)	{
					CxImage *newImage = new CxImage();
					newImage->SetFrame(i);
					newImage->Load(filename,type);
					NewDoc->image = newImage;
					CString s;
					s.Format(_T("%s (%d)"),filename.Mid(j),i+1);
					NewDoc->SetTitle(s);
					NewDoc->UpdateAllViews(NULL,WM_USER_NEWIMAGE);
				}
			}
		} else {
			if (type == CXIMAGE_FORMAT_GIF){
				image->SetRetreiveAllFrames(true);
				image->SetFrame(image->GetNumFrames()-1);
				image->Load(filename, type);
				s = _T("Play animation?");
				if (AfxMessageBox(s,MB_YESNO)==IDYES){
					OnViewPlayanimation();
				}
			}
		}
	}

	// EXIF jpegs
	if (image->GetType() == CXIMAGE_FORMAT_JPG){
		FILE* hfile = _tfopen(filename,_T("rb"));
		m_exif.DecodeExif(hfile);
		fclose(hfile);
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == _T("")) return FALSE;

	int type = FindType(ext);
	if (type == CXIMAGE_FORMAT_UNKNOWN) return FALSE;

	if (type == CXIMAGE_FORMAT_GIF && image->GetBpp()>8){
		AfxMessageBox(_T("The image will be saved as a true color GIF!\nThis is ok for CxImage, but not for many other programs.\nFor better compatibility, please use DecreaseBpp to 8 bits or less."),MB_ICONINFORMATION);
	}

	bool retval;
	Stopwatch(0);
	retval = image->Save(filename, type);
	Stopwatch(1);
	UpdateStatusBar();
	if (retval) return TRUE;
	CString s = image->GetLastError();
	AfxMessageBox(s);

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////
BOOL CDemoDoc::DoSave(LPCTSTR pszPathName, BOOL bReplace /*=TRUE*/)
{
	if (!image)	return FALSE;

	CString newName = pszPathName;
	BOOL bModified = IsModified();

	BOOL bSaveAs = FALSE;
	if (newName.IsEmpty()) bSaveAs = TRUE;
	else if (!theApp.GetWritableType(image->GetType()))	bSaveAs = TRUE;

	if (bSaveAs){
		newName = m_strPathName;

		newName = RemoveExtension(newName);

		if (bReplace && newName.IsEmpty()){
			newName = m_strTitle;
			newName = RemoveExtension(newName);
			int iBad = newName.FindOneOf(_T("#%;/\\"));    // dubious filename
			if (iBad != -1)	//newName.ReleaseBuffer(iBad);
				newName = _T("UntitledImage");

			// append the default suffix if there is one
			//if (image->GetType()) newName += theApp.GetExtFromType(image->GetType()).Mid(1,4);
		}

		if (image->GetType())
			theApp.nDocType = image->GetType();

		if (!theApp.PromptForFileName(newName, 
			bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, &theApp.nDocType))
		{
			return FALSE;       // don't even try to save
		}
	}

	BeginWaitCursor();
	if (!OnSaveDocument(newName)){
		if (pszPathName == NULL){
			// be sure to delete the file
			TRY 
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs\n");
			}
			END_CATCH_ALL
		}
		EndWaitCursor();
		return FALSE;
	}

	EndWaitCursor();
	if (bReplace) {
		// Reset the title and change the document name
		SetPathName(newName, TRUE);
		ASSERT(m_strPathName == newName); // must be set
	}
	else // SaveCopyAs
	{
		SetModifiedFlag(bModified);
	}
	return TRUE;        // success
}
//////////////////////////////////////////////////////////////////////////////
#define EPSILON (0.0000001)

int CDemoDoc::ComputePixel(float x, float y, float &x1, float &y1)
{
  double r, nn;

  if (x==0 && y==0) {
	 x1 = x;
	 y1 = y;
	 return 1;
  }

  nn = sqrt(x*x + y*y);
  r =  (fabs(x) > fabs(y)) ? fabs(nn/x): fabs(nn/y);

  x1 = (float)(r*x);
  y1 = (float)(r*y);

  return 1;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(image==0 || hThread));
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(0);
//	pCmdUI->Enable((image != NULL)); //&& theApp.GetWritableType(image->GetType()));
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnStretchMode() 
{
	stretchMode = !stretchMode;
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateStretchMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(stretchMode);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateCximageFlip(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread)
		pCmdUI->Enable(0);
}
void CDemoDoc::OnUpdateCximageGrayscale(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageMirror(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageNegative(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageResample(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotater(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotatel(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDither(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageThreshold(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplityuv(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplitrgb(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplithsl(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplityiq(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplitxyz(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSplitcmyk(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximagePseudocolors(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFiltersColorize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageLighten(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDarken(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageContrast(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageEmboss(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageBlur(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDilate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}

void CDemoDoc::OnUpdateCximageTest(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCornerDetection(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDetectBlock(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDetectDCTCodeBlock(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDetectEdgeBlock(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDetectStripe(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageDetectBlockiness(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}

void CDemoDoc::OnUpdateCximageEdge(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageErode(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSharpen(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSoften(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCrop(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->SelectionIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRemovealphachannel(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageInvetalpha(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAlphapalettetoggle(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaPaletteIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAlphastrip(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || (!image->AlphaIsValid() && !image->AlphaPaletteIsValid())) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRemovetransparency(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || image->GetTransIndex()<0) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGamma(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageMedian(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAddnoise(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCombine(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFft(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRepair(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageAlphachannelSplit(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->AlphaIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFiltersLog(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageFiltersRoot(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramEqualize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramNormalize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretch(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGaussian3x3(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGaussian5x5(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageContour(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageLesscontrast(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageJitter(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateWindowDuplicate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateFiltersMix(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformCylinder(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformPinch(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformPunch(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformSwirl(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCircletransformBathroom(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretch1(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretch2(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateFiltersNonlinearEdge(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSkew(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateJpegcompression(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateFiltersDataext(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageUnsharpmask(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageTextblur(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRedeyeremove(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->SelectionIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageBlurselborder(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->SelectionIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageSelectiveblur(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGettransparencymask(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || (image->GetTransIndex()<0 && !image->AlphaIsValid())) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsCountcolors(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateFiltersLinearCustom(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageCanvassize(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRemoveselection(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || !image->SelectionIsValid()) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsMoresaturationhsl(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsMoresaturationyuv(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsLesssaturation(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsHistogramHalfsaturation(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsHistogramFullsaturation(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretcht0(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretcht1(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageHistogramStretcht2(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateColorsAdaptivethreshold(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateViewPreviousframe(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || image->GetFrame(0)==0) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateViewNextframe(CCmdUI* pCmdUI) 
{	if(image==0 || hThread || image->GetFrame(0)==0) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateFiltersAddshadow(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}

//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateTransformEllipse(CCmdUI* pCmdUI) 
{
	if (image==NULL) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnTransformEllipse() 
{
	SubmitUndo();
	DWORD x, y;
	float x1, y1; //***bd*** use float source with GetPixelColorInterpolated
	float fx, fy, xmid, ymid, ar;
	CxImage *image2 = new CxImage(*image,false,false,true);

	xmid = (float) (image->GetWidth()/2.0);
	ymid = (float) (image->GetHeight()/2.0);
	ar = (float)(image->GetHeight())/(float)(image->GetWidth());
	for (y=0; y<image->GetHeight(); y++) {
		for (x=0; x<image->GetWidth(); x++) {
			ComputePixel(ar*(x-xmid), y-ymid, fx, fy);
			x1 = xmid+fx/ar;
			y1 = ymid+fy;
			//correct method to use would be GetAreaColorAveraged (but I guess there's not that much aliasing here)
			image2->SetPixelColor(x, y, image->GetPixelColorInterpolated(x1, y1, CxImage::IM_BILINEAR, CxImage::OM_BACKGROUND));
			//image2->SetPixelColor(x, y, image->GetPixelColor(x1, y1));
		}
	}
	delete image;
	image = image2;
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnWindowDuplicate() 
{
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 

	if (NewDoc)	{
		CxImage *newImage = new CxImage(*image);

		NewDoc->image = newImage;

		CString s;
		s.Format(_T("Copy %d of %s"),((CDemoApp*)AfxGetApp())->m_nDocCount++,GetTitle());
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	if (image==NULL) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnEditCopy() 
{
	CxImage* iSrc = image;

	//copy only the selected region box
	CxImage iSel;
	if (image->SelectionIsValid()){
		RECT r;
		image->SelectionGetBox(r);
		r.bottom = image->GetHeight() - 1 -r.bottom; 
		r.top = image->GetHeight() - 1 -r.top; 
		image->Crop(r, &iSel);
		iSrc = &iSel;
	}

	// standard DIB image
	HANDLE hDIB=iSrc->CopyToHandle();

#define USE_CF_CXIMAGE 1

#if USE_CF_CXIMAGE
	//custom CXIMAGE object
	HANDLE hMem=NULL;
	if (iSrc->IsValid() && (iSrc->AlphaIsValid() || iSrc->SelectionIsValid() || iSrc->IsTransparent())){
		hMem= GlobalAlloc(GHND, iSrc->DumpSize());
		if (hMem){
			BYTE* pDst=(BYTE*)GlobalLock(hMem);
			iSrc->Dump(pDst);
			GlobalUnlock(hMem);
		}
	}
#endif //USE_CF_CXIMAGE

	if (::OpenClipboard(AfxGetApp()->m_pMainWnd->GetSafeHwnd())) {
		if(::EmptyClipboard()) {
			if (::SetClipboardData(CF_DIB,hDIB) == NULL ) {
				AfxMessageBox( _T("Unable to set DIB clipboard data") );
			}
#if USE_CF_CXIMAGE
			if (hMem){
				UINT cf = ((CDemoApp*)AfxGetApp())->GetCF();
				if (::SetClipboardData(cf,hMem) == NULL ) {
					AfxMessageBox( _T("Unable to set CXIMAGE clipboard data") );
				}
			}
#endif //USE_CF_CXIMAGE
		}
	}
	CloseClipboard();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread) pCmdUI->Enable(0);
	else pCmdUI->Enable(m_UndoLevel>0);

	CString s;
	s.Format(_T("Undo (%d)\tCtrl+Z"),m_UndoLevel);
	pCmdUI->SetText(s);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread) pCmdUI->Enable(0);
	else pCmdUI->Enable((m_UndoLevel<(MAX_UNDO_LEVELS))&&
				   (imageUndo[m_UndoLevel]!=0));
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnEditUndo() 
{
	m_UndoLevel--;
	CxImage* tmp = image;
	image=imageUndo[m_UndoLevel];
	imageUndo[m_UndoLevel]=tmp;

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnEditRedo() 
{
	CxImage* tmp = image;
	image=imageUndo[m_UndoLevel];
	imageUndo[m_UndoLevel]=tmp;
	m_UndoLevel++;

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::SubmitUndo()
{
	if (m_UndoLevel>=MAX_UNDO_LEVELS){	// Max Undo reached
		delete imageUndo[0];			// discard the early undo
		for(int i=1;i<MAX_UNDO_LEVELS;i++){
			imageUndo[i-1]=imageUndo[i]; //shift the history
		}
		imageUndo[MAX_UNDO_LEVELS-1]=0;	// clear the undo slot
		m_UndoLevel=MAX_UNDO_LEVELS-1;  // reposition at last level
	}
	// we must clear the "redo" history when a new action is performed
	for (int i=m_UndoLevel;i<MAX_UNDO_LEVELS;i++){
		if (imageUndo[i]){
			delete imageUndo[i];
			imageUndo[i]=0;
		}
	}
	// save the actual image in the undo history
	if (image->IsValid()){
		imageUndo[m_UndoLevel] = new CxImage();
		imageUndo[m_UndoLevel]->Copy(*image);
		m_UndoLevel++;
	}
}
//////////////////////////////////////////////////////////////////////////////
void /*unsigned long _stdcall*/ RunProgressThread(void *lpParam)
{
	CDemoDoc *pDoc = (CDemoDoc *)lpParam;
	POSITION pos;
	CView *pView;
	while(pDoc->hThread){
		Sleep(333);
		if(!pDoc->image) break;
		if(pDoc->image->GetEscape()) break;
		long n=pDoc->image->GetProgress();
		pos = pDoc->GetFirstViewPosition();
		pView = pDoc->GetNextView(pos);
		if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,n,0);
	}
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,100,0);
	Sleep(111);
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_NEWIMAGE,0,0);
	pDoc->hProgress = 0;
	_endthread();
	return;
}
//////////////////////////////////////////////////////////////////////////////
void /*unsigned long _stdcall*/ RunCxImageThread(void *lpParam)
{
	CDemoDoc *pDoc = (CDemoDoc *)lpParam;
	if (pDoc==NULL) return;
	if (pDoc->image==NULL){
		pDoc->hThread=0;
		return;
	}

	 //prepare for elaboration
	pDoc->image->SetProgress(0);
	pDoc->image->SetEscape(0);

	pDoc->SubmitUndo();
	
	// auxilary thread for progress bar
	pDoc->hProgress = (HANDLE)_beginthread(RunProgressThread,0,pDoc);

	pDoc->Stopwatch(0);

	bool status = true;

	switch (pDoc->m_MenuCommand)
	{
//	case ID_FILE_OPEN:
//		status = pDoc->image->ReadFile(theApp.m_filename,theApp.m_filetype);
//		break;

	case ID_CXIMAGE_TEST:
		//pDoc->TestFunc();
		pDoc->DetectBlockiness();
		break;

	case ID_CXIMAGE_CORNER_DETECTION:
		pDoc->CornerDetection();
		break;

	case ID_CXIMAGE_DETECTBLOCK:
		pDoc->DetectBlock();
		break;
	case ID_CXIMAGE_DETECTDCTCODEBLOCK:
		pDoc->DCTCodeBlock();
		break;
	case ID_CXIMAGE_DETECTEDGEBLOCK:
		pDoc->DetectEdgeBlock();
		break;
	case ID_CXIMAGE_DTTECTSTRIPE:
		pDoc->DetectStripe();
		break;
	case ID_CXIMAGE_DTTECTBLOCKINESS:
		pDoc->DetectBlockiness();
		break;


	case ID_CXIMAGE_FLIP:
		status = pDoc->image->Flip();
		break;
	case ID_CXIMAGE_MIRROR:
		status = pDoc->image->Mirror();
		break;
	case ID_CXIMAGE_NEGATIVE:
		status = pDoc->image->Negative();
		break;
	case ID_CXIMAGE_GRAYSCALE:
		status = pDoc->image->GrayScale();
		break;
	case ID_CXIMAGE_DITHER:
		status = pDoc->image->Dither(theApp.m_Filters.DitherMethod);
		break;
	case ID_CXIMAGE_THRESHOLD:
		if (theApp.m_Filters.ThreshPreserveColors){
			RGBQUAD c = {255,255,255,0};
			status = pDoc->image->Threshold2(theApp.m_Filters.ThreshLevel,true,c,true);
		} else {
			status = pDoc->image->Threshold(theApp.m_Filters.ThreshLevel);
		}
		break;
	case ID_COLORS_ADAPTIVETHRESHOLD:
		{
			/*
			CxImage iContrastMask;
			iContrastMask.Copy(*pDoc->image,true,false,false);
			if (!iContrastMask.IsValid()) break;
			iContrastMask.GrayScale();
			long edge[]={-1,-1,-1,-1,8,-1,-1,-1,-1};
			iContrastMask.Filter(edge,3,1,0);
			long blur[]={1,1,1,1,1,1,1,1,1};
			iContrastMask.Filter(blur,3,9,0);
			status = pDoc->image->AdaptiveThreshold(0,64,&iContrastMask);
			*/
			status = pDoc->image->AdaptiveThreshold();
		}
		break;
	case ID_CXIMAGE_COLORIZE:
		switch (theApp.m_Filters.ColorMode)
		{
		case 1:
			status = pDoc->image->Colorize(theApp.m_Filters.ColorHSL.rgbRed,theApp.m_Filters.ColorHSL.rgbGreen,theApp.m_Filters.ColorHSL.rgbBlue/100.0f);
			break;
		case 2:
			status = pDoc->image->Solarize(theApp.m_Filters.ColorSolarLevel,theApp.m_Filters.ColorSolarLink!=0);
			break;
		default:
			status = pDoc->image->ShiftRGB(theApp.m_Filters.ColorRed,theApp.m_Filters.ColorGreen,theApp.m_Filters.ColorBlue);
		}
		break;
	case ID_CXIMAGE_LIGHTEN:
		status = pDoc->image->Light(10);
		break;
	case ID_CXIMAGE_DARKEN:
		status = pDoc->image->Light(-10);
		break;
	case ID_CXIMAGE_CONTRAST:
		status = pDoc->image->Light(0,10);
		break;
	case ID_CXIMAGE_LESSCONTRAST:
		status = pDoc->image->Light(0,-10);
		break;
	case ID_COLORS_MORESATURATIONHSL:
		status = pDoc->image->Saturate(25,1);
		break;
	case ID_COLORS_MORESATURATIONYUV:
		status = pDoc->image->Saturate(25,2);
		break;
	case ID_COLORS_LESSSATURATION:
		status = pDoc->image->Saturate(-20,2);
		break;
	case ID_CXIMAGE_DILATE:
		status = pDoc->image->Dilate(3);
		break;
	case ID_CXIMAGE_ERODE:
		status = pDoc->image->Erode(3);
		break;
	case ID_CXIMAGE_CONTOUR:
		status = pDoc->image->Contour();
		break;
	case ID_CXIMAGE_ADDNOISE:
		status = pDoc->image->Noise(25);
		break;
	case ID_CXIMAGE_JITTER:
		status = pDoc->image->Jitter();
		break;
	case ID_CXIMAGE_TEXTBLUR:
		status = pDoc->image->TextBlur(100,2,3,true,true);
		break;
	case ID_CXIMAGE_BLURSELBORDER:
		{
			CxImage iSel1,iSel2;
			pDoc->image->SelectionSplit(&iSel1);
			pDoc->image->SelectionSplit(&iSel2);
			iSel2.Edge();
			//iSel2.Erode();
			iSel2.Negative();
			pDoc->image->SelectionSet(iSel2);
			pDoc->image->GaussianBlur();
			pDoc->image->SelectionSet(iSel1);
			break;
		}
	case ID_CXIMAGE_SELECTIVEBLUR:
		status = pDoc->image->SelectiveBlur(1,25);
		break;
	case ID_CXIMAGE_REDEYEREMOVE:
		status = pDoc->image->RedEyeRemove();
		break;
	case ID_FILTERS_NONLINEAR_EDGE:
		status = pDoc->image->Edge();
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER:
		status = pDoc->image->CircleTransform(3,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_PINCH:
		status = pDoc->image->CircleTransform(1,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_PUNCH:
		status = pDoc->image->CircleTransform(0,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_SWIRL:
		status = pDoc->image->CircleTransform(2,0,100);
		break;
	case ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM:
		status = pDoc->image->CircleTransform(4);
		break;
	case ID_CXIMAGE_EMBOSS:
		{
		long kernel[]={0,0,-1,0,0,0,1,0,0};
		status = pDoc->image->Filter(kernel,3,-1,127);
		break;
		}
	case ID_CXIMAGE_BLUR:
		{
		long kernel[]={1,1,1,1,1,1,1,1,1};
		status = pDoc->image->Filter(kernel,3,9,0);
		break;
		}
	case ID_CXIMAGE_GAUSSIAN3X3:
		{
		//long kernel[]={1,2,1,2,4,2,1,2,1};
		//status = pDoc->image->Filter(kernel,3,16,0);
		status = pDoc->image->GaussianBlur(1.0f);
		break;
		}
	case ID_CXIMAGE_GAUSSIAN5X5:
		{
		//long kernel[]={0,1,2,1,0,1,3,4,3,1,2,4,8,4,2,1,3,4,3,1,0,1,2,1,0};
		//status = pDoc->image->Filter(kernel,5,52,0);
		status = pDoc->image->GaussianBlur(2.0f);
		break;
		}
	case ID_CXIMAGE_SOFTEN:
		{
		long kernel[]={1,1,1,1,8,1,1,1,1};
		status = pDoc->image->Filter(kernel,3,16,0);
		break;
		}
	case ID_CXIMAGE_SHARPEN:
		{
		long kernel[]={-1,-1,-1,-1,15,-1,-1,-1,-1};
		status = pDoc->image->Filter(kernel,3,7,0);
		break;
		}
	case ID_CXIMAGE_EDGE:
		{
		long kernel[]={-1,-1,-1,-1,8,-1,-1,-1,-1};
		status = pDoc->image->Filter(kernel,3,-1,255);
		break;
		}
	case ID_FILTERS_LINEAR_CUSTOM: // [Priyank Bolia]
		{
			if(theApp.m_Filters.kSize==3)
				pDoc->image->Filter(theApp.m_Filters.Kernel3x3,3,theApp.m_Filters.kDivisor,theApp.m_Filters.kBias);
			else
				pDoc->image->Filter(theApp.m_Filters.Kernel5x5,5,theApp.m_Filters.kDivisor,theApp.m_Filters.kBias);
		break;
		}
	case ID_CXIMAGE_MEDIAN:
		status = pDoc->image->Median(3);
		break;
	case ID_CXIMAGE_UNSHARPMASK:
		status = pDoc->image->UnsharpMask();
		break;
	case ID_CXIMAGE_GAMMA:
		if (theApp.m_Filters.GammaLink){
			status = pDoc->image->GammaRGB(theApp.m_Filters.GammaR,theApp.m_Filters.GammaG,theApp.m_Filters.GammaB);
		} else {
			status = pDoc->image->Gamma(theApp.m_Filters.GammaLevel);
		}
		break;
	case ID_CXIMAGE_HISTOGRAM_LOG:
		status = pDoc->image->HistogramLog();
		break;
	case ID_CXIMAGE_HISTOGRAM_ROOT:
		status = pDoc->image->HistogramRoot();
		break; 
	case ID_CXIMAGE_HISTOGRAM_EQUALIZE:
		status = pDoc->image->HistogramEqualize();
		break;
	case ID_CXIMAGE_HISTOGRAM_NORMALIZE:
		status = pDoc->image->HistogramNormalize();
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCH:
		status = pDoc->image->HistogramStretch();
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCH1:
		status = pDoc->image->HistogramStretch(1);
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCH2:
		status = pDoc->image->HistogramStretch(2);
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCHT0:
		status = pDoc->image->HistogramStretch(0,0.005f);
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCHT1:
		status = pDoc->image->HistogramStretch(1,0.005f);
		break;
	case ID_CXIMAGE_HISTOGRAM_STRETCHT2:
		status = pDoc->image->HistogramStretch(2,0.005f);
		break;
	case ID_COLORS_HISTOGRAM_FULLSATURATION:
		{
			CxImage tmp;
			tmp.Copy(*(pDoc->image),true,false,false);
			tmp.ConvertColorSpace(2,0);
			long u[256];
			long v[256];
			tmp.Histogram(0,u,v,0,0);
			int umin = 255;
			int umax = 0;
			int vmin = 255;
			int vmax = 0;
			for (int i = 0; i<255; i++){
				if (u[i]) umin = i;
				if (u[255-i]) umax = i;
				if (v[i]) vmin = i;
				if (v[255-i]) vmax = i;
			}
			float cmin = (float)min(umin,vmin);
			float cmax = (float)max(umax,vmax);
			if (cmin<128) cmin = 128.0f/(128-cmin);
			else cmin = 128.0f;
			if (cmax>128) cmax = 128.0f/(cmax-128);
			else cmax = 128.0f;
			int sat = (int)(100.0f*(min(cmin,cmax)-1.0f));
			pDoc->image->Saturate(sat,2);
		}
		break;
	case ID_COLORS_HISTOGRAM_HALFSATURATION:
		{
			CxImage tmp;
			tmp.Copy(*(pDoc->image),true,false,false);
			tmp.ConvertColorSpace(2,0);
			long u[256];
			long v[256];
			tmp.Histogram(0,u,v,0,0);
			int umin = 255;
			int umax = 0;
			int vmin = 255;
			int vmax = 0;
			for (int i = 0; i<255; i++){
				if (u[i]) umin = i;
				if (u[255-i]) umax = i;
				if (v[i]) vmin = i;
				if (v[255-i]) vmax = i;
			}
			float cmin = (float)min(umin,vmin);
			float cmax = (float)max(umax,vmax);
			if (cmin<128) cmin = 128.0f/(128-cmin);
			else cmin = 128.0f;
			if (cmax>128) cmax = 128.0f/(cmax-128);
			else cmax = 128.0f;
			int sat = (int)(50.0f*(min(cmin,cmax)-1.0f));
			pDoc->image->Saturate(sat,2);
		}
		break;
	case ID_CXIMAGE_SKEW:
		status = pDoc->image->Skew(theApp.m_Filters.SkewSlopeX,theApp.m_Filters.SkewSlopeY,
							theApp.m_Filters.SkewPivotX,theApp.m_Filters.SkewPivotY,
							theApp.m_Filters.SkewInterp!=0);
		break;
	case ID_CXIMAGE_ROTATE:
		//***bd*** more rotation options
		CxImage::InterpolationMethod intm;
		CxImage::OverflowMethod overm;
		switch (theApp.m_Filters.RotateMethod) {
		case 0: intm=CxImage::IM_NEAREST_NEIGHBOUR; break;
		case 1: intm=CxImage::IM_BILINEAR; break;
		case 2: intm=CxImage::IM_BICUBIC; break;
		case 3: intm=CxImage::IM_BICUBIC2; break;
		case 4: intm=CxImage::IM_BSPLINE; break;
		case 5: intm=CxImage::IM_LANCZOS; break;
		case 6: intm=CxImage::IM_HERMITE; break;
		default: throw(0);
		}//switch
		switch (theApp.m_Filters.RotateOverflow) {
		case 0: overm=CxImage::OM_BACKGROUND; break;
		case 1: overm=CxImage::OM_BACKGROUND; break;
		case 2: overm=CxImage::OM_BACKGROUND; break;
		case 3: overm=CxImage::OM_WRAP; break;
		case 4: overm=CxImage::OM_REPEAT; break;
		case 5: overm=CxImage::OM_MIRROR; break;
		case 6: overm=CxImage::OM_TRANSPARENT; break;
		}//switch
		switch (theApp.m_Filters.RotateOverflow) {
		case 0: {
			RGBQUAD bkg = pDoc->image->GetPixelColor(0,0);
			status = pDoc->image->Rotate2(theApp.m_Filters.RotateAngle, 0, intm, overm, &bkg,true,theApp.m_Filters.RotateKeepsize!=0);
			break; }
		case 1: {
			RGBQUAD bkg = {0,0,0,0};
			status = pDoc->image->Rotate2(theApp.m_Filters.RotateAngle, 0, intm, overm, &bkg,true,theApp.m_Filters.RotateKeepsize!=0);
			break; }
		default:
			status = pDoc->image->Rotate2(theApp.m_Filters.RotateAngle, 0, intm, overm, 0,true,theApp.m_Filters.RotateKeepsize!=0);
		}
		break;
	case ID_CXIMAGE_ROTATEL:
		status = pDoc->image->RotateLeft();
		if (status) pDoc->RegionRotateLeft();
		break;
	case ID_CXIMAGE_ROTATER:
		status = pDoc->image->RotateRight();
		if (status) pDoc->RegionRotateRight();
		break;
	case ID_CXIMAGE_RESAMPLE:
		//***bd*** more resample options
		CxImage::InterpolationMethod rintm;
		switch (theApp.m_Filters.ResampleMethod) {
		case 0: rintm=CxImage::IM_NEAREST_NEIGHBOUR; break;
		case 1: rintm=CxImage::IM_BILINEAR; break;
		case 2: rintm=CxImage::IM_BILINEAR; break;
		case 3: rintm=CxImage::IM_BICUBIC; break;
		case 4: rintm=CxImage::IM_BICUBIC2; break;
		case 5: rintm=CxImage::IM_BSPLINE; break;
		case 6: rintm=CxImage::IM_LANCZOS; break;
		case 7: rintm=CxImage::IM_HERMITE; break;
		default: throw(0);
		}//switch
		switch (theApp.m_Filters.ResampleMethod) {
		case 0:
			status = pDoc->image->Resample(theApp.m_Filters.ResampleW,theApp.m_Filters.ResampleH,1);
			break;
		case 1:
			status = pDoc->image->Resample(theApp.m_Filters.ResampleW,theApp.m_Filters.ResampleH,0);
			break;
		case 2:
			if ((long)pDoc->image->GetWidth()>theApp.m_Filters.ResampleW && (long)pDoc->image->GetHeight()>theApp.m_Filters.ResampleH)
				status = pDoc->image->QIShrink(theApp.m_Filters.ResampleW,theApp.m_Filters.ResampleH);
			else
				status = pDoc->image->Resample2(theApp.m_Filters.ResampleW,theApp.m_Filters.ResampleH,rintm,CxImage::OM_REPEAT);
			break;
		default:
			status = pDoc->image->Resample2(theApp.m_Filters.ResampleW,theApp.m_Filters.ResampleH,rintm,CxImage::OM_REPEAT);
		}
		break;
	case ID_CXIMAGE_CANVASSIZE:
		{
			RGBQUAD color = CxImage::RGBtoRGBQUAD(theApp.m_Filters.CanvasBkg);
			if (theApp.m_Filters.CanvasUseImageBkg)
				color = pDoc->image->GetTransColor();

			RECT r;
			if (theApp.m_Filters.CanvasMode == 0){
				r.top = 0;
				r.left = 0;
				r.right = theApp.m_Filters.CanvasW - pDoc->image->GetWidth();
				r.bottom = theApp.m_Filters.CanvasH - pDoc->image->GetHeight();
				if (theApp.m_Filters.CanvasCenterH){
					r.left = (theApp.m_Filters.CanvasW - pDoc->image->GetWidth()) / 2;
					r.right = theApp.m_Filters.CanvasW - pDoc->image->GetWidth() - r.left;
				}
				if (theApp.m_Filters.CanvasCenterV){
					r.top = (theApp.m_Filters.CanvasH - pDoc->image->GetHeight()) / 2;
					r.bottom = theApp.m_Filters.CanvasH - pDoc->image->GetHeight() - r.top;
				}
			} else {
				r.top = theApp.m_Filters.CanvasTop;
				r.left = theApp.m_Filters.CanvasLeft;
				r.right = theApp.m_Filters.CanvasRight;
				r.bottom = theApp.m_Filters.CanvasBottom;
			}

			status = pDoc->image->Expand(r.left, r.top,	r.right, r.bottom, color);											
		}
		break;
	case ID_CXIMAGE_INCREASEBPP:
		status = pDoc->image->IncreaseBpp(theApp.m_Filters.IncBppBPP);
		break;
	case ID_CXIMAGE_DECREASEBPP:
		{
			long bit = theApp.m_Filters.DecBppBPP;
			long method = theApp.m_Filters.DecBppPalMethod;
			bool errordiffusion = theApp.m_Filters.DecBppErrDiff!=0;
			long colors = theApp.m_Filters.DecBppMaxColors;

			//pDoc->image->IncreaseBpp(24);
			RGBQUAD c = pDoc->image->GetTransColor();

			RGBQUAD* ppal = NULL;
			if (method==1){
				switch (bit){
				/*case 1:
					{
						CQuantizer q(2,8);
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(2*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
						break;
					}*/
				case 4:
					{
						CQuantizer q(colors,8);
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(16*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
						break;
					}
				case 8:
					{
						CQuantizer q(colors,(colors>16?7:8));
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(256*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
					}
				}
				status = pDoc->image->DecreaseBpp(bit,errordiffusion,ppal,colors);
			} else status = pDoc->image->DecreaseBpp(bit,errordiffusion,0);

			if (!pDoc->image->AlphaPaletteIsValid()) pDoc->image->AlphaPaletteEnable(0);

			if (pDoc->image->IsTransparent()){
				pDoc->image->SetTransIndex(pDoc->image->GetNearestIndex(c));
			}

			if (ppal) free(ppal);
			break;
		}
	}

	pDoc->Stopwatch(1);

	pDoc->image->SetProgress(100);

	if (!status){
		CString s = pDoc->image->GetLastError();
		AfxMessageBox(s);
	}

	pDoc->hThread=0;

	_endthread();
	return ;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFlip() 
{
	m_MenuCommand=ID_CXIMAGE_FLIP;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageMirror() 
{
	m_MenuCommand=ID_CXIMAGE_MIRROR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageNegative() 
{
	m_MenuCommand=ID_CXIMAGE_NEGATIVE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGrayscale() 
{
	m_MenuCommand=ID_CXIMAGE_GRAYSCALE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDecreasebpp() 
{
	if (image==NULL) return;
	DlgDecBpp dlg;
	dlg.m_bit = theApp.m_Filters.DecBppBPP;
	dlg.m_method = theApp.m_Filters.DecBppPalMethod;
	dlg.m_errordiffusion = theApp.m_Filters.DecBppErrDiff;
	dlg.m_bLimitColors = theApp.m_Filters.DecBppLimitColors;
	dlg.m_maxcolors = theApp.m_Filters.DecBppMaxColors;

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_DECREASEBPP;
		theApp.m_Filters.DecBppBPP = dlg.m_bit;
		theApp.m_Filters.DecBppPalMethod = dlg.m_method;
		theApp.m_Filters.DecBppErrDiff = dlg.m_errordiffusion;
		theApp.m_Filters.DecBppLimitColors = dlg.m_bLimitColors;
		theApp.m_Filters.DecBppMaxColors = dlg.m_maxcolors;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageIncreasebpp() 
{
	if (image==NULL) return;
	DlgIncBpp dlg;
	dlg.m_bit = theApp.m_Filters.IncBppBPP;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_INCREASEBPP;
		theApp.m_Filters.IncBppBPP = dlg.m_bit;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRotatel() 
{
	m_MenuCommand=ID_CXIMAGE_ROTATEL;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRotater() 
{
	m_MenuCommand=ID_CXIMAGE_ROTATER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRotate() 
{
	if (image==NULL) return;
	DlgRotate dlg;
	dlg.m_angle = theApp.m_Filters.RotateAngle;
	dlg.m_method = theApp.m_Filters.RotateMethod;
	dlg.m_overflow = theApp.m_Filters.RotateOverflow;
	dlg.m_keepsize = theApp.m_Filters.RotateKeepsize;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_ROTATE;
		theApp.m_Filters.RotateAngle = dlg.m_angle;
		theApp.m_Filters.RotateMethod = dlg.m_method;
		theApp.m_Filters.RotateOverflow = dlg.m_overflow;
		theApp.m_Filters.RotateKeepsize = dlg.m_keepsize;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageResample() 
{
	if (image==NULL) return;
	
	DlgResample dlg;
	dlg.m_w = image->GetWidth();
	dlg.m_h = image->GetHeight();
	dlg.m_ratio = ((float)image->GetWidth())/((float)image->GetHeight());

	dlg.m_sizemode = theApp.m_Filters.ResampleSizemode;
	dlg.m_factor = theApp.m_Filters.ResampleFactor;
	dlg.m_newwidth = theApp.m_Filters.ResampleW;
	dlg.m_newheight = theApp.m_Filters.ResampleH;
	dlg.m_bKeepRatio = theApp.m_Filters.ResampleKeepRatio;
	dlg.m_mode = theApp.m_Filters.ResampleMethod;
	if (dlg.m_bKeepRatio) dlg.m_newheight = (DWORD)(dlg.m_newwidth/dlg.m_ratio);

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_RESAMPLE;

		if (dlg.m_sizemode==1){
			dlg.m_newwidth = (DWORD)(dlg.m_w * fabs(dlg.m_factor));
			dlg.m_newheight = (DWORD)(dlg.m_h * fabs(dlg.m_factor));
		}

		theApp.m_Filters.ResampleSizemode = dlg.m_sizemode;
		theApp.m_Filters.ResampleFactor = dlg.m_factor;
		theApp.m_Filters.ResampleW = dlg.m_newwidth;
		theApp.m_Filters.ResampleH = dlg.m_newheight;
		theApp.m_Filters.ResampleKeepRatio = dlg.m_bKeepRatio;
		theApp.m_Filters.ResampleMethod = dlg.m_mode;

		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::UpdateStatusBar()
{
	if (image){
		CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
		CString s,t;
		t = theApp.GetDescFromType(image->GetType());
		s.Format(_T("(%dx%dx%d)"),image->GetWidth(),image->GetHeight(),image->GetBpp());
		statusBar.SetPaneText(4, s);
		statusBar.SetPaneText(3,t.Mid(0,3));
		s.Format(_T("Time (s): %.3f"),m_etime);
		statusBar.SetPaneText(2, s);

//		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetProgressBar().SetPos(0);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewZoomin() 
{
	if (m_ZoomFactor>=16) return;

	if		(m_ZoomFactor == 0.50f) m_ZoomFactor = 0.75f;
	else if (m_ZoomFactor == 0.75f) m_ZoomFactor = 1.00f;
	else if (m_ZoomFactor == 1.00f)	m_ZoomFactor = 1.50f;
	else if (m_ZoomFactor == 1.50f)	m_ZoomFactor = 2.00f;
	else							m_ZoomFactor*=2;

	CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
	CString s;
	s.Format(_T("%4.0f %%"),m_ZoomFactor*100);
	statusBar.SetPaneText(2, s);

	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewZoomout() 
{
	if (m_ZoomFactor<=0.0625) return;

	if		(m_ZoomFactor == 2.00f) m_ZoomFactor = 1.50f;
	else if (m_ZoomFactor == 1.50f) m_ZoomFactor = 1.00f;
	else if (m_ZoomFactor == 1.00f)	m_ZoomFactor = 0.75f;
	else if (m_ZoomFactor == 0.75f)	m_ZoomFactor = 0.50f;
	else							m_ZoomFactor/=2;

	CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
	CString s;
	s.Format(_T("%4.1f %%"),m_ZoomFactor*100);
	statusBar.SetPaneText(2, s);

	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor>=16) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor<=0.125) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewNormalviewing11() 
{
	m_ZoomFactor=1;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewNormalviewing11(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor==1) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateCximageSettransparency(CCmdUI* pCmdUI) 
{
	if (image && hThread==0) pCmdUI->Enable(1);
	else pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRemovetransparency() 
{
	SubmitUndo();
	if (image) image->SetTransIndex(-1);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSettransparency() 
{
	m_WaitingClick=TRUE;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::Stopwatch(int start0stop1)
{
	if (start0stop1==0)	QueryPerformanceCounter(&m_swStart);
	else {
		QueryPerformanceCounter(&m_swStop);
		if (m_swFreq.LowPart==0 && m_swFreq.HighPart==0) m_etime = -1;
		else {
			m_etime = (float)(m_swStop.LowPart - m_swStart.LowPart);
			if (m_etime < 0) m_etime += 2^32;
			m_etime /= (m_swFreq.LowPart+m_swFreq.HighPart * 2^32);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageOptions() 
{
	if (image==NULL) return;
	
	DlgOptions dlg;
	dlg.m_jpeg_quality = image->GetJpegQualityF();
	dlg.m_xres = image->GetXDPI();
	dlg.m_yres = image->GetYDPI();

#if CXIMAGE_SUPPORT_TIF
	dlg.m_Opt_tif = image->GetCodecOption(CXIMAGE_FORMAT_TIF);
#endif
#if CXIMAGE_SUPPORT_GIF
	dlg.m_Opt_gif = image->GetCodecOption(CXIMAGE_FORMAT_GIF);
#endif
#if CXIMAGE_SUPPORT_JPG
	dlg.m_Opt_jpg = image->GetCodecOption(CXIMAGE_FORMAT_JPG);
#endif
#if CXIMAGE_SUPPORT_PNG
	dlg.m_Opt_png = image->GetCodecOption(CXIMAGE_FORMAT_PNG);
#endif
#if CXIMAGE_SUPPORT_RAW
	dlg.m_Opt_raw = image->GetCodecOption(CXIMAGE_FORMAT_RAW);
#endif
	
	dlg.m_exif = &m_exif;
	if (dlg.DoModal()==IDOK){
		image->SetJpegQualityF(dlg.m_jpeg_quality);
		image->SetXDPI(dlg.m_xres);
		image->SetYDPI(dlg.m_yres);

#if CXIMAGE_SUPPORT_TIF
		image->SetCodecOption(dlg.m_Opt_tif, CXIMAGE_FORMAT_TIF);
#endif
#if CXIMAGE_SUPPORT_GIF
		image->SetCodecOption(dlg.m_Opt_gif, CXIMAGE_FORMAT_GIF);
#endif
#if CXIMAGE_SUPPORT_JPG
		image->SetCodecOption(dlg.m_Opt_jpg, CXIMAGE_FORMAT_JPG);
#endif
#if CXIMAGE_SUPPORT_PNG
		image->SetCodecOption(dlg.m_Opt_png, CXIMAGE_FORMAT_PNG);
#endif
#if CXIMAGE_SUPPORT_RAW
		image->SetCodecOption(dlg.m_Opt_raw, CXIMAGE_FORMAT_RAW);
#endif

#ifdef VATI_EXTENSIONS
		theApp.m_optJpegQuality = dlg.m_jpeg_quality;
		theApp.m_optJpegOptions = dlg.m_Opt_jpg;
		theApp.m_optRawOptions  = dlg.m_Opt_raw;
#endif
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDither() 
{
	if (image==NULL) return;
	
	DlgDither dlg;
	dlg.m_method = theApp.m_Filters.DitherMethod;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_DITHER;
		theApp.m_Filters.DitherMethod = dlg.m_method;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageThreshold() 
{
	if (image==NULL) return;
	DlgThreshold dlg;

	CxImage iContrastMask;
	iContrastMask.Copy(*image,true,false,false);
	if (!iContrastMask.IsValid()){
		AfxMessageBox(_T("cannot create ContrastMask")); 
		return;
	}
	iContrastMask.GrayScale();
	long edge[]={-1,-1,-1,-1,8,-1,-1,-1,-1};
	iContrastMask.Filter(edge,3,1,0);
	long blur[]={1,1,1,1,1,1,1,1,1};
	iContrastMask.Filter(blur,3,9,0);

	if (image->IsGrayScale()){
		dlg.m_thresh1 = (long)image->OptimalThreshold(0,0);
		dlg.m_thresh2 = (long)image->OptimalThreshold(0,0,&iContrastMask);
	} else {
		CxImage iGray;
		iGray.Copy(*image,true,false,false);
		iGray.GrayScale();
		dlg.m_thresh1 = (long)iGray.OptimalThreshold(0,0);
		dlg.m_thresh2 = (long)iGray.OptimalThreshold(0,0,&iContrastMask);
	}

	dlg.m_mean = (BYTE)image->Mean();
	dlg.m_bPreserve = theApp.m_Filters.ThreshPreserveColors;
	dlg.m_level = theApp.m_Filters.ThreshLevel;

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_THRESHOLD;
		theApp.m_Filters.ThreshLevel = dlg.m_level;
		theApp.m_Filters.ThreshPreserveColors = dlg.m_bPreserve;
		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplitrgb() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);
	
	image->SplitRGB(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format(_T("Red Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format(_T("Green Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format(_T("Blue Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplityuv() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);

	image->SplitYUV(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format(_T("Y Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format(_T("U Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format(_T("V Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplithsl() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);

	image->SplitHSL(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();
	
	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format(_T("Hue Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format(_T("Saturation Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format(_T("Lightness Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplitcmyk() 
{
	if (image==NULL) return;

	CxImage *newc = new CxImage();
	CxImage *newm = new CxImage();
	CxImage *newy = new CxImage();
	CxImage *newk = new CxImage();

	Stopwatch(0);
	
	image->SplitCMYK(newc,newm,newy,newk);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newc;
		CString s;
		s.Format(_T("C Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newm;
		CString s;
		s.Format(_T("M Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newy;
		CString s;
		s.Format(_T("Y Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDock=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDock)	{
		NewDock->image = newk;
		CString s;
		s.Format(_T("K Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDock->SetTitle(s);
		NewDock->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximagePseudocolors() 
{
	if (image==NULL) return;
	
	SubmitUndo();

	if (!image->IsGrayScale()) image->GrayScale();
	image->HuePalette();

/*	POSITION pos = GetFirstViewPosition();
	CDemoView* pView = (CDemoView*)GetNextView(pos);
	HDC srcDC = ::GetDC(pView->GetSafeHwnd());
	HDC memDC = ::CreateCompatibleDC(srcDC);
	// copy the screen to the bitmap
	CSize sz(image->GetWidth(), image->GetHeight());
	int xshift = 0, yshift = 0;
	HBITMAP bm =::CreateCompatibleBitmap(srcDC, sz.cx, sz.cy);
	HBITMAP oldbm = (HBITMAP)::SelectObject(memDC,bm);
	::BitBlt(memDC, 0, 0, sz.cx, sz.cy, srcDC, xshift, yshift, SRCCOPY);
//	image->SetTransIndex(-1);
//	image->Draw(memDC);
	::TextOut(memDC,10,10,_T("test"),4);
	
	CxImage newima;
	newima.CreateFromHBITMAP(bm);
	image->Transfer(newima);
	// free objects
	SelectObject(memDC,oldbm);    
	DeleteObject(memDC);*/

	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFiltersColorize() 
{
	if (image==NULL) return;
	DlgColorize dlg;

	dlg.m_bHSL = theApp.m_Filters.ColorMode;
	dlg.m_blend = theApp.m_Filters.ColorHSL.rgbBlue;
	dlg.m_sat = theApp.m_Filters.ColorHSL.rgbGreen;
	dlg.m_hue = theApp.m_Filters.ColorHSL.rgbRed;
	dlg.m_b = theApp.m_Filters.ColorBlue;
	dlg.m_g = theApp.m_Filters.ColorGreen;
	dlg.m_r = theApp.m_Filters.ColorRed;
	dlg.m_sol = theApp.m_Filters.ColorSolarLevel;
	dlg.m_bLinked = theApp.m_Filters.ColorSolarLink;

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_COLORIZE;

		theApp.m_Filters.ColorMode = dlg.m_bHSL;
		theApp.m_Filters.ColorHSL.rgbBlue = dlg.m_blend;
		theApp.m_Filters.ColorHSL.rgbGreen = dlg.m_sat;
		theApp.m_Filters.ColorHSL.rgbRed = dlg.m_hue;
		theApp.m_Filters.ColorBlue = dlg.m_b;
		theApp.m_Filters.ColorGreen = dlg.m_g;
		theApp.m_Filters.ColorRed = dlg.m_r;
		theApp.m_Filters.ColorSolarLevel = dlg.m_sol;
		theApp.m_Filters.ColorSolarLink = dlg.m_bLinked;

		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDarken() 
{
	m_MenuCommand=ID_CXIMAGE_DARKEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageLighten() 
{
	m_MenuCommand=ID_CXIMAGE_LIGHTEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageContrast() 
{
	m_MenuCommand=ID_CXIMAGE_CONTRAST;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageEmboss() 
{
	m_MenuCommand=ID_CXIMAGE_EMBOSS;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageBlur() 
{
	m_MenuCommand=ID_CXIMAGE_BLUR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageDilate() 
{
	m_MenuCommand=ID_CXIMAGE_DILATE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageTest() 
{
	m_MenuCommand=ID_CXIMAGE_TEST;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}

//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCornerDetection() 
{
	m_MenuCommand=ID_CXIMAGE_CORNER_DETECTION;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}

void CDemoDoc::OnCximageDetectBlock() 
{
	m_MenuCommand=ID_CXIMAGE_DETECTBLOCK;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}

void CDemoDoc::OnCximageDetectDCTCodeBlock() 
{
	m_MenuCommand=ID_CXIMAGE_DETECTDCTCODEBLOCK;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}

void CDemoDoc::OnCximageDetectEdgeBlock() 
{
	m_MenuCommand= ID_CXIMAGE_DETECTEDGEBLOCK;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}


void CDemoDoc::OnCximageDetectStripe() 
{
	m_MenuCommand= ID_CXIMAGE_DTTECTSTRIPE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
void CDemoDoc::OnCximageDetectBlockiness() 
{
	m_MenuCommand= ID_CXIMAGE_DTTECTBLOCKINESS;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageEdge() 
{
	m_MenuCommand=ID_CXIMAGE_EDGE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageErode() 
{
	m_MenuCommand=ID_CXIMAGE_ERODE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSharpen() 
{
	m_MenuCommand=ID_CXIMAGE_SHARPEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSoften() 
{
	m_MenuCommand=ID_CXIMAGE_SOFTEN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCrop() 
{
	SubmitUndo();
	RECT r;
	
#ifdef VATI_EXTENSIONS
	// if there is a valid rectangle selection, then call the CropRotatedRectangle instead original Crop
	if (m_isRectSel && m_NumSel==5 )
	{
		CPoint top;
		long height, width;
		float angle;
		int topcorner = -1;

		// get upperleft corner
		top.x = 999999;
		top.y = 999999;
		for(int i=0; i<4; i++)
		{
			if ( top.y >= m_Sel[i].y )
			{
				if ( top.y == m_Sel[i].y && top.x < m_Sel[i].x )
					continue;
				top.x = m_Sel[i].x;
				top.y = m_Sel[i].y;
				topcorner = i;
			}
		}
		// get side lengths (-1st and +1st indexes points to 2 sides)
		if ( topcorner > 0 && topcorner < 4 )
			height = (long)LEN2D( top.x - m_Sel[topcorner-1].x, top.y - m_Sel[topcorner-1].y );
		else if ( topcorner == 0 )
			height = (long)LEN2D( top.x - m_Sel[3].x, top.y - m_Sel[3].y );
		else
			return;	// fatal prog error

		width  = (long)LEN2D( top.x - m_Sel[topcorner+1].x, top.y - m_Sel[topcorner+1].y );
		angle = (float)atan2( (float)(m_Sel[topcorner+1].y - top.y), (float)(m_Sel[topcorner+1].x - top.x) );

		image->CropRotatedRectangle( top.x, top.y, width, height, angle );
	}
		
	else // freehand selection
	{
		image->SelectionGetBox(r);
		r.bottom = image->GetHeight() - 1 -r.bottom; 
		r.top = image->GetHeight() - 1 -r.top; 
		image->Crop(r);
	}
#else
	image->SelectionGetBox(r);
	r.bottom = image->GetHeight() - 1 -r.bottom; 
	r.top = image->GetHeight() - 1 -r.top; 
	image->Crop(r);
#endif	
	UpdateStatusBar(); // VAti - to refresh image size in the status bar
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}

//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRemovealphachannel() 
{
	SubmitUndo();
	image->AlphaDelete();
	image->AlphaSetMax(255);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageOpacity() 
{
	if (image==NULL) return;
	DlgOpacity dlg;
	dlg.m_level=image->AlphaGetMax();
	if (dlg.DoModal()==IDOK){
		SubmitUndo();
		if (!image->AlphaIsValid()){
			image->AlphaCreate();
		}
		image->AlphaSetMax(dlg.m_level);
	}
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageInvetalpha() 
{
	SubmitUndo();
	image->AlphaInvert();
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphapalettetoggle() 
{
	SubmitUndo();
	image->AlphaPaletteEnable(!image->AlphaPaletteIsEnabled());
	UpdateAllViews(NULL);	
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphastrip() 
{
	SubmitUndo();
	SetCursor(LoadCursor(0,IDC_WAIT));
	Stopwatch(0);

	RGBQUAD c={255,255,255,0};
	image->SetTransColor(c);
	image->AlphaStrip();

	Stopwatch(1);
	SetCursor(LoadCursor(0,IDC_ARROW));
	UpdateStatusBar();
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);	
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGamma() 
{
	if (image==NULL) return;
	DlgGamma dlg;
	dlg.m_gamma = theApp.m_Filters.GammaLevel;
	dlg.m_gammaR = theApp.m_Filters.GammaR;
	dlg.m_gammaG = theApp.m_Filters.GammaG;
	dlg.m_gammaB = theApp.m_Filters.GammaB;
	dlg.m_bGammaMode = theApp.m_Filters.GammaLink;

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_GAMMA;
		theApp.m_Filters.GammaLevel = dlg.m_gamma;
		theApp.m_Filters.GammaR = dlg.m_gammaR;
		theApp.m_Filters.GammaG = dlg.m_gammaG;
		theApp.m_Filters.GammaB = dlg.m_gammaB;
		theApp.m_Filters.GammaLink = dlg.m_bGammaMode;

		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageMedian() 
{
	m_MenuCommand=ID_CXIMAGE_MEDIAN;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAddnoise() 
{
	m_MenuCommand=ID_CXIMAGE_ADDNOISE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsMove() 
{
	m_tool=0;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsMove(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsSelect() 
{
	m_tool=1;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==1);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsZoom() 
{
	m_tool=2;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsZoom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==2);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsText() 
{
	if (image==NULL) return;
	DlgText dlg;

#ifndef VATI_EXTENSIONS
	memcpy(&(dlg.m_font),&m_font,sizeof(m_font));
	dlg.m_text=m_text;
	dlg.m_color=m_color;
	if (dlg.DoModal()==IDOK){
		m_text=dlg.m_text;
		m_color=dlg.m_color;
		memcpy(&m_font,&(dlg.m_font),sizeof(m_font));
		m_tool=3;
	}
#else
    //pass all data about text
    memcpy( &(dlg.m_textdata), &theApp.m_text, sizeof(CxImage::CXTEXTINFO) );
    if (dlg.DoModal()==IDOK)
    {
        //retrieve all data about text
		memcpy( &theApp.m_text, &(dlg.m_textdata), sizeof(CxImage::CXTEXTINFO) );
		m_tool=3;
	}
#endif
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsText(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==3);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewPalette(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread || image->GetNumColors()==0) pCmdUI->Enable(0);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewPalette() 
{
	if (image==NULL) return;
	DlgPalette dlg;
	dlg.m_numcolors=image->GetNumColors();
	memcpy(dlg.m_pal,image->GetPalette(),dlg.m_numcolors*sizeof(RGBQUAD));
	if (dlg.DoModal()==IDOK){
		if (dlg.m_changed){
			SubmitUndo();
			switch (dlg.m_replace){
			case 1:
				{
					image->SetPalette(dlg.m_pal,dlg.m_numcolors);
					break;
				}
			case 2:
				{
					int bpp=image->GetBpp();
					image->IncreaseBpp(24);
					image->DecreaseBpp(bpp,false,dlg.m_pal);
					break;
				}
			case 3:
				{
					int bpp=image->GetBpp();
					image->IncreaseBpp(24);
					image->DecreaseBpp(bpp,true,dlg.m_pal);
					break;
				}
			}

			UpdateAllViews(NULL,WM_USER_NEWIMAGE);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCombine() 
{
	if (image==NULL) return;
	DlgCombine dlg;
	if (dlg.DoModal()==IDOK){
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);
		CxImage *newr,*newg,*newb,*newa;
		newr=newg=newb=newa=NULL;

		newr = new CxImage();
		switch(dlg.pChR){
		case 0:
			newr->Copy(*(dlg.pDocR->GetImage()),1,0,0);
			newr->GrayScale();
			break;
		case 1:
			dlg.pDocR->GetImage()->SplitRGB(newr,0,0);
			break;
		case 2:
			dlg.pDocR->GetImage()->SplitRGB(0,newr,0);
			break;
		case 3:
			dlg.pDocR->GetImage()->SplitRGB(0,0,newr);
			break;
		}

		newg = new CxImage();
		switch(dlg.pChG){
		case 0:
			newg->Copy(*(dlg.pDocG->GetImage()),1,0,0);
			newg->GrayScale();
			break;
		case 1:
			dlg.pDocG->GetImage()->SplitRGB(newg,0,0);
			break;
		case 2:
			dlg.pDocG->GetImage()->SplitRGB(0,newg,0);
			break;
		case 3:
			dlg.pDocG->GetImage()->SplitRGB(0,0,newg);
			break;
		}

		newb = new CxImage();
		switch(dlg.pChB){
		case 0:
			newb->Copy(*(dlg.pDocB->GetImage()),1,0,0);
			newb->GrayScale();
			break;
		case 1:
			dlg.pDocB->GetImage()->SplitRGB(newb,0,0);
			break;
		case 2:
			dlg.pDocB->GetImage()->SplitRGB(0,newb,0);
			break;
		case 3:
			dlg.pDocB->GetImage()->SplitRGB(0,0,newb);
			break;
		}

		if (dlg.pDocA){
			newa = new CxImage();
			switch(dlg.pChA){
			case 0:
				newa->Copy(*(dlg.pDocA->GetImage()),1,0,0);
				newa->GrayScale();
				break;
			case 1:
				dlg.pDocA->GetImage()->SplitRGB(newa,0,0);
				break;
			case 2:
				dlg.pDocA->GetImage()->SplitRGB(0,newa,0);
				break;
			case 3:
				dlg.pDocA->GetImage()->SplitRGB(0,0,newa);
				break;
			}
		}

		CxImage *mix = new CxImage();
		mix->Combine(newr,newg,newb,newa,dlg.pChS);
		
		CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDocr)	{
			NewDocr->image = mix;
			CString s;
			s.Format(_T("NewImage%d"),((CDemoApp*)AfxGetApp())->m_nDocCount++);
			NewDocr->SetTitle(s);
			NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		delete newr;
		delete newg;
		delete newb;
		delete newa;
		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFft() 
{
	if (image==NULL) return;
	DlgFFT dlg;
	if (dlg.DoModal()==IDOK){
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		CxImage *srcr,*srci,*dstr,*dsti,tmp;

		srcr = (dlg.pDocReal) ? dlg.pDocReal->GetImage() : 0;
		srci = (dlg.pDocImag) ? dlg.pDocImag->GetImage() : 0;

		if (srcr==0 && srci==0) return;

		if (srcr) dstr = new CxImage(*srcr,true,false,false); else dstr=0;
		if (srci) dsti = new CxImage(*srci,true,false,false); else dsti=0;

		if (dstr==0){
			dstr = new CxImage(dsti->GetWidth(),dsti->GetHeight(),8);
			dstr->Clear(0);
			dstr->SetGrayPalette();
		}
		if (dsti==0){
			dsti = new CxImage(dstr->GetWidth(),dstr->GetHeight(),8);
			dsti->Clear(0);
			dsti->SetGrayPalette();
		}

		tmp.FFT2(dstr,dsti,0,0,dlg.bInverse,dlg.bForceFFT!=0,dlg.bMagnitude!=0);

		((CDemoApp*)AfxGetApp())->m_nDocCount++;
		CDemoDoc *NewDoci=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDoci)	{
			NewDoci->image = dsti;
			CString s;
			if (dlg.bMagnitude){
				s.Format(_T("FFT Phase %d"),((CDemoApp*)AfxGetApp())->m_nDocCount);
			} else {
				s.Format(_T("FFT Imag %d"),((CDemoApp*)AfxGetApp())->m_nDocCount);
			}
			NewDoci->SetTitle(s);
			NewDoci->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}
		CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDocr)	{
			NewDocr->image = dstr;
			CString s;
			if (dlg.bMagnitude){
				s.Format(_T("FFT Magnitude %d"),((CDemoApp*)AfxGetApp())->m_nDocCount);
			} else {
				s.Format(_T("FFT Real %d"),((CDemoApp*)AfxGetApp())->m_nDocCount);
			}
			NewDocr->SetTitle(s);
			NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplityiq() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);

	image->SplitYIQ(newr,newg,newb);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format(_T("Y Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format(_T("I Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format(_T("Q Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSplitxyz() 
{
	if (image==NULL) return;

	CxImage *newr = new CxImage();
	CxImage *newg = new CxImage();
	CxImage *newb = new CxImage();

	Stopwatch(0);
	
	image->SplitXYZ(newr,newg,newb);
	
	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newr;
		CString s;
		s.Format(_T("X Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocg=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocg)	{
		NewDocg->image = newg;
		CString s;
		s.Format(_T("Y Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocg->SetTitle(s);
		NewDocg->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
	CDemoDoc *NewDocb=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocb)	{
		NewDocb->image = newb;
		CString s;
		s.Format(_T("Z Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocb->SetTitle(s);
		NewDocb->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRepair() 
{
	if (image==NULL) return;
	
	DlgRepair dlg;
	dlg.m_iterations = 2;
	dlg.m_radius = (float)0.25;
	if (dlg.DoModal()==IDOK){
		SubmitUndo();
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		image->Repair(dlg.m_radius,dlg.m_iterations,dlg.m_ncs);

		Stopwatch(1);
		UpdateAllViews(NULL);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphachannelSplit() 
{
	if (image==NULL) return;

	CxImage *newa = new CxImage();

	Stopwatch(0);
	
	image->AlphaSplit(newa);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newa;
		CString s;
		s.Format(_T("Alpha Channel %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageAlphaCreate() 
{
	if (image==NULL) return;
	CxImage gray(*image,true,false,false);
	gray.IncreaseBpp(8);
	gray.Negative();
	gray.GrayScale();
	image->AlphaSet(gray);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFiltersLog() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_LOG;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageFiltersRoot() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_ROOT;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramEqualize() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_EQUALIZE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramNormalize() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_NORMALIZE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretch() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCH;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGaussian3x3() 
{
	m_MenuCommand=ID_CXIMAGE_GAUSSIAN3X3;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGaussian5x5() 
{
	m_MenuCommand=ID_CXIMAGE_GAUSSIAN5X5;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageContour() 
{
	m_MenuCommand=ID_CXIMAGE_CONTOUR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageLesscontrast() 
{
	m_MenuCommand=ID_CXIMAGE_LESSCONTRAST;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageJitter() 
{
	m_MenuCommand=ID_CXIMAGE_JITTER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnFiltersMix() 
{
	if (image==NULL) return;
	DlgMix dlg;
	if (dlg.DoModal()==IDOK){
		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		CxImage *src, *dst, *tmp;

		src = (dlg.pDocSrc) ? dlg.pDocSrc->GetImage() : 0;
		dst = (dlg.pDocDst) ? dlg.pDocDst->GetImage() : 0;

		if (src==0 && dst==0) return;

		tmp = new CxImage(*dst);
		tmp->Mix(*src,(CxImage::ImageOpType)dlg.OpType,dlg.m_xoffset,dlg.m_yoffset,dlg.m_mixalpha!=0);

		((CDemoApp*)AfxGetApp())->m_nDocCount++;
		CDemoDoc *NewDoci=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDoci)	{
			NewDoci->image = tmp;
			CString s;
			s.Format(_T("Mix %d"),((CDemoApp*)AfxGetApp())->m_nDocCount);
			NewDoci->SetTitle(s);
			NewDoci->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformCylinder() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_CYLINDER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformPinch() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_PINCH;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformPunch() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_PUNCH;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformSwirl() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_SWIRL;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCircletransformBathroom() 
{
	m_MenuCommand=ID_CXIMAGE_CIRCLETRANSFORM_BATHROOM;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretch1() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCH1;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretch2() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCH2;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnFiltersNonlinearEdge() 
{
	m_MenuCommand=ID_FILTERS_NONLINEAR_EDGE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageSkew() 
{
	if (image==NULL) return;
	
	DlgSkew dlg;
	dlg.m_w = image->GetWidth();
	dlg.m_h = image->GetHeight();

	dlg.m_skewx = theApp.m_Filters.SkewX;
	dlg.m_skewy = theApp.m_Filters.SkewY;
	dlg.m_pivotx = theApp.m_Filters.SkewPivotX;
	dlg.m_pivoty = theApp.m_Filters.SkewPivotY;
	dlg.m_bEnableInterpolation = theApp.m_Filters.SkewInterp;

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_SKEW;

		theApp.m_Filters.SkewX = dlg.m_skewx;
		theApp.m_Filters.SkewY = dlg.m_skewy;
		theApp.m_Filters.SkewSlopeX = dlg.m_slopex;
		theApp.m_Filters.SkewSlopeY = dlg.m_slopey;
		theApp.m_Filters.SkewPivotX = dlg.m_pivotx;
		theApp.m_Filters.SkewPivotY = dlg.m_pivoty;
		theApp.m_Filters.SkewInterp = dlg.m_bEnableInterpolation;

		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsTracker(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==4);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsTracker() 
{
	m_tool=4;
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnJpegcompression() 
{
	if (image==NULL) return;
	DlgJpeg dlg;
	dlg.m_quality=50.0f;
	if (dlg.DoModal()==IDOK){

		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		CxImage *tmp;
		tmp = new CxImage(*image);
		if (!tmp->IsGrayScale()) tmp->IncreaseBpp(24);
		tmp->SetTransIndex(-1);
		tmp->SetJpegQualityF(dlg.m_quality);

		DWORD imagetype = 0;
#if CXIMAGE_SUPPORT_JPG
		if (dlg.m_format==0) imagetype = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_JPC
		if (dlg.m_format==1) imagetype = CXIMAGE_FORMAT_JPC;
#endif

		CxMemFile tmpFile;
		tmpFile.Open();

		if (tmp->Encode(&tmpFile,imagetype)){

			tmpFile.Seek(0,SEEK_SET);
			if (tmp->Decode(&tmpFile,imagetype)){

				((CDemoApp*)AfxGetApp())->m_nDocCount++;
				CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
				if (NewDoc)	{
					NewDoc->image = tmp;
					CString s;
					s.Format(_T("Jpeg compr. %d, q = %.3f, size = %d"),
							((CDemoApp*)AfxGetApp())->m_nDocCount, (double)dlg.m_quality, tmpFile.Size());
					NewDoc->SetTitle(s);
					NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
				}
			} else {
				CString s = tmp->GetLastError();
				AfxMessageBox(s);
				delete tmp;
			}
		} else {
			CString s = tmp->GetLastError();
			AfxMessageBox(s);
			delete tmp;
		}

		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewSmooth() 
{
	m_bSmoothDisplay = !m_bSmoothDisplay;
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewSmooth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bSmoothDisplay);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnFiltersDataext() 
{
	if (image==NULL) return;
	DlgDataExt dlg;

	dlg.m_image = image;

	dlg.m_Ymin = dlgDataExtInfos.fYmin;
	dlg.m_Ymax = dlgDataExtInfos.fYmax;
	dlg.m_Xmin = dlgDataExtInfos.fXmin;
	dlg.m_Xmax = dlgDataExtInfos.fXmax;
	dlg.m_thresh = dlgDataExtInfos.nThresh;
	dlg.m_color = dlgDataExtInfos.cColor;
	dlg.m_bMinmax = dlgDataExtInfos.bMinmax;
	dlg.m_bAvg = dlgDataExtInfos.bAvg;
	dlg.m_bDetect = dlgDataExtInfos.bDetect;
	dlg.m_bLogXaxis = dlgDataExtInfos.bLogXaxis;
	dlg.m_bLogYaxis = dlgDataExtInfos.bLogYaxis;


	if (dlg.DoModal()==IDOK){
		dlgDataExtInfos.fYmin = dlg.m_Ymin;
		dlgDataExtInfos.fYmax = dlg.m_Ymax;
		dlgDataExtInfos.fXmin = dlg.m_Xmin;
		dlgDataExtInfos.fXmax = dlg.m_Xmax ;
		dlgDataExtInfos.nThresh = dlg.m_thresh;
		dlgDataExtInfos.cColor = dlg.m_color;
		dlgDataExtInfos.bMinmax = dlg.m_bMinmax;
		dlgDataExtInfos.bAvg = dlg.m_bAvg;
		dlgDataExtInfos.bDetect = dlg.m_bDetect;
		dlgDataExtInfos.bLogXaxis = dlg.m_bLogXaxis;
		dlgDataExtInfos.bLogYaxis = dlg.m_bLogYaxis;
	}

}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageUnsharpmask() 
{
	m_MenuCommand=ID_CXIMAGE_UNSHARPMASK;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::RegionRotateLeft()
{
	long i,n;
	long h=image->GetHeight();
	for(i=0;i<m_NumSel;i++){
		n = m_Sel[i].x;
		m_Sel[i].x = m_Sel[i].y;
		m_Sel[i].y = h-1-n;
	}

}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::RegionRotateRight()
{
	long i,n;
	long w=image->GetWidth();
	for(i=0;i<m_NumSel;i++){
		n = m_Sel[i].y;
		m_Sel[i].y = m_Sel[i].x;
		m_Sel[i].x = w-1-n;
	}

}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageTextblur() 
{
	m_MenuCommand=ID_CXIMAGE_TEXTBLUR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRedeyeremove() 
{
	m_MenuCommand=ID_CXIMAGE_REDEYEREMOVE;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageBlurselborder() 
{
	m_MenuCommand=ID_CXIMAGE_BLURSELBORDER;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////

void CDemoDoc::OnCximageSelectiveblur() 
{
	m_MenuCommand=ID_CXIMAGE_SELECTIVEBLUR;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
/*void CDemoDoc::OnFiltersSka280x350() 
{
	if (image==NULL) return;

	SubmitUndo();

	image->IncreaseBpp(24);

	if (image->GetWidth()<280 && image->GetHeight()<350){
		image->Resample2((image->GetWidth()*350)/image->GetHeight(),350);
	}

	RGBQUAD canvas = {0,0,0,0};
	image->Thumbnail(280,350,canvas);

	long colors=232;
	RGBQUAD* ppal = NULL;
	CQuantizer q(colors,(colors>16?7:8));
	q.ProcessImage(image->GetDIB());
	ppal=(RGBQUAD*)calloc(256*sizeof(RGBQUAD),1);
	q.SetColorTable(ppal);

	int idx=0;
	for(; colors>0;colors--){
		ppal[colors+23]=ppal[colors];
		idx++;
	}

	const BYTE data[96] = {
			0x00,0x00,0x00,0x00,
			0xA8,0x00,0x00,0x00,
			0x00,0xA8,0x00,0x00,
			0xA8,0xA8,0x00,0x00,
			0x00,0x00,0xA8,0x00,
			0xA8,0x00,0xA8,0x00,
			0x00,0x54,0xA8,0x00,
			0xA8,0xA8,0xA8,0x00,
			0x54,0x54,0x54,0x00,
			0xFF,0x54,0x54,0x00,
			0x54,0xFF,0x54,0x00,
			0xFF,0xFF,0x54,0x00,
			0x54,0x54,0xFF,0x00,
			0xFF,0x54,0xFF,0x00,
			0x54,0xFF,0xFF,0x00,
			0xFF,0xFF,0xFF,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00
	};
	memcpy(ppal,data,96);

	image->DecreaseBpp(8,1,ppal,256);

	free(ppal);
	
	image->SetType(CXIMAGE_FORMAT_SKA);

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}*/
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageGettransparencymask() 
{
	if (image==NULL) return;

	CxImage *newa = new CxImage();

	Stopwatch(0);

	image->GetTransparentMask(newa);

	Stopwatch(1);
	UpdateStatusBar();

	((CDemoApp*)AfxGetApp())->m_nDocCount++;
	CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDocr)	{
		NewDocr->image = newa;
		CString s;
		s.Format(_T("Transparency mask %d from %s"),((CDemoApp*)AfxGetApp())->m_nDocCount,GetTitle());
		NewDocr->SetTitle(s);
		NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsCountcolors() 
{
	if (image==NULL) return;

	SetCursor(LoadCursor(0,IDC_WAIT));
	Stopwatch(0);

	CQuantizer q(16777216,8);
	q.ProcessImage(image->GetDIB());

	Stopwatch(1);
	UpdateStatusBar();
	SetCursor(LoadCursor(0,IDC_ARROW));

	CString s;
	s.Format(_T("The number of colors in the active image is: %d"), q.GetColorCount());
	AfxMessageBox(s);

}
//////////////////////////////////////////////////////////////////////////////

void CDemoDoc::OnFiltersLinearCustom() 
{
	// <Priyank Bolia> priyank_bolia@yahoo.com
	// TODO: Add your command handler code here
	if (image==NULL) return;
	DlgCustomFilter dlg;

	memcpy(dlg.dlgkernel,theApp.m_Filters.Kernel5x5,25*sizeof(long));
	dlg.m_kSize = theApp.m_Filters.kSize;
	dlg.m_EditBias = theApp.m_Filters.kBias;
	dlg.m_EditDivisor = theApp.m_Filters.kDivisor;

	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_FILTERS_LINEAR_CUSTOM;

		theApp.m_Filters.kDivisor = dlg.m_EditDivisor;
		theApp.m_Filters.kBias = dlg.m_EditBias;
		theApp.m_Filters.kSize = dlg.m_kSize;

		memcpy(theApp.m_Filters.Kernel5x5,dlg.dlgkernel,25*sizeof(long));

		theApp.m_Filters.Kernel3x3[0]=(long)dlg.dlgkernel[6];
		theApp.m_Filters.Kernel3x3[1]=(long)dlg.dlgkernel[7];
		theApp.m_Filters.Kernel3x3[2]=(long)dlg.dlgkernel[8];

		theApp.m_Filters.Kernel3x3[3]=(long)dlg.dlgkernel[11];
		theApp.m_Filters.Kernel3x3[4]=(long)dlg.dlgkernel[12];
		theApp.m_Filters.Kernel3x3[5]=(long)dlg.dlgkernel[13];

		theApp.m_Filters.Kernel3x3[6]=(long)dlg.dlgkernel[16];
		theApp.m_Filters.Kernel3x3[7]=(long)dlg.dlgkernel[17];
		theApp.m_Filters.Kernel3x3[8]=(long)dlg.dlgkernel[18];

		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageCanvassize() 
{
	if (image==NULL) return;
	DlgExpand dlg;

	dlg.m_Mode = theApp.m_Filters.CanvasMode;
	dlg.m_CenterH = theApp.m_Filters.CanvasCenterH;
	dlg.m_CenterV = theApp.m_Filters.CanvasCenterV;
	dlg.m_KeepRatio = theApp.m_Filters.CanvasKeepRatio;
	dlg.m_UseImageBkg = theApp.m_Filters.CanvasUseImageBkg;
	dlg.m_color = theApp.m_Filters.CanvasBkg;
	dlg.m_newwidth = theApp.m_Filters.CanvasW;
	dlg.m_newheight = theApp.m_Filters.CanvasH;
	dlg.m_left = theApp.m_Filters.CanvasLeft;
	dlg.m_right = theApp.m_Filters.CanvasRight;
	dlg.m_top = theApp.m_Filters.CanvasTop;
	dlg.m_bottom = theApp.m_Filters.CanvasBottom;

	if (dlg.m_newwidth < (long)image->GetWidth()) dlg.m_newwidth = (long)image->GetWidth();
	if (dlg.m_newheight < (long)image->GetHeight()) dlg.m_newheight = (long)image->GetHeight();

	dlg.m_ratio = ((float)image->GetWidth())/((float)image->GetHeight());

	if (dlg.DoModal()==IDOK){

		m_MenuCommand=ID_CXIMAGE_CANVASSIZE;

		theApp.m_Filters.CanvasMode = dlg.m_Mode;
		theApp.m_Filters.CanvasCenterH = dlg.m_CenterH;
		theApp.m_Filters.CanvasCenterV = dlg.m_CenterV;
		theApp.m_Filters.CanvasKeepRatio = dlg.m_KeepRatio;
		theApp.m_Filters.CanvasUseImageBkg = dlg.m_UseImageBkg;
		theApp.m_Filters.CanvasBkg = dlg.m_color;
		theApp.m_Filters.CanvasW = dlg.m_newwidth;
		theApp.m_Filters.CanvasH = dlg.m_newheight;
		theApp.m_Filters.CanvasLeft = dlg.m_left;
		theApp.m_Filters.CanvasRight = dlg.m_right;
		theApp.m_Filters.CanvasTop = dlg.m_top;
		theApp.m_Filters.CanvasBottom = dlg.m_bottom;

		if (dlg.m_Mode == 0 && ((dlg.m_newwidth < (long)image->GetWidth()) || (dlg.m_newheight < (long)image->GetHeight()))){
			AfxMessageBox(_T("New canvas size must be greater than the original"));
			return;
		}
		if (dlg.m_Mode == 1 && (dlg.m_left<0 || dlg.m_right<0 || dlg.m_top<0 || dlg.m_bottom<0)){
			AfxMessageBox(_T("New canvas size must be greater than the original"));
			return;
		}

		hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
	}

}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewToolsFloodfill(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_tool==5);
	DlgFloodFill* pDlg = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->m_pDlgFlood;
	if (pDlg && pDlg->GetSafeHwnd() && m_tool!=5){
		pDlg->ShowWindow(SW_HIDE);
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewToolsFloodfill() 
{
	m_tool=5;
	DlgFloodFill* pDlg = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->m_pDlgFlood;
	if (pDlg){
		if (pDlg->GetSafeHwnd()==0){
			pDlg->m_color = RGB(theApp.m_FloodColor.rgbRed, theApp.m_FloodColor.rgbGreen, theApp.m_FloodColor.rgbBlue);
			pDlg->m_tol = theApp.m_FloodTolerance;
			pDlg->m_opacity = theApp.m_FloodOpacity;
			pDlg->m_select = theApp.m_FloodSelect;
			pDlg->Create();
		} else {
			pDlg->ShowWindow(SW_SHOW);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageRemoveselection() 
{
	if (image==NULL) return;
	image->SelectionDelete();

	POSITION pos = GetFirstViewPosition();
	CDemoView *pView = (CDemoView *)GetNextView(pos);
	if (pView) pView->KillTimer(1);
	pView->m_SelShift=0;
	m_NumSel=0;

	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsMoresaturationhsl() 
{
	m_MenuCommand=ID_COLORS_MORESATURATIONHSL;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsMoresaturationyuv() 
{
	m_MenuCommand=ID_COLORS_MORESATURATIONYUV;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsLesssaturation() 
{
	m_MenuCommand=ID_COLORS_LESSSATURATION;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsHistogramFullsaturation() 
{
	m_MenuCommand=ID_COLORS_HISTOGRAM_FULLSATURATION;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsHistogramHalfsaturation() 
{
	m_MenuCommand=ID_COLORS_HISTOGRAM_HALFSATURATION;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretcht0() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCHT0;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretcht1() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCHT1;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnCximageHistogramStretcht2() 
{
	m_MenuCommand=ID_CXIMAGE_HISTOGRAM_STRETCHT2;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnColorsAdaptivethreshold() 
{
	m_MenuCommand=ID_COLORS_ADAPTIVETHRESHOLD;
	hThread=(HANDLE)_beginthread(RunCxImageThread,0,this);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewPreviousframe() 
{
	long m = image->GetNumFrames();
	long n = image->GetFrame()-1;
	if (n<0) n=m-1;
	if (image->GetFrame(n))
		image->Copy(*image->GetFrame(n));
	image->SetFrame(n);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewNextframe() 
{
	long m = image->GetNumFrames();
	long n = image->GetFrame()+1;
	if (n>=m) n=0;
	if (image->GetFrame(n))
		image->Copy(*image->GetFrame(n));
	image->SetFrame(n);
	UpdateAllViews(NULL);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnUpdateViewPlayanimation(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread || image->GetFrame(0)==0) pCmdUI->Enable(0);
	pCmdUI->SetCheck(m_playanimation);
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnViewPlayanimation() 
{
	m_playanimation = 1-m_playanimation;

	POSITION pos = GetFirstViewPosition();
	CDemoView *pView = (CDemoView *)GetNextView(pos);
	if (pView){
		if (m_playanimation){
			pView->SetTimer(2,200,NULL);
		} else {
			pView->KillTimer(2);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::PlayNextFrame()
{
	POSITION pos = GetFirstViewPosition();
	CDemoView *pView = (CDemoView *)GetNextView(pos);
	if (pView && image){
		pView->KillTimer(2);
		pView->SetTimer(2,10*max(1,image->GetFrameDelay()),NULL);
	}
	OnViewNextframe();
}
//////////////////////////////////////////////////////////////////////////////
void CDemoDoc::OnFiltersAddshadow() 
{
	if (image==NULL) return;
	DlgShadow dlg;

	dlg.m_x = theApp.m_Filters.ShadowX;
	dlg.m_y = theApp.m_Filters.ShadowY;
	dlg.m_radius = theApp.m_Filters.ShadowR;
	dlg.m_shadow = theApp.m_Filters.ShadowColor;
	dlg.m_bkg = theApp.m_Filters.ShadowBkg;
	dlg.m_intensity = theApp.m_Filters.ShadowIntensity;
	dlg.m_relative = theApp.m_Filters.ShadowRelative;

	if (dlg.DoModal()==IDOK){

		theApp.m_Filters.ShadowX = dlg.m_x;
		theApp.m_Filters.ShadowY = dlg.m_y;
		theApp.m_Filters.ShadowR = dlg.m_radius;
		theApp.m_Filters.ShadowColor = dlg.m_shadow;
		theApp.m_Filters.ShadowBkg = dlg.m_bkg;
		theApp.m_Filters.ShadowIntensity = dlg.m_intensity;
		theApp.m_Filters.ShadowRelative = dlg.m_relative;

		SetCursor(LoadCursor(0,IDC_WAIT));
		Stopwatch(0);

		RGBQUAD c0 = CxImage::RGBtoRGBQUAD(theApp.m_Filters.ShadowColor);
		RGBQUAD c1 = CxImage::RGBtoRGBQUAD(theApp.m_Filters.ShadowBkg);

		CxImage *mix = new CxImage(*image);
		mix->IncreaseBpp(24);
		mix->SelectionClear();
		mix->SelectionAddColor(c1);
		CxImage iShadow;
		mix->SelectionSplit(&iShadow);
		mix->SelectionDelete();

		if (theApp.m_Filters.ShadowRelative){
			CxImage gray(*image);
			gray.GrayScale();
			iShadow.Mix(gray,CxImage::OpOr);
		}

		iShadow.GaussianBlur(theApp.m_Filters.ShadowR);

		for (int n = 0; n<256; n++){
			BYTE r = (BYTE)(c1.rgbRed   + ((theApp.m_Filters.ShadowIntensity*n*((long)c0.rgbRed   - (long)c1.rgbRed))>>16));
			BYTE g = (BYTE)(c1.rgbGreen + ((theApp.m_Filters.ShadowIntensity*n*((long)c0.rgbGreen - (long)c1.rgbGreen))>>16));
			BYTE b = (BYTE)(c1.rgbBlue  + ((theApp.m_Filters.ShadowIntensity*n*((long)c0.rgbBlue  - (long)c1.rgbBlue))>>16));
			iShadow.SetPaletteColor((BYTE)(255-n),r,g,b);
		}

		mix->SetTransColor(c1);
		mix->SetTransIndex(0);
		mix->Mix(iShadow,CxImage::OpSrcCopy,theApp.m_Filters.ShadowX,theApp.m_Filters.ShadowY);
		//mix->Transfer(iShadow);
		mix->SetTransIndex(-1);

		CDemoDoc *NewDocr=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDocr)	{
			NewDocr->image = mix;
			CString s;
			s.Format(_T("NewImage%d"),((CDemoApp*)AfxGetApp())->m_nDocCount++);
			NewDocr->SetTitle(s);
			NewDocr->UpdateAllViews(0,WM_USER_NEWIMAGE);
		}

		Stopwatch(1);
		UpdateStatusBar();
		SetCursor(LoadCursor(0,IDC_ARROW));
	}
}
//////////////////////////////////////////////////////////////////////////////
BOOL lowpass
(  unsigned char* img ,//image source //ex)R,G,B,R,G,B,R,...,B
 int            dx  ,//image width
 int            dy  ,//image height
 int            byte)//byte per pixel
{
	int size = dx*dy*byte;
	unsigned char *img2 = new unsigned char[size];
	memset(img2,0,size);

	unsigned char *src,*dst;

	int xscale = dx*byte;
	src=img ;
	dst=img2;

	float result;
	int   cscale;
	int   twobyte=byte*2;

	dst+=xscale;
	for( int i=1,j,k ; i<dy-1 ; i++ )
	{
		dst+=byte;
		for( j=1 ; j<dx-1 ; j++ )
		{
			for( k=0 ; k<byte ; k++, dst++ )
			{
				cscale = j*byte;
				result =(             float ( img[(i-1)*xscale+(cscale-byte+k)] )  
					+ (2.0f * float ( img[(i-1)*xscale+(cscale     +k)] ))  
					+         float ( img[(i-1)*xscale+(cscale+byte+k)] )  
					+ (2.0f * float ( img[(i  )*xscale+(cscale-byte+k)] ))  
					+ (4.0f * float ( img[(i  )*xscale+(cscale     +k)] )) 
					+ (2.0f * float ( img[(i  )*xscale+(cscale+byte+k)] ))  
					+         float ( img[(i+1)*xscale+(cscale-byte+k)] )  
					+ (2.0f * float ( img[(i+1)*xscale+(cscale     +k)] ))  
					+         float ( img[(i+1)*xscale+(cscale+byte+k)] )   )/16.0f ;

				//�߾Ⱥ��̹Ƿ� �ణ ����..
				*dst = (result>255)?255:((result<0)?0:unsigned char(result+0.5f));
			}
		}
		dst+=byte;
	}

	memcpy(img,img2,size);
	delete []img2;

	return TRUE;
}

void CDemoDoc::CornerDetection()
{
////////////////////////////////////////////////////////////////////////////////////////
//�ڳ� ����

	COLORREF color = RGB(255,0,0);

	int   nSize = image->GetWidth()*image->GetHeight();
	BYTE* pBuf  = image->GetBits();
	BYTE* pGray = new BYTE[ nSize ];

	if( image->GetBpp() == 8 )
	{
		memcpy( pGray, image->GetBits(), nSize );
		color = RGB(255,255,255);
	}
	else
		ipl_RGBToGray( pGray, pBuf,image->GetWidth(),image->GetHeight(), 3);


	HCORNERDETECT hCorner = iplCornerDetectOpen( image->GetWidth(), image->GetHeight(), 25 );

//	VECTOR_POINT vectorCorner;
//	ipl_corner_detect( pGray, image->GetWidth(), image->GetHeight(), vectorCorner, 25 );

	DWORD t0 = timeGetTime();
	for( int k=0 ; k<10000 ; k++ )
	{
		VECTOR_POINT _vectorCorner;
		iplCornerDetectBlock( hCorner, pGray, _vectorCorner );
	}
	DWORD t1 = timeGetTime();

	VECTOR_POINT vectorCorner;
//	iplCornerDetect     ( hCorner, pGray, vectorCorner );
	iplCornerDetectBlock( hCorner, pGray, vectorCorner );

	delete[] pGray;
	pGray = NULL;

	VECTOR_POINTItor itor = vectorCorner.begin();

	while( itor != vectorCorner.end())
	{
		LPIPLPOINT lpPoint = &(*itor);

		image->DrawLine( lpPoint->x-2,lpPoint->x+2,lpPoint->y  ,lpPoint->y,color  );
		image->DrawLine( lpPoint->x  ,lpPoint->x  ,lpPoint->y-2,lpPoint->y+2,color);
		itor++;
	}

	iplCornerDetectClose( hCorner );

	CString szMsg;
	szMsg.Format(_T("nCount=%d, %d milli second"), vectorCorner.size(), (t1-t0));
	::AfxMessageBox( szMsg );


//�ڳ� ����
////////////////////////////////////////////////////////////////////////////////////////

}

BOOL _ipl_RGBToGray(OUT LPBYTE pGrayBuffer, IN const LPBYTE pSrc, int nSrcWidth, int nSrcHeight, int nBytes)
{
	if(nBytes<3) return -1;

	LPBYTE lpDst = pGrayBuffer;
	LPBYTE lpSrc = pSrc       ;
	register int nByteGap = nBytes-3;
	if(nByteGap<0) nByteGap=0;

	int nSize = nSrcHeight*nSrcWidth;
	LPBYTE lpDstEnd = lpDst + nSize;

	int nTmp = 0;

	BYTE   rgbBlue,rgbGreen,rgbRed;

	while(lpDst<lpDstEnd)
	{
		rgbBlue  = *(lpSrc++);
		rgbGreen = *(lpSrc++);
		rgbRed   = *(lpSrc++);

//		rgbGreen = *(lpSrc++);//b
//		rgbRed   = *(lpSrc++);//g
//		rgbBlue  = *(lpSrc++);//r
//		*lpDst++ = (BYTE)(0.2125f*(float)rgbRed + 0.7154f*(float)rgbGreen + 0.0721f*(float)rgbBlue);

		*lpDst++ = (BYTE)((rgbBlue+rgbGreen+rgbRed) / 3);

//		nTmp = (int)*(lpSrc++) + (int)*(lpSrc++) + (int)*(lpSrc++);
//		*lpDst++ =  nTmp / 3;
		lpSrc += nByteGap;
	}

	return 1;
}

BOOL CheckGradationCode( DWORD dwCode )
{
	switch( dwCode )
	{
	case 0x000000F://(1111)2
	case 0x000000E://(1110)2
	case 0x000000D://(1101)2
	case 0x000000B://(1011)2
	case 0x0000007://(0111)2
		return TRUE ; break;
	default:
		return FALSE; break;
	}
	return FALSE;
}

BOOL IsGradation( LPLIST_POSITIONINFO lpList, int nWidth, int nHeight, const LPBYTE lpGraySrc, int nBarrier )
{
	int nMask = 5;

	LIST_POSITIONINFOItor itor = lpList->begin();
	int nCount = lpList->size() / 2;
	while( nCount-- > 0 ) itor++;
	CPositionInfo* pPos = &(*itor);

	LPBYTE lpItor = NULL;
	lpItor = lpGraySrc + ( pPos->nY*nWidth ) + pPos->nX - (nMask/2);

	DWORD dwNegative = 0;
	DWORD dwPositive = 0;

	int nIndex = 0;
	int nValue = 0;
	while( nIndex < nMask-1 )
	{
		nValue = *lpItor - *(lpItor+1);
		if( nValue>0 ) dwPositive |= (0x01<<nIndex);
		if( nValue<0 ) dwNegative |= (0x01<<nIndex);
		nIndex++;
		lpItor++;
	}

	if( CheckGradationCode(dwPositive) ) return TRUE;
	if( CheckGradationCode(dwNegative) ) return TRUE;

	return FALSE;
}

void CDemoDoc::DetectBlock()
{
	COLORREF color = RGB(255,0,0);

	int   nWidth  = image->GetWidth ();
	int   nHeight = image->GetHeight();
	int   nSize   = image->GetWidth()*image->GetHeight();
	BYTE* pBuf    = image->GetBits  ();
	BYTE* pGray   = new BYTE[ nSize ];
	BYTE* pGrayOrg= new BYTE[ nSize ];


	if( image->GetBpp() == 8 )
	{
		memcpy( pGrayOrg, image->GetBits(), nSize );
		color = RGB(255,255,255);
	}
	else
		_ipl_RGBToGray(pGrayOrg,pBuf,image->GetWidth(),image->GetHeight(), 3);

	memcpy(pGray, pGrayOrg,nSize);
	LPBYTE lpSrc    = pGray;//frame.GetGrayBuffer();//pGray;
	LPBYTE lpSrcEnd = lpSrc + nSize;
	image->Save(_T("c:\\src.tif"), CXIMAGE_FORMAT_TIF);

	CxImage xImageLP;
	xImageLP.SetGrayPalette();
	xImageLP.CreateFromArray( lpSrc, nWidth, nHeight, sizeof(BYTE)*8, nWidth, false );
	xImageLP.Save(_T("c:\\Gray.tif"), CXIMAGE_FORMAT_TIF);

	while(lpSrc<lpSrcEnd)
	{
		if(*lpSrc==255)*lpSrc=254;
		lpSrc++;
	}



//	ipl_Flip( pGray, image->GetWidth(), image->GetHeight(), 1 );

	lpSrc = pGray;//frame.GetGrayBuffer();//pGray;
	LIST_BLOCK listBlock;

	DWORD t1=timeGetTime();
	ipl_BlockDetect( lpSrc, nWidth, nHeight, &listBlock, 20 );

	LIST_BLOCKItor itorBlock = listBlock.begin();
	while( itorBlock != listBlock.end() )
	{
		LPLIST_POSITIONINFO listLineLeft  = (*itorBlock).GetListLeft ();
		LPLIST_POSITIONINFO listLineRight = (*itorBlock).GetListRight();
		LPLIST_POSITIONINFO listLineUp    = (*itorBlock).GetListUp   ();

		LIST_POSITIONINFOItor itorLeft  = listLineLeft ->begin();
		LIST_POSITIONINFOItor itorRight = listLineRight->begin();
		LIST_POSITIONINFOItor itorUp    = listLineUp   ->begin();

		int nLeftMod  = ((*itorLeft ).nX+1) %_MACRO_BLOCK_SIZE;//+1:��ǥ index�� 0���� ����
		int nRightMod = ((*itorRight).nX+1) %_MACRO_BLOCK_SIZE;
		int nUpMod    = ((*itorUp   ).nY+1) %_MACRO_BLOCK_SIZE;

		//��,�� ��ǥ�� 8�� ��� �μ��� ����. . 3x3x3=27���� ����� ��
		//Noise Level = 1 Pixel Distance, �ػ󵵿� ����.
		nLeftMod = (nUpMod<<16) | (nLeftMod<<8) | nRightMod;
		switch( nLeftMod )
		{
		case 0x00000000:
		case 0x00000001:
		case 0x00000007:

		case 0x00000100:
		case 0x00000101:
		case 0x00000107:

		case 0x00000700:
		case 0x00000701:
		case 0x00000707:

		case 0x00010000:
		case 0x00010001:
		case 0x00010007:

		case 0x00070000:
		case 0x00070001:
		case 0x00070007:

		case 0x00010100:
		case 0x00010101:
		case 0x00010107:

		case 0x00010700:
		case 0x00010701:
		case 0x00010707:

		case 0x00070100:
		case 0x00070101:
		case 0x00070107:

		case 0x00070700:
		case 0x00070701:
		case 0x00070707:

			if( IsGradation( listLineLeft, nWidth, nHeight, pGrayOrg, 20 ) == TRUE )
				 itorBlock = listBlock.erase( itorBlock );
			else itorBlock++;
			break;
		default:
			itorBlock = listBlock.erase( itorBlock );
			break;
		}
//		if( abs( (int)listLineLeft->size() - (int)listLineUp->size() ) > _MACRO_BLOCK_SIZE )
//			 itorBlock = listBlock.erase( itorBlock );
//		else itorBlock++;
	}
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("nCount=%d, %d milli second"), listBlock.size(), (t2-t1));
	::AfxMessageBox(szMsg);

	CxImage xImageRst;
	xImageRst.SetGrayPalette();
	xImageRst.CreateFromArray( lpSrc, nWidth, nHeight, sizeof(BYTE)*8, nWidth, false );
	xImageRst.Save(_T("c:\\GrayRst.tif"), CXIMAGE_FORMAT_TIF);

	LIST_BLOCKItor itor = listBlock.begin();

	DWORD nLength = 0;
	while( itor != listBlock.end())
	{
		LPLIST_POSITIONINFO   lpListLeftPosition = (*itor).GetListLeft();
		LIST_POSITIONINFOItor itorLeftStart = lpListLeftPosition->begin();
		LIST_POSITIONINFOItor itorLeftEnd   = lpListLeftPosition->end  (); itorLeftEnd --;

		LPLIST_POSITIONINFO   lpListRightPosition = (*itor).GetListRight();
		LIST_POSITIONINFOItor itorRightStart = lpListRightPosition->begin();
		LIST_POSITIONINFOItor itorRightEnd   = lpListRightPosition->end  (); itorRightEnd--;

		LPLIST_POSITIONINFO   lpListUpPosition = (*itor).GetListUp();
		LIST_POSITIONINFOItor itorUpStart = lpListUpPosition->begin();
		LIST_POSITIONINFOItor itorUpEnd   = lpListUpPosition->end  (); itorUpEnd--;

		LPLIST_POSITIONINFO   lpListDownPosition = (*itor).GetListDown();
		LIST_POSITIONINFOItor itorDownStart = lpListDownPosition->begin();
		LIST_POSITIONINFOItor itorDownEnd   = lpListDownPosition->end  (); itorDownEnd--;

		image->DrawLine( (*itorLeftStart).GetX()  ,(*itorLeftEnd).GetX(),
						 (*itorLeftStart).GetY()  ,(*itorLeftEnd).GetY(), color );


		image->DrawLine( (*itorRightStart).GetX()  ,(*itorRightEnd).GetX(),
						 (*itorRightStart).GetY()  ,(*itorRightEnd).GetY(), color );

		image->DrawLine( (*itorUpStart).GetX()  ,(*itorUpEnd).GetX(),
						 (*itorUpStart).GetY()  ,(*itorUpEnd).GetY(), color );

		image->DrawLine( (*itorDownStart).GetX()  ,(*itorDownEnd).GetX(),
						 (*itorDownStart).GetY()  ,(*itorDownEnd).GetY(), color );

		nLength += (*itor).GetSize();
		itor++;
	}


	delete[] pGray;
	delete[] pGrayOrg;
}

BOOL IsColorBars( LPBYTE lpGray, DWORD dwSize, const DWORD& dwWidth, const DWORD& dwHeight )
{
	int m_nNoiseLevel = 6;
	int m_nBarCount   = 6;//minnum color bar count

	VECTOR_LINE vectorLine;

	int nLengthThreshold = (int)( (dwWidth/12) * 0.9 );// 12 is max color bar count, 90%
	int nMiddleHeight    = dwHeight/2;

	LPBYTE lpScan        = lpGray + (nMiddleHeight*dwWidth);
	LPBYTE lpStart       = lpScan ;
	LPBYTE lpEnd         = lpScan + dwWidth;
	LPBYTE lpLocalStart  = NULL;   

	int    nPosStart     = 0;
	int    nPosEnd       = 0;
	int    nSub          = 0;
	float  nSumDistance  = 0;

	while( lpScan<lpEnd )
	{
		lpLocalStart = lpScan;
		while( abs( (int)*lpScan - (int)*(lpScan+1) )< m_nNoiseLevel && 
			   ( lpScan<lpEnd )    )
		{
			lpScan++;
		}
		nPosStart = (int)(lpLocalStart - lpStart);
		nPosEnd   = (int)(lpScan       - lpStart);

		nSub = nPosEnd-nPosStart;
		if( nSub > nLengthThreshold )
		{
			CIplLineExtension line( nPosStart, nMiddleHeight, nPosEnd, nMiddleHeight );
			vectorLine.push_back( line );
//			nSumDistance += nSub;
		}
		if( nSub==0 ) lpScan++;
	}

	float fSumDistance = 0;
	VECTOR_LINEItor itor = vectorLine.begin();
	for( ; itor!=vectorLine.end() ; itor++ )
	{
		fSumDistance += (*itor).GetLength();
	}

	if( vectorLine.size() >= (size_t)m_nBarCount )
	{
		if( fSumDistance      >  (dwWidth*0.8f)       )
			return TRUE;
	}

	return FALSE;
}

// 0 255 0
// 0 255 0
// 0 255 0
// error pattern nPixelVariation=255*6=1530
// 1530*0.7 = 1071
// 1530*0.8 = 1224
UINT GetPixelVariation3X3( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, INT nThreshold = 1224 )
{
	int      nHeightScan    = nHeight-1;
	int      nWidthScan     = nWidth -1;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;

	int      NW, NN, NE;
	int      WW, CC, EE;
	int      SW, SS, SE; 
	int      fGyValue = 0;
	int      fGxValue = 0;
	float    fsdValue = 0;
	register int     x,y;

	int      nPixelVariation = 0;
	UINT     nCount          = 0;

#ifdef _OPENMP
#pragma omp parallel for private(x,lpSrc,lpSrcUp,lpSrcDn, NW, NN, NE,WW, CC, EE, SW, SS, SE, nPixelVariation) reduction(+:nCount)
	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc   = pSrc  + (y*nWidth) + 1;
		lpSrcUp = lpSrc - nWidth;
		lpSrcDn = lpSrc + nWidth;

		for( x=1; x<nWidthScan ; x++ )
		{
			NW = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); SE = *(lpSrcDn+1); 

			nPixelVariation = abs(NW-NN) + abs(NE-NN) +
				              abs(NW-WW) + abs(NN-CC) + abs(NE-EE) +
							  abs(WW-CC) + abs(CC-EE) +
							  abs(WW-SW) + abs(CC-SS) + abs(EE-SE) +
							  abs(SW-SS) + abs(SS-SE);

			if( nPixelVariation > nThreshold )
				nCount++;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
	}
#else
	lpSrcUp = pSrc             ;
	lpSrc   = pSrc  + nWidth;
	lpSrcDn = lpSrc + nWidth;

	for( y=1 ; y<nHeightScan ; y++ )
	{
		lpSrc++;lpSrcUp++;lpSrcDn++;
		for( x=1; x<nWidthScan ; x++ )
		{
			NW = *(lpSrcUp-1); NN = *(lpSrcUp  ); NE = *(lpSrcUp+1); 
			WW = *(lpSrc  -1); CC = *(lpSrc    ); EE = *(lpSrc  +1); 
			SW = *(lpSrcDn-1); SS = *(lpSrcDn  ); SE = *(lpSrcDn+1); 

			nPixelVariation = abs(NW-NN) + abs(NE-NN) +
				              abs(NW-WW) + abs(NN-CC) + abs(NE-EE) +
							  abs(WW-CC) + abs(CC-EE) +
							  abs(WW-SW) + abs(CC-SS) + abs(EE-SE) +
							  abs(SW-SS) + abs(SS-SE);

			if( nPixelVariation > nThreshold )
				nCount++;

			lpSrcUp++;lpSrc++;lpSrcDn++;
		}
		lpSrc++;lpSrcUp++;lpSrcDn++;
	}

#endif
	return nCount;
}

// 0 255 0 255 0
// 0 255 0 255 0
// 0 255 0 255 0
// 0 255 0 255 0
// 0 255 0 255 0
// error pattern nPixelVariation=255*5*4=5100
// 5100*0.9 = 4590
// 

UINT GetPixelVariation5X5( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, INT nThreshold = 4590 )
{
	int      nHeightScan    = nHeight-2;
	int      nWidthScan     = nWidth -2;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;
	register LPBYTE lpSrcUp2= NULL;
	register LPBYTE lpSrcDn2= NULL;

	int   a=0,b=0,c=0,d=0,e=0;
	int   f=0,g=0,h=0,i=0,j=0;
	int   k=0,l=0,m=0,n=0,o=0;
	int   p=0,q=0,r=0,s=0,t=0;
	int   u=0,v=0,w=0,x=0,y=0;

	int   itorX=0, itorY=0;

	int      nPixelVariation = 0;
	UINT     nCount          = 0;
	int      nScanTmp        = nWidth*2;
	double   dVariation      = 0.0;


#ifdef _OPENMP
#pragma omp parallel for private( itorX,lpSrc,lpSrcUp,lpSrcDn,lpSrcUp2,lpSrcDn2,\
	                              a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,\
								  nPixelVariation) reduction(+:nCount)
	for( itorY=2 ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc    = pSrc  + (itorY*nWidth) + 2;
		lpSrcUp2 = lpSrc - nScanTmp;
		lpSrcUp  = lpSrc - nWidth  ;
		lpSrcDn  = lpSrc + nWidth  ;
		lpSrcDn2 = lpSrc + nScanTmp;

		for( itorX=2; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2-2); b = *(lpSrcUp2-1); c = *(lpSrcUp2  ); d = *(lpSrcUp2+1); e = *(lpSrcUp2+2); 
			f = *(lpSrcUp -2); g = *(lpSrcUp -1); h = *(lpSrcUp   ); i = *(lpSrcUp +1); j = *(lpSrcUp +2); 
			k = *(lpSrc   -2); l = *(lpSrc   -1); m = *(lpSrc     ); n = *(lpSrc   +1); o = *(lpSrc   +2); 
			p = *(lpSrcDn -2); q = *(lpSrcDn -1); r = *(lpSrcDn   ); s = *(lpSrcDn +1); t = *(lpSrcDn +2); 
			u = *(lpSrcDn2-2); v = *(lpSrcDn2-1); w = *(lpSrcDn2  ); x = *(lpSrcDn2+1); y = *(lpSrcDn2+2); 
/*
			dVariation = 2.*( a*a + e*e + u*u + y*y ) +
				         3.*( b*b + c*c + d*d + f*f + k*k + p*p + j*j + o*o + t*t + v*v + w*w + x*x ) +
						 4.*( g*g + h*h + i*i + l*l + m*m + n*n + g*g + r*r + s*s ) -
						 2.*( g*(b+h+l+f) + q*(l+r+v+p) + i*(d+j+n+h) + s*(n+t+x+r) + m*(h+n+r+l) +
						  	  c*(b+h+d) + o*(j+n+t) + w*(x+r+v) + k*(f+l+p) +
							  a*(b+f) + e*(d+j) + y*(t+x) + u*(p+v) );

			nPixelVariation = (int) sqrt( dVariation );
*/

			nPixelVariation = abs(a-b) + abs(b-c) + abs(c-d) + abs(d-e) +
				              abs(a-f) + abs(b-g) + abs(c-h) + abs(d-i) + abs(e-j) + 
							  abs(f-g) + abs(g-h) + abs(j-i) + abs(i-j) + 
				              abs(f-k) + abs(g-l) + abs(h-m) + abs(i-n) + abs(j-o) + 
							  abs(k-l) + abs(l-m) + abs(m-n) + abs(n-o) + 
				              abs(k-p) + abs(l-q) + abs(m-r) + abs(n-s) + abs(o-t) + 
							  abs(p-q) + abs(q-r) + abs(r-s) + abs(s-t) + 
				              abs(p-u) + abs(q-v) + abs(r-w) + abs(s-x) + abs(t-y) + 
							  abs(u-v) + abs(v-w) + abs(w-x) + abs(x-y) ;

			if( nPixelVariation > nThreshold )
				nCount++;

			lpSrcUp2++;lpSrcUp++;lpSrc++;lpSrcDn++;lpSrcDn2++;
		}
	}

#else
	lpSrcUp2 = pSrc;
	lpSrcUp  = pSrc  + nWidth;
	lpSrc    = pSrc  + nWidth*2;
	lpSrcDn  = pSrc  + nWidth*3;
	lpSrcDn2 = pSrc  + nWidth*4;

	for( itorY=2 ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=2;lpSrcUp+=2;lpSrcDn+=2;lpSrcDn2+=2;lpSrcUp2+=2;
		for( itorX=2; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2-2); b = *(lpSrcUp2-1); c = *(lpSrcUp2  ); d = *(lpSrcUp2+1); e = *(lpSrcUp2+2); 
			f = *(lpSrcUp -2); g = *(lpSrcUp -1); h = *(lpSrcUp   ); i = *(lpSrcUp +1); j = *(lpSrcUp +2); 
			k = *(lpSrc   -2); l = *(lpSrc   -1); m = *(lpSrc     ); n = *(lpSrc   +1); o = *(lpSrc   +2); 
			p = *(lpSrcDn -2); q = *(lpSrcDn -1); r = *(lpSrcDn   ); s = *(lpSrcDn +1); t = *(lpSrcDn +2); 
			u = *(lpSrcDn2-2); v = *(lpSrcDn2-1); w = *(lpSrcDn2  ); x = *(lpSrcDn2+1); y = *(lpSrcDn2+2); 

//			dVariation = 2.*( a*a + e*e + u*u + y*y ) +
//				         3.*( b*b + c*c + d*d + f*f + k*k + p*p + j*j + o*o + t*t + v*v + w*w + x*x ) +
//						 4.*( g*g + h*h + i*i + l*l + m*m + n*n + g*g + r*r + s*s ) -
//						 2.*( g*(b+h+l+f) + q*(l+r+v+p) + i*(d+j+n+h) + s*(n+t+x+r) + m*(h+n+r+l) +
//						  	  c*(b+h+d) + o*(j+n+t) + w*(x+r+v) + k*(f+l+p) +
//							  a*(b+f) + e*(d+j) + y*(t+x) + u*(p+v) );
//
//			nPixelVariation = (int) sqrt( dVariation );


			nPixelVariation = abs(a-b) + abs(b-c) + abs(c-d) + abs(d-e) +
				              abs(a-f) + abs(b-g) + abs(c-h) + abs(d-i) + abs(e-j) + 
							  abs(f-g) + abs(g-h) + abs(j-i) + abs(i-j) + 
				              abs(f-k) + abs(g-l) + abs(h-m) + abs(i-n) + abs(j-o) + 
							  abs(k-l) + abs(l-m) + abs(m-n) + abs(n-o) + 
				              abs(k-p) + abs(l-q) + abs(m-r) + abs(n-s) + abs(o-t) + 
							  abs(p-q) + abs(q-r) + abs(r-s) + abs(s-t) + 
				              abs(p-u) + abs(q-v) + abs(r-w) + abs(s-x) + abs(t-y) + 
							  abs(u-v) + abs(v-w) + abs(w-x) + abs(x-y) ;
			
			if( nPixelVariation > nThreshold )
			{
#ifdef _LOGDATA
//				LOGOUT(_T("%d"),nPixelVariation);
#endif

				nCount++;
			}

			lpSrcUp2++;lpSrcUp++;lpSrc++;lpSrcDn++;lpSrcDn2++;
		}
		lpSrc+=2;lpSrcUp+=2;lpSrcDn+=2;lpSrcDn2+=2;lpSrcUp2+=2;
	}
#endif

	return nCount;
}

UINT GetPixelVariation5X5( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, OUT LPVECTOR_POINT vOutPoints, INT nThreshold = 4590 )
{
	int      nHeightScan    = nHeight-2;
	int      nWidthScan     = nWidth -2;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;
	register LPBYTE lpSrcUp2= NULL;
	register LPBYTE lpSrcDn2= NULL;

	int   a=0,b=0,c=0,d=0,e=0;
	int   f=0,g=0,h=0,i=0,j=0;
	int   k=0,l=0,m=0,n=0,o=0;
	int   p=0,q=0,r=0,s=0,t=0;
	int   u=0,v=0,w=0,x=0,y=0;

	int   itorX=0, itorY=0;

	int      nPixelVariation = 0;
	UINT     nCount          = 0;
	int      nScanTmp        = nWidth*2;
	double   dVariation      = 0.0;


#ifdef _OPENMP
#pragma omp parallel for private( itorX,lpSrc,lpSrcUp,lpSrcDn,lpSrcUp2,lpSrcDn2,\
	                              a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,\
								  nPixelVariation) reduction(+:nCount)
	for( itorY=2 ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc    = pSrc  + (itorY*nWidth) + 2;
		lpSrcUp2 = lpSrc - nScanTmp;
		lpSrcUp  = lpSrc - nWidth  ;
		lpSrcDn  = lpSrc + nWidth  ;
		lpSrcDn2 = lpSrc + nScanTmp;

		for( itorX=2; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2-2); b = *(lpSrcUp2-1); c = *(lpSrcUp2  ); d = *(lpSrcUp2+1); e = *(lpSrcUp2+2); 
			f = *(lpSrcUp -2); g = *(lpSrcUp -1); h = *(lpSrcUp   ); i = *(lpSrcUp +1); j = *(lpSrcUp +2); 
			k = *(lpSrc   -2); l = *(lpSrc   -1); m = *(lpSrc     ); n = *(lpSrc   +1); o = *(lpSrc   +2); 
			p = *(lpSrcDn -2); q = *(lpSrcDn -1); r = *(lpSrcDn   ); s = *(lpSrcDn +1); t = *(lpSrcDn +2); 
			u = *(lpSrcDn2-2); v = *(lpSrcDn2-1); w = *(lpSrcDn2  ); x = *(lpSrcDn2+1); y = *(lpSrcDn2+2); 
/*
			dVariation = 2.*( a*a + e*e + u*u + y*y ) +
				         3.*( b*b + c*c + d*d + f*f + k*k + p*p + j*j + o*o + t*t + v*v + w*w + x*x ) +
						 4.*( g*g + h*h + i*i + l*l + m*m + n*n + g*g + r*r + s*s ) -
						 2.*( g*(b+h+l+f) + q*(l+r+v+p) + i*(d+j+n+h) + s*(n+t+x+r) + m*(h+n+r+l) +
						  	  c*(b+h+d) + o*(j+n+t) + w*(x+r+v) + k*(f+l+p) +
							  a*(b+f) + e*(d+j) + y*(t+x) + u*(p+v) );

			nPixelVariation = (int) sqrt( dVariation );
*/

			nPixelVariation = abs(a-b) + abs(b-c) + abs(c-d) + abs(d-e) +
				              abs(a-f) + abs(b-g) + abs(c-h) + abs(d-i) + abs(e-j) + 
							  abs(f-g) + abs(g-h) + abs(j-i) + abs(i-j) + 
				              abs(f-k) + abs(g-l) + abs(h-m) + abs(i-n) + abs(j-o) + 
							  abs(k-l) + abs(l-m) + abs(m-n) + abs(n-o) + 
				              abs(k-p) + abs(l-q) + abs(m-r) + abs(n-s) + abs(o-t) + 
							  abs(p-q) + abs(q-r) + abs(r-s) + abs(s-t) + 
				              abs(p-u) + abs(q-v) + abs(r-w) + abs(s-x) + abs(t-y) + 
							  abs(u-v) + abs(v-w) + abs(w-x) + abs(x-y) ;

			if( nPixelVariation > nThreshold )
			{
				nCount++;
				if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));
			}

			lpSrcUp2++;lpSrcUp++;lpSrc++;lpSrcDn++;lpSrcDn2++;
		}
	}

#else
	lpSrcUp2 = pSrc;
	lpSrcUp  = pSrc  + nWidth;
	lpSrc    = pSrc  + nWidth*2;
	lpSrcDn  = pSrc  + nWidth*3;
	lpSrcDn2 = pSrc  + nWidth*4;

	for( itorY=2 ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=2;lpSrcUp+=2;lpSrcDn+=2;lpSrcDn2+=2;lpSrcUp2+=2;
		for( itorX=2; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2-2); b = *(lpSrcUp2-1); c = *(lpSrcUp2  ); d = *(lpSrcUp2+1); e = *(lpSrcUp2+2); 
			f = *(lpSrcUp -2); g = *(lpSrcUp -1); h = *(lpSrcUp   ); i = *(lpSrcUp +1); j = *(lpSrcUp +2); 
			k = *(lpSrc   -2); l = *(lpSrc   -1); m = *(lpSrc     ); n = *(lpSrc   +1); o = *(lpSrc   +2); 
			p = *(lpSrcDn -2); q = *(lpSrcDn -1); r = *(lpSrcDn   ); s = *(lpSrcDn +1); t = *(lpSrcDn +2); 
			u = *(lpSrcDn2-2); v = *(lpSrcDn2-1); w = *(lpSrcDn2  ); x = *(lpSrcDn2+1); y = *(lpSrcDn2+2); 

//			dVariation = 2.*( a*a + e*e + u*u + y*y ) +
//				         3.*( b*b + c*c + d*d + f*f + k*k + p*p + j*j + o*o + t*t + v*v + w*w + x*x ) +
//						 4.*( g*g + h*h + i*i + l*l + m*m + n*n + g*g + r*r + s*s ) -
//						 2.*( g*(b+h+l+f) + q*(l+r+v+p) + i*(d+j+n+h) + s*(n+t+x+r) + m*(h+n+r+l) +
//						  	  c*(b+h+d) + o*(j+n+t) + w*(x+r+v) + k*(f+l+p) +
//							  a*(b+f) + e*(d+j) + y*(t+x) + u*(p+v) );
//
//			nPixelVariation = (int) sqrt( dVariation );


			nPixelVariation = abs(a-b) + abs(b-c) + abs(c-d) + abs(d-e) +
				              abs(a-f) + abs(b-g) + abs(c-h) + abs(d-i) + abs(e-j) + 
							  abs(f-g) + abs(g-h) + abs(j-i) + abs(i-j) + 
				              abs(f-k) + abs(g-l) + abs(h-m) + abs(i-n) + abs(j-o) + 
							  abs(k-l) + abs(l-m) + abs(m-n) + abs(n-o) + 
				              abs(k-p) + abs(l-q) + abs(m-r) + abs(n-s) + abs(o-t) + 
							  abs(p-q) + abs(q-r) + abs(r-s) + abs(s-t) + 
				              abs(p-u) + abs(q-v) + abs(r-w) + abs(s-x) + abs(t-y) + 
							  abs(u-v) + abs(v-w) + abs(w-x) + abs(x-y) ;
			
			if( nPixelVariation > nThreshold )
			{
				nCount++;
				if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));
			}

			lpSrcUp2++;lpSrcUp++;lpSrc++;lpSrcDn++;lpSrcDn2++;
		}
		lpSrc+=2;lpSrcUp+=2;lpSrcDn+=2;lpSrcDn2+=2;lpSrcUp2+=2;
	}
#endif

	return nCount;
}

//int BufferCountData( BYTE* pData,int nSize, BYTE byteCompData1, BYTE byteCompData2 )
int BufferCountData( BYTE* pData,int nSize, BYTE byteCompData )
{
	LPBYTE lpItor    = pData;
	LPBYTE lpItorEnd = pData+nSize;

	int nCount =0  ;
	while( lpItor<lpItorEnd )
	{
		if( *lpItor   == byteCompData )//1 ||
			//*lpItor   == byteCompData2 )
			nCount++;

		lpItor++;
	}

	return nCount;
}

#define GET_RELATION_LBP_HORIZONTAL_C3X3(a,b,c,d,e,\
	                                     f,g,h,i,j,\
									     k,l,m,n,o,\
									     p,q,r,s,t,\
									     u,v,w,x,y,nBarrier) (\
	( (abs(g-h)>nBarrier)?1:0 )<< 5 |\
	( (abs(j-i)>nBarrier)?1:0 )<< 4 |\
\
	( (abs(l-m)>nBarrier)?1:0 )<< 3 |\
	( (abs(m-n)>nBarrier)?1:0 )<< 2 |\
\
	( (abs(q-r)>nBarrier)?1:0 )<< 1 |\
	( (abs(r-s)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_RIGHT(a,b,c,d,e,\
	                                 f,g,h,i,j,\
									 k,l,m,n,o,\
									 p,q,r,s,t,\
									 u,v,w,x,y,nBarrier)(\
	( (abs(d-j)>nBarrier)?1:0 )<<15 |\
\
	( (abs(c-i)>nBarrier)?1:0 )<<14 |\
	( (abs(i-o)>nBarrier)?1:0 )<<13 |\
\
	( (abs(b-h)>nBarrier)?1:0 )<<12 |\
	( (abs(h-n)>nBarrier)?1:0 )<<11 |\
	( (abs(n-t)>nBarrier)?1:0 )<<10 |\
\
	( (abs(a-g)>nBarrier)?1:0 )<< 9 |\
	( (abs(g-m)>nBarrier)?1:0 )<< 8 |\
	( (abs(m-s)>nBarrier)?1:0 )<< 7 |\
	( (abs(s-y)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(f-l)>nBarrier)?1:0 )<< 5 |\
	( (abs(l-r)>nBarrier)?1:0 )<< 4 |\
	( (abs(r-x)>nBarrier)?1:0 )<< 3 |\
\
	( (abs(k-q)>nBarrier)?1:0 )<< 2 |\
	( (abs(q-w)>nBarrier)?1:0 )<< 1 |\
\
	( (abs(p-v)>nBarrier)?1:0 )<< 0 )




#define GET_RELATION_LBP_CROSS_LEFT(a,b,c,d,e,\
	                                f,g,h,i,j,\
									k,l,m,n,o,\
									p,q,r,s,t,\
									u,v,w,x,y,nBarrier)(\
	( (abs(b-f)>nBarrier)?1:0 )<<15 |\
\
	( (abs(c-g)>nBarrier)?1:0 )<<14 |\
	( (abs(g-k)>nBarrier)?1:0 )<<13 |\
\
	( (abs(d-h)>nBarrier)?1:0 )<<12 |\
	( (abs(h-l)>nBarrier)?1:0 )<<11 |\
	( (abs(l-p)>nBarrier)?1:0 )<<10 |\
\
	( (abs(e-i)>nBarrier)?1:0 )<< 9 |\
	( (abs(i-m)>nBarrier)?1:0 )<< 8 |\
	( (abs(m-q)>nBarrier)?1:0 )<< 7 |\
	( (abs(q-u)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(j-n)>nBarrier)?1:0 )<< 5 |\
	( (abs(n-r)>nBarrier)?1:0 )<< 4 |\
	( (abs(r-v)>nBarrier)?1:0 )<< 3 |\
\
	( (abs(o-s)>nBarrier)?1:0 )<< 2 |\
	( (abs(s-w)>nBarrier)?1:0 )<< 1 |\
\
	( (abs(t-x)>nBarrier)?1:0 )<< 0 )

//ž������ ȭ�� ��ȭ�� ����ó��
#define GET_RELATION_LBP_TOWER8BIT(a,b,c,d,e,\
	                               f,g,h,i,j,\
								   k,l,m,n,o,\
								   p,q,r,s,t,\
								   u,v,w,x,y,nBarrier)(\
	( ((m-g)>nBarrier)?1:0 )<< 7 |\
	( ((g-a)>nBarrier)?1:0 )<< 6 |\
\
	( ((m-i)>nBarrier)?1:0 )<< 5 |\
	( ((i-e)>nBarrier)?1:0 )<< 4 |\
\
	( ((m-q)>nBarrier)?1:0 )<< 3 |\
	( ((q-u)>nBarrier)?1:0 )<< 2 |\
\
	( ((m-s)>nBarrier)?1:0 )<< 1 |\
	( ((s-y)>nBarrier)?1:0 )<< 0  )



/////////////////////////////////////
//  MMMMM
//  MLMHM
//  MMMMM
//  MHMLM
//  MMMMM
//  M:Middle pixel vlaue
//  H:High     "
//  L:Low      "
// ��� ������ ��� �Ʒ� �ڵ�� ����.
// abs�Լ��� ���°Ϳ� ���Ͽ� �ӵ� ����.

//  MMMMM
//  MLMLM
//  MMMMM
//  MHMHM
//  MMMMM
// ��� ���µ� ����.
/*
#define GET_RELATION_LBP_CROSS_LEFT(a,b,c,d,e,\
	                                f,g,h,i,j,\
									k,l,m,n,o,\
									p,q,r,s,t,\
									u,v,w,x,y,nBarrier)(\
	( ((b-f)>nBarrier)?1:0 )<<15 |\
\
	( ((c-g)>nBarrier)?1:0 )<<14 |\
	( ((k-g)>nBarrier)?1:0 )<<13 |\
\
	( ((d-h)>nBarrier)?1:0 )<<12 |\
	( ((h-l)>nBarrier)?1:0 )<<11 |\
	( ((l-p)>nBarrier)?1:0 )<<10 |\
\
	( ((i-e)>nBarrier)?1:0 )<< 9 |\
	( ((i-m)>nBarrier)?1:0 )<< 8 |\
	( ((q-m)>nBarrier)?1:0 )<< 7 |\
	( ((q-u)>nBarrier)?1:0 )<< 6 |\
\
	( ((j-n)>nBarrier)?1:0 )<< 5 |\
	( ((n-r)>nBarrier)?1:0 )<< 4 |\
	( ((r-v)>nBarrier)?1:0 )<< 3 |\
\
	( ((o-s)>nBarrier)?1:0 )<< 2 |\
	( ((w-s)>nBarrier)?1:0 )<< 1 |\
\
	( ((t-x)>nBarrier)?1:0 )<< 0 )

#define GET_RELATION_LBP_CROSS_RIGHT(a,b,c,d,e,\
	                                 f,g,h,i,j,\
									 k,l,m,n,o,\
									 p,q,r,s,t,\
									 u,v,w,x,y,nBarrier)(\
	( (abs(d-j)>nBarrier)?1:0 )<<15 |\
\
	( (abs(i-c)>nBarrier)?1:0 )<<14 |\
	( (abs(i-o)>nBarrier)?1:0 )<<13 |\
\
	( (abs(b-h)>nBarrier)?1:0 )<<12 |\
	( (abs(h-n)>nBarrier)?1:0 )<<11 |\
	( (abs(n-t)>nBarrier)?1:0 )<<10 |\
\
	( (abs(a-g)>nBarrier)?1:0 )<< 9 |\
	( (abs(m-g)>nBarrier)?1:0 )<< 8 |\
	( (abs(m-s)>nBarrier)?1:0 )<< 7 |\
	( (abs(y-s)>nBarrier)?1:0 )<< 6 |\
\
	( (abs(f-l)>nBarrier)?1:0 )<< 5 |\
	( (abs(l-r)>nBarrier)?1:0 )<< 4 |\
	( (abs(r-x)>nBarrier)?1:0 )<< 3 |\
\
	( (abs(q-k)>nBarrier)?1:0 )<< 2 |\
	( (abs(q-w)>nBarrier)?1:0 )<< 1 |\
\
	( (abs(p-v)>nBarrier)?1:0 )<< 0 )
*/

int GetLBPCount5X5Diagonal( LPBYTE pSrc, INT nSize, const INT& nWidth, const INT& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier )
{
	int      nHeightScan    = nHeight-2;
	int      nWidthScan     = nWidth -2;

	register LPBYTE lpSrc   = pSrc;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcDn = NULL;
	register LPBYTE lpSrcUp2= NULL;
	register LPBYTE lpSrcDn2= NULL;

	int   a=0,b=0,c=0,d=0,e=0;
	int   f=0,g=0,h=0,i=0,j=0;
	int   k=0,l=0,m=0,n=0,o=0;
	int   p=0,q=0,r=0,s=0,t=0;
	int   u=0,v=0,w=0,x=0,y=0;

	int   itorX=0, itorY=0;

	UINT     nPixelVariation = 0;
	UINT     nLBP_CL         = 0;
	UINT     nLBP_CR         = 0;
	UINT     nLBP_TW         = 0;
	int      nCount          = 0;
	int      nScanTmp        = nWidth*2;
	double   dVariation      = 0.0;


#ifdef _OPENMP
#pragma omp parallel for private( itorX,lpSrc,lpSrcUp,lpSrcDn,lpSrcUp2,lpSrcDn2,\
	                              a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,\
								  nLBP_CL,nLBP_CR) reduction(+:nCount)
	for( itorY=2 ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc    = pSrc  + (itorY*nWidth) + 2;
		lpSrcUp2 = lpSrc - nScanTmp;
		lpSrcUp  = lpSrc - nWidth  ;
		lpSrcDn  = lpSrc + nWidth  ;
		lpSrcDn2 = lpSrc + nScanTmp;

		for( itorX=2; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2-2); b = *(lpSrcUp2-1); c = *(lpSrcUp2  ); d = *(lpSrcUp2+1); e = *(lpSrcUp2+2); 
			f = *(lpSrcUp -2); g = *(lpSrcUp -1); h = *(lpSrcUp   ); i = *(lpSrcUp +1); j = *(lpSrcUp +2); 
			k = *(lpSrc   -2); l = *(lpSrc   -1); m = *(lpSrc     ); n = *(lpSrc   +1); o = *(lpSrc   +2); 
			p = *(lpSrcDn -2); q = *(lpSrcDn -1); r = *(lpSrcDn   ); s = *(lpSrcDn +1); t = *(lpSrcDn +2); 
			u = *(lpSrcDn2-2); v = *(lpSrcDn2-1); w = *(lpSrcDn2  ); x = *(lpSrcDn2+1); y = *(lpSrcDn2+2); 

			nLBP_CL =
			GET_RELATION_LBP_CROSS_LEFT(\
			                             a,b,c,d,e,\
										 f,g,h,i,j,\
										 k,l,m,n,o,\
										 p,q,r,s,t,\
										 u,v,w,x,y,nBarrier);

			nLBP_CR =
			GET_RELATION_LBP_CROSS_RIGHT(\
			                             a,b,c,d,e,\
										 f,g,h,i,j,\
										 k,l,m,n,o,\
										 p,q,r,s,t,\
										 u,v,w,x,y,nBarrier);

			nLBP_TW =
			GET_RELATION_LBP_TOWER8BIT(\
										 a,b,c,d,e,\
										 f,g,h,i,j,\
										 k,l,m,n,o,\
										 p,q,r,s,t,\
										 u,v,w,x,y,nBarrier);


			if( (nLBP_CL==0x000063C6) && 
				(nLBP_CR==0x000063C6) &&
				(nLBP_TW!=0x000000FF)  )
			{
				nCount++;
				if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));
			}

			lpSrcUp2++;lpSrcUp++;lpSrc++;lpSrcDn++;lpSrcDn2++;
		}
	}

#else
	lpSrcUp2 = pSrc;
	lpSrcUp  = pSrc  + nWidth;
	lpSrc    = pSrc  + nWidth*2;
	lpSrcDn  = pSrc  + nWidth*3;
	lpSrcDn2 = pSrc  + nWidth*4;

	for( itorY=2 ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=2;lpSrcUp+=2;lpSrcDn+=2;lpSrcDn2+=2;lpSrcUp2+=2;
		for( itorX=2; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2-2); b = *(lpSrcUp2-1); c = *(lpSrcUp2  ); d = *(lpSrcUp2+1); e = *(lpSrcUp2+2); 
			f = *(lpSrcUp -2); g = *(lpSrcUp -1); h = *(lpSrcUp   ); i = *(lpSrcUp +1); j = *(lpSrcUp +2); 
			k = *(lpSrc   -2); l = *(lpSrc   -1); m = *(lpSrc     ); n = *(lpSrc   +1); o = *(lpSrc   +2); 
			p = *(lpSrcDn -2); q = *(lpSrcDn -1); r = *(lpSrcDn   ); s = *(lpSrcDn +1); t = *(lpSrcDn +2); 
			u = *(lpSrcDn2-2); v = *(lpSrcDn2-1); w = *(lpSrcDn2  ); x = *(lpSrcDn2+1); y = *(lpSrcDn2+2); 


			nLBP_CL =
			GET_RELATION_LBP_CROSS_LEFT(\
			                             a,b,c,d,e,\
										 f,g,h,i,j,\
										 k,l,m,n,o,\
										 p,q,r,s,t,\
										 u,v,w,x,y,nBarrier);

			nLBP_CR =
			GET_RELATION_LBP_CROSS_RIGHT(\
			                             a,b,c,d,e,\
										 f,g,h,i,j,\
										 k,l,m,n,o,\
										 p,q,r,s,t,\
										 u,v,w,x,y,nBarrier);

			nLBP_TW =
			GET_RELATION_LBP_TOWER8BIT(\
										 a,b,c,d,e,\
										 f,g,h,i,j,\
										 k,l,m,n,o,\
										 p,q,r,s,t,\
										 u,v,w,x,y,nBarrier);


			if( (nLBP_CL==0x000063C6) && 
				(nLBP_CR==0x000063C6) &&
				(nLBP_TW!=0x000000FF)  )
			{
				nCount++;
				if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));
			}

			lpSrcUp2++;lpSrcUp++;lpSrc++;lpSrcDn++;lpSrcDn2++;
		}
		lpSrc+=2;lpSrcUp+=2;lpSrcDn+=2;lpSrcDn2+=2;lpSrcUp2+=2;
	}
#endif

	return nCount;
};

void CDemoDoc::DCTCodeBlock()
{
	int nSize = image->GetWidth()*image->GetHeight();

	LPBYTE lpBuffer = NULL;
	BYTE*  pGray    = NULL;
	switch( image->GetBpp() )
	{
	case 24:
		{
			BYTE* pBuf = image->GetBits();
			pGray      = new BYTE[nSize];
			ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());
			CxImage xImageLP;
			xImageLP.SetGrayPalette();
			xImageLP.CreateFromArray( pGray, image->GetWidth(),image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
			xImageLP.Save(_T("c:\\Gray.tif"), CXIMAGE_FORMAT_TIF);
			lpBuffer = pGray;
		}
		break;
	case 8:
		lpBuffer = image->GetBits();
		break;
	}


	VECTOR_POINT vPoints;

	DWORD t1=timeGetTime();
	UINT nCount = 0;
	nCount  = iplGetDCTCodeBlockCount5X5( lpBuffer, nSize, image->GetWidth(),image->GetHeight(), &vPoints, 200, 50 );
//	nCount += iplGetLBPCount5X5Diagonal( lpBuffer, nSize, image->GetWidth(),image->GetHeight(), &vPoints, 50 );
//	nCount += iplGetLBPCount5X5_H_V    ( lpBuffer, nSize, image->GetWidth(),image->GetHeight(), &vPoints );
//	nCount += iplGetLBPCount5X5Diagonal( lpBuffer, nSize, image->GetWidth(),image->GetHeight(),  50 );
//	nCount += iplGetLBPCount5X5_H_V    ( lpBuffer, nSize, image->GetWidth(),image->GetHeight() );
	//BOOL bRst = IsColorBars( pGray, nSize, image->GetWidth(),image->GetHeight() );
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("nCount=%d, %d milli second"), nCount, (t2-t1));
	::AfxMessageBox(szMsg);

	if(pGray) delete[] pGray;

	COLORREF color = RGB(255,0,0);
	VECTOR_POINTItor itor = vPoints.begin();

	while( itor != vPoints.end())
	{
		LPIPLPOINT lpPoint = &(*itor);

		image->DrawLine( lpPoint->x-2,lpPoint->x+2,lpPoint->y  ,lpPoint->y,color  );
		image->DrawLine( lpPoint->x  ,lpPoint->x  ,lpPoint->y-2,lpPoint->y+2,color);
		itor++;
	}

}

/*
int GetEdgeBlockCandidate( const LPBYTE lpSrcGray, const int& nWidth, const int& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier = 20 )
{
	//���������� ���� ������� �� �����ӿ� ���Ͽ� 
	//������ ���� ������ ���� max count�� ���Ͽ� 
	//�� ���� ���� �� ��� ������ �ߴ��Ͽ� �ӵ� ������ �⿩ �� �� ����.
	int      nMaskSize      = 24  ;
	BYTE     byteMask[25*25]={0}  ;
	int      byteNoiseLevel = 5*4 ;

	LPBYTE   lpMasks00 = byteMask + 25* 0 +1;
	LPBYTE   lpMasks01 = byteMask + 25* 1 +1;
	LPBYTE   lpMasks02 = byteMask + 25* 2 +1;
	LPBYTE   lpMasks03 = byteMask + 25* 3 +1;
	LPBYTE   lpMasks04 = byteMask + 25* 4 +1;
	LPBYTE   lpMasks05 = byteMask + 25* 5 +1;
	LPBYTE   lpMasks06 = byteMask + 25* 6 +1;
	LPBYTE   lpMasks07 = byteMask + 25* 7 +1;
	LPBYTE   lpMasks08 = byteMask + 25* 8 +1;
	LPBYTE   lpMasks09 = byteMask + 25* 9 +1;
	LPBYTE   lpMasks10 = byteMask + 25*10 +1;
	LPBYTE   lpMasks11 = byteMask + 25*11 +1;
	LPBYTE   lpMasks12 = byteMask + 25*12 +1;
	LPBYTE   lpMasks13 = byteMask + 25*13 +1;
	LPBYTE   lpMasks14 = byteMask + 25*14 +1;
	LPBYTE   lpMasks15 = byteMask + 25*15 +1;
	LPBYTE   lpMasks16 = byteMask + 25*16 +1;
	LPBYTE   lpMasks17 = byteMask + 25*17 +1;
	LPBYTE   lpMasks18 = byteMask + 25*18 +1;
	LPBYTE   lpMasks19 = byteMask + 25*19 +1;
	LPBYTE   lpMasks20 = byteMask + 25*20 +1;
	LPBYTE   lpMasks21 = byteMask + 25*21 +1;
	LPBYTE   lpMasks22 = byteMask + 25*22 +1;
	LPBYTE   lpMasks23 = byteMask + 25*23 +1;
	LPBYTE   lpMasks24 = byteMask + 25*24 +1;

	int      nStartPos      = nMaskSize / 2          ;
	int      nStartPosSub1  = nStartPos - 1          ;
	int      nHeightScan    = nHeight - nStartPos    ;
	int      nWidthScan     = nWidth  - nStartPosSub1;
	int      nCount         = 0   ;
	int      nSumStart      = 0   ;
	int      nSumEnd        = 0   ;

	register LPBYTE lpSrc   = NULL;
	register LPBYTE lpSrcUp = NULL;
	register LPBYTE lpSrcUp2= NULL;
	register LPBYTE lpSrcUp3= NULL;
	register LPBYTE lpCpySrc= NULL;
	register LPBYTE lpCpyEnd= NULL;

	int   a=0,b=0,c=0,d=0,e=0;
	int   f=0,g=0,h=0,i=0,j=0;

	int   itorX=0, itorY=0;


	lpSrc    = lpSrcGray + nWidth*nStartPos ;
	lpSrcUp  = lpSrc     + nWidth;
	lpSrcUp2 = lpSrcUp   + nWidth;
	lpSrcUp3 = lpSrcUp2  + nWidth;

	for( itorY=nStartPos ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=nStartPos;lpSrcUp+=nStartPos;lpSrcUp2+=nStartPos;lpSrcUp3+=nStartPos;
		for( itorX=nStartPos; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrc     );
			e = *(lpSrc  + 1);
			if( abs(a-e)<nBarrier )  //�ӵ� ����� ����
			{
				lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
				continue;
			}

			b = *(lpSrcUp   );
			f = *(lpSrcUp +1);
			if( abs(b-f)<nBarrier )  //�ӵ� ����� ����
			{
				lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
				continue;
			}

			c = *(lpSrcUp2   );
			g = *(lpSrcUp2 +1);
			if( abs(c-g)<nBarrier )  //�ӵ� ����� ����
			{
				lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
				continue;
			}

			d = *(lpSrcUp3   );
			h = *(lpSrcUp3 +1);
			if( abs(d-h)<nBarrier )  //�ӵ� ����� ����
			{
				lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
				continue;
			}

			lpCpySrc = lpSrc - (nStartPos*nWidth) - nStartPos;
			nSumStart = *lpCpySrc + *(lpCpySrc+1) + *(lpCpySrc+2) + *(lpCpySrc+3);
			if( nSumStart < byteNoiseLevel )//Letterbox���� ����
			{
				lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
				continue;
			}

			lpCpyEnd = lpCpySrc + nMaskSize - 4;
			if( *lpCpyEnd + *(lpCpyEnd+1) + *(lpCpyEnd+2) + *(lpCpyEnd+3) < byteNoiseLevel )//Letterbox���� ����
			{
				lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
				continue;
			}

			iplmemcpy( lpMasks01, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks02, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks03, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks04, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks05, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks06, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks07, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks08, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks09, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks10, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks11, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks12, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks13, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks14, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks15, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks16, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks17, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks18, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks19, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks20, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks21, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks22, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks23, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks24, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;


			TCHAR szPath[MAX_PATH]={0};
			_stprintf( szPath, _T("C:\\TestCheckResult\\TrainData\\%08d.bmp"), nCount++ );

			CxImage xImageorg;
			xImageorg.SetGrayPalette();
			xImageorg.CreateFromArray( byteMask, 25, 25, sizeof(BYTE)*8, 25, true );
			xImageorg.Save( szPath, CXIMAGE_SUPPORT_BMP);


			if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));

			lpSrc++;lpSrcUp++;lpSrcUp2++;lpSrcUp3++;
		}
		lpSrc+=nStartPosSub1;lpSrcUp+=nStartPosSub1;lpSrcUp2+=nStartPosSub1;lpSrcUp3+=nStartPosSub1;
	}

	return nCount;
}
*/

int GetEdgeBlockCandidate7x7( const LPBYTE lpSrcGray, const int& nWidth, const int& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier = 20 )
{
	//���������� ���� ������� �� �����ӿ� ���Ͽ� 
	//������ ���� ������ ���� max count�� ���Ͽ� 
	//�� ���� ���� �� ��� ������ �ߴ��Ͽ� �ӵ� ������ �⿩ �� �� ����.
	int      nMaskSize      = 24  ;
	BYTE     byteMask[24*24]={0}  ;//openMP���� thread ����ŭ �����ؾ� ��.
	int      nNoiseLevel    = 5   ;

	LPBYTE   lpMasks00 = byteMask + 24* 0 ;
	LPBYTE   lpMasks01 = byteMask + 24* 1 ;
	LPBYTE   lpMasks02 = byteMask + 24* 2 ;
	LPBYTE   lpMasks03 = byteMask + 24* 3 ;
	LPBYTE   lpMasks04 = byteMask + 24* 4 ;
	LPBYTE   lpMasks05 = byteMask + 24* 5 ;
	LPBYTE   lpMasks06 = byteMask + 24* 6 ;
	LPBYTE   lpMasks07 = byteMask + 24* 7 ;
	LPBYTE   lpMasks08 = byteMask + 24* 8 ;
	LPBYTE   lpMasks09 = byteMask + 24* 9 ;
	LPBYTE   lpMasks10 = byteMask + 24*10 ;
	LPBYTE   lpMasks11 = byteMask + 24*11 ;
	LPBYTE   lpMasks12 = byteMask + 24*12 ;
	LPBYTE   lpMasks13 = byteMask + 24*13 ;
	LPBYTE   lpMasks14 = byteMask + 24*14 ;
	LPBYTE   lpMasks15 = byteMask + 24*15 ;
	LPBYTE   lpMasks16 = byteMask + 24*16 ;
	LPBYTE   lpMasks17 = byteMask + 24*17 ;
	LPBYTE   lpMasks18 = byteMask + 24*18 ;
	LPBYTE   lpMasks19 = byteMask + 24*19 ;
	LPBYTE   lpMasks20 = byteMask + 24*20 ;
	LPBYTE   lpMasks21 = byteMask + 24*21 ;
	LPBYTE   lpMasks22 = byteMask + 24*22 ;
	LPBYTE   lpMasks23 = byteMask + 24*23 ;


	int      nStartPos      = nMaskSize / 2          ;
	int      nStartPosSub1  = nStartPos - 1          ;
	int      nHeightScan    = nHeight - nStartPos    ;
	int      nWidthScan     = nWidth  - nStartPosSub1;
	int      nSumStart      = 0   ;
	int      nSumEnd        = 0   ;
	int      nBoundary      = 3   ;
	int      nBoundaryX2    = 6   ;
	int      nCount         = 0;

	register LPBYTE lpSrc   = NULL;
	register LPBYTE lpSrcDn2= NULL;
	register LPBYTE lpSrcUp2= NULL;

	register LPBYTE lpCpySrc= NULL;
	register LPBYTE lpCpyEnd= NULL;

	int   a=0,b=0;
	int   c=0,d=0;
//
//   a ����������b
//   ��������������
//   ��������������
//   ������o ������
//   ��������������
//   ��������������
//   c ����������d
//

	int   itorX=0, itorY=0;


	lpSrc    = lpSrcGray + nWidth*nStartPos ;
	lpSrcUp2 = lpSrc     - 2*nWidth - nBoundary;
	lpSrcDn2 = lpSrc     + 2*nWidth - nBoundary;

	for( itorY=nStartPos ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=nStartPos;lpSrcDn2+=nStartPos;lpSrcUp2+=nStartPos;
		for( itorX=nStartPos; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp2);
			c = *(lpSrcDn2);
			if( abs(a-c)<nBarrier )  
			{
				lpSrc++;lpSrcDn2++;lpSrcUp2++;
				continue;
			}

			b = *(lpSrcUp2 + nBoundaryX2 );
			if( abs(a-b)<nBarrier ) 
			{
				lpSrc++;lpSrcDn2++;lpSrcUp2++;
				continue;
			}

//			if( abs(b-c)>nNoiseLevel )
//			{
//				lpSrc++;lpSrcDn2++;lpSrcUp2++;
//				continue;
//			}

			d = *(lpSrcDn2 + nBoundaryX2 );
//			if( abs(a-d)>nNoiseLevel )
//			{
//				lpSrc++;lpSrcDn2++;lpSrcUp2++;
//				continue;
//			}

			if( abs(c-d)<nBarrier ) 
			{
				lpSrc++;lpSrcDn2++;lpSrcUp2++;
				continue;
			}
			if( abs(b-d)<nBarrier ) 
			{
				lpSrc++;lpSrcDn2++;lpSrcUp2++;
				continue;
			}

			lpCpySrc = lpSrc - (nStartPos*nWidth) - nStartPos;

			iplmemcpy( lpMasks00, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks01, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks02, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks03, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks04, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks05, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks06, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks07, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks08, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks09, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks10, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks11, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks12, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks13, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks14, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks15, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks16, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks17, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks18, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks19, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks20, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks21, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks22, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks23, lpCpySrc, sizeof(BYTE)*nMaskSize ); 


			static int nImgCount = 0;
			TCHAR szPath[MAX_PATH]={0};
			_stprintf( szPath, _T("C:\\TestCheckResult\\EgdeBlockiness������\\20100809_00001\\%09d.bmp"), nImgCount++ );

			CxImage xImageorg;
			xImageorg.SetGrayPalette();
			xImageorg.CreateFromArray( byteMask, 24, 24, sizeof(BYTE)*8, 24, false );
			xImageorg.Save( szPath, CXIMAGE_SUPPORT_BMP);


			if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));

			lpSrc++;lpSrcDn2++;lpSrcUp2++;
		}
		lpSrc+=nStartPosSub1;lpSrcDn2+=nStartPosSub1;lpSrcUp2+=nStartPosSub1;
	}

	return nCount;
}

int GetEdgeBlockCandidate2x2( const LPBYTE lpSrcGray, const int& nWidth, const int& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier = 70 )
{
	//���������� ���� ������� �� �����ӿ� ���Ͽ� 
	//������ ���� ������ ���� max count�� ���Ͽ� 
	//�� ���� ���� �� ��� ������ �ߴ��Ͽ� �ӵ� ������ �⿩ �� �� ����.
	int      nMaskSize      = 24  ;
	BYTE     byteMask[24*24]={0}  ;//openMP���� thread ����ŭ �����ؾ� ��.
	int      nNoiseLevel    = 5   ;

	LPBYTE   lpMasks00 = byteMask + 24* 0 ;
	LPBYTE   lpMasks01 = byteMask + 24* 1 ;
	LPBYTE   lpMasks02 = byteMask + 24* 2 ;
	LPBYTE   lpMasks03 = byteMask + 24* 3 ;
	LPBYTE   lpMasks04 = byteMask + 24* 4 ;
	LPBYTE   lpMasks05 = byteMask + 24* 5 ;
	LPBYTE   lpMasks06 = byteMask + 24* 6 ;
	LPBYTE   lpMasks07 = byteMask + 24* 7 ;
	LPBYTE   lpMasks08 = byteMask + 24* 8 ;
	LPBYTE   lpMasks09 = byteMask + 24* 9 ;
	LPBYTE   lpMasks10 = byteMask + 24*10 ;
	LPBYTE   lpMasks11 = byteMask + 24*11 ;
	LPBYTE   lpMasks12 = byteMask + 24*12 ;
	LPBYTE   lpMasks13 = byteMask + 24*13 ;
	LPBYTE   lpMasks14 = byteMask + 24*14 ;
	LPBYTE   lpMasks15 = byteMask + 24*15 ;
	LPBYTE   lpMasks16 = byteMask + 24*16 ;
	LPBYTE   lpMasks17 = byteMask + 24*17 ;
	LPBYTE   lpMasks18 = byteMask + 24*18 ;
	LPBYTE   lpMasks19 = byteMask + 24*19 ;
	LPBYTE   lpMasks20 = byteMask + 24*20 ;
	LPBYTE   lpMasks21 = byteMask + 24*21 ;
	LPBYTE   lpMasks22 = byteMask + 24*22 ;
	LPBYTE   lpMasks23 = byteMask + 24*23 ;

	int      nStartPos      = nMaskSize / 2          ;
	int      nStartPosSub1  = nStartPos - 1          ;
	int      nHeightScan    = nHeight - nStartPos    ;
	int      nWidthScan     = nWidth  - nStartPosSub1;
	int      nSumStart      = 0   ;
	int      nSumEnd        = 0   ;
	int      nBoundary      = 3   ;
	int      nBoundaryX2    = 6   ;
	int      nCount         = 0   ;

	register LPBYTE lpSrc   = NULL;
	register LPBYTE lpSrcUp = NULL;

	register LPBYTE lpCpySrc= NULL;
	register LPBYTE lpCpyEnd= NULL;

	int   a=0,b=0;
	int   c=0,d=0;
//
//   ab
//   cd
//

	int   itorX=0, itorY=0;


	lpSrc    = lpSrcGray + nWidth*nStartPos ;
	lpSrcUp  = lpSrc     - nWidth - nBoundary;
//	lpSrcDn2 = lpSrc     + nWidth - nBoundary;

	for( itorY=nStartPos ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=nStartPos;lpSrcUp+=nStartPos;
		for( itorX=nStartPos; itorX<nWidthScan ; itorX++ )
		{
			a = *(lpSrcUp);
			c = *(lpSrc  );
			if( abs(a-c)<nBarrier )  
			{
				lpSrc++;lpSrcUp++;
				continue;
			}

			b = *(lpSrcUp + 1 );
			if( abs(a-b)<nBarrier ) 
			{
				lpSrc++;lpSrcUp++;
				continue;
			}


			d = *(lpSrc + 1 );
			if( abs(c-d)<nBarrier ) 
			{
				lpSrc++;lpSrcUp++;
				continue;
			}
			if( abs(c-d)<nBarrier ) 
			{
				lpSrc++;lpSrcUp++;
				continue;
			}


			lpCpySrc = lpSrc - (nStartPos*nWidth) - nStartPos;

			iplmemcpy( lpMasks00, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks01, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks02, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks03, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks04, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks05, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks06, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks07, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks08, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks09, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks10, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks11, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks12, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks13, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks14, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks15, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks16, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks17, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks18, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks19, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks20, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks21, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks22, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
			iplmemcpy( lpMasks23, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;


			static int nImgCount = 0   ;
			TCHAR szPath[MAX_PATH]={0};
			_stprintf( szPath, _T("C:\\TestCheckResult\\TrainData\\%09d.bmp"), nCount++ );

			CxImage xImageorg;
			xImageorg.SetGrayPalette();
			xImageorg.CreateFromArray( byteMask, 24, 24, sizeof(BYTE)*8, 24, false );
			xImageorg.Save( szPath, CXIMAGE_SUPPORT_BMP);


			if(vOutPoints) vOutPoints->push_back(CIplPoint(itorX,itorY));

			lpSrc++;lpSrcUp++;
		}
		lpSrc+=nStartPosSub1;lpSrcUp+=nStartPosSub1;
	}

	return nCount;
}


BOOL IsGradation( const int& nPosX, const int& nPosY, const int& nWidth, const int& nHeight, const LPBYTE lpGraySrc, int nBarrier=5 )
{
	int nMask = 5;//mask size


	LPBYTE lpItor = NULL;
	lpItor = lpGraySrc + ( nPosY*nWidth ) + nPosX - (nMask/2);
 
	DWORD dwNegative = 0;
	DWORD dwPositive = 0;
	int   nIndex     = 0;
	int   nValue     = 0;
	while( nIndex < nMask-1 )
	{
		nValue = *lpItor - *(lpItor+1);
		if( nValue>  nBarrier ) dwPositive |= (0x01<<nIndex);
		if( nValue< -nBarrier ) dwNegative |= (0x01<<nIndex);
		nIndex++;
		lpItor++;
	}

	if( CheckGradationCode(dwPositive) ) return TRUE;
	if( CheckGradationCode(dwNegative) ) return TRUE;

	return FALSE;
}

#define _CHECK_DIR_RIGHT(pSrc, pCur, nGap, nBarrier)if( abs(*pCur - *(pCur+nGap) ) < nBarrier )continue;
#define _CHECK_DIFF( pS1, pS2, nBarrier)if( abs(*pS1 - *pS2 ) < nBarrier )continue;

//int GetEdgeBlockCandidate( const LPBYTE lpSrcGray, const int& nWidth, const int& nHeight, OUT LPVECTOR_POINT vOutPoints, BYTE nBarrier = 20 )
int GetEdgeBlockCandidate( const LPBYTE lpSrcGray, const int& nWidth, const int& nHeight, OUT LPVECTOR_RECT vOutRects, BYTE nBarrier = 20 )
{
	int      nMaskSize       = 24  ;
	int      nStartPos       = nMaskSize / 2          ;
	int      nStartPosSub1   = nStartPos - 1          ;
	int      nHeightScan     = nHeight - nStartPos    ;
	int      nWidthScan      = nWidth  - nStartPos    ;
	int      nGap            = 2;
	int      nHalfGap        = nGap/2;
	int      nGapPHalf       = nGap + nHalfGap;
	int      nScan           = 0;
	int      nWidthX2        = nWidth*4;
	int      nCount          = 0;
	int      nMinBlockSize   = 4;
	int      nHalfBarrier    = nBarrier/2;

	register LPBYTE lpSrc    = NULL;
	register LPBYTE lpSrcDn0 = NULL;
	register LPBYTE lpSrcDn1 = NULL;
	register LPBYTE lpSrcDn2 = NULL;
	register LPBYTE lpSrcDn3 = NULL;
	register LPBYTE lpSrcDnT = NULL;
	register LPBYTE lpSrcUpT = NULL;
	register LPBYTE lpSrcT   = NULL;
	register LPBYTE lpSrcO   = NULL;
	register LPBYTE lpItorEnd= NULL;
	register LPBYTE lpItorPos= NULL;
	register LPBYTE lpItorMax= NULL;




	int      nTop             = 0;
	int      nBottom          = 0;
	int      nRight           = 0;
	int      nRightTop        = 0;
	int      nRightBottom     = 0;
	int      nLeft            = 0;
	int      nLeftTop         = 0;
	int      nLeftBottom      = 0;

	int      nLocalMaxima     = 0;
	int      nMaxmaScanCount  = 0;
	int      nGrad            = 0;
	int      itorX = 0, itorY = 0;


	lpSrc = lpSrcGray + nWidth*nStartPos ;

	for( itorY=nStartPos ; itorY<nHeightScan ; itorY++ )
	{
		lpSrc+=nStartPos;
		for( itorX=nStartPos ; itorX<nWidthScan ; itorX++, lpSrc++ )
		{
			nTop            = 0;
			nBottom         = 0;
			nRight          = 0;
			nRightTop       = 0;
			nRightBottom    = 0;
			nLeft           = 0;
			nLeftTop        = 0;
			nLeftBottom     = 0;

			_CHECK_DIR_RIGHT( lpSrc, lpSrc, nGap, nBarrier );

			//Left Wall
			lpSrcDn0 = lpSrc    + nWidth;  _CHECK_DIR_RIGHT( lpSrc, lpSrcDn0, nGap, nBarrier );
			lpSrcDn1 = lpSrcDn0 + nWidth;  _CHECK_DIR_RIGHT( lpSrc, lpSrcDn1, nGap, nBarrier );
			lpSrcDn2 = lpSrcDn1 + nWidth;  _CHECK_DIR_RIGHT( lpSrc, lpSrcDn2, nGap, nBarrier );


//Scan_WallLeft_Left:
			lpSrcO = lpSrcT = lpSrc + nGap; //�� ���η� �̵�.
			nLeft  = itorX + nGap;
			if( nLeft > nWidthScan ) break;

			nTop    = itorY;
			nBottom = itorY+4;//4=nMinBlockSize; �ӵ��� ���� fix �������Ƿ� ���ڸ� �״�� �ڵ忡 ����


			lpSrcDnT= lpSrcDn2;
			nScan   = 0;
			while( nScan<nMaskSize )
			{
				lpSrcDnT = lpSrcDnT + nWidth;
				if( abs(*lpSrcDnT - *(lpSrcDnT+nGap) ) < nBarrier ) break;
				nScan ++;
			}

			nBottom = nBottom + nScan;
			if( nBottom > nHeightScan ) goto Find_Continue;//goto Scan_WallLeft_Right;

			//���ζ��ο��� local line maxima�� ã�� �̰��� ������ �������� Ȯ�� �� ���
			//local maxima x��ǥ�� nLeft�� ���ٸ�,...
			lpItorPos        = lpSrcO - nMinBlockSize;
			lpItorEnd        = lpSrcO + nMinBlockSize;
			nMaxmaScanCount  = nScan + (nBottom-nTop);
			nScan            = 0;
			while( nScan<nMaxmaScanCount )
			{
				lpItorMax    = lpSrcDnT = lpItorPos;
				nLocalMaxima = 0;
				while( lpSrcDnT<lpItorEnd )
				{
					nGrad = abs( *lpSrcDnT - *(lpSrcDnT+nGap) );
					if( nLocalMaxima<nGrad ){  nLocalMaxima = nGrad; lpItorMax = lpSrcDnT; }
					lpSrcDnT++;
				}
				if( abs( nMinBlockSize-int(lpItorEnd-lpItorMax)+nHalfGap ) >= nGap ) 
//				if( nMinBlockSize-int(lpItorEnd-lpItorMax)+nHalfGap == 0 ) 
					goto Find_Continue;//goto Scan_WallLeft_Right;

				lpItorPos += nWidth;
				lpItorEnd += nWidth;
				nScan     ++;
			}

//Scan_WallUp_Left:
			lpSrcUpT = lpSrcT - nWidthX2;
			nScan    = 0;
			while( nScan<nMaskSize )
			{
				//��������� ��ĭ��� �簢 ���� ��� ��� �ʿ�
				if( abs(*lpSrcT - *lpSrcUpT ) < nBarrier ) break;
				lpSrcT++; lpSrcUpT++; nScan++;
			}
			nRightTop = nLeft + (lpSrcT-lpSrc);

			if( nRightTop-nLeft < nMinBlockSize ) goto Scan_WallLeft_Right;

//Scan_WallDown_Left:
			lpSrcO   = lpSrcT = lpSrcDnT;
			lpSrcDnT = lpSrcT + nWidthX2;
			nScan    = 0;
			while( nScan<nMaskSize )
			{
				//��������� ��ĭ��� �簢 ���� ��� ��� �ʿ�
				if( abs(*lpSrcT - *lpSrcDnT ) < nHalfBarrier ) break;
				lpSrcT++; lpSrcDnT++; nScan++;
			}
			nRightBottom = nLeft + (lpSrcT-lpSrcO);
			if( nRightBottom-nLeft < nMinBlockSize ) goto Find_Continue;//goto Scan_WallLeft_Right;
			nRight = max( nRightTop, nRightBottom );

			if( IsGradation( nLeft, nTop, nWidth, nHeight, lpSrcGray) == TRUE )
				 goto Find_Continue;//goto Scan_WallLeft_Right;
			else goto Find_Success;

Scan_WallLeft_Right:
			lpSrcO = lpSrcT = lpSrc - nGap -1; //�� ���η� �̵�.
			nRight = itorX ;//- nGap - 1;
			if( nRight < 0 ) break;

			nTop    = itorY;
			nBottom = itorY+4;//4=nMinBlockSize; �ӵ��� ���� fix �������Ƿ� ���ڸ� �״�� �ڵ忡 ����


			lpSrcDnT= lpSrcDn2 - nGap -1;
			nScan   = 0;
			while( nScan<nMaskSize )
			{
				lpSrcDnT = lpSrcDnT + nWidth;
				if( abs(*lpSrcDnT - *(lpSrcDnT+nGap) ) < nBarrier ) break;
				nScan ++;
			}

			nBottom = nBottom + nScan;
			if( nBottom > nHeightScan ) goto Find_Continue;//goto Scan_WallLeft_Right;

			//���ζ��ο��� local line maxima�� ã�� �̰��� ������ �������� Ȯ�� �� ���
			//local maxima x��ǥ�� nLeft�� ���ٸ�,...
			lpItorPos        = lpSrcO - nMinBlockSize;
			lpItorEnd        = lpSrcO + nMinBlockSize;
			nMaxmaScanCount  = nScan + (nBottom-nTop);
			nScan            = 0;
			while( nScan<nMaxmaScanCount )
			{
				lpItorMax    = lpSrcDnT = lpItorPos;
				nLocalMaxima = 0;
				while( lpSrcDnT<lpItorEnd )
				{
					nGrad = abs( *lpSrcDnT - *(lpSrcDnT+nGap) );
					if( nLocalMaxima<nGrad ){  nLocalMaxima = nGrad; lpItorMax = lpSrcDnT; }
					lpSrcDnT++;
				}
				if( abs( nMinBlockSize-int(lpItorEnd-lpItorMax)-nGapPHalf ) >= nGap ) 
					goto Find_Continue;

				lpItorPos += nWidth;
				lpItorEnd += nWidth;
				nScan     ++;
			}

//Scan_WallUp_Right:
			lpSrcUpT = lpSrcT - nWidthX2;
			nScan    = 0;
			while( nScan<nMaskSize )
			{
				//��������� ��ĭ��� �簢 ���� ��� ��� �ʿ�
				if( abs(*lpSrcT - *lpSrcUpT ) < nBarrier ) break;
				lpSrcT--; lpSrcUpT--; nScan++;
			}
			nLeftTop = nRight - (lpSrc-lpSrcT);

			if( nRight-nLeftTop < nMinBlockSize ) goto Find_Continue;

//Scan_WallDown_Right:
			lpSrcO   = lpSrcT = lpSrcDnT;
			lpSrcDnT = lpSrcT + nWidthX2;
			nScan    = 0;
			while( nScan<nMaskSize )
			{
				//��������� ��ĭ��� �簢 ���� ��� ��� �ʿ�
				if( abs(*lpSrcT - *lpSrcDnT ) < nHalfBarrier ) break;
				lpSrcT--; lpSrcDnT--; nScan++;
			}
			nLeftBottom = nRight - (lpSrcO-lpSrcT);
			if( nRight-nLeftBottom < nMinBlockSize ) goto Find_Continue;
			//nRight-nLeftBottom�� ���̰� �ι谡 ������, *lpSrcT - *lpSrcDnT�� �̺� ��ȣ�� �ݴ�� , ������Ű�Ͻ�.
			//��⸦ Ȯ�� , �ӵ� ����� �ʿ�.
			nLeft = min( nLeftTop, nLeftBottom );

			if( IsGradation( nLeft, nTop, nWidth, nHeight, lpSrcGray) == TRUE )
				 goto Find_Continue;
			else goto Find_Success;

Find_Success:
			nCount ++;
			lpSrc += nGap;
			itorX += nGap;
			
//			if(vOutPoints) vOutPoints->push_back( CIplPoint(nLeft, nTop) );
			if(vOutRects ) vOutRects ->push_back( CIplRect (nLeft, nTop, nRight, nBottom) );
			continue;

Find_Continue:
			continue;
		}
		lpSrc+=nStartPos;
	}

	return nCount;
}

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

//by kiok ahn, 20080807
//���⼭ �Լ��� �׽�Ʈ �Ͻÿ�.
void CDemoDoc::TestFunc()
{

///////////////////////////////////////////////////////////////////////////////////////
//IPL BASE INFO �ӵ� ����
	int nSize   = image->GetWidth ()*image->GetHeight();
	int nWidth  = image->GetWidth ();
	int nHeight = image->GetHeight();
	COLORREF color ;

	LPBYTE lpBuffer = NULL;
	BYTE*  pGray    = NULL;
	switch( image->GetBpp() )
	{
	case 24:
		{
			BYTE* pBuf = image->GetBits();
			pGray      = new BYTE[nSize];
			ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());
			CxImage xImageLP;
			xImageLP.SetGrayPalette();
			xImageLP.CreateFromArray( pGray, image->GetWidth(),image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
			xImageLP.Save(_T("c:\\Gray.tif"), CXIMAGE_FORMAT_TIF);
			lpBuffer = pGray;
			color = RGB(255,0,0);
		}
		break;
	case 8:
		lpBuffer = image->GetBits();
		color = RGB(255,255,255);
		break;
	}

	CRGBCompoment m_rgbBlack(0,0,0);
	BYTE          m_byteNoiseLevel = 0;

	LPBYTE lpItor  = image->GetBits();
	LPBYTE lpEnd   = image->GetBits() + nSize*3 ;

	BYTE R=0,G=0,B=0;
	BYTE tmpR=0,tmpG=0,tmpB=0;
	for( ; lpItor<lpEnd ; )
	{
		tmpR = (*lpItor++)>>m_byteNoiseLevel;
		tmpG = (*lpItor++)>>m_byteNoiseLevel;
		tmpB = (*lpItor++)>>m_byteNoiseLevel;

		R = R | tmpR;
		G = G | tmpG;
		B = B | tmpB;
	}

	CRGBCompoment bgrVal  (R,G,B);
	LPBYTE lpStart = image->GetBits();
	CRGBCompoment bgrStart(*lpStart++,*lpStart++,*lpStart);

	if( bgrVal==bgrStart && bgrVal==m_rgbBlack ) 
	{
		INT k = 0;
	}

	BITMAPINFOHEADER		bih;
	iplmemzero( &bih, sizeof(BITMAPINFOHEADER) );
	bih.biBitCount = image->GetBpp() ;
	bih.biHeight   = nHeight  ;
	bih.biWidth    = nWidth   ;
	bih.biPlanes   = 1        ;
	bih.biSizeImage= nHeight*nWidth*(image->GetBpp()/8);
	bih.biSize     = sizeof(BITMAPINFOHEADER);


	CHistoRGB12bitBin iplHisto; 
	CIplFrameEx       iplFrame( nWidth, nHeight, image->GetBits(),  nSize*(image->GetBpp()/8) );
#ifdef _OPENMP
//	omp_lock_t lck;
//	omp_init_lock(&lck);
#endif
	DWORD t0 = timeGetTime();
	for( int i=0 ; i<1000 ; i++ )
	{
//		iplHisto.CalcHistFromBitmapRGB( image->GetBits(), &bih );
		iplFrame.ComputeBaseInfo( IPL_VCM_GRAY );
	}
	DWORD t1 = timeGetTime();

	CxImage xImageLP;
	xImageLP.SetGrayPalette();
	xImageLP.CreateFromArray( iplFrame.GetGrayBuffer(), image->GetWidth(), image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
	xImageLP.Save(_T("c:\\Gray.bmp"), CXIMAGE_FORMAT_BMP);


	CString szMsg;
	szMsg.Format(_T("average time = %d milli second"), (t1-t0));
	::AfxMessageBox(szMsg);


	if(pGray   ) delete[] pGray   ;
//IPL BASE INFO �ӵ� ����
///////////////////////////////////////////////////////////////////////////////////////

/*
///////////////////////////////////////////////////////////////////////////////////////
//Detect Interlace 
	int nSize = image->GetWidth()*image->GetHeight();

	LPBYTE lpBuffer = NULL;
	BYTE*  pGray    = NULL;
	switch( image->GetBpp() )
	{
	case 24:
		{
			BYTE* pBuf = image->GetBits();
			pGray      = new BYTE[nSize];
			ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());
			CxImage xImageLP;
			xImageLP.SetGrayPalette();
			xImageLP.CreateFromArray( pGray, image->GetWidth(),image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
			xImageLP.Save(_T("c:\\Gray.tif"), CXIMAGE_FORMAT_TIF);
			lpBuffer = pGray;
		}
		break;
	case 8:
		lpBuffer = image->GetBits();
		break;
	}

	BYTE* pLBPGray = new BYTE[nSize];
	memset( pLBPGray, 0, nSize ); 



	DWORD t1=timeGetTime();
//	ipl_GenerateLBPGray( lpBuffer, image->GetWidth(),image->GetHeight(), pLBPGray );
//	int nCount = BufferCountData(pLBPGray, nSize, 0x40);
	int nCount = ipl_GetLBPInterlaceCountGray( lpBuffer, image->GetWidth(),image->GetHeight() );

	//BOOL bRst = IsColorBars( pGray, nSize, image->GetWidth(),image->GetHeight() );
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("nCount=%d, %d milli second"), nCount, (t2-t1));
	::AfxMessageBox(szMsg);

	CxImage xImageLP;
	xImageLP.SetGrayPalette();
	xImageLP.CreateFromArray( pLBPGray, image->GetWidth(), image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
	xImageLP.Save(_T("c:\\LP.bmp"), CXIMAGE_FORMAT_BMP);

	if(pGray   ) delete[] pGray   ;
	if(pLBPGray) delete[] pLBPGray;

//Detect Interlace 
///////////////////////////////////////////////////////////////////////////////////////
*/



/*
	long kernel[] = {-1,-1,-1,-1,8,-1,-1,-1,-1};
	DWORD t1=timeGetTime();
	image->Filter(kernel, 3, -1, 255);
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("%d"),t2-t1);
	::AfxMessageBox(szMsgR;
*/
/*
	BYTE* pBuf    = image->GetBits();
	int nSize = image->GetWidth()*image->GetHeight();
	BYTE*  pGray      = new BYTE[nSize];
	WORD*  pDirection = new WORD[nSize];
	memset(pDirection, 0, sizeof(WORD)*nSize);

	ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());
	ipl_FilterSobelPhase3x3Gray(pGray,image->GetWidth(),image->GetHeight(),pDirection);


	BYTE* pBuf    = image->GetBits();
	int nSize = image->GetWidth()*image->GetHeight();
	BYTE*  pGray      = new BYTE[nSize];
	WORD*  pDirection = new WORD[nSize];
	memset(pDirection, 0, sizeof(WORD)*nSize);

	ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());
	ipl_FilterSobelPhase3x3Gray(pGray,image->GetWidth(),image->GetHeight(),pDirection);


	CHAR szTmp[4]={0};
	FILE* fp = _tfopen(_T("c:\\dvd.txt"),"a+");
	if(fp==NULL) return;
	LPWORD lpBuf = pDirection;
	for(int x, y=0 ; y<image->GetHeight() ; y++ )
	{
		for( x=0 ; x<image->GetWidth() ; x++ )
		{
			sprintf(szTmp,"%03d",(int)(*lpBuf++));
			fwrite( szTmp, sizeof(CHAR), 3, fp );
			//_tprintf( _T("%06d"), (int)(*lpBuf++), fp );
			//_tprintf( fp, _T("	"), fp);
			fwrite( "	", sizeof(CHAR), 1, fp );
		}
		fwrite( "\r\n", sizeof(CHAR), 2, fp );
	}

	fclose(fp);

	delete[] pGray                     ;
	delete[] pDirection                ;
*/

/*
////////////////////////////////////////////////////////////////////////////////////////
//apply filters test
	BYTE* pBuf    = image->GetBits();
	int nSize = image->GetWidth()*image->GetHeight();
	BYTE* pGray   = new BYTE[nSize];
	ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());


	DWORD dwApplyFlag = _IPL_FILTER_LOWPASS|_IPL_FILTER_SOBEL_MAG;
	IPLFILTERRESULT iplResult;
	iplResult.lpLowPass        = new BYTE[nSize];
	iplResult.lpSobelMagnitude = new BYTE[nSize];
	iplResult.lpSobelPhase     = new WORD[nSize];
	iplmemzero(iplResult.lpLowPass       , sizeof(BYTE)*nSize);
	iplmemzero(iplResult.lpSobelMagnitude, sizeof(BYTE)*nSize);
	iplmemzero(iplResult.lpSobelPhase    , sizeof(BYTE)*nSize);

	DWORD t1=timeGetTime();
	ipl_ApplyFilters3x3Gray(pGray,image->GetWidth(),image->GetHeight(),dwApplyFlag,&iplResult);
//	for(int i=0;i<1000;i++)
//	ipl_FilterLowPass3x3Gray       (pGray,image->GetWidth(),image->GetHeight(),iplResult.lpSobelMagnitude);
//	ipl_FilterSobelMagnitude3x3Gray(pGray,image->GetWidth(),image->GetHeight(),iplResult.lpSobelMagnitude);
	//ipl_FilterSobelPhase3x3Gray    (pGray,image->GetWidth(),image->GetHeight(),iplResult.lpSobelPhase    );
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("%d milli second"), (t2-t1));
	::AfxMessageBox(szMsg);

	CxImage xImageLP;
	xImageLP.SetGrayPalette();
	xImageLP.CreateFromArray( iplResult.lpLowPass, image->GetWidth(), image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
	xImageLP.Save(_T("c:\\LP.bmp"), CXIMAGE_FORMAT_BMP);

	CxImage xImageSM;
	xImageSM.SetGrayPalette();
	xImageSM.CreateFromArray( iplResult.lpSobelMagnitude, image->GetWidth(), image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
	xImageSM.Save(_T("c:\\SM.bmp"), CXIMAGE_FORMAT_BMP);

	delete[] pGray                     ;
	delete[] iplResult.lpLowPass       ; 
	delete[] iplResult.lpSobelMagnitude;
	delete[] iplResult.lpSobelPhase    ; 



//apply filters test
////////////////////////////////////////////////////////////////////////////////////////
*/


////////////////////////////////////////////////////////////////////////////////////////
//Sobel Direction
/*
	BYTE* pBuf    = image->GetBits();
	BYTE* pGray    = new BYTE[image->GetWidth()*image->GetHeight()];
	BYTE* pMag     = new BYTE[image->GetWidth()*image->GetHeight()];
	SHORT* pPhase  = new SHORT[image->GetWidth()*image->GetHeight()];
	ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());


	DWORD t1=timeGetTime();
	for(int i=0; i<1000 ; i++)
		ipl_FilterSobelMagNPhase3x3Gray(pGray,image->GetWidth(),image->GetHeight(),pMag,pPhase);
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("average time = %f milli second"), (double)(t2-t1)/1000.0);
	::AfxMessageBox(szMsg);

	bool bRst;
	CxImage xImage;
	xImage.SetGrayPalette();
	bRst = xImage.CreateFromArray( (BYTE*)pMag, image->GetWidth(), image->GetHeight(), sizeof(WORD)*8, image->GetWidth(), false );
	bRst = xImage.Save(_T("c:\\1.bmp"), CXIMAGE_FORMAT_BMP);
	delete[] pGray;
	delete[] pMag;
	delete[] pPhase;
*/
//Sobel Direction
////////////////////////////////////////////////////////////////////////////////////////



/*
////////////////////////////////////////////////////////////////////////////////////////
//Sobel Magnitude
	BYTE* pBuf    = image->GetBits();
	BYTE* pGray   = new BYTE[image->GetWidth()*image->GetHeight()];
	BYTE* pGraySM = new BYTE[image->GetWidth()*image->GetHeight()];
	ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());

	DWORD t1=timeGetTime();
	ipl_FilterSobelMagnitude3x3Gray(pGray,image->GetWidth(),image->GetHeight(),pGraySM);
	DWORD t2=timeGetTime();
	CString szMsg;
	szMsg.Format(_T("%d milli second"), (t2-t1));
	::AfxMessageBox(szMsg);
	CxImage xImage;
	xImage.SetGrayPalette();
	xImage.CreateFromArray( pGraySM, image->GetWidth(), image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
	xImage.Save(_T("c:\\1.bmp"), CXIMAGE_FORMAT_BMP);
	delete[] pGray;
	delete[] pGraySM;

//Sobel
////////////////////////////////////////////////////////////////////////////////////////
*/
}

void SaveEdgeblockinessBlock( const LPBYTE lpSrc, const int& nWidth, const int& nHeight, LPIPLRECT lpRect )
{
	int      nMaskSize      = 24  ;
	BYTE     byteMask[24*24]={0}  ;//openMP���� thread ����ŭ �����ؾ� ��.
	int      nNoiseLevel    = 5   ;

	LPBYTE   lpMasks00 = byteMask + 24* 0 ;
	LPBYTE   lpMasks01 = byteMask + 24* 1 ;
	LPBYTE   lpMasks02 = byteMask + 24* 2 ;
	LPBYTE   lpMasks03 = byteMask + 24* 3 ;
	LPBYTE   lpMasks04 = byteMask + 24* 4 ;
	LPBYTE   lpMasks05 = byteMask + 24* 5 ;
	LPBYTE   lpMasks06 = byteMask + 24* 6 ;
	LPBYTE   lpMasks07 = byteMask + 24* 7 ;
	LPBYTE   lpMasks08 = byteMask + 24* 8 ;
	LPBYTE   lpMasks09 = byteMask + 24* 9 ;
	LPBYTE   lpMasks10 = byteMask + 24*10 ;
	LPBYTE   lpMasks11 = byteMask + 24*11 ;
	LPBYTE   lpMasks12 = byteMask + 24*12 ;
	LPBYTE   lpMasks13 = byteMask + 24*13 ;
	LPBYTE   lpMasks14 = byteMask + 24*14 ;
	LPBYTE   lpMasks15 = byteMask + 24*15 ;
	LPBYTE   lpMasks16 = byteMask + 24*16 ;
	LPBYTE   lpMasks17 = byteMask + 24*17 ;
	LPBYTE   lpMasks18 = byteMask + 24*18 ;
	LPBYTE   lpMasks19 = byteMask + 24*19 ;
	LPBYTE   lpMasks20 = byteMask + 24*20 ;
	LPBYTE   lpMasks21 = byteMask + 24*21 ;
	LPBYTE   lpMasks22 = byteMask + 24*22 ;
	LPBYTE   lpMasks23 = byteMask + 24*23 ;

	LPBYTE lpCpySrc = lpSrc + (lpRect->top*nWidth) + lpRect->left;

	iplmemcpy( lpMasks00, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks01, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks02, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks03, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks04, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks05, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks06, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks07, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks08, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks09, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks10, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks11, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks12, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks13, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks14, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks15, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks16, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks17, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks18, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks19, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks20, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks21, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks22, lpCpySrc, sizeof(BYTE)*nMaskSize ); lpCpySrc += nWidth;
	iplmemcpy( lpMasks23, lpCpySrc, sizeof(BYTE)*nMaskSize ); 


	static int nImgCount = 0;
	TCHAR szPath[MAX_PATH]={0};
	_stprintf( szPath, _T("C:\\TestCheckResult\\EgdeBlockiness������\\Result\\%09d.bmp"), nImgCount++ );

	CxImage xImageorg;
	xImageorg.SetGrayPalette();
	xImageorg.CreateFromArray( byteMask, 24, 24, sizeof(BYTE)*8, 24, false );
	xImageorg.Save( szPath, CXIMAGE_SUPPORT_BMP);

}

void CDemoDoc::DetectEdgeBlock( )
{
/*
///////////////////////////////////////////////////////////////////////////////////////
//Detect EdgeBlockiness �ĺ����� ����
	int nSize = image->GetWidth()*image->GetHeight();
	COLORREF color ;

	LPBYTE lpBuffer = NULL;
	BYTE*  pGray    = NULL;
	switch( image->GetBpp() )
	{
	case 24:
		{
			BYTE* pBuf = image->GetBits();
			pGray      = new BYTE[nSize];
			ipl_RGBToGray(pGray,pBuf,image->GetWidth(),image->GetHeight());
			CxImage xImageLP;
			xImageLP.SetGrayPalette();
			xImageLP.CreateFromArray( pGray, image->GetWidth(),image->GetHeight(), sizeof(BYTE)*8, image->GetWidth(), false );
			xImageLP.Save(_T("c:\\Gray.tif"), CXIMAGE_FORMAT_TIF);
			lpBuffer = pGray;
			color = RGB(255,0,0);
		}
		break;
	case 8:
		lpBuffer = image->GetBits();
		color = RGB(255,255,255);
		break;
	}

	VECTOR_POINT vPoints;
	GetEdgeBlockCandidate7x7( lpBuffer, image->GetWidth(),image->GetHeight(), &vPoints );


	VECTOR_POINTItor itor = vPoints.begin();
	while( itor != vPoints.end())
	{
		LPIPLPOINT lpPoint = &(*itor);

		image->DrawLine( lpPoint->x-2,lpPoint->x+2,lpPoint->y  ,lpPoint->y,color  );
		image->DrawLine( lpPoint->x  ,lpPoint->x  ,lpPoint->y-2,lpPoint->y+2,color);
		itor++;
	}

	CString szMsg;
	szMsg.Format(_T("count = %d "), vPoints.size() );
	::AfxMessageBox(szMsg);


	if(pGray   ) delete[] pGray   ;
	return;
//Detect EdgeBlockiness �ĺ����� ����
///////////////////////////////////////////////////////////////////////////////////////
*/

}

#define _STRIPE_NONE_CHANGE_VALUE  8

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��� 1
inline void CheckLeftTmpLines( LPVECTOR_LINE lpvLines   ,
							   CIplLine*     plineTmp   ,
							   const int&    nTmpLength )
{
	int    nCurLength  = 0;
	int    nGapLength  = 0;
	int    nMaxLength  = 0;
	LONG*  pnP1X       = &(plineTmp->p1.x);
	LONG*  pnP2X       = &(plineTmp->p2.x);

	VECTOR_LINEItor itor = lpvLines->end(); itor--; 
	while( itor != lpvLines->begin())
	{
		LPIPLLINE lpLine = &(*itor);

		nCurLength = lpLine->p2.x - lpLine->p1.x;
		nMaxLength = max( nCurLength, nTmpLength );
		nGapLength = *pnP1X - lpLine->p2.x ;

		if( nMaxLength > nGapLength )
		{
			*pnP1X = lpLine->p1.x;
		}

		itor--;//����� ������� ��.
	}

	//vTmpLines.begin() �׸� ���� �˻�, ���ǿ� ���� 1���� �־�� ����.
	LPIPLLINE lpLine = &(*itor);

	nCurLength = lpLine->p2.x - lpLine->p1.x;
	nMaxLength = max( nCurLength, nTmpLength );
	nGapLength = *pnP1X - lpLine->p2.x ;

	if( nMaxLength > nGapLength )
	{
		*pnP1X = lpLine->p1.x;
	}

	lpvLines->clear();

}

//3x1 mask���� ���� �������� �˻�, ���� ������ ������ return FALSE
inline BOOL CheckVerticalCompnent(  const LPBYTE  lpSubtractImg   ,
									const int&    nWidth          ,
									const int&    nCurHeight      ,
									const BYTE&   byteLowBarrier  )
{
	LPBYTE lpItor      = lpSubtractImg + (nWidth*nCurHeight);
	LPBYTE lpItorEnd   = lpItor + nWidth;
	int    nValue      = 0;

	while( lpItor<lpItorEnd )
	{
		nValue = abs( int(*lpItor) - int(*(lpItor+2)) );
		if( nValue > byteLowBarrier )
			return FALSE;

		lpItor++;
	}
	return TRUE;
}


//�� ����� line�� �� �ϴ��� line�� �˻�
inline int CheckAndAddStripeLine( const LPBYTE  lpSubtractImg   ,
								  LPVECTOR_LINE lpvLines        ,
								  CIplLine*     plineCurrent    ,
								  const int&    nWidth          ,
								  const BYTE&   byteLowBarrier  )
{
	BOOL bResult  = FALSE;
	int  nCurYPos = plineCurrent->p1.y;

	bResult = bResult | CheckVerticalCompnent( lpSubtractImg, nWidth, nCurYPos + 3, byteLowBarrier );
	bResult = bResult | CheckVerticalCompnent( lpSubtractImg, nWidth, nCurYPos - 3, byteLowBarrier );

	if( bResult )
	{
		lpvLines->push_back( *plineCurrent );
		return 1;
	}

	return 0;
}
							    

inline int GetSingleHorizontalLine( const LPBYTE  lpBeforeImg     ,
									const LPBYTE  lpCurrentImg    ,
									const LPBYTE  lpSubtractImg   ,
								    const int&    nWidth          ,
									const int&    nCurHeight      ,
								    LPVECTOR_LINE lpvLines        ,
									const int&    nMinThreshold   ,
									const BYTE&   byteLowBarrier  ,
									const int&    nMinElementCount = 5 )
{
	LPBYTE lpItorUp    = lpSubtractImg + (nWidth*nCurHeight);
	LPBYTE lpItorDn    = lpItorUp      + (nWidth*2);
	int    itorX       = 0;
	int    nValue      = 0;
	int    nStartX     = 0;
	int    nEndX       = 0;
	int    nCurLength  = 0;
	int    nGapLength  = 0;
	int    nMaxLength  = 0;
	int    nTmpLength  = 0;
	int    nAddedCount = 0;


	VECTOR_LINE vTmpLines;

//	pLine->p1.y = nCurHeight;
//	pLine->p2.y = nCurHeight;

	CIplLine lineTmp(0,nCurHeight+1,0,nCurHeight+1);
	LONG*  pnP1X = &(lineTmp.p1.x);
	LONG*  pnP2X = &(lineTmp.p2.x);

	for( itorX=0 ; itorX<nWidth ; itorX++, lpItorUp++, lpItorDn++ )
	{
		nValue = abs( int(*lpItorDn) - int(*lpItorUp) );
		if( nValue < byteLowBarrier )
			continue;

		nStartX = itorX;
		while( nValue >= byteLowBarrier )
		{
			if( itorX >= nWidth )
				break;

			itorX++; lpItorUp++; lpItorDn++;
			nValue = abs( int(*lpItorDn) - int(*lpItorUp) );
		}

		nEndX      = itorX;
		nCurLength = nEndX - nStartX;

		if( nCurLength < nMinElementCount )
			continue;

		nTmpLength = *pnP2X - *pnP1X;

		if( nTmpLength == 0 )
		{
			*pnP1X = nStartX;
			*pnP2X = nEndX  ;
			continue;
		}

		nMaxLength = max( nCurLength, nTmpLength );
		nGapLength = nStartX - *pnP2X ;

//		line�� �Ÿ��� ����� ������ �Ÿ����� ��� merge.
//		����� ���̴� 1��, line�� 2�� �̹Ƿ� �� �� �� �������� ������ ����.
//		_____   __ : Merge
//		__   _____ : Merge
//		__     ___ : lineTmp�� ���ο� ������ ��ü. vTmpLines�� ����
		if( nMaxLength > nGapLength )
		{
			*pnP2X = nEndX  ;
		}
		else
		{
			if( nTmpLength > nMinThreshold )
			{
				if( vTmpLines.size()  )//�� line�� ���� ¥���� line�� merge
					CheckLeftTmpLines( &vTmpLines, &lineTmp, nTmpLength );

				lpvLines->push_back ( lineTmp );
				nAddedCount++;

			}
			else
			{
				vTmpLines.push_back( lineTmp );
			}


			*pnP1X = nStartX;
			*pnP2X = nEndX  ;
		}
	}

	nTmpLength = *pnP2X - *pnP1X;
	if( nTmpLength > nMinThreshold )
	{
		if( vTmpLines.size()  )//�� line�� ���� ¥���� line�� merge
			CheckLeftTmpLines( &vTmpLines, &lineTmp, nTmpLength );

		lpvLines->push_back ( lineTmp );
		nAddedCount++;
	}

	//�� line�� ���� ¥���� line�� merge
	if( nAddedCount == 0                  && 
		vTmpLines.size()                  &&
		nTmpLength > int(nMinThreshold/2)  )
	{
		CheckLeftTmpLines( &vTmpLines, &lineTmp, nTmpLength );

		nTmpLength = *pnP2X - *pnP1X;
		if( nTmpLength > nMinThreshold )
		{
			lpvLines->push_back ( lineTmp );
			nAddedCount++;
		}

	}

	return nAddedCount;
}

int	GetHorizontalLine( const LPBYTE  lpBeforeImg            ,
					   const LPBYTE  lpCurrentImg           ,
					   const LPBYTE  lpSubtractImg          ,
					   const int&    nWidth                 ,
					   const int&    nHeight                ,
					   LPVECTOR_LINE lpvLines               ,//OUT
					   BOOL*         pbIsCurrentFrame       ,
					   FLOAT         fMinLenghtRate   = 0.5f,
					   BYTE          byteHeighBarrier = 70  , 
					   BYTE          byteLowBarrier   = 10  , 
					   int           nSeedCount       = 10  )
{
	if( lpvLines    ==NULL || lpSubtractImg==NULL || lpBeforeImg==NULL ||
		lpCurrentImg==NULL || nWidth       < 1    || nHeight<1          )
		return 0;

	int    nThreshold    = int(nWidth*fMinLenghtRate);
	int    nMinThreshold = int(nWidth*0.1f);
	int    nStartPos     = 5;

	LPBYTE lpItorUp      = lpSubtractImg + (nWidth*nStartPos);
	LPBYTE lpItorDn      = lpItorUp      + (nWidth*2);
	int    nScanHeight   = nHeight       - nStartPos;
	int    itorX         = 0;
	int    itorY         = 0;
	int    itorSeed      = 0;
	int    nValue        = 0;


	for( itorY=nStartPos ; itorY<nScanHeight ; itorY++ )
	{
		for( itorX=0 ; itorX<nWidth ; itorX++, lpItorUp++, lpItorDn++ )
		{
			itorSeed = 0;;
			while( itorSeed<nSeedCount )
			{
				nValue = abs( int(*(lpItorDn+itorSeed)) - int(*(lpItorUp+itorSeed)) );
				if( nValue < byteHeighBarrier )
					break;

				itorSeed++;
			}
			if( itorSeed < nSeedCount )
				continue;

			GetSingleHorizontalLine( lpBeforeImg, lpCurrentImg, lpSubtractImg, 
				                     nWidth, itorY, lpvLines, nMinThreshold, byteLowBarrier );
			//Seed�� �ִ� line�� GetSingleHorizontalLine�Լ� ������ ��� ���簡 ����.
			lpItorUp = lpSubtractImg + (nWidth*(itorY+1));
			lpItorDn = lpItorUp      + (nWidth*2);
			break;
		}
	}

	return int( lpvLines->size() );
}
//��� 1
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
BOOL CheckFrameRelation( const LPBYTE lpData, const int& nSize )
{
	CHistoGray8bitBin m_histogramSG;
	m_histogramSG.CalcHistFromBuf( lpData, nSize );

	//ȭ���� 98%�� ��ȭ �������� �����Ǿ�� Stripe �˻� 
	UINT  nThreaholdCount = (UINT)(nSize*0.98f);
	BYTE  byteThreshold   = 0;
	UINT* pItorHisto      = m_histogramSG.GetBinData();
	UINT* pEndHisto       = pItorHisto + m_histogramSG.GetBinCount();
	UINT  nSum            = 0;

	while( pItorHisto<pEndHisto )
	{
		nSum += *pItorHisto;

		if(nSum>=nThreaholdCount) break;

		byteThreshold++;
		pItorHisto++;
	}

	if( byteThreshold >= _STRIPE_NONE_CHANGE_VALUE ) 
		return FALSE;

	return TRUE;
}
float  CDemoDoc::GetAvg(DWORD dwSum)
{
	if(dwSum == 0)
		return 0;
	dwSum /=64;
	return dwSum;
}
DWORD  CDemoDoc::GetSum(BYTE** lpBytePixelBlock, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	DWORD dwSum=0;
	for(unsigned int i=nHeightPoint;i<nHeightPoint+8;i=i++)
	{
		if(i== nHeight)
			break;
		for(unsigned int j=nWidthPoint;j<nWidthPoint+8;j=j++)
		{
			if(j== nWidth)
				break;
			dwSum+=lpBytePixelBlock[i][j]		;
		}
	}
	return dwSum;
}
DWORD  CDemoDoc::GetSum(LPBYTE lpBytePixelBlock, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	DWORD dwSum=0;
	LPBYTE lpItor = lpBytePixelBlock;
/*
	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
		for(unsigned int i=0;i<nHeightPoint;i=i++)
		{
			for(unsigned int j=0;j<nWidth;j=j++)
			{
				*lpItor++;
			}
		}
	}
	if(nWidthPoint!=0)
	{
		for(unsigned int j=0;j<nWidthPoint;j=j++)
		{
			*lpItor++;
		}
	}
	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		for(unsigned int k=0;k<8;k++)
		{
			dwSum+=*lpItor;
			*lpItor++;
		}
		for(unsigned int j=0;j<nWidth-(BLOCK_SIZE+1);j++)
		{
			*lpItor++;
		}
	}
	*/
	/*
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
		*/
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		for(unsigned int j=0;j<BLOCK_SIZE+1;j++)
		{
			dwSum+=*lpItor;
			*lpItor++;
		}
	}
	return dwSum;
}
DWORD  CDemoDoc::GetSum(LPBYTE lpLine1, LPBYTE lpLine2, LPBYTE lpLine3, LPBYTE lpLine4, LPBYTE lpLine5, LPBYTE lpLine6, LPBYTE lpLine7, LPBYTE lpLine8, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	DWORD dwSum=0;
	LPBYTE lpItorLine1 = lpLine1;
	LPBYTE lpItorLine2 = lpLine2;
	LPBYTE lpItorLine3 = lpLine3;
	LPBYTE lpItorLine4 = lpLine4;
	LPBYTE lpItorLine5 = lpLine5;
	LPBYTE lpItorLine6 = lpLine6;
	LPBYTE lpItorLine7 = lpLine7;
	LPBYTE lpItorLine8 = lpLine8;
	/*
	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
	for(unsigned int i=0;i<nHeightPoint;i=i++)
	{
	for(unsigned int j=0;j<nWidth;j=j++)
	{
	*lpItor++;
	}
	}
	}
	if(nWidthPoint!=0)
	{
	for(unsigned int j=0;j<nWidthPoint;j=j++)
	{
	*lpItor++;
	}
	}
	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
	for(unsigned int k=0;k<8;k++)
	{
	dwSum+=*lpItor;
	*lpItor++;
	}
	for(unsigned int j=0;j<nWidth-(BLOCK_SIZE+1);j++)
	{
	*lpItor++;
	}
	}
	*/
	/*
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
		*/
	for(unsigned int i=0;i<8;i=i++)
	{
		dwSum+=*lpItorLine1;
		*lpItorLine1++;
		dwSum+=*lpItorLine2;
		*lpItorLine2++;
		dwSum+=*lpItorLine3;
		*lpItorLine3++;
		dwSum+=*lpItorLine4;
		*lpItorLine4++;
		dwSum+=*lpItorLine5;
		*lpItorLine5++;
		dwSum+=*lpItorLine6;
		*lpItorLine6++;
		dwSum+=*lpItorLine7;
		*lpItorLine7++;
		dwSum+=*lpItorLine8;
		*lpItorLine8++;
	}
	return dwSum;
}
float  CDemoDoc::GetVariance(DWORD dwAvg, BYTE** lpBytePixelBlock, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwVar=0;
	if(dwAvg==0)
		return 0;

	for(unsigned int i=nHeightPoint;i<nHeightPoint+8;i=i++)
	{
		if(i== nHeight)
			break;
		for(unsigned int j=nWidthPoint;j<nWidthPoint+8;j=j++)
		{
			if(j== nWidth)
				break;
			dwVar += ((float)lpBytePixelBlock[i][j]		- dwAvg) * ((float)lpBytePixelBlock[i][j]		- dwAvg);
		}
	}
	if(dwVar !=0)
	{
		dwVar /=64;
		float fVar = sqrt(dwVar);
		return fVar;
	}
	else
		return 0;
}
float  CDemoDoc::GetVariance(DWORD dwAvg, LPBYTE lpBytePixelBlock, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwVar=0;
	if(dwAvg==0)
		return 0;
	DWORD dwSum=0;
	LPBYTE lpItor = lpBytePixelBlock;
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
/*
	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
		for(unsigned int i=0;i<nHeightPoint;i=i++)
		{
			for(unsigned int j=0;j<nWidth;j=j++)
			{
				*lpItor++;
			}
		}
	}
	if(nWidthPoint!=0)
	{
		for(unsigned int j=0;j<nWidthPoint;j=j++)
		{
			*lpItor++;
		}
	}
	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		for(unsigned int k=0;k<8;k++)
		{
			dwVar += ((float)*lpItor		- dwAvg) * ((float)*lpItor		- dwAvg);
			*lpItor++;
		}
		for(unsigned int j=0;j<nWidth-(BLOCK_SIZE+1);j++)
		{
			*lpItor++;
		}
	}
	*/
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		for(unsigned int j=0;j<BLOCK_SIZE+1;j++)
		{
			dwVar += ((float)*lpItor		- dwAvg) * ((float)*lpItor		- dwAvg);
			*lpItor++;
		}
	}
	if(dwVar !=0)
	{
		dwVar /=64;
		float fVar = sqrt(dwVar);
		return fVar;
	}
	else
		return 0;
}
float  CDemoDoc::GetVariance(DWORD dwAvg, LPBYTE lpLine1, LPBYTE lpLine2, LPBYTE lpLine3, LPBYTE lpLine4, LPBYTE lpLine5, LPBYTE lpLine6, LPBYTE lpLine7, LPBYTE lpLine8, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwVar=0;
	if(dwAvg==0)
		return 0;
	DWORD dwSum=0;
	LPBYTE lpItorLine1 = lpLine1;
	LPBYTE lpItorLine2 = lpLine2;
	LPBYTE lpItorLine3 = lpLine3;
	LPBYTE lpItorLine4 = lpLine4;
	LPBYTE lpItorLine5 = lpLine5;
	LPBYTE lpItorLine6 = lpLine6;
	LPBYTE lpItorLine7 = lpLine7;
	LPBYTE lpItorLine8 = lpLine8;

	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		dwVar += ((float)*lpLine1		- dwAvg) * ((float)*lpLine1		- dwAvg);
		*lpLine1++;
		dwVar += ((float)*lpLine2		- dwAvg) * ((float)*lpLine2		- dwAvg);
		*lpLine2++;
		dwVar += ((float)*lpLine3		- dwAvg) * ((float)*lpLine3		- dwAvg);
		*lpLine3++;
		dwVar += ((float)*lpLine4		- dwAvg) * ((float)*lpLine4		- dwAvg);
		*lpLine4++;
		dwVar += ((float)*lpLine5		- dwAvg) * ((float)*lpLine5		- dwAvg);
		*lpLine5++;
		dwVar += ((float)*lpLine6		- dwAvg) * ((float)*lpLine6		- dwAvg);
		*lpLine6++;
		dwVar += ((float)*lpLine7		- dwAvg) * ((float)*lpLine7		- dwAvg);
		*lpLine7++;
		dwVar += ((float)*lpLine8		- dwAvg) * ((float)*lpLine8		- dwAvg);
		*lpLine8++;
	}
	if(dwVar !=0)
	{
		dwVar /=64;
		float fVar = sqrt(dwVar);
		return fVar;
	}
	else
		return 0;
}
float  CDemoDoc::GetRightBoundaryPixel(DWORD dwVar, BYTE** lpBytePixelBlock, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwBoundary=0;
	if(dwVar==0)
		return 0;
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
	for(unsigned int i=nHeightPoint;i<nHeightPoint+8;i++)
	{
		if(nWidthPoint+8 >= nWidth || i== nHeight)
		//if(nWidthPoint+8 >= nWidth )
			break;
		dwBoundary += GetAbsolute((float)lpBytePixelBlock[i][nWidthPoint+7] - (float)lpBytePixelBlock[i][nWidthPoint+8]);
	}
	dwBoundary /=8;
	if(dwBoundary <3)
		return 0;

	return dwBoundary;
}
float  CDemoDoc::GetRightBoundaryPixel(DWORD dwVar, LPBYTE lpBytePixelBlock, LPBYTE lpRightData, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwBoundary=0;
	if(dwVar==0)
		return 0;
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
	LPBYTE lpItor = lpBytePixelBlock;
	LPBYTE lpLineData =lpRightData;

	if(nWidthPoint+8 >= nWidth)
		return 0;
	if(nWidthPoint==0)
		return 0;

	/*
	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
		for(unsigned int i=0;i<nHeightPoint;i=i++)
		{
			for(unsigned int j=0;j<nWidth;j=j++)
			{
				*lpItor++;
			}
		}
	}
	if(nWidthPoint!=0)
	{
		for(unsigned int j=0;j<nWidthPoint;j=j++)
		{
			*lpItor++;
		}
	}
	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		for(unsigned int k=0;k<7;k++)
		{
			*lpItor++;
		}
		lpLineTemp = lpItor++;
		dwBoundary += GetAbsolute((float)*lpLineTemp - (float)*lpItor);
		for(unsigned int j=0;j<nWidth-(BLOCK_SIZE+1);j++)
		{
			*lpItor++;
		}
	}
	*/
	//�� 8�� 7�����;� �̵��Ͽ�, LineData�� ���̸� ���Ѵ�.
	for(unsigned int i=0;i<BLOCK_SIZE+1;i++)
	{
		*lpItor++;
		*lpItor++;
		*lpItor++;
		*lpItor++;
		*lpItor++;
		*lpItor++;
		*lpItor++;
		dwBoundary += GetAbsolute((float)*lpItor - (float)*lpLineData);
		*lpItor++;
		*lpLineData++;
	}
	dwBoundary /=8;
	if(dwBoundary <3)
		return 0;

	return dwBoundary;
}
float  CDemoDoc::GetRightBoundaryPixel(DWORD dwVar, LPBYTE lpLine1, LPBYTE lpLine2, LPBYTE lpLine3, LPBYTE lpLine4, LPBYTE lpLine5, LPBYTE lpLine6, LPBYTE lpLine7, LPBYTE lpLine8, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwBoundary=0;
	if(dwVar==0)
		return 0;
	/*
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
		*/
	

	if(nWidthPoint+8 >= nWidth)
		return 0;
	
	LPBYTE lpLineData1 	= 	lpLine1+7;
	LPBYTE lpLineData2 	= 	lpLine2+7;
	LPBYTE lpLineData3 	= 	lpLine3+7;
	LPBYTE lpLineData4 	= 	lpLine4+7;
	LPBYTE lpLineData5 	= 	lpLine5+7;
	LPBYTE lpLineData6 	= 	lpLine6+7;
	LPBYTE lpLineData7 	= 	lpLine7+7;
	LPBYTE lpLineData8 	= 	lpLine8+7;


	LPBYTE lpRightData1 =	lpLine1+8;
	LPBYTE lpRightData2 =	lpLine2+8;
	LPBYTE lpRightData3 =	lpLine3+8;
	LPBYTE lpRightData4 =	lpLine4+8;
	LPBYTE lpRightData5 =	lpLine5+8;
	LPBYTE lpRightData6 =	lpLine6+8;
	LPBYTE lpRightData7 =	lpLine7+8;
	LPBYTE lpRightData8 =	lpLine8+8;
	/*
	//�� 8�� 7�����;� �̵��Ͽ�, LineData�� ���̸� ���Ѵ�.
	for(unsigned int i=0;i<BLOCK_SIZE;i++)
	{
		*lpItorLine1++;
		*lpItorLine2++;
		*lpItorLine3++;
		*lpItorLine4++;
		*lpItorLine5++;
		*lpItorLine6++;
		*lpItorLine7++;
		*lpItorLine8++;
	}
	*/
	dwBoundary += GetAbsolute((float)*lpLineData1 - (float)*lpRightData1);
	
	dwBoundary += GetAbsolute((float)*lpLineData2 - (float)*lpRightData2);
	
	dwBoundary += GetAbsolute((float)*lpLineData3 - (float)*lpRightData3);
	
	dwBoundary += GetAbsolute((float)*lpLineData4 - (float)*lpRightData4);
	
	dwBoundary += GetAbsolute((float)*lpLineData5 - (float)*lpRightData5);
	
	dwBoundary += GetAbsolute((float)*lpLineData6 - (float)*lpRightData6);
	
	dwBoundary += GetAbsolute((float)*lpLineData7 - (float)*lpRightData7);
	
	dwBoundary += GetAbsolute((float)*lpLineData8 - (float)*lpRightData8);
	dwBoundary /=8;
	
	if(dwBoundary <10)
		return 0;

	return dwBoundary;
}
float  CDemoDoc::GetBottomBoundaryPixel(DWORD dwVar, BYTE** lpBytePixelBlock, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwBoundary=0;
	//if(dwVar==0)
	//	return 0;
	for(unsigned int i=nWidthPoint;i<nWidthPoint+8;i++)
	{
		if(nHeightPoint+8 >= nHeight || i == nWidth)
		//if(nHeightPoint+8 >= nHeight )
			break;
		if(nHeightPoint == nHeight)
			break;
		if(nHeightPoint==0)
			break;
		dwBoundary += GetAbsolute((float)lpBytePixelBlock[(nHeight-1)-nHeightPoint][i] - (float)lpBytePixelBlock[(nHeight-1)-nHeightPoint-1][i]);
	}
	dwBoundary /=8;
	if(dwBoundary <3)
		return 0;

	return dwBoundary;
}
/*
float  CDemoDoc::GetBottomBoundaryPixel(DWORD dwVar, LPBYTE lpBytePixelBlock, LPBYTE lpBottomData, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwBoundary=0;
	if(dwVar==0)
		return 0;
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;

	LPBYTE lpItor = lpBytePixelBlock;
	LPBYTE lpLineData =lpBottomData;

	if(nHeightPoint+8 >= nHeight)
		return 0;

/*
	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
		for(unsigned int i=0;i<nHeightPoint;i=i++)
		{
			for(unsigned int j=0;j<nWidth;j=j++)
			{
				*lpItor++;
			}
		}
	}
	if(nWidthPoint!=0)
	{
		for(unsigned int j=0;j<nWidthPoint;j=j++)
		{
			*lpItor++;
		}
	}
	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+1;i=i++)
	{
		//�������ٷ� �̵��Ѵ�.
		if(i==0)
		{
			for(unsigned int j=0;j<BLOCK_SIZE;j++)
			{
				*lpItor++;
			}
		}
		//���������� �����͸� �ӽ������ͺ����� �����ϰ�, �� �Ʒ��ٷ� �̵��Ͽ� ���� ����, �ӽ������ͺ����� �ٽ� �ȱ��.
		lpLineTemp = lpItor;
		for(unsigned int j=0;j<nWidth;j++)
		{
			*lpItor++;
		}
		dwBoundary += GetAbsolute((float)*lpLineTemp - (float)*lpItor);
		lpItor = lpLineTemp;
		*lpItor++;

	}
	*/
/*
	//�� �������ٱ��� �̵��Ͽ�,56��° �� 8�� LineData�� ���Ѵ�.
	for(unsigned int i=0;i<56;i++)
	{
		*lpItor++;
	}
	for(unsigned int i=0;i<8;i++)
	{
		dwBoundary += GetAbsolute((float)*lpItor - (float)*lpLineData);
		*lpItor++;
		*lpLineData++;
	}
	dwBoundary /=8;

	if(dwBoundary <3)
		return 0;

	return dwBoundary;
}
*/
float  CDemoDoc::GetBottomBoundaryPixel(DWORD dwVar, LPBYTE lpLine8, LPBYTE lpBottomData, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	float dwBoundary=0;
	if(dwVar==0)
		return 0;
	/*
	if(nWidthPoint==0 || nHeightPoint == 0)
		return 0;
		*/
	LPBYTE lpLineData =lpBottomData;
	LPBYTE lpItorLine8 = lpLine8;

	if(nHeightPoint+8 >= nHeight)
		return 0;

	//�� �������ٱ��� �̵��Ͽ�,56��° �� 8�� LineData�� ���Ѵ�.
	for(unsigned int i=0;i<8;i++)
	{
		dwBoundary += GetAbsolute((float)*lpItorLine8 - (float)*lpLineData);
		*lpItorLine8++;
		*lpLineData++;
	}
	dwBoundary /=8;

	if(dwBoundary <10 )
		return 0;

	return dwBoundary;
}
float CDemoDoc::GetAbsolute(float nInput)
{
	if(nInput <0)
		nInput*=-1;

	return nInput;
}
void CDemoDoc::GetBlockData(LPBYTE lpBytePixelBlock, BYTE **lpOutBlockByte, BYTE **lpRightData,BYTE **lpBottomData, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{
	DWORD dwSum			=	0					;
	LPBYTE lpItor		=	lpBytePixelBlock	;
	LPBYTE lpOutItor	=	*lpOutBlockByte		;
	LPBYTE lpRightItor	=	*lpRightData		;
	LPBYTE lpBottomItor =	*lpBottomData		;

	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
		for(unsigned int i=0;i<nHeightPoint;i=i++)
		{
			for(unsigned int j=0;j<nWidth;j=j++)
			{
				*lpItor++;
			}
		}
	}
	if(nWidthPoint!=0)
	{
		for(unsigned int j=0;j<nWidthPoint;j=j++)
		{
			*lpItor++;
		}
	}
	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+2;i=i++)
	{
		for(unsigned int k=0;k<9;k++)
		{
			if(k==8)
			{
				//k�� 8�� ���, 0~7���� Right���ȭ�Ұ�������, ���ȭ�ҹ��ۿ� �����Ѵ�.
				*lpRightItor = *lpItor;
				*lpRightItor++;
			}
			else if(i==8)
			{
				//i�� 8�ϰ��, 0~7���� Bottom���ȭ�Ұ�������, ���ȭ�ҹ��ۿ� �����Ѵ�.
				*lpBottomItor = *lpItor;
				*lpBottomItor++;
				*lpItor++;
			}
			else if(k!=8 || i!=8)
			{
				*lpOutItor = *lpItor;
				*lpItor++;
				*lpOutItor++;
			}
		}
		for(unsigned int j=0;j<nWidth-(BLOCK_SIZE+1);j++)
		{
			*lpItor++;
		}
	}

}
void CDemoDoc::GetBlockData( LPBYTE lpBytePixelBlock, LPBYTE *lpLine1, LPBYTE *lpLine2, LPBYTE *lpLine3, LPBYTE *lpLine4, LPBYTE *lpLine5, LPBYTE *lpLine6, LPBYTE *lpLine7, LPBYTE *lpLine8, BYTE **lpRightData,BYTE **lpBottomData, unsigned int nHeightPoint, unsigned int nWidthPoint, unsigned int nHeight, unsigned int nWidth)
{

	DWORD dwSum			=	0					;
	LPBYTE lpItor		=	lpBytePixelBlock	;
	LPBYTE lpTemp		=	lpBytePixelBlock	;
	LPBYTE lpRightItor	=	*lpRightData		;
	LPBYTE lpBottomItor =	*lpBottomData		;
	LPBYTE lpItorLine1  =   *lpLine1			;
	LPBYTE lpItorLine2  =   *lpLine2			;
	LPBYTE lpItorLine3  =   *lpLine3			;
	LPBYTE lpItorLine4  =   *lpLine4			;
	LPBYTE lpItorLine5  =   *lpLine5			;
	LPBYTE lpItorLine6  =   *lpLine6			;
	LPBYTE lpItorLine7  =   *lpLine7			;
	LPBYTE lpItorLine8  =   *lpLine8			;

	//nHeightPoint����, �� �̵�, nWidthPoint����  ������ �̵�
	if(nHeightPoint!=0)
	{
		lpItor = lpItor+(nHeightPoint*nWidth);
	}
	if(nWidthPoint!=0)
	{
		lpItor = lpItor+(nWidthPoint);
	}

	//ù�� 8�ȼ��� ���� ��������, 8������, ���̵��� �ϸ�, �ȼ����� ���ذ���.
	for(unsigned int i=0;i<BLOCK_SIZE+2;i=i++)
	{
		for(unsigned int k=0;k<9;k++)
		{
			if(k==8)
			{
				//k�� 8�� ���, 0~7���� Right���ȭ�Ұ�������, ���ȭ�ҹ��ۿ� �����Ѵ�.
				*lpRightItor = *lpItor;
				*lpRightItor++;
			}
			else if(i==8)
			{
				//i�� 8�ϰ��, 0~7���� Bottom���ȭ�Ұ�������, ���ȭ�ҹ��ۿ� �����Ѵ�.
				*lpBottomItor = *lpItor;
				*lpBottomItor++;
				*lpItor++;
			}
			
			else
			{
				//8x8��Ͽ��� ù��° �ȼ��� �����͸� �ѱ�
				switch(i)
				{
				case 0:
					*lpItorLine1 = *lpItor;
					*lpItorLine1++;
					break;
				case 1:
					*lpItorLine2 = *lpItor;
					*lpItorLine2++;
					break;
				case 2:
					*lpItorLine3 = *lpItor;
					*lpItorLine3++;
					break;
				case 3:
					*lpItorLine4 = *lpItor;
					*lpItorLine4++;
					break;
				case 4:
					*lpItorLine5 = *lpItor;
					*lpItorLine5++;
					break;
				case 5:
					*lpItorLine6 = *lpItor;
					*lpItorLine6++;
					break;
				case 6:
					*lpItorLine7 = *lpItor;
					*lpItorLine7++;
					break;
				case 7:
					*lpItorLine8 = *lpItor;
					*lpItorLine8++;
					break;
				}
				*lpItor++;
			}
			
		}

		lpItor= lpItor+nWidth-(BLOCK_SIZE+1);
	}
}
void CDemoDoc::DetectBlockiness( const LPBYTE lpData, const int& nWidth, const int& nHeight, LPVECTOR_LINE lpvecotrLine )
{
	LPBYTE pBuf = lpData;
	
	BYTE** m_bCurFrame = new BYTE *[nHeight];
	for(unsigned int i=0;i<nHeight;i++)
	{
		m_bCurFrame[i] = new BYTE[nWidth];
	}
	for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			m_bCurFrame[i][j] = 0;
		}
	}
	BYTE *bCurBlockData = new BYTE[64];
	BYTE *bRightData = new BYTE[8];
	BYTE *bBottomData = new BYTE[8];
	for(int i=0;i<64;i++)
	{
		bCurBlockData[i] = 0;
	}
	for(int i=0;i<8;i++)
	{
		bRightData[i]	= 0;
		bBottomData[i]	= 0;
	}
	
	//LPBYTE ������ 2���� �迭�� ��ȯ
	for(int i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			BYTE curPixel		= *pBuf++		;
			m_bCurFrame[i][j]	= curPixel		;
		}
	}
	
	pBuf = lpData;

	DWORD dwBlockSum	= 0				;
	DWORD dwBlockSum1	= 0				;
	UINT  nBlockCount	= 0				;
	UINT  nBlockCount1	= 0				;

	INT nWidthStart  = BLOCK_SIZE + 1;
	INT nHeightStart = BLOCK_SIZE + 1;
	INT nWidthEnd    = nWidth-(BLOCK_SIZE+1) ;
	INT nHeightEnd   = nHeight-(BLOCK_SIZE+1);

	//INT nScanLine    = nHeightStart*(nWidth);
	INT nScanLine    = (nWidth);
	/*
	LPBYTE lpLine1 = pBuf + nScanLine + nWidthStart;
	LPBYTE lpLine2 = lpLine1   + nScanLine + nWidthStart;
	LPBYTE lpLine3 = lpLine2   + nScanLine + nWidthStart;
	LPBYTE lpLine4 = lpLine3   + nScanLine + nWidthStart;
	LPBYTE lpLine5 = lpLine4   + nScanLine + nWidthStart;
	LPBYTE lpLine6 = lpLine5   + nScanLine + nWidthStart;
	LPBYTE lpLine7 = lpLine6   + nScanLine + nWidthStart;
	LPBYTE lpLine8 = lpLine7   + nScanLine + nWidthStart;
	LPBYTE lpBottomData = lpLine8  + nScanLine + nWidthStart;
	*/
	pBuf				= pBuf +(nWidth*8);
	LPBYTE lpLine1 		= pBuf			+ nWidthStart	;
	LPBYTE lpLine2 		= lpLine1  		+ nScanLine		;
	LPBYTE lpLine3 		= lpLine2  		+ nScanLine		;
	LPBYTE lpLine4 		= lpLine3  		+ nScanLine		;
	LPBYTE lpLine5 		= lpLine4  		+ nScanLine		;
	LPBYTE lpLine6 		= lpLine5  		+ nScanLine		;
	LPBYTE lpLine7 		= lpLine6  		+ nScanLine		;
	LPBYTE lpLine8 		= lpLine7  		+ nScanLine		;
	LPBYTE lpBottomData = lpLine8		+ nScanLine		;

		//��ü�ػ󵵸� ���� 8x8 ������, ȭ�Ұ��� ����� ���ϰ�, �л��� ���Ѵ�.
		for(unsigned int i=nHeightStart ; i<nHeightEnd ; i=i+(BLOCK_SIZE+1) )
		{
			if(i == nHeight)
				break;
			if(i+8 >= nHeight)
				break;
			for(unsigned int j=nWidthStart ; j<nWidthEnd ; j=j+(BLOCK_SIZE+1) )
			{
				if(j== nWidth)
					break;
				if(j+8 >= nWidth)
					break;
	/*
				LPBYTE lpLine1=new BYTE[8];
				LPBYTE lpLine2=new BYTE[8];
				LPBYTE lpLine3=new BYTE[8];
				LPBYTE lpLine4=new BYTE[8];
				LPBYTE lpLine5=new BYTE[8];
				LPBYTE lpLine6=new BYTE[8];
				LPBYTE lpLine7=new BYTE[8];
				LPBYTE lpLine8=new BYTE[8];
				for(unsigned int k=0;k<8;k++)
				{
					lpLine1[k]=0;
					lpLine2[k]=0;
					lpLine3[k]=0;
					lpLine4[k]=0;
					lpLine5[k]=0;
					lpLine6[k]=0;
					lpLine7[k]=0;
					lpLine8[k]=0;
				}
				*/
				//GetBlockData(lpData, &bCurBlockData, &bRightData, &bBottomData, i, j, nHeight, nWidth);
				//GetBlockData(pBuf, &lpLine1,&lpLine2,&lpLine3,&lpLine4,&lpLine5,&lpLine6,&lpLine7,&lpLine8, &bRightData, &bBottomData, i, j, nHeight, nWidth);
				//dwBlockSum	=	GetSum(bCurBlockData,i,j,nHeight, nWidth);
				dwBlockSum1 =   GetSum(lpLine1,lpLine2,lpLine3,lpLine4,lpLine5,lpLine6,lpLine7,lpLine8,i,j,nHeight, nWidth);

				//���� ����� ���Ѵ�.
				//float dwBlockAvg = GetAvg(dwBlockSum);
				float dwBlockAvg1 = GetAvg(dwBlockSum1);

				//�� ���� �л��� ���Ѵ�.
				//float dwBlockVar = GetVariance(dwBlockAvg,m_bCurFrame,i,j,nHeight, nWidth);
				//float dwBlockVar = GetVariance(dwBlockAvg1,bCurBlockData,i,j,nHeight, nWidth);
				float dwBlockVar1 = GetVariance(dwBlockAvg1,lpLine1,lpLine2,lpLine3,lpLine4,lpLine5,lpLine6,lpLine7,lpLine8,i,j,nHeight, nWidth);

				//���� ���ȭ�� |���̰�| �� /8
				//float dwRightBoundary  = GetRightBoundaryPixel(dwBlockVar,m_bCurFrame,i,j, nHeight, nWidth);
				float dwRightBoundary1  = GetRightBoundaryPixel(dwBlockVar1,lpLine1,lpLine2,lpLine3,lpLine4,lpLine5,lpLine6,lpLine7,lpLine8,i,j, nHeight, nWidth);
				//�ϴ� ���ȭ�� |���̰�| �� /8
				//float dwBottomBoundary = GetBottomBoundaryPixel(dwBlockVar,m_bCurFrame,i,j, nHeight, nWidth);
				//�ϴ� ���ȭ�� |���̰�| �� /8
				float dwBottomBoundary1 = GetBottomBoundaryPixel(dwBlockVar1,lpLine8,lpBottomData,i,j, nHeight, nWidth);
	/*
				//���ȭ�� ���̰��� �л꺸�� Ŭ ���, ���ȭ ������ ��Ÿ�������� ����
				if( dwRightBoundary >  (dwBlockVar))
				{
					//Add Line
					lpvecotrLine->push_back( CIplLine( j+BLOCK_SIZE,nHeight - i, j+BLOCK_SIZE,nHeight - i+BLOCK_SIZE ) );

					//iplmemzero(m_CurFrameData,(nWidth*nHeight*4));
					//memcpy(m_CurFrameData,image->GetBits(),nSize);
					//CheckBlockiness(m_CurFrameData, nSize, nHeight, nWidth, i, j, BLOCK_TYPE_RIGHT);
					nBlockCount++;

				}
				
				if( dwBottomBoundary >  (dwBlockVar))
				{
					//Add Line
					lpvecotrLine->push_back( CIplLine( j,nHeight - i, j+BLOCK_SIZE,nHeight - i ) );

					//iplmemzero(m_CurFrameData,(nWidth*nHeight*4));
					//memcpy(m_CurFrameData,image->GetBits(),nSize);
					//CheckBlockiness(m_CurFrameData,nSize, nHeight, nWidth, i, j, BLOCK_TYPE_BOTTOM);
					nBlockCount++;

				}
	*/
				
				//���ȭ�� ���̰��� �л꺸�� Ŭ ���, ���ȭ ������ ��Ÿ�������� ����
				if( dwRightBoundary1 >  (dwBlockVar1))
				{
					//Add Line
					lpvecotrLine->push_back( CIplLine( j+BLOCK_SIZE, i, j+BLOCK_SIZE, i+BLOCK_SIZE ) );

					//iplmemzero(m_CurFrameData,(nWidth*nHeight*4));
					//memcpy(m_CurFrameData,image->GetBits(),nSize);
					//CheckBlockiness(m_CurFrameData, nSize, nHeight, nWidth, i, j, BLOCK_TYPE_RIGHT);
					nBlockCount1++;

				}

				if( dwBottomBoundary1 >  (dwBlockVar1))
				{
					//Add Line
					lpvecotrLine->push_back( CIplLine( j, i, j+BLOCK_SIZE, i ) );

					//iplmemzero(m_CurFrameData,(nWidth*nHeight*4));
					//memcpy(m_CurFrameData,image->GetBits(),nSize);
					//CheckBlockiness(m_CurFrameData,nSize, nHeight, nWidth, i, j, BLOCK_TYPE_BOTTOM);
					nBlockCount1++;

				}
				lpLine1 += BLOCK_SIZE+1;
				lpLine2 += BLOCK_SIZE+1;
				lpLine3 += BLOCK_SIZE+1;
				lpLine4 += BLOCK_SIZE+1;
				lpLine5 += BLOCK_SIZE+1;
				lpLine6 += BLOCK_SIZE+1;
				lpLine7 += BLOCK_SIZE+1;
				lpLine8 += BLOCK_SIZE+1;
				lpBottomData += BLOCK_SIZE+1;
				
			}
			lpLine1 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine2 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine3 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine4 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine5 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine6 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine7 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpLine8 += (nScanLine*7)+(2*(BLOCK_SIZE+1));
			lpBottomData += (nScanLine*7)+(2*(BLOCK_SIZE+1));
		}
	
	float fCheckBlockiness = ((float)(nBlockCount1 * 100) / (float)(nHeight*nWidth));
	
	
	CString szMsg;
	szMsg.Format(_T("Block Count	=	%d\r\nBlock Ratio	=	%f"),nBlockCount1,fCheckBlockiness);
	//szMsg.Format(_T("Block Count	=	0\r\nBlock Ratio	=	0"));
	::AfxMessageBox(szMsg);

}

void CDemoDoc::DetectBlockiness( )
{
	int nSize   = image->GetWidth ()*image->GetHeight()*3;
	int nWidth  = image->GetWidth ();
	int nHeight = image->GetHeight();



	COLORREF color ;

	LPBYTE lpBuffer01 = NULL;
	BYTE*  pGray01    = NULL;
	BYTE*  pBuf		  = NULL;
	switch( image->GetBpp() )
	{
	case 24:
		{
			pBuf = image->GetBits();
			pGray01    = new BYTE[nSize];
			ipl_RGBToGray(pGray01,pBuf,nWidth, nHeight);
			lpBuffer01 = pGray01;
			//CxImage imgGray;
			//imgGray.CreateFromArray( pGray01, nWidth, nHeight, 8, nWidth, FALSE );
			//image->Transfer( imgGray );
			color = RGB(255,255,255);
		}
		break;
	case 8:
		lpBuffer01 = image->GetBits();
		color = RGB(255,255,255);
		break;
	}




	VECTOR_LINE vLines;
	DetectBlockiness(lpBuffer01, nWidth, nHeight, &vLines);

	VECTOR_LINEItor itor = vLines.begin();
	while( itor != vLines.end())
	{
		LPIPLLINE lpLine = &(*itor);

		image->DrawLine( lpLine->p1.x , lpLine->p2.x, lpLine->p1.y, lpLine->p2.y, color );
		itor++;
	}
	
	


	if(pGray01      ) delete[] pGray01      ;

	return;

}
void CDemoDoc::DetectStripe( )
{
	TCHAR szFilter[] = _T("Image (*.bmp, *.gif, *.jpg, *.tif) | *.bmp;*.gif;*.jpg;*.tif;*.BMP;*.GIF;*.JPG;*.TIF | All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if( dlg.DoModal() != IDOK )
		return;

	CString szSecondFile = dlg.GetPathName();
	CxImage xImageSec;
	xImageSec.Load( szSecondFile );

	if( xImageSec.IsValid() == false )
		return;

	if( ( image->GetWidth () != xImageSec.GetWidth () ) ||
		( image->GetHeight() != xImageSec.GetHeight() )  )
		return;


	int nSize   = image->GetWidth ()*image->GetHeight();
	int nWidth  = image->GetWidth ();
	int nHeight = image->GetHeight();

	COLORREF color ;

	LPBYTE lpBuffer01 = NULL;
	BYTE*  pGray01    = NULL;
	switch( image->GetBpp() )
	{
	case 24:
		{
			BYTE* pBuf = image->GetBits();
			pGray01    = new BYTE[nSize];
			ipl_RGBToGray(pGray01,pBuf,nWidth, nHeight);
			lpBuffer01 = pGray01;
			color = RGB(255,0,0);
		}
		break;
	case 8:
		lpBuffer01 = image->GetBits();
		color = RGB(255,255,255);
		break;
	}


	LPBYTE lpBuffer02 = NULL;
	BYTE*  pGray02    = NULL;
	switch( xImageSec.GetBpp() )
	{
	case 24:
		{
			BYTE* pBuf = xImageSec.GetBits();
			pGray02    = new BYTE[nSize];
			ipl_RGBToGray(pGray02,pBuf,nWidth, nHeight);
			lpBuffer02 = pGray02;
			color = RGB(255,0,0);
		}
		break;
	case 8:
		lpBuffer02 = xImageSec.GetBits();
		color = RGB(255,255,255);
		break;
	}


	BYTE* pGraySubtract    = new BYTE[nSize];
	iplImageSubtraction( lpBuffer01, lpBuffer02, pGraySubtract, nSize, nWidth, nHeight );

	CxImage xImageLP;
	xImageLP.SetGrayPalette();
	xImageLP.CreateFromArray( pGraySubtract, nWidth, nHeight, sizeof(BYTE)*8, nWidth, false );
	xImageLP.Save(_T("c:\\pGraySubtract.tif"), CXIMAGE_FORMAT_TIF);


	//image->Copy( xImageLP );
	image->Copy( xImageSec );


	BOOL bIsCurrentFrame = TRUE;
	VECTOR_LINE vLines;
	if( CheckFrameRelation( pGraySubtract, nWidth*nHeight ) )
		iplGetHorizontalLine( pGraySubtract, nWidth, nHeight, &vLines );

	if( xImageSec.GetBpp() == 24 )
	{
		iplStripeSingleColorLineFilter( xImageSec.GetBits(), &vLines, nWidth, nHeight );
		iplStripeLetterboxFilter      ( xImageSec.GetBits(), &vLines, nWidth, nHeight );
	}


	VECTOR_LINEItor itor = vLines.begin();
	while( itor != vLines.end())
	{
		LPIPLLINE lpLine = &(*itor);

		image->DrawLine( lpLine->p1.x , lpLine->p2.x, lpLine->p1.y, lpLine->p2.y, color );
		itor++;
	}

	int nDistance = 0;
	if( vLines.size() )
	{
		itor = vLines.begin();
		LPIPLLINE lpLine01 = &(*itor++);
		LPIPLLINE lpLine02 = &(*itor);
		nDistance = lpLine02->p1.y - lpLine01->p1.y;
	}

	CString szMsg;
	szMsg.Format(_T("count = %d , gap = %d"), vLines.size(), nDistance );
	::AfxMessageBox(szMsg);


	if(pGray01      ) delete[] pGray01      ;
	if(pGray02      ) delete[] pGray02      ;
	if(pGraySubtract) delete[] pGraySubtract;
	
	return;

}
