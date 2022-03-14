#include <iostream>
#include <sstream>
#include <fstream>
#include "TPolinom.h"

using namespace std;

int main()
{

}

/*void write_to_file(const string& file_path, const TPolinom& polinomchik) {
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
	string str;
	stringstream ss;
	TPolinom polinom;
	polinom.AddMonom(TMonom(1, 2, 3, 4));
	polinom.InsLast(TMonom(5, 6, 7, 8));
	//polinom = polinom + polinom;
	ss << polinom;
	ss >> str;
	cout << str;
}*/