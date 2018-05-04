#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int count_the_word(string, string, int); // First string: want to detect / Second string: compare
bool is_it_have_astroid(string);
int how_many_it_have_astroid(string);
int get_count(const char* body, int body_size,  char** seg, int* seg_len, int seg_total_size, int seg_count); // Get all count when * exist

int main()
{
	ifstream inFile;
	int word_number;
	string* word; // word
	int* word_count; // number of word
	int* astroid_num; // number of *
	string body_str = ""; // This is dummy string to get str

	inFile.open("input.txt");
	if (!inFile)// if file cannot read, Then return 0;
		return 0;

	inFile >> word_number;

	word = new string[word_number];
	word_count = new int[word_number];
	astroid_num = new int[word_number];

	for (int i = 0; i < word_number; i++)
	{
		inFile >> word[i];
		word_count[i] = 0;
		astroid_num[i] = how_many_it_have_astroid(word[i]);
	}
	
	while (inFile >> body_str) // I will detect count simultaneously reading.
	{
		for (int i = 0; i < word_number; i++)
			word_count[i] += count_the_word(word[i], body_str, astroid_num[i]); // Count the word number in string.
	}
	
	inFile.close();

	for (int i = 0; i < word_number; i++)
		cout << word_count[i] << endl << endl; // output

	return 0;
}

int count_the_word(string detect, string body, int astroid_num)
{
	int count = 0;

	if (body.size() < detect.size() - astroid_num)
		return 0; // Do not need to compare

	if (astroid_num < 1)
	{
		for (int i = 0; i <= body.size() - detect.size(); i++) // initial
		{
			for (int j = 0; j < detect.size(); j++)
			{
				if (detect[j] == '?')
				{
					if (j == detect.size() - 1)
						count++; // j is last. i.e. compare string: ab?
					continue; // ? => continue
				}
				else if (toupper(detect[j]) != toupper(body[i + j]))
					break;
				if (j == detect.size() - 1)
					count++;
			}
		}
	}
	else // astroid_num > 0
	{
		int segment_number;
		char** segment;
		int* segment_len;

		if (detect[detect.size() - 1] == '*')
			segment_number = how_many_it_have_astroid(detect);
		else
			segment_number = how_many_it_have_astroid(detect) + 1;

		segment = new char*[segment_number];
		segment_len = new int[segment_number];

		for (int i = 0; i < segment_number; i++)
			segment[i] = new char[detect.size()];

		for (int i = 0; i < detect.size(); i++)
		{
			static int count_ = 0;
			static int count__ = 0;
			if (detect[i] == '*')
			{
				segment_len[count_] = count__;
				count_++;
				count__ = 0;
				if (i == detect.size() - 1)
					count_ = 0;
				continue;
			}
			segment[count_][count__] = detect[i];
			count__++;
			if (i == detect.size() - 1)
			{
				segment_len[count_] = count__;
				count_ = 0;
				count__ = 0;
			}
		} // Make the segment divided by *. i.e. ab*cd => ab / cd

		count = get_count(body.c_str(), body.size(), segment, segment_len, segment_number, 0);
	}
	
	return count;
}

bool is_it_have_astroid(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '*')
			return true;
	}
	return false;
}

int how_many_it_have_astroid(string str)
{
	int count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '*')
			count++;
	}
	return count;
} 

int get_count(const char* body, int body_size, char** seg, int* seg_len, int seg_total_size, int seg_count) // Use recursion to get count on * exist.
{
	if (seg_count >= seg_total_size)
		return 1; // compare with all segment and already exist all count.
	else
	{
		int count = 0;

		for (int i = 0; i < body_size; i++)
		{
			for (int j = 0; j < seg_len[seg_count]; j++)
			{
				if (seg[seg_count][j] == '?')
				{
					if (j == seg_len[seg_count] - 1)
						count += get_count(body + i + seg_len[seg_count], body_size - i - seg_len[seg_count], seg, seg_len, seg_total_size, seg_count + 1);
					continue;
				} // '?' case, skip
				if (toupper(seg[seg_count][j]) != toupper(body[i + j]))
					break;
				if (j == seg_len[seg_count] - 1)
					count += get_count(body + i + seg_len[seg_count], body_size - i - seg_len[seg_count], seg, seg_len, seg_total_size, seg_count + 1); // remove before and segment word of body. ex) segment: ab, body: 1abcde => consider 'de'
			}
		}

		return count;
	}
}