
#ifndef _MACROS_H_
#define _MACROS_H_

//define media extension
#define _EXT_AVI  _T("AVI")
#define _EXT_AVIs _T("avi")

#define _EXT_MPG  _T("MPG")
#define _EXT_MPGs _T("mpg")

#define _EXT_MXF  _T("MXF")
#define _EXT_MXFs _T("mxf")

#define _EXT_WAV  _T("WAV")
#define _EXT_WAVs _T("wav")

#define _EXT_MPEG  _T("MPEG")
#define _EXT_MPEGs _T("mpeg")

#define _EXT_MP4  _T("MP4")
#define _EXT_MP4s _T("mp4")

#define _EXT_MPC  _T("MPC")
#define _EXT_MPCs _T("mpc")


#define _EXT_APE  _T("APE")
#define _EXT_APEs _T("ape")

#define _EXT_FLAC _T("FLAC")
#define _EXT_FLACs _T("flac")

#define _EXT_H264 _T("H264")
#define _EXT_H264s _T("h264")

#ifndef SAFE_RELEASE
#define SAFE_RELEASE( x )   \
    if ( x )                \
    {                       \
        x->Release();       \
        x = NULL;           \
    }
#endif

#define SAFE_ADDREF( x )    \
    if ( x )                \
    {                       \
        x->AddRef();        \
    }

#define SAFE_DELETE( x )    \
    if ( x )                \
    {                       \
        delete x;           \
        x = NULL;           \
    }

#define SAFE_ARRAYDELETE( x )   \
    if ( x )                    \
    {                           \
        delete[] x;             \
        x = NULL;               \
    }

#define SAFE_SYSFREESTRING( x ) \
    if ( x )                    \
    {                           \
        SysFreeString( x );     \
        x = NULL;               \
    }

#define SAFE_CLOSEHANDLE( x )               \
    if ( x && INVALID_HANDLE_VALUE != x )   \
    {                                       \
        CloseHandle( x );                   \
        x = NULL;                           \
    }


#endif // _MACROS_H_
