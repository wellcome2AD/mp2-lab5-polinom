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

	explicit TMonom(double _coef = 0, int _x = 0, int _y = 0, int _z = -1) : coef(_coef), x(_x), y(_y), z(_z) {}

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
	bool operator==(int m) const {
		return TMonom(m, 0, 0, 0) == *this;
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
	TMonom operator*(double coef) const
	{
		return TMonom(this->coef * coef, x, y, z);
	}
	TMonom operator*(const TMonom& monom) const
	{
		return TMonom(coef * monom.coef, x + monom.x, y + monom.y, z + monom.z);
	}
	template <class T>
	TMonom& operator*=(T coef)
	{
		return *this = *this * coef;
	}
	friend std::ostream& operator<<(std::ostream& os, const TMonom& m) {
		os << m.coef;
		if (m.x != 0)
		{
			os << '*' << "x^" << m.x;
		}
		if (m.y != 0)
		{
			os << '*' << "y^" << m.y;
		}
		if (m.z != 0)
		{
			os << '*' << "z^" << m.z;
		}
		return os;
	}
	friend std::istream& operator>>(std::istream& is, TMonom& m) {
		is >> m.coef >> m.x >> m.y >> m.z;
		return is;
	}
};
