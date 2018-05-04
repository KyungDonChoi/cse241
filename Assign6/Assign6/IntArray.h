#pragma once
#include <iostream>

class IntArray
{
private:
	int nelements;
	int *elements;
public:	IntArray() {
		nelements = 0;
		elements = new int;
		*elements = 0; // Basic constructor
	}	IntArray(int num) {
		nelements = 1;
		elements = new int;
		*elements = num; // Basic constructor: initialize
	}

	IntArray(const IntArray& IntArr) {
		nelements = IntArr.nelements;
		elements = new int[nelements];
		for (int i = 0; i < nelements; i++)
			elements[i] = IntArr.elements[i]; // Copy constructor;
	}
	~IntArray() {
		nelements = 0;
		delete[] elements;
	}
	int pop() {
		if (empty())
			throw "Error: invalid memory";

		nelements--;

		int* new_arr;
		int old = top();

		new_arr = new int[nelements];

		for (int i = 0; i < nelements; i++)
			new_arr[i] = elements[i + 1];

		delete[] elements;

		elements = new int[nelements];

		for (int i = 0; i < nelements; i++)
			elements[i] = new_arr[i];

		delete[] new_arr;

		return old;
	}
	bool empty() const {
		if (nelements == 0)
			return true;
		else
			return false;
	}
	int top() const {
		if (empty())
			throw "Error: invalid memory";
		return elements[0];
	}
	void push(int num) {
		nelements++;

		int* new_arr;

		new_arr = new int[nelements];
		new_arr[nelements - 1] = num;

		for (int i = 0; i < nelements - 1; i++)
			new_arr[i] = elements[i];

		delete[] elements;

		elements = new int[nelements];

		for (int i = 0; i < nelements; i++)
			elements[i] = new_arr[i];

		delete[] new_arr;
	}
	int& operator[](int i) {
		if (i >= nelements)
			throw "Error: invalid memory";

		return elements[i];
	}
	IntArray& operator=(const IntArray& IntArr) {
		if (this == &IntArr)
			return *this;
		nelements = IntArr.nelements;
		delete[] elements;
		elements = new int[nelements];
		for (int i = 0; i < nelements; i++)
			elements[i] = IntArr.elements[i];
		return *this;
	}
	void appendCopyAtEnd(const IntArray& IntArr) {
		int old = nelements;

		nelements += IntArr.nelements;

		int* new_arr;
		new_arr = new int[nelements];

		for (int i = 0; i < old; i++)
			new_arr[i] = elements[i];
		for (int i = old; i < nelements; i++)
			new_arr[i] = IntArr.elements[i - old];

		delete[] elements;
		elements = new int[nelements];

		for (int i = 0; i < nelements; i++)
			elements[i] = new_arr[i];

		delete[] new_arr;
	}
	friend std::ostream& operator<<(std::ostream& os, const IntArray& arg)
	{
		for (int i = 0; i<arg.nelements; i++) {
			os << arg.elements[i] << ' ';
		}
		return os;
	}
};

