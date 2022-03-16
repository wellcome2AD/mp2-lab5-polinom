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

}
