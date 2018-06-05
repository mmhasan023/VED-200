#include "stdafx.h"
#include <uuids.h>
#include <dshow.h>
#include <mtype.h>
#include "reftime.h"



#include "DSUtil.h"

#include "apputil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

STDMETHODIMP CDSUtil::SaveGraph(IGraphBuilder *pGraphBuilder, LPCTSTR lpGraphFile)
{
//#if !defined(_DEBUG)
//	return S_FALSE;
//#endif

	CString szFullPath(lpGraphFile);

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (pGraphBuilder == NULL)
		return E_FAIL;

	USES_CONVERSION;
	LPWSTR		wlpGraphFile;

#ifdef _UNICODE	
	wlpGraphFile = (LPTSTR)(LPCTSTR)szFullPath;
#else
	int nSize = (int)_tcslen(szFullPath) + 1;
	wlpGraphFile = new WCHAR[nSize];
	memset(wlpGraphFile,0,sizeof(WCHAR)*nSize);
	MultiByteToWideChar(CP_ACP, 0, szFullPath, nSize-1, wlpGraphFile, nSize); 
#endif

	const WCHAR	wszStreamName[] = L"ActiveMovieGraph";
	IStorage	*pStorage		= NULL;    

	// First, create a document file that will hold the GRF file    
	HRESULT hr = StgCreateDocfile(wlpGraphFile,
		STGM_CREATE | STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
		0,
		&pStorage);    
	if (FAILED(hr))
	{
		goto return_SaveGraph;    
	}    

	// Next, create a stream to store.    
	IStream *pStream;    
	hr = pStorage->CreateStream(wszStreamName,
		STGM_WRITE | STGM_CREATE | STGM_SHARE_EXCLUSIVE,
		0, 0, &pStream);
	if (FAILED(hr))
	{
		pStorage->Release();            
		goto return_SaveGraph;    
	}    

	// The IpersistStream::Save method converts a stream    
	// into a persistent object.    
	IPersistStream *pPersist = NULL;    
	pGraphBuilder->QueryInterface(IID_IPersistStream, reinterpret_cast<void**>(&pPersist));

	hr = pPersist->Save(pStream, TRUE);

	if (SUCCEEDED(hr))
		hr = pStorage->Commit(STGC_DEFAULT);    

	pStream->Release();
	pPersist->Release();
	pStorage->Release();

return_SaveGraph:
#ifdef _UNICODE	
#else
	delete[] wlpGraphFile;
#endif
	return hr;
}

IPin* CDSUtil::GetFormatTypePin(IBaseFilter *pFilter, GUID FormatType, PIN_DIRECTION PinDir) 
{ 
	IEnumPins  *pEnum; 
	IPin       *pPin; 

	HRESULT hr = pFilter->EnumPins(&pEnum); 
	if (FAILED(hr)) 
	{ 
		return NULL; 
	} 
	while(pEnum->Next(1, &pPin, 0) == S_OK) 
	{ 
		PIN_DIRECTION PinDirThis; 
		pPin->QueryDirection(&PinDirThis); 

		IEnumMediaTypes * types = NULL; 
		pPin->EnumMediaTypes (&types); 
		AM_MEDIA_TYPE *pt; 
		ULONG f; 
		while(types->Next (1, &pt, &f) == S_OK) 
		{ 
			if( (pt->formattype == FormatType  ) && 
				(PinDir         == PinDirThis )  ) 
			{ 
				types->Release (); 
				return pPin;
			} 
		} 

		types->Release (); 
		pPin->Release(); 
	} 

	pEnum->Release(); 
	return NULL;  
} 

IPin* CDSUtil::GetTypePin( IBaseFilter   *pFilter, GUID MajorType, GUID SubType, PIN_DIRECTION PinDir)
{
	IEnumPins  *pEnum = NULL; 
	IPin       *pPin  = NULL; 

	HRESULT hr = pFilter->EnumPins(&pEnum); 
	if (FAILED(hr)) 
	{ 
		return NULL; 
	} 
	while(pEnum->Next(1, &pPin, 0) == S_OK) 
	{ 
		PIN_DIRECTION PinDirThis; 
		pPin->QueryDirection(&PinDirThis); 

		IEnumMediaTypes * types = NULL; 
		pPin->EnumMediaTypes (&types); 
		AM_MEDIA_TYPE *pt; 
		ULONG f; 
		while(types->Next (1, &pt, &f) == S_OK) 
		{ 
			if( (pt->majortype == MajorType  ) && 
				(pt->subtype   == SubType    ) && 
				(PinDir        == PinDirThis )  ) 
			{ 
				types->Release (); 
				return pPin;
			} 
		} 

		types->Release (); 
		pPin->Release(); 
	} 

	pEnum->Release(); 
	return NULL;  
}


