#pragma once
#include <iostream>

int intcmp(const int* arr1, const int* arr2, int size=3) {
	for (; size; size--, arr1++, arr2++) {
		if (*arr1 > * arr2)
			return 1;
		else if (*arr1 < *arr2)
			return -1;
	}
	return 0;
}

struct TMonom {
	double coef;
	int x, y, z;

	TMonom(double _coef, int _x, int _y, int _z) : coef(_coef), x(_x), y(_y), z(_z) {}

	TMonom operator+(const TMonom& m) const
	{
		TMonom res(*this);
		res.coef += m.coef;
		return res;
	}

	TMonom& operator+=(const TMonom& m)
	{
		return *this = *this + m;
	}

	bool operator==(const TMonom& m) const{
		int arr1[] = { x, y, z };
		int arr2[] = { m.x, m.y, m.z };
		return intcmp(arr1, arr2, sizeof(arr1) / sizeof(int)) == 0;
	}
	bool operator>(const TMonom& m) const{
		int arr1[] = { x, y, z };
		int arr2[] = { m.x, m.y, m.z };
		return intcmp(arr1, arr2, sizeof(arr1) / sizeof(int)) > 0;
	}
	bool operator<(const TMonom& m) const {
		int arr1[] = { x, y, z };
		int arr2[] = { m.x, m.y, m.z };
		return intcmp(arr1, arr2, sizeof(arr1) / sizeof(int)) < 0;
	}
	friend std::ostream& operator<<(std::ostream& os, const TMonom& m) {
		return os << m.coef << ' ' << "x^" << m.x << ' ' << "y^" << m.y << ' ' << "z^" << m.z << '\n';
	}
	friend std::istream& operator>>(std::istream& is, TMonom& m) {
		is >> m.coef >> m.x >> m.y >> m.z;
		return is;
	}
};