//Usama Hassan Alvi
//Maintain a sorted circular doubly linked list with dummy node at head
#include <iostream>
using namespace std;
template<typename T>
class circularDoubly
{
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    public:
        Node():next(nullptr), prev(nullptr)
        {}
        Node(T val, Node* nptr = nullptr, Node* pptr = nullptr) :data(val), next(nptr), prev(pptr)
        {}
    };
    Node* head, * tail;
    int size;
public:
    circularDoubly()
    {
        head = tail = new Node; //dummy node
        head->next = head;
        head->prev = tail;
        size = 0;
    }
    void insertAtHead(T val)
    {
        head->next = new Node(val, head->next, head);
        if (size == 0)
        {
            tail = head->next;
            head->prev = tail; 
        }
        else
            head->next->next->prev = head->next;
        size++;
    }
    void insertAtTail(T val)
    {
        tail->next = new Node(val, head, tail);
        tail = tail->next;
        head->prev = tail; 
        size++;
    }
    void insertInOrder(T val)
    {
        if (size == 0)
        {
            insertAtHead(val);
        }
        else if (val < head->next->data)
        {
            insertAtHead(val);
        }
        else if (val > tail->data)
        {
            insertAtTail(val);
        }
        else
        {
            Node* curr = head->next;
            while (curr->data < val)
            {
                curr = curr->next;
            }
            curr->prev->next = new Node(val, curr, curr->prev);
            curr->prev = curr->prev->next;
            size++;
        }
    }
    void deleteATHead() {
        if (size > 0) {
            Node* temp = head->next;
            head->next = head->next->next;
            head->next->prev = head;
            delete temp;
            if (size == 1)
                tail = head;
            size--;
        }
    }
    void deleteATTail() {
        tail = tail->prev;
        delete tail->next;
        tail->next = head;
        head->prev = tail;
        size--;
    }
    void deleteParticular(const T& val)
    {
        if (size > 0)
        {
            if (head->next->data == val)
                deleteATHead();
            else if (tail->data == val)
                deleteATTail();
            else
            {
                Node* temp = head->next;
                while (temp != head && temp->data != val)
                {
                    temp = temp->next;
                }
                if (temp != head)
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                    size--;
                }
            }
        }
    }
    void print()
    {
        Node* temp = head->next;
        while (temp != head)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void RevPrint()
    {
        Node* temp = tail;
        while (temp != head)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
    }
    
    class Iterator
    {
        Node* ptr;
        public:
        Iterator(Node * p): ptr(p)
        {}
        Iterator & operator ++(){
            ptr = ptr->next;
            return *this;
        }
        Iterator& operator++(int) {
            Iterator temp = *this;
            ptr = ptr->next;
            return temp;
        }
        Iterator& operator --() {
            ptr = ptr->prev;
            return *this;
        }
        Iterator& operator--(int) {
            Iterator temp = *this;
            ptr = ptr->prev;
            return temp;
        }
        T& operator *() const
        {
            return ptr->data;
        }
        bool operator != (const Iterator& other) const {
            return !(ptr == other.ptr);
        }        
    };
    Iterator begin(){
        return Iterator(head->next);
    }
    Iterator end(){
        return Iterator(head);
    }
    Iterator r_begin() {
        return Iterator(tail);
    }
    Iterator r_end() {
        return Iterator(head);
    }
    ~circularDoubly()
    {
        Node* curr = head->next;
        Node* prev = head;
        while (curr != head)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        delete curr;
    }
};
int main()
{
    circularDoubly<int> d1;
    d1.insertInOrder(8);
    d1.insertInOrder(18);
    d1.insertInOrder(10);
    d1.insertInOrder(15);
    d1.insertInOrder(21);
    d1.insertInOrder(12);
    d1.insertInOrder(9);
    d1.insertInOrder(20);
    d1.print();
    d1.deleteParticular(8);
    d1.deleteParticular(21);
    d1.print();

    d1.RevPrint();
    d1.deleteParticular(90);
    d1.deleteParticular(20);
    cout << endl;
    d1.print();
    d1.RevPrint();


    return 0;
}