IPin* CDSUtil::GetMajorTypePin(IBaseFilter *pFilter, GUID MajorType, PIN_DIRECTION PinDir) 
{ 
	IEnumPins  *pEnum; 
	IPin       *pPin; 

	HRESULT hr = pFilter->EnumPins(&pEnum); 
	if (FAILED(hr)) 
	{ 
		return NULL; 
	} 
	while(pEnum->Next(1, &pPin, 0) == S_OK) 
	{ 
		PIN_DIRECTION PinDirThis; 
		pPin->QueryDirection(&PinDirThis); 

		IEnumMediaTypes * types = NULL; 
		pPin->EnumMediaTypes (&types); 
		AM_MEDIA_TYPE *pt; 
		ULONG f; 
		while(types->Next (1, &pt, &f) == S_OK) 
		{ 
			if( (pt->majortype == MajorType  ) && 
				(PinDir        == PinDirThis )  ) 
			{ 
				types->Release (); 
				return pPin;
			} 
		} 

		types->Release (); 
		pPin->Release(); 
	} 

	pEnum->Release(); 
	return NULL;  
} 

void CDSUtil::UtilDeleteMediaType(AM_MEDIA_TYPE *pmt)
{
	// Allow NULL pointers for coding simplicity
	if (pmt == NULL) {
		return;
	}

	// Free media type's format data
	if (pmt->cbFormat != 0) 
	{
		CoTaskMemFree((PVOID)pmt->pbFormat);

		// Strictly unnecessary but tidier
		pmt->cbFormat = 0;
		pmt->pbFormat = NULL;
	}

	// Release interface
	if (pmt->pUnk != NULL) 
	{
		pmt->pUnk->Release();
		pmt->pUnk = NULL;
	}

	// Free media type
	CoTaskMemFree((PVOID)pmt);
}

HRESULT CDSUtil::GetUnconnectedPin(
										IBaseFilter *pFilter,   // Pointer to the filter.
										PIN_DIRECTION PinDir,   // Direction of the pin to find.
										IPin **ppPin)           // Receives a pointer to the pin.
{
	IEnumPins *pEnum = 0;
	IPin *pPin = 0;

	if (!ppPin || !pFilter)
		return E_POINTER;
	*ppPin = 0;

	// Get a pin enumerator
	HRESULT hr = pFilter->EnumPins(&pEnum);
	if (FAILED(hr))
		return hr;

	// Look for the first unconnected pin
	while (pEnum->Next(1, &pPin, NULL) == S_OK)
	{
		PIN_DIRECTION ThisPinDir;

		pPin->QueryDirection(&ThisPinDir);
		if (ThisPinDir == PinDir)
		{
			IPin *pTmp = 0;

			hr = pPin->ConnectedTo(&pTmp);
			if (SUCCEEDED(hr))  // Already connected, not the pin we want.
			{
				pTmp->Release();
			}
			else  // Unconnected, this is the pin we want.
			{
				pEnum->Release();
				*ppPin = pPin;
				return S_OK;
			}
		}
		pPin->Release();
	}

	// Release the enumerator
	pEnum->Release();

	// Did not find a matching pin
	return E_FAIL;
}


