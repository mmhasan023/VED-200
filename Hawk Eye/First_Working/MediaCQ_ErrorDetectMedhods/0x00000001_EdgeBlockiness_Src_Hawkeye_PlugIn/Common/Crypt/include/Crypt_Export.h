
//TVSCode.h

#ifndef _PRODUCT_KEY_MANAGER_DLL_EXPORT_H_INCLUDE_
#define _PRODUCT_KEY_MANAGER_DLL_EXPORT_H_INCLUDE_

struct _TVSSERIAL{
	USHORT id1;
	USHORT id2;
	USHORT id3;
	USHORT id4;
};


extern "C" __declspec( dllimport )
int __stdcall I_KeyEncord( OUT _TVSSERIAL &id,//��� �ø��� ��ȣ. 
						   IN  const USHORT& iKnd,//2����Ʈ ���� �ڵ�
						   IN  const UCHAR& ucCountry,//1����Ʈ ���� �ڵ�
						   IN  const CHAR* szName);//�빮�� 2��.

extern "C" __declspec( dllimport )
int __stdcall I_KeyDecord( OUT INT& year  , OUT INT& month  , OUT INT& day,//Ű ������.
						   OUT UINT& serial, //2����Ʈ ���� �ڵ�
						   OUT UINT& country,//���� �ڵ�
						   OUT CHAR* szName,//�빮�� 2��.
						   IN  const _TVSSERIAL id);//�ø��� �ѹ�.

extern "C" __declspec( dllimport )
int __stdcall I_KeyAgree(  IN const CHAR* szCharID1,
						   IN const CHAR* szCharID2,
						   IN const CHAR* szCharID3,
						   IN const CHAR* szCharID4);
/*
extern "C" __declspec( dllimport )
int __stdcall I_KeyAgree01(  IN const CHAR* szChar );
*/

extern "C" __declspec( dllexport )
BOOL __stdcall I_StrEncord( IN     const CHAR* szInput,
						   OUT          CHAR* szEncorded   ,
						   IN OUT       int&  nSize        );

extern "C" __declspec( dllexport )
BOOL __stdcall I_StrDecord( IN  const CHAR* szInput      , 
						   OUT       CHAR* szDecorded   , 
						   IN  OUT   int&  nSize        );

#ifdef WIN64
	#ifdef UNICODE
		#ifdef _DEBUG
			#pragma comment(lib, "../common/Crypt/lib_x64/CryptDU.lib")
		#else
			#pragma comment(lib, "../common/Crypt/lib_x64/CryptRU.lib")
		#endif//_DEBUG
	#else
		#ifdef _DEBUG
			#pragma comment(lib, "../common/Crypt/lib_x64/CryptD.lib")
		#else
			#pragma comment(lib, "../common/Crypt/lib_x64/CryptR.lib")
		#endif//_DEBUG
	#endif
#else
	#ifdef UNICODE
		#ifdef _DEBUG
			#pragma comment(lib, "../common/Crypt/lib/CryptDU.lib")
		#else
			#pragma comment(lib, "../common/Crypt/lib/CryptRU.lib")
		#endif//_DEBUG
	#else
		#ifdef _DEBUG
			#pragma comment(lib, "../common/Crypt/lib/CryptD.lib")
		#else
			#pragma comment(lib, "../common/Crypt/lib/CryptR.lib")
		#endif//_DEBUG
	#endif
#endif
#endif//_PRODUCT_KEY_MANAGER_DLL_EXPORT_H_INCLUDE_

