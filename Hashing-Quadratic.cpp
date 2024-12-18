#include <iostream>
#include <string>
using namespace std;

// HashItem struct as defined previously
template <class T>
struct HashItem {
    int key;
    T value;
    short status; // 0 = empty, 1 = deleted, 2 = occupied
    HashItem() : key(0), status(0) {}
};

// HashMap class from question 1
template <class T>
class HashMap {
protected:
    HashItem<T>* hashArray;
    int capacity;
    int currentElements;

    // Linear probing by default
    virtual int getNextCandidateIndex(int key, int i) const {
        return (key + i) % capacity;
    }

    void doubleCapacity() {
        int oldCapacity = capacity;
        capacity *= 2;
        HashItem<T>* oldArray = hashArray;

        hashArray = new HashItem<T>[capacity];
        for (int i = 0; i < capacity; i++) {
            hashArray[i].status = 0; // Set all slots to empty
        }

        currentElements = 0; // Reset element count
        for (int i = 0; i < oldCapacity; i++) {
            if (oldArray[i].status == 2) {
                insert(oldArray[i].key, oldArray[i].value);
            }
        }
        delete[] oldArray;
    }

public:
    HashMap() : capacity(10), currentElements(0) {
        hashArray = new HashItem<T>[capacity];
        for (int i = 0; i < capacity; i++) {
            hashArray[i].status = 0; // Set all slots to empty
        }
    }

    HashMap(int const capacity) : capacity(capacity), currentElements(0) {
        if (capacity <= 1) {
            cerr << "Error: Capacity must be greater than 1." << endl;
            exit(1);
        }
        hashArray = new HashItem<T>[capacity];
        for (int i = 0; i < capacity; i++) {
            hashArray[i].status = 0; // Set all slots to empty
        }
    }

    void insert(int const key, T const value) {
        int index = key % capacity;
        int i = 1;
        while (hashArray[index].status == 2) {
            index = getNextCandidateIndex(key, i++);
        }

        hashArray[index].key = key;
        hashArray[index].value = value;
        hashArray[index].status = 2;
        currentElements++;

        if ((double)currentElements / capacity >= 0.75) {
            doubleCapacity();
        }
    }

    bool deleteKey(int const key) {
        int index = key % capacity;
        int i = 1;
        while (hashArray[index].status != 0) {
            if (hashArray[index].status == 2 && hashArray[index].key == key) {
                hashArray[index].status = 1;
                currentElements--;
                return true;
            }
            index = getNextCandidateIndex(key, i++);
        }
        return false;
    }

    T* get(int const key) const {
        int index = key % capacity;
        int i = 1;
        while (hashArray[index].status != 0) {
            if (hashArray[index].status == 2 && hashArray[index].key == key) {
                return &hashArray[index].value;
            }
            index = getNextCandidateIndex(key, i++);
        }
        return nullptr;
    }

    ~HashMap() {
        delete[] hashArray;
    }
};

// QHashMap class for quadratic probing
template <class T>
class QHashMap : public HashMap<T> {
protected:
    int getNextCandidateIndex(int key, int i) const override {
        return (key + i * i) % this->capacity;
    }
};

int main() {
    QHashMap<string> qMap;

    qMap.insert(10, "Hello");
    qMap.insert(20, "World");
    qMap.insert(30, "C++");
    qMap.insert(40, "Programming");
    qMap.insert(50, "HashMap");

    cout << "Retrieving values:" << endl;
    cout << "Key 10: " << *(qMap.get(10)) << endl;
    cout << "Key 20: " << *(qMap.get(20)) << endl;
    cout << "Key 30: " << *(qMap.get(30)) << endl;
    cout << "Key 40: " << *(qMap.get(40)) << endl;
    cout << "Key 50: " << *(qMap.get(50)) << endl;

    cout << "Deleting key 30..." << endl;
    qMap.deleteKey(30);

    if (qMap.get(30) == nullptr) {
        cout << "Key 30 successfully deleted." << endl;
    }

    return 0;
}
