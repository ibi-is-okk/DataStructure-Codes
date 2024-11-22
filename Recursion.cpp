#include <iostream>
using namespace std;

// Function to find the largest element in an array recursively
int Largest(const int list[], int low, int high) {
    if (low == high)
        return list[low];
    else {
        int max = Largest(list, low + 1, high);
        return (list[low] >= max) ? list[low] : max;
    }
}

// Recursive factorial function
int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

// Recursive sum of first N numbers
int SumtoN(int n) {
    if (n == 0)
        return 0;
    else
        return n + SumtoN(n - 1);
}

// Recursive linear search
int Lsearch(const int items[], int key, int i) {
    if (i < 0)
        return -1;
    else if (key == items[i])
        return i;
    else
        return Lsearch(items, key, i - 1);
}

// Recursive binary search
int bsearch(const int data[], int first, int last, int value) {
    if (first > last)
        return -1;
    int middle = (first + last) / 2;
    if (data[middle] == value)
        return middle;
    else if (value < data[middle])
        return bsearch(data, first, middle - 1, value);
    else
        return bsearch(data, middle + 1, last, value);
}

// Recursive palindrome check
bool isPalindrome(const char *s, int low, int high) {
    if (high <= low)
        return true;
    else if (s[low] != s[high])
        return false;
    else
        return isPalindrome(s, low + 1, high - 1);
}

// Recursive Fibonacci sequence
int fibonacci(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

// Merge function used in merge sort
void merge(int arr[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = 0;
    int temp[high - low + 1];

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; ++i, ++k)
        arr[i] = temp[k];
}

// Recursive merge sort function
void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
string commas(int num) {
    if (num < 1000) {
        return to_string(num);
    }
    string last3 = to_string(num % 1000);
    int remaining = num / 1000;

    if (last3.length() < 3) {
        last3 = string(3 - last3.length(), '0') + last3;
    }
    return commas(remaining) + "," + last3;
}

string removeduplicates(const string& str) {
    if (str.length() <= 1) {
        return str;
    }
    if (str[0] == str[1]) {
        return removeduplicates(str.substr(1));
    }
    else {
        return str[0] + removeduplicates(str.substr(1));
    }
}


void PrintBinary(int n, string x) {// n is the number of bits to show all combos of binary in
    if (x.length() == n)
        cout << x;
    else
    {
        PrintBinary(n, x + '1');
        PrintBinary(n, x + '0');
    }
}


// Main function to test all the recursive functions
int main() {
    const int N = 5;
    int items[N] = {2, 5, 6, 7, 8};
    int key = 5;

    // Test Largest function
    cout << "Largest element in array: " << Largest(items, 0, N - 1) << endl;

    // Test factorial function
    int num = 5;
    cout << "Factorial of " << num << " is " << factorial(num) << endl;

    // Test SumtoN function
    int sumNum = 10;
    cout << "Sum of first " << sumNum << " numbers is " << SumtoN(sumNum) << endl;

    // Test Linear Search function
    int location = Lsearch(items, key, N - 1);
    if (location != -1)
        cout << "Linear Search: Key " << key << " found at index " << location << endl;
    else
        cout << "Linear Search: Key " << key << " not found." << endl;

    // Test Binary Search function
    int sortedItems[] = {2, 5, 6, 7, 8};
    location = bsearch(sortedItems, 0, N - 1, key);
    if (location != -1)
        cout << "Binary Search: Key " << key << " found at index " << location << endl;
    else
        cout << "Binary Search: Key " << key << " not found." << endl;

    // Test isPalindrome function
    const char *str = "madam";
    bool palindrome = isPalindrome(str, 0, 4);
    if (palindrome)
        cout << "The string \"" << str << "\" is a palindrome." << endl;
    else
        cout << "The string \"" << str << "\" is not a palindrome." << endl;

    // Test Fibonacci function
    int fibNum = 6;
    cout << "Fibonacci of " << fibNum << " is " << fibonacci(fibNum) << endl;

    // Test Merge Sort function
    int unsortedItems[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(unsortedItems) / sizeof(unsortedItems[0]);
    mergeSort(unsortedItems, 0, size - 1);
    cout << "Merge Sorted array: ";
    for (int i = 0; i < size; ++i)
        cout << unsortedItems[i] << " ";
    cout << endl;

    return 0;
}
