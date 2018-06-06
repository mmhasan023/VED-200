//XmlElementDef.h

#ifndef _XML_ELEMENT_DEFINE_H_INCLUDE_
#define _XML_ELEMENT_DEFINE_H_INCLUDE_

//Plug-In Define
#define _XE_ALGORITHM_METHOD_LIST   _T("algorithm-method-list")
	#define _XE_ALGORITHM_METHOD        _T("algorithm-method")
			#define _XATT_ALGORITHM_METHOD_FILE   _T("file")
			#define _XATT_ALGORITHM_METHOD_FLAG   _T("flag")
			#define _XATT_ALGORITHM_METHOD_COMMON _T("common")
			#define _XATT_ALGORITHM_METHOD_TYPE   _T("type")
//			#define _XATT_ALGORITHM_METHOD_THREAD _T("thread")
		#define _XE_ALGORITHM_METHOD_OPEN     _T("open")
		#define _XE_ALGORITHM_METHOD_FUNC     _T("function")
		#define _XE_ALGORITHM_METHOD_CLOSE    _T("close")
		#define _XE_ALGORITHM_METHOD_CALLBACK _T("callback")
		#define _XE_ALGORITHM_METHOD_FINISHED _T("finished-stream")
		#define _XE_ALGORITHM_METHOD_SET_OPT  _T("set-option")
	//_XE_ALGORITHM_METHOD
//_XE_ALGORITHM_METHOD_LIST


//Check Profile Define
#define _XE_CHECK_PROFILE _T("checkprofile")
	#define _XE_CHECK_VIDEO   _T("checkvideo")
		#define _XE_ITEM _T("item")
			#define _XATT_ID _T("id")
			#define _XE_OPTIONS _T("options")
				#define _XATT_COUNT _T("count")
					#define _XEOPTION _T("option")
						#define _XATT_OPTION_NAME _T("name")
						#define _XATT_OPTIONVALUE _T("value")
	//_XE_CHECK_VIDEO
	#define _XE_CHECK_AUDIO   _T("checkaudio")

	//_XE_CHECK_VIDEO

//_XE_CHECK_PROFILE

#define _X_ATT_SENSITIVITY _T("Sensitivity")
//#define _X_ATT_THREAD_MULTIT  _T("multi")//thread의 그룹
//#define _X_ATT_THREAD_SINGLE  _T("single")////thread의 그룹, single 그룹은 모든 그룹내의 멤버를 한 thread에서 처리

#endif//_XML_ELEMENT_DEFINE_H_INCLUDE_