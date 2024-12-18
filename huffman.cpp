#include <iostream>
#include <vector>

using namespace std;

// Node Structure
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};


// Min-Heap Class
class MinHeap {
    vector<Node*> heap;

    void heapify(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left]->freq < heap[smallest]->freq)
            smallest = left;
        if (right < heap.size() && heap[right]->freq < heap[smallest]->freq)
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    MinHeap() {}

    void insert(Node* newNode) {
        heap.push_back(newNode);
        int index = heap.size() - 1;
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index]->freq >= heap[parent]->freq)
                break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    Node* extractMin() {
        if (heap.empty())
            return nullptr;

        Node* minNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);

        return minNode;
    }

    int size() const {
        return heap.size();
    }
};


//***********************************************************

void getFrequency(const string& str, vector<int>& freq) {
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (isalpha(ch)) {
            freq[tolower(ch) - 'a']++;
        }
        else if (ch == ' ') {
            freq[26]++;
        }
    }
}


Node* buildHuffmanTree(const vector<int>& freq) {
    MinHeap minHeap;

    // insert nonzero freq char into heap AS in min heap they are in order an extmin wld giv min values
    for (int i = 0; i <= 26; i++) {
        if (freq[i] > 0) {
            char ch;
            if (i == 26) {
                ch = ' ';
            }
            else {
                ch = 'a' + i;
            }
            Node* newNode = new Node(ch, freq[i]);
            minHeap.insert(newNode);
        }
    }

    // Huffman Tree
    while (minHeap.size() > 1) {
        Node* left = minHeap.extractMin();
        Node* right = minHeap.extractMin();

        Node* n = new Node('\0', left->freq + right->freq); //n the parent wld be the sum of its 2 childs
        n->left = left;
        n->right = right;

        minHeap.insert(n);
    }

    return minHeap.extractMin();//to return root of minheap (heaps only remaining node) (which will be root of huffman treee)
}


void encode(Node* root, string code, vector<string>& codes) {
    if (!root)
        return;

    if (!root->left && !root->right) { // as value are only at leaf nodes
        if (root->ch == ' ') {
            codes[26] = code;
        }
        else {
            codes[root->ch - 'a'] = code;
        }
    }

    encode(root->left, code + "0", codes);
    encode(root->right, code + "1", codes);
}


void decode(Node* root, const string& encodedString, string& decodedString) {
    Node* current = root;
    for (int i = 0; i < encodedString.length(); i++) {
        char bit = encodedString[i];

        if (bit == '0') {
            current = current->left;
        }
        else if (bit == '1') {
            current = current->right;
        }

        if (!current->left && !current->right) {        //leaf has the actual char
            decodedString += current->ch;
            current = root; // reset to the root
        }
    }

}

void deleteTree(Node* root) {
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main Function
int main() {
    string str = "yep it works";

    // 26 letters + space
    vector<int> freq(27, 0);
    getFrequency(str, freq);

    // print character freq
    for (int i = 0; i <= 26; i++) {
        if (freq[i] > 0) {
            if (i == 26) {
                cout << " : " << freq[i] << endl; // space 
            }
            else {
                char ch = i + 'a';
                cout << ch << ": " << freq[i] << endl;
            }
        }
    }
    cout << endl;

    // huffman Tree
    Node* root = buildHuffmanTree(freq);

    // huffman codes
    vector<string> codes(27);
    encode(root, "", codes);

    // print codes
    for (int i = 0; i <= 26; i++) {
        if (!codes[i].empty()) {
            char ch;
            if (i == 26) {
                ch = ' ';
            }
            else {
                ch = 'a' + i;
            }
            cout << ch << ": " << codes[i] << endl;
        }
    }

    // Encode
    string encodedS = "";
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (isalpha(ch)) {
            encodedS += codes[tolower(ch) - 'a'];
        }
        else if (ch == ' ') {
            encodedS += codes[26];
        }
    }

    cout << "\nEncoded String: " << encodedS << endl;

    // Decode
    string decodedString = "";
    decode(root, encodedS, decodedString);
    cout << "Decoded String: " << decodedString << endl;

    deleteTree(root);

    return 0;
}