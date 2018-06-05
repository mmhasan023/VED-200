//Sort algorithm demonstration

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

template<typename T>
class CSort {
protected:
	T *m_pData; int m_nCount; time_t m_dwElapsed;

	class CTimeRecorder {
		time_t& m_rWriteTo, m_dwBegin;
	public:
		CTimeRecorder(time_t& rTo): m_rWriteTo(rTo), m_dwBegin(clock()) { }
		~CTimeRecorder() { m_rWriteTo=clock()-m_dwBegin; }
	};
	template<typename V> static void Swap(V& a, V& b) { V c; c=a; a=b; b=c; }

public:
	//Construction
	CSort(T *pArr, int nCnt): m_pData(pArr), m_nCount(nCnt) { }
	virtual ~CSort() { }
	virtual void Sort() = 0;

	//Elapsed time
	time_t GetElapsedTime() const { return m_dwElapsed; }
};

template<typename T>
class CBubbleSort: public CSort<T> {
public:
	CBubbleSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CSelectionSort: public CSort<T> {
public:
	CSelectionSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CInsertionSort: public CSort<T> {
public:
	CInsertionSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CQuickSort: public CSort<T> {
public:
	CQuickSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CMergeSort: public CSort<T> {
public:
	CMergeSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CHeapSort: public CSort<T> {
	void FixHeap(T *dt, int start, int end);
public:
	CHeapSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CShellSort: public CSort<T> {
public:
	CShellSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
class CRadixSort: public CSort<T> {
public:
	CRadixSort(T *p, int n): CSort<T>(p, n) {};
	void Sort();
};

template<typename T>
void CBubbleSort<T>::Sort()
{
	int i,j, flag=1; CTimeRecorder rec(m_dwElapsed);
	for(i=0;i<m_nCount && flag;i++)
		for(j=flag=0;j<m_nCount-i-1;j++)
			if(m_pData[j]>m_pData[j+1]) { flag=1; Swap(m_pData[j], m_pData[j+1]); }
}

template<typename T>
void CSelectionSort<T>::Sort()
{
	int i,j,k; CTimeRecorder rec(m_dwElapsed);
	for(i=0;i<m_nCount-1;i++) {
		for(k=i, j=i+1;j<m_nCount;j++) if(m_pData[k]>m_pData[j]) k=j;
		Swap(m_pData[k], m_pData[i]);
	}
}

template<typename T>
void CInsertionSort<T>::Sort()
{
	int i,j; T r;
	CTimeRecorder rec(m_dwElapsed);
	for(i=1;i<m_nCount;i++) {
		for(j=i-1, r=m_pData[i];j>=0 && m_pData[j]>r;j--) m_pData[j+1]=m_pData[j];
		m_pData[j+1]=r;
	}
}

template<typename T>
void CShellSort<T>::Sort()
{
	int i,j,k,l; T r; 
	CTimeRecorder rec(m_dwElapsed);
	for(i=1;i<m_nCount;k=i, i=i*3+1);
 
	do {
		for(l=0;l<k;l++)
			for(i=l+k;i<m_nCount;i+=k) {
				for(j=i-k, r=m_pData[i];j>=l && m_pData[j]>r;j-=k)
					m_pData[j+k]=m_pData[j];
				m_pData[j+k]=r;
			}
		k=(k-1)/3;
	}
	while(k>=1);
}
 
template<typename T>
void CQuickSort<T>::Sort()
{
	CTimeRecorder rec(m_dwElapsed);
	//sorting boundary, pivot index, and traveling pointers for partition step
	int lo, hi, mid, loguy, higuy;
 
	//stack for saving sub-array to be processed
	int lostk[40], histk[40], stkptr=0;
	lo=0; hi=m_nCount-1; //initialize limits
 
	while(1) {
		mid=lo+( ((hi-lo)+1) /2); //find middle element
		Swap(m_pData[mid], m_pData[lo]); //swap it to beginning of array
 
/* Would it be better to use insertion sort, when hi-lo is very small?
			for(loguy=lo+1; loguy<=hi; loguy++) {
				for(higuy=loguy-1, r=m_pData[loguy]; higuy>=lo && m_pData[higuy]>r;
					higuy--) m_pData[higuy+1]=m_pData[higuy];
				m_pData[higuy+1]=r;
			}
*/
		loguy=lo; higuy=hi+1;
		while(1) {
			do loguy++; while (loguy<=hi && m_pData[loguy]<=m_pData[lo]);
			do higuy--; while (higuy>lo && m_pData[higuy]>=m_pData[lo]);
 
			if(higuy<loguy) break;
			Swap(m_pData[loguy], m_pData[higuy]);
		}
		Swap(m_pData[lo], m_pData[higuy]); //put pivot element in place
 
		if( higuy-1-lo >= hi-loguy ) {
			if(lo+1<higuy) { //save big recursion for later
				lostk[stkptr]=lo; histk[stkptr]=higuy-1; ++stkptr;
			}
			if(loguy<hi) { lo=loguy; continue; } //do small recursion
		}
		else {
			if(loguy<hi) { //save big recursion for later
				lostk[stkptr]=loguy; histk[stkptr]=hi; ++stkptr;
			}
			if(lo+1<higuy) { hi=higuy-1; continue; } //do small recursion
		}
 
		--stkptr; //pop subarray from stack
		if(stkptr>=0) { lo=lostk[stkptr]; hi=histk[stkptr]; }
		else break; //all subarrays done--sorting finished.
	}
}
 
template<typename T>
void CHeapSort<T>::FixHeap(T *dt, int start, int end)
{
	T root( dt[start] ); int j;
	for(j=(start<<1); j<=end; j<<=1) {
		if(j<end && dt[j]<dt[j+1]) j++; if(root>=dt[j]) break;
		dt[j>>1]=dt[j];
	}
	dt[j>>1]=root;
}

template<typename T>
void CHeapSort<T>::Sort()
{
	CTimeRecorder rec(m_dwElapsed);
	int i; T *dt=m_pData-1; //dt is a 1-based index for m_pData
	//construct the heap.
	for(i=m_nCount/2;i>=1;i--) FixHeap(dt, i, m_nCount);
 	//Perform sorting now~
	for(i=m_nCount;i>0;) { Swap(dt[1], dt[i]); i--; FixHeap(dt, 1, i); }
}
 
template<typename T>
void CMergeSort<T>::Sort()
{
	int i,j,a,b,c,d; CTimeRecorder rec(m_dwElapsed);
	T *pTmp=new T[m_nCount], *orig=m_pData, *dest=pTmp;
 
	for(i=1;i<m_nCount;i<<=1) {
		for(j=0;j<m_nCount;j+=(i<<1)) { //for each fragment,
			d=j+(i<<1); if(d>m_nCount) d=m_nCount;
			if(j+i>=m_nCount) { //Copy the remaining elems
				for(a=j;a<m_nCount;a++) dest[a]=orig[a]; break;
			}
 
			for(a=c=j,b=j+i; c<d; c++)
				if((orig[a]<=orig[b] && a<j+i) || b==d) dest[c]=orig[a], a++;
				else dest[c]=orig[b], b++;
		}
		Swap(orig, dest);
	}
	if(orig!=m_pData) memcpy(m_pData, orig, sizeof(T)*m_nCount);
	delete []pTmp;
}
 
template<typename T>
void CRadixSort<T>::Sort()
{
#define BITOF(i,b) ((unsigned char *)orig)[i*sizeof(T)+b]
//#define BITOF(i,b) ((orig[i])>>(b<<3))&0xff
	CTimeRecorder rec(m_dwElapsed); int b,i, count[256], index[256];
	T *pTmp=new T[m_nCount], *orig=m_pData, *dest=pTmp;
	for(b=0;b<sizeof(T);b++) {
		memset(count, 0, sizeof(count));
		for(i=0;i<m_nCount;i++) count[ BITOF(i,b) ]++;
		index[0]=0;
		for(i=1;i<256;i++) index[i]=index[i-1]+count[i-1];
		for(i=0;i<m_nCount;i++)
			dest[index[BITOF(i,b)]++]=orig[i];
		Swap(orig, dest);
	}
#undef BITOF

	if(orig!=m_pData) memcpy(m_pData, orig, sizeof(T)*m_nCount);
	delete []pTmp;
}

/*
int main(int argc, const char *argv[])
{
	int N, *arr, *ar2, i,j; CSort<int> *srt;
	N=argc>1 ? atoi(argv[1]): 100; arr=new int[N], ar2=new int[N];
	srand(time(0));
	for(i=0;i<N;i++) {
		arr[i]= rand(); if(N>20000) arr[i]|=(rand()<<16); //make number bigger
	}

	for(i=0;i<8;i++) {
		memcpy(ar2, arr, sizeof(int)*N);
		if(N>30000 && i<=2) continue; //O(n^2) algorithms are too slow
		switch(i) {
		case 0: srt=new CBubbleSort<int>(ar2, N); printf("BubbleSort: "); break;
		case 1: srt=new CSelectionSort<int>(ar2, N); printf("SelectionSort: "); break;
		case 2: srt=new CInsertionSort<int>(ar2, N); printf("InsertionSort: "); break;
		case 3: srt=new CHeapSort<int>(ar2, N); printf("HeapSort: "); break;
		case 4: srt=new CQuickSort<int>(ar2, N); printf("QuickSort: "); break;
		case 5: srt=new CMergeSort<int>(ar2, N); printf("MergeSort: "); break;
		case 6: srt=new CShellSort<int>(ar2, N); printf("ShellSort: "); break;
		case 7: srt=new CRadixSort<int>(ar2, N); printf("RadixSort: "); break;
		}
		srt->Sort();
		printf("%.3g sec\n", srt->GetElapsedTime()/(double)CLOCKS_PER_SEC);
		for(j=0;j<20;j++) printf("%d ", ar2[j]); puts("\n"); delete srt;
	}

	delete []arr; delete []ar2;
	return 0;
}
*/