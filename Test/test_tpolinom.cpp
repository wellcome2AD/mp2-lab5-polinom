#include "gtest.h"
#include "..\mp2-lab5-polinom\TPolinom.h"
#include <sstream>

static bool operator==(const TPolinom& polinom, std::string expected)
{
	std::stringstream str_stream;
	str_stream << polinom;
	std::string res;
	getline(str_stream, res);
	return res == expected;
}

TEST(TPolinom, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinom());
}

TEST(TPolinom, can_add_monom)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	ASSERT_EQ(polinom, "1*x^2*y^3*z^4");
}

/*TEST(TPolinom, can_insert_first)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	monom = {-5, 6, 7, 8};
	polinom.InsFirst(monom);
	ASSERT_EQ(polinom, "-5*x^6*y^7*z^8 + 1*x^2*y^3*z^4");
}

TEST(TPolinom, can_insert_current)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.InsCurr(monom);
	ASSERT_EQ(polinom, "1*x^2*y^3*z^4 - 5*x^6*y^7*z^8");
}

TEST(TPolinom, can_insert_last)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.InsLast(monom);
	polinom.GoNext();
	ASSERT_EQ(polinom.GetCurrVal(), monom);
}
*/

TEST(TPolinom, can_copy_polinom)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	ASSERT_EQ(TPolinom(polinom), "1*x^2*y^3*z^4");
}

TEST(TPolinom, can_sum_polinoms)
{
	TPolinom polinom1, polinom2;
	polinom1.AddMonom(TMonom(1, 2, 3, 4));
	polinom2.AddMonom(TMonom(-1, 2, 3, 4));
	TPolinom polinom3 = polinom1 + polinom2;
	ASSERT_EQ(polinom3, "0");
}

TEST(TPolinom, can_mul_by_num)
{
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(-5, 6, 7, 8));
	polinom *= 4;
	ASSERT_EQ(polinom, "-20*x^6*y^7*z^8 + 4*x^2*y^3*z^4");
}

TEST(TPolinom, can_mul_by_monom)
{
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(-5, 6, 7, 8));
	polinom *= TMonom(4, 1, 2, 3);
	ASSERT_EQ(polinom, "-20*x^7*y^9*z^11 + 4*x^3*y^5*z^7");
}

TEST(TPolinom, can_print_polinom)
{
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(5, 6, 7, 8));
	polinom = polinom + polinom;
	ASSERT_EQ(polinom, "10*x^6*y^7*z^8 + 2*x^2*y^3*z^4");
}

TEST(TPolinom, can_read_polinom)
{
	TPolinom polinom;
	std::string expected = "5*x^6*y^7*z^8 + 1*x^2*y^3*z^4";
	std::stringstream str_stream;
	str_stream << expected;
	str_stream >> polinom;
	ASSERT_EQ(polinom, expected);
}
