#pragma once
#include "TList.h"

template <class T>
class THeadList : public TList<T> {
protected:
	TNode<T>* pHead;
private:
	void initialize()
	{
		pHead = new TNode<T>();
		pHead->pNext = pHead;
		pStop = pHead;
		pLast = pFirst = pHead;
		pCurr = pHead;
		pPrev = nullptr;
		len = 0;
	}

protected:
	virtual void nulify() override
	{
		__super::nulify();
		pHead = nullptr;
	}
public:
	THeadList() {
		initialize();
	}
	~THeadList() {
		TList<T>::pStop = nullptr;
		if (TList<T>::pLast != nullptr)
			TList<T>::pLast->pNext = TList<T>::pStop;
		if (pHead != nullptr) {
			if (pHead->pNext == pHead) {
				TList<T>::pFirst = TList<T>::pLast = nullptr;
			}
			else {
				TList<T>::pFirst = pHead->pNext;
			}
		}
		delete pHead;
		pFirst = pStop;
	}
	THeadList(const THeadList& theList)
		: TList<T>::TList(theList)
	{
		pHead = new TNode<T>();
		TList<T>::pStop = pHead;
		TList<T>::pCurr /*= TList<T>::pPrev*/ = pHead;
		TList<T>::pPrev = nullptr;

		pHead->pNext = TList<T>::pFirst;
		if (TList<T>::pLast != NULL)
			TList<T>::pLast->pNext = TList<T>::pStop;

		pHead->value = theList.pHead->value;
	}

	THeadList& operator=(THeadList theList)
	{
		TList<T>::pFirst = theList.pFirst;
		TList<T>::pLast = theList.pLast;
		TList<T>::pStop = theList.pStop;
		TList<T>::pCurr = theList.pCurr;
		TList<T>::pPrev = theList.pPrev;
		TList<T>::len = theList.len;


		pHead = theList.pHead;

		theList.nulify();

		return *this;
	}
	void InsFirst(T val) {
		TList<T>::InsFirst(val);
		pHead->pNext = TList<T>::pFirst;
	}
	void DelFirst() {
		TList<T>::DelFirst();
		pHead->pNext = TList<T>::pFirst;
	}
};
