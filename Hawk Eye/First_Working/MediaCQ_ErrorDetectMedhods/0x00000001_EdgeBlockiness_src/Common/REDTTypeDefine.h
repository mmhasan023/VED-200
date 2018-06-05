//2008.11.7
//by kiok ahn
//각종 전송을 위한 데이터 타입 정의

#ifndef _TRANSFORM_TYPE_DEFINENITION_H_INCLUDE_
#define _TRANSFORM_TYPE_DEFINENITION_H_INCLUDE_

#include "iplDefine.h"
#include "NameInfo.h"
#include <list>
#include <map>
#include <string>

using namespace std;

typedef	list<CNameInfo> LIST_NAMEINFO,*LPLIST_NAMEINFO;
typedef LIST_NAMEINFO::iterator LIST_NAMEINFOItor;

typedef list<std::string> LIST_STRING, *LPLIST_STRING;

#ifdef UNICODE
	typedef std::wstring STD_TSTRING;
#else
	typedef std::string  STD_TSTRING;
#endif
typedef list<STD_TSTRING> LIST_TSTRING, *LPLIST_TSTRING;
typedef LIST_TSTRING::iterator LIST_TSTRINGIter;

#ifndef _VIDEO_CHECK_SERVICE
	#include "./MediaInfo/MediaInfoDLL.h"
	using namespace MediaInfoDLL;

	//typedef map <String, String> STR_MAP ,*LPSTR_MAP;
	//typedef pair<String, String> STR_PAIR;
	//typedef std::basic_string<TCHAR> String;

	typedef map <String, String>  STR_MAP   ,*LPSTR_MAP  ;
	typedef map <String, STR_MAP> STRMU_MAP ,*LPSTRMU_MAP;
	typedef pair<String, String>  STR_PAIR;
	typedef pair<String, STR_MAP> TAG_PAIR;
#endif


//다중 프로세서를 지원 할 경우 아래를 사용
//#define HAWKEYE_CHECK_SVR_PROCESS_WND_NAME _T("CheckingProcessor%08x")
#define HAWKEYE_CHECK_SVR_PROCESS_WND_NAME   _T("CheckingProcessor")
#define HAWKEYE_WINDOW_TITLE_DEFAULT         _T("Hawkeye_Check_Processor")
#define HAWKEYE_WINDOW_TITLE                 _T("Hawkeye_Check_Processor%08x")
//#define HAWKEYE_MEDIA_CHECK_PROCESS          _T("VCSExcution%08x.exe")
#define HAWKEYE_MEDIA_CHECK_PROCESS          _T("VCSExcution.exe")
//#define HAWKEYE_MEDIA_CHECK_MUTEX          _T("HawkeyeCheckSvrMutex%08x")
#define HAWKEYE_MEDIA_CHECK_MUTEX            _T("_HawkeyeCheckSvrMutex_")
#define HAWKEYE_PIPE_NAME                    _T("\\\\.\\pipe\\hawkeye_ipc%08x")
//#define HAWKEYE_PIPE_NAME                    _T("\\\\.\\pipe\\hawkeye_ipc")
#define HAWKEYE_PIPE_NAME_DEFAULT            _T("\\\\.\\pipe\\hawkeye_ipc")
#define HAWKEYE_KILL_CHECK_PROCESS          _T("KillProcess.exe")


#define DEFAULT_WIDTH    720
#define DEFAULT_HEIGHT   480

#define TIMECODE_VIDEO		9000
#define TIMECODE_AUDIO		8000

