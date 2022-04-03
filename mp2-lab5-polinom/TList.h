#pragma once

template <class T>
struct TNode {
	T value;
	TNode* pNext;

	TNode(const T& _val = T(), TNode* next = NULL) : value(_val), pNext(next) {}
};

template <class T>
class TList {
protected:
	TNode<T>* pFirst, * pLast, * pStop, * pCurr, * pPrev;
	int len;

protected:
	virtual void nulify()
	{
		pFirst = pLast = pStop = pCurr = pPrev = nullptr;
		len = 0;
	}

public:
	TList() :pFirst(nullptr), len(0), pLast(nullptr), pStop(nullptr), pCurr(nullptr), pPrev(nullptr) {}
	
	TList(const TList& theList) : TList()
	{
		for (TNode<T>* aCurrent = theList.pFirst;
			 aCurrent != theList.pStop;
			 aCurrent = aCurrent->pNext)
		{
			InsLast(aCurrent->value);
		}
	}
	
	~TList() {
		Reset();
		while (pCurr != pStop) {
			pPrev = pCurr;
			pCurr = pCurr->pNext;
			delete pPrev;
		}
	}
	
	TList& operator=(TList theList)
	{
		pFirst = theList.pFirst;
		pLast = theList.pLast;
		pStop = theList.pStop;
		pCurr = theList.pCurr;
		pPrev = theList.pPrev;
		len = theList.len;

		theList.nulify();

		return *this;
	}
	
	void InsFirst(T _value) {
		TNode<T>* pNew = new TNode<T>(_value, pFirst);
		pFirst = pNew;
		len++;
		if (len == 1) { pLast = pNew; }
	}

	void InsLast(T _value) {
		TNode<T>* pNew = new TNode<T>(_value, pStop);
		if (pLast == pStop)
			pFirst = pNew;
		else
			pLast->pNext = pNew;
		pLast = pNew;
		len++;
	}

	void InsCurr(T _value) {
		if (pCurr == pFirst) {
			InsFirst(_value);
			pPrev = pStop;
			pCurr = pFirst;
		}
		else if (pPrev == pLast) {
			InsLast(_value);
			pPrev = pLast;
		}
		else {
			TNode<T>* pNew = new TNode<T>(_value, pCurr);
			if (pPrev != nullptr)
			{
				pPrev->pNext = pNew;
			}
			pCurr = pNew;
			len++;
		}
	}

	void DelCurr() {
		if (pCurr != pStop) {
			if (pCurr == pFirst)
				DelFirst();
			else
			{
				if (pCurr == pLast)
				{
					pLast = pPrev;
				}

				TNode<T>* del = pCurr;
				pCurr = pCurr->pNext;
				pPrev->pNext = pCurr;
				delete del;
				len--;
				
			}
		}
	}

	void DelFirst() {
		if (pFirst != pStop) {
			TNode<T>* del = pFirst;
			pFirst = pFirst->pNext;
			delete del;
			len--;
			if (len == 0)
				pLast = pStop;
		}
	}

	T GetCurrVal() {
		if (pCurr != pStop)
			return pCurr->value;
	}

	void Reset() {
		pCurr = pFirst;
		pPrev = pStop;
	}

	void GoNext() {
		if (pCurr != pStop) {
			pPrev = pCurr;
			pCurr = pCurr->pNext;
		}
	}

	bool IsEnd() const { return pCurr == pStop; }
};
