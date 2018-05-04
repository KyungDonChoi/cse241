#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ListNode {
private:
	ListNode* up; // up pointer
	ListNode* right; // right pointer
	int f_num; // first number
	int l_num; // last number
public:
	ListNode(int f_num = 0, int l_num = 0, ListNode* right = NULL, ListNode* up = NULL)
	{
		this->f_num = f_num;
		this->l_num = l_num;
		this->right = right;
		this->up = up;
	}
	ListNode(const ListNode& that)
	{
		up = that.up;
		right = that.right;
		f_num = that.f_num;
		l_num = that.l_num;
	}
	ListNode& operator=(const ListNode& that)
	{
		if (this == &that)
			return *this;
		up = that.up;
		right = that.right;
		f_num = that.f_num;
		l_num = that.l_num;
		return *this;
	}

	friend class DList;
};

class DList {
private:
	ListNode* head;
public:
	DList(ListNode* head = NULL)
	{
		this->head = head;
	}
	void add(int f_int, int l_int)
	{
		if (find(f_int, l_int))
		{
			cout << "Already Exist" << endl;
			return;
		}
		if (head == NULL || head->f_num > f_int)
			head = new ListNode(f_int, l_int, head);
		else if (head->f_num == f_int)
		{
			if (head->l_num > l_int) {
				head = new ListNode(f_int, l_int, head->right, head);
				head->up->right = NULL;
			}
			else
			{
				ListNode *nodePtr, *prevNodePtr;
				prevNodePtr = head;
				nodePtr = head->up;

				while (nodePtr != NULL && nodePtr->l_num < l_int)
				{
					prevNodePtr = nodePtr;
					nodePtr = nodePtr->up;
				}

				prevNodePtr->up = new ListNode(f_int, l_int, NULL, nodePtr);
			}
		}
		else // head->f_num < f_int
		{
			ListNode* nodePtr, *prevNodePtr;
			prevNodePtr = head;
			nodePtr = head->right;

			while (nodePtr != NULL && nodePtr->f_num < f_int)
			{
				prevNodePtr = nodePtr;
				nodePtr = nodePtr->right;
			}

			// nodePtr is NULL or nodePtr->f_num >= f_int
			if (nodePtr == NULL)
				prevNodePtr->right = new ListNode(f_int, l_int);
			else if (nodePtr->f_num == f_int)
			{
				if (nodePtr->l_num > l_int) // compare with l_int
				{
					prevNodePtr->right = new ListNode(f_int, l_int, nodePtr->right, nodePtr);
					nodePtr->right = NULL;
				}
				else // if same...?
				{
					prevNodePtr = nodePtr;
					nodePtr = nodePtr->up;
					while (nodePtr != NULL && nodePtr->l_num < l_int)
					{
						prevNodePtr = nodePtr;
						nodePtr = nodePtr->up;
					}
					prevNodePtr->up = new ListNode(f_int, l_int, NULL, nodePtr);
				}
			}
			else
				prevNodePtr->right = new ListNode(f_int, l_int, nodePtr);
		}
	}
	bool find(int f_int, int l_int)
	{
		if (head == NULL)
			return false;
		else if (head->f_num > f_int)
			return false;
		else // head->f_num <= f_int
		{
			ListNode* nodePtr;
			int x, y;
			x = 1, y = 1;

			nodePtr = head;

			while (nodePtr != NULL && nodePtr->f_num < f_int)
			{
				nodePtr = nodePtr->right;
				x++;
			}

			if (nodePtr == NULL || nodePtr->f_num > f_int)
				return false;
			else // nodePtr != NULL and nodePtr->f_num == f_int
			{
				while (nodePtr != NULL && nodePtr->l_num < l_int)
				{
					nodePtr = nodePtr->up;
					y++;
				}

				if (nodePtr == NULL || nodePtr->l_num > l_int)
					return false;
				else
					return true;
			}
		}
	}
	bool find_print_ver(int f_int, int l_int)
	{
		if (head == NULL)
		{
			cout << "none" << endl;
			return false;
		}
		else if (head->f_num > f_int)
		{
			cout << "none" << endl;
			return false;
		}
		else // head->f_num <= f_int
		{
			ListNode* nodePtr;
			int x, y;
			x = 1, y = 1;

			nodePtr = head;

			while (nodePtr != NULL && nodePtr->f_num < f_int)
			{
				nodePtr = nodePtr->right;
				x++;
			}

			if (nodePtr == NULL || nodePtr->f_num > f_int)
			{
				cout << "none" << endl;
				return false;
			}
			else // nodePtr != NULL and nodePtr->f_num == f_int
			{
				while (nodePtr != NULL && nodePtr->l_num < l_int)
				{
					nodePtr = nodePtr->up;
					y++;
				}

				if (nodePtr == NULL || nodePtr->l_num > l_int)
				{
					cout << "none" << endl;
					return false;
				}
				else
				{
					cout << "(" << x << "," << y << ")" << endl;
					return true;
				}
			}
		}
	}
	void travel()
	{
		ListNode* p = head;
		while (p != NULL)
		{
			cout << p->f_num << "-" << p->l_num << endl;
			p = p->right;
		}
	}
	void remove(int f_int, int l_int)
	{
		if (head == NULL)
			cout << "List is EMPTY!!!!!!!!" << endl;
		else if (head->f_num > f_int || !find(f_int, l_int))
			cout << "There is no " << f_int << "-" << l_int << endl;
		else // It has guarantee that there is (f_int, l_int) by passing !find()
		{
			ListNode *nodePtr, *prevNodePtr;
			if (head->f_num == f_int)
			{
				if (head->l_num == l_int && head->up != NULL)
				{
					nodePtr = head;
					head->up->right = head->right;
					head = head->up;
					delete nodePtr;
				}
				else if (head->l_num == l_int && head->up == NULL) // this is single
				{
					nodePtr = head;
					head = head->right;
					delete nodePtr;
				}
				else
				{
					prevNodePtr = head;
					nodePtr = head->up;
					while (nodePtr->l_num != l_int) // The solution is exist! So we do not need to consider nodePtr is NULL
					{
						prevNodePtr = nodePtr;
						nodePtr = nodePtr->up;
					}
					prevNodePtr->up = nodePtr->up;
					delete nodePtr;
				}
			}
			else // head->f_num < l_int!
			{
				nodePtr = head;
				while (nodePtr->f_num != f_int)
				{
					prevNodePtr = nodePtr;
					nodePtr = nodePtr->right;
				}
				if (nodePtr->l_num == l_int && nodePtr->up != NULL)
				{
					prevNodePtr->right = nodePtr->up;
					nodePtr->up->right = nodePtr->right;
					delete nodePtr;
				}
				else if (nodePtr->l_num == l_int && nodePtr->up == NULL)
				{
					prevNodePtr->right = nodePtr->right;
					delete nodePtr;
				}
				else
				{
					prevNodePtr = nodePtr;
					nodePtr = nodePtr->up;
					while (nodePtr->l_num != l_int)
					{
						prevNodePtr = nodePtr;
						nodePtr = nodePtr->up;
					}
					prevNodePtr->up = nodePtr->up;
					delete nodePtr;
				}
			}
		}
	}
};

