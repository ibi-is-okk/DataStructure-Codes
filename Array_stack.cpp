#include <iostream>
using namespace std;

template<typename T>
class StackArray {
    T* arr;
    int top;
    int capacity;

public:
    StackArray(int size = 100) {
        arr = new T[size];
        top = -1;
        capacity = size;
    }

    ~StackArray() {
        delete[] arr;
    }

    // Push element onto stack
    void push(const T& val) {
        if (top == capacity - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    // Pop element from stack
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    // Return the top element without removing it
    T peek() const {
        if (!isEmpty()) {
            return arr[top];
        }
        throw out_of_range("Stack is empty");
    }

    // Check if stack is empty
    bool isEmpty() const {
        return top == -1;
    }

    // Return the number of elements in the stack
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

int main() {
    StackArray<int> stack(5);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.print();

    cout << "Top element: " << stack.peek() << endl;
    stack.pop();
    stack.print();

    return 0;
}
