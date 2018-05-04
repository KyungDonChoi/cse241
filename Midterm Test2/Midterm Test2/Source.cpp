#include <iostream>

using namespace std;

class parent {
private:
	int x, y;
public:
	parent()
	{
		cout << "Parent: Nothing construct" << endl;
	}
	parent(int a, int b)
	{
		cout << "Parent: parameter construct" << endl;
	}
	~parent()
	{
		cout << "Parent: destruct" << endl;
	}
	int a()
	{
		cout << 0 << endl;
		return 0;
	}
};

class child : public parent{
private:
	int z;
public:
	child()
	{
		cout << "Child: Nothing construct" << endl;
	}
	child(int a) : parent(a, a)
	{
		cout << "Child: parameter construct" << endl;
	}
	~child()
	{
		cout << "Child: destruct" << endl;
	}
	int a()
	{
		cout << 1 << endl;
		return 0;
	}
};

class a
{
private:
	parent par;
public:
	a()
	{
		cout << "a: construct" << endl;
	}
};

int main()
{
	parent par(10, 10); // constructor
	parent p = par; // copy

	return 0;
}