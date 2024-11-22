#include <iostream>
using namespace std;

template<typename T>
class StackArray {
public:
    T* arr;
    int top;
    int capacity;


    StackArray(int size = 100) {
        arr = new T[size];
        top = -1;
        capacity = size;
    }

    ~StackArray() {
        delete[] arr;
    }

    void push(const T& val) {
        if (top == capacity - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    T topElement() const {  
        if (!isEmpty()) {
            return arr[top];
        }
        throw out_of_range("Stack is empty");
    }

    bool isEmpty() const {
        return top == -1;
    }

    int size() const {
        return top + 1;
    }

    void print() const {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        for (int i = top; i >= 0; --i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};
template <typename T>
class Queue {
private:
    StackArray<T> stack1;
    StackArray<T> stack2;

public:
    Queue(int size = 100) : stack1(size), stack2(size) {}

    bool IsFull() const {
        return stack1.size() == stack1.capacity;
    }

    bool IsEmpty() const {
        return stack1.isEmpty() && stack2.isEmpty();
    }

    void Enqueue(const T& element) {
        stack1.push(element);
    }

    void Dequeue() {
        if (IsEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }

        if (stack2.isEmpty()) {
            while (!stack1.isEmpty()) {
                stack2.push(stack1.topElement());
                stack1.pop();
            }
        }

        stack2.pop();  
    }

    void Print() {
        if (!stack2.isEmpty()) {
            for (int i = stack2.size() - 1; i >= 0; --i) {
                cout << stack2.arr[i] << " ";
            }
        }
        if (!stack1.isEmpty()) {
            for (int i = 0; i < stack1.size(); ++i) {
                cout << stack1.arr[i] << " ";
            }
        }

        cout << endl;
    }
};
int main() {
    Queue<int> q(10);  

    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    q.Enqueue(5);

    cout << "Queue after enqueueing: "; 
    q.Print();
    q.Dequeue();
    q.Dequeue();

    cout << "Queue after two dequeues: ";
    q.Print();

    return 0;
}