#include <iostream>
#include "TPolinom.h"

int main() {
	TList<int> l;
	for (int i = 0; i < 10; i++) {
		l.InsCurr(i);
	}

	for (l.Reset(); !l.IsEnd(); l.GoNext()) {
		std::cout << l.GetCurrVal() << ' ';
	}
}