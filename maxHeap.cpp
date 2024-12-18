#include<iostream>
using namespace std;
class Heap
{
	int* h_Arr, size;
public:
	Heap(int arr[], int s)
	{
		size = s;
		h_Arr = new int[size];
		for (int i = 0; i < size; i++)
			h_Arr[i] = arr[i];
	}
	//build-heap function is used to make max-heap from complete binary tree
	//using heapify function.
	void buildheap()
	{
		for (int i = (size - 2) / 2; i >= 0; i--)		//LAST non leaf element
		{
			heapify(i);			// heapifys frm eachhh elemnet (keeps moving up the tree as the heapify is DOWN ) heapify wld fix lower table this for loop takes it up
		}
	}
	void heapify(int index)								//does the swapping  DOWN WARD
	{
		int largest = index;
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		if (left < size && h_Arr[left] > h_Arr[largest])
			largest = left;
		if (right < size && h_Arr[right] > h_Arr[largest])
			largest = right;
		if (largest != index)
		{
			swap(h_Arr[largest], h_Arr[index]);
			heapify(largest);					// what evr it was swapped with is now recursively made max heap
		}
	}
	int extMax()
	{
		swap(h_Arr[size - 1], h_Arr[0]);
		size--;
		heapify(0);
		return h_Arr[size + 1];		// as max wld now be at size+1 after the swap
	}
	void print()
	{
		for (int i = 0; i < size; i++)
			cout << h_Arr[i] << " ";
		cout << endl;
	}
	void heapSort()			// no longer max heap			extract max then put at end
	{
		int temp = size;
		for (int i = size - 1; i >= 0; i--)
		{
			swap(h_Arr[0], h_Arr[i]);
			size--;						// so as size reduced in heapify wont be able to access the LARGEST elements that after swap hv been placed at size+1
			heapify(0);					// so that new max element comes to root
		}
		size = temp;
	}
};
int main()
{
	int arr[] = { 25,20,22,17,15,14,18,8,10,7,5,12,6,9,2 };
	//make a complete binary tree
	Heap h1(arr, sizeof(arr) / 4);					// AS each integer in the array is 4 bytes
	h1.print(); //print the complete binary tree
	//convert the complete binary tree into max-heap
	h1.buildheap();
	h1.print(); //print the max heap
//use max heap for sorting. remove max elements one by one from the heap
//and place them at the last.
	h1.heapSort();
	h1.print(); //print the sorted array
}