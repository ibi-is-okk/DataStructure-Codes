#include <iostream>
using namespace std;


template <class T>
struct HashItem {
    int key;
    T value;
    short status; // 0: empty, 1: deleted, 2: occupied

    HashItem() : key(0), value(T()), status(0) {}
};


template <class T>
class HashMap {
private:
    HashItem<T>* hashArray;
    int capacity;
    int currentElements;

    virtual int getNextCandidateIndex(int key, int i) const {
        return (key + i) % capacity; // linear probing
    }

    // double the capacity and rehash existing items
    void doubleCapacity() {
        int oldCapacity = capacity;
        capacity *= 2;
        HashItem<T>* oldArray = hashArray;
        hashArray = new HashItem<T>[capacity];
        currentElements = 0;

        for (int i = 0; i < oldCapacity; ++i) {
            if (oldArray[i].status == 2) { // rehash only occupied items
                insert(oldArray[i].key, oldArray[i].value);
            }
        }
        delete[] oldArray;
    }

public:

    HashMap() : capacity(10), currentElements(0) {
        hashArray = new HashItem<T>[capacity];
    }

    // overloaded constructor
    HashMap(int const c) : currentElements(0) {
        capacity = c;
        hashArray = new HashItem<T>[c];
    }

    void insert(int const key, T const value) {
        int index = key % capacity;
        int i = 1;

        // collision
        while (hashArray[index].status == 2) {
            index = getNextCandidateIndex(key, i++);
        }

        hashArray[index].key = key;
        hashArray[index].value = value;
        hashArray[index].status = 2;
        currentElements++;

        // resize if necessary
        if (static_cast<float>(currentElements) / capacity >= 0.75) {
            doubleCapacity();
        }
    }

    bool deleteKey(int const key) {
        int index = key % capacity;
        int i = 1;

        while (hashArray[index].status != 0) {      //search for key
            if (hashArray[index].status == 2 && hashArray[index].key == key) {
                hashArray[index].status = 1; 
                currentElements--;
                return true;
            }
            index = getNextCandidateIndex(key, i++);
        }

        return false;
    }

   
    T* get(int const key) const {       //search key
        int index = key % capacity;
        int i = 1;

        while (hashArray[index].status != 0) {
            if (hashArray[index].status == 2 && hashArray[index].key == key) {
                return &(hashArray[index].value);
            }
            index = getNextCandidateIndex(key, i++);
        }

        return nullptr; 
    }


    ~HashMap() {
        delete[] hashArray;
    }
};

int main() {
    HashMap<string> map;

    map.insert(1, "Alice");
    map.insert(2, "Bob");
    map.insert(3, "Charlie");
    map.insert(12, "David"); 

    string* val = map.get(2);
    if (val) cout << "Key 2: " << *val << endl;

    if (map.deleteKey(2)) cout << "Key 2 deleted." << endl;

    val = map.get(2);
    if (!val) cout << "Key 2 not found." << endl;

    val = map.get(12);
    if (val) cout << "Key 12: " << *val << endl;

    return 0;
}
