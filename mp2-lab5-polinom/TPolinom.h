#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <iostream>
#include <regex>
#include <string>

class TPolinom : public THeadList<TMonom> {
private :
	void InsFirst(TMonom value) { return __super::InsFirst(value); }
	void InsLast(TMonom value) { return __super::InsLast(value); }
	void InsCurr(TMonom value) { return __super::InsCurr(value); }
public:
	TPolinom() {
		TMonom m;
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
				return;
			}
			if (m > pCurr->value) {
				InsCurr(m);
				return;
			}
		}

		InsFirst(m);
	}
	
	TPolinom operator+(TPolinom pol) const
	{
		TPolinom res = *this;
		pol.Reset();
		res.Reset();
		while (!pol.IsEnd())
		{
			if (res.pCurr->value > pol.pCurr->value)
			{
				res.GoNext();
			}
			else if (res.pCurr->value < pol.pCurr->value)
			{
				res.InsCurr(pol.pCurr->value);
				pol.GoNext();
			}
			else
			{
				res.pCurr->value.coef += pol.pCurr->value.coef;
				if (res.pCurr->value.coef != 0)
				{
					res.GoNext();
				}
				else
				{
					res.DelCurr();
				}
				pol.GoNext();
			}
		}
		return res;
	}
	
	template <class T>
	TPolinom operator*(T coef) const
	{
		if (coef == 0)
			return TPolinom();
		TPolinom res(*this);
		for (res.Reset(); !res.IsEnd(); res.GoNext()) {
			res.pCurr->value *= coef;
		}
		return res;
	}
	
	template <class T>
	TPolinom& operator*=(T coef) {
		return *this = *this * coef;
	}
	
	friend std::istream& operator>>(std::istream& in, TPolinom& pol)
	{
		std::string str; //строка для считывания
		std::getline(in, str);
		std::string regex_string = R"(([\+\-]?\d+)(?:\*x\^(\d+))?(?:\*y\^(\d+))?(?:\*z\^(\d+))?)";//регулярное выражение
		std::regex pattern(regex_string);//шаблон
		std::smatch result;
		for (auto iter = str.cbegin();
			 iter != str.cend() && std::regex_search(iter, str.cend(), result, pattern);
			 iter = result[0].second)
		{
			int coef = GetNumberFromGroup(result, 1);
			int x = GetNumberFromGroup(result, 2);
			int y = GetNumberFromGroup(result, 3);
			int z = GetNumberFromGroup(result, 4);
			TMonom aMonom(coef, x, y, z);
			pol.AddMonom(aMonom);
		}
		return in;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const TPolinom& pol)
	{
		if (pol.len == 0)
			return out << 0;
		if (pol.pFirst != nullptr)
		{
			out << pol.pFirst->value;
			
			for (auto current = pol.pFirst->pNext; current != pol.pStop; current = current->pNext)
			{
				out << (current->value.coef >= 0 ? "+" : "");
				out << current->value;
			}
		}		
		return out;
	}

	static int GetNumberFromGroup(const std::smatch& theMatch, int theGroupNumber)
	{
		try
		{
			std::string match(theMatch[theGroupNumber].first, theMatch[theGroupNumber].second);
			return std::stoi(match);
		}
		catch (...)
		{
			return 0;
		}
	}
};
