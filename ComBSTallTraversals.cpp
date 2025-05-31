//COMPLETE BST with all the Traversals
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Helper for insert
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        // If val == node->data, duplicates not inserted (can be changed if needed)
        return node;
    }

    // Helper for search
    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        else if (val < node->data) return search(node->left, val);
        else return search(node->right, val);
    }

    // Helper for inorder traversal
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Helper for preorder traversal
    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Helper for postorder traversal
    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Helper to find minimum node in subtree
    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    // Helper for delete
    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        } else {
            // Node to be deleted found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children:
            // Get inorder successor (smallest in right subtree)
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Helper to delete entire tree (destructor)
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(int val) { root = insert(root, val); }
    bool search(int val) { return search(root, val); }
    void deleteNode(int val) { root = deleteNode(root, val); }

    void inorder() {
        inorder(root);
        cout << "\n";
    }

    void preorder() {
        preorder(root);
        cout << "\n";
    }

    void postorder() {
        postorder(root);
        cout << "\n";
    }
};

// Sample usage
int main() {
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder traversal: ";
    tree.inorder();    // 20 30 40 50 60 70 80

    cout << "Preorder traversal: ";
    tree.preorder();   // 50 30 20 40 70 60 80

    cout << "Postorder traversal: ";
    tree.postorder();  // 20 40 30 60 80 70 50

    cout << "Search 40: " << (tree.search(40) ? "Found\n" : "Not Found\n");
    cout << "Search 25: " << (tree.search(25) ? "Found\n" : "Not Found\n");

    tree.deleteNode(20);
    cout << "After deleting 20, inorder traversal: ";
    tree.inorder();    // 30 40 50 60 70 80

    tree.deleteNode(30);
    cout << "After deleting 30, inorder traversal: ";
    tree.inorder();    // 40 50 60 70 80

    tree.deleteNode(50);
    cout << "After deleting 50, inorder traversal: ";
    tree.inorder();    // 40 60 70 80

    return 0;
}