HRESULT CDSUtil::FindOtherSplitterPin(IPin *pPinIn, GUID guid, int nStream, IPin **ppSplitPin)
{
	if (!ppSplitPin)
		return E_POINTER;

	CComPtr< IPin > pPinOut;
	pPinOut = pPinIn;

	while(pPinOut)
	{
		PIN_INFO ThisPinInfo;
		pPinOut->QueryPinInfo(&ThisPinInfo);
		if(ThisPinInfo.pFilter) ThisPinInfo.pFilter->Release();

		pPinOut = NULL;
		CComPtr< IEnumPins > pEnumPins;
		ThisPinInfo.pFilter->EnumPins(&pEnumPins);
		if(!pEnumPins)
		{
			return NULL;
		}

		// look at every pin on the current filter...
		//
		ULONG Fetched = 0;
		while(1)
		{
			CComPtr< IPin > pPin;
			Fetched = 0;
			ASSERT(!pPin); // is it out of scope?
			pEnumPins->Next(1, &pPin, &Fetched);
			if(!Fetched)
			{
				break;
			}

			PIN_INFO pi;
			pPin->QueryPinInfo(&pi);
			if(pi.pFilter) pi.pFilter->Release();

			// if it's an input pin...
			//
			if(pi.dir == PINDIR_INPUT)
			{
				// continue searching upstream from this pin
				//
				if(!pPinOut)
					pPin->ConnectedTo(&pPinOut);

				// a pin that supports the required media type is the
				// splitter pin we are looking for!  We are done
				//
			}
			else
			{
				CComPtr< IEnumMediaTypes > pMediaEnum;
				pPin->EnumMediaTypes(&pMediaEnum);
				if(pMediaEnum)
				{
					Fetched = 0;
					AM_MEDIA_TYPE *pMediaType;
					pMediaEnum->Next(1, &pMediaType, &Fetched);
					if(Fetched)
					{
						if(pMediaType->majortype == guid)
						{
							if(nStream-- == 0)
							{
								UtilDeleteMediaType(pMediaType);
								*ppSplitPin = pPin;
								(*ppSplitPin)->AddRef();
								return S_OK;
							}
						}
						UtilDeleteMediaType(pMediaType);
					}
				}
			}

			// go try the next pin

		} // while
	}
	//	ASSERT(FALSE);
	return E_FAIL;
}

HRESULT CDSUtil::ConnectFilters(IGraphBuilder *pGraph, IBaseFilter *pFirst, IBaseFilter *pSecond)
{
#ifdef _LOGDATA
//	DEBUG_MSG(_T("ConnectFilters start"));
#endif

	/*
	IPin *pOut = NULL, *pIn = NULL;
	HRESULT hr = GetPin(pSecond, PINDIR_INPUT, &pIn);
	if (FAILED(hr)) return hr;
	// The previous filter may have multiple outputs, so try each one!
	IEnumPins  *pEnum;

	pFirst->EnumPins(&pEnum);
	while(pEnum->Next(1, &pOut, 0) == S_OK)
	{
		PIN_DIRECTION PinDirThis;
		pOut->QueryDirection(&PinDirThis);
		if (PINDIR_OUTPUT == PinDirThis)
		{
			hr = pGraph->Connect(pOut, pIn);
			if(!FAILED(hr))
			{
				break;
			}
		}
		pIn->Release();
		pOut->Release();
	}
	pEnum->Release();
	pIn->Release();
	pOut->Release();
	return hr;
	*/
	IEnumPins  *				m_pEnum;
	IPin* pOut = NULL;
	IPin* pIn  = NULL;

//by kiok ahn 20090528
	HRESULT hr = GetUnconnectedPin(pSecond,PINDIR_INPUT, &pIn);
//	HRESULT hr = GetPin(pSecond, PINDIR_INPUT, &pIn);
//by kiok ahn 20090528
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	} 
	// The previous filter may have multiple outputs, so try each one!
	// 출력핀을 찾는다 . 
	pFirst->EnumPins(&m_pEnum);
	while(m_pEnum->Next(1, &pOut, 0) == S_OK)
	{
		PIN_DIRECTION PinDirThis;
		pOut->QueryDirection(&PinDirThis);
		if (PINDIR_OUTPUT == PinDirThis)
		{
			AM_MEDIA_TYPE pmt;
			pOut->ConnectionMediaType(&pmt);
			//hr = m_pOut->Connect(m_pIn,&pmt);
			//hr = pGraph->ConnectDirect(m_pOut, m_pIn,&pmt);
			try{//20091103 by kiok ahn, SK,2_DS_25356_특수요원-오소(우리말)_20091027_01.mpg,Haali Media Splitter2004-2007
				hr = pGraph->Connect(pOut, pIn);
			}
			catch(...)
			{
				hr = E_FAIL;
			}
			if(!FAILED(hr))
			{
				pOut->Release();
				break;
			}
		}
		pOut->Release();
		pOut = NULL;
	}
	m_pEnum->Release();
	pIn->Release();
	//	m_pOut->Release();