///////////////////////////////////////////////////////////////////////////
//
//QC 처리 옵션, dwProcessFlag에 대한 정의
//
// 사용예 = (CQ_CATELOG|CQ_SAVE_IMG|CQ_QC_ALL) = Hex(0x8000FFFF) = Dec(2147549183)
// Catalog와 QC를 동시진행, QC는 모든 알고리즘을 적용하고, 모든 검출 프레임은 이미지 파일로 저장.
//
#ifndef _CQ_PROCESS_FLAG_//32가지의 옵션이 존재 할 수 있음.
#define _CQ_PROCESS_FLAG_
#define CQ_ERROR                  0x00000000
#define CQ_CATELOG                0x80000000 // Shot Detection, Dec(2147483648), Catalog 프로세서 활성화, MediaCQ_CommonDataVideo
#define CQ_CATELOG_SHOT           CQ_CATELOG // MediaCQ_CommonDataVideo
#define CQ_CATELOG_SCENE          0x40000000 // Scene Detection, Dec(1073741824), Scene은 Shot을 포함, MediaCQ_CommonDataVideo, shot에대한 index만을 전송.
#define CQ_CATELOG_SS             0xC0000000 // CQ_CATELOG_SHOT | CQ_CATELOG_SCENE
//#define CQ_SAVE_IMG             0x00010000 // Dec(2147483648) 검출 프레임을 이미지 파일(jpeg)로 저장
//#define CQ_QC                   0x00008000 // Dec(36863), QC 프로세서 활성화 사용하지 않음.
#define CQ_QC_ALL                 0xFFFFFFFF // Dec(65535), 전체 알고리즘 활성화
#define CQ_QC_EDGE_BLOC           0x00000001 // QC 1번, Edge Block,사물의 가장자리로 블럭화가 발생하는 에러 검출.
#define CQ_QC_FS_STAR             0x00000002 // QC 2번, Check Full Screen Star, 전체 화면에 거처 번쩍이는 화이트 노이즈 에러 화면 검출.
#define CQ_QC_FS_BLACK            0x00000004 // QC 3번, Check Full Screen Black, 전체 화면에 거처 검정색 프레임이 삽입된 에러 검출.
#define CQ_QC_AU_MUTE             0x00000008 // QC 4번, Check Audio Mute, 오디오 묵음 검사.
#define CQ_QC_AU_VOLUME_LEVEL     0x00000010 // QC 5번, Compute Audio Level, 오디오 음압 측정      
#define CQ_QC_FLICKERING_EFFECT   0x00000020 // Flickering Effect
//#define CQ_QC_BOUNDARY_ERROR    0x00000020 // Screen Boundary Error
#define CQ_QC_BOUNDARY_MOVE       0x00000040 // Boundary Movement
#define CQ_QC_STRIPE_ERROR        0x00000080 // Video, Strtpe Error
//#define CQ_QC_FS_MACRO		  0x00000100 // QC 7번, Check Macro Block, 사용하지 않음, Block Error로 편입
#define CQ_QC_SINGLE_COLOR	      0x00000100 // video, Single color frame
#define CQ_QC_BLOCK_SMOOTHING     0x00000200 // Block Smoothing
#define CQ_QC_BLACK_BAR           0x00000400 // Block Bar
#define CQ_QC_COLOR_BARS          0x00000800 // Color Bars
//#define CQ_QC_MACRO_BLOCK       0x00000100 // Macro Block Error
#define CQ_QC_AU_TEST_TONE        0x00001000 // Audio  1KHz Test tone
#define CQ_QC_AU_CONST_FFREQ      0x00002000 // Audio  고정 주파수 검출, Test Tone, High Frequency Noise 검충
#define CQ_QC_FS_FREEZE           0x00004000 // QC 6번, Check Freezed Screen
#define CQ_QC_INTERLACE           0x00008000 // Video Interlace Detector
#define CQ_QC_AU_VOL_DROP         0x00010000 // Audio Volume drop
#define CQ_QC_BLOCK_ERROR         0x00020000 // Video Block Error
#define CQ_QC_AUDIO_LEVEL         0x00040000 // Audio Level Check
#define CQ_QC_AUDIO_ATTACK        0x00080000 // Audio Attack Error
#define CQ_QC_SAMPLINGRATE_ERROR  0x00100000 // Audio Sampling Rate Error
#define CQ_QC_JITTER_ERROR        0x00200000 // Audio jitter Error
#define CQ_QC_HAZARDOUS_CTS       0x00400000 // Hazardous Image Candidate
#define CQ_QC_BLOCKINESS		  0x00800000 // Video Blockiness
#define CQ_QC_LATTER_BOX	      0x01000000 // Video Latter box
#define CQ_QC_BRIGHT_LEVEL	      0x02000000 // Video Brightness Levels
#define CQ_QC_CHROMA_LEVEL	      0x04000000 // Video Chroma Levels
#define CQ_QC_CONTRAST_LEVEL      0x08000000 // Video Contrast Levels
#define CQ_QC_DROP_FRAME          0x10000000 // Video Drop Frame


