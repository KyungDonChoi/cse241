#include <iostream>
#include <string>

using namespace std;

char change_lower(char); // This is the function to change char to capital. EX) a -> A

int main()
{
	int Test_Case;
	cin >> Test_Case;

	for (int n = 0; n < Test_Case; n++)
	{
		int row, column;
		int word_count;
		char** board;
		string* word; // String Pointer to set Dynamic allocate

		cin >> row >> column;

		board = new char*[row];

		for (int i = 0; i < row; i++)
			board[i] = new char[column];

		for (int i = 0; i < row; i++)
			cin >> board[i];

		cin >> word_count;

		word = new string[word_count];

		for (int i = 0; i < word_count; i++)
			cin >> word[i];

		// End to input.

		for (int i = 0; i < word_count; i++)
		{
			const char* ch = word[i].c_str(); // We use string as char pointer
			int word_len = word[i].length(); // Easy to see, we declare another var.

			int posit_row = 0;
			int posit_col = 0;
			int max = 0;

			// Initialize clear.

			for (int j = 0; j < row; j++)
			{
				for (int k = 0; k < column; k++)
				{
					for (int l = 0; l < word_len; l++) // Direct from up to down.
					{
						if (j + l >= row) // Out range for allocate
							break;
						if (change_lower(board[j + l][k]) != change_lower(ch[l]))
							break;
						if (l + 1 > max) // l + 1 means real size of same char.
						{
							max = l + 1; // Maximum changed
							posit_row = j;
							posit_col = k;
							// Position saved.
						}
						// This code will run and can answer to the problem if we assume there must be 'answer!'
						// If there is not answer, it will print similar answer.
						// Below codes are similar with this code.
					}
					for (int l = 0; l < word_len; l++) // Direct from down to up
					{
						if (j - l < 0)
							break;
						if (change_lower(board[j - l][k]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}
					for (int l = 0; l < word_len; l++) // Direct from left to right
					{
						if (k + l >= column)
							break;
						if (change_lower(board[j][k + l]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}
					for (int l = 0; l < word_len; l++) // Direct from right to left
					{
						if (k - l < 0)
							break;
						if (change_lower(board[j][k - l]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}
					for (int l = 0; l < word_len; l++) // Direct from up to down, left to right (Diagonal)
					{
						if (j + l >= row || k + l >= column)
							break;
						if (change_lower(board[j + l][k + l]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}
					for (int l = 0; l < word_len; l++) // Direct from down to up, left to right (Diagonal)
					{
						if (j - l < 0 || k + l >= column)
							break;
						if (change_lower(board[j - l][k + l]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}
					for (int l = 0; l < word_len; l++) // Direct from up to down, right to left (Diagonal)
					{
						if (j + l >= row || k - l < 0)
							break;
						if (change_lower(board[j + l][k - l]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}
					for (int l = 0; l < word_len; l++) // Direct from down to up, right to left (Diagonal)
					{
						if (j - l < 0 || k - l < 0)
							break;
						if (change_lower(board[j - l][k - l]) != change_lower(ch[l]))
							break;
						if (l + 1 > max)
						{
							max = l + 1;
							posit_row = j;
							posit_col = k;
						}
					}

				}
			}
			cout << posit_row + 1 << " " << posit_col + 1 << endl; // Print saved position
		}
	}
}

char change_lower(char ch)
{
	if (ch < 97)
		return ch + 32; // capital - small_letter = 32.
	else
		return ch;
}