#ifdef _LOGDATA
//	DEBUG_MSG(_T("ConnectFilters end=0x%08x"),hr);
#endif
	return hr;
}

HRESULT CDSUtil::ConnectFiltersVideoPin(IGraphBuilder *pGraph, IBaseFilter *pVideoFilter, IBaseFilter *pSecond)
{
#ifdef _LOGDATA
//	DEBUG_MSG(_T("ConnectFiltersVideoPin start"));
#endif

	IPin* pOut = NULL;
	IPin* pIn  = NULL;
	/*
	IPin *pOut = NULL, *pIn = NULL;
	HRESULT hr = GetPin(pSecond, PINDIR_INPUT, &pIn);
	if (FAILED(hr)) return hr;
	// The previous filter may have multiple outputs, so try each one!
	pOut = GetMajorTypePin( pVideoFilter, MEDIATYPE_Video, PINDIR_OUTPUT );
	if( pOut == NULL ) return E_FAIL;

	//AM_MEDIA_TYPE mt;
	//mt.majortype = MEDIATYPE_Video;
	//hr = pGraph->ConnectDirect(pOut,pIn,&mt);
	hr =  pGraph->Connect(pOut, pIn);
	pIn->Release();
	pOut->Release();
	return hr;
	*/
	HRESULT hr = GetPin( pSecond, PINDIR_INPUT, &pIn );
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	}
	// The previous filter may have multiple outputs, so try each one!
	pOut = GetMajorTypePin( pVideoFilter, MEDIATYPE_Video, PINDIR_OUTPUT );
	if( pOut == NULL ) return E_FAIL;

	hr =  pGraph->Connect( pOut, pIn);
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	} 
	pIn ->Release();
	pOut->Release();
#ifdef _LOGDATA
//	DEBUG_MSG(_T("ConnectFiltersVideoPin end=0x%08x"),hr);
#endif
	return hr;
}

static GUID g_guidMpegVideos[] =
{
	MEDIASUBTYPE_MPEG2_PROGRAM  ,
	MEDIASUBTYPE_MPEG2_TRANSPORT,
	MEDIASUBTYPE_MPEG2_VIDEO    ,
	MEDIASUBTYPE_MPEG1Video     ,
	MEDIASUBTYPE_MPEG1VideoCD   ,
	GUID_NULL
};

HRESULT CDSUtil::ConnectFiltersMpegStreamPin(IGraphBuilder *pGraph, IBaseFilter *pVideoFilter, IBaseFilter *pSecond)
{
	IPin* pOut = NULL;
	IPin* pIn  = NULL;

	HRESULT hr = GetPin( pSecond, PINDIR_INPUT, &pIn );
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	}
	// The previous filter may have multiple outputs, so try each one!
	//pOut = GetTypePin( pVideoFilter, MEDIATYPE_Stream, MEDIASUBTYPE_MPEG2_TRANSPORT, PINDIR_OUTPUT );
	int nIndex = 0;
	while ( pOut==NULL && g_guidMpegVideos[nIndex]!=GUID_NULL )
		pOut = GetTypePin( pVideoFilter, MEDIATYPE_Stream, g_guidMpegVideos[nIndex++], PINDIR_OUTPUT );

	if( pOut == NULL ) return E_FAIL;

	hr =  pGraph->Connect( pOut, pIn);
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	} 
	pIn ->Release();
	pOut->Release();
#ifdef _LOGDATA
//	DEBUG_MSG(_T("ConnectFiltersVideoPin end=0x%08x"),hr);
#endif
	return hr;
}

