#include <iostream>
using namespace std;

class MinHeap
{
    int* h_Arr, size;
public:
    MinHeap(int arr[], int s)
    {
        size = s;
        h_Arr = new int[size];
        for (int i = 0; i < size; i++)
            h_Arr[i] = arr[i];
    }

    // Build-heap function is used to make min-heap from a complete binary tree
    // using the heapify function.
    void buildheap()
    {
        for (int i = (size - 2) / 2; i >= 0; i--) // Start from the last non-leaf node
        {
            heapify(i);
        }
    }

    void heapify(int index) // Maintains the Min-Heap property
    {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && h_Arr[left] < h_Arr[smallest])
            smallest = left;
        if (right < size && h_Arr[right] < h_Arr[smallest])
            smallest = right;
        if (smallest != index)
        {
            swap(h_Arr[smallest], h_Arr[index]);
            heapify(smallest); // Recursively maintain Min-Heap property
        }
    }

    int extMin() // Extract the minimum element
    {
        swap(h_Arr[0], h_Arr[size - 1]);
        size--;
        heapify(0);
        return h_Arr[size]; // Min element is at the last position after the swap
    }

    void print() // Print the current state of the heap
    {
        for (int i = 0; i < size; i++)
            cout << h_Arr[i] << " ";
        cout << endl;
    }

    void heapSort() // Sort the array in descending order using Min-Heap
    {
        int temp = size;
        for (int i = size - 1; i >= 0; i--)
        {
            swap(h_Arr[0], h_Arr[i]);
            size--;
            heapify(0);
        }
        size = temp; // Restore original size after sorting
    }
};

int main()
{
    int arr[] = { 25, 20, 22, 17, 15, 14, 18, 8, 10, 7, 5, 12, 6, 9, 2 };
    MinHeap h1(arr, sizeof(arr) / sizeof(arr[0])); // Calculate array size
    h1.print(); // Print the initial complete binary tree
    h1.buildheap(); // Convert the tree into a Min-Heap
    h1.print(); // Print the Min-Heap
    h1.heapSort(); // Use Min-Heap for sorting
    h1.print(); // Print the sorted array
}
