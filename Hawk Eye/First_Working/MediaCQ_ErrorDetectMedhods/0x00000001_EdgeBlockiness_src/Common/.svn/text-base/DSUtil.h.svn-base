//DSUtil.h
#ifndef _DIRECT_SHOW_UTILITY_H_INCLUDE_
#define _DIRECT_SHOW_UTILITY_H_INCLUDE_
#ifndef CHECK_HR
#define CHECK_HR(hr) if (FAILED(hr)) { goto done; }
#endif
class CDSUtil
{
public:
	static STDMETHODIMP WINAPI SaveGraph              (IGraphBuilder *pGraphBuilder, LPCTSTR szGraphFile);//
	static IPin*        WINAPI GetFormatTypePin       (IBaseFilter *pFilter, GUID FormatType, PIN_DIRECTION PinDir);//
	static IPin*        WINAPI GetMajorTypePin        (IBaseFilter *pFilter, GUID MajorType, PIN_DIRECTION PinDir) ;//
	static void         WINAPI UtilDeleteMediaType    (AM_MEDIA_TYPE *pmt);//
	static HRESULT      WINAPI GetUnconnectedPin      (IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin);//
	static HRESULT      WINAPI FindOtherSplitterPin   (IPin *pPinIn, GUID guid, int nStream, IPin **ppSplitPin);//
	static HRESULT      WINAPI ConnectFilters         (IGraphBuilder *pGraph, IBaseFilter *pFirst, IBaseFilter *pSecond);//
	static HRESULT      WINAPI ConnectFiltersVideoPin (IGraphBuilder *pGraph, IBaseFilter *pVideoFilter, IBaseFilter *pSecond);//
	static HRESULT      WINAPI ConnectFiltersAudioPin (IGraphBuilder *pGraph, IBaseFilter *pAudioFilter, IBaseFilter *pSecond);//
	static HRESULT      WINAPI GetPin                 (IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin);//
	static CComPtr<IPin>WINAPI GetPin				  (IBaseFilter *pFilter, LPCOLESTR pinname);
	static HRESULT		WINAPI GetPin				  (IBaseFilter* pFilter, const GUID* pFormat, PIN_DIRECTION PinDir, IPin** ppPin);
	static HRESULT      WINAPI ConnectFiltersUnconnectedPin( IGraphBuilder *pGraph, IBaseFilter *pFirst, IBaseFilter *pSecond);
	static HRESULT		WINAPI ConnectFilters(IGraphBuilder* pGraph, IBaseFilter* pUpstream, LPCWSTR pUpstreamPinName, IBaseFilter* pDownstream, LPCWSTR pDownstreamPinName);
	static HRESULT      WINAPI FindPinInterface(IBaseFilter* pFilter, LPCWSTR pName, const IID& riid, void** ppvInterface);
	static HRESULT      WINAPI FindPinInterface				(IBaseFilter* pFilter, const GUID* pFormat, PIN_DIRECTION PinDir, const IID& riid, void** ppvInterface);
	static HRESULT      WINAPI ConnectFiltersMpegStreamPin	( IGraphBuilder *pGraph , IBaseFilter *pVideoFilter, IBaseFilter *pSecond);
	static IPin*        WINAPI GetTypePin					( IBaseFilter   *pFilter, GUID MajorType, GUID SubType, PIN_DIRECTION PinDir) ;//

	static HRESULT 		GetPin		(IBaseFilter* pFilter, LPCWSTR pName, IPin** ppPin);
	static HRESULT		RenderFilter(IGraphBuilder* pGraph, IBaseFilter* pUpstream, LPCWSTR pUpstreamPinName);
	static HRESULT 		AddFilter	(IGraphBuilder* pGraph, const GUID &clsid, LPCWSTR pName, IBaseFilter** ppFilter);
	static HRESULT 		AddFilter2	(IGraphBuilder* pGraph, const GUID &clsid, LPCWSTR pName, IBaseFilter** ppFilter);
	static HRESULT AddFilterByCLSID(IGraphBuilder *pGraph,          // Pointer to the Filter Graph Manager.
		const GUID& clsid,              // CLSID of the filter to create.
		IBaseFilter **ppF,              // Receives a pointer to the filter.
		LPCWSTR wszName          // A name for the filter (can be NULL).
		);

};



#endif//_DIRECT_SHOW_UTILITY_H_INCLUDE_