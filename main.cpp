#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include <string>

#include "vector.cpp"

using namespace std;

int main() {
	cout << __cplusplus;
	vector<ofstream> files;

	size_t num = 6;

	for (size_t i = 0; i < num; i++) {
		string f_name =  to_string(i) + ".txt";
		ofstream f( f_name );
		files.push_back(move(f));
	}
	mt19937 Rand{ random_device{}() };
	Rand.seed(time(NULL));
	shuffle(files.begin(), files.end(), Rand);
	
	for (size_t i = 0; i < files.size(); i++)
	{
		files[i] << i << endl;
		files[i].close();
	}
}