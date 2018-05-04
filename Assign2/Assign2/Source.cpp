#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// I used the word 'DA' means Dynamic Array.

using namespace std;

int* convert_vector_to_DArr(vector<int>);
int* select_sort_algorithm(int*, int);
void answering_the_assign(vector<string>, vector<int>, vector<int>, string, int, bool&, int);

int main()
{
	vector<string>* vec_str_ptr;
	vector<int>* vec_int_ptr;
	vector<int>* vec_int_value_ptr;
	vector<int>* vec_int_count_ptr;
	int* counter;
	int* sum;
	int** length;
	int Test_Case;
	ifstream inFile;

	inFile.open("input.txt");

	inFile >> Test_Case; // Input the Test Case: How many the program run?

	vec_str_ptr = new vector<string>[Test_Case]; // make vector<string> DA. The string is broken piles.
	vec_int_ptr = new vector<int>[Test_Case]; // make vector<int> DA. The int is length of the piles. (vec_int_ptr[i][j] means jth string's length in ith test case.)
	vec_int_value_ptr = new vector<int>[Test_Case]; // make vector<int> DA. The int is the series of length of input.
	vec_int_count_ptr = new vector<int>[Test_Case]; // make vector<int> DA. The int is the count of length of input.
	length = new int*[Test_Case]; // make int* DA. length[i] is Dynamic Array version of vec_int_ptr to handle easy.
	counter = new int[Test_Case]; // make int DA. counter[i] means the total string number of ith test case
	sum = new int[Test_Case]; // make int DA. sum[i] means the summation of string in ith test case

	for (int i = 0; i < Test_Case; i++)
	{
		counter[i] = 0;
		sum[i] = 0;

		while (true)
		{
			string str;

			static bool ignore_is_okay = false; // if it is true, then we ignore .ignore() function.

			if (!ignore_is_okay)
				inFile.ignore(); // If we use getline, we use this first.

			ignore_is_okay = true;

			getline(inFile, str);

			if (str == "" && counter[i] == 0)
			{
				continue;
			}
			if (str == "")
				break;

			vec_str_ptr[i].push_back(str);
			vec_int_ptr[i].push_back(str.length());

			sum[i] += str.length();

			counter[i]++;
		}
	} // Input Clear!

	inFile.close();

	bool can_divide_2 = true;

	for (int i = 0; i < Test_Case; i++)
	{
		if (counter[i] % 2 != 0)
		{
			can_divide_2 = false;
			cout << "Input Error!" << endl;
			return 0;
		}
	} // First Error Case (Input Error: 2N)

	for (int i = 0; i < Test_Case; i++)
	{
		length[i] = convert_vector_to_DArr(vec_int_ptr[i]);
		length[i] = select_sort_algorithm(length[i], vec_int_ptr[i].size());
	} // Convert vector to Dynamic Array to handle easy

	// Description: I sorted length array small to large. So I can check how many string that has each length.
	// ex) input: 100 1 10 01 1 001
	// Then vec_int_ptr == [3, 1, 2, 2, 1, 3]
	// length == [1, 1, 2, 2, 3, 3]

	for (int i = 0; i < Test_Case; i++)
	{
		for (int j = 0; j < vec_int_ptr[i].size(); j++)
		{
			static int count = 0;
			static int value = length[i][j];
			

			if (length[i][j] > value)
			{
				vec_int_count_ptr[i].push_back(count);
				vec_int_value_ptr[i].push_back(value);
				value = length[i][j];
				count = 0;
			}

			count++;

			if (j == vec_int_ptr[i].size() - 1)
			{
				vec_int_count_ptr[i].push_back(count);
				vec_int_value_ptr[i].push_back(value);
				if (i < Test_Case - 1)
					value = length[i + 1][0];
				count = 0;
			}

			// There is exception!
			// When j is last, then we can't compare anymore.
			// So put count and value to vectors.
			// And prepare next test case. We know that initialize is zero.
		}
	} // make 2 room array dynamic array to search value || count easy

	for (int i = 0; i < Test_Case; i++)
	{
		for (int j = 0; j < vec_int_count_ptr[i].size(); j++)
		{
			if (vec_int_count_ptr[i][j] != vec_int_count_ptr[i][vec_int_count_ptr[i].size() - j - 1])
			{
				cout << "Input Error! 2" << endl;
				return 0;
			}
		}
	} // Second Error Case (the pair is not correct)

	for (int i = 0; i < Test_Case; i++)
	{
		for (int j = 0; j < vec_int_value_ptr[i].size(); j++)
		{
			if (sum[i] * 2 / counter[i] != vec_int_value_ptr[i][j] + vec_int_value_ptr[i][vec_int_value_ptr[i].size() - j - 1])
			{
				cout << "Input Error! 3" << endl;
				return 0;
			}
		}
	} // Third Error Case (the pair sum is not constant)

	// Handling Error Clear!

	bool switch_ = false;

	for (int i = 0; i < Test_Case; i++)
	{
		int whole_length = sum[i] * 2 / counter[i];
		answering_the_assign(vec_str_ptr[i], vec_int_count_ptr[i], vec_int_value_ptr[i], "", -1, switch_, whole_length);
		switch_ = false;
		cout << endl;
	}

	return 0;
}

