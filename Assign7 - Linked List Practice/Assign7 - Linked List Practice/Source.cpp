#include <iostream>

using namespace std;

class ListNode {
private:
	int data;
	ListNode* next;
public:
	ListNode(int d, ListNode* p = NULL)
	{
		data = d;
		next = p;
	}
	friend class Linked_List;
	ListNode& operator=(ListNode &that)
	{
		if (this == &that)
			return *this;
		data = that.data;
		next = that.next;
		return *this;
	}
};

class Linked_List{
private:
	ListNode* head;
public:
	Linked_List(ListNode* p = NULL)
	{
		head = p;
	}
	void add(int number)
	{
		ListNode *NodePtr, *PrevNodePtr;
		if (head == NULL || head->data >= number)
			head = new ListNode(number, head);
		else
		{
			PrevNodePtr = head;
			NodePtr = head->next;
			while (NodePtr != NULL && NodePtr->data < number)
			{
				PrevNodePtr = NodePtr;
				NodePtr = NodePtr->next;
			}
			PrevNodePtr->next = new ListNode(number, NodePtr);
		}
	}
	void del(int number)
	{
		ListNode *nodePtr, *prevNodePtr;
		if (!head) return;
		if (head->data == number) {
			nodePtr = head;
			head = head->next;
			delete nodePtr;
		}
		else {
			nodePtr = head;
			while (nodePtr != NULL && nodePtr->data != number) {
				prevNodePtr = nodePtr;
				nodePtr = nodePtr->next;
			}
			if (nodePtr) {
				prevNodePtr->next = nodePtr->next;
				delete nodePtr;
			}
		}
	}
	void travel()
	{
		if (head == NULL)
			cout << "Empty List" << endl;
		else
		{
			ListNode *NodePtr;
			NodePtr = head;
			while (NodePtr != NULL)
			{
				static int count = 0;
				cout << count << "th number: " << NodePtr->data << endl;
				NodePtr = NodePtr->next;
				count++;
			}
		}
	}
};
int main()
{
	Linked_List ll;
	ll.add(10);
	ll.add(5);
	ll.add(12);
	ll.travel();

}