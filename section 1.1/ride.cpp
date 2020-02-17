/*
ID: maitian1
PROG: ride
LANG: C++14
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ofstream fout("ride.out");
	ifstream fin("ride.in");
	string sA, sB, output;
	fin >> sA >> sB;
	unsigned int iA = 1, iB = 1;
	for (auto i : sA)
	{
		iA *= (i - 'A' + 1);
	}
	for (auto i : sB)
	{
		iB *= (i - 'A' + 1);
	}

	output = (iA % 47 == iB % 47) ? "GO" : "STAY";

	fout << output << endl;
	fin.close();
	fout.close();
	return 0;
}