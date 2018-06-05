/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 25 14:16:19 2010
 */
/* Compiler settings for .\DVDecoder.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DVDecoder_h__
#define __DVDecoder_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMLDVProperties_FWD_DEFINED__
#define __IMLDVProperties_FWD_DEFINED__
typedef interface IMLDVProperties IMLDVProperties;
#endif 	/* __IMLDVProperties_FWD_DEFINED__ */


#ifndef __IMLDVDecoder_FWD_DEFINED__
#define __IMLDVDecoder_FWD_DEFINED__
typedef interface IMLDVDecoder IMLDVDecoder;
#endif 	/* __IMLDVDecoder_FWD_DEFINED__ */


#ifndef __MLDVDecoder_FWD_DEFINED__
#define __MLDVDecoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class MLDVDecoder MLDVDecoder;
#else
typedef struct MLDVDecoder MLDVDecoder;
#endif /* __cplusplus */

#endif 	/* __MLDVDecoder_FWD_DEFINED__ */


#ifndef __MLDVDecoderPP_FWD_DEFINED__
#define __MLDVDecoderPP_FWD_DEFINED__

#ifdef __cplusplus
typedef class MLDVDecoderPP MLDVDecoderPP;
#else
typedef struct MLDVDecoderPP MLDVDecoderPP;
#endif /* __cplusplus */

#endif 	/* __MLDVDecoderPP_FWD_DEFINED__ */


#ifndef __MLDVDecoderAbout_FWD_DEFINED__
#define __MLDVDecoderAbout_FWD_DEFINED__

#ifdef __cplusplus
typedef class MLDVDecoderAbout MLDVDecoderAbout;
#else
typedef struct MLDVDecoderAbout MLDVDecoderAbout;
#endif /* __cplusplus */

#endif 	/* __MLDVDecoderAbout_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMLDVProperties_INTERFACE_DEFINED__
#define __IMLDVProperties_INTERFACE_DEFINED__