HRESULT CDSUtil::ConnectFiltersAudioPin(IGraphBuilder *pGraph, IBaseFilter *pAudioFilter, IBaseFilter *pSecond)
{
	CComPtr<IPin> pOut = NULL;
	CComPtr<IPin> pIn  = NULL;

	//by kiok ahn 20090528
	HRESULT hr = GetUnconnectedPin(pSecond,PINDIR_INPUT, &pIn);
//	HRESULT hr = GetPin(pSecond, PINDIR_INPUT, &m_pIn);
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	} 
	// The previous filter may have multiple outputs, so try each one!
	pOut = GetMajorTypePin( pAudioFilter, MEDIATYPE_Audio, PINDIR_OUTPUT );
	if( pOut == NULL )
	{
		SetLastError(ERROR_INVALID_DATA);	
		return E_FAIL;
	}
	hr =  pGraph->Connect(pOut, pIn);
	return hr;
}
CComPtr<IPin> CDSUtil::GetPin(IBaseFilter *pFilter, LPCOLESTR pinname)
{
	CComPtr<IEnumPins>  pEnum;
	CComPtr<IPin>       pPin;

	HRESULT hr = pFilter->EnumPins(&pEnum);
	if (!SUCCEEDED(hr))
		return NULL;

	while(pEnum->Next(1, &pPin, 0) == S_OK)
	{
		PIN_INFO pinfo;
		pPin->QueryPinInfo(&pinfo);
		BOOL found = !_wcsicmp(pinname, pinfo.achName);
		if (pinfo.pFilter) pFilter->Release();
		if (found)
			return pPin;
		pPin.Release();
	}
	printf("Pin not found!\n");
	return NULL;  
}
HRESULT CDSUtil::GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin)
{
	IEnumPins  *pEnum;
	IPin       *pPin;
	pFilter->EnumPins(&pEnum);
	while(pEnum->Next(1, &pPin, 0) == S_OK)
	{
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if (PinDir == PinDirThis)
		{
			pEnum->Release();
			*ppPin = pPin;
			return S_OK;
		}
		pPin->Release();
	}
	pEnum->Release();
	return E_FAIL;  
}

HRESULT CDSUtil::ConnectFiltersUnconnectedPin(IGraphBuilder *pGraph, IBaseFilter *pFirst, IBaseFilter *pSecond)
{
	IEnumPins* pEnum = NULL;
	IPin*      pOut  = NULL;
	IPin*      pIn   = NULL;
	HRESULT    hr;

	hr = GetUnconnectedPin( pSecond, PINDIR_INPUT, &pIn );
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	} 

	hr = GetUnconnectedPin( pFirst, PINDIR_OUTPUT, &pOut );
	if ( FAILED( hr ) )	
	{
		SetLastError(ERROR_INVALID_DATA);		
		return hr;
	} 
	hr = pGraph->Connect(pOut, pIn);

	pOut->Release();
	pIn ->Release();
	return hr;

}

//-----------------------------------------------------------------------------
// AddFilter
// Attempts to locate a filter of a given class ID and name	and add it to the graph
HRESULT CDSUtil::AddFilter(IGraphBuilder* pGraph, const GUID &clsid, LPCWSTR pName, IBaseFilter** ppFilter)
{
	HRESULT hr = S_OK;

	if (pGraph && pName && ppFilter)
	{
		*ppFilter = NULL;
		IBaseFilter* pFilter = NULL;
		hr = CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&pFilter));
		if (SUCCEEDED(hr))
		{
			hr = pGraph->AddFilter(pFilter, pName);
			if (SUCCEEDED(hr))
			{
				*ppFilter = pFilter;
			}
			else
			{
				SAFE_RELEASE(pFilter);
			}
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
///////////////////////////////////////////////////////////////////////
// Name: AddFilterByCLSID
// Desc: Create a filter by CLSID and add it to the graph.
///////////////////////////////////////////////////////////////////////

HRESULT CDSUtil::AddFilterByCLSID(
								IGraphBuilder *pGraph,          // Pointer to the Filter Graph Manager.
								const GUID& clsid,              // CLSID of the filter to create.
								IBaseFilter **ppF,              // Receives a pointer to the filter.
								LPCWSTR wszName          // A name for the filter (can be NULL).
								)
{
	if (!pGraph || ! ppF) 
	{
		return E_POINTER;
	}

	*ppF = 0;

	IBaseFilter *pFilter = NULL;
	HRESULT hr = S_OK;

	CHECK_HR(hr = CoCreateInstance(
		clsid, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, 
		(void**)&pFilter));

	CHECK_HR(hr = pGraph->AddFilter(pFilter, wszName));

	*ppF = pFilter;
	(*ppF)->AddRef();

done:
	SAFE_RELEASE(pFilter);
	return hr;
}
//-----------------------------------------------------------------------------
// AddFilter2
// Attempts to locate a filter of a given class category and name
HRESULT CDSUtil::AddFilter2(IGraphBuilder* pGraph, const GUID &clsid, LPCWSTR pName, IBaseFilter** ppFilter)
{
	HRESULT hr = S_OK;

	if (pGraph && pName && ppFilter)
	{
		// first enumerate the system devices for the specifed class and filter name
		CComPtr<ICreateDevEnum> pSysDevEnum = NULL;
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, reinterpret_cast<void**>(&pSysDevEnum));

		if (SUCCEEDED(hr))
		{
			CComPtr<IEnumMoniker> pEnumCat = NULL;
			hr = pSysDevEnum->CreateClassEnumerator(clsid, &pEnumCat, 0);

			if (S_OK == hr)
			{
				IMoniker* pMoniker = NULL;
				bool Loop = true;
				while ((S_OK == pEnumCat->Next(1, &pMoniker, NULL)) && Loop)
				{
					IPropertyBag* pPropBag = NULL;
					hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, reinterpret_cast<void**>(&pPropBag));

					if (SUCCEEDED(hr))
					{
						VARIANT varName;
						VariantInit(&varName);
						hr = pPropBag->Read(L"FriendlyName", &varName, 0);
						if (SUCCEEDED(hr))
						{
							if (0 == wcscmp(varName.bstrVal, pName))
							{
								hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, reinterpret_cast<void**>(ppFilter));
								Loop = false;
							}
						}

						VariantClear(&varName);

						// contained within a loop, decrement the reference count
						SAFE_RELEASE(pPropBag);
					}
					SAFE_RELEASE(pMoniker);
				}
			}
		}

		// if a filter has been located add it to the graph
		if (*ppFilter)
		{
			hr = pGraph->AddFilter(reinterpret_cast<IBaseFilter*>(*ppFilter), pName);
		}
		else
		{
			hr = E_FAIL;
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}

