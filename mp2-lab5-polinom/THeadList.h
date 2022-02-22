#pragma once
#include "TList.h"

template <class T>
class THeadList : public TList<T> {
protected:
	TNode<T>* pHead;
public:
	THeadList(){
		pHead = new TNode<T>;
		pHead->pNext = pHead;
		TList<T>::pStop = pHead; //? это и ниже - не его поля, а "родителя"
		pLast = pFirst = pHead;
		pCurr = pPrev = pHead;
		len = 0; //? конструктор родителя проинициализирует нулём
	} //нужно ли явно вызывать конструктор TList<T>?

	~THeadList() { delete pHead; }
	void InsFirst(T val) {
		TList<T>::InsFirst(val);
		pHead->pNext = pFirst;
	}
	void DelFirst() {
		TList<T>::DelFirst();
		pHead->pNext = pFirst;
	}
};