//#define CQ_QC_MACRO_BLOCK_Except 0xFFFFFEFF     


/*
#define CQ_QC_VIDEO_PSNR      0x00000400 // Reference Video, PSNR (Peak-to-peak Signal to Noise Ratio)
#define CQ_QC_VIDEO_MSE       0x00000800 // Reference Video, MSE (Mean Square Error)
#define CQ_QC_VIDEO_DELTA     0x00001000 // Reference Video, Delta
#define CQ_QC_VIDEO_MSAD      0x00002000 // Reference Video, MSAD (Mean Square Absolute Difference???)
*/


//이미지 한장 전송하는 구분자.
//#define CQ_IMAGE_INCLUDE    (CQ_CATELOG_SHOT|CQ_QC_EDGE_BLOC|CQ_QC_FS_STAR|CQ_QC_FS_BLACK|CQ_QC_BOUNDARY_ERROR|CQ_QC_BOUNDARY_MOVE|CQ_QC_VIDEO_SLICE|CQ_QC_MACRO_BLOCK|CQ_QC_BLOCK_SMOOTHING) 

#define CQ_IMAGE_COMPARE      (CQ_QC_VIDEO_PSNR|CQ_QC_VIDEO_MSE|CQ_QC_VIDEO_DELTA|CQ_QC_VIDEO_MSAD)//이미지3장 + 동영상 전송        

// 오디오 검사 플레그를 구분하기위한 구분자.
// 오디오 검사 Method가 추가 될때마다 여기도 추가시켜 준다. 
#define CQ_AUDIO_CHECK        (CQ_QC_AU_MUTE            |\
							   CQ_QC_AU_VOLUME_LEVEL    |\
					           CQ_QC_AU_CONST_FFREQ     |\
							   CQ_QC_AU_TEST_TONE       |\
							   CQ_QC_AU_VOL_DROP        |\
							   CQ_QC_AUDIO_LEVEL        |\
							   CQ_QC_AUDIO_ATTACK       |\
							   CQ_QC_SAMPLINGRATE_ERROR |\
							   CQ_QC_JITTER_ERROR        )
							    
							   
							   

// 비디오 검사 Method가 추가 될때마다 여기도 추가시켜 준다. 
#define CQ_VIDEO_CHECK        (CQ_CATELOG_SHOT      |\
							   CQ_CATELOG_SCENE     |\
							   CQ_QC_EDGE_BLOC      |\
							   CQ_QC_FS_STAR        |\
							   CQ_QC_FS_BLACK       |\
							   CQ_QC_FS_FREEZE      |\
							   CQ_QC_FLICKERING_EFFECT |\
							   CQ_QC_BOUNDARY_MOVE  |\
							   CQ_QC_STRIPE_ERROR   |\
							   CQ_QC_BLOCK_SMOOTHING|\
							   CQ_QC_BLACK_BAR      |\
							   CQ_QC_COLOR_BARS     |\
							   CQ_QC_INTERLACE      |\
							   CQ_QC_LATTER_BOX		|\
							   CQ_QC_BRIGHT_LEVEL   |\
							   CQ_QC_BLOCK_ERROR    |\
							   CQ_QC_CONTRAST_LEVEL |\
							   CQ_QC_CHROMA_LEVEL   |\
							   CQ_QC_SINGLE_COLOR   |\
							   CQ_QC_BLOCKINESS		|\
							   CQ_QC_HAZARDOUS_CTS  |\
							   CQ_QC_DROP_FRAME     )
//							   CQ_QC_MACRO_BLOCK    
//							   CQ_QC_FS_MACRO		
#endif//_CQ_PROCESS_FLAG_
//
///////////////////////////////////////////////////////////////////////////

#define CQ_MAKE_BITMAP_VIDEO    (	CQ_VIDEO_CHECK)


#define CQ_MAKE_BITMAP_AUDIO    (	CQ_QC_AUDIO_LEVEL|CQ_QC_AU_MUTE|CQ_QC_AUDIO_ATTACK|CQ_QC_AU_TEST_TONE|CQ_QC_AU_CONST_FFREQ	)


#define _STR_FOURCC_SIZE       8
#define _MAX_METHOD_THREAD     4
#define _FRAME_WINDOW_SIZE     7
#define _BLUR_RESOLUTION 480+360 // 480x360
//#define _BLUR_RESOLUTION 720+480 // 480x360 //SK broad& 미디어 적용을 위한 작업

