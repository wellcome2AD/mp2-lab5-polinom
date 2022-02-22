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
		TList<T>::pStop = pHead; //? ��� � ���� - �� ��� ����, � "��������"
		pLast = pFirst = pHead;
		pCurr = pPrev = pHead;
		len = 0; //? ����������� �������� ����������������� ����
	} //����� �� ���� �������� ����������� TList<T>?

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
