#include <iostream>
using namespace std;

template <class T>
class BSTree {
private:
    // Node structure
    struct Bnode {
        T data;
        Bnode* left;
        Bnode* right;

        Bnode(T d) : data(d), left(nullptr), right(nullptr) {}
    };

    Bnode* root; // Pointer to the root node

    // Helper function for in-order (LNR) traversal
    void inOrderHelper(Bnode* node) const {
        if (node) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // Helper function for pre-order (NLR) traversal
    void preOrderHelper(Bnode* node) const {
        if (node) {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Helper function for post-order (LRN) traversal
    void postOrderHelper(Bnode* node) const {
        if (node) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    // Helper function for recursive insert
    Bnode* insertRHelper(Bnode* node, T d) {
        if (!node)
            return new Bnode(d);
        if (d < node->data)
            node->left = insertRHelper(node->left, d);
        else if (d > node->data)
            node->right = insertRHelper(node->right, d);
        return node;
    }

    // Helper function for recursive search
    bool searchRHelper(Bnode* node, T d) const {
        if (!node)
            return false;
        if (d == node->data)
            return true;
        else if (d < node->data)
            return searchRHelper(node->left, d);
        else
            return searchRHelper(node->right, d);
    }

    // Helper function to destroy the tree (used in the public Destroy)
    void DestroyHelper(Bnode*& node) {
        if (node) {
            DestroyHelper(node->left);
            DestroyHelper(node->right);
            delete node;
            node = nullptr;
        }
    }

public:
    // Constructor
    BSTree() : root(nullptr) {}

    // Recursive insert function
    void insertR(T d) {
        root = insertRHelper(root, d);
    }

    // Iterative insert function
    void insertI(T d) {
        Bnode* newNode = new Bnode(d);
        if (!root) {
            root = newNode;
            return;
        }

        Bnode* current = root;
        Bnode* parent = nullptr;
        while (current) {
            parent = current;
            if (d < current->data)
                current = current->left;
            else if (d > current->data)
                current = current->right;
            else
                return; // Duplicate values not allowed
        }

        if (d < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    // Recursive search function
    bool searchR(T d) const {
        return searchRHelper(root, d);
    }

    // Iterative search function
    bool searchI(T d) const {
        Bnode* current = root;
        while (current) {
            if (d == current->data)
                return true;
            else if (d < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }

    // In-order traversal (LNR)
    void inOrder() const {
        inOrderHelper(root);
        cout << endl;
    }

    // Pre-order traversal (NLR)
    void preOrder() const {
        preOrderHelper(root);
        cout << endl;
    }

    // Post-order traversal (LRN)
    void postOrder() const {
        postOrderHelper(root);
        cout << endl;
    }

    // Public function to destroy the tree
    void Destroy() {
        DestroyHelper(root);
    }

    // Destructor to free memory
    ~BSTree() {
        Destroy();
    }
};

// Main function to test the class
int main() {
    BSTree<int> bst;

    // Insertion using recursive method
    bst.insertR(50);
    bst.insertR(30);
    bst.insertR(70);
    bst.insertR(20);
    bst.insertR(40);
    bst.insertR(60);
    bst.insertR(80);

    // Insertion using iterative method
    bst.insertI(35);
    bst.insertI(65);

    // Search using recursive method
    cout << "Recursive Search for 40: " << (bst.searchR(40) ? "Found" : "Not Found") << endl;

    // Search using iterative method
    cout << "Iterative Search for 65: " << (bst.searchI(65) ? "Found" : "Not Found") << endl;

    // Traversals
    cout << "In-order (LNR): ";
    bst.inOrder();

    cout << "Pre-order (NLR): ";
    bst.preOrder();

    cout << "Post-order (LRN): ";
    bst.postOrder();

    // Explicitly destroy the tree
    cout << "Destroying the tree." << endl;
    bst.Destroy();

    return 0;
}
