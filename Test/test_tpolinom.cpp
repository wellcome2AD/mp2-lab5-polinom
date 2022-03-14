#include "gtest.h"
#include "..\mp2-lab5-polinom\TPolinom.h"
#include <sstream>

TEST (TMonom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom(0,0,0,0));
}

TEST(TPolinom, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinom);
}

TEST(TPolinom, can_add_monom)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	ASSERT_EQ(polinom.GetCurrVal(), monom);
}

TEST(TPolinom, can_insert_first)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.InsFirst(monom);
	polinom.GoNext();
	ASSERT_EQ(polinom.GetCurrVal(), monom);
}

TEST(TPolinom, can_insert_current)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.InsCurr(monom);
	ASSERT_EQ(polinom.GetCurrVal(), monom);
}

TEST(TPolinom, can_insert_last)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.InsLast(monom);
	polinom.GoNext();
	ASSERT_EQ(polinom.GetCurrVal(), monom);
}

TEST(TPolinom, can_copy_polinom)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	ASSERT_NO_THROW(TPolinom(polinom));
}

TEST(TPolinom, can_sum_polinoms)
{
	TPolinom polinom1, polinom2;
	polinom1.AddMonom(TMonom(1, 2, 3, 4));
	polinom2.AddMonom(TMonom(-1, 2, 3, 4));
	TPolinom polinom3 = polinom1 + polinom2;
	ASSERT_EQ(polinom3.GetCurrVal(), TMonom(0, 2, 3, 4));
}

TEST(TPolinom, can_print_polinom)
{
	std::ostringstream strout;
	std::string("");
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(5, 6, 7, 8));
	polinom = polinom + polinom;
	strout << polinom;
	//ASSERT_EQ(strout, string);
}