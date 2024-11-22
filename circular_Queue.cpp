#include <iostream>
using namespace std;

class CircularQueue {
private:
    int *queue; 
    int front;   
    int rear;   
    int size;    
    int count;   

public:
    CircularQueue(int maxSize) {
        size = maxSize;
        queue = new int[size];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == size;
    }

    // Function to resize the queue when full
    void resize() {
        int newSize = size * 2;  // Double the size
        int *newQueue = new int[newSize];

        // Copy elements from the old queue to the new one
        for (int i = 0; i < count; ++i) {
            newQueue[i] = queue[(front + i) % size];
        }

        // Update the front, rear, and size
        front = 0;
        rear = count - 1; // cus count mai ham 0 index ko include ni kertay its 0,1,2,3 // count = 4 rear = 3
        size = newSize;

        delete[] queue;  
        queue = newQueue;  // Point to the new memory
    }

    void enqueue(int value) {
        if (isFull()) {
            resize();  
        }
        rear = (rear + 1) % size;  // Update rear to the next position circularly
        queue[rear] = value;
        count++; 
    }

    int dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        int result = queue[front];  // Get the front element
        front = (front + 1) % size;  // Update front to the next position circularly
        count--;  // Decrement the count of elements
        return result;
    }

    // Function to get the front element without removing it
    int peek() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return queue[front];
    }

    int getCount() {
        return count;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < count; ++i) {
            cout << queue[(front + i) % size] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q(5);  

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    
    q.display();


    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Dequeued: " << q.dequeue() << endl;

    q.display();

    // Enqueue more elements (should trigger resizing)
    q.enqueue(60);
    q.enqueue(70);

    q.display();

    cout << "Front element: " << q.peek() << endl;

    cout << "Number of elements in the queue: " << q.getCount() << endl;

    return 0;
}