/* interface IMLDVProperties */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMLDVProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("334AC9D5-42D1-47d1-A3A8-6A3E6E7E8EC3")
    IMLDVProperties : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDateTime( 
            /* [in] */ BOOL bVideo,
            /* [out] */ DWORD __RPC_FAR *pdwTimeCode,
            /* [out] */ DWORD __RPC_FAR *pdwRecDate,
            /* [out] */ DWORD __RPC_FAR *pdwRecTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimeCodeOutput( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimeCodeOutput( 
            /* [out] */ BOOL __RPC_FAR *pbEnabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLDVPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLDVProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLDVProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLDVProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDateTime )( 
            IMLDVProperties __RPC_FAR * This,
            /* [in] */ BOOL bVideo,
            /* [out] */ DWORD __RPC_FAR *pdwTimeCode,
            /* [out] */ DWORD __RPC_FAR *pdwRecDate,
            /* [out] */ DWORD __RPC_FAR *pdwRecTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeCodeOutput )( 
            IMLDVProperties __RPC_FAR * This,
            /* [in] */ BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeCodeOutput )( 
            IMLDVProperties __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbEnabled);
        
        END_INTERFACE
    } IMLDVPropertiesVtbl;

    interface IMLDVProperties
    {
        CONST_VTBL struct IMLDVPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLDVProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLDVProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLDVProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLDVProperties_GetDateTime(This,bVideo,pdwTimeCode,pdwRecDate,pdwRecTime)	\
    (This)->lpVtbl -> GetDateTime(This,bVideo,pdwTimeCode,pdwRecDate,pdwRecTime)

#define IMLDVProperties_SetTimeCodeOutput(This,bEnable)	\
    (This)->lpVtbl -> SetTimeCodeOutput(This,bEnable)

#define IMLDVProperties_GetTimeCodeOutput(This,pbEnabled)	\
    (This)->lpVtbl -> GetTimeCodeOutput(This,pbEnabled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMLDVProperties_GetDateTime_Proxy( 
    IMLDVProperties __RPC_FAR * This,
    /* [in] */ BOOL bVideo,
    /* [out] */ DWORD __RPC_FAR *pdwTimeCode,
    /* [out] */ DWORD __RPC_FAR *pdwRecDate,
    /* [out] */ DWORD __RPC_FAR *pdwRecTime);


void __RPC_STUB IMLDVProperties_GetDateTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVProperties_SetTimeCodeOutput_Proxy( 
    IMLDVProperties __RPC_FAR * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IMLDVProperties_SetTimeCodeOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVProperties_GetTimeCodeOutput_Proxy( 
    IMLDVProperties __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbEnabled);


void __RPC_STUB IMLDVProperties_GetTimeCodeOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLDVProperties_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_DVDecoder_0209 */
/* [local] */ 

EXTERN_C void CALLBACK SetMerit(HWND hWnd, HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow);
typedef void (CALLBACK SETMERIT)(HWND hWnd, HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow);
typedef 
enum tagMLDVResize
    {	MLDV_RESIZE_NN	= 0,
	MLDV_RESIZE_LINEAR	= MLDV_RESIZE_NN + 1,
	MLDV_RESIZE_CUBIC	= MLDV_RESIZE_LINEAR + 1
    }	MLDV_RESIZE;

typedef 
enum tagMLDVProgressive
    {	MLDV_ORIGINAL	= 0,
	MLDV_PROGRESSIVE_BOTH	= MLDV_ORIGINAL + 1,
	MLDV_PROGRESSIVE_FIRST	= MLDV_PROGRESSIVE_BOTH + 1,
	MLDV_PROGRESSIVE_SECOND	= MLDV_PROGRESSIVE_FIRST + 1
    }	MLDV_PROGRESSIVE;



extern RPC_IF_HANDLE __MIDL_itf_DVDecoder_0209_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DVDecoder_0209_v0_0_s_ifspec;

#ifndef __IMLDVDecoder_INTERFACE_DEFINED__
#define __IMLDVDecoder_INTERFACE_DEFINED__

/* interface IMLDVDecoder */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMLDVDecoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8738E78F-B58D-48C6-BA11-25F47DCB696A")
    IMLDVDecoder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMultiCpu( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiCpu( 
            /* [out] */ BOOL __RPC_FAR *pbEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDeinterlacing( 
            /* [in] */ BOOL bEnable,
            /* [in] */ DWORD dwInterlaceFlags,
            /* [in] */ DWORD dwMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeinterlacing( 
            /* [out] */ BOOL __RPC_FAR *pbEnabled,
            /* [out] */ DWORD __RPC_FAR *pdwInterlaceFlags,
            /* [out] */ DWORD __RPC_FAR *pdwMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProgressive( 
            /* [in] */ MLDV_PROGRESSIVE eProgressive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProgressive( 
            /* [out] */ MLDV_PROGRESSIVE __RPC_FAR *peProgressive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFieldOrder( 
            /* [in] */ BOOL bChangeFieldOrder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFieldOrder( 
            /* [out] */ BOOL __RPC_FAR *bFieldOrderChanged) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHDVResize( 
            /* [in] */ BOOL bResize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHDVResize( 
            /* [out] */ BOOL __RPC_FAR *pbResized) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetResizeType( 
            /* [in] */ MLDV_RESIZE eResize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetResizeType( 
            /* [out] */ MLDV_RESIZE __RPC_FAR *peResize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MaintainVMRAspectRatio( 
            /* [in] */ BOOL bMaintain) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsVMRAspectRatioMaintained( 
            /* [out] */ BOOL __RPC_FAR *pbMaintain) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMLDVDecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMLDVDecoder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMLDVDecoder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiCpu )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiCpu )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDeinterlacing )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ BOOL bEnable,
            /* [in] */ DWORD dwInterlaceFlags,
            /* [in] */ DWORD dwMask);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeinterlacing )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbEnabled,
            /* [out] */ DWORD __RPC_FAR *pdwInterlaceFlags,
            /* [out] */ DWORD __RPC_FAR *pdwMask);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProgressive )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ MLDV_PROGRESSIVE eProgressive);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProgressive )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ MLDV_PROGRESSIVE __RPC_FAR *peProgressive);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFieldOrder )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ BOOL bChangeFieldOrder);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFieldOrder )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bFieldOrderChanged);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHDVResize )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ BOOL bResize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHDVResize )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbResized);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetResizeType )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ MLDV_RESIZE eResize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetResizeType )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ MLDV_RESIZE __RPC_FAR *peResize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MaintainVMRAspectRatio )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [in] */ BOOL bMaintain);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsVMRAspectRatioMaintained )( 
            IMLDVDecoder __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbMaintain);
        
        END_INTERFACE
    } IMLDVDecoderVtbl;

    interface IMLDVDecoder
    {
        CONST_VTBL struct IMLDVDecoderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMLDVDecoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMLDVDecoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMLDVDecoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMLDVDecoder_SetMultiCpu(This,bEnable)	\
    (This)->lpVtbl -> SetMultiCpu(This,bEnable)

#define IMLDVDecoder_GetMultiCpu(This,pbEnabled)	\
    (This)->lpVtbl -> GetMultiCpu(This,pbEnabled)

#define IMLDVDecoder_SetDeinterlacing(This,bEnable,dwInterlaceFlags,dwMask)	\
    (This)->lpVtbl -> SetDeinterlacing(This,bEnable,dwInterlaceFlags,dwMask)

#define IMLDVDecoder_GetDeinterlacing(This,pbEnabled,pdwInterlaceFlags,pdwMask)	\
    (This)->lpVtbl -> GetDeinterlacing(This,pbEnabled,pdwInterlaceFlags,pdwMask)

#define IMLDVDecoder_SetProgressive(This,eProgressive)	\
    (This)->lpVtbl -> SetProgressive(This,eProgressive)

#define IMLDVDecoder_GetProgressive(This,peProgressive)	\
    (This)->lpVtbl -> GetProgressive(This,peProgressive)

#define IMLDVDecoder_SetFieldOrder(This,bChangeFieldOrder)	\
    (This)->lpVtbl -> SetFieldOrder(This,bChangeFieldOrder)

#define IMLDVDecoder_GetFieldOrder(This,bFieldOrderChanged)	\
    (This)->lpVtbl -> GetFieldOrder(This,bFieldOrderChanged)

#define IMLDVDecoder_SetHDVResize(This,bResize)	\
    (This)->lpVtbl -> SetHDVResize(This,bResize)

#define IMLDVDecoder_GetHDVResize(This,pbResized)	\
    (This)->lpVtbl -> GetHDVResize(This,pbResized)

#define IMLDVDecoder_SetResizeType(This,eResize)	\
    (This)->lpVtbl -> SetResizeType(This,eResize)

#define IMLDVDecoder_GetResizeType(This,peResize)	\
    (This)->lpVtbl -> GetResizeType(This,peResize)

#define IMLDVDecoder_MaintainVMRAspectRatio(This,bMaintain)	\
    (This)->lpVtbl -> MaintainVMRAspectRatio(This,bMaintain)

#define IMLDVDecoder_IsVMRAspectRatioMaintained(This,pbMaintain)	\
    (This)->lpVtbl -> IsVMRAspectRatioMaintained(This,pbMaintain)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMLDVDecoder_SetMultiCpu_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IMLDVDecoder_SetMultiCpu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_GetMultiCpu_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbEnabled);


