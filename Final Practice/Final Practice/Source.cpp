#include <iostream>

using namespace std;

template<class T>
void swap1(T &x, T &y) {
	T temp = x;
	x = y;
	y = temp;
}


int main() {
	char* a = "aaaaa";
	char* b = "cccc";

	swap1(a, b);

	cout << a << endl << b << endl;
}