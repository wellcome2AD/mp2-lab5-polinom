#pragma once
#include "THeadList.h"
#include "TMonom.h"

class TPolinom : public THeadList<TMonom> {
public:
	TPolinom() {
		TMonom m(0, 0, 0, -1);
		pHead->value = m;
	}

	void AddMonom(const TMonom m) {
		if (pLast->value > m) {
			InsLast(m);
			return;
		}
		for (Reset(); !IsEnd(); GoNext()) {
			if (pCurr->value == m) {
				pCurr->value += m;
				if (pCurr->value.coef == 0)
					DelCurr();
				break;
			}
			if (m > pCurr->value) {
				InsCurr(m);
				break;
			}
		}
	}
};
