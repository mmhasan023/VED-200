#ifndef _MAC_ADDRESS_LIST_H_INCLUDE_
#define _MAC_ADDRESS_LIST_H_INCLUDE_

#ifndef MAX_ADAPTER_ADDRESS_LENGTH
#define MAX_ADAPTER_ADDRESS_LENGTH 8
#endif

#include <vector>
using namespace std;

class CMacAddress
{
public:
	CMacAddress()
	{
		memset( byteData, 0, sizeof(TCHAR)*MAX_ADAPTER_ADDRESS_LENGTH );
	};
	CMacAddress( const CMacAddress& address )
	{
		*this = address;
	};
	CMacAddress( LPBYTE lpMacAddress )
	{
		memcpy( byteData, lpMacAddress, sizeof(BYTE)*MAX_ADAPTER_ADDRESS_LENGTH );
	};
	~CMacAddress(){};
public:
	void operator=(const CMacAddress& op)
	{
		memcpy( byteData, op.byteData, sizeof(BYTE)*MAX_ADAPTER_ADDRESS_LENGTH );
	};


public:
	BYTE byteData[MAX_ADAPTER_ADDRESS_LENGTH];
};

typedef vector<CMacAddress> VECTOR_MACADDRESS, *LPVECTOR_MACADDRESS;
typedef VECTOR_MACADDRESS::iterator VECTOR_MACADDRESSIter;

#endif