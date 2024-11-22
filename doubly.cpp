#include <iostream> 
using namespace std;

template<typename T>
class doubly
{
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node() : next(nullptr), prev(nullptr)
        {}
        Node(T val, Node* nptr = nullptr, Node* pptr = nullptr) : data(val), next(nptr), prev(pptr)
        {}
    };

    Node* head, * tail;
    int size;

public:
    doubly()
    {
        head = tail = new Node;
        size = 0;
    }


    void insertAtHead(T val)
    {
        head->next = new Node(val, head->next, head);
        if (size == 0)
        {
            tail = head->next;
        }
        else
            head->next->next->prev = head->next;
        size++;
    }

    void insertAtTail(T val)
    {
        tail->next = new Node(val, nullptr, tail);
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
            Node* curr = head->next; // start from the first real node
            while (curr->data < val)
            {
                curr = curr->next;
            }
            curr->prev->next = new Node(val, curr, curr->prev);
            curr->prev = curr->prev->next;
            size++;

        }
    }

    // (after the dummy)
    void deleteATHead()
    {
        if (size > 0) // if the list is not empty
        {
            Node* temp = head->next;
            head->next = head->next->next; // update head to point to the second node
            if (temp->next) // if there's more than one node, adjust the previous pointer of the second node
                temp->next->prev = head;
            delete temp; // delete the first node
            if (size == 1) // if the list had only one element, update tail to point to dummy head
                tail = head;
            size--; // decrement size
        }
    }

    void deleteATTail()
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        size--;
    }

    void deleteParticular(const T& val)
    {
        if (size > 0) // if list isn't empty
        {
            if (head->next->data == val) // if the first real node contains the value, delete it
                deleteATHead();
            else if (tail->data == val) // if the tail contains the value, delete it
                deleteATTail();
            else
            {
                Node* temp = head->next;
                while (temp != nullptr && temp->data != val)
                {
                    temp = temp->next;
                }
                if (temp != nullptr) //  if lagayi to make sure the loop didnt just end
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
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void RevPrint()
    {
        Node* temp = tail;
        while (temp->prev != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
    }

    // Iterator class for forward and reverse iteration
    class Iterator
    {
        Node* ptr; // pointer to the current node in the iteration
    public:
        Iterator(Node* p) : ptr(p) {} // constructor initializes the iterator with a node pointer

        Iterator& operator ++() // pre-increment operator
        {
            ptr = ptr->next; // move to the next node
            return *this;
        }

        Iterator& operator++(int) // post-increment operator
        {
            Iterator temp = *this; // store current state
            ptr = ptr->next; // move to the next node
            return temp;
        }

        Iterator& operator --() // pre-decrement operator
        {
            ptr = ptr->prev; // move to the previous node
            return *this;
        }

        Iterator& operator--(int) // post-decrement operator
        {
            Iterator temp = *this; // store current state
            ptr = ptr->prev; // move to the previous node
            return temp;
        }

        T& operator *() const // dereference operator to access data
        {
            return ptr->data;
        }

        bool operator != (const Iterator& other) const
        {
            return !(ptr == other.ptr); // check if two iterators are not equal
        }
    };

    Iterator begin() {
        return Iterator(head->next); // return an iterator starting at the first real node
    }

    Iterator end() {
        return Iterator(tail->next); // return an iterator representing the end (past the last node)
    }

    Iterator r_begin() {
        return Iterator(tail); // return an iterator starting at the tail
    }

    Iterator r_end() {
        return Iterator(head); // return an iterator representing the start (before the first node)
    }

    ~doubly() // destructor to clean up memory
    {
        Node* curr = head; // start from the dummy head
        Node* prev;
        while (curr != nullptr) // traverse the list and delete nodes
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }



};


template<typename T>
void printList(doubly<T>& a) {
    cout << "\nPrint using Iterator: ";
    for (typename doubly<T>::Iterator it = a.begin(); it != a.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}


template<typename T>
void unionList(doubly<T>& a, doubly<T>& b, doubly<T>& c) {
    for (typename doubly<T>::Iterator it = a.begin(); it != a.end(); ++it) {
        c.insertAtTail(*it);
    }
    for (typename doubly<T>::Iterator it = b.begin(); it != b.end(); ++it) {
        if (!c.Search(*it)) { // assuming Search is implemented
            c.insertAtTail(*it);
        }
    }
}


template<typename T>
void intersectList(doubly<T>& a, doubly<T>& b, doubly<T>& c) {
    for (typename doubly<T>::Iterator it = a.begin(); it != a.end(); ++it) {
        if (b.Search(*it)) { // assuming Search is implemented
            c.insertAtTail(*it); // if found in both lists, add to result
        }
    }
}

// Function to compute the difference between two lists (a - b)
template<typename T>
void differenceList(doubly<T>& a, doubly<T>& b, doubly<T>& c) {
    for (typename doubly<T>::Iterator it = a.begin(); it != a.end(); ++it) {
        if (!b.Search(*it)) { // assuming Search is implemented
            c.insertAtTail(*it); // add to result if not found in b
        }
    }
}

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}


template<typename T>
void bubblesortList(doubly<T>& a) {
    for (typename doubly<T>::Iterator outerIt = a.begin(); outerIt != a.end(); ++outerIt) {
        bool swapped = false;
        for (typename doubly<T>::Iterator it = a.begin(); it != a.end(); ++it) {
            typename doubly<T>::Iterator nextIt = it;
            ++nextIt;
            if (nextIt != a.end() && *it < *nextIt) {
                swap(*it, *nextIt);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}



int main() {
    doubly<int> d1, d2, d3, d4, d5;

    // Insert values into d1 and d2
    d1.insertInOrder(8);
    d1.insertInOrder(18);
    d1.insertInOrder(10);

    d2.insertInOrder(15);
    d2.insertInOrder(18);
    d2.insertInOrder(10);

    // Print the original lists
    printList(d1);
    printList(d2);

    // Intersection of d1 and d2 into d3
    intersectList(d1, d2, d3);
    cout << "Intersection List: ";
    printList(d3); // Printing the intersection of d1 and d2

    // Difference of d1 and d2 into d4 (d1 - d2)
    differenceList(d1, d2, d4);
    cout << "Difference List (d1 - d2): ";
    printList(d4); // Printing the difference of d1 and d2

    // Difference of d2 and d1 into d5 (d2 - d1)
    differenceList(d2, d1, d5);
    cout << "Difference List (d2 - d1): ";
    printList(d5); // Printing the difference of d2 and d1

    return 0;
}

