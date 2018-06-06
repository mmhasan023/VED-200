



#ifndef __IDeinterlace_Ex_INTERFACE_DEFINED__
#define __IDeinterlace_Ex_INTERFACE_DEFINED__

//#include "DeinterlaceEx_i.c"
/* interface IDeinterlace */
/* [unique][helpstring][uuid][object] */ 

EXTERN_C const IID IID_IDeinterlace_Ex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    //MIDL_INTERFACE("0075EC3C-C807-42a8-A6FF-9FD8ECF97D1B")
	MIDL_INTERFACE("C22DE86E-83E7-422d-9175-3EFE97CE52E4")
		IDeinterlace_Ex : public IDeinterlace
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FlipCheck( 
            /* [retval][out] */ bool *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FlipCheck( 
            /* [in] */ bool newVal) = 0;
    };
#endif
#endif