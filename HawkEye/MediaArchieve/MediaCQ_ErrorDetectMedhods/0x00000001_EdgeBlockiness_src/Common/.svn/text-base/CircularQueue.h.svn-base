//CircularQueue.h
//Circular Queue
//2008.5.16
//by kiok ahn
//kiokahn@korea.com

#ifndef _CIRCULAR_QUEUE_H_INCLUDE_
#define _CIRCULAR_QUEUE_H_INCLUDE_
#include <math.h>

//const int MAX_QUEUE_SIZE = 7;

template <class T>
class cqueue 
{
public:
	cqueue(const int& nQSize=7);
	virtual ~cqueue();

public:
	void  push   (const T& );
	T*    pop    (void );
	void  empty  (void );
	bool  IsEmpty(     ){return m_bEmpty;};

	//현재 기준 i번째 엘리먼트 리턴, -는 이전, +는 이후.
	T*    get    (int i);
	T*    Clear  (     );

	T*    rear   (     );
	T*    front  (     );
	T*    next   (T*   );
	T*    prev   (T*   );

	void SetPopMode(){m_bPopMode=!m_bPopMode;};
protected:
//	T*    m_Data[MAX_QUEUE_SIZE];
	T*    m_Data;

	int   m_nMaxQSize;
protected:
	int   MAX_QUEUE_SIZE;
	int   m_nRear ;
	int   m_nFront;
	bool  m_bEmpty;
	bool  m_bTurn ;
	bool  m_bPopMode;
};



////////////////////////////////////////////////////////////////////////////////
//구현부
////////////////////////////////////////////////////////////////////////////////

template <class T>
cqueue<T>::cqueue(const int& nQSize=7)
{
	MAX_QUEUE_SIZE = nQSize;
	m_nMaxQSize = MAX_QUEUE_SIZE;

	m_Data = new T[MAX_QUEUE_SIZE];

	m_nRear=m_nFront=m_bTurn=0;
	m_bPopMode=m_bEmpty=true;
}

template <class T>
cqueue<T>::~cqueue()
{
	delete[] m_Data; 
	//Clear();
}

template <class T>
T* cqueue<T>::rear()
{
	if(!m_bEmpty)
		return &m_Data[(m_nRear+MAX_QUEUE_SIZE-1)%MAX_QUEUE_SIZE];
	return NULL;
};

template <class T>
T* cqueue<T>::front()
{
	if(!m_bEmpty)
		return &m_Data[m_nFront];
	return NULL;
};

template <class T>
void cqueue<T>::push (const T& pushData)
{
	if(m_bTurn){
		//ASSERT(m_Data[m_nRear]);
		//m_Data[m_nRear]=(T)NULL;
		//delete ((T)m_Data[m_nRear]);
		m_nFront=(m_nFront +1) % MAX_QUEUE_SIZE;
	}

	//InPut Action
	m_Data[m_nRear] = pushData;
	m_nRear=(m_nRear+1) % MAX_QUEUE_SIZE;
	
	if(m_nRear==m_nFront) m_bTurn=true;
	
	m_bEmpty=false;

}

template <class T>
T*  cqueue<T>::pop  (void)
{
	//ASSERT(0);
	if(m_bEmpty||!m_bPopMode)return NULL;

	//OutPut Action
	int tmp = m_nFront;
	m_nFront = (m_nFront +1) % MAX_QUEUE_SIZE;
	
	if(m_nFront==m_nRear && !m_bEmpty)
	{
		m_bEmpty=true;
		m_bTurn=false;
	}
	return &m_Data[tmp];
}

template <class T>
void cqueue<T>::empty(void)
{
	m_nRear=m_nFront=m_bTurn=0;
	m_bEmpty=true;
}

template <class T>
T* cqueue<T>::get(int i)
{
	if( abs(i) >= MAX_QUEUE_SIZE ) 
		return NULL;

	if( m_bTurn==false && i >= m_nRear)
		return NULL;

	int nData = m_nFront + i;

	if(nData<0) nData = MAX_QUEUE_SIZE + nData;
	if(nData>=MAX_QUEUE_SIZE) nData = nData - MAX_QUEUE_SIZE ;
	return &(m_Data[nData]);
}
template <class T>
T* cqueue<T>::Clear()
{


	return NULL;
}

template <class T>
T* cqueue<T>::next(T* input)
{
	T* pCur = m_Data;
	for( int i=0 ; i<MAX_QUEUE_SIZE ; i++ )
	{
		if( pCur==input )
		{
			if( i== MAX_QUEUE_SIZE-1 ) return &(m_Data[0]);
			else return ++pCur;
		}
		pCur++;
	}
	return NULL;
}

template <class T>
T* cqueue<T>::prev(T* input)
{
	T* pCur = m_Data;
	for( int i=0 ; i<MAX_QUEUE_SIZE ; i++ )
	{
		if( pCur==input )
		{
			if( i== 0 ) return &(m_Data[MAX_QUEUE_SIZE-1]);
			else return --pCur;
		}
		pCur++;
	}
	return NULL;
}

#endif//_CIRCULAR_QUEUE_H_INCLUDE_