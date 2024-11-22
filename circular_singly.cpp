//Usama Hassan Alvi
//Maintain a sorted circular singly linked list with dummy node at head
#include <iostream>
using namespace std;
template<typename T>
class circularSingly
{
    struct Node
    {
        T data;
        Node* next;
      
    public:
        Node(): data(900), next(nullptr)
        {}
        Node(T val, Node* nptr = nullptr) :data(val), next(nptr)
        {}
    };
    Node* head, * tail;
    int size;
public:
    circularSingly()
    {
        head = tail = new Node(); //dummy node at head
        head->next = head; // if ttail points to head and head ->next = head ....circular
        size = 0;
    }
    void insertAtHead(T val)
    {
        head->next = new Node(val, head->next);
        if (size == 0)
        {
            tail = head->next;  //TAIL = HEAD->NEXT where HEAD->NEXT KA NEXT ALSO POINTS AT HEAD->NEXT SO KHUDI HOJATA POINT
        }
        size++;
    }
    void insertAtTail(T val)
    {
        tail->next = new Node(val, tail->next);  // tail->next wld be frst if it is empty so need to add to insert at head
        tail = tail->next;
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
            Node* prev = head;
            while (curr->data < val)
            {
                prev = curr;
                curr = curr->next;
            }
            prev->next = new Node(val, curr);
            size++;
        }
    }
    void deleteATHead() {
        if (size > 0) {
            Node* temp = head->next;
            head->next = head->next->next;

            delete temp;
            if (size == 1)
                tail = head;
            size--;
        }
    }
    void deleteATTail() {
        if (size > 0) {
            Node* temp = head;
            while (temp->next != tail) 
                temp = temp->next;
            temp->next = temp->next->next;
            delete tail;
            tail = temp;
            size--;
        }
    }
    void deleteParticular(const T& val)
    {
        if (size > 0)
        {
            if (val == head->next->data)
            {
                deleteATHead();
            }
            else if (val == tail->data)
            {
                deleteATTail();
            }
            else
            {
                Node* curr = head->next;
                Node* prev = head;
                while (curr != head && curr->data != val) // a minor change
                {
                    prev = curr;
                    curr = curr->next;
                }
                if (curr != head) // if curr is at head it means the "val" does not exits.
                {
                    prev->next = curr->next;
                    delete curr;
                    size--;
                }
            }
        }
    }
    void print()
    {
        Node* temp = head->next;
        while (temp != tail->next)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    class Iterator
    {
        Node* ptr;
    public:
        Iterator(Node* p) : ptr(p)
        {}
        Iterator& operator ++() {
            ptr = ptr->next;
            return *this;
        }
        Iterator& operator++(int) {
            Iterator temp = *this;
            ptr = ptr->next;
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
    Iterator begin() {
        return Iterator(head->next);
    }
    Iterator end() {
        return Iterator(tail->next);
    }
    ~circularSingly()
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
    circularSingly<int> s1;
    s1.insertInOrder(8);
    s1.insertInOrder(18);
    s1.insertInOrder(10);
    s1.insertInOrder(15);
    s1.insertInOrder(21);
    s1.insertInOrder(12);
    s1.insertInOrder(9);
    s1.insertInOrder(20);
    for (circularSingly<int>::Iterator it = s1.begin(); it != s1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    s1.deleteParticular(8);
    s1.deleteParticular(21);

    for (circularSingly<int>::Iterator it = s1.begin(); it != s1.end(); ++it) {
        cout << *it << " ";
    }
    return 0;
}