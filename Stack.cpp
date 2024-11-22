#include <iostream>
using namespace std;

template<typename T>
class StackList {
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* top;

public:
    StackList() : top(nullptr) {}

    ~StackList() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Push element onto stack
    void push(const T& val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    // Pop element from stack
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // Return the top element without removing it
    T peek() const {
        if (!isEmpty()) {
            return top->data;
        }
        throw out_of_range("Stack is empty");
    }

    // Check if stack is empty
    bool isEmpty() const {
        return top == nullptr;
    }

    // Return the number of elements in the stack
    int size() const {
        Node* temp = top;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void print() const {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        Node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool check(char expression[]) {
        stack<char> s(100);
        for (int i = 0; expression[i] != '\0'; i++) {
            char c = expression[i];
            if (c == '(' || c == '{' || c == '[') s.push(c);
            else if (c == ')' || c == '}' || c == ']') {
                if (s.isEmpty()) return false;
                char top;
                s.top(top);
                if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                    return false;
                }
                s.pop();
            }
        }
        return s.isEmpty();
    }

    bool precedence(char a, char b) {
        int prec1, prec2;
        // Assign precedence levels (*/ = 2, +- = 1, others = 0)
        if (a == '+' || a == '-') prec1 = 1;
        else if (a == '*' || a == '/') prec1 = 2;
        else prec1 = 0;

        if (b == '+' || b == '-') prec2 = 1;
        else if (b == '*' || b == '/') prec2 = 2;
        else prec2 = 0;

        return prec1 >= prec2;
    }

    void infixtopostfix(char infix[]) {
        string postfix = "";
        stack<char> s(100);
        for (int i = 0; infix[i] != '\0'; i++) {
            char c = infix[i];
            if (isalnum(c)) {  // Operand (alphabet or number)
                postfix += c;
            }
            else if (c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while (!s.isEmpty() && s.top2() != '(') {
                    postfix += s.top2();
                    s.pop();
                }
                s.pop(); // Pop '('
            }
            else {  // Operator
                while (!s.isEmpty() && precedence(s.top2(), c)) {
                    postfix += s.top2();
                    s.pop();
                }
                s.push(c);
            }
        }

        while (!s.isEmpty()) {
            postfix += s.top2();
            s.pop();
        }

        cout << "Postfix Expression: " << postfix << endl;
    }


    void evaluate_postfix(char postfix[]) {
        stack<int> s(100);
        for (int i = 0; postfix[i] != '\0'; i++) {
            char c = postfix[i];
            if (isdigit(c)) {
                s.push(c - '0');
            }
            else {
                int val1, val2;
                s.top(val2);
                s.pop();
                s.top(val1);
                s.pop();
                switch (c) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
                }
            }
        }
        int result;
        s.top(result);
        cout << "Postfix Evaluation Result: " << result << endl;
    }
};

int main() {
    StackList<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.print();

    cout << "Top element: " << stack.peek() << endl;
    stack.pop();
    stack.print();

   
    return 0;
}
