#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int llint;

int main()
{
	int Test_Case;

	cin >> Test_Case;

	for (int test = 0; test < Test_Case; test++)
	{
		llint KS_num;
		llint sum;
		llint KS_1_size;
		llint KS_2_size;
		llint* answer_sheet;
		llint* used_1;
		llint* used_2;
		vector<llint> KS_1_cost;
		vector<llint> KS_2_cost; 
		// we can divide case for 1 and 2 by assumption;

		cin >> KS_num;

		for (llint i = 0; i < KS_num; i++)
		{
			int weight, cost;
			
			cin >> weight >> cost;

			if (weight == 1)
				KS_1_cost.push_back(cost);
			else if (weight == 2)
				KS_2_cost.push_back(cost);
		}

		KS_1_size = KS_1_cost.size();
		KS_2_size = KS_2_cost.size();

		if (KS_1_cost.size() > 0)
			sort(KS_1_cost.begin(), KS_1_cost.end());
		if (KS_2_cost.size() > 0)
			sort(KS_2_cost.begin(), KS_2_cost.end());

		// If sizes are not zero, then sort. (If it is zero, there is no need to sort)

		sum = 1 * KS_1_size + 2 * KS_2_size;

		answer_sheet = new llint[sum + 1];
		used_1 = new llint[sum + 1];
		used_2 = new llint[sum + 1];

		if (KS_1_size > 0)
		{
			answer_sheet[0] = 0;
			answer_sheet[1] = KS_1_cost.back();
			used_1[0] = 0;
			used_2[0] = 0;
			used_1[1] = 1;
			used_2[1] = 0;
		}
		else if (KS_2_size > 0)
		{
			answer_sheet[0] = 0;
			answer_sheet[1] = 0;
			answer_sheet[2] = KS_2_cost.back();
			used_1[0] = 0;
			used_2[0] = 0;
			used_1[1] = 0;
			used_2[1] = 0;
			used_1[2] = 0;
			used_2[2] = 1;
		}
		// It is trivial!

		cout << answer_sheet[1] << " ";

		for (llint i = 2; i <= sum; i++)
		{
			/*
			I used Dynamic Programming Algorithm, such that make 'answer sheet' array to read and write last cases' answer.
			Main algorithm is like below. 
			f(n) = max(f(n-1) + max of unused weight 1's cost, f(n-2) + max of unused weight 2's cost)
			I implemented f(n) by answer sheet and by defining used_1 and used_2 array, we can approach maximum of remainder of costs.
			*/

			llint max_1 = 0;
			llint max_2 = 0;

			if(KS_1_size - 1 - used_1[i - 1] >= 0)
				max_1 = answer_sheet[i - 1] + KS_1_cost[KS_1_size - 1 - used_1[i - 1]];
			
			if(KS_2_size - 1 - used_2[i - 2] >= 0)
				max_2 = answer_sheet[i - 2] + KS_2_cost[KS_2_size - 1 - used_2[i - 2]];
			
			if (max_1 > max_2)
			{
				answer_sheet[i] = max_1;
				used_1[i] = used_1[i - 1] + 1;
				used_2[i] = used_2[i - 1];
			}
			else if (max_1 <= max_2)
			{
				answer_sheet[i] = max_2;
				used_1[i] = used_1[i - 2];
				used_2[i] = used_2[i - 2] + 1;
			}

			if (KS_1_size == 0 && i % 2 == 1)
				answer_sheet[i] = 0;
			cout << answer_sheet[i] << " ";
		}
		cout << endl;
		
		delete[] answer_sheet;
		delete[] used_1;
		delete[] used_2;
	}

	return 0;
}