int* convert_vector_to_DArr(vector<int> arr_)
{
	int size = arr_.size();
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = arr_[i];

	return arr;
}

int* select_sort_algorithm(int* arr, int size) // sort with selection_sort
{
	for (int i = 0; i < size; i++)
	{
		int min = arr[i];
		int min_pos = i;
		for (int j = i; j < size; j++)
		{
			if (min > arr[j])
			{
				min = arr[j];
				min_pos = j;
			}
		}
		arr[min_pos] = arr[i];
		arr[i] = min;
	}
	return arr;
}

void answering_the_assign(vector<string> str, vector<int> counter, vector<int> value, string sample, int pos, bool& switch_, int whole_length) 
// str is pile, counter is count, value is value, sample is candidate for answer (initialize will be ""), pos is minimum counter of length(initialize will be -1), if switch_ is true, then all of function won't work, whole_length is whole length.
{
	// In this program, we find the solution with compare some of combination on broken piles.
	// We can calculate whole length of complete pile. So find minimum length of piles to run (combination the piles) fast, and compare with 2nd minimum's combination.
	// So I used recursion function.
	if (sample == "")
	{
		int min = 2147483647; // dummy data.
		int min_value;

		for (int i = 0; i < counter.size(); i++)
		{
			if (min > counter[i])
			{
				min = counter[i];
				pos = i;
			}
		}

		min_value = value[pos];

		for (int i = 0; i < str.size(); i++)
		{
			for (int j = 0; j < str.size(); j++)
			{
				if (str[i].length() == value[pos] && str[j].length() == value[counter.size() - pos - 1])
				{
					if (value[pos] == value[counter.size() - pos - 1] && j < str.size() - 1)
					{
						if (str[i] == str[j])
							continue; // prevent to consider pick string again on minimum counter is whole length / 2.
					}
					answering_the_assign(str, counter, value, str[i] + str[j], pos, switch_, whole_length); // think str[i] + str[j] is answer
					answering_the_assign(str, counter, value, str[j] + str[i], pos, switch_, whole_length); // think str[j] + str[i] is answer
				}
			}
		}
	} // Basic (Fundamental)
	else if (!switch_) // initial: switch_ == false;
	{
		int min = 2147483647; // dummy data
		int min_value;

		for (int i = 0; i < counter.size(); i++)
		{
			if (i == pos || value[i] > whole_length / 2)
				continue; // prevent to consider same length
			if (min > counter[i])
			{
				min = counter[i];
				pos = i;
			}
		}

		// So pos is 2nd minimum length.
		// If there is only one case, then skip this.

		min_value = value[pos];

		bool concentrate_true = false;

		for (int i = 0; i < str.size(); i++)
		{
			for (int j = 0; j < str.size(); j++)
			{
				if (str[i].length() == value[pos] && str[j].length() == value[counter.size() - pos - 1])
				{
					if (str[i] + str[j] == sample || str[j] + str[i] == sample)
						concentrate_true = true;
				}
			}
		}
		if (concentrate_true)
		{
			cout << sample << endl;
			switch_ = true; // End this test case's function.
		}
	}
}