enum _EXECTION_TYPE{ _eUnknown, 
                     _eAVI    , 
					 _eWMV    , 
					 _eMXF    ,
					 _eMPG    , 
					 _eWAV    , 
					 _eWMA    , 
					 _eMP3    , 
					 _eFLAC   , 
					 _eAPE    , 
					 _eQT     , 
					 _eMXF_DV , 
					 _eAIFF   , 
					 _eSDI    , 
					 _eMP4    
};


//define media extension
#define _EXT_AVI   _T("AVI")
#define _EXT_MXF   _T("MXF")
#define _EXT_WAV   _T("WAV")
#define _EXT_WMA   _T("WMA")
#define _EXT_WMV   _T("WMV")
#define _EXT_MPG   _T("MPG")
#define _EXT_MP3   _T("MP3")
#define _EXT_APE   _T("APE")
#define _EXT_FLAC  _T("FLAC")
#define _EXT_MOV   _T("MOV")
#define _EXT_TS    _T("TS")
#define _EXT_TP    _T("TP")
#define _EXT_AIFF  _T("AIFF")
#define _EXT_MP4   _T("MP4")
#define _EXT_SDI   _T("SDI_CAPTURE")




enum _AL_MEDIA_TYPE {_AL_MEDIA_Unknow,_AL_MEDIA_Video, _AL_MEDIA_Audio};
#define _AL_TYPE_VIDEO _T("video")
#define _AL_TYPE_AUDIO _T("audio")

//#define _AL_TIME_OUT_CHECK_TIME   60000 // 1분
//#define _AL_TIME_OUT_CHECK_TIME  350000 // 5분
#define _AL_TIME_OUT_CHECK_TIME    700000 //10분, 네트웍이 느린 상태에서 체크 필요.
//#define _AL_TIME_OUT_CHECK_TIME 1400000 //20분
//#define _AL_TIME_OUT_CHECK_TIME 5600000 //80분

typedef struct tagAVOption
{
	WORD wMuteTime        ;//mute 검출 시간 (초 단위)
	BYTE byteShotSensitive;//샷 검출 민감도.(1~9)

}AVOPTION, *LPAVOPTION;
//_CQ_PROCESS_FLAG_의 옵션에 따라 출력 결과를 union으로 정의하는 것도 검토.
//_CQ_PROCESS_FLAG_에 따라 union으로 구분된 다른 종류의 구조체를 출력으로 결정 하는 방법 검토.

enum _AL_AUDIO_CHANNEL{ eAUDIO_AVERAGE   ,// 0
                        eAUDIO_LEFT      ,// 1
						eAUDIO_RIGHT     ,// 2 
						eAUDIO_CENTER    ,// 3
						eAUDIO_MID_LEFT  ,// 4
						eAUDIO_MID_RIGHT ,// 5
						eAUDIO_REAR_LEFT ,// 6
						eAUDIO_REAR_RIGHT,// 7
						eAUDIO_SUBWOOFER ,// 8

						eAUDIO_COUNT
};

enum _AL_RESULT_CONDITION{ eCONDITION_DETECTION,// 0
						   eCONDITION_ALARM    ,// 1

						   eCONDITION_COUNT
};

enum _FRAME_RATE_MODE{ eFRT_UNKNOW = 0,
                       eFRT_CONSTANT  ,//Contant  frame rate mode
					   eFRE_VARIABLE   //Variable frame rate mode
};

enum _SCAN_TYPE{ eST_UNKNOW = 0  ,
                 eST_PROGRESSIVE ,
				 eST_INTERLACED    
};

#ifndef TIMECODE_DEFINED
#define TIMECODE_DEFINED
typedef union _timecode {
	struct {
		WORD   wFrameRate;
		WORD   wFrameFract;
		DWORD  dwFrames;
	};
	DWORDLONG  qw;
} TIMECODE;

#endif /* TIMECODE_DEFINED */

