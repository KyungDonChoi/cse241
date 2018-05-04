#include <iostream>
#include <fstream>
#include <list>

using namespace std;

unsigned int make_reverse(unsigned int, unsigned int); // reverse function
bool is_it_pelindrome(unsigned int); // decision is it pelindrome or not
unsigned int pelindrome(unsigned int, int&); // recursion. find how many process it add.

int main()
{
	int Test_Case;
	ifstream inFile("input.txt");

	inFile >> Test_Case;

	for (int i = 0; i < Test_Case; i++)
	{
		unsigned int init_num;
		int count = 0;
		inFile >> init_num;
		unsigned int pelin = pelindrome(init_num, count);
		cout << count << " " << pelin << endl;
	}
}

unsigned int make_reverse(unsigned int process, unsigned int reversed) // former: process, latter: reversed
{
	if (process == 0)
		return reversed;
	else
		return make_reverse(process / 10, reversed * 10 + process % 10);
}

bool is_it_pelindrome(unsigned int pelin)
{
	list<unsigned int> pelin_list; // Use list to control int easy.
	unsigned int dummy = pelin; // We have to use while loop, so define dummy
	
	while (dummy != 0)
	{
		pelin_list.push_front(dummy % 10);
		dummy /= 10;
	}
	
	while (pelin_list.size() > 1) // it can be odd!
	{
		if (pelin_list.front() != pelin_list.back())
			return false;
		pelin_list.pop_back(); // remove back.
		pelin_list.pop_front(); // remove front.
	}

	return true;
}

unsigned int pelindrome(unsigned int pelin, int& count)
{
	if (count > 1000)
	{
		count = 0;
		return 0;
	}

	if (is_it_pelindrome(pelin))
		return pelin;

	unsigned int reverse = make_reverse(pelin, 0); // reverse pelindrome
	
	if (reverse > reverse + pelin || pelin > reverse + pelin) // If there occurs overflow
	{
		count = 0;
		return 0;
	}

	count++;

	return pelindrome(reverse + pelin, count); // recursion
}