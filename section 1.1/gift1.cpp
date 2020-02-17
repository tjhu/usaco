/*
ID: maitian1
PROG: gift1
LANG: C++14
*/
#include <fstream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned short WORD;

class person
{
public:
	string name;
	WORD InitialMoney;
	short Balance = 0;

	person(string n);
	vector<string> recivers;
	void GiveMoney(person& thatdude);
	
};

person::person(string n)
{
	this->name = n;
}

void person::GiveMoney(person& thatdude)
{
	if (!this->name.compare(thatdude.name))
		return;
	if (this->InitialMoney == 0)
		return;
	WORD HowMuchIGive = this->InitialMoney / (WORD)(this->recivers.size());
	for (auto reciver : this->recivers)
	{
		if (!reciver.compare(thatdude.name))
		{
			this->Balance -= HowMuchIGive;
			thatdude.Balance += HowMuchIGive;
		}
	}
}

void init(ifstream& fin, vector<person>& group)
{
	WORD NumOfReciver;
	string buffer;
	fin >> buffer;
	auto boy = group.begin();
	for (; boy != group.end(); ++boy)
	{
		if (!boy->name.compare(buffer))
		{
			break;
		}
	}

	fin >> boy->InitialMoney >> NumOfReciver;
	for (WORD i = 0; i < NumOfReciver; ++i)
	{
		fin >> buffer;
		boy->recivers.push_back(buffer);
	}
}


int main() 
{
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");
	string buffer;
	// Allocate memory for group
	WORD count;
	fin >> count;
	vector<person> group;
	for (WORD i = 0; i < count; ++i)
	{
		fin >> buffer;
		group.push_back(person(buffer));
	}

	// Init
	for (WORD i = 0; i < count; ++i)
	{
		init(fin, group);
	}
	// Give away money
	for (auto& giver : group)
	{
		for (auto& reciver : group)
		{
			giver.GiveMoney(reciver);
		}
	}
	for (auto person : group)
	{
		fout << person.name << ' ' << person.Balance << endl;
	}
	
	fin.close();
	fout.close();
	return 0;
}