typedef struct tagAVResult
{
	DWORD                dwDetectFlag              ;//0=No Error(Not Detected), return _CQ_PROCESS_FLAG_ 
	DOUBLE               dbPSNR                    ;//PSNR , dB(decibel)
	REFERENCE_TIME       rtStartTime               ;//audio current start position, 100 nanoseconds
	REFERENCE_TIME       rtEndTime                 ;//audio current end position, 100 nanoseconds
	UINT                 nFrameNumber              ;//detected frame number
	LPVOID               lpData                    ;
	DWORD                dwDataSize                ;
	LPBITMAPINFOHEADER   lpBih                     ;
	UINT                 nFrameStart               ;
	UINT                 nFrameEnd                 ;
	WORD			     wAudioChannel             ;//
	DOUBLE               dbAudioLevel[eAUDIO_COUNT];//dB(decibel), Average Volume Level from AudioGain

	LPVOID               lpvoid                    ;

	TIMECODE			 tcStart		   ;//RED, Embedded SDI와 RS422 타입일 경우 사용
	TIMECODE			 tcEnd			   ;//RED, Embedded SDI와 RS422 타입일 경우 사용

	time_t               tSystemTimeStart          ;//RED, 검출 당시의 System Time, 1970년 1월 1일 이후 지나간 초 
	time_t               tSystemTimeEnd            ;//RED, 검출 당시의 System Time, 1970년 1월 1일 이후 지나간 초 
	_AL_RESULT_CONDITION eResultCondition          ;//현재 구조체의 상태. RED에서 dwDetectFlag에 대한 알람 상태 확인
}AVRESULT, *LPAVRESULT;

typedef const LPAVRESULT LPCAVRESULT;

/*
typedef struct algAudio8Channel //오디오 24비트레이트 8채널용 구조체선언 by mingi 2010.3.18
{
	BYTE cFirbyte;
	BYTE cSecbyte;
	BYTE cThrbyte;
}Audio8Channel;
*/
typedef VOID (CALLBACK * LPFN_AVRESULT) ( LPAVRESULT lpAVResult, LPVOID  lpUserData );


typedef LPVOID HALGORITHMM, *LPHALGORITHMM ;//Algorithm Manager Handle
typedef LPVOID HCDVIDEO   , *LPHCDVIDEO    ;//Video Common Data Handle
typedef LPVOID HCDAUDIO   , *LPHCDAUDIO    ;//Audio Common Data Handle

typedef struct _tagAudioData
{
	REFERENCE_TIME rtStartTime    ;//audio current start position, 100 nanoseconds
	REFERENCE_TIME rtEndTime      ;//audio current end position, 100 nanoseconds
	REFERENCE_TIME rtDulation     ;//audio total time, 100 nanoseconds
	WORD           wChannels      ;//number of channels (i.e. mono, stereo, etc.) 
	WORD           wBitsPerSample ;//8bit or 16bit ...
	DWORD          dwSamplesPerSec;//sample rate 
	HCDAUDIO       hCAudio        ;//audio common data handle
	DWORD          dwWidth        ;//video, image width, default=720 ,if audio files
	DWORD          dwHeight       ;//video, image height, default=480 ,if audio files
}AUDIODATA, *LPAUDIODATA;

typedef struct _tagAudioFormat
{
	REFERENCE_TIME rtDulation     ;//audio total time, 100 nanoseconds
	WORD           wChannels      ;//number of channels (i.e. mono, stereo, etc.) 
	WORD           wBitsPerSample ;//8bit or 16bit ...
	DWORD          dwSamplesPerSec;//sample rate 
}AUDIOFORMAT, *LPAUDIOFORMAT;


typedef struct _tagVideoData
{
	double            dbSampleTime   ;//video current position
	double            dbFrameRate    ;//frames per second, if(eFrameRateMode==eFRE_VARIABLE) dbFrameRate is average frame rate.
	DWORD             dwWidth        ;//video, image width
	DWORD             dwHeight       ;//video, image height
	DWORD             dwBytes        ;//Bytes in 1 Pixel
	DWORD             dwCurrentFrame ;//video, Current Frame Number
	DWORD             dwTotalFrames  ;//video, Total Frames
	HCDVIDEO          hCVideo        ;//video common data handle

	//20110310, by Kiok Ahn
	_FRAME_RATE_MODE  eFrameRateMode ;//Frame rate mode, 
	DOUBLE            dMinFrameRate  ;//fps, Minimum frame rate
	DOUBLE            dMaxFrameRate  ;//fps, Maximum frame rate

	//20110513, by Kiok Ahn
	_SCAN_TYPE        eScanType      ;
}VIDEODATA, *LPVIDEODATA;

