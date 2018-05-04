#include <iostream>

using namespace std;
class Parent
{
protected:
	int* ptr;
public:
	Parent() {
		ptr = new int;
		*ptr = 0;
		cout << "Parent: constructor is called\n";
	}
	~Parent() {
		cout << "Parent: destructor is called\n";
		delete ptr;
	}
	virtual void setValue(int x) { *ptr = x; };
	int getValue() { return *ptr; };
};
class Child : public Parent
{
public:
	Child() {
		*ptr = 1;
		cout << "Child: constructor is called\n";
	}
	~Child() {
		cout << "Child: destructor is called\n";
	}
	void setValue(int x) { *ptr = x + 1; };
	int getValue() { return *ptr + 1; };
};
int main() {
	Child* childPtr = new Child();
	Parent* parentPtr = new Parent();
	Parent* parentChildPtr = new Child();
	childPtr->setValue(1);
	parentPtr->setValue(1);
	parentChildPtr->setValue(1);
	cout << childPtr->getValue() << endl;
	cout << parentPtr->getValue() << endl;
	cout << parentChildPtr->getValue() << endl;
	delete childPtr;
	delete parentPtr;
	delete parentChildPtr;
	return 0;
}