void __RPC_STUB IMLDVDecoder_GetMultiCpu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_SetDeinterlacing_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ BOOL bEnable,
    /* [in] */ DWORD dwInterlaceFlags,
    /* [in] */ DWORD dwMask);


void __RPC_STUB IMLDVDecoder_SetDeinterlacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_GetDeinterlacing_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbEnabled,
    /* [out] */ DWORD __RPC_FAR *pdwInterlaceFlags,
    /* [out] */ DWORD __RPC_FAR *pdwMask);


void __RPC_STUB IMLDVDecoder_GetDeinterlacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_SetProgressive_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ MLDV_PROGRESSIVE eProgressive);


void __RPC_STUB IMLDVDecoder_SetProgressive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_GetProgressive_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ MLDV_PROGRESSIVE __RPC_FAR *peProgressive);


void __RPC_STUB IMLDVDecoder_GetProgressive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_SetFieldOrder_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ BOOL bChangeFieldOrder);


void __RPC_STUB IMLDVDecoder_SetFieldOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_GetFieldOrder_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bFieldOrderChanged);


void __RPC_STUB IMLDVDecoder_GetFieldOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_SetHDVResize_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ BOOL bResize);


void __RPC_STUB IMLDVDecoder_SetHDVResize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_GetHDVResize_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbResized);


void __RPC_STUB IMLDVDecoder_GetHDVResize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_SetResizeType_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ MLDV_RESIZE eResize);


void __RPC_STUB IMLDVDecoder_SetResizeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_GetResizeType_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ MLDV_RESIZE __RPC_FAR *peResize);


void __RPC_STUB IMLDVDecoder_GetResizeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_MaintainVMRAspectRatio_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [in] */ BOOL bMaintain);


void __RPC_STUB IMLDVDecoder_MaintainVMRAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMLDVDecoder_IsVMRAspectRatioMaintained_Proxy( 
    IMLDVDecoder __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbMaintain);


void __RPC_STUB IMLDVDecoder_IsVMRAspectRatioMaintained_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMLDVDecoder_INTERFACE_DEFINED__ */



#ifndef __DVDECODERLib_LIBRARY_DEFINED__
#define __DVDECODERLib_LIBRARY_DEFINED__

/* library DVDECODERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DVDECODERLib;

EXTERN_C const CLSID CLSID_MLDVDecoder;

#ifdef __cplusplus

class DECLSPEC_UUID("D0351C50-6531-40D6-A540-DFAA1BFD6C8F")
MLDVDecoder;
#endif

EXTERN_C const CLSID CLSID_MLDVDecoderPP;

#ifdef __cplusplus

class DECLSPEC_UUID("D0351C51-6531-40D6-A540-DFAA1BFD6C8F")
MLDVDecoderPP;
#endif

EXTERN_C const CLSID CLSID_MLDVDecoderAbout;

#ifdef __cplusplus

class DECLSPEC_UUID("D0351C52-6531-40D6-A540-DFAA1BFD6C8F")
MLDVDecoderAbout;
#endif
#endif /* __DVDECODERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