typedef struct _tagVideoFormat
{
	double         dbFrameRate    ;//frames per second
	DWORD          dwWidth        ;//video, image width
	DWORD          dwHeight       ;//video, image height
	DWORD          dwBytes        ;//Bytes in 1 Pixel
	DWORD          dwTotalFrames  ;//video, Total Frames
}VIDEOFORMAT, *LPVIDEOFORMAT;

typedef struct _ROIData
{
	RECT	ROIRect			;
	DWORD	dwOrgWidth	;
	DWORD	dwOrgHeight	;
} ROIDATA, *LPROIDATA;


typedef struct _tagAVData
{
	_AL_MEDIA_TYPE     eType        ;

	LPBYTE             lpData       ;//video,audio low data
	DWORD              dwDataSize   ;//video,audio low data size
	DWORD              dwProcessFlag;//need check process, _CQ_PROCESS_FLAG_
	LPBITMAPINFOHEADER lpBih        ;
	LPFN_AVRESULT      lpFnAVResult ;//result callback function
	LPVOID             lpUserData   ;
	LPVOID             lpvoid       ;

	ROIDATA			   ROIData	    ;
	AVOPTION           option       ;

	TIMECODE		   TimeCode		;

	union{
		AUDIODATA audio;
		VIDEODATA video;
	};
} AVDATA, *LPAVDATA;

typedef struct tagDShowMediaInfo
{
	DWORD     dwTotalFrame                  ;//TotalFrame 비디오 전체프레임(frames, int), direct-show의 정보
	DOUBLE    dTotalDulation                ;//TotalTime	비디오 전체 시간(second, double), direct-show의 정보
	DOUBLE    dFrameRate                    ;//FrameRate	비디오 프레임레이트(fps, double), direct-show의 정보
	CHAR      szVideoCodec[_STR_FOURCC_SIZE];//Encoding 인코딩형식(FOURCC, char[4])//http://www.fourcc.org/
	DWORD     dwVideoWidth                  ;//VideoWidth 비디오 Width(pixel, int), direct-show의 정보
	DWORD     dwVideoHeight                 ;//VideoHeight 비디오 Height(pixel, int), direct-show의 정보
	CHAR      szAudioCodec[_STR_FOURCC_SIZE];//AudioCodec  오디오코덱(FOURCC, char[4])//http://www.fourcc.org/
	DOUBLE    dAudioDulation                ;//AudioTime	오디오전체시간(second, double), direct-show의 정보
	WORD      wAudioChannels                ;//AudioChannel	오디오 채널(channel numbers, int), direct-show의 정보
	WORD      wAudioBitsPerSample           ;//AudioBPS	오디오 BitsPerSample(bit number, int), direct-show의 정보
	DWORD     dwAudioSamplePerSec           ;//AudioSamplePerSec	오디오 SamplePerSec(Hz, int), direct-show의 정보
}DSHOWMEDIAINFO, *LPDSHOWMEDIAINFO;

//미디어 정보.
typedef struct _tagMediaInformation
{
	DWORD     dwTotalFrame                  ;//TotalFrame 비디오 전체프레임(frames, int), direct-show의 정보
	DOUBLE    dTotalDulation                ;//TotalTime	비디오 전체 시간(second, double), direct-show의 정보
	DOUBLE    dFrameRate                    ;//FrameRate	비디오 프레임레이트(fps, double), direct-show의 정보
	CHAR      szVideoCodec[_STR_FOURCC_SIZE];//Encoding 인코딩형식(FOURCC, char[4])//http://www.fourcc.org/
	DWORD     dwVideoWidth                  ;//VideoWidth 비디오 Width(pixel, int), direct-show의 정보
	DWORD     dwVideoHeight                 ;//VideoHeight 비디오 Height(pixel, int), direct-show의 정보
	CHAR      szAudioCodec[_STR_FOURCC_SIZE];//AudioCodec  오디오코덱(FOURCC, char[4])//http://www.fourcc.org/
	DOUBLE    dAudioDulation                ;//AudioTime	오디오전체시간(second, double), direct-show의 정보
	WORD      wAudioChannels                ;//AudioChannel	오디오 채널(channel numbers, int), direct-show의 정보
	WORD      wAudioBitsPerSample           ;//AudioBPS	오디오 BitsPerSample(bit number, int), direct-show의 정보
	DWORD     dwAudioSamplePerSec           ;//AudioSamplePerSec	오디오 SamplePerSec(Hz, int), direct-show의 정보

#ifndef _VIDEO_CHECK_SERVICE
	STRMU_MAP mapMUMediaInfo                ;//"MediaInfo" Open Source를 활용한 미디어 정보
#endif
} MEDIAINFORMATION, *LPMEDIAINFORMATION;

