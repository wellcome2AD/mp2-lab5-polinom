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
	ASSERT_EQ(TPolinom(), "0");
}

TEST(TPolinom, can_add_monom)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	ASSERT_EQ(polinom, "1*x^2*y^3*z^4");
}

TEST(TPolinom, can_copy_polinom_with_one_monom)
{
	TPolinom polinom;
	TMonom monom(1, 2, 3, 4);
	polinom.AddMonom(monom);
	ASSERT_EQ(TPolinom(polinom), "1*x^2*y^3*z^4");
}

TEST(TPolinom, can_copy_polinom_with_several_monoms)
{
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(4, 5, 0, 9));
	polinom.AddMonom(TMonom(-7, 3, 2, 7));
	ASSERT_EQ(TPolinom(polinom), "4*x^5*z^9-7*x^3*y^2*z^7+1*x^2*y^3*z^4");
}

TEST(TPolinom, can_sum_polinoms_with_one_monom)
{
	TPolinom polinom1, polinom2;
	polinom1.AddMonom(TMonom(1, 2, 3, 4));
	polinom2.AddMonom(TMonom(-1, 2, 3, 4));
	TPolinom polinom3 = polinom1 + polinom2;
	ASSERT_EQ(polinom3, "0");
}

TEST(TPolinom, can_sum_polinoms_with_several_monoms)
{
	TPolinom polinom1, polinom2;
	polinom1.AddMonom(TMonom(4, 5, 1, 9));
	polinom1.AddMonom(TMonom(3, 3, 0, 2));
	polinom1.AddMonom(TMonom(1, 2, 3, 4)); // 1) сокращаются

	polinom2.AddMonom(TMonom(-7, 3, 2, 7));
	polinom2.AddMonom(TMonom(-8, 3, 0, 7));
	polinom2.AddMonom(TMonom(-1, 2, 3, 4));// 1) сокращаются

	TPolinom polinom3 = polinom1 + polinom2;

	ASSERT_EQ(polinom3, "4*x^5*y^1*z^9-7*x^3*y^2*z^7-8*x^3*z^7+3*x^3*z^2");
}

TEST(TPolinom, can_mul_by_num)
{
	TPolinom polinom;
	polinom.AddMonom(TMonom(3, 1, 0, 0));
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(-5, 6, 7, 8));
	polinom *= 4;
	ASSERT_EQ(polinom, "-20*x^6*y^7*z^8+4*x^2*y^3*z^4+12*x^1");
}

TEST(TPolinom, can_mul_by_monom)
{
	TPolinom polinom;
	polinom.AddMonom(TMonom(3, 1, 0, 0));
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.AddMonom(TMonom(-5, 6, 7, 8));
	polinom *= TMonom(4, 1, 2, 3);
	ASSERT_EQ(polinom, "-20*x^7*y^9*z^11+4*x^3*y^5*z^7+12*x^2*y^2*z^3");
}

TEST(TPolinom, can_print_polinom)
{
	TPolinom polinom1, polinom2;
	polinom1.AddMonom(TMonom(4, 5, 1, 9));
	polinom1.AddMonom(TMonom(3, 3, 0, 2));
	polinom1.AddMonom(TMonom(1, 2, 3, 4)); // 1) сокращаются

	polinom2.AddMonom(TMonom(-7, 3, 2, 7));
	polinom2.AddMonom(TMonom(-8, 3, 0, 7));
	polinom2.AddMonom(TMonom(-1, 2, 3, 4));// 1) сокращаются
	
	std::stringstream str_stream;
	TPolinom polinom = polinom1 + polinom2;
	std::string expected;

	str_stream << polinom;
	str_stream >> expected;

	ASSERT_EQ(polinom, expected);
}

TEST(TPolinom, can_read_polinom)
{
	TPolinom polinom;
	std::string expected = "4*x^5*y^1*z^9-7*x^3*y^2*z^7-8*x^3*z^7+3*x^3*z^2";
	std::stringstream str_stream;
	str_stream << expected;
	str_stream >> polinom;
	ASSERT_EQ(polinom, expected);
}
