/*
ID: maitian1
PROG: friday
LANG: C++14
*/
#include <fstream>
#include <iostream>
// Using cl to compile
using namespace std;

enum Date
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

inline Date operator+(Date date, int i)
{
	i = (i + (int)date) % 7;
	return Date(i);
}

inline Date operator+=(Date& date, int i)
{
	date = date + i;
	return date;
}

class Foo
{
private:
	struct DateCollection
	{
		// The first day is Monday
		int Monday = 0, Tuesday = 0, Wednesday = 0, Thursday = 0, Friday = 0, Saturday = 0, Sunday = 0;
	};

	// Variables
	DateCollection dateCollection;
	int year;
	int month;
	int day;
	int finalYear;
	bool bLeapYear;
	Date date;

	// Functions
	void FastForwardOneMonth();
	int DaysOfThisMonth();
	void IsLeapYear();

public:
	Foo(int n);
	void run();
	void init();
	void get(ofstream& fout);
};

Foo::Foo(int n)
{
	// Set initial day to one month before
	this->year = 1899;
	this->finalYear = this->year + n + 1;
	this->month = 12;
	this->day = 13;
	this->date = Wednesday;
	this->IsLeapYear();
}

void Foo::run()
{
	while (this->finalYear !=  this->year)
	{
		this->FastForwardOneMonth();
	}
}

void Foo::FastForwardOneMonth()
{
	// Get date of next month
	int days = DaysOfThisMonth();
	this->date += days;
	this->month++;
	if (this->month > 12)
	{
		this->year++;
		this->IsLeapYear();
		// Reset month
		this->month = 1;
	}
	if (this->finalYear == this->year)
		return;
	switch (this->date)
	{
	case Monday:
		this->dateCollection.Monday++;
		break;

	case Tuesday:
		this->dateCollection.Tuesday++;
		break;

	case Wednesday:
		this->dateCollection.Wednesday++;
		break;

	case Thursday:
		this->dateCollection.Thursday++;
		break;

	case Friday:
		this->dateCollection.Friday++;
		break;

	case Saturday:
		this->dateCollection.Saturday++;
		break;

	case Sunday:
		this->dateCollection.Sunday++;
		break;

	default:
		break;
	}

	// Move to next month

}

int Foo::DaysOfThisMonth()
{
	switch (this->month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
		break;

	case 2:
		if (bLeapYear)
			return 29;
		else
			return 28;
		break;

	default:
		return 31;
		break;
	}
	return 0;
}

void Foo::IsLeapYear()
{
	// Century years
	if (!(this->year % 100))
	{
		if (!(this->year % 400))
		{
			this->bLeapYear = true;
			return;
		}
		else
		{
			this->bLeapYear = false;
			return;
		}
	}
	// Non-century years
	if (!(this->year % 4))
	{
		this->bLeapYear = true;
		return;
	}
	else
	{
		this->bLeapYear = false;
		return;
	}
}

void Foo::get(ofstream& fout)
{
	DateCollection data = this->dateCollection;
	fout << data.Saturday << ' ' << data.Sunday << ' ' << data.Monday << ' '
		<< data.Tuesday << ' ' << data.Wednesday << ' ' << data.Thursday << ' '
		<< data.Friday << ' ';
}

void Foo::init()
{
	// Jump to 01/13/1900
	this->day = 13;
	this->date += (13 - 1);
	this->dateCollection.Monday++;
	this->IsLeapYear();
}

int main(void)
{
	ifstream fin("friday.in");
	ofstream fout("friday.out");
	int N = 0;
	fin >> N;
	fin.close();

	Foo foo(N);
	foo.run();
	foo.get(fout);
	fout.close();

	return 0;
}