//-----------------------------------------------------------------------------
// FindPinInterface
// Attempt to locate the interface on the pin with the specified format or on the first pin if no
// format is provided.
HRESULT CDSUtil::FindPinInterface(IBaseFilter* pFilter, const GUID* pFormat, PIN_DIRECTION PinDir, const IID& riid, void** ppvInterface)
{
	HRESULT hr = S_OK;

	if (pFilter && ppvInterface)
	{
		CComPtr<IPin> pIPin = NULL;
		if (pFormat)
		{
			hr = GetPin(pFilter, pFormat, PinDir, &pIPin);
		}
		else
		{
			CComPtr<IEnumPins> pIEnumPins = NULL;
			hr = pFilter->EnumPins(&pIEnumPins);
			if (SUCCEEDED(hr))
			{
				hr = pIEnumPins->Next(1, &pIPin, NULL);
			}
		}

		if (SUCCEEDED(hr))
		{
			hr = pIPin->QueryInterface(riid, ppvInterface);
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
HRESULT CDSUtil::FindPinInterface(IBaseFilter* pFilter, LPCWSTR pName, const IID& riid, void** ppvInterface)
{
	HRESULT hr = S_OK;

	if (pFilter && ppvInterface)
	{
		CComPtr<IPin> pIPin = NULL;
		if (pName)
		{
			hr = GetPin(pFilter, pName, &pIPin);
		}
		else
		{
			CComPtr<IEnumPins> pIEnumPins = NULL;
			hr = pFilter->EnumPins(&pIEnumPins);
			if (SUCCEEDED(hr))
			{
				hr = pIEnumPins->Next(1, &pIPin, NULL);
			}
		}

		if (SUCCEEDED(hr))
		{
			hr = pIPin->QueryInterface(riid, ppvInterface);
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
//-----------------------------------------------------------------------------
// GetPin
// Find the pin of the specified format type on the given filter
// This method leaves an outstanding reference on the pin if successful
HRESULT CDSUtil::GetPin(IBaseFilter* pFilter, const GUID* pFormat, PIN_DIRECTION PinDir, IPin** ppPin)
{
	HRESULT hr = S_OK;

	if (pFilter && pFormat && ppPin)
	{
		CComPtr<IEnumPins> pIEnumPins = NULL;
		hr = pFilter->EnumPins(&pIEnumPins);
		if (SUCCEEDED(hr))
		{
			// find the pin with the specified format
			IPin* pIPin = NULL;
			while (S_OK == pIEnumPins->Next(1, &pIPin, NULL))
			{
				// match the pin direction
				PIN_DIRECTION pinDir;
				pIPin->QueryDirection(&pinDir);
				if (pinDir == PinDir)
				{
					// match pin direction check the first media type returned from the upstream pin
					CComPtr<IEnumMediaTypes> pIEnumMT = NULL;
					hr = pIPin->EnumMediaTypes(&pIEnumMT);
					if (SUCCEEDED(hr))
					{
						AM_MEDIA_TYPE* pmt = NULL;
						hr = pIEnumMT->Next(1, &pmt, NULL);
						if (S_OK == hr)
						{
							if (pmt->majortype == *pFormat)
							{
								// found the pin with the specified format
								*ppPin = pIPin;
								DeleteMediaType(pmt);
								break;
							}
							else
							{
								DeleteMediaType(pmt);
							}
						}
					}
				}
				SAFE_RELEASE(pIPin);
			}

			if (NULL == *ppPin)
			{
				// failed to find the named pin
				hr = E_FAIL;
			}
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
//-----------------------------------------------------------------------------
// RenderFilter
// Renders the named output pin of the filter, or the first unconnected output if 
// no name is provided
HRESULT CDSUtil::RenderFilter(IGraphBuilder* pGraph, IBaseFilter* pUpstream, LPCWSTR pUpstreamPinName)
{
	HRESULT hr = S_OK;

	if (pUpstream)
	{
		CComPtr<IPin> pIPinOutput = NULL;
		if (pUpstreamPinName)
		{
			hr = GetPin(pUpstream, pUpstreamPinName, &pIPinOutput);
		}
		else
		{
			hr = GetUnconnectedPin(pUpstream, PINDIR_OUTPUT, &pIPinOutput);
		}

		if (SUCCEEDED(hr))
		{
			hr = pGraph->Render(pIPinOutput);
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
//-----------------------------------------------------------------------------
// GetPin
// Find the pin of the specified name on the given filter
// This method leaves an outstanding reference on the pin if successful
HRESULT CDSUtil::GetPin(IBaseFilter* pFilter, LPCWSTR pName, IPin** ppPin)
{
	HRESULT hr = S_OK;

	if (pFilter && pName && ppPin)
	{
		CComPtr<IEnumPins> pIEnumPins = NULL;
		hr = pFilter->EnumPins(&pIEnumPins);
		if (SUCCEEDED(hr))
		{
			IPin* pIPin = NULL;
			while (S_OK == pIEnumPins->Next(1, &pIPin, NULL))
			{
				PIN_INFO info = {0};
				hr = pIPin->QueryPinInfo(&info);
				if (SUCCEEDED(hr))
				{
					SAFE_RELEASE(info.pFilter);

					if (0 == wcsncmp(info.achName, pName, wcslen(pName)))
					{
						// matched the pin category
						*ppPin = pIPin;
						break;
					}
				}
				SAFE_RELEASE(pIPin);
			}
		}

		if (NULL == *ppPin)
		{
			// failed to find the named pin
			hr = E_FAIL;
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
HRESULT CDSUtil::ConnectFilters(IGraphBuilder* pGraph, IBaseFilter* pUpstream, LPCWSTR pUpstreamPinName, IBaseFilter* pDownstream, LPCWSTR pDownstreamPinName)
{
	HRESULT hr = S_OK;

	if (pUpstream && pDownstream)
	{
		// get the upstream output pin
		CComPtr<IPin> pIPinOutput = NULL;
		if (pUpstreamPinName)
		{
			hr = GetPin(pUpstream, pUpstreamPinName, &pIPinOutput);
		}
		else
		{
			hr = GetUnconnectedPin(pUpstream, PINDIR_OUTPUT, &pIPinOutput);
		}

		if (SUCCEEDED(hr))
		{
			// get the downstream input pin
			CComPtr<IPin> pIPinInput = NULL;
			if (pDownstreamPinName)
			{
				hr = GetPin(pDownstream, pDownstreamPinName, &pIPinInput);
			}
			else
			{
				hr = GetUnconnectedPin(pDownstream, PINDIR_INPUT, &pIPinInput);
			}

			if (SUCCEEDED(hr))
			{
				// connect the pins
				hr = pGraph->Connect(pIPinOutput, pIPinInput);
			}
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}