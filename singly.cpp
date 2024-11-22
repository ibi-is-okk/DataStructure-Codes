#include <iostream>
using namespace std;
template<typename T>
class singly
{
	struct Node
	{
		T data;
		Node* next;
		Node(T val, Node* nptr = nullptr) : data(val), next(nptr)
		{}
	};
	Node* head, * tail;
public:
	singly() :head(nullptr), tail(nullptr)
	{}
	void insertAtHead(const T val)
	{
		Node* n = new Node(val); //parameterized constr
		if (head == nullptr)
		{
			head = n;
			tail = n;
			return;
		}
		n->next = head;
		head = n;
	}
	void print()
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
	void insertAtTail(const T val)
	{
		if (head == nullptr)
		{
			insertAtHead(val);
			return;
		}
		Node* n = new Node(val);
		tail->next = n;
		tail = tail->next;
	}
	void deleteAtHead()
	{
		if (head == nullptr)
			return;
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	void insertInorder(T val)
	{
		if (head != nullptr && val < head->data)
		{
			insertAtHead(val);
		}
		else if (val > tail->data)
		{
			insertAtTail(val);
		}
		Node* curr = head->next;
		Node* prev = head;
		while (curr->data < val)
		{
			prev = curr;
			curr = curr->next;
		}
		Node* n = new Node(val, curr);
		prev->next = n;
	}
	void deleteAtTail()
	{
		if (head == nullptr)
			return;
		Node* curr = head->next; //only single node case isko kahin aur bhi na use kerna 
		Node* prev = head;
		while (curr->next != nullptr)
		{
			prev = curr;
			curr = curr->next;
		}
		delete curr;
		prev->next = nullptr;
		tail = prev;
	}

	int totalCount() const {
		int count = 0;
		Node* curr = head;
		while (curr != nullptr) {
			count++;
			curr = curr->next;
		}
		return count;
	}

	void split(SinglyLinkedList& firstHalf, SinglyLinkedList& secondHalf) {
		int len = totalCount();
		int mid = len / 2;
		Node* curr = head;
		for (int i = 0; i < mid; i++) {
			firstHalf.insertAtTail(curr->data);
			curr = curr->next;
		}
		while (curr != nullptr) {
			secondHalf.insertAtTail(curr->data);
			curr = curr->next;
		}
	}

	void merge(SinglyLinkedList& firstHalf, SinglyLinkedList& secondHalf) {
		Node* curr = firstHalf.head;
		while (curr != nullptr) {
			insertAtTail(curr->data);
			curr = curr->next;
		}
		curr = secondHalf.head;
		while (curr != nullptr) {
			insertAtTail(curr->data);
			curr = curr->next;
		}
	}
};
int main()
{
	singly<int> s1;
	s1.insertAtTail(80);
	s1.insertAtTail(180);
	s1.insertAtHead(45);
	s1.insertAtHead(25);
	s1.insertAtHead(35);
	s1.insertAtHead(75);
	s1.insertAtTail(200);
	s1.insertAtTail(490);
	s1.deleteAtHead();
	s1.deleteAtTail();
	s1.insertInorder(70);
	s1.insertInorder(10);
	s1.print();
}