int main()
{
	ifstream inFile("input.txt");

	int Test_Case;

	inFile >> Test_Case;

	for (int test = 0; test < Test_Case; test++)
	{
		cout << '-' << endl;

		DList linked;
		string str;
		int num;

		inFile >> str;

		if (str == "-")
			inFile >> str;

		num = atoi(str.c_str());

		for (int i = 0; i < num; i++)
		{
			string str2;
			inFile >> str2;
			if (str2[0] == '>' && str2[1] == '>')
			{
				string numstr = str2.c_str() + 2;
				int dash_count = 0;
				for (int j = 0; j < numstr.length(); j++)
				{
					if (numstr[j] != '-')
						dash_count++;
					else
						break;
				}
				char numstr1[100];
				string numstr2 = numstr.c_str() + dash_count + 1;
				strncpy(numstr1, numstr.c_str(), dash_count);
				numstr1[dash_count] = '\0';
				int num1, num2;
				num1 = atoi(numstr1);
				num2 = atoi(numstr2.c_str());
				linked.add(num1, num2);
			}
			else if (str2[0] == '<' && str2[1] == '<')
			{
				string numstr = str2.c_str() + 2;
				int dash_count = 0;
				for (int j = 0; j < numstr.length(); j++)
				{
					if (numstr[j] != '-')
						dash_count++;
					else
						break;
				}
				char numstr1[100];
				string numstr2 = numstr.c_str() + dash_count + 1;
				strncpy(numstr1, numstr.c_str(), dash_count);
				numstr1[dash_count] = '\0';
				int num1, num2;
				num1 = atoi(numstr1);
				num2 = atoi(numstr2.c_str());
				linked.remove(num1, num2);
			}
		}
		int print;
		inFile >> print;
		for (int i = 0; i < print; i++)
		{
			string numstr;
			inFile >> numstr;
			int dash_count = 0;
			for (int j = 0; j < numstr.length(); j++)
			{
				if (numstr[j] != '-')
					dash_count++;
				else
					break;
			}
			char numstr1[100];
			string numstr2 = numstr.c_str() + dash_count + 1;
			strncpy(numstr1, numstr.c_str(), dash_count);
			numstr1[dash_count] = '\0';
			int num1, num2;
			num1 = atoi(numstr1);
			num2 = atoi(numstr2.c_str());
			linked.find_print_ver(num1, num2);
		}
	}

	return 0;
}