typedef struct _tagCQInfoResult
{
//	HANDLE     nCQHandle              ;// 공통사항이므로 별도 관리 스택을 사용치 않음
//	LPVOID     lpUserData             ;// 공통사항이므로 별도 관리 스택을 사용치 않음
	HBITMAP    hBitmap                ;
	TCHAR      szThumbPath[MAX_PATH*2];
	AVRESULT   AVResult               ;
}CQINFORESULT, *LPCQINFORESULT;


#ifndef _VIDEO_CHECK_SERVICE
	//General Algorithm Function Type 
	typedef HRESULT (WINAPI* LPFN_ALGORITHM                )(HANDLE hHandle, LPAVDATA lpAVData);//Send Stream Data
	typedef HANDLE  (WINAPI* LPFN_ALGORITHM_OPEN           )(VOID             );//Create Handle
	typedef HRESULT (WINAPI* LPFN_ALGORITHM_CLOSE          )(HANDLE hHandle   );//Close Handle
	typedef HRESULT (WINAPI* LPFN_ALGORITHM_SET_CALLBACK   )(HANDLE hHandle, LPFN_AVRESULT lpCallback, LPVOID lpUserData);//SetCallback Data
	typedef HRESULT (WINAPI* LPFN_ALGORITHM_FINISHED_STREAM)(HANDLE hHandle   );//*User Selected*, Stream Finished
	typedef HRESULT (WINAPI* LPFN_ALGORITHM_SET_OPTION     )(HANDLE hHandle, LPSTR_MAP lpmapOption );//Set Option
#endif

const __int64 FILETIME_WEEK = (__int64)10000000*60*60*24*7;
const __int64 FILETIME_DAY  = (__int64)10000000*60*60*24;
const __int64 FILETIME_HOUR = (__int64)10000000*60*60;
const __int64 FILETIME_MIN  = (__int64)10000000*60;
const __int64 FILETIME_SEC  = (__int64)10000000; 

#ifndef MAX_PATH_DOUBLE
	#define MAX_PATH_DOUBLE 520
#endif


typedef struct tagInt24
{
	BYTE ucFirst;
	BYTE ucSecond;
	BYTE ucThird;
}INT24, *LPINT24;

class CInt24 : public INT24
{
public:
	CInt24(){
		memset( this, 0, sizeof(tagInt24) );
	};
	CInt24(const INT24& op){
		ucFirst  = op.ucFirst ;
		ucSecond = op.ucSecond;
		ucThird  = op.ucThird ;
	};

	virtual ~CInt24(){};


public:
	operator INT64()
	{
		return (INT64)ucFirst<<16 | (INT64)ucSecond<<8 | (INT64)ucThird;
	};
	operator UINT()
	{
		return (UINT)ucFirst<<16 | (UINT)ucSecond<<8 | (UINT)ucThird;
	};
	operator float()
	{
		return 0.f;
		//return (unsigned long)ucFirst<<8 | (unsigned long)ucSecond<<4 | (unsigned long)ucThird;
	};
	operator double()
	{
		if( ucThird & 0x80 ) //리틀인디안에서는 ucThird가 처음 최상위 비트. 부호연산자를 가짐.
		{
			INT nTmp = 0xFFFFFFFF - ( 0xFFFFFF - (ucThird<<16 | ucSecond<<8 | ucFirst ) );
			//nTmp INT형은 signed 32비트형이여야함.
			return (double)(nTmp);
		}
		else
			return   (unsigned long)ucFirst | (unsigned long)ucSecond<<8 | (unsigned long)ucThird<<16;
	};
	
};

#endif//_TRANSFORM_TYPE_DEFINENITION_H_INCLUDE_