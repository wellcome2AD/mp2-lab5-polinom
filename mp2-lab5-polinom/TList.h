#pragma once
#include <iostream>
using namespace std;

struct TMonom {
	double coef;
	int x, y, z;

	bool operator==(const TMonom& m) {
		return (x == m.x && y == m.y && z == m.z);
	}
	bool operator>(const TMonom& m) {
		return (x > m.x && y > m.y && z > m.z);
	}
	bool operator<(const TMonom& m) {
		return (x < m.x && y < m.y && z < m.z);
	}
	friend ostream& operator<<(ostream& os, const TMonom& m){
		//printf("coef = %f; x^%d y^%d z^%d\n", m.coef, m.x, m.y, m.z);
		return os << m.coef << ' ' << "x^" << m.x << ' ' << "y^" << m.y << ' ' << "z^" << m.z << '\n';
	}
	friend istream& operator>>(istream& is, TMonom& m) {
		is >> m.coef >> m.x >> m.y >> m.z;
		return is;
	}
};

template <class T>
struct TNode{
	T value;
	TNode* pNext;

	TNode(const T& _val, TNode* next = NULL) : value(_val), pNext(next) {}
};

template <class T>
class TList{
protected:
	TNode<T>* pFirst, *pLast, *pStop, *pCurr, *pPrev;
	int len;

public:
	TList() :pFirst(NULL), len(0), pLast(NULL), pStop(NULL), pCurr(NULL), pPrev(NULL) {}
	
	class iterator
	{
		TNode<T>* pCurr;
	public:
		iterator() {}
		iterator(const iterator& iter) : pCurr(iter.pCurr) {}
		iterator& operator=(const iterator& iter) { pCurr = iter.pCurr; }

		iterator& operator++() // prefix
		{
			pCurr = pCurr->pNext;
			return *this;
		}

		iterator operator++(int) // postfix
		{
			iterator iter = *this;
			++(*this);
			return iter;
		}

		T& operator*()
		{
			return pCurr->value;
		}

		bool operator==(const iterator& iter)
		{
			return pCurr == iter.pCurr;
		}

		bool operator!=(const iterator& iter)
		{
			return !(*this == iter);
		}

		friend TList;
	private:
		iterator(TNode<T>* current) : pCurr(current) {}
	};

	iterator begin() { iterator iter(pFirst); return iter; }
	iterator end() { return iterator(pStop); }

	void InsFirst(T _value) {
		TNode<T>* pNew = new TNode<T>(_value, pFirst);
		pFirst = pNew;
		len++;
		if (len == 1) {
			pLast = pNew;
		}
	}

	void InsLast(T _value) {
		TNode<T>* pNew = new TNode<T>(_value, pStop);
		if (pLast == pStop) {
			pFirst = pNew;
		}
		else {
			pLast->pNext = pNew;
		}
		pLast = pNew;
		len++;
		pLast = pNew;
	}

	void InsCurr(T _value) {
		if (pCurr == pFirst) {
			InsFirst(_value);
			pCurr = pFirst;
		}
		else if (pCurr == pLast) {
			InsLast(_value);
			pCurr = pLast;
		}
		else {
			TNode<T>* pNew = new TNode<T>(_value, pCurr);
			pPrev->pNext = pNew;
			pCurr = pNew;
			len++;
		}
	}

	void DelCur() {
		if (pCurr == NULL)
			return;
		pPrev->pNext = pCurr->pNext;
		pCurr = pCurr->pNext;
	}

};
