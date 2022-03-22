#include <iostream>
#include <sstream>
#include <fstream>
#include "TPolinom.h"

using namespace std;

void write_to_file(const string& file_path, const TPolinom& polinomchik) {
	ofstream file(file_path);
	file << polinomchik;
	file.close();
}
const TPolinom read_from_file(string file_path) {
	TPolinom polinomchik;
	ifstream file(file_path);
	file >> polinomchik;
	file.close();
	return polinomchik;
}

int main() {
	TPolinom polinom1, polinom2;
	polinom1.AddMonom(TMonom(4, 5, 1, 9));
	polinom1.AddMonom(TMonom(3, 3, 0, 2));
	polinom1.AddMonom(TMonom(1, 2, 3, 4));

	polinom2.AddMonom(TMonom(-7, 3, 2, 7));
	polinom2.AddMonom(TMonom(-8, 3, 0, 7));
	polinom2.AddMonom(TMonom(-1, 2, 3, 4));

	TPolinom polinom3 = polinom1 + polinom2;

	
	cout << polinom3; //4*x^5*y^1*z^9-7*x^3*y^2*z^7-8*x^3*z^7 + 3*x^3